// ***********************************************************************************************
// *                                                                                             *
// * createMenu.cpp - creates application menus                                                  *
// *                                                                                             *
// * Dr. Rainer Sieger - 2008-05-18                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Erstellen der Menue-Aktionen. */

void MainWindow::createActions()
{
// File menu
    newWindowAction = new QAction(tr("New window"), this);
    newWindowAction->setShortcut(tr("Ctrl+N"));
    connect(newWindowAction, SIGNAL(triggered()), this, SLOT(newWindow()));

    openFileAction = new QAction(tr("Open..."), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(chooseFiles()));

    openFolderAction = new QAction(tr("Select Folder..."), this);
    openFolderAction->setShortcut(tr("Ctrl+F"));
    connect(openFolderAction, SIGNAL(triggered()), this, SLOT(chooseFolder()));

    saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveAsAction = new QAction(tr("Save As..."), this);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    hideWindowAction = new QAction(tr("Close window"), this);
    hideWindowAction->setShortcut(tr("Ctrl+W"));
    connect(hideWindowAction, SIGNAL(triggered()), this, SLOT(hideWindow()));

    exitAction = new QAction(tr("Quit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitApplication()));

    setGlobalOptionsDialogAction = new QAction(tr("General options..."), this);
    setGlobalOptionsDialogAction->setShortcut(tr("Ctrl+,"));
    connect(setGlobalOptionsDialogAction, SIGNAL(triggered()), this, SLOT(doSetGlobalOptionsDialog()));

    runBenthosScriptAction = new QAction(tr("Run Benthos script..."), this);
    connect(runBenthosScriptAction, SIGNAL(triggered()), this, SLOT(doBuildBenthosScript()));

    runOFOSScriptAction = new QAction(tr("Run OFOS script..."), this);
    connect(runOFOSScriptAction, SIGNAL(triggered()), this, SLOT(doBuildOFOSScript()));

    runCoresScriptAction = new QAction(tr("Run Cores script..."), this);
    connect(runCoresScriptAction, SIGNAL(triggered()), this, SLOT(doBuildCoresScript()));

    runLinescansScriptAction = new QAction(tr("Run Linescans script..."), this);
    connect(runLinescansScriptAction, SIGNAL(triggered()), this, SLOT(doBuildLinescansScript()));

    runJubanyScriptAction = new QAction(tr("Run Jubany script..."), this);
    connect(runJubanyScriptAction, SIGNAL(triggered()), this, SLOT(doCreateJubanyThumbnails()));

    turnImagesAction = new QAction(tr("Turn images..."), this);
    connect(turnImagesAction, SIGNAL(triggered()), this, SLOT(doTurnImages()));

    // Help menu
    aboutAction = new QAction(tr("About ") + getApplicationName(), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    showHelpAction = new QAction(getApplicationName() + tr("Help"), this);
    showHelpAction->setShortcut(tr("F1"));
    connect(showHelpAction, SIGNAL(triggered()), this, SLOT(displayHelp()));

#if defined(Q_OS_WIN)
    newWindowAction->setStatusTip(tr("Create a new file"));
    runScriptAction->setStatusTip(tr("Run the upload script"));
    openFolderAction->setStatusTip(tr("Choose an existing folder"));
    saveAction->setStatusTip(tr("Save the document to disk"));
    saveAsAction->setStatusTip(tr("Save the document under a new name"));
    exitAction->setStatusTip(tr("Exit the application"));
    setGlobalOptionsDialogAction->setStatusTip(tr("Set global options"));
    aboutAction->setStatusTip(tr("Show the application's About box"));
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    showHelpAction->setStatusTip(tr("Show the application's help"));
#endif

}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Verbindet Menues mit Aktionen. */

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu( tr( "&File" ) );
    fileMenu->addAction( openFileAction );
    fileMenu->addAction( openFolderAction );
    fileMenu->addSeparator();

#if defined(Q_OS_LINUX)
    ;
#endif

#if defined(Q_OS_MAC)
    fileMenu->addAction( newWindowAction );
    newWindowAction->setEnabled( false );
    fileMenu->addAction( hideWindowAction );
#endif

#if defined(Q_OS_WIN)
    fileMenu->addAction( hideWindowAction );
#endif

    fileMenu->addSeparator();
    fileMenu->addAction( setGlobalOptionsDialogAction );

    fileMenu->addSeparator();
    fileMenu->addAction( exitAction );

// **********************************************************************************************

    scriptMenu = menuBar()->addMenu( tr( "&Script" ) );
    scriptMenu->addAction( runBenthosScriptAction );
    scriptMenu->addAction( runOFOSScriptAction );
    scriptMenu->addAction( runCoresScriptAction );
    scriptMenu->addAction( runJubanyScriptAction );
    scriptMenu->addAction( runLinescansScriptAction );
    scriptMenu->addSeparator();
    scriptMenu->addAction( turnImagesAction );

    helpMenu = menuBar()->addMenu( tr( "&Help" ) );
    helpMenu->addAction( aboutAction );
    helpMenu->addAction( aboutQtAction );
    helpMenu->addSeparator();
    helpMenu->addAction( showHelpAction );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::enableMenuItems( const QStringList &sl_FilenameList )
{
    bool b_containsBinaryFile = containsBinaryFile( sl_FilenameList );

// **********************************************************************************************

    QList<QAction*> scriptMenuActions = scriptMenu->actions();

    if ( b_containsBinaryFile == false )
    {
        for ( int i=0; i<scriptMenuActions.count(); ++i )
            scriptMenuActions.at( i )->setEnabled( true );
    }
    else
    {
        ;
    }
}
