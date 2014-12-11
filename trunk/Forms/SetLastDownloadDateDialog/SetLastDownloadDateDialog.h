#ifndef SETLASTDOWNLOADDATEDIALOG_H
#define SETLASTDOWNLOADDATEDIALOG_H

#include <QDialog>

#include "ui_setlastdownloaddatedialog.h"

class SetLastDownloadDateDialog : public QDialog, public Ui::SetLastDownloadDateDialog
{
    Q_OBJECT

public:
    SetLastDownloadDateDialog( QWidget *parent = 0 );
};

#endif
