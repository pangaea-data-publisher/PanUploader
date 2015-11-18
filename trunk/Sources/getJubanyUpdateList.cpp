/* getJubanyUpdateList.cpp    */
/* 2012-12-30                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************

QString MainWindow::getJubanyUpdateList( const QString &s_lastDate, const QString &s_WorkingDirectory, const QString &s_User, const QString &s_Password )
{
    int     i               = 0;

    QString s_Host          = "hssrv2.awi.de";
    QString s_UpdateListDir = "/hs/usero/tmp/jupdates";

    QDate   lastDate        = QDate( QDate::currentDate() );
    QDate   currentDate     = QDate( QDate::currentDate() );

    QVector<QDate> Dates;

// **********************************************************************************************

    if ( s_lastDate.isEmpty() == false )
        lastDate.setDate( s_lastDate.section( "-", 0, 0 ).toInt(), s_lastDate.section( "-", 1, 1 ).toInt(), s_lastDate.section( "-", 2, 2 ).toInt() );

    if ( lastDate >= currentDate )
        return( tr( "Last date is equal to current date" ) );

    Dates.append( lastDate.addDays( 1 ) );

    while( Dates.at( i ) < currentDate )
        Dates.append( Dates.at( i++ ).addDays( 1 ) );

// **********************************************************************************************

    if ( ( s_User.isEmpty() == true ) || ( s_Password.isEmpty() == true ) )
        return( tr( "Account settings not vaild" ) );

// **********************************************************************************************

    setWaitCursor();

// **********************************************************************************************

    QString s_FilenameOut = QDir::toNativeSeparators( s_WorkingDirectory + "/newJubanyPictures_" + Dates.at( i ).toString( Qt::ISODate ) + ".txt" );

    QFile outfile( s_FilenameOut );

    if ( outfile.exists() == true )
        outfile.remove();

    if ( outfile.open( QIODevice::WriteOnly | QIODevice::Text ) == true )
    {
        QTextStream tout( &outfile );

/*
        ftp->connectToHost( s_Host );
        ftp->login( s_User, s_Password );
        ftp->cd( s_UpdateListDir );
*/
        for( i=0; i<Dates.count(); i++ )
        {
            QString s_Filename = Dates.at( i ).toString( Qt::ISODate );
            s_Filename.replace( "-", "" );

            tout << s_Filename << endl;

//          wait( 2000 );
        }

        outfile.close();
    }

// **********************************************************************************************

    setNormalCursor();

// **********************************************************************************************

    QFileInfo fi( s_FilenameOut );

    if ( fi.size() < 10 )
        return( tr( "No more images available. Try again after " ) + currentDate.addDays( 1 ).toString( Qt::ISODate ) + tr( " 10:30 h." ) );
    else
        QMessageBox::information( this, getApplicationName(), tr( "Download of dates has been finished." ) );

    return( s_FilenameOut );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doGetDates()
{
    clearFilenameList( gi_ActionNumber, gsl_FilenameList );

    gsl_FilenameList.append( getJubanyUpdateList( gs_lastDate, gs_WorkingDirectory, gs_User_hssrv2, gs_Password_hssrv2 ) );

    showList( gsl_FilenameList );
}
