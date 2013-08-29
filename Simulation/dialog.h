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
#include "stinyconfigfile.h"
#include "skyconfigfile.h"

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
QT_END_NAMESPACE

//! [0]
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();

private:
    void initParameter();
    void createMenu();
    void createGridGroupBox1();
    void createGridGroupBox2();
    void createGridGroupBox3();
    void createGridGroupBox4();
    void createGridGroupBox5();
    void createGridGroupBox6();
    void createGridGroupBox7();
    void createButtonBox();
    void createWorkDirectory(QString path);
    void readConfigFile();
    void showDefaultParameter();
    void saveParameter();

    bool loadObjectParameterFileNames();
    bool hasSameFileName(QString tmpFileName);

    enum { InputBoxMaxLength = 100,
           NumButtons = 4,
           WidgetVerticalSpacing = 2,
           LayoutContentsMargin = 2,
           LayoutContentsMarginTop = 6,
           ButtonMaximumHeight = 27
         };

    QString ObjectParameterFile;

    QTextCodec *codec;
    QString tmpString;
    StinyConfigFile *stinyConf;
    SkyConfigFile * skyConf;

    QString simulationDirectory;
    QString runDirectory;
    QString psfDirectory;
    QString stuffDirectory;
    QString skyDirectory;

    QString curDirectory;
    QString confDirectory;
    QString tempDirectory;
    QString outputDirectory;

    char curStinyConf[MAX_STRING];
    char curSkyConf[MAX_STRING];

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

    //观测策略
    QGroupBox *gridGroupBox1;
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

    //光学系统特征
    QGroupBox *gridGroupBox2;
    QLabel *label21;
    QLabel *label22;
    QLabel *label23;
    QLabel *label24;
    QLabel *label25;
    QLabel *label26;
    QLabel *label27;
    QLineEdit *lineEdit21;
    QLineEdit *lineEdit22;
    QLineEdit *lineEdit23;
    QLineEdit *lineEdit24;
    QLineEdit *lineEdit25;
    QPushButton *button21;
    QPushButton *button22;
    QPushButton *button23;
    QPushButton *button24;

    //探测器参数
    QGroupBox *gridGroupBox3;
    QLabel *label31;
    QLabel *label32;
    QLabel *label33;
    QLabel *label34;
    QLabel *label35;
    QLabel *label36;
    QLabel *label37;
    QLabel *label38;
    QLabel *label39;
    QLabel *label310;
    QLabel *label311;
    QLabel *label312;
    QLabel *label313;
    QLabel *label314;
    QLineEdit *lineEdit32;
    QLineEdit *lineEdit33;
    QLineEdit *lineEdit34;
    QLineEdit *lineEdit35;
    QLineEdit *lineEdit36;
    QLineEdit *lineEdit37;
    QLineEdit *lineEdit39;
    QLineEdit *lineEdit310;
    QLineEdit *lineEdit311;
    QLineEdit *lineEdit312;
    QLineEdit *lineEdit313;
    QLineEdit *lineEdit314;
    QPushButton *button32;
    QPushButton *button33;
    QPushButton *button34;
    QPushButton *button35;
    QPushButton *button36;
    QPushButton *button37;
    QPushButton *button39;
    QPushButton *button310;
    QPushButton *button311;
    QPushButton *button312;
    QPushButton *button313;
    QPushButton *button314;

    //平台稳定性参数
    QGroupBox *gridGroupBox4;
    QLabel *label41;
    QLineEdit *lineEdit41;
    QLabel *symble41;

    //天光背景模型
    QGroupBox *gridGroupBox5;
    QCheckBox *checkBox51;
    QCheckBox *checkBox52;
    QCheckBox *checkBox53;

    //目标天体参数
    QGroupBox *gridGroupBox6;
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

    //输出类型选择
    QGroupBox *gridGroupBox7;
    QLabel *label71;
    QLabel *label72;
    QComboBox *comboBox71;  //QComboBox

    //执行按钮
    QPushButton *generateConfig;
    QPushButton *executeButton;

    QList<QString> fileNameList;

private slots:
    void slotOpenFile21();
    void slotOpenFile22();
    void slotOpenFile23();
    void slotOpenFile24();

    void slotOpenFile32();
    void slotOpenFile33();
    void slotOpenFile34();
    void slotOpenFile35();
    void slotOpenFile36();
    void slotOpenFile37();
    void slotOpenFile39();
    void slotOpenFile310();
    void slotOpenFile311();
    void slotOpenFile312();
    void slotOpenFile313();
    void slotOpenFile314();

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
