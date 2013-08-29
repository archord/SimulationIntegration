#ifndef DETECTORDIALOG_H
#define DETECTORDIALOG_H

#include <QDialog>

#include "ui_detectorDialog.h"

class DetectorDialog : public QDialog, public Ui_DetectorDialogUI
{
    Q_OBJECT
public:
    explicit DetectorDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // DETECTORDIALOG_H
