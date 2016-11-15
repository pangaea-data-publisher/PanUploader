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
    int         i            = 0;
    int         err          = 0;
    int         stopProgress = 0;

    QProcess    process;

// **********************************************************************************************

    existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList );

    if (  gsl_FilenameList.count() > 0 )
    {
        if ( doSetTurnImagesOptionsDialog( gi_ImagesTurnAngle ) == QDialog::Accepted )
        {
            initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Turn images..." ) );

            while ( ( i < gsl_FilenameList.count() ) && ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
            {
                if ( ( gsl_FilenameList.at( i ).endsWith( "jpg" ) == true )
                     || ( gsl_FilenameList.at( i ).endsWith( "png" ) == true )
                     || ( gsl_FilenameList.at( i ).endsWith( "gif" ) == true )
                     || ( gsl_FilenameList.at( i ).endsWith( "tif" ) == true ) )
                {
                    switch ( gi_ImagesTurnAngle )
                    {
                    case -180:
                    case -90:
                        process.start( QString( "sips -r %1 \"%2\"" ).arg( gi_ImagesTurnAngle + 360 ).arg( gsl_FilenameList.at( i ) ) );
                        break;

                    case 90:
                    case 180:
                        process.start( QString( "sips -r %1 \"%2\"" ).arg( gi_ImagesTurnAngle ).arg( gsl_FilenameList.at( i ) ) );
                        break;

                    default:
                        break;
                    }

                    process.waitForFinished( -1 );
                }

                stopProgress = incFileProgress( gsl_FilenameList.count(), ++i );
            }

            resetFileProgress( gsl_FilenameList.count() );
        }
        else
            err = _CHOOSEABORTED_;
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

// **********************************************************************************************

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Turning images was canceled" ), false, false );

    onError( err );
}

