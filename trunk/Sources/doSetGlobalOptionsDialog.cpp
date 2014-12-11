#include <QtGui>

#include "Application.h"
#include "Globals.h"
#include "../Forms/SetGlobalOptionsDialog/SetGlobalOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetGlobalOptionsDialog()
{
    int i_DialogResult = QDialog::Rejected;

    SetGlobalOptionsDialog *dialog	= new SetGlobalOptionsDialog();

// ***********************************************************************************************************************

    dialog->OKPushButton->setWhatsThis( "Set new parameter title orientation" );
    dialog->CancelPushButton->setWhatsThis( "Cancel dialog" );

// ***********************************************************************************************************************
// Options

    dialog->DownloadDirectory_lineEdit->setText( gs_DownloadDirectory );
    dialog->ThumbnailDirectory_lineEdit->setText( gs_ThumbnailDirectory );
    dialog->EasyThumbnailsProgram_lineEdit->setText( gs_EasyThumbnails );
    dialog->wgetProgram_lineEdit->setText( gs_wget );
    dialog->psftpProgram_lineEdit->setText( gs_psftp );
    dialog->ServerUpload_lineEdit->setText( gs_ServerUpload );
    dialog->UserUpload_lineEdit->setText( gs_UserUpload );
    dialog->PasswordUpload_lineEdit->setText( gs_PasswordUpload );

    dialog->adjustSize();
    dialog->move( posDialog );

// ******************************************************************************************************

    i_DialogResult = dialog->exec();

    posDialog = dialog->pos();

    switch ( i_DialogResult )
    {
    case QDialog::Accepted:
        gs_DownloadDirectory    = dialog->DownloadDirectory_lineEdit->text();
        gs_ThumbnailDirectory   = dialog->ThumbnailDirectory_lineEdit->text();
        gs_EasyThumbnails       = dialog->EasyThumbnailsProgram_lineEdit->text();
        gs_wget                 = dialog->wgetProgram_lineEdit->text();
        gs_psftp                = dialog->psftpProgram_lineEdit->text();
        gs_ServerUpload         = dialog->ServerUpload_lineEdit->text();
        gs_UserUpload           = dialog->UserUpload_lineEdit->text();
        gs_PasswordUpload       = dialog->PasswordUpload_lineEdit->text();
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    delete dialog;
}
