#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <QString>
#include <QDateTime>

class FlightData
{
public:
    QTime   Time;
    double  Latitude;
    double  Longitude;
    int     Course;
    int     kts;
    int     mph;
    int     AltitudeFeet;
    QString ReportingFacility;

    FlightData(const QString& time, double latitude, double longitude, int course,
               int kts, int mph, int altitudeFeet, const QString& facility)
        : Time(QTime::fromString(time, "hh:mm:ss AP")),
          Latitude(latitude),
          Longitude(longitude),
          Course(course),
          kts(kts),
          mph(mph),
          AltitudeFeet(altitudeFeet),
          ReportingFacility(facility)
    {}
};

#endif // FLIGHTDATA_H
