#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "parkinghall.hh"

#include <memory>
#include <QString>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QNetworkReply>


// Luokka parsii Xml tiedoston. Xml tiedosto haetaan http osoitteesta.
class XmlParser: public QObject
{
Q_OBJECT
public:
    XmlParser(bool useHttp);
    ~XmlParser(){}

    // Palauttaa listan parkkihalleista.
    QList<ParkingHall> createListOfParkingHalls();

    // Päivittää yhden parkkihallin tiedot.
    void updateParkingHall(ParkingHall &p);

    // Päivittää kaikkien parkkihallien tiedot.
    QList<ParkingHall> updateAllParkingHalls();

private:
    QNetworkReply *latestReply_;
    QXmlStreamReader reader_;
    bool useHttp_;
    QString filename_;
    // Metodi tarkistaa filun oikeellisuuden.
    void getFileDataReader(QString filename);

    // Metodi hakee filun verkosta.
    void getHTTPDataReader();

    // Lukee parkkihallin id:n, nimen ja koordinaatit ja sijoittaa ne ParkingHall p.
    void readFacilityInfo(QXmlStreamReader& reader, ParkingHall &p);

    // Kuten ylempi, mutta lukee ja sijoittaa occupied ja vacant spots lukumäärät.
    void readFacilityStatus(QXmlStreamReader& reader, ParkingHall &p);

    // Asettaa readerin kohtaan josta alkaa vaihtuva data.
    void setReaderToDynamicData(QXmlStreamReader& reader);

    // Asettaa readerin tietyn id:n kohdalle.
    void setReaderToId(QXmlStreamReader& reader, QString id);


};

#endif // XMLPARSER_H
