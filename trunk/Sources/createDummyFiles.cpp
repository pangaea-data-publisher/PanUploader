/* uploadImages.cpp           */
/* 2012-12-30                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-01-10

int MainWindow::createDummyFiles( const QString &s_WorkingDirectory )
{
    QString s_CoreDescriptionFilename		= s_WorkingDirectory + "/" + _COREDESCRIPTION_FILENAME_;
    QString s_CoreLegendFilename			= s_WorkingDirectory + "/" + _CORELEGEND_FILENAME_;
    QString s_CoreLoggerProtokollFilename	= s_WorkingDirectory + "/" + _CORELOGGERPROTOKOLL_FILENAME_;
    QString s_CoreSectionTableFilename      = s_WorkingDirectory + "/" + _CORESECTIONTABLE_FILENAME_;
    QString s_BenthosMapFilename			= s_WorkingDirectory + "/" + _BENTHOSMAP_FILENAME_;
    QString s_BenthosTrackFilename			= s_WorkingDirectory + "/" + _BENTHOSTRACK_FILENAME_;
    QString s_BenthosBathFilename			= s_WorkingDirectory + "/" + _BENTHOSBATH_FILENAME_;
    QString s_InfoFilename					= s_WorkingDirectory + "/" + _INFO_FILENAME_;

//--------------------------------------------------------------------------------------------------------------------------------

    QFile fout( s_CoreLoggerProtokollFilename );
    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tCoreLoggerProtokoll( &fout );

    tCoreLoggerProtokoll << "This is not the corelogger protokoll. The protokoll can be found in the core directory on hs.pangaea.de." << endl;

    fout.close();

//--------------------------------------------------------------------------------------------------------------------------------

    fout.setFileName( s_CoreDescriptionFilename );
    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tDescription( &fout );

    tDescription << "This is not the core description. The core description can be found in the core directory on hs.pangaea.de." << endl;

    fout.close();

//--------------------------------------------------------------------------------------------------------------------------------

    fout.setFileName( s_CoreLegendFilename );
    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tLegend( &fout );

    tLegend << "This is not the description legend. The legend can be found in the core directory on hs.pangaea.de." << endl;

    fout.close();

//--------------------------------------------------------------------------------------------------------------------------------

    fout.setFileName( s_CoreSectionTableFilename );
    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tCoreSectionTable( &fout );

    tCoreSectionTable << "This is not the core section table. The core section table can be found in the core directory on hs.pangaea.de." << endl;

    fout.close();

//--------------------------------------------------------------------------------------------------------------------------------

    fout.setFileName( s_BenthosBathFilename );
    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tBenthosBath( &fout );

    tBenthosBath << "This is not the map. The map can be found in the benthos directory on hs.pangaea.de." << endl;

    fout.close();

//--------------------------------------------------------------------------------------------------------------------------------

    fout.setFileName( s_BenthosMapFilename );
    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tBenthosMap( &fout );

    tBenthosMap << "This is not the map. The map can be found in the benthos directory on hs.pangaea.de." << endl;

    fout.close();

//--------------------------------------------------------------------------------------------------------------------------------

    fout.setFileName( s_BenthosTrackFilename );
    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tBenthosTrack( &fout );

    tBenthosTrack << "This is not the track at the station. The track file can be found in the benthos directory on hs.pangaea.de." << endl;

    fout.close();

//--------------------------------------------------------------------------------------------------------------------------------

    fout.setFileName( s_InfoFilename );
    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tInfo( &fout );

    tInfo << "This is not the information file. The info file can be found in the directory on hs.pangaea.de." << endl;

    fout.close();

//--------------------------------------------------------------------------------------------------------------------------------

    return( _NOERROR_ );
}
