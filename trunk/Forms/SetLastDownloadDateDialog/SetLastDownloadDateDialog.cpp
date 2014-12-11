#include <QtWidgets>

#include "Application.h"
#include "SetLastDownloadDateDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetLastDownloadDateDialog()
{
    SetLastDownloadDateDialog dialog( this );

    dialog.LastDownloadDate_dateEdit->setDate( QDate::fromString( gs_lastDate, Qt::ISODate ) );

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        gs_lastDate = dialog.LastDownloadDate_dateEdit->date().toString( Qt::ISODate );
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    posDialog = dialog.pos();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

SetLastDownloadDateDialog::SetLastDownloadDateDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
}
