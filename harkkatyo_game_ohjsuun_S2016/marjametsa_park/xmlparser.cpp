#include "xmlparser.h"

#include <random>
#include <time.h>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>


XmlParser::XmlParser(bool useHttp):
    latestReply_(nullptr),
    useHttp_(useHttp),
    filename_("")
{
    if (useHttp_){
        getHTTPDataReader();
    }
    else {
        getFileDataReader(":/temp_parkingdata.xml");
    }
    srand(time(NULL));
}


QList<ParkingHall> XmlParser::createListOfParkingHalls() {
    QList<ParkingHall> listOfHalls;

    if (useHttp_) {
        reader_.setDevice(latestReply_);
    }
    else {
        QFile file(filename_);
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug() << "Tiedoston luku epäonnistui." << file.errorString();
            exit(0);
        }
        reader_.setDevice(&file);
    }

    // Tässä luupissa käydään läpi ParkingFacilityt ja kerätään näistä tiedot
    // id:stä, nimestä sekä koordinaateista. Näiden avulla luodaan ParkingHall
    // ja sijoitetaan se list_of_halls.
    while (!reader_.atEnd()) {
        ParkingHall p;
        if(reader_.name() == "parkingFacility"){
            readFacilityInfo(reader_, p);
            listOfHalls.append(p);
        }
        else if(reader_.name() == "parkingFacilityTableStatusPublication") {
            break;
        }
        reader_.readNextStartElement();
    }

    // Tässä käydään läpi "dynaaminen" data ja kerätään tieto
    // parkkihallien käyttöasteesta ja sijoitetaan se ParkingHall
    // arvoihin vacant ja occupied.
    int counter = 0;
    while (!reader_.atEnd()){
        if (reader_.name() == "parkingFacilityStatus") {
            if (listOfHalls.length() <= counter){
                break;
            }
            else {
                readFacilityStatus(reader_, listOfHalls[counter]);
                counter++;
            }
        }
        reader_.readNextStartElement();
    }

    return listOfHalls;
}


void XmlParser::updateParkingHall(ParkingHall &p) {
    if (useHttp_) {
        reader_.setDevice(latestReply_);
    }
    else {
        QFile file(filename_);
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug() << "Tiedoston luku epäonnistui." << file.errorString();
            exit(0);
        }
        reader_.setDevice(&file);
    }

    // Ohjataan reader muuttuvan datan luo.
    setReaderToDynamicData(reader_);

    // Etsitään oikea ParkingHall Id:n avulla.
    QString id = p.getId();
    setReaderToId(reader_, id);

    // Haetaan nyt halutun hallin käyttöaste.
    readFacilityStatus(reader_, p);

}


QList<ParkingHall> XmlParser::updateAllParkingHalls() {
    getHTTPDataReader();
    return createListOfParkingHalls();
}

// Metodi tarkistaa Xml tiedoston oikeellisuuden ja tallentaa
// filename_:n.
void XmlParser::getFileDataReader(QString filename) {
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Tiedoston luku epäonnistui." << file.errorString();
        exit(0);
    }
    reader_.setDevice(&file);
    if (reader_.readNextStartElement()) {
        QString s = reader_.readElementText();
        if (reader_.name() != "exchange"){
            reader_.raiseError(QObject::tr("Incorrect file"));
        }
        else {
            filename_ = filename;
        }
    }
}


// Hakee tiedoston nettisivulta.
void XmlParser::getHTTPDataReader() {

    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
    QEventLoop eventLoop;
    QObject::connect(mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req(QUrl(QString("http://parkingdata.finnpark.fi:8080/Datex2/ParkingFacilities") ) );
    QString encoded = QString("tut:E2ksnh").toLocal8Bit().toBase64();
    encoded = "Basic " + encoded;
    req.setRawHeader("Authorization", encoded.toLocal8Bit());
    latestReply_ = mgr->get(req);
    int code = eventLoop.exec();

    reader_.setDevice(latestReply_);
}


// Metodi lukee yhden Parkkihallin id:n nimen ja koordinaatit ja sijoittaa ne
// ParkingHall:iin.
void XmlParser::readFacilityInfo(QXmlStreamReader &reader, ParkingHall &p) {
    float x;
    float y;
    QString id;
    QString name;
    if (reader.attributes().hasAttribute("id")){
        id = reader.attributes().value("id").toString();
    }
    reader.readNextStartElement();
    while(reader.name() != "parkingFacility"){
        if (reader.name() == "parkingFacilityName") {
            name = reader.readElementText();
        }
        else if (reader.name() == "latitude") {
            y = reader.readElementText().toFloat();
        }
        else if (reader.name() == "longitude") {
            x = reader.readElementText().toFloat();
        }
        reader.readNextStartElement();
    }
    p.setId(id);
    p.setName(name);
    p.setGeoCoordinates(x, y);
}


// Metodi lukee parkkihallin occupied ja vacant arvot ja sijoittaa ne parametrina
// saatuun ParkingHall:iin.
void XmlParser::readFacilityStatus(QXmlStreamReader &reader, ParkingHall &p) {
    int occupied = -1;
    int vacant = -1;
    reader.readNextStartElement();

    // Karin maaginen algoritmi joka osaa parsia huonosti muotoillun parkingFacilityStatus
    // elementin näppärästi.
    while (!reader.atEnd() && (!reader.isEndElement() || reader.name() != "parkingFacilityStatus")){
        if (reader.name() == "totalNumberOfOccupiedParkingSpaces") {
            occupied = reader.readElementText().toInt();
        }
        else if (reader.name() == "totalNumberOfVacantParkingSpaces"){
            vacant = reader.readElementText().toInt();
        }
        else if(reader.name() == "parkingFacilityStatus"){
            reader.readNext();
            while (reader.name() != "parkingFacilityStatus") {
                reader.readNext();
            }
        }
        reader.readNext();
    }
    if((occupied == -1) && (vacant == -1)){
        occupied = rand() % 20;
        vacant = rand() % 20;
    }
    p.setOccupied(occupied);
    p.setVacant(vacant);
}


void XmlParser::setReaderToDynamicData(QXmlStreamReader &reader) {
    while (!reader_.atEnd()) {
        if(reader_.name() == "parkingFacilityTableStatusPublication") {
            break;
        }
        reader_.readNextStartElement();
    }
}


void XmlParser::setReaderToId(QXmlStreamReader &reader, QString id){
    QString hall_id;

    while (!reader.atEnd()) {
        if(reader.name() == "parkingFacilityReference") {
            if (reader.attributes().hasAttribute("id")){
                hall_id = reader.attributes().value("id").toString();

                if (hall_id == id) {
                    // Löytyi.
                    break;
                }
            }
        }
        reader.readNextStartElement();
    }
}
