#ifndef SETTURNIMAGESOPTIONSDIALOG_H
#define SETTURNIMAGESOPTIONSDIALOG_H

#include <QDialog>

#include "ui_setturnimagesoptionsdialog.h"

class SetTurnImagesOptionsDialog : public QDialog, public Ui::SetTurnImagesOptionsDialog
{
    Q_OBJECT

public:
    SetTurnImagesOptionsDialog( QWidget *parent = 0 );

private slots:
    void enableOKButton(int);
};

#endif
