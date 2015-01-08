/****************************************************************
**
** Preferences
** 2008-12-01, Dr. Rainer Sieger
** last change: 2009-12-01
**
****************************************************************/

#include "Application.h"

/*! @brief Sichern der Programmeinstellungen */

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-07-03

void MainWindow::savePreferences()
{
    #if defined(Q_OS_LINUX)
        gi_Codec = _UTF8_; // UTF-8
        gi_EOL   = _UNIX_;
    #endif

    #if defined(Q_OS_MAC)
        gi_Codec = _APPLEROMAN_; // Mac Roman
        gi_EOL   = _UNIX_;
    #endif

    #if defined(Q_OS_WIN)
        gi_Codec = _LATIN1_; // Latin-1 = ISO 8859-1
        gi_EOL   = _WIN_;
    #endif

    #if defined(Q_OS_LINUX)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    #if defined(Q_OS_MAC)
        QSettings settings( getPreferenceFilename(), QSettings::NativeFormat );
    #endif

    #if defined(Q_OS_WIN)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    settings.beginGroup( getApplicationName( true ) );

    settings.setValue( "NumOfProgramStarts", gi_NumOfProgramStarts );
    settings.setValue( "WindowX", x() );
    settings.setValue( "WindowY", y() );
    settings.setValue( "WindowHeight", height() );
    settings.setValue( "WindowWidth", width() );

    settings.setValue( "DialogX", posDialog.x() );
    settings.setValue( "DialogY", posDialog.y() );

    settings.setValue( "Path", gs_Path );

    settings.setValue( "LastDate", gs_lastDate );

    settings.setValue( "WorkingDirectory", gs_WorkingDirectory );

    settings.setValue( "EasyThumbnails", gs_EasyThumbnails );
    settings.setValue( "Wget", gs_wget );
    settings.setValue( "Psftp", gs_psftp );

    settings.setValue( "UserP", gs_User_pangaea );
    settings.setValue( "PasswordP", gs_Password_pangaea );

    settings.setValue( "UserH", gs_User_hssrv1 );
    settings.setValue( "PasswordH", gs_Password_hssrv1 );

    settings.setValue( "Level1_static", gs_Level1_static );
    settings.setValue( "Level2_static", gs_Level2_static );
    settings.setValue( "Level2_first", gi_Level2_first );
    settings.setValue( "Level2_last", gi_Level2_last );
    settings.setValue( "Level3_static", gs_Level3_static );
    settings.setValue( "Level3_first", gi_Level3_first );
    settings.setValue( "Level3_last", gi_Level3_last );
    settings.setValue( "Level4_static", gs_Level4_static );
    settings.setValue( "Level4_first", gi_Level4_first );
    settings.setValue( "Level4_last", gi_Level4_last );
    settings.setValue( "ImagesTurnAngle", gi_ImagesTurnAngle );
    settings.setValue( "ThumbnailWidth", gi_ThumbnailWidth );
    settings.setValue( "ThumbnailHeight", gi_ThumbnailHeight );

    settings.setValue( "CreateThumbnails", gb_createThumbnails );
    settings.setValue( "UploadThumbnails", gb_uploadThumbnails );
    settings.setValue( "UploadImages", gb_uploadImages );
    settings.setValue( "TurnImages", gb_turnImages );
    settings.setValue( "RunScript", gb_runScript );

    settings.endGroup();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-07-03

/*! @brief Laden der Programmeinstellungen */

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::loadPreferences()
{
    #if defined(Q_OS_LINUX)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    #if defined(Q_OS_MAC)
        QSettings settings( getPreferenceFilename(), QSettings::NativeFormat );
    #endif

    #if defined(Q_OS_WIN)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    settings.beginGroup( getApplicationName( true ) );

    posWindow.setX( settings.value( "WindowX", 100 ).toInt() );
    posWindow.setY( settings.value( "WindowY", 100 ).toInt() );
    sizeWindow.setHeight( settings.value( "WindowHeight", 250 ).toInt() );
    sizeWindow.setWidth( settings.value( "WindowWidth", 600 ).toInt() );

    posDialog.setX( settings.value( "DialogX", 110 ).toInt() );
    posDialog.setY( settings.value( "DialogY", 110 ).toInt() );

    gs_Path                 = settings.value( "Path", getDocumentDir() ).toString();
    gi_NumOfProgramStarts   = settings.value( "NumOfProgramStarts", 0 ).toInt();

    gs_lastDate             = settings.value( "LastDate", QDate::currentDate().toString( Qt::ISODate ) ).toString();
    gs_WorkingDirectory     = settings.value( "WorkingDirectory", getDocumentDir() ).toString();

    gs_EasyThumbnails       = settings.value( "EasyThumbnails", "" ).toString();
    gs_wget                 = settings.value( "Wget", "" ).toString();
    gs_psftp                = settings.value( "Psftp", "" ).toString();

    gs_User_pangaea         = settings.value( "UserP", "" ).toString();
    gs_Password_pangaea     = settings.value( "PasswordP", "" ).toString();

    gs_User_hssrv1          = settings.value( "UserH", "" ).toString();
    gs_Password_hssrv1      = settings.value( "PasswordH", "" ).toString();

    gs_Level1_static        = settings.value( "Level1_static", "M" ).toString();
    gs_Level2_static        = settings.value( "Level2_static", "M25" ).toString();
    gi_Level2_first         = settings.value( "Level2_first", "1" ).toInt();
    gi_Level2_last          = settings.value( "Level2_last", "4" ).toInt();
    gs_Level3_static        = settings.value( "Level3_static", "" ).toString();
    gi_Level3_first         = settings.value( "Level3_first", "1" ).toInt();
    gi_Level3_last          = settings.value( "Level3_last", "8" ).toInt();
    gs_Level4_static        = settings.value( "Level4_static", "" ).toString();
    gi_Level4_first         = settings.value( "Level4_first", "1" ).toInt();
    gi_Level4_last          = settings.value( "Level4_last", "10" ).toInt();
    gi_ImagesTurnAngle      = settings.value( "ImagesTurnAngle", 90 ).toInt();
    gi_ThumbnailWidth       = settings.value( "ThumbnailWidth", "250" ).toInt();
    gi_ThumbnailHeight      = settings.value( "ThumbnailHeight", "250" ).toInt();
    gb_createThumbnails     = settings.value( "CreateThumbnails", true ).toBool();
    gb_uploadThumbnails     = settings.value( "UploadThumbnails", true ).toBool();
    gb_uploadImages         = settings.value( "UploadImages", true ).toBool();
    gb_turnImages           = settings.value( "TurnImages", false  ).toBool();
    gb_runScript            = settings.value( "RunScript", false ).toBool();

    settings.endGroup();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Ermitteln des Dateinamens fuer die Programmeinstellungen.
*   @return Name der Datei fuer die Programmeinstellungen. Dateiname ist gleich "_ERROR_",
*   wenn Betriebssystem ungleich Windows, Mac OS oder Unix ist.
*/

QString MainWindow::getPreferenceFilename()
{
    QString s_PrefFilename = "";

    #if defined(Q_OS_LINUX)
        s_PrefFilename = QDir::homePath() + QLatin1String( "/.config/" ) + QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName() + "/" + QCoreApplication::applicationName() + QLatin1String( ".conf" );
    #endif

    #if defined(Q_OS_MAC)
        s_PrefFilename = QDir::homePath() + QLatin1String( "/Library/Preferences/" ) + QCoreApplication::organizationDomain().section( ".", 1, 1 ) + "." + QCoreApplication::organizationDomain().section( ".", 0, 0 ) + "." + QCoreApplication::applicationName() + QLatin1String( ".plist" );
    #endif

    #if defined(Q_OS_WIN)
        if ( QCoreApplication::applicationName().toLower().endsWith( "portable" ) )
        {
            s_PrefFilename = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + QLatin1String( ".ini" );
        }
        else
        {
            QSettings cfg( QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName() );
            s_PrefFilename = QFileInfo( cfg.fileName() ).absolutePath() + "/" + QCoreApplication::applicationName() + "/" + QCoreApplication::applicationName() + QLatin1String( ".ini" );
        }
    #endif

    return( s_PrefFilename );
}
