/* ApplicationMainWindow.cpp  */
/* 2009-08-09                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Initalisierung des CentralWidget.
*
*   Am Beginn der Methode wird der Cursor auf den WaitCursor des Betriebssystems
*   gesetzt. Dann folgt die Intialisierung einiger globaler Variablen (ActionNumer, sl_FilenameList,
*   sl_Message). Model und ListView werden erzeugt und das CentralWidget gesetzt. Nach dem Laden
*   der Programmeinstellungen werden die Menues erzeugt. Die Fensterposition und -groesse wird
*   gesetzt. Abschliessend wird das Fenster angezeigt und der Cursor zuruek auf den NormalCursor gesetzt.
*/

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent )
{
//  QObject::connect( this, SIGNAL( finishedBuildFilelist() ), this, SLOT( doCreateJubanyThumbnails() ) );

// **********************************************************************************************

    setWaitCursor();

// **********************************************************************************************
// init

    gi_ActionNumber  = 1;
    gi_Extension     = _TXT_;

    gs_Version       = "unknown";

    gsl_FilenameList.clear();

// **********************************************************************************************

    #if defined(Q_OS_LINUX)
        gb_showProgressBar = true;
    #endif

    #if defined(Q_OS_MAC)
        gb_showProgressBar = false;
    #endif

    #if defined(Q_OS_WIN)
        gb_showProgressBar = true;
    #endif

// **********************************************************************************************

    Model		= new QStringListModel( this );
    ListView	= new QListView;

    ListView->setModel( Model );
    ListView->setEditTriggers( QAbstractItemView::NoEditTriggers );

    setCentralWidget( ListView );

    setAcceptDrops( true );

// **********************************************************************************************

    loadPreferences();

    if ( gi_NumOfProgramStarts++ < 1 )
        savePreferences();

    gs_Version = getVersion();

// **********************************************************************************************

    createActions();
    createMenus();
    createStatusBar( gb_showProgressBar );

// **********************************************************************************************

    this->resize( sizeWindow );
    this->move( posWindow );
    this->show();

// **********************************************************************************************

    gsl_FilenameList = expandCommandline();

    if ( gsl_FilenameList.count() > 0 )
    {
        if ( gsl_FilenameList.at( 0 ) == "/auto" )
        {
            doGetDates();
            doCreateJubanyThumbnails();
        }
    }

// **********************************************************************************************

    setWTitle( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList );
    setStatusBar( tr( "Ready" ), 2 );
    setNormalCursor();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

MainWindow::~MainWindow()
{
}
