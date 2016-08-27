/* createJubanyThumbnails.cpp        */
/* 2012-12-12                        */
/* first run on new iMac: 2013-03-20 */
/* Dr. Rainer Sieger                 */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int MainWindow::createJubanyThumbnails( const QString &s_FilenameIn, const QString &s_WorkingDirectory, const QString &s_EasyThumbnail, const QString &s_wget, const QString &s_psftp, const QString &s_UserUpload, const QString &s_PasswordUpload, const QString &s_CommandFile, const QString &s_ScriptFile, const QString &s_LogFile )
{
    bool        b_testmode  = false;

    int         i           = 0;
    int         n           = 0;

    QString     s_UrlUpload = "/pangaea/htdocs/pangaea-family/store/Images/Documentation";

    QStringList sl_Input;

// **********************************************************************************************
// read data file

    if ( ( n = readFile( s_FilenameIn, sl_Input ) ) < 1 ) // System encoding
        return( _NODATAFOUND_ );

    while ( ( i < n ) && ( sl_Input.at( i ).startsWith( "/hs/" ) == false ) )
        ++i;

    if ( i >= n )
        return( _NODATAFOUND_ );

    QFile fscript( s_ScriptFile );
    if ( fscript.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QFile fcmd( s_CommandFile );
    if ( fcmd.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
    {
        fscript.close();
        return( -20 );
    }

    QTextStream tscript( &fscript );
    QTextStream tcmd( &fcmd );

// **********************************************************************************************

    sl_Input.sort();

// **********************************************************************************************

#if defined(Q_OS_MAC)
    QString s_Dummy = s_EasyThumbnail; s_Dummy = s_wget; s_Dummy = s_psftp; s_Dummy = s_LogFile;

    tcmd << "#!/bin/bash" << endl;
    tcmd << "echo downloading latest pictures of Jubany station" << endl << endl;

    tcmd << "JubanyLocalPath=\"" + s_WorkingDirectory + "\"" << endl << endl;

    tcmd << "mkdir ${JubanyLocalPath}/images" << endl;
    tcmd << "mkdir ${JubanyLocalPath}/images/thumbs" << endl << endl;

    tscript << "not used in OS X script" << endl;

    while ( i<n )
    {
        QString s_DownloadFile  = sl_Input.at( i ).section( "/", -1, -1 );
        QString s_Year          = sl_Input.at( i ).section( "/", 6, 6 );
        QString s_UrlDownload   = "http://hs.pangaea.de/Images/Documentation";

        if ( s_DownloadFile.contains( "Jubany_Station1" ) == true )
            s_UrlDownload.append( "/Jubany1/" );
        else
            s_UrlDownload.append( "/Jubany/" );

        tcmd << "curl " << "-o \"" << QDir::toNativeSeparators( "${JubanyLocalPath}/images/" + s_DownloadFile ) << "\" " << s_UrlDownload << s_Year << "/" << s_DownloadFile << endl;
        ++i;
    }

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
    tcmd << "spawn sftp " << s_UserUpload << "@pangaea-mw1.awi.de" << endl;
    tcmd << "expect \"password:\"" << endl;
    tcmd << "send \"" << s_PasswordUpload << "\\n\"" << endl;
    tcmd << "expect \"sftp> \"" << endl;

    if ( sl_Input.at( 0 ).section( "/", -1, -1 ).contains( "Jubany_Station1" ) == true ) // !!! find UrlUpload for first year only !!!
        s_UrlUpload.append( "/Jubany1/" );
    else
        s_UrlUpload.append( "/Jubany/" );

    tcmd << "send \"cd " << s_UrlUpload << sl_Input.at( 0 ).section( "/", 6, 6 ) << "\\n\"" << endl; // !!! find UrlUpload for first year only !!!

    tcmd << "expect \"sftp> \"" << endl;
    tcmd << "send \"lcd " << s_WorkingDirectory << "/images/thumbs\\n\"" << endl;
    tcmd << "expect \"sftp> \"" << endl;
    tcmd << "send \"mput *.jpg\\n\"" << endl;
    tcmd << "expect \"sftp> \"" << endl;
    tcmd << "send \"quit\\n\"" << endl;
    tcmd << "expect eof ' | /usr/bin/expect" << endl << endl;

    tcmd << "rm " << s_ScriptFile << endl;

    if ( b_testmode == false )
    {
        tcmd << "rm " << s_FilenameIn << endl;
        tcmd << "rm -r images" << endl;
        tcmd << "rm runJubany.sh" << endl;
    }
#endif

#if defined(Q_OS_WIN)
    tcmd << "@echo off" << endl;
    tcmd << "@echo downloading latest pictures of Jubany station" << endl << endl;

    tcmd << "md \"" << QDir::toNativeSeparators( s_WorkingDirectory + "/images" ) << "\"" << endl;
    tcmd << "md \"" << QDir::toNativeSeparators( s_WorkingDirectory + "/images/thumbs" ) << "\"" << endl << endl;

    while ( i<n )
    {
        QString s_UrlDownload   = "http://hs.pangaea.de/Images/Documentation/Jubany/";
        QString s_DownloadFile  = sl_Input.at( i ).section( "/", -1, -1 );
        QString s_ThumbnailFile = tr( "TN_%1" ).arg( sl_Input.at( i ).section( "/", -1, -1 ) );
        QString s_Year          = sl_Input.at( i ).section( "/", 6, 6 );

        tcmd << "\"" << QDir::toNativeSeparators( s_wget ) << "\" " << s_UrlDownload << s_Year << "/" << s_DownloadFile << " -O \"" << QDir::toNativeSeparators( s_WorkingDirectory + "/images/" + s_DownloadFile ) << "\"" << endl;
        tscript << "put \"" << QDir::toNativeSeparators( s_WorkingDirectory + "/images/thumbs/" + s_ThumbnailFile ) << "\" " << s_UrlUpload << s_Year << "/" << s_ThumbnailFile << endl;

        ++i;
    }

    tscript << "quit" << endl;

    tcmd << endl << "@echo creating thumbnails" << endl;
    tcmd << "\"" << s_EasyThumbnail << "\" \"" << QDir::toNativeSeparators( s_WorkingDirectory + "/images" ) << "\\*.*\" /D=\"" << QDir::toNativeSeparators( s_WorkingDirectory + "/images/thumbs" ) << "\" /P=\"TN_\" /W=250 /H=250 /ShrinkToFit /F=Smart /Q=75 /Log=\"" << QDir::toNativeSeparators( s_LogFile ) << "\"" << endl;

    tcmd << endl << "@echo uploading thumbnails" << endl;
    tcmd << "\"" << QDir::toNativeSeparators( s_psftp ) << "\" -b \"" << QDir::toNativeSeparators( s_ScriptFile ) << "\" -be -pw " << s_PasswordUpload << " " << s_UserUpload << "@" << "www.pangaea.de" << " > \"" << QDir::toNativeSeparators( s_LogFile ) << "\"" << endl;

    tcmd << endl << "cd " << "\"" << QDir::toNativeSeparators( s_WorkingDirectory ) << "\"";
    tcmd << endl << "rd /S /Q images";

    if ( b_testmode == false )
    {
        tcmd << endl << "del /Q *.txt";
        tcmd << endl << "del /Q *.log";
        tcmd << endl << "del /Q runJubany.cmd" << endl;
    }
#endif

#if defined(Q_OS_LINUX)
    ;
#endif

// **********************************************************************************************

    fscript.close();
    fcmd.close();

#if defined(Q_OS_WIN)
    startProgram( s_CommandFile, "" );
#endif

#if defined(Q_OS_MAC)
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
#endif

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doCreateJubanyThumbnails()
{
    int         err               = _NOERROR_;

    int         i_File            = 0;
    int         stopProgress      = 0;

    QString     s_ScriptFile      = "";
    QString     s_LogFile         = "";
    QString     s_CommandFile     = "";

// **********************************************************************************************

    if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
    {
        initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Run script..." ) );

        while ( ( i_File < gsl_FilenameList.count() ) && ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
        {
            setStatusBarFileInProgress( gsl_FilenameList.at( i_File ) );

            QFileInfo fi( gsl_FilenameList.at( i_File ) );

#if defined(Q_OS_MAC)
            s_ScriptFile  = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "Jubany.txt";
            s_LogFile     = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "Jubany.log";
            s_CommandFile = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "runJubany.sh";
#endif

#if defined(Q_OS_WIN)
            s_ScriptFile  = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "Jubany.txt";
            s_LogFile     = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "Jubany.log";
            s_CommandFile = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "runJubany.cmd";
#endif

#if defined(Q_OS_LINUX)
            s_ScriptFile  = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "Jubany.txt";
            s_LogFile     = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "Jubany.log";
            s_CommandFile = QDir::toNativeSeparators( fi.absolutePath() ) + QDir::toNativeSeparators( "/" ) + "runJubany.sh";
#endif

            err = createJubanyThumbnails( gsl_FilenameList.at( i_File ), gs_WorkingDirectory, gs_EasyThumbnails, gs_wget, gs_psftp, gs_User_pangaea, gs_Password_pangaea, s_CommandFile, s_ScriptFile, s_LogFile );

            stopProgress = incFileProgress( gsl_FilenameList.count(), i_File++ );
        }

        resetFileProgress( gsl_FilenameList.count() );
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

// **********************************************************************************************

    gs_lastDate = QDate::currentDate().toString( Qt::ISODate );

    clearFilenameList( gi_ActionNumber, gsl_FilenameList );

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Process was canceled" ) );

    if ( err == _NODATAFOUND_ )
    {
        QStringList sl_List;
        sl_List.append( tr( "No more images available. Try again after " ) + QDate::currentDate().addDays( 1 ).toString( Qt::ISODate ) + tr( " 10:30 h." ) );
        showList( sl_List );
    }

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
