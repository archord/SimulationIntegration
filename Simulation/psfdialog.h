#ifndef PSFDIALOG_H
#define PSFDIALOG_H

#include <QDialog>

#include "ui_psfDialog.h"

class PSFDialog : public QDialog, public Ui_PSFDialogUI
{
    Q_OBJECT
public:
    explicit PSFDialog(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // PSFDIALOG_H
