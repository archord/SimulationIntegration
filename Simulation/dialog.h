/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "inputdefaultfile.h"

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QTextCodec;
class QFileDialog;
class QRadioButton;
class QComboBox;
class QCheckBox;
class QToolBox;
QT_END_NAMESPACE

//! [0]
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();

private:
    void createMenu();
    void createWorkSpaceBox();
    void createGridGroupBox1();
    void createGridGroupBox2();
    void createGridGroupBox3();
    void createGridGroupBox4();
    void createGridGroupBox5();
    void createGridGroupBox6();
    void createGridGroupBox7();
    void createGridGroupBox8();
    void createGridGroupBox9();
    void createButtonBox();

    void initParameter();
    void readSimulationConfigFile();
    void writeSimulationConfigFile();
    void readInputDefaultFile();
    void createWorkDirectory();
    void readConfigFile();
    void showDefaultParameter();
    void saveInputDefaultFile();

    bool loadObjectParameterFileNames();
    bool hasSameFileName(QString tmpFileName);

    enum { InputBoxMaxLength = 100,
           NumButtons = 4,
           WidgetVerticalSpacing = 2,
           LayoutContentsMargin = 2,
           LayoutContentsMarginTop = 6,
           ButtonMaximumHeight = 27
         };


    QTextCodec *codec;
    QString tmpString;
    QString ObjectParameterFile;
    QString inputDefaultFile;
    QString defaultWorkspace;
    QString simulationConfigDir;

    QString simulationDirectory;
    QString runDirectory;
    QString configDirectory;

    InputDefaultFile *inputfile;
    //菜单
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;

    QMenu *functionMenu;
    QAction *psfAction;
    QAction *detectorAction;

    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *helpAction;

    QDialogButtonBox *buttonBox;

    QToolBox *toolbox;

    //工作路径
    QGroupBox *groupBox0;
    QLabel *label01;
    QLineEdit *lineEdit01;
    QPushButton *button01;
    QLabel *label02;
    QLineEdit *lineEdit02;
    QCheckBox *checkBox03;

    //观测策略
    QLabel *label11;
    QLineEdit *lineEdit11;
    QLabel *symble11;

    QLabel *label12;
    QLineEdit *lineEdit12;
    QLabel *symble12;

    QLabel *label13;
    QLineEdit *lineEdit13;
    QLabel *symble13;

    QLabel *label14;
    QLineEdit *lineEdit14;
    QLabel *symble14;

    QLabel *label15;
    QLineEdit *lineEdit15;
    QLabel *symble15;

    QLabel *label16;
    QLineEdit *lineEdit16;
    QLabel *symble16;

    QLabel *label17;
    QLineEdit *lineEdit17;
    QLabel *symble17;

    //光学系统特征
    QLabel *label21;
    QLabel *label22;
    QLabel *label23;
    QLabel *label24;

    QLabel *label25;
    QLineEdit *lineEdit25;

    QLabel *label26;
    QLabel *label27;
    QLabel *label28;
    QLabel *label29;
    QLabel *label210;
    QLabel *label211;
    QLabel *label212;
    QLabel *label213;
    QLabel *label214;
    QLabel *label215;
    QLabel *label216;
    QLabel *label217;
    QLabel *label218;
    QLabel *label219;
    QLabel *label220;
    QLabel *label221;
    QLineEdit *lineEdit26;
    QLineEdit *lineEdit27;
    QLineEdit *lineEdit28;
    QLineEdit *lineEdit29;
    QLineEdit *lineEdit210;
    QLineEdit *lineEdit211;
    QLineEdit *lineEdit212;
    QLineEdit *lineEdit213;
    QLineEdit *lineEdit214;
    QLineEdit *lineEdit215;
    QLineEdit *lineEdit216;
    QLineEdit *lineEdit217;
    QLineEdit *lineEdit218;
    QLineEdit *lineEdit219;
    QLineEdit *lineEdit220;
    QLineEdit *lineEdit221;
    QPushButton *button26;
    QPushButton *button27;
    QPushButton *button210;
    QPushButton *button211;
    QPushButton *button214;
    QPushButton *button215;
    QPushButton *button218;
    QPushButton *button219;

    //探测器参数
    QLabel *label31;
    QLabel *label32;
    QLabel *label33;
    QLabel *label34;

    QLabel *label35;
    QLineEdit *lineEdit35;
    QLabel *label36;
    QLineEdit *lineEdit36;

    QLabel *label37;
    QLineEdit *lineEdit37;
    QLabel *label38;
    QLineEdit *lineEdit38;
    QLabel *label39;
    QLineEdit *lineEdit39;
    QLabel *label310;
    QLineEdit *lineEdit310;

    QLabel *label311;
    QLineEdit *lineEdit311;
    QLabel *label312;
    QLineEdit *lineEdit312;
    QLabel *label313;
    QLineEdit *lineEdit313;
    QLabel *label314;
    QLineEdit *lineEdit314;

    QLabel *label315;
    QLineEdit *lineEdit315;
    QLabel *label316;
    QLineEdit *lineEdit316;
    QLabel *label317;
    QLineEdit *lineEdit317;
    QLabel *label318;
    QLineEdit *lineEdit318;

    QLabel *label319;
    QLineEdit *lineEdit319;
    QLabel *label320;
    QLineEdit *lineEdit320;
    QLabel *label321;
    QLineEdit *lineEdit321;
    QLabel *label322;
    QLineEdit *lineEdit322;

    QPushButton *button39;
    QPushButton *button313;
    QPushButton *button317;
    QPushButton *button321;

    //平台稳定性参数
    QCheckBox *checkBox41;

    QLabel *label42;
    QLineEdit *lineEdit42;
    QLabel *symble42;
    QLabel *label43;
    QLineEdit *lineEdit43;
    QLabel *symble43;
    QLabel *label44;
    QLineEdit *lineEdit44;
    QLabel *symble44;

    //天光背景模型
    QLabel *label51;
    QLineEdit *lineEdit51;
    QPushButton *button51;
    QLabel *space51;

    QLabel *label52;
    QLineEdit *lineEdit52;

    //目标天体参数
    QLabel *label61;
    QComboBox *comboBox61;
    QLabel *label62;
    QLineEdit *lineEdit62;
    QLabel *unit62;
    QLabel *label63;
    QComboBox *comboBox63;
    QLabel *label64;
    QCheckBox *checkBox64;
    QLabel *label65;
    QComboBox *comboBox65;
    QLabel *label66;
    QComboBox *comboBox66;
    QLabel *label67;
    QLineEdit *lineEdit67;
    QLabel *label68;
    QLineEdit *lineEdit68;
    QLabel *label69;
    QLineEdit *lineEdit69;

    //输出类型选择
    QLabel *label71;
    QLabel *label72;
    QComboBox *comboBox71;  //QComboBox

    //噪声背景
    QLabel *label81;
    QCheckBox *checkBox81;
    QLineEdit *lineEdit81;
    QLabel *label82;
    QLineEdit *lineEdit82;
    QPushButton *button82;
    QLabel *label83;
    QLineEdit *lineEdit83;
    QPushButton *button83;
    QLabel *label84;
    QLineEdit *lineEdit84;
    QPushButton *button84;
    QLabel *label85;
    QLineEdit *lineEdit85;
    QPushButton *button85;
    QLabel *label86;
    QLineEdit *lineEdit86;
    QPushButton *button86;
    QLabel *label87;
    QLineEdit *lineEdit87;
    QPushButton *button87;
    QLabel *label88;
    QLineEdit *lineEdit88;
    QPushButton *button88;
    QLabel *label89;
    QLineEdit *lineEdit89;
    QPushButton *button89;
    QLabel *label810;
    QLineEdit *lineEdit810;
    QPushButton *button810;
    QLabel *label811;
    QLineEdit *lineEdit811;
    QPushButton *button811;
    QLabel *label812;
    QLineEdit *lineEdit812;
    QPushButton *button812;
    QLabel *label813;
    QLineEdit *lineEdit813;
    QPushButton *button813;


    //探测效率参数
    QLabel *label91;
    QLineEdit *lineEdit91;
    QLabel *label92;
    QLineEdit *lineEdit92;
    QLabel *label93;
    QLineEdit *lineEdit93;
    QLabel *label94;
    QLineEdit *lineEdit94;
    QLabel *label95;
    QLineEdit *lineEdit95;
    QLabel *label96;
    QLineEdit *lineEdit96;
    QLabel *label97;
    QLineEdit *lineEdit97;
    QLabel *label98;
    QLineEdit *lineEdit98;

    //执行按钮
    QPushButton *generateConfig;
    QPushButton *executeButton;

    QList<QString> fileNameList;

private slots:
    void slotPyCall();
    void slotOpenFile01();
    void slotOpenFile26();
    void slotOpenFile27();
    void slotOpenFile210();
    void slotOpenFile211();
    void slotOpenFile214();
    void slotOpenFile215();
    void slotOpenFile218();
    void slotOpenFile219();

    void slotOpenFile39();
    void slotOpenFile313();
    void slotOpenFile317();
    void slotOpenFile321();

    void slotCheckBox41();

    void slotOpenFile51();

    void slotCheckBox81();
    void slotOpenFile82();
    void slotOpenFile83();
    void slotOpenFile84();
    void slotOpenFile85();
    void slotOpenFile86();
    void slotOpenFile87();
    void slotOpenFile88();
    void slotOpenFile89();
    void slotOpenFile810();
    void slotOpenFile811();
    void slotOpenFile812();
    void slotOpenFile813();

    void slotCheckBox64();
    void slotSetValueEdit67();

    void slotExecuteAction();
    void slotGenerateConfigAction();

    void showPSFDialog();
    void showDetectorDialog();
    void about();
};
//! [0]

#endif // DIALOG_H
