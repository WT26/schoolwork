#ifndef PARKINGHALL_H
#define PARKINGHALL_H

#include <QString>

// Parkkihalli luokka, jossa tiedot parkkihallista.
// Tiedot saadaan Tampere parking Api:sta.
class ParkingHall
{
public:
    ParkingHall();
    ~ParkingHall(){}

    // Metodit joilla astetaan tietoja parkkihallista.
    void setId(QString id);
    void setName(QString name);
    void setGeoCoordinates(float x, float y);
    void setAvailability(bool availability);
    void setOccupied(int amount);
    void setVacant(int amount);
    void setTaken(bool isTaken);

    // Metodit joilla palautetaan eri arvoja parkkihallista.
    QString getName();
    QString getId();
    std::pair<float, float> getGeoCoordinates();
    std::pair<int, int> getCoordinates();
    int getOccupied();
    int getVacant();

    // Palauttaa totuusarvon siitä että onko parkkihalli jo vallattu.
    bool isTaken();

private:
    QString id_;
    QString name_;

    // GeoCoordinates_ ovat Apista saadut longitude ja latitude,
    // ja coordinates_ on samat koordinaatit muutettuna näkymän x, y:ksi.
    std::pair<float, float> geoCoordinates_;
    std::pair<int, int> coordinates_;
    bool isTaken_;
    int occupiedSpaces_;
    int vacantSpaces_;

    // Metodi vaihtaa GeoCoordinaatit Coordinaateiksi.
    void convertCoordinates();

    // Metodeilla joilla vaihtaminen lasketaan.
    int geoToCoordsY(float geoY);
    int geoToCoordsX(float geoX);
    float coordsToGeoY(int coordY);
    float coordsToGeoX(int coordX);



};

#endif // PARKINGHALL_H
