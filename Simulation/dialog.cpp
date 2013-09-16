
#include <QtWidgets>
#include <QTextCodec>

#include "parmdefine.h"
#include "dialog.h"
#include "detectordialog.h"

//! [0]
Dialog::Dialog()
{
    //this->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

    codec = QTextCodec::codecForName("utf-8"); //gbk utf-8

    this->setMinimumWidth(900);
    this->setMinimumHeight(630);
    toolbox = new QToolBox;

    createMenu();
    createWorkSpaceBox();
    createGridGroupBox1();
    createGridGroupBox2();
    createGridGroupBox3();
    createGridGroupBox4();
    createGridGroupBox5();
    createGridGroupBox6();
    createGridGroupBox8();
    createGridGroupBox9();
    //createGridGroupBox7();
    createButtonBox();


    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->setSpacing(2);
    mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(groupBox0);
    mainLayout->addWidget(toolbox);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    tmpString = codec->toUnicode("空间红外天文观测仿真软件");
    setWindowTitle(tmpString);
    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    //this->setWindowState(Qt::WindowMinimized);

    initParameter();

//    createWorkDirectory();
//    readConfigFile();
//    showDefaultParameter();
}

void Dialog::initParameter()
{
    fileNameList = QList<QString>();

    readSimulationConfigFile();
    loadObjectParameterFileNames();
    readInputDefaultFile();

}

void Dialog::readSimulationConfigFile(){

    QFile qfile(SIMULATIONCONFIG);
    if (!qfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&qfile);
    QString line = in.readLine();
    while (!line.isNull()) {
        QStringList tslist = line.split('=');
        if(tslist.at(0).compare("OBJECTPARAMETERFILE")==0){
            ObjectParameterFile = tslist.at(1);
        }else if(tslist.at(0).compare("INPUTDEFAULTFILE")==0){
            inputDefaultFile = tslist.at(1);
        }else if(tslist.at(0).compare("DEFAULTWORKSPACE")==0){
            defaultWorkspace = tslist.at(1);
        }else if(tslist.at(0).compare("SIMULATIONCONFIG")==0){
            simulationConfigDir = tslist.at(1);
        }
        line = in.readLine();
    }
    qfile.close();
}

void Dialog::writeSimulationConfigFile(){

    QFile qfile("simulationConfig_new.txt");
    if (!qfile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    qfile.write("DEFAULTWORKSPACE=");
    qfile.write(defaultWorkspace.toLatin1());
    qfile.write("\n");
    qfile.write("SIMULATIONCONFIG=");
    qfile.write(simulationConfigDir.toLatin1());
    qfile.write("\n");
    qfile.write("OBJECTPARAMETERFILE=");
    qfile.write(ObjectParameterFile.toLatin1());
    qfile.write("\n");
    qfile.write("INPUTDEFAULTFILE=");
    qfile.write(inputDefaultFile.toLatin1());
    qfile.write("\n");

    qfile.close();
}

void Dialog::readConfigFile(){


}

void Dialog::slotGenerateConfigAction(){

    createWorkDirectory();
    saveInputDefaultFile();
}

void Dialog::slotExecuteAction(){

    runDirectory = defaultWorkspace;

    /*
    char extStr[MAX_STRING];
    char message[MAX_STRING];
    memset(extStr, 0, MAX_STRING);
    strcat(extStr, "cd ");
    strcat(extStr, runDirectory.toLatin1().data());
    strcat(extStr, " && runsimulator.py -c ");
    strcat(extStr, lineEdit02->text().toLatin1().data());
    strcat(extStr, "_default.dat");

    if(checkBox03->isChecked()){
        strcat(extStr, " --getwise");
    }

    FILE *fpRead = popen(extStr, "r");
    if(fpRead == NULL){
        QMessageBox::warning(this, tr("跳转到工作目录"), tr("跳转到工作目录失败!"));
    }else{
        //if(fgets(message, MAX_STRING, fpRead) != NULL){
            //QMessageBox::warning(this, tr("跳转到工作目录"), message);
        //}
        pclose(fpRead);
    }*/

    QString cmdStr = "runsimulator.py";
    QStringList arguments;
    arguments.append("-c");
    arguments.append(lineEdit02->text()+"_default.dat");

    if(checkBox03->isChecked()){
        arguments.append("--getwise");
    }
    QProcess *pyCall = new QProcess(this);
    pyCall->setWorkingDirectory(runDirectory);
    pyCall->start(cmdStr, arguments);
    executeButton->setEnabled(false);
    generateConfig->setEnabled(false);
    connect(pyCall, SIGNAL(finished(int , QProcess::ExitStatus)), this, SLOT(slotPyCall()));

    QMessageBox::warning(this, tr("提示"), tr("程序正在后台运行，请稍等！"));

//    QMessageBox::warning(this, tr("跳转到工作目录"), tr("start!"));
//    QObject *parent;
//    QString cmdStr = "mkdir";
//    QStringList arguments;
//    arguments.append("-v");
//    arguments.append("abc");
//    arguments.append("cba");


//    QProcess *pyCall = new QProcess(this);
//    pyCall->setWorkingDirectory(runDirectory);
//    pyCall->start(cmdStr, arguments);
//    QMessageBox::warning(this, tr("跳转到工作目录"), tr("end!"));
}

void Dialog::slotPyCall(){

    executeButton->setEnabled(true);
    generateConfig->setEnabled(true);
    QMessageBox::warning(this, tr("提示"), tr("程序执行完成！"));
}

void Dialog::showDefaultParameter(){

}

void Dialog::createWorkDirectory()
{
    QDir *tmpDir = new QDir;
    QDateTime curTime = QDateTime::currentDateTime();
    QString timeStr = curTime.toString("yyyyMMddhhmmss");

    //runDirectory = defaultWorkspace + "/" + timeStr;
    runDirectory = defaultWorkspace;
    configDirectory = runDirectory + "/config";

    bool dirExist = tmpDir->exists(runDirectory);
    if(!dirExist){
        bool runDir = tmpDir->mkdir(runDirectory);
        if(!runDir){
            QMessageBox::warning(this, tr("创建工作目录"), tr("创建工作目录失败"));
            return;
        }
    }

    dirExist = tmpDir->exists(configDirectory);
    if(!dirExist){
        char extStr[MAX_STRING];
        memset(extStr, 0, MAX_STRING);
        strcat(extStr, "ln -s ");
        strcat(extStr, simulationConfigDir.toLatin1().data());
        strcat(extStr, " ");
        strcat(extStr, configDirectory.toLatin1().data());
        FILE *fpRead = popen(extStr, "r");
        if(fpRead == NULL){
            QMessageBox::warning(this, tr("链接config"), tr("链接config失败!"));
        }else{
            pclose(fpRead);
        }
    }
}

void Dialog::readInputDefaultFile(){

    QString inputDefaultFilePath = simulationConfigDir+"/"+inputDefaultFile;
    inputfile = new InputDefaultFile();
    inputfile->setFileName(inputDefaultFilePath);
    inputfile->readFile();


    lineEdit02->setText(inputfile->getValue("outfilprefix"));

    //观测策略
    lineEdit01->setText(defaultWorkspace);
    lineEdit11->setText(inputfile->getValue("ra"));
    lineEdit12->setText(inputfile->getValue("dec"));
    lineEdit15->setText(inputfile->getValue("dithering"));

    QString tStr = inputfile->getValue("exposure_time");
    QStringList tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit13->setText(tslist.at(0));
        lineEdit14->setText(tslist.at(1));
        lineEdit16->setText(tslist.at(2));
        lineEdit17->setText(tslist.at(3));
    }

    //光学系统特征
    lineEdit25->setText(inputfile->getValue("m1_diameter"));

    tStr = inputfile->getValue("optical_throughput");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit26->setText(tslist.at(0));
        lineEdit210->setText(tslist.at(1));
        lineEdit214->setText(tslist.at(2));
        lineEdit218->setText(tslist.at(3));
    }

    tStr = inputfile->getValue("psf_name");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit27->setText(tslist.at(0));
        lineEdit211->setText(tslist.at(1));
        lineEdit215->setText(tslist.at(2));
        lineEdit219->setText(tslist.at(3));
    }

    tStr = inputfile->getValue("psf_oversamp");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit28->setText(tslist.at(0));
        lineEdit212->setText(tslist.at(1));
        lineEdit216->setText(tslist.at(2));
        lineEdit220->setText(tslist.at(3));
    }

    tStr = inputfile->getValue("psf_mapsize");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit29->setText(tslist.at(0));
        lineEdit213->setText(tslist.at(1));
        lineEdit217->setText(tslist.at(2));
        lineEdit221->setText(tslist.at(3));
    }

    //探测器参数
    lineEdit35->setText(inputfile->getValue("image_size"));
    lineEdit36->setText(inputfile->getValue("pixel_size"));

    tStr = inputfile->getValue("readout_noise");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit37->setText(tslist.at(0));
        lineEdit311->setText(tslist.at(1));
        lineEdit315->setText(tslist.at(2));
        lineEdit319->setText(tslist.at(3));
    }
    tStr = inputfile->getValue("gain");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit38->setText(tslist.at(0));
        lineEdit312->setText(tslist.at(1));
        lineEdit316->setText(tslist.at(2));
        lineEdit320->setText(tslist.at(3));
    }
    tStr = inputfile->getValue("ccdQE_file");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit39->setText(tslist.at(0));
        lineEdit313->setText(tslist.at(1));
        lineEdit317->setText(tslist.at(2));
        lineEdit321->setText(tslist.at(3));
    }
    tStr = inputfile->getValue("nos_darkcurent");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit310->setText(tslist.at(0));
        lineEdit314->setText(tslist.at(1));
        lineEdit318->setText(tslist.at(2));
        lineEdit322->setText(tslist.at(3));
    }

    //平台稳定性参数
    tStr = inputfile->getValue("trackerror_type");
    if(tStr.compare("JITTER")==0){
        checkBox41->setChecked(true);
    }else{
        checkBox41->setChecked(false);
        lineEdit42->setReadOnly(true);
        lineEdit43->setReadOnly(true);
        lineEdit44->setReadOnly(true);
    }
    lineEdit42->setText(inputfile->getValue("trackerror_maj"));
    lineEdit43->setText(inputfile->getValue("trackerror_min"));
    lineEdit44->setText(inputfile->getValue("trackerror_ang"));

    //天光背景模型
    lineEdit51->setText(inputfile->getValue("sky_spec"));
    lineEdit52->setText(inputfile->getValue("sky_back"));

    //展源目标天体分布模型
    tStr = inputfile->getValue("extsource_file");
    if(tStr.compare("config/extsources/galaxy_sf.fit")==0){
        comboBox61->setCurrentIndex(0);
    }else if(tStr.compare("config/extsources/HII.fit")==0){
        comboBox61->setCurrentIndex(1);
    }else if(tStr.compare("config/extsources/PDR1.fit")==0){
        comboBox61->setCurrentIndex(2);
    }else if(tStr.compare("config/extsources/PDR2.fit")==0){
        comboBox61->setCurrentIndex(3);
    }else if(tStr.compare("config/extsources/PlanetaryNebular.fit")==0){
        comboBox61->setCurrentIndex(4);
    }else if(tStr.compare("config/extsources/ReflectNebula.fit")==0){
        comboBox61->setCurrentIndex(5);
    }
    lineEdit62->setText(inputfile->getValue("ext_mag"));
    lineEdit67->setText(inputfile->getValue("ext_pahfil"));
    lineEdit68->setText(inputfile->getValue("ext_pos"));
    lineEdit69->setText(inputfile->getValue("ext_shaperate"));

    //噪声背景
    tStr = inputfile->getValue("nos_cosray");
    if(tStr.compare("None", Qt::CaseInsensitive)!=0){
        checkBox81->setChecked(true);
        lineEdit81->setText(tStr);
    }else{
        lineEdit81->setText("None");
    }
    tStr = inputfile->getValue("nos_flat");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit82->setText(tslist.at(0));
        lineEdit83->setText(tslist.at(1));
        lineEdit84->setText(tslist.at(2));
        lineEdit85->setText(tslist.at(3));
    }
    tStr = inputfile->getValue("nos_darkback");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit86->setText(tslist.at(0));
        lineEdit87->setText(tslist.at(1));
        lineEdit88->setText(tslist.at(2));
        lineEdit89->setText(tslist.at(3));
    }
    tStr = inputfile->getValue("nos_zero");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit810->setText(tslist.at(0));
        lineEdit811->setText(tslist.at(1));
        lineEdit812->setText(tslist.at(2));
        lineEdit813->setText(tslist.at(3));
    }

    //探测效率参数
    tStr = inputfile->getValue("detect_aperture");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit91->setText(tslist.at(0));
        lineEdit92->setText(tslist.at(1));
        lineEdit93->setText(tslist.at(2));
        lineEdit94->setText(tslist.at(3));
    }
    tStr = inputfile->getValue("detect_snr");
    tslist = tStr.split(",");
    if(tslist.size()==4){
        lineEdit95->setText(tslist.at(0));
        lineEdit96->setText(tslist.at(1));
        lineEdit97->setText(tslist.at(2));
        lineEdit98->setText(tslist.at(3));
    }
}

void Dialog::saveInputDefaultFile(){

    inputfile->replaceValue("outfilprefix", lineEdit02->text());

    //观测策略
    inputfile->replaceValue("ra",lineEdit11->text());
    inputfile->replaceValue("dec",lineEdit12->text());
    inputfile->replaceValue("dithering",lineEdit15->text());

    QString tStr = lineEdit13->text();
    tStr.append(",");
    tStr.append(lineEdit14->text());
    tStr.append(",");
    tStr.append(lineEdit16->text());
    tStr.append(",");
    tStr.append(lineEdit17->text());
    inputfile->replaceValue("exposure_time",tStr);

    //光学系统特征
    inputfile->replaceValue("m1_diameter",lineEdit25->text());

    tStr = lineEdit26->text();
    tStr.append(",");
    tStr.append(lineEdit210->text());
    tStr.append(",");
    tStr.append(lineEdit214->text());
    tStr.append(",");
    tStr.append(lineEdit218->text());
    inputfile->replaceValue("optical_throughput",tStr);

    tStr = lineEdit27->text();
    tStr.append(",");
    tStr.append(lineEdit211->text());
    tStr.append(",");
    tStr.append(lineEdit215->text());
    tStr.append(",");
    tStr.append(lineEdit219->text());
    inputfile->replaceValue("psf_name",tStr);

    tStr = lineEdit28->text();
    tStr.append(",");
    tStr.append(lineEdit212->text());
    tStr.append(",");
    tStr.append(lineEdit216->text());
    tStr.append(",");
    tStr.append(lineEdit220->text());
    inputfile->replaceValue("psf_oversamp",tStr);

    tStr = lineEdit29->text();
    tStr.append(",");
    tStr.append(lineEdit213->text());
    tStr.append(",");
    tStr.append(lineEdit217->text());
    tStr.append(",");
    tStr.append(lineEdit221->text());
    inputfile->replaceValue("psf_mapsize",tStr);

    //探测器参数
    inputfile->replaceValue("image_size",lineEdit35->text());
    inputfile->replaceValue("pixel_size",lineEdit36->text());

    tStr = lineEdit37->text();
    tStr.append(",");
    tStr.append(lineEdit311->text());
    tStr.append(",");
    tStr.append(lineEdit315->text());
    tStr.append(",");
    tStr.append(lineEdit319->text());
    inputfile->replaceValue("readout_noise",tStr);

    tStr = lineEdit38->text();
    tStr.append(",");
    tStr.append(lineEdit312->text());
    tStr.append(",");
    tStr.append(lineEdit316->text());
    tStr.append(",");
    tStr.append(lineEdit320->text());
    inputfile->replaceValue("gain",tStr);

    tStr = lineEdit39->text();
    tStr.append(",");
    tStr.append(lineEdit313->text());
    tStr.append(",");
    tStr.append(lineEdit317->text());
    tStr.append(",");
    tStr.append(lineEdit321->text());
    inputfile->replaceValue("ccdQE_file",tStr);

    tStr = lineEdit310->text();
    tStr.append(",");
    tStr.append(lineEdit314->text());
    tStr.append(",");
    tStr.append(lineEdit318->text());
    tStr.append(",");
    tStr.append(lineEdit322->text());
    inputfile->replaceValue("nos_darkcurent",tStr);

    //平台稳定性参数
    inputfile->replaceValue("trackerror_maj",lineEdit42->text());
    inputfile->replaceValue("trackerror_min",lineEdit43->text());
    inputfile->replaceValue("trackerror_ang",lineEdit44->text());

    //天光背景模型
    inputfile->replaceValue("sky_spec",lineEdit51->text());
    inputfile->replaceValue("sky_back",lineEdit52->text());

    //展源目标天体分布模型
    inputfile->replaceValue("extsource_file",comboBox61->itemData(comboBox61->currentIndex()).toString());
    inputfile->replaceValue("ext_mag",lineEdit62->text());
    inputfile->replaceValue("ext_pahfil",lineEdit67->text());
    inputfile->replaceValue("ext_pos",lineEdit68->text());
    inputfile->replaceValue("ext_shaperate",lineEdit69->text());

    //噪声背景
    inputfile->replaceValue("nos_cosray",lineEdit81->text());

    tStr = lineEdit82->text();
    tStr.append(",");
    tStr.append(lineEdit83->text());
    tStr.append(",");
    tStr.append(lineEdit84->text());
    tStr.append(",");
    tStr.append(lineEdit85->text());
    inputfile->replaceValue("nos_flat",tStr);

    tStr = lineEdit86->text();
    tStr.append(",");
    tStr.append(lineEdit87->text());
    tStr.append(",");
    tStr.append(lineEdit88->text());
    tStr.append(",");
    tStr.append(lineEdit89->text());
    inputfile->replaceValue("nos_darkback",tStr);

    tStr = lineEdit810->text();
    tStr.append(",");
    tStr.append(lineEdit811->text());
    tStr.append(",");
    tStr.append(lineEdit812->text());
    tStr.append(",");
    tStr.append(lineEdit813->text());
    inputfile->replaceValue("nos_zero",tStr);

    //探测效率参数
    tStr = lineEdit91->text();
    tStr.append(",");
    tStr.append(lineEdit92->text());
    tStr.append(",");
    tStr.append(lineEdit93->text());
    tStr.append(",");
    tStr.append(lineEdit94->text());
    inputfile->replaceValue("detect_aperture",tStr);

    tStr = lineEdit95->text();
    tStr.append(",");
    tStr.append(lineEdit96->text());
    tStr.append(",");
    tStr.append(lineEdit97->text());
    tStr.append(",");
    tStr.append(lineEdit98->text());
    inputfile->replaceValue("detect_snr",tStr);

    QString inputDefaultFilePath = runDirectory+"/" + lineEdit02->text() + "_default.dat";
    inputfile->setFileName(inputDefaultFilePath);

    if(!inputfile->writeFile()){
        QMessageBox::warning(this, tr(""), tr("保存配置文件失败!"));
    }else{
        QMessageBox::warning(this, tr(""), tr("保存配置文件成功!"));
    }
}

void Dialog::createButtonBox()
{
    buttonBox = new QDialogButtonBox();
    generateConfig = buttonBox->addButton("生成配置", QDialogButtonBox::ActionRole);
    generateConfig->setDefault(true);
    connect(generateConfig, SIGNAL(clicked()), this, SLOT(slotGenerateConfigAction()));

    executeButton = buttonBox->addButton("生成图像", QDialogButtonBox::ActionRole);
    executeButton->setDefault(true);
    connect(executeButton, SIGNAL(clicked()), this, SLOT(slotExecuteAction()));

    buttonBox->addButton("关闭", QDialogButtonBox::AcceptRole);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

}

void Dialog::createWorkSpaceBox(){

    QGridLayout *layout = new QGridLayout;
    layout->setVerticalSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    groupBox0  = new QGroupBox();
    tmpString = codec->toUnicode("    工作路径:");
    label01 = new QLabel(tmpString);
    lineEdit01 = new QLineEdit;
    lineEdit01->setMaximumWidth(InputBoxMaxLength*3);
    button01 = new QPushButton;
    button01->setIcon(QIcon(":/images/open.png"));
    connect(button01, SIGNAL(clicked()), this, SLOT(slotOpenFile01()));
    tmpString = codec->toUnicode("输出文件前缀:");
    label02 = new QLabel(tmpString);
    lineEdit02 = new QLineEdit;
    lineEdit02->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("下载星表");
    checkBox03 = new QCheckBox(tmpString);
    checkBox03->setLayoutDirection(Qt::RightToLeft);
    checkBox03->setChecked(true);

    layout->addWidget(label01, 0, 0);
    layout->addWidget(lineEdit01, 0, 1);
    layout->addWidget(button01, 0, 2);
    layout->addWidget(label02, 0, 3);
    layout->addWidget(lineEdit02, 0, 4);
    layout->addWidget(checkBox03, 0, 5);

//    layout->setColumnStretch(0, 1);
//    layout->setColumnStretch(1, 2);
//    layout->setColumnStretch(2, 0.5);
//    layout->setColumnStretch(3, 3);

    groupBox0->setLayout(layout);
    //groupBox0->setMaximumHeight(40);
}

//Observation strategy
void Dialog::createGridGroupBox1()
{
    tmpString = codec->toUnicode("观测策略");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);

    tmpString = codec->toUnicode("赤经:");
    label11 = new QLabel(tmpString);
    lineEdit11 = new QLineEdit;
    lineEdit11->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("度");
    symble11 = new QLabel(tmpString);
    layout->addWidget(label11, 0, 0);
    layout->addWidget(lineEdit11, 0, 1);
    layout->addWidget(symble11, 0, 2);

    tmpString = codec->toUnicode("赤纬:");
    label12 = new QLabel(tmpString);
    lineEdit12 = new QLineEdit;
    lineEdit12->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("度");
    symble12 = new QLabel(tmpString);
    layout->addWidget(label12, 0, 3);
    layout->addWidget(lineEdit12, 0, 4);
    layout->addWidget(symble12, 0, 5);

    tmpString = codec->toUnicode("dithring:");
    label15 = new QLabel(tmpString);
    lineEdit15 = new QLineEdit;
    lineEdit15->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("次");
    symble15 = new QLabel(tmpString);
    layout->addWidget(label15, 0, 6);
    layout->addWidget(lineEdit15, 0, 7);
    layout->addWidget(symble15, 0, 8);

    tmpString = codec->toUnicode("曝光时间1:");
    label13 = new QLabel(tmpString);
    lineEdit13 = new QLineEdit;
    lineEdit13->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("秒");
    symble13 = new QLabel(tmpString);
    layout->addWidget(label13, 1, 0);
    layout->addWidget(lineEdit13, 1, 1);
    layout->addWidget(symble13, 1, 2);

    tmpString = codec->toUnicode("曝光时间2:");
    label14 = new QLabel(tmpString);
    lineEdit14 = new QLineEdit;
    lineEdit14->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("秒");
    symble14 = new QLabel(tmpString);
    layout->addWidget(label14, 1, 3);
    layout->addWidget(lineEdit14, 1, 4);
    layout->addWidget(symble14, 1, 5);

    tmpString = codec->toUnicode("曝光时间3:");
    label16 = new QLabel(tmpString);
    lineEdit16 = new QLineEdit;
    lineEdit16->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("秒");
    symble16 = new QLabel(tmpString);
    layout->addWidget(label16, 2, 0);
    layout->addWidget(lineEdit16, 2, 1);
    layout->addWidget(symble16, 2, 2);

    tmpString = codec->toUnicode("曝光时间4:");
    label17 = new QLabel(tmpString);
    lineEdit17 = new QLineEdit;
    lineEdit17->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("秒");
    symble17 = new QLabel(tmpString);
    layout->addWidget(label17, 2, 3);
    layout->addWidget(lineEdit17, 2, 4);
    layout->addWidget(symble17, 2, 5);

    //layout->setColumnStretch(2, 20);
    //layout->setColumnStretch(5, 20);
}

//optical system feature
void Dialog::createGridGroupBox2()
{
    tmpString = codec->toUnicode("光学系统特征");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);

    //有效孔径
    tmpString = codec->toUnicode("有效孔径(D/m):");
    label25 = new QLabel(tmpString);
    lineEdit25 = new QLineEdit;
    lineEdit25->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label25, 0, 1);
    layout->addWidget(lineEdit25, 0, 2);

    //通道1
    tmpString = codec->toUnicode("通道1");
    label21 = new QLabel(tmpString);
    layout->addWidget(label21, 1, 0);

    tmpString = codec->toUnicode("光学透过率:");
    label26 = new QLabel(tmpString);
    lineEdit26 = new QLineEdit;
    lineEdit26->setMaximumWidth(InputBoxMaxLength);
    button26 = new QPushButton;
    button26->setIcon(QIcon(":/images/open.png"));
    connect(button26, SIGNAL(clicked()), this, SLOT(slotOpenFile26()));
    layout->addWidget(label26, 1, 1);
    layout->addWidget(lineEdit26, 1, 2);
    layout->addWidget(button26, 1, 3);

    tmpString = codec->toUnicode("PSF:");
    label27 = new QLabel(tmpString);
    lineEdit27 = new QLineEdit;
    lineEdit27->setMaximumWidth(InputBoxMaxLength);
    button27 = new QPushButton;
    button27->setIcon(QIcon(":/images/open.png"));
    connect(button27, SIGNAL(clicked()), this, SLOT(slotOpenFile27()));
    layout->addWidget(label27, 1, 4);
    layout->addWidget(lineEdit27, 1, 5);
    layout->addWidget(button27, 1, 6);

    tmpString = codec->toUnicode("OverSample:");
    label28 = new QLabel(tmpString);
    lineEdit28 = new QLineEdit;
    lineEdit28->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label28, 1, 7);
    layout->addWidget(lineEdit28, 1, 8);

    tmpString = codec->toUnicode("PSFSize:");
    label29 = new QLabel(tmpString);
    lineEdit29 = new QLineEdit;
    lineEdit29->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label29, 1, 9);
    layout->addWidget(lineEdit29, 1, 10);

    //通道2
    tmpString = codec->toUnicode("通道2");
    label22 = new QLabel(tmpString);
    layout->addWidget(label22, 2, 0);

    tmpString = codec->toUnicode("光学透过率:");
    label210 = new QLabel(tmpString);
    lineEdit210 = new QLineEdit;
    lineEdit210->setMaximumWidth(InputBoxMaxLength);
    button210 = new QPushButton;
    button210->setIcon(QIcon(":/images/open.png"));
    connect(button210, SIGNAL(clicked()), this, SLOT(slotOpenFile210()));
    layout->addWidget(label210, 2, 1);
    layout->addWidget(lineEdit210, 2, 2);
    layout->addWidget(button210, 2, 3);

    tmpString = codec->toUnicode("PSF:");
    label211 = new QLabel(tmpString);
    lineEdit211 = new QLineEdit;
    lineEdit211->setMaximumWidth(InputBoxMaxLength);
    button211 = new QPushButton;
    button211->setIcon(QIcon(":/images/open.png"));
    connect(button211, SIGNAL(clicked()), this, SLOT(slotOpenFile211()));
    layout->addWidget(label211, 2, 4);
    layout->addWidget(lineEdit211, 2, 5);
    layout->addWidget(button211, 2, 6);

    tmpString = codec->toUnicode("OverSample:");
    label212 = new QLabel(tmpString);
    lineEdit212 = new QLineEdit;
    lineEdit212->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label212, 2, 7);
    layout->addWidget(lineEdit212, 2, 8);

    tmpString = codec->toUnicode("PSFSize:");
    label213 = new QLabel(tmpString);
    lineEdit213 = new QLineEdit;
    lineEdit213->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label213, 2, 9);
    layout->addWidget(lineEdit213, 2, 10);

    //通道3
    tmpString = codec->toUnicode("通道3");
    label23 = new QLabel(tmpString);
    layout->addWidget(label23, 3, 0);

    tmpString = codec->toUnicode("光学透过率:");
    label214 = new QLabel(tmpString);
    lineEdit214 = new QLineEdit;
    lineEdit214->setMaximumWidth(InputBoxMaxLength);
    button214 = new QPushButton;
    button214->setIcon(QIcon(":/images/open.png"));
    connect(button214, SIGNAL(clicked()), this, SLOT(slotOpenFile214()));
    layout->addWidget(label214, 3, 1);
    layout->addWidget(lineEdit214, 3, 2);
    layout->addWidget(button214, 3, 3);

    tmpString = codec->toUnicode("PSF:");
    label215 = new QLabel(tmpString);
    lineEdit215 = new QLineEdit;
    lineEdit215->setMaximumWidth(InputBoxMaxLength);
    button215 = new QPushButton;
    button215->setIcon(QIcon(":/images/open.png"));
    connect(button215, SIGNAL(clicked()), this, SLOT(slotOpenFile215()));
    layout->addWidget(label215, 3, 4);
    layout->addWidget(lineEdit215, 3, 5);
    layout->addWidget(button215, 3, 6);

    tmpString = codec->toUnicode("OverSample:");
    label216 = new QLabel(tmpString);
    lineEdit216 = new QLineEdit;
    lineEdit216->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label216, 3, 7);
    layout->addWidget(lineEdit216, 3, 8);

    tmpString = codec->toUnicode("PSFSize:");
    label217 = new QLabel(tmpString);
    lineEdit217 = new QLineEdit;
    lineEdit217->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label217, 3, 9);
    layout->addWidget(lineEdit217, 3, 10);

    //通道4
    tmpString = codec->toUnicode("通道4");
    label24 = new QLabel(tmpString);
    layout->addWidget(label24, 4, 0);

    tmpString = codec->toUnicode("光学透过率:");
    label218 = new QLabel(tmpString);
    lineEdit218 = new QLineEdit;
    lineEdit218->setMaximumWidth(InputBoxMaxLength);
    button218 = new QPushButton;
    button218->setIcon(QIcon(":/images/open.png"));
    connect(button218, SIGNAL(clicked()), this, SLOT(slotOpenFile218()));
    layout->addWidget(label218, 4, 1);
    layout->addWidget(lineEdit218, 4, 2);
    layout->addWidget(button218, 4, 3);

    tmpString = codec->toUnicode("PSF:");
    label219 = new QLabel(tmpString);
    lineEdit219 = new QLineEdit;
    lineEdit219->setMaximumWidth(InputBoxMaxLength);
    button219 = new QPushButton;
    button219->setIcon(QIcon(":/images/open.png"));
    connect(button219, SIGNAL(clicked()), this, SLOT(slotOpenFile219()));
    layout->addWidget(label219, 4, 4);
    layout->addWidget(lineEdit219, 4, 5);
    layout->addWidget(button219, 4, 6);

    tmpString = codec->toUnicode("OverSample:");
    label220 = new QLabel(tmpString);
    lineEdit220 = new QLineEdit;
    lineEdit220->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label220, 4, 7);
    layout->addWidget(lineEdit220, 4, 8);

    tmpString = codec->toUnicode("PSFSize:");
    label221 = new QLabel(tmpString);
    lineEdit221 = new QLineEdit;
    lineEdit221->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label221, 4, 9);
    layout->addWidget(lineEdit221, 4, 10);

}


//detector parameter
void Dialog::createGridGroupBox3()
{
    tmpString = codec->toUnicode("探测器参数");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);

    tmpString = codec->toUnicode("像元数目:");
    label35 = new QLabel(tmpString);
    lineEdit35 = new QLineEdit;
    lineEdit35->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label35, 0, 1);
    layout->addWidget(lineEdit35, 0, 2);

    tmpString = codec->toUnicode("像元尺寸:");
    label36 = new QLabel(tmpString);
    lineEdit36 = new QLineEdit;
    lineEdit36->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label36, 0, 3);
    layout->addWidget(lineEdit36, 0, 4);

    //通道1
    tmpString = codec->toUnicode("通道1");
    label31 = new QLabel(tmpString);
    layout->addWidget(label31, 1, 0);

    tmpString = codec->toUnicode("读出噪声:");
    label37 = new QLabel(tmpString);
    lineEdit37 = new QLineEdit;
    lineEdit37->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label37, 1, 1);
    layout->addWidget(lineEdit37, 1, 2);

    tmpString = codec->toUnicode("增益:");
    label38 = new QLabel(tmpString);
    lineEdit38 = new QLineEdit;
    lineEdit38->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label38, 1, 3);
    layout->addWidget(lineEdit38, 1, 4);

    tmpString = codec->toUnicode("响应曲线:");
    label39 = new QLabel(tmpString);
    lineEdit39 = new QLineEdit;
    lineEdit39->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label39, 1, 5);
    layout->addWidget(lineEdit39, 1, 6);
    button39 = new QPushButton;
    button39->setIcon(QIcon(":/images/open.png"));
    connect(button39, SIGNAL(clicked()), this, SLOT(slotOpenFile39()));
    layout->addWidget(button39, 1, 7);

    tmpString = codec->toUnicode("暗流:");
    label310 = new QLabel(tmpString);
    lineEdit310 = new QLineEdit;
    lineEdit310->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label310, 1, 8);
    layout->addWidget(lineEdit310, 1, 9);


    //通道2
    tmpString = codec->toUnicode("通道2");
    label32 = new QLabel(tmpString);
    layout->addWidget(label32, 2, 0);

    tmpString = codec->toUnicode("读出噪声:");
    label311 = new QLabel(tmpString);
    lineEdit311 = new QLineEdit;
    lineEdit311->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label311, 2, 1);
    layout->addWidget(lineEdit311, 2, 2);

    tmpString = codec->toUnicode("增益:");
    label312 = new QLabel(tmpString);
    lineEdit312 = new QLineEdit;
    lineEdit312->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label312, 2, 3);
    layout->addWidget(lineEdit312, 2, 4);

    tmpString = codec->toUnicode("响应曲线:");
    label313 = new QLabel(tmpString);
    lineEdit313 = new QLineEdit;
    lineEdit313->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label313, 2, 5);
    layout->addWidget(lineEdit313, 2, 6);
    button313 = new QPushButton;
    button313->setIcon(QIcon(":/images/open.png"));
    connect(button313, SIGNAL(clicked()), this, SLOT(slotOpenFile313()));
    layout->addWidget(button313, 2, 7);

    tmpString = codec->toUnicode("暗流:");
    label314 = new QLabel(tmpString);
    lineEdit314 = new QLineEdit;
    lineEdit314->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label314, 2, 8);
    layout->addWidget(lineEdit314, 2, 9);

    //通道3
    tmpString = codec->toUnicode("通道3");
    label33 = new QLabel(tmpString);
    layout->addWidget(label33, 3, 0);

    tmpString = codec->toUnicode("读出噪声:");
    label315 = new QLabel(tmpString);
    lineEdit315 = new QLineEdit;
    lineEdit315->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label315, 3, 1);
    layout->addWidget(lineEdit315, 3, 2);

    tmpString = codec->toUnicode("增益:");
    label316 = new QLabel(tmpString);
    lineEdit316 = new QLineEdit;
    lineEdit316->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label316, 3, 3);
    layout->addWidget(lineEdit316, 3, 4);

    tmpString = codec->toUnicode("响应曲线:");
    label317 = new QLabel(tmpString);
    lineEdit317 = new QLineEdit;
    lineEdit317->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label317, 3, 5);
    layout->addWidget(lineEdit317, 3, 6);
    button317 = new QPushButton;
    button317->setIcon(QIcon(":/images/open.png"));
    connect(button317, SIGNAL(clicked()), this, SLOT(slotOpenFile317()));
    layout->addWidget(button317, 3, 7);

    tmpString = codec->toUnicode("暗流:");
    label318 = new QLabel(tmpString);
    lineEdit318 = new QLineEdit;
    lineEdit318->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label318, 3, 8);
    layout->addWidget(lineEdit318, 3, 9);

    //通道4
    tmpString = codec->toUnicode("通道4");
    label34 = new QLabel(tmpString);
    layout->addWidget(label34, 4, 0);

    tmpString = codec->toUnicode("读出噪声:");
    label319 = new QLabel(tmpString);
    lineEdit319 = new QLineEdit;
    lineEdit319->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label319, 4, 1);
    layout->addWidget(lineEdit319, 4, 2);

    tmpString = codec->toUnicode("增益:");
    label320 = new QLabel(tmpString);
    lineEdit320 = new QLineEdit;
    lineEdit320->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label320, 4, 3);
    layout->addWidget(lineEdit320, 4, 4);

    tmpString = codec->toUnicode("响应曲线:");
    label321 = new QLabel(tmpString);
    lineEdit321 = new QLineEdit;
    lineEdit321->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label321, 4, 5);
    layout->addWidget(lineEdit321, 4, 6);
    button321 = new QPushButton;
    button321->setIcon(QIcon(":/images/open.png"));
    connect(button321, SIGNAL(clicked()), this, SLOT(slotOpenFile321()));
    layout->addWidget(button321, 4, 7);

    tmpString = codec->toUnicode("暗流:");
    label322 = new QLabel(tmpString);
    lineEdit322 = new QLineEdit;
    lineEdit322->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label322, 4, 8);
    layout->addWidget(lineEdit322, 4, 9);
}

//plantform stable parameter
void Dialog::createGridGroupBox4()
{
    tmpString = codec->toUnicode("平台稳定性参数");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);

    tmpString = codec->toUnicode("平台稳定度");
    checkBox41 = new QCheckBox(tmpString);
    checkBox41->setLayoutDirection(Qt::RightToLeft);
    layout->addWidget(checkBox41, 0, 1);
    connect(checkBox41, SIGNAL(clicked()), this, SLOT(slotCheckBox41()));

    tmpString = codec->toUnicode("横向:");
    label42 = new QLabel(tmpString);
    lineEdit42 = new QLineEdit;
    lineEdit42->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("arcsec");
    symble42 = new QLabel(tmpString);
    layout->addWidget(label42, 1, 0);
    layout->addWidget(lineEdit42, 1, 1);
    layout->addWidget(symble42, 1, 2);

    tmpString = codec->toUnicode("纵向:");
    label43 = new QLabel(tmpString);
    lineEdit43 = new QLineEdit;
    lineEdit43->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("arcsec");
    symble43 = new QLabel(tmpString);
    layout->addWidget(label43, 1, 3);
    layout->addWidget(lineEdit43, 1, 4);
    layout->addWidget(symble43, 1, 5);

    tmpString = codec->toUnicode("方向角:");
    label44 = new QLabel(tmpString);
    lineEdit44 = new QLineEdit;
    lineEdit44->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("deg");
    symble44 = new QLabel(tmpString);
    layout->addWidget(label44, 1, 6);
    layout->addWidget(lineEdit44, 1, 7);
    layout->addWidget(symble44, 1, 8);

    //layout->setColumnStretch(2, 20);
}

//sky background module
void Dialog::createGridGroupBox5()
{
    tmpString = codec->toUnicode("天光背景模型");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);

    tmpString = codec->toUnicode("天光背景谱模板:");
    label51 = new QLabel(tmpString);
    lineEdit51 = new QLineEdit;
    lineEdit51->setMaximumWidth(InputBoxMaxLength*2);
    space51 = new QLabel("");
    button51 = new QPushButton;
    button51->setIcon(QIcon(":/images/open.png"));
    connect(button51, SIGNAL(clicked()), this, SLOT(slotOpenFile51()));
    layout->addWidget(label51, 0, 0);
    layout->addWidget(lineEdit51, 0, 1);
    layout->addWidget(button51, 0, 2);
    layout->addWidget(space51, 0, 3);

    tmpString = codec->toUnicode("星等(V星等):");
    label52 = new QLabel(tmpString);
    lineEdit52 = new QLineEdit;
    lineEdit52->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label52, 1, 0);
    layout->addWidget(lineEdit52, 1, 1);

    layout->setColumnStretch(3,0.8);
}

//Object distribute module
void Dialog::createGridGroupBox6()
{

    tmpString = codec->toUnicode("展源目标天体分布模型");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);


    tmpString = codec->toUnicode("展源目标类型:");
    label61 = new QLabel(tmpString);
    comboBox61 = new QComboBox;
    comboBox61->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("星系");
    comboBox61->addItem(tmpString, "config/extsources/galaxy_sf.fit");
    tmpString = codec->toUnicode("轻II区");
    comboBox61->addItem(tmpString, "config/extsources/HII.fit");
    tmpString = codec->toUnicode("PDR区1");
    comboBox61->addItem(tmpString, "config/extsources/PDR1.fit");
    tmpString = codec->toUnicode("PDR区2");
    comboBox61->addItem(tmpString, "config/extsources/PDR2.fit");
    tmpString = codec->toUnicode("行星状星云");
    comboBox61->addItem(tmpString, "config/extsources/PlanetaryNebular.fit");
    tmpString = codec->toUnicode("反射星云");
    comboBox61->addItem(tmpString, "config/extsources/ReflectNebula.fit");

    tmpString = codec->toUnicode("目标亮度(NICE-1):");
    label62 = new QLabel(tmpString);
    lineEdit62 = new QLineEdit;
    lineEdit62->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("mag/arcsec2");
    unit62 = new QLabel(tmpString);

    tmpString = codec->toUnicode("ExtModel+qPAH:");
    label63 = new QLabel(tmpString);
    comboBox63 = new QComboBox;
    tmpString = codec->toUnicode("MW3.1_00(0.47)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("MW3.1_10(1.12)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("MW3.1_20(1.77)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("MW3.1_30(2.50)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("MW3.1_40(3.19)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("MW3.1_50(3.90)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("MW3.1_60(4.58)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("LMC2_00(0.75)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("LMC2_05(1.49)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("LMC2_10(2.37)");
    comboBox63->addItem(tmpString);
    tmpString = codec->toUnicode("smc(0.10)");
    comboBox63->addItem(tmpString);

    tmpString = codec->toUnicode("");
    label64 = new QLabel(tmpString);
    tmpString = codec->toUnicode("U_single");
    checkBox64 = new QCheckBox(tmpString);
    checkBox64->setLayoutDirection(Qt::RightToLeft);

    tmpString = codec->toUnicode("Umin:");
    label65 = new QLabel(tmpString);
    comboBox65 = new QComboBox;
    tmpString = codec->toUnicode("0.10");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("0.15");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("0.20");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("0.30");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("0.40");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("0.50");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("0.70");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("0.80");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("1.00");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("1.20");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("1.50");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("2.00");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("2.50");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("3.00");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("4.00");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("5.00");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("7.00");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("8.00");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("10.0");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("12.0");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("15.0");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("20.0");
    comboBox65->addItem(tmpString);
    tmpString = codec->toUnicode("25.0");
    comboBox65->addItem(tmpString);

    tmpString = codec->toUnicode("Umax:");
    label66 = new QLabel(tmpString);
    comboBox66 = new QComboBox;
    comboBox66->setMinimumWidth(100);
    tmpString = codec->toUnicode("1e3");
    comboBox66->addItem(tmpString);
    tmpString = codec->toUnicode("1e4");
    comboBox66->addItem(tmpString);
    tmpString = codec->toUnicode("1e5");
    comboBox66->addItem(tmpString);
    tmpString = codec->toUnicode("1e6");
    comboBox66->addItem(tmpString);
    tmpString = codec->toUnicode("1e7");
    comboBox66->addItem(tmpString);

    tmpString = codec->toUnicode("PAHTempFile:");
    label67 = new QLabel(tmpString);
    lineEdit67 = new QLineEdit;
    tmpString = codec->toUnicode("无匹配文件");
    lineEdit67->setText(tmpString);
    lineEdit67->setReadOnly(true);

    tmpString = codec->toUnicode("展源位置:");
    label68 = new QLabel(tmpString);
    lineEdit68 = new QLineEdit;
    lineEdit68->setMaximumWidth(InputBoxMaxLength);
    tmpString = codec->toUnicode("形状倍率:");
    label69 = new QLabel(tmpString);
    lineEdit69 = new QLineEdit;
    lineEdit69->setMaximumWidth(InputBoxMaxLength);

    layout->addWidget(label61,    0, 0);
    layout->addWidget(comboBox61, 0, 1);
    layout->addWidget(label62,    0, 2);
    layout->addWidget(lineEdit62, 0, 3);
    layout->addWidget(unit62,     0, 4);

    layout->addWidget(label68,    1, 0);
    layout->addWidget(lineEdit68, 1, 1);
    layout->addWidget(label69,    1, 2);
    layout->addWidget(lineEdit69, 1, 3);

    layout->addWidget(label63,    2, 0);
    layout->addWidget(comboBox63, 2, 1);
    layout->addWidget(label65,    2, 2);
    layout->addWidget(comboBox65, 2, 3);
    layout->addWidget(label66,    2, 5);
    layout->addWidget(comboBox66, 2, 6);

    //layout->addWidget(label64,    2, 0);
    layout->addWidget(checkBox64, 3, 1);
    //void	addWidget(QWidget * widget, int fromRow, int fromColumn, int rowSpan, int columnSpan, Qt::Alignment alignment = 0)
    layout->addWidget(label67,    3, 2);
    layout->addWidget(lineEdit67, 3, 3, 1, 2);

    connect(checkBox64, SIGNAL(clicked()), this, SLOT(slotCheckBox64()));
    connect(comboBox63, SIGNAL(activated(int)), this, SLOT(slotSetValueEdit67()));
    connect(comboBox65, SIGNAL(activated(int)), this, SLOT(slotSetValueEdit67()));
    connect(comboBox66, SIGNAL(activated(int)), this, SLOT(slotSetValueEdit67()));

}

//output type select
void Dialog::createGridGroupBox7()
{
    tmpString = codec->toUnicode("输出类型选择");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);

    tmpString = codec->toUnicode("输出类型:");
    label71 = new QLabel(tmpString);
    comboBox71 = new QComboBox;
    comboBox71->setMaximumWidth(InputBoxMaxLength+50);
    tmpString = codec->toUnicode("仅图像输出");
    comboBox71->addItem(tmpString);
    tmpString = codec->toUnicode("仅灵敏度输出");
    comboBox71->addItem(tmpString);
    tmpString = codec->toUnicode("二者同时输出");
    comboBox71->addItem(tmpString);
    label72 = new QLabel("");
    layout->addWidget(label71, 0, 0);
    layout->addWidget(comboBox71, 0, 1);
    layout->addWidget(label72, 0, 2);

    layout->setColumnStretch(2, 20);
}

//noise background
void Dialog::createGridGroupBox8()
{
    tmpString = codec->toUnicode("噪声背景");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);

    tmpString = codec->toUnicode("宇宙射线");
    checkBox81 = new QCheckBox(tmpString);
    checkBox81->setLayoutDirection(Qt::RightToLeft);
    lineEdit81 = new QLineEdit;
    lineEdit81->setVisible(false);
    layout->addWidget(checkBox81, 0, 0);
    layout->addWidget(lineEdit81, 0, 1);
    connect(checkBox81, SIGNAL(clicked()), this, SLOT(slotCheckBox81()));


    tmpString = codec->toUnicode("平场1:");
    label82 = new QLabel(tmpString);
    lineEdit82 = new QLineEdit;
    lineEdit82->setMaximumWidth(InputBoxMaxLength);
    button82 = new QPushButton;
    button82->setIcon(QIcon(":/images/open.png"));
    connect(button82, SIGNAL(clicked()), this, SLOT(slotOpenFile82()));
    layout->addWidget(label82, 1, 0);
    layout->addWidget(lineEdit82, 1, 1);
    layout->addWidget(button82, 1, 2);

    tmpString = codec->toUnicode("平场2:");
    label83 = new QLabel(tmpString);
    lineEdit83 = new QLineEdit;
    lineEdit83->setMaximumWidth(InputBoxMaxLength);
    button83 = new QPushButton;
    button83->setIcon(QIcon(":/images/open.png"));
    connect(button83, SIGNAL(clicked()), this, SLOT(slotOpenFile83()));
    layout->addWidget(label83, 1, 3);
    layout->addWidget(lineEdit83, 1, 4);
    layout->addWidget(button83, 1, 5);

    tmpString = codec->toUnicode("平场3:");
    label84 = new QLabel(tmpString);
    lineEdit84 = new QLineEdit;
    lineEdit84->setMaximumWidth(InputBoxMaxLength);
    button84 = new QPushButton;
    button84->setIcon(QIcon(":/images/open.png"));
    connect(button84, SIGNAL(clicked()), this, SLOT(slotOpenFile84()));
    layout->addWidget(label84, 1, 6);
    layout->addWidget(lineEdit84, 1, 7);
    layout->addWidget(button84, 1, 8);

    tmpString = codec->toUnicode("平场4:");
    label85 = new QLabel(tmpString);
    lineEdit85 = new QLineEdit;
    lineEdit85->setMaximumWidth(InputBoxMaxLength);
    button85 = new QPushButton;
    button85->setIcon(QIcon(":/images/open.png"));
    connect(button85, SIGNAL(clicked()), this, SLOT(slotOpenFile85()));
    layout->addWidget(label85, 1, 9);
    layout->addWidget(lineEdit85, 1, 10);
    layout->addWidget(button85, 1, 11);

    tmpString = codec->toUnicode("热背景1:");
    label86 = new QLabel(tmpString);
    lineEdit86 = new QLineEdit;
    lineEdit86->setMaximumWidth(InputBoxMaxLength);
    button86 = new QPushButton;
    button86->setIcon(QIcon(":/images/open.png"));
    connect(button86, SIGNAL(clicked()), this, SLOT(slotOpenFile86()));
    layout->addWidget(label86, 2, 0);
    layout->addWidget(lineEdit86, 2, 1);
    layout->addWidget(button86, 2, 2);

    tmpString = codec->toUnicode("热背景2:");
    label87 = new QLabel(tmpString);
    lineEdit87 = new QLineEdit;
    lineEdit87->setMaximumWidth(InputBoxMaxLength);
    button87 = new QPushButton;
    button87->setIcon(QIcon(":/images/open.png"));
    connect(button87, SIGNAL(clicked()), this, SLOT(slotOpenFile87()));
    layout->addWidget(label87, 2, 3);
    layout->addWidget(lineEdit87, 2, 4);
    layout->addWidget(button87, 2, 5);

    tmpString = codec->toUnicode("热背景3:");
    label88 = new QLabel(tmpString);
    lineEdit88 = new QLineEdit;
    lineEdit88->setMaximumWidth(InputBoxMaxLength);
    button88 = new QPushButton;
    button88->setIcon(QIcon(":/images/open.png"));
    connect(button88, SIGNAL(clicked()), this, SLOT(slotOpenFile88()));
    layout->addWidget(label88, 2, 6);
    layout->addWidget(lineEdit88, 2, 7);
    layout->addWidget(button88, 2, 8);

    tmpString = codec->toUnicode("热背景4:");
    label89 = new QLabel(tmpString);
    lineEdit89 = new QLineEdit;
    lineEdit89->setMaximumWidth(InputBoxMaxLength);
    button89 = new QPushButton;
    button89->setIcon(QIcon(":/images/open.png"));
    connect(button89, SIGNAL(clicked()), this, SLOT(slotOpenFile89()));
    layout->addWidget(label89, 2, 9);
    layout->addWidget(lineEdit89, 2, 10);
    layout->addWidget(button89, 2, 11);

    tmpString = codec->toUnicode("本底1:");
    label810 = new QLabel(tmpString);
    lineEdit810 = new QLineEdit;
    lineEdit810->setMaximumWidth(InputBoxMaxLength);
    button810 = new QPushButton;
    button810->setIcon(QIcon(":/images/open.png"));
    connect(button810, SIGNAL(clicked()), this, SLOT(slotOpenFile810()));
    layout->addWidget(label810, 3, 0);
    layout->addWidget(lineEdit810, 3, 1);
    layout->addWidget(button810, 3, 2);

    tmpString = codec->toUnicode("本底2:");
    label811 = new QLabel(tmpString);
    lineEdit811 = new QLineEdit;
    lineEdit811->setMaximumWidth(InputBoxMaxLength);
    button811 = new QPushButton;
    button811->setIcon(QIcon(":/images/open.png"));
    connect(button811, SIGNAL(clicked()), this, SLOT(slotOpenFile811()));
    layout->addWidget(label811, 3, 3);
    layout->addWidget(lineEdit811, 3, 4);
    layout->addWidget(button811, 3, 5);

    tmpString = codec->toUnicode("本底3:");
    label812 = new QLabel(tmpString);
    lineEdit812 = new QLineEdit;
    lineEdit812->setMaximumWidth(InputBoxMaxLength);
    button812 = new QPushButton;
    button812->setIcon(QIcon(":/images/open.png"));
    connect(button812, SIGNAL(clicked()), this, SLOT(slotOpenFile812()));
    layout->addWidget(label812, 3, 6);
    layout->addWidget(lineEdit812, 3, 7);
    layout->addWidget(button812, 3, 8);

    tmpString = codec->toUnicode("本底4:");
    label813 = new QLabel(tmpString);
    lineEdit813 = new QLineEdit;
    lineEdit813->setMaximumWidth(InputBoxMaxLength);
    button813 = new QPushButton;
    button813->setIcon(QIcon(":/images/open.png"));
    connect(button813, SIGNAL(clicked()), this, SLOT(slotOpenFile813()));
    layout->addWidget(label813, 3, 9);
    layout->addWidget(lineEdit813, 3, 10);
    layout->addWidget(button813, 3, 11);

}

//detection efficiency parameter
void Dialog::createGridGroupBox9()
{
    tmpString = codec->toUnicode("探测效率参数");

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    toolbox->addItem(page, tmpString);

    layout->setVerticalSpacing(WidgetVerticalSpacing);
    layout->setContentsMargins(LayoutContentsMargin,LayoutContentsMarginTop,LayoutContentsMargin,LayoutContentsMargin);

    tmpString = codec->toUnicode("有效能量孔径1:");
    label91 = new QLabel(tmpString);
    lineEdit91 = new QLineEdit;
    lineEdit91->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label91, 0, 0);
    layout->addWidget(lineEdit91, 0, 1);
    tmpString = codec->toUnicode("有效能量孔径2:");
    label92 = new QLabel(tmpString);
    lineEdit92 = new QLineEdit;
    lineEdit92->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label92, 0, 2);
    layout->addWidget(lineEdit92, 0, 3);
    tmpString = codec->toUnicode("有效能量孔径3:");
    label93 = new QLabel(tmpString);
    lineEdit93 = new QLineEdit;
    lineEdit93->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label93, 0, 4);
    layout->addWidget(lineEdit93, 0, 5);
    tmpString = codec->toUnicode("有效能量孔径4:");
    label94 = new QLabel(tmpString);
    lineEdit94 = new QLineEdit;
    lineEdit94->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label94, 0, 6);
    layout->addWidget(lineEdit94, 0, 7);

    tmpString = codec->toUnicode("信噪比1:");
    label95 = new QLabel(tmpString);
    lineEdit95 = new QLineEdit;
    lineEdit95->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label95, 1, 0);
    layout->addWidget(lineEdit95, 1, 1);
    tmpString = codec->toUnicode("信噪比2:");
    label96 = new QLabel(tmpString);
    lineEdit96 = new QLineEdit;
    lineEdit96->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label96, 1, 2);
    layout->addWidget(lineEdit96, 1, 3);
    tmpString = codec->toUnicode("信噪比3:");
    label97 = new QLabel(tmpString);
    lineEdit97 = new QLineEdit;
    lineEdit97->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label97, 1, 4);
    layout->addWidget(lineEdit97, 1, 5);
    tmpString = codec->toUnicode("信噪比4:");
    label98 = new QLabel(tmpString);
    lineEdit98 = new QLineEdit;
    lineEdit98->setMaximumWidth(InputBoxMaxLength);
    layout->addWidget(label98, 1, 6);
    layout->addWidget(lineEdit98, 1, 7);
}

void Dialog::slotOpenFile01()
{
    //QString fileName = QFileDialog::getOpenFileName(this);
    //lineEdit22->setText(fileName);
    //QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Images"),
                            //QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                           // "*.jpg *.png");
//    QMessageBox msgBox;
//    msgBox.setText("Get File name:");
//    msgBox.setInformativeText("File Name is:"+fileName);
//    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//    msgBox.setDefaultButton(QMessageBox::Save);
//    int ret = msgBox.exec();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                defaultWorkspace,
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    if(dir!=NULL&&dir!=""){
        lineEdit01->setText(dir);
        defaultWorkspace = dir;
    }
    //QString fileName = QFileDialog::getOpenFileName(this);
    //lineEdit01->setText(fileName);
}


void Dialog::slotOpenFile26()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit26->setText(fileName);
}

void Dialog::slotOpenFile27()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit27->setText(fileName);
}

void Dialog::slotOpenFile210()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit210->setText(fileName);
}

void Dialog::slotOpenFile211()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit211->setText(fileName);
}

void Dialog::slotOpenFile214()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit214->setText(fileName);
}

void Dialog::slotOpenFile215()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit215->setText(fileName);
}

void Dialog::slotOpenFile218()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit218->setText(fileName);
}

void Dialog::slotCheckBox41()
{
    if(checkBox41->isChecked())
    {
        lineEdit42->setReadOnly(false);
        lineEdit43->setReadOnly(false);
        lineEdit44->setReadOnly(false);
    }else{
        lineEdit42->setReadOnly(true);
        lineEdit43->setReadOnly(true);
        lineEdit44->setReadOnly(true);
    }
}

void Dialog::slotOpenFile219()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit219->setText(fileName);
}

void Dialog::slotOpenFile39()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    lineEdit39->setText(fileName);
}

void Dialog::slotOpenFile313()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit313->setText(fileName);
}

void Dialog::slotOpenFile317()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit317->setText(fileName);
}

void Dialog::slotOpenFile321()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit321->setText(fileName);
}

void Dialog::slotOpenFile51()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit51->setText(fileName);
}

void Dialog::slotCheckBox81()
{
    if(checkBox81->isChecked())
    {
        lineEdit81->setText("config/noises/CRs_temp_700_723_1000.pkl,\
                            config/noises/CRs_temp_700_723_1000.pkl,\
                            config/noises/CRs_temp_700_723_1000.pkl,\
                            config/noises/CRs_temp_700_723_1000.pkl");
    }else{
        lineEdit81->setText("None");
    }
}

void Dialog::slotOpenFile82()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit82->setText(fileName);
}

void Dialog::slotOpenFile83()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit83->setText(fileName);
}

void Dialog::slotOpenFile84()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit84->setText(fileName);
}

void Dialog::slotOpenFile85()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit85->setText(fileName);
}

void Dialog::slotOpenFile86()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit86->setText(fileName);
}

void Dialog::slotOpenFile87()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit87->setText(fileName);
}

void Dialog::slotOpenFile88()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit88->setText(fileName);
}

void Dialog::slotOpenFile89()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit89->setText(fileName);
}

void Dialog::slotOpenFile813()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit813->setText(fileName);
}

void Dialog::slotOpenFile810()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit810->setText(fileName);
}

void Dialog::slotOpenFile811()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit811->setText(fileName);
}

void Dialog::slotOpenFile812()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName!=NULL&&fileName!="")
        lineEdit812->setText(fileName);
}

void Dialog::createMenu()
{
    menuBar = new QMenuBar;

    tmpString = codec->toUnicode("文件");
    fileMenu = new QMenu(tmpString, this);
    tmpString = codec->toUnicode("打开");
    openAction = fileMenu->addAction(tmpString);
    tmpString = codec->toUnicode("保存");
    saveAction = fileMenu->addAction(tmpString);
    tmpString = codec->toUnicode("另存为");
    saveAsAction = fileMenu->addAction(tmpString);
    tmpString = codec->toUnicode("退出");
    exitAction = fileMenu->addAction(tmpString);

    tmpString = codec->toUnicode("功能");
    functionMenu = new QMenu(tmpString, this);
    tmpString = codec->toUnicode("PSF仿真");
    psfAction = functionMenu->addAction(tmpString);
    connect(psfAction, SIGNAL(triggered()), this, SLOT(showPSFDialog()));
    tmpString = codec->toUnicode("探测器仿真");
    detectorAction = functionMenu->addAction(tmpString);
    connect(detectorAction, SIGNAL(triggered()), this, SLOT(showDetectorDialog()));

    tmpString = codec->toUnicode("帮助");
    helpMenu = new QMenu(tmpString, this);
    tmpString = codec->toUnicode("关于该软件");
    aboutAction = helpMenu->addAction(tmpString);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    tmpString = codec->toUnicode("帮助");
    helpAction = helpMenu->addAction(tmpString);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(functionMenu);
    menuBar->addMenu(helpMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    //connect
}

void Dialog::showPSFDialog()
{
//    PSFDialog *psfDialog = new PSFDialog;
//    psfDialog->show();
}

void Dialog::showDetectorDialog()
{
    DetectorDialog *detectorDialog = new DetectorDialog;
    detectorDialog->show();
}

void Dialog::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}


void Dialog::slotCheckBox64()
{
    if(checkBox64->isChecked())
    {
        comboBox66->setEnabled(false);
    }else{
        comboBox66->setEnabled(true);
    }
    slotSetValueEdit67();
}

void Dialog::slotSetValueEdit67()
{
    QString tmpFileName("U");
    if(checkBox64->isChecked())
    {
        QString comboBox63Value = comboBox63->currentText();
        QString comboBox65Value = comboBox65->currentText();
        comboBox63Value.remove(QRegExp("\\(\\d.\\d{2}\\)"));
        comboBox65Value.append("_");
        tmpFileName.append(comboBox65Value).append(comboBox65Value).append(comboBox63Value).append(".fits");
    }else{
        QString comboBox63Value = comboBox63->currentText();
        QString comboBox65Value = comboBox65->currentText();
        QString comboBox66Value = comboBox66->currentText();
        comboBox63Value.remove(QRegExp("\\(\\d.\\d{2}\\)"));
        comboBox65Value.append("_");
        comboBox66Value.append("_");
        tmpFileName.append(comboBox65Value).append(comboBox66Value).append(comboBox63Value).append(".fits");
    }
    if(hasSameFileName(tmpFileName))
    {
        QString tStr("config/pahtemp/");
        lineEdit67->setText(tStr.append(tmpFileName));
    }else{
        tmpString = codec->toUnicode("无匹配文件");
        lineEdit67->setText(tmpString);
    }
}

bool Dialog::loadObjectParameterFileNames()
{
    QString tStr = simulationConfigDir;
    tStr.append("/pahtemp/");
    tStr.append(ObjectParameterFile);

    QFile qfile(tStr);
    if (!qfile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("提示"), tr("加载参数配置文件失败！"));
        return false;
    }

    QTextStream in(&qfile);
    QString line = in.readLine();
    while (!line.isNull()) {
        fileNameList.append(line);
        line = in.readLine();
    }

    return true;
}


bool Dialog::hasSameFileName(QString tmpFileName)
{
    bool findName = false;
    for (int i = 0; i < fileNameList.size(); ++i) {
        if (fileNameList.at(i) == tmpFileName)
        {
            findName = true;
            break;
        }
    }

    return findName;
}
