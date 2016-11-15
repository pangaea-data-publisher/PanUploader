/* turnImages.cpp             */
/* 2016-11-15                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2016-11-15

void MainWindow::doTurnImages()
{
    int         err       = 0;

    QString     s_arg     = "";

    QProcess    process;

// **********************************************************************************************

    existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList );

    if (  gsl_FilenameList.count() > 0 )
    {
        if ( doSetTurnImagesOptionsDialog( gi_ImagesTurnAngle ) == QDialog::Accepted )
        {
            for ( int i=0; i<gsl_FilenameList.count(); i++ )
            {
                if ( ( gsl_FilenameList.at( i ).endsWith( "jpg" ) == true ) || ( gsl_FilenameList.at( i ).endsWith( "png" ) == true ) || ( gsl_FilenameList.at( i ).endsWith( "gif" ) == true ) || ( gsl_FilenameList.at( i ).endsWith( "tif" ) == true ) )
                {
                    s_arg = QString( "sips -r %1 \"%2\"" ).arg( gi_ImagesTurnAngle ).arg( gsl_FilenameList.at( i ) );

                    process.start( s_arg );
                    process.waitForFinished( -1 );
                }
            }
        }
        else
            err = _CHOOSEABORTED_;
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

    if ( err == _NOERROR_ )
        err = _DONE_;

// **********************************************************************************************

    onError( err );
}

