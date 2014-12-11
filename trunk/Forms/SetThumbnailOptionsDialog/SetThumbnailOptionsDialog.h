#ifndef SETTHUMBNAILOPTIONSDIALOG_H
#define SETTHUMBNAILOPTIONSDIALOG_H

#include <QDialog>

#include "ui_setthumbnailoptionsdialog.h"

class SetThumbnailOptionsDialog : public QDialog, public Ui::SetThumbnailOptionsDialog
{
    Q_OBJECT

public:
    SetThumbnailOptionsDialog( QWidget *parent = 0 );
    void changePath();
    QString addPath( const QString &Path );

private slots:
    void setLastCharValue(int);
    void changePathSpinBox(int);
    void changePathLineEdit(QString);
};

#endif
