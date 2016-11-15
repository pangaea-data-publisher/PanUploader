/* uploadImages.cpp           */
/* 2012-12-30                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-12-30

int MainWindow::buildScript( const int mode, const QString &s_User_hssrv2, const QString &s_Password_hssrv2, const QString &s_User_pangaea, const QString &s_Password_pangaea,
                             QStringList &sl_FilenameList, const QString &s_EasyThumbnails, const QString &s_wget, const QString &s_psftp,
                             const QString &s_Level1_static, const QString &s_Level2_static, const int i_Level2_first, const int i_Level2_last,
                             const QString &s_Level3_static, const int i_Level3_first, const int i_Level3_last,
                             const QString &s_Level4_static, const int i_Level4_first, const int i_Level4_last,
                             const int i_ImagesTurnAngle, const int i_ThumbnailWidth, const int i_ThumbnailHeight,
                             const bool b_createThumbnails, const bool b_uploadThumbnails, const bool b_uploadImages, const bool b_turnImages,
                             const bool b_runScript )
{
    QString   s_Dummy = s_EasyThumbnails; s_Dummy = s_wget; s_Dummy = s_psftp;

    QFileInfo fi( sl_FilenameList.at( 0 ) );

    QString   s_RootDir        = fi.absolutePath().section( "/", 0, -2 ) + "/";
    QString   s_oldPath        = s_RootDir;
    QString   s_CommandFile    = s_RootDir + "runScript.sh";
    QString   s_ImportFile     = s_RootDir + "import_datasets.txt";

    QString   s_EventLabel_old = "";

// **********************************************************************************************

    if ( ( b_createThumbnails == false ) && ( b_uploadImages == false ) && ( b_uploadThumbnails == false ) && ( b_turnImages == false ) )
        return( _APPBREAK_ );

    if ( ( s_User_hssrv2.isEmpty() == true ) || ( s_Password_hssrv2.isEmpty() == true ) )
        return( -30 );

    if ( ( s_User_pangaea.isEmpty() == true ) || ( s_Password_pangaea.isEmpty() == true ) )
        return( -40 );

    if ( ( b_createThumbnails == true ) && ( b_uploadThumbnails == true ) )
    {
        if ( createDummyFiles( s_RootDir ) != _NOERROR_ )
            return( -20 );
    }

    QFile fcmd( s_CommandFile );
    if ( fcmd.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QFile fimp( s_ImportFile );
    if ( fimp.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
    {
        fcmd.close();
        return( -20 );
    }

// **********************************************************************************************

    QTextStream tcmd( &fcmd );
    QTextStream timp( &fimp );

// **********************************************************************************************

    QStringList sl_UploadDirectoryList = createUploadDirectoryList( sl_FilenameList, s_Level1_static, s_Level2_static, i_Level2_first, i_Level2_last, s_Level3_static, i_Level3_first, i_Level3_last );
    QStringList sl_EventLabelList      = createEventLabelList( sl_FilenameList, s_Level1_static, s_Level2_static, i_Level2_first, i_Level2_last, s_Level3_static, i_Level3_first, i_Level3_last, s_Level4_static, i_Level4_first, i_Level4_last );

// **********************************************************************************************

    tcmd << "#!/bin/bash" << endl;

    if ( b_turnImages == true )
    {
        for ( int i=0; i<sl_FilenameList.count(); i++ )
        {
            if ( ( sl_FilenameList.at( i ).endsWith( "jpg" ) == true ) || ( sl_FilenameList.at( i ).endsWith( "png" ) == true ) || ( sl_FilenameList.at( i ).endsWith( "gif" ) == true ) || ( sl_FilenameList.at( i ).endsWith( "tif" ) == true ) )
                tcmd << QString( "sips -r %1 \"%2\"" ).arg( i_ImagesTurnAngle ).arg( sl_FilenameList.at( i ) ) << endl;
        }
    }

    if ( b_createThumbnails == true )
    {
        s_oldPath = sl_FilenameList.at( 0 );

        for ( int i=0; i<sl_FilenameList.count(); i++ )
        {
            fi.setFile( sl_FilenameList.at( i ) );

            if ( sl_FilenameList.at( i ).contains( "_descr.", Qt::CaseInsensitive ) == false )
            {
                if ( ( sl_FilenameList.at( i ).endsWith( "jpg" ) == true ) ||
                     ( sl_FilenameList.at( i ).endsWith( "png" ) == true ) ||
                     ( sl_FilenameList.at( i ).endsWith( "gif" ) == true ) ||
                     ( sl_FilenameList.at( i ).endsWith( "tif" ) == true ) )
                {
                    if ( s_oldPath != fi.absolutePath() )
                    {
                        tcmd << "cd \"" << fi.absolutePath() << "\"" << endl;
                        tcmd << "mkdir thumbs" << endl;

                        s_oldPath = fi.absolutePath();
                    }
                }

                if ( ( sl_FilenameList.at( i ).endsWith( "jpg" ) == true ) || ( sl_FilenameList.at( i ).endsWith( "png" ) == true ) || ( sl_FilenameList.at( i ).endsWith( "gif" ) == true ) )
                    tcmd << QString( "sips -Z %1 \"%2\" --out thumbs" ).arg( qMax( i_ThumbnailWidth, i_ThumbnailHeight ) ).arg( sl_FilenameList.at( i ) ) << endl;

                if ( sl_FilenameList.at( i ).endsWith( "tif" ) == true )
                {
                    tcmd << QString( "sips -s format jpeg \"%1\" --out \"%2.jpg\"" ).arg( sl_FilenameList.at( i ) ).arg( fi.completeBaseName() ) << endl;
                    tcmd << QString( "sips -Z %1 \"%2.jpg\" --out thumbs" ).arg( qMax( i_ThumbnailWidth, i_ThumbnailHeight ) ).arg( fi.completeBaseName() ) << endl;
                    tcmd << QString( "rm \"%1.jpg\"" ).arg( fi.completeBaseName() ) << endl;;
                }
            }
        }
    }

    if ( b_uploadImages == true )
    {
        QStringList sl_RemoteFilenameList = createRemoteFilenameList( _IMAGES_, sl_FilenameList, s_Level1_static, s_Level2_static, i_Level2_first, i_Level2_last, s_Level3_static, i_Level3_first, i_Level3_last );

        tcmd << "ftp -inv hssrv2.awi.de<<ENDFTP" << endl;
        tcmd << "user " << s_User_hssrv2 << " " << s_Password_hssrv2 << endl;
        tcmd << "cd " << UploadDirectory( _HSSRV2_, mode ) << endl;

        for ( int i=0; i<sl_UploadDirectoryList.count(); i++ )
            tcmd << "mkdir " << sl_UploadDirectoryList.at( i ) << endl;

        for ( int i=0; i<sl_FilenameList.count(); i++ )
            tcmd << "put \"" << sl_FilenameList.at( i ) << "\" " << sl_RemoteFilenameList.at( i ) << endl;

        tcmd << "bye" << endl;
        tcmd << "ENDFTP" << endl;
    }

    if ( b_uploadThumbnails == true )
    {
        QStringList sl_RemoteFilenameList = createRemoteFilenameList( _THUMBNAILS_, sl_FilenameList, s_Level1_static, s_Level2_static, i_Level2_first, i_Level2_last, s_Level3_static, i_Level3_first, i_Level3_last );

        tcmd << "echo ' #!/usr/bin/expect" << endl;
        tcmd << "spawn sftp " << s_User_pangaea << "@pangaea-mw1.awi.de" << endl;
        tcmd << "expect \"password:\"" << endl;
        tcmd << "send \"" << s_Password_pangaea << "\\n\"" << endl;
        tcmd << "expect \"sftp> \"" << endl;
        tcmd << "send \"cd " << UploadDirectory( _MW1_, mode ) << "\\n\"" << endl;

        for ( int i=0; i<sl_UploadDirectoryList.count(); i++ )
        {
            tcmd << "expect \"sftp> \"" << endl;
            tcmd << "send \"mkdir " << sl_UploadDirectoryList.at( i ) << "\\n\"" << endl;
        }

        for ( int i=0; i<sl_FilenameList.count(); i++ )
        {
            tcmd << "expect \"sftp> \"" << endl;
            tcmd << "send \"put \\\"" << sl_FilenameList.at( i ).section( "/", 0, -2 );
            tcmd << setLocalFile( sl_FilenameList.at( i ).section( "/", -1, -1 ) ) << "\\\" ";
            tcmd << sl_RemoteFilenameList.at( i ) << "\\n\"" << endl;
        }

        tcmd << "expect \"sftp> \"" << endl;
        tcmd << "send \"quit\\n\"" << endl;
        tcmd << "expect eof ' | /usr/bin/expect" << endl;
    }

    if ( ( b_createThumbnails == true ) && ( b_uploadThumbnails == true ) )
    {
        tcmd << "rm " << s_RootDir << _COREDESCRIPTION_FILENAME_ << endl;
        tcmd << "rm " << s_RootDir << _CORELEGEND_FILENAME_ << endl;
        tcmd << "rm " << s_RootDir << _CORELOGGERPROTOKOLL_FILENAME_ << endl;
        tcmd << "rm " << s_RootDir << _CORESECTIONTABLE_FILENAME_ << endl;

        tcmd << "rm " << s_RootDir << _BENTHOSMAP_FILENAME_ << endl;
        tcmd << "rm " << s_RootDir << _BENTHOSTRACK_FILENAME_ << endl;
        tcmd << "rm " << s_RootDir << _BENTHOSBATH_FILENAME_ << endl;
        tcmd << "rm " << s_RootDir << _INFO_FILENAME_ << endl;

        s_oldPath = s_RootDir;

        for ( int i=0; i<sl_FilenameList.count(); i++ )
        {
            if ( s_oldPath != sl_FilenameList.at( i ).section( "/", 0, -2 ) )
            {
                tcmd << "rm -r " << sl_FilenameList.at( i ).section( "/", 0, -2 ) << "/thumbs" << endl;

                s_oldPath = sl_FilenameList.at( i ).section( "/", 0, -2 );
            }
        }
    }

    if ( b_runScript == true )
        tcmd << "rm " << s_CommandFile << endl;

    fcmd.close();

// **********************************************************************************************
// create dataset import file

    timp << "Event label\t15651" << endl;

    for ( int i=0; i<sl_EventLabelList.count(); i++ )
    {
        QString s_UploadDirectory = UploadDirectory( 0, mode );
        QString s_PHP_cmd         = "https://www.pangaea.de/helpers";

        s_PHP_cmd.append( s_UploadDirectory.replace( "Images/", "" ) );
        s_PHP_cmd.append( tr( ".php?B=" ) );
        s_PHP_cmd.append( sl_EventLabelList.at( i ).section( "/", 0, 0 ) );  // Level 1 (Basis)
        s_PHP_cmd.append( tr( "&C=" ) );
        s_PHP_cmd.append( sl_EventLabelList.at( i ).section( "/", 1, 1 ) );  // Level 2 (Campaign)
        s_PHP_cmd.append( tr( "&S=" ) );
        s_PHP_cmd.append( sl_EventLabelList.at( i ).section( "/", 2, 2 ) );  // Level 3 (Site)
        s_PHP_cmd.append( tr( "&ID=%ID_dataSet%" ) ); // ID of the new dataset

        if ( sl_EventLabelList.at( i ).section( "/", 3, 3 ) != s_EventLabel_old )
        {
            timp << sl_EventLabelList.at( i ).section( "/", 3, 3 ) << "\t" << s_PHP_cmd << endl;

            s_EventLabel_old = sl_EventLabelList.at( i ).section( "/", 3, 3 );
        }
    }

    fimp.close();

// **********************************************************************************************

    #if defined(Q_OS_MAC)
        QProcess process;
        QString s_arg = "chmod u+x \"" + fcmd.fileName() + "\"";
        process.startDetached( s_arg );
        wait( 100 );
    #endif

    if ( b_runScript == true )
    {
        #if defined(Q_OS_WIN)
            startProgram( s_CommandFile, "" );
        #endif

        #if defined(Q_OS_MAC)
            s_arg = "\"" + QDir::toNativeSeparators( fcmd.fileName() ) + "\"";
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
    }

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-01-30

QString MainWindow::setLocalFile( const QString &s_LocalFileIn )
{
    const QString _ERROR_  = "_ERROR_";

    QString s_LocalFileOut = s_LocalFileIn;

// **********************************************************************************************

    s_LocalFileOut.replace( ".tif", ".jpg" );

// **********************************************************************************************

    if ( s_LocalFileIn.contains( "_bath", Qt::CaseInsensitive ) == true )
        return( tr( "/" ) + _BENTHOSBATH_FILENAME_ );

    if ( s_LocalFileIn.contains( "_coresec", Qt::CaseInsensitive ) == true )
        return( tr( "/" ) + _CORESECTIONTABLE_FILENAME_ );

    if ( s_LocalFileIn.contains( "_descr", Qt::CaseInsensitive ) == true )
        return( tr( "/" ) + _COREDESCRIPTION_FILENAME_ );

    if ( s_LocalFileIn.contains( "_legend", Qt::CaseInsensitive ) == true )
        return( tr( "/" ) + _CORELEGEND_FILENAME_ );

    if ( s_LocalFileIn.contains( "_log", Qt::CaseInsensitive ) == true )
        return( tr( "/" ) + _CORELOGGERPROTOKOLL_FILENAME_ );

    if ( s_LocalFileIn.contains( "_map", Qt::CaseInsensitive ) == true )
        return( tr( "/" ) + _BENTHOSMAP_FILENAME_ );

    if ( s_LocalFileIn.contains( "_track", Qt::CaseInsensitive ) == true )
        return( tr( "/" ) + _BENTHOSTRACK_FILENAME_ );

    if ( s_LocalFileIn.endsWith( "jpg" ) == true )
        return( tr( "/thumbs/" ) + s_LocalFileOut );

    if ( s_LocalFileIn.endsWith( "png" ) == true )
        return( tr( "/thumbs/" ) + s_LocalFileOut );

    if ( s_LocalFileIn.endsWith( "gif" ) == true )
        return( tr( "/thumbs/" ) + s_LocalFileOut );

    if ( s_LocalFileIn.endsWith( "tif" ) == true )
        return( tr( "/thumbs/" ) + s_LocalFileOut );

    return( _ERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-01-02

QStringList MainWindow::createUploadDirectoryList( const QStringList &sl_FilenameList, const QString &s_Level1_static, const QString &s_Level2_static, const int l2f, const int l2l, const QString &s_Level3_static, const int l3f, const int l3l )
{
    QStringList sl_UploadDirectoryList;

// **********************************************************************************************

    for ( int i=0; i<sl_FilenameList.count(); i++ )
    {
        QFileInfo fimage( sl_FilenameList.at( i ) );
        QString   s_FilenameImage = fimage.completeBaseName();
        QString   s_newPath       = s_Level1_static;

        if ( sl_UploadDirectoryList.contains( s_newPath ) == false )
            sl_UploadDirectoryList.append( s_newPath );

        s_newPath.append( tr( "/" ) + s_Level2_static );
        if ( ( l2l > 0 ) && ( l2f > 0 ) )
            s_newPath.append( s_FilenameImage.mid( l2f-1, l2l-l2f+1 ) );

        if ( sl_UploadDirectoryList.contains( s_newPath ) == false )
            sl_UploadDirectoryList.append( s_newPath );

        s_newPath.append( tr( "/" ) + s_Level3_static );
        if ( ( l3l > 0 ) && ( l3f > 0 ) )
            s_newPath.append( s_FilenameImage.mid( l3f-1, l3l-l3f+1 ) );

        if ( sl_UploadDirectoryList.contains( s_newPath ) == false )
            sl_UploadDirectoryList.append( s_newPath );
    }

    sl_UploadDirectoryList.sort();

    return( sl_UploadDirectoryList );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-09-11

QStringList MainWindow::createEventLabelList( const QStringList &sl_FilenameList, const QString &s_Level1_static, const QString &s_Level2_static, const int l2f, const int l2l, const QString &s_Level3_static, const int l3f, const int l3l,const QString &s_Level4_static, const int l4f, const int l4l )
{
    QStringList sl_EventLabelList;

// **********************************************************************************************

    for ( int i=0; i<sl_FilenameList.count(); i++ )
    {
        QFileInfo fimage( sl_FilenameList.at( i ) );
        QString   s_FilenameImage = fimage.completeBaseName();
        QString   s_EventLabel    = s_Level1_static;

        s_EventLabel.append( tr( "/" ) + s_Level2_static );
        if ( ( l2l > 0 ) && ( l2f > 0 ) )
            s_EventLabel.append( s_FilenameImage.mid( l2f-1, l2l-l2f+1 ) );

        s_EventLabel.append( tr( "/" ) + s_Level3_static );
        if ( ( l3l > 0 ) && ( l3f > 0 ) )
            s_EventLabel.append( s_FilenameImage.mid( l3f-1, l3l-l3f+1 ) );

        s_EventLabel.append( tr( "/" ) + s_Level4_static );
        if ( ( l4f > 0 ) && ( l4l > 0 ) )
            s_EventLabel.append( s_FilenameImage.mid( l4f-1, l4l-l4f+1 ) );

        sl_EventLabelList.append( s_EventLabel );
    }

    return( sl_EventLabelList );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-01-02

QStringList MainWindow::createRemoteFilenameList( const int mode, const QStringList &sl_FilenameList, const QString &s_Level1_static, const QString &s_Level2_static, const int l2f, const int l2l, const QString &s_Level3_static, const int l3f, const int l3l )
{
    QStringList sl_RemoteFilenameList;

    for ( int i=0; i<sl_FilenameList.count(); i++ )
    {
        QFileInfo fimage( sl_FilenameList.at( i ) );
        QString   s_FilenameImage  = fimage.completeBaseName();
        QString   s_FilenameRemote = s_Level1_static;

        s_FilenameRemote.append( tr( "/" ) + s_Level2_static );
        if ( ( l2l > 0 ) && ( l2f > 0 ) )
            s_FilenameRemote.append( s_FilenameImage.mid( l2f-1, l2l-l2f+1 ) );

        s_FilenameRemote.append( tr( "/" ) + s_Level3_static );
        if ( ( l3l > 0 ) && ( l3f > 0 ) )
            s_FilenameRemote.append( s_FilenameImage.mid( l3f-1, l3l-l3f+1 ) );

        switch ( mode )
        {
        case _THUMBNAILS_:
            if ( ( s_FilenameImage.endsWith( "_bath", Qt::CaseInsensitive ) == false )
              && ( s_FilenameImage.endsWith( "_coresec", Qt::CaseInsensitive ) == false )
              && ( s_FilenameImage.endsWith( "_descr", Qt::CaseInsensitive ) == false )
              && ( s_FilenameImage.endsWith( "_legend", Qt::CaseInsensitive ) == false )
              && ( s_FilenameImage.endsWith( "_log", Qt::CaseInsensitive ) == false )
              && ( s_FilenameImage.endsWith( "_map", Qt::CaseInsensitive ) == false )
              && ( s_FilenameImage.endsWith( "_track", Qt::CaseInsensitive ) == false ) )
            {
                if ( fimage.suffix() == "tif" )
                    s_FilenameRemote.append( tr( "/TN_" ) + s_FilenameImage + tr( "_tiff.jpg" ) );

                if ( fimage.suffix() == "pdf" )
                    s_FilenameRemote.append( tr( "/TN_" ) + s_FilenameImage + tr( "_pdf.txt" ) );

                if ( fimage.suffix() == "txt" )
                    s_FilenameRemote.append( tr( "/TN_" ) + s_FilenameImage + tr( "_txt.txt" ) );

                if ( fimage.suffix() == "jpg" )
                    s_FilenameRemote.append( tr( "/TN_" ) + s_FilenameImage + tr( ".jpg" ) );

                if ( fimage.suffix() == "png" )
                    s_FilenameRemote.append( tr( "/TN_" ) + s_FilenameImage + tr( ".png" ) );

                if ( fimage.suffix() == "gif" )
                    s_FilenameRemote.append( tr( "/TN_" ) + s_FilenameImage + tr( ".gif" ) );
            }
            else
            {
                if ( fimage.suffix() == "pdf" )
                    s_FilenameRemote.append( tr( "/" ) + s_FilenameImage + tr( "_pdf.txt" ) );

                if ( fimage.suffix() == "txt" )
                    s_FilenameRemote.append( tr( "/" ) + s_FilenameImage + tr( "_txt.txt" ) );

                if ( fimage.suffix() == "jpg" )
                    s_FilenameRemote.append( tr( "/" ) + s_FilenameImage + tr( "_jpg.txt" ) );

                if ( fimage.suffix() == "png" )
                    s_FilenameRemote.append( tr( "/" ) + s_FilenameImage + tr( "_png.txt" ) );

                if ( fimage.suffix() == "gif" )
                    s_FilenameRemote.append( tr( "/" ) + s_FilenameImage + tr( "_gif.txt" ) );
            }

            break;

        default:
            s_FilenameRemote.append( "/" + s_FilenameImage + "." + fimage.suffix() );
            break;
        }

        sl_RemoteFilenameList.append( s_FilenameRemote );
    }

    return( sl_RemoteFilenameList );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-01-02

QString MainWindow::UploadDirectory( const int server, const int mode )
{
    QString s_UploadDirectory = "";

    switch ( server )
    {
    case _HSSRV2_:
        s_UploadDirectory = "/hs/usero";
        break;
    case _MW1_:
        s_UploadDirectory = "/pangaea/htdocs/pangaea-family/store";
        break;
    default:
        break;
    }

    switch ( mode )
    {
    case _BENTHOS_:
        s_UploadDirectory.append( "/Images/Benthos" );
        break;
    case _CORES_:
        s_UploadDirectory.append( "/Images/Cores" );
        break;
    case _LINESCANS_:
        s_UploadDirectory.append( "/Images/Linescan" );
    default:
        break;
    }

    return( s_UploadDirectory );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-12-30

int MainWindow::doBuildScript( const int mode )
{
    int     err             = 0;

// **********************************************************************************************

    existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList );

    if (  gsl_FilenameList.count() > 0 )
    {
        if ( doSetThumbnailOptionsDialog( mode, gsl_FilenameList.at( 0 ), gs_Level1_static, gs_Level2_static, gi_Level2_first, gi_Level2_last, gs_Level3_static, gi_Level3_first, gi_Level3_last, gs_Level4_static, gi_Level4_first, gi_Level4_last, gi_ImagesTurnAngle, gi_ThumbnailWidth, gi_ThumbnailHeight, gb_createThumbnails, gb_uploadThumbnails, gb_uploadImages, gb_turnImages, gb_runScript ) == QDialog::Accepted )
            err = buildScript( mode, gs_User_hssrv2, gs_Password_hssrv2, gs_User_pangaea, gs_Password_pangaea, gsl_FilenameList, gs_EasyThumbnails, gs_wget, gs_psftp, gs_Level1_static, gs_Level2_static, gi_Level2_first, gi_Level2_last, gs_Level3_static, gi_Level3_first, gi_Level3_last, gs_Level4_static, gi_Level4_first, gi_Level4_last, gi_ImagesTurnAngle, gi_ThumbnailWidth, gi_ThumbnailHeight, gb_createThumbnails, gb_uploadThumbnails, gb_uploadImages, gb_turnImages, gb_runScript );
        else
            err = _CHOOSEABORTED_;
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

    if ( err == _NOERROR_ )
        return( _DONE_ );

    return( err );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-12-30

void MainWindow::doBuildBenthosScript()
{
    int err = doBuildScript( _BENTHOS_ );

    onError( err );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doBuildOFOSScript()
{
    int err = doBuildScript( _OFOS_ );

    onError( err );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doBuildCoresScript()
{
    int err = doBuildScript( _CORES_ );

    onError( err );
}

void MainWindow::doBuildLinescansScript()
{
    int err = doBuildScript( _LINESCANS_ );

    onError( err );
}

