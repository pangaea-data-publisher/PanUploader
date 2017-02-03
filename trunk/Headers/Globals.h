#ifndef _GLOBALS

    #define _GLOBALS

// Application constants

    const QString _PROGRAMDOI_          = "";
    const QString _PROGRAMREADME_       = "https://wiki.pangaea.de/wiki/PanUploader";

    const QString _VERSION_             = "2.12"; // Version number, 2017-02-02
    const QChar   _PSEPARATOR_          = '|';

    const int   _NOERROR_               = 0;
    const int   _ERROR_                 = 1;
    const int   _APPBREAK_              = 2;
    const int   _DATAFOUND_             = 4;
    const int   _CHOOSEABORTED_         = 5;
    const int   _FILENOTEXISTS_         = 6;
    const int   _DONE_                  = 7;

    const int   _NODATAFOUND_           = -3;

    const int   _ZIP_                   = 1;
    const int   _GZIP_                  = 2;

    const int   _HSSRV2_                = 1;
    const int   _MW1_                   = 2;

    const int   _BENTHOS_               = 1;
    const int   _OFOS_                  = 2;
    const int   _CORES_                 = 3;
    const int   _LINESCANS_             = 4;
    const int   _JUBANY_                = 5;

    const int   _IMAGES_                = 1;
    const int   _THUMBNAILS_            = 2;

// EOL
    const int   _UNIX_                  = 0;    // LF
    const int   _MACOS_                 = 1;    // CR
    const int   _WIN_                   = 2;    // CR+LF

// Encoding
    const int   _SYSTEM_                = -1;   // System
    const int   _UTF8_                  = 0;    // UTF-8
    const int   _APPLEROMAN_            = 1;    // Apple Roman
    const int   _LATIN1_                = 2;    // Latin-1 = ISO 8859-1

// Extension
    const int   _TXT_                   = 0;
    const int   _CSV_                   = 1;

// Filenames
    const QString _COREDESCRIPTION_FILENAME_     = "CoreDescription.txt";
    const QString _CORELEGEND_FILENAME_          = "CoreLegend.txt";
    const QString _CORELOGGERPROTOKOLL_FILENAME_ = "CoreLoggerProtokoll.txt";
    const QString _CORESECTIONTABLE_FILENAME_    = "CoreSectionTable.txt";
    const QString _BENTHOSMAP_FILENAME_          = "BenthosMap.txt";
    const QString _BENTHOSTRACK_FILENAME_        = "BenthosTrack.txt";
    const QString _BENTHOSBATH_FILENAME_         = "BenthosBath.txt";
    const QString _INFO_FILENAME_                = "Info.txt";

#endif
