#include <QtWidgets>

#include "Application.h"
#include "SetTurnImagesOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

int MainWindow::doSetTurnImagesOptionsDialog( int &i_ImagesTurnAngle )
{
    int i_DialogResult  = QDialog::Rejected;

// ***********************************************************************************************************************

    SetTurnImagesOptionsDialog dialog( this );

// ***********************************************************************************************************************

    dialog.ImagesTurnAngle_spinBox->setValue( i_ImagesTurnAngle );

    dialog.OK_pushButton->setWhatsThis( "Set new parameter title orientation" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    i_DialogResult = dialog.exec();

    switch ( i_DialogResult )
    {
    case QDialog::Accepted:
        i_ImagesTurnAngle = dialog.ImagesTurnAngle_spinBox->value();
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    posDialog = dialog.pos();

    return( i_DialogResult );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

SetTurnImagesOptionsDialog::SetTurnImagesOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    ImagesTurnAngle_spinBox->setRange( -180, 180 );

    connect(ImagesTurnAngle_spinBox, SIGNAL(valueChanged(int)), this, SLOT(enableOKButton(int)));

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));

    enableOKButton( 0 );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetTurnImagesOptionsDialog::enableOKButton( int i_ImagesTurnAngle )
{
    if ( i_ImagesTurnAngle == 0 )
    {
        OK_pushButton->setDefault( false );
        OK_pushButton->setDisabled( true );
        Cancel_pushButton->setDefault( true );
    }
    else
    {
        OK_pushButton->setDefault( true );
        OK_pushButton->setDisabled( false );
        Cancel_pushButton->setDefault( false );
    }
}
