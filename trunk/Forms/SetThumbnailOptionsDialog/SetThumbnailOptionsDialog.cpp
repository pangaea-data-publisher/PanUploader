#include <QtWidgets>

#include "Application.h"
#include "SetThumbnailOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

int MainWindow::doSetThumbnailOptionsDialog( const int mode, const QString &s_FilenameIn, QString &s_Level1_static, QString &s_Level2_static, int &i_Level2_first, int &i_Level2_last,
                                             QString &s_Level3_static, int &i_Level3_first, int &i_Level3_last, QString &s_Level4_static, int &i_Level4_first, int &i_Level4_last,
                                             int &i_ThumbnailWidth, int &i_ThumbnailHeight, bool &b_createThumbnails, bool &b_uploadThumbnails, bool &b_uploadImages, bool &b_runScript )
{
    int i_DialogResult  = QDialog::Rejected;

// ***********************************************************************************************************************

    SetThumbnailOptionsDialog dialog( this );

// ***********************************************************************************************************************

    QFileInfo fi( s_FilenameIn );

    switch (mode )
    {
    case _BENTHOS_:
        dialog.PartOfPath->setText( tr( ".../Images/Benthos/" ) );
        break;
    case _OFOS_:
        dialog.PartOfPath->setText( tr( ".../Images/OFOS/" ) );
        break;
    case _CORES_:
        dialog.PartOfPath->setText( tr( ".../Images/Cores/" ) );
        break;
    case _LINESCANS_:
        dialog.PartOfPath->setText( tr( ".../Images/Linescan/" ) );
        break;
    case _JUBANY_:
        dialog.PartOfPath->setText( tr( ".../Images/Documentation/") );
    default:
        break;
    }

    dialog.firstFilename->setText( fi.fileName() );
    dialog.Level1_lineEdit->setText( s_Level1_static );
    dialog.Level2_lineEdit->setText( s_Level2_static );
    dialog.Level2_first_spinBox->setValue( i_Level2_first );
    dialog.Level2_last_spinBox->setValue( i_Level2_last );
    dialog.Level3_lineEdit->setText( s_Level3_static );
    dialog.Level3_first_spinBox->setValue( i_Level3_first );
    dialog.Level3_last_spinBox->setValue( i_Level3_last );
    dialog.Level4_lineEdit->setText( s_Level4_static );
    dialog.Level4_first_spinBox->setValue( i_Level4_first );
    dialog.Level4_last_spinBox->setValue( i_Level4_last );

    dialog.Width_spinBox->setValue( i_ThumbnailWidth );
    dialog.Height_spinBox->setValue( i_ThumbnailHeight );

    dialog.CreateThumbnails_checkBox->setChecked( b_createThumbnails );
    dialog.UploadThumbnails_checkBox->setChecked( b_uploadThumbnails );
    dialog.UploadImages_checkBox->setChecked( b_uploadImages );
    dialog.RunScript_checkBox->setChecked( b_runScript );

    dialog.OK_pushButton->setWhatsThis( "Set new parameter title orientation" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    if ( mode == _JUBANY_ )
    {
        dialog.Result_groupBox->hide();
        dialog.DirectoryStructure_groupBox->hide();
        dialog.ThumbnailSize_groupBox->hide();
    }

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    i_DialogResult = dialog.exec();

    switch ( i_DialogResult )
    {
    case QDialog::Accepted:
        s_Level1_static     = dialog.Level1_lineEdit->text();
        s_Level2_static     = dialog.Level2_lineEdit->text();
        i_Level2_first      = dialog.Level2_first_spinBox->value();
        i_Level2_last       = dialog.Level2_last_spinBox->value();
        s_Level3_static     = dialog.Level3_lineEdit->text();
        i_Level3_first      = dialog.Level3_first_spinBox->value();
        i_Level3_last       = dialog.Level3_last_spinBox->value();
        s_Level4_static     = dialog.Level4_lineEdit->text();
        i_Level4_first      = dialog.Level4_first_spinBox->value();
        i_Level4_last       = dialog.Level4_last_spinBox->value();
        i_ThumbnailWidth    = dialog.Width_spinBox->value();
        i_ThumbnailHeight   = dialog.Height_spinBox->value();
        b_createThumbnails  = dialog.CreateThumbnails_checkBox->isChecked();
        b_uploadThumbnails  = dialog.UploadThumbnails_checkBox->isChecked();
        b_uploadImages      = dialog.UploadImages_checkBox->isChecked();
        b_runScript         = dialog.RunScript_checkBox->isChecked();
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

SetThumbnailOptionsDialog::SetThumbnailOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    Level2_first_spinBox->setRange( 0, 250 );
    Level2_last_spinBox->setRange( 0, 250 );
    Level3_first_spinBox->setRange( 0, 250 );
    Level3_last_spinBox->setRange( 0, 250 );

    Width_spinBox->setRange( 50, 1500 );
    Height_spinBox->setRange( 50, 1500 );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(Clear_pushButton, SIGNAL(clicked()), this, SLOT(clearAll()));

    connect(Level1_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(changePathLineEdit(QString)));
    connect(Level2_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(changePathLineEdit(QString)));
    connect(Level3_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(changePathLineEdit(QString)));
    connect(Level4_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(changePathLineEdit(QString)));

    connect(Level2_first_spinBox, SIGNAL(valueChanged(int)), this, SLOT(changePathSpinBox(int)));
    connect(Level2_last_spinBox, SIGNAL(valueChanged(int)), this, SLOT(changePathSpinBox(int)));
    connect(Level3_first_spinBox, SIGNAL(valueChanged(int)), this, SLOT(changePathSpinBox(int)));
    connect(Level3_last_spinBox, SIGNAL(valueChanged(int)), this, SLOT(changePathSpinBox(int)));
    connect(Level4_first_spinBox, SIGNAL(valueChanged(int)), this, SLOT(changePathSpinBox(int)));
    connect(Level4_last_spinBox, SIGNAL(valueChanged(int)), this, SLOT(changePathSpinBox(int)));

    connect(Level2_first_spinBox, SIGNAL(valueChanged(int)), this, SLOT(setLastCharValue(int)));
    connect(Level2_last_spinBox, SIGNAL(valueChanged(int)), this, SLOT(setLastCharValue(int)));
    connect(Level3_first_spinBox, SIGNAL(valueChanged(int)), this, SLOT(setLastCharValue(int)));
    connect(Level3_last_spinBox, SIGNAL(valueChanged(int)), this, SLOT(setLastCharValue(int)));
    connect(Level4_first_spinBox, SIGNAL(valueChanged(int)), this, SLOT(setLastCharValue(int)));
    connect(Level4_last_spinBox, SIGNAL(valueChanged(int)), this, SLOT(setLastCharValue(int)));
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetThumbnailOptionsDialog::clearAll()
{
    Level1_lineEdit->setText( "" );
    Level2_lineEdit->setText( "" );
    Level2_first_spinBox->setValue( 0 );
    Level2_last_spinBox->setValue( 0 );
    Level3_lineEdit->setText( "" );
    Level3_first_spinBox->setValue( 0 );
    Level3_last_spinBox->setValue( 0 );
    Level4_lineEdit->setText( "" );
    Level4_first_spinBox->setValue( 0 );
    Level4_last_spinBox->setValue( 0 );

    Width_spinBox->setValue( 250 );
    Height_spinBox->setValue( 250 );

    CreateThumbnails_checkBox->setChecked( false );
    UploadThumbnails_checkBox->setChecked( false );
    UploadImages_checkBox->setChecked( false );
    RunScript_checkBox->setChecked( false );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetThumbnailOptionsDialog::changePathSpinBox(int)
{
    changePath();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetThumbnailOptionsDialog::changePathLineEdit(QString)
{
    changePath();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

QString SetThumbnailOptionsDialog::addPath( const QString &s_Path )
{
    if ( s_Path.contains( "/" ) == true )
        return( "_ERROR_" );

    if ( s_Path.contains( " " ) == true )
        return( "_ERROR_" );

    return( s_Path );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetThumbnailOptionsDialog::changePath()
{
    int      l2f                = Level2_first_spinBox->value()-1;
    int      l2l                = Level2_last_spinBox->value()-1;
    int      l3f                = Level3_first_spinBox->value()-1;
    int      l3l                = Level3_last_spinBox->value()-1;
    int      l4f                = Level4_first_spinBox->value()-1;
    int      l4l                = Level4_last_spinBox->value()-1;

    QString  s_Filename         = firstFilename->text();
    QString  s_newPath          = "";
    QString  s_EventLabel       = "";

// ****************************************************************************

    if ( PartOfPath->text().startsWith( ".../Images/Cores/" ) )
        s_newPath = tr( ".../Images/Cores/" ) + addPath( Level1_lineEdit->text() );

    if ( PartOfPath->text().startsWith( ".../Images/Benthos/" ) )
        s_newPath = tr( ".../Images/Benthos/" ) + addPath( Level1_lineEdit->text() );

    s_newPath.append( tr( "/" ) + addPath( Level2_lineEdit->text() ) );
    if ( ( l2l >= 0 ) && ( l2f >= 0 ) )
        s_newPath.append( s_Filename.mid( l2f, l2l-l2f+1 ) );

    s_newPath.append( tr( "/" ) + addPath( Level3_lineEdit->text() ) );
    if ( ( l3l >= 0 ) && ( l3f >= 0 ) )
        s_newPath.append( s_Filename.mid( l3f, l3l-l3f+1 ) );

    s_EventLabel.append( Level4_lineEdit->text() );
    if ( ( l4l >= 0 ) && ( l4f >= 0 ) )
        s_EventLabel.append( s_Filename.mid( l4f, l4l-l4f+1 ) );

    s_newPath.append( tr( "/..." ) );
    s_newPath.replace( "//", "/_ERROR_/" );

    PartOfPath->setText( s_newPath );
    EventLabel->setText( s_EventLabel );

    if ( s_newPath.contains( "_ERROR_") == true )
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

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetThumbnailOptionsDialog::setLastCharValue(int)
{
    if ( Level2_last_spinBox->value() < Level2_first_spinBox->value() )
        Level2_last_spinBox->setValue( Level2_first_spinBox->value() );
    if ( Level3_last_spinBox->value() < Level3_first_spinBox->value() )
        Level3_last_spinBox->setValue( Level3_first_spinBox->value() );
    if ( Level4_last_spinBox->value() < Level4_first_spinBox->value() )
        Level4_last_spinBox->setValue( Level4_first_spinBox->value() );

    if ( Level2_first_spinBox->value() == 0 )
        Level2_last_spinBox->setValue( 0 );
    if ( Level3_first_spinBox->value() == 0 )
        Level3_last_spinBox->setValue( 0 );
    if ( Level4_first_spinBox->value() == 0 )
        Level4_last_spinBox->setValue( 0 );
}
