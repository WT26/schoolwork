#ifndef TAMPEREPARKING_H
#define TAMPEREPARKING_H

#include "tampereparkinginterface.hh"
#include "parkinghall.hh"
#include "xmlparser.h"

#include <QFile>
#include <QXmlStreamReader>

namespace Parking {

// Luokka joka toteuttaa TampereParkingInterfaciä. Luokka toimii
// rajapintana TampereParkingApi:lle. Se käyttää Xml parsijaa
// tiedon parsimiseen ja luo ja pitää yllä tietoa ja tilaa
// nykyisistä parkkihalleista.
class TampereParking : public TampereParkingInterface
{
public:
    // Rakentaja.
    TampereParking();
    ~TampereParking(){}

    // Alustaa parkkihallit.
    void initGameData();

    // Palauttaa listan parkkihalleista.
    QList<std::shared_ptr<ParkingHall>> getParkingHalls();

    // Päivittää tietyn parkkihallin.
    void updateParkingHall(ParkingHall &p);

    // Päivittää kaikki parkkihallit.
    void updateAllParkingHalls();

    void debugPrintData();
    void debugGatherUselessParks();

private:
    std::shared_ptr<XmlParser> parsija_;

    QList<std::shared_ptr<ParkingHall>> parkingHalls_;

    QList<std::shared_ptr<ParkingHall>> createPointersToHalls(QList<ParkingHall> halls);
    QList<std::shared_ptr<ParkingHall>> useUsefulParkingHalls(QList<ParkingHall> halls);

};

}
#endif // TAMPEREPARKING_H
