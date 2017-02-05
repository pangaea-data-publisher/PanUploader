/* Application.h              */
/* 2013-05-15                 */
/* Dr. Rainer Sieger          */

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QTextEdit>
#include <QTextCodec>
#include <QTextStream>
#include <QStringListModel>
#include <QListView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QProcess>
#include <QTimer>
#include <QTime>
#include <QMimeData>
#include <QDesktopServices>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>
#include <QStatusBar>
#include <QSettings>
#include <QSslError>

#include "Globals.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QAction;
class QLabel;
class QProgressDialog;
class QProgressBar;
class QTimer;
class QDateTime;
class QUrl;
class QTextEdit;
class QStringListModel;
class QListView;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO( "author", "Rainer Sieger" )
    Q_CLASSINFO( "url", "https://pangaea.de" )

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    int         gi_EOL;                          //!< End-of-Line Zeichen fuer die Outputdateien
    int         gi_Codec;                        //!< Zeichenkodierung
    int         gi_Extension;                    //!< Dateierweiterung fuer Ausgabedateien
    int         gi_ActionNumber;                 //!< Die ActionNumber wird bei jedem angewandenten Tool um 1 erhoeht.
    int         gi_NumOfProgramStarts;           //!< Anzahl der Programmstarts

    bool        gb_showProgressBar;              //!< Soll der ProgressBar im Fenster unten rechts angezeigt werden?

    QStringList gsl_FilenameList;                //!< Liste aller InputDateinamen incl. Pfad.

    QString		gs_FilenameFormat;               //!< Bestimmt in die Form des automatisch erzeugten neuen Dateinamens. \%a = aktuelle Actionnumber, \%N = Dateiname.
    QString		gs_Path;                         //!< Der zuletzt verwendete Pfad.
    QString     gs_Version;                      //!< Aktuelle Version des Programms.
    QString     gs_lastDate;                     //!< Datum des letzten Downloads

    QPoint      posWindow;                       //!< Position des Programmfensters.
    QSize       sizeWindow;                      //!< Groesse des Programmfensters.

    QPoint      posDialog;                       //!< Position der Dialoge.
    QSize       sizeParameterDialog;             //!< Groesse der Parameterdialogs.

    QString     gs_WorkingDirectory;

    QString     gs_EasyThumbnails;
    QString     gs_wget;
    QString     gs_psftp;

    QString     gs_User_pangaea;
    QString     gs_Password_pangaea;

    QString     gs_User_hssrv2;
    QString     gs_Password_hssrv2;

    QString     gs_Level1_static;
    QString     gs_Level2_static;
    QString     gs_Level3_static;
    QString     gs_Level4_static;

    int         gi_Level2_first;
    int         gi_Level2_last;
    int         gi_Level3_first;
    int         gi_Level3_last;
    int         gi_Level4_first;
    int         gi_Level4_last;

    int         gi_ThumbnailWidth;
    int         gi_ThumbnailHeight;
    int         gi_ImagesTurnAngle;

    bool        gb_createThumbnails;
    bool        gb_uploadThumbnails;
    bool        gb_uploadImages;
    bool        gb_runScript;

    int doBuildScript( const int mode );
    int createDummyFiles( const QString &WorkingDirectory );
    int uploadImagesJubany( const QStringList &FilenameList, const QString &User_hssrv2, const QString &Password_hssrv2, const QString &User_pangaea, const QString &Password_pangaea, bool &createThumbnails, bool &uploadThumbnails, bool &uploadImages, bool &runScript );
    int buildScript( const int mode, const QString &User_hssrv2, const QString &Password_hssrv2, const QString &User_pangaea, const QString &Password_pangaea, QStringList &FilenameList, const QString &EasyThumbnails, const QString &wget, const QString &psftp, const QString &Level1_static, const QString &Level2_static, const int Level2_first, const int Level2_last, const QString &Level3_static, const int Level3_first, const int Level3_last, const QString &Level4_static, const int Level4_first, const int Level4_last, const int ThumbnailWidth, const int ThumbnailHeight, const bool createThumbnails, const bool uploadThumbnails, const bool uploadImages, const bool runScript );
    int startProgram( const QString &Program, const QString &Filename );

    QString UploadDirectory(const int server, const int mode );
    QString setLocalFile( const QString &LocalFileIn );

    QStringList createEventLabelList( const QStringList &FilenameList, const QString &Level1_static, const QString &Level2_static, const int l2f, const int l2l, const QString &Level3_static, const int l3f, const int l3l, const QString &Level4_static, const int l4f, const int l4l );
    QStringList createUploadDirectoryList( const QStringList &FilenameList, const QString &Level1_static, const QString &Level2_static, const int Level2_first, const int Level2_last, const QString &Level3_static, const int Level3_first, const int Level3_last );
    QStringList createRemoteFilenameList( const int mode, const QStringList &FilenameList, const QString &Level1_static, const QString &Level2_static, const int Level2_first, const int Level2_last, const QString &Level3_static, const int Level3_first, const int Level3_last );

    int doSetThumbnailOptionsDialog( const int mode, const QString &FilenameIn, QString &Level1_static, QString &Level2_static, int &Level2_first, int &Level2_last, QString &Level3_static, int &Level3_first, int &Level3_last, QString &Level4_static, int &Level4_first, int &Level4_last, int &ThumbnailWidth, int &ThumbnailHeight, bool &createThumbnails, bool &uploadThumbnails, bool &uploadImages, bool &runScript );
    int doSetTurnImagesOptionsDialog( int &ImagesTurnAngle );

protected:
    void dragEnterEvent( QDragEnterEvent *event );
    void dropEvent( QDropEvent *event );
    void closeEvent( QCloseEvent *event );
    void onError( const int err );

signals:
    void finishedBuildFilelist();

private slots:
    int  chooseFile();
    int  chooseFiles();
    int  chooseFolder( const QString &Folder = "" );
    int  saveFile();
    int  saveFileAs();

    void exitApplication();
    void hideWindow();
    void newWindow();
    void displayHelp();
    void about();
    void clearStatusMessage();

    void doSetGlobalOptionsDialog();

    void doBuildBenthosScript();
    void doBuildOFOSScript();
    void doBuildCoresScript();
    void doBuildLinescansScript();
    void doUploadImagesJubany();

    void doTurnImages();

private:
    QStringList expandCommandline();
    QStringList renameFiles( const QStringList &Filename, const QString &searchStr, const QString &replaceStr );
    bool buildFilename( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QString &Filename, QString &FilenameIn, QString &FilenameOut );
    bool containsBinaryFile( const QStringList &FilenameList );
    bool existsFirstFile( const int ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList );
    bool isEmptyLine( const QString &String );
    QString findCurl();
    QString findZip( const int mode = 1 );
    QString findUnzip( int const mode = 1 );
    int NumOfSections( const QString &String );
    int addToFilenameList( QStringList &FilenameList, const QString &Filename, const bool showAllFiles = true, const bool decompressFile = false );
    int calcFileSizeClass( const QString &FilenameIn, const int NumOfFiles, const int lowerLimit = 100, const int upperLimit = 1000 );
    int copyStringList( const QStringList &InStringList, QStringList &OutStringList, const QString &s_Pattern = "*" );
    int emptyDir( const QString &Dir );
    int decompressFile( const QString &Filename, const bool delZipFile = false, const int mode = 1, const QString &Program = "zip" );
    int incFileProgress( const int NumOfFiles, const int FileNumber );
    int incProgress( const int NumOfFiles, const int Step );
    int readFile( const QString &FilenameIn, QStringList &Input, const int Codec = -1, const int NumOfFiles = 0, const qint64 Bytes = 0 );
    int removeFile( const QString &Filename );
    int downloadFile( const QString &Curl, const QString &Url, const QString &Filename );
    unsigned int incProgress( const int NumOfFiles, const unsigned int filesize, const unsigned int length, const QString &InputStr );
    void appendItem( QStringList &List, const QString &Item, const QString &SS = "", const QString &RS = "" );
    void compressFolder( const QString &FolderIn, const int mode = 1, const QString &Program = "zip" );
    void compressFile( const QString &FilenameIn, const int mode = 1, const QString &Program = "zip" );
    void clearFilenameList( int &ActionNumber, QStringList &FilenameList );
    void clearList( QStringList &List );
    void clearMessage();
    void createActions();
    void createMenus();
    void createStatusBar( const bool showProgressBar );
    void enableMenuItems( const QStringList &FilenameList );
    void endTool( const int err, const int stopProgress, int &ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList, const QString &doneMessage = "Done", const QString &canceledMessage = "Converter was canceled", const bool clearList = false, const bool incActionNumber = true );
    void initFileProgress( const int NumOfFiles, const QString &FilenameIn, const QString &MessageText );
    void initProgress( const int NumOfFiles, const QString &Filename, const QString &MessageText, const int totalNumberOfSteps );
    void initProgress( const int totalNumberOfSteps );
    void listDir( QStringList &Filename, const QString &Directory, const bool showAllFiles = true, const bool decompressFile = false );
    void loadPreferences();
    void resetFileProgress( const int NumOfFiles );
    void resetProgress( const int NumOfFiles = 0 );
    void savePreferences();
    void setNormalCursor();
    void setStatusBar( const QString &Message = "", const int seconds = 0 );
    void setStatusBarFileInProgress( const QString &Filename, const QString &Message = "", const int i_seconds = 0 );
    void setWTitle( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList &FilenameList );
    void setWaitCursor();
    void showFilenameList( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList &FilenameList );
    void showList( const QStringList &List );
    void showMessage( const QString &Message, QStringList &MessageList );
    void wait( const int msec );

    QString getApplicationName( const bool replaceUnderline = false );
    QString getDataLocation();
    QString getDocumentDir();
    QString getPreferenceFilename();
    QString getVersion();
    QString setEOLChar( const int EOL );
    QString setExtension( const int Extension );
    QString getFileChecksum( const QString &FilenameIn );

    QMenu	*fileMenu;
    QMenu	*scriptMenu;
    QMenu	*helpMenu;

    QAction *newWindowAction;
    QAction *openFileAction;
    QAction *openFolderAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *hideWindowAction;
    QAction *setGlobalOptionsDialogAction;
    QAction *exitAction;
    QAction *getDatesAction;
    QAction *runBenthosScriptAction;
    QAction *runOFOSScriptAction;
    QAction *runCoresScriptAction;
    QAction *runJubanyScriptAction;
    QAction *runLinescansScriptAction;
    QAction *turnImagesAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *showHelpAction;

    QProgressDialog *ProgressDialog;
    QProgressDialog *FileProgressDialog;
    QProgressBar    *ProgressBar;
    QLabel			*StatusMessage;

    QStringListModel	*Model;
    QListView			*ListView;
    QTextEdit			*textViewer;
};

#endif
