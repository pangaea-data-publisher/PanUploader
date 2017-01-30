/* createJubanyThumbnails.cpp        */
/* 2012-12-12                        */
/* first run on new iMac: 2013-03-20 */
/* Dr. Rainer Sieger                 */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2017-01-30

int MainWindow::createJubanyThumbnails( const QStringList &sl_FilenameList, const QString &s_WorkingDirectory, const QString &s_User_hssrv2, const QString &s_Password_hssrv2, const QString &s_User_pangaea, const QString &s_Password_pangaea, const QString &s_CommandFile )
{
    bool        b_testmode  = false;

    QString     s_UrlUpload = "/pangaea/store/Images/Documentation";

// **********************************************************************************************

    QFile fcmd( s_CommandFile );
    if ( fcmd.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tcmd( &fcmd );

// **********************************************************************************************

#if defined(Q_OS_MAC)
    tcmd << "#!/bin/bash" << endl;
    tcmd << "echo downloading latest pictures of Jubany station" << endl << endl;

    tcmd << "JubanyLocalPath=\"" + s_WorkingDirectory + "\"" << endl << endl;

    tcmd << "mkdir ${JubanyLocalPath}/images" << endl;
    tcmd << "mkdir ${JubanyLocalPath}/images/thumbs" << endl << endl;

    tcmd << endl << "echo creating thumbnails" << endl;
    tcmd << "cd ${JubanyLocalPath}/images" << endl;
    tcmd << "sips -Z 250 *.jpg --out thumbs" << endl << endl;

    tcmd << "cd thumbs" << endl;
    tcmd << "for file in *.jpg" << endl;
    tcmd << "do" << endl;
    tcmd << "  mv \"$file\" \"${file/Jubany/TN_Jubany}\"" << endl;
    tcmd << "done" << endl << endl;

    tcmd << "cd ../.." << endl << endl;

    tcmd << "echo ' #!/usr/bin/expect" << endl;
    tcmd << "spawn sftp " << s_User_pangaea << "@pangaea-mw1.awi.de" << endl;
    tcmd << "expect \"password:\"" << endl;
    tcmd << "send \"" << s_Password_pangaea << "\\n\"" << endl;
    tcmd << "expect \"sftp> \"" << endl;

    for ( int i=0; i<sl_FilenameList.count(); i++ )
    {
        if ( sl_FilenameList.at( i ).section( "/", -1, -1 ).contains( "Jubany_Station1" ) == true )
            s_UrlUpload.append( "/Jubany1/" );
        else
            s_UrlUpload.append( "/Jubany/" );

        tcmd << "send \"cd " << s_UrlUpload << sl_FilenameList.at( i ).section( "/", 6, 6 ) << "\\n\"" << endl;

        tcmd << "expect \"sftp> \"" << endl;
        tcmd << "send \"lcd " << s_WorkingDirectory << "/images/thumbs\\n\"" << endl;
        tcmd << "expect \"sftp> \"" << endl;
        tcmd << "send \"mput *.jpg\\n\"" << endl;
        tcmd << "expect \"sftp> \"" << endl;
    }

    tcmd << "send \"quit\\n\"" << endl;
    tcmd << "expect eof ' | /usr/bin/expect" << endl << endl;

    if ( b_testmode == false )
    {
        tcmd << "rm -r images" << endl;
        tcmd << "rm runJubany.sh" << endl;
    }
#endif

#if defined(Q_OS_WIN)
    ;
#endif

#if defined(Q_OS_LINUX)
    ;
#endif

// **********************************************************************************************

    fcmd.close();

#if defined(Q_OS_MAC)
/*
    QProcess process;
    QString s_arg = "chmod u+x \"" + fcmd.fileName() + "\"";
    process.startDetached( s_arg );

    wait( 100 );

    s_arg = "\"" + fcmd.fileName() + "\"";

    if ( process.startDetached( s_arg ) == false )
    {
        QString s_Message = "Cannot start the script\n\n    " + QDir::toNativeSeparators( fcmd.fileName() ) + "\n\n Please start the script manually from your shell.";
        QMessageBox::warning( this, getApplicationName( true ), s_Message );
    }
    else
    {
        while ( fcmd.exists() == true )
            wait( 1000 );
    }
*/
#endif

#if defined(Q_OS_WIN)
    ;
#endif

#if defined(Q_OS_LINUX)
    ;
#endif

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doCreateJubanyThumbnails()
{
    int         err               = _NOERROR_;

    int         stopProgress      = 0;

    QString     s_CommandFile     = "";

// **********************************************************************************************

    if ( gsl_FilenameList.count() > 0 )
        err = createJubanyThumbnails( gsl_FilenameList, gs_WorkingDirectory, gs_User_hssrv2, gs_Password_hssrv2, gs_User_pangaea, gs_Password_pangaea, s_CommandFile );
    else
        err = _CHOOSEABORTED_;

// **********************************************************************************************

    clearFilenameList( gi_ActionNumber, gsl_FilenameList );

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Process was canceled" ) );

    if ( err == _NOERROR_ )
        err = _DONE_;

// **********************************************************************************************

    onError( err );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int MainWindow::startProgram( const QString &s_Program, const QString &s_Filename )
{
    QProcess    process;
    QStringList sl_args;
    QString     s_ProgramFilePath = "";

// ***********************************************************************************************

    QFileInfo fi( s_Program );

    if ( fi.exists() == false )
    {
        QString s_Message = "Cannot find the program\n\n    " + QDir::toNativeSeparators( s_Program ) + "\n\n Please start the program manually from your shell.";
        QMessageBox::warning( this, getApplicationName(), s_Message );

        return( _ERROR_ );
    }
    else
    {
        #if defined(Q_OS_LINUX)
            s_ProgramFilePath = s_Program;
        #endif

        #if defined(Q_OS_WIN)
            s_ProgramFilePath = s_Program;
        #endif

        #if defined(Q_OS_MAC)
            s_ProgramFilePath = fi.absoluteFilePath();
            s_ProgramFilePath.replace( ".app", "" );
            s_ProgramFilePath.append( ".app/Contents/MacOS/" + fi.baseName() );
        #endif

        sl_args.append( QDir::toNativeSeparators( s_Filename ) );

        if ( process.startDetached( QDir::toNativeSeparators( s_ProgramFilePath ), sl_args ) == false )
        {
            QString s_Message = "Cannot start the program\n\n    " + QDir::toNativeSeparators( s_Program ) + "\n\n Please start the program manually from your shell.";
            QMessageBox::warning( this, getApplicationName(), s_Message );

            return( _ERROR_ );
        }
    }

    return( _NOERROR_ );
}
