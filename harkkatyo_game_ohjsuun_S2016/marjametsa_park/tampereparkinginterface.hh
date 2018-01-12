#ifndef TAMPEREPARKINGINTERFACE_H
#define TAMPEREPARKINGINTERFACE_H

#include "parkinghall.hh"

#include <QList>
#include <memory>

namespace Parking {



class TampereParkingInterface
{
public:
    // Tyhjä purkaja.
    virtual ~TampereParkingInterface(){}

    // Esiehto: Ei ole.
    // Jälkiehto: Ei ole.
    virtual void initGameData() = 0;

    // Esiehto: initGameData() suoritettu.
    // Jälkiehto: palautetaan lista parkkihalleista.
    virtual QList<std::shared_ptr<ParkingHall>> getParkingHalls() = 0;


    // Esiehto: Parametrinä saatu ParkingHall on olemassa.
    // Jälkiehto: Parametrinä saadun ParkingHall:n tiedot päivitetty.
    virtual void updateParkingHall(ParkingHall &p) = 0;

    // Esiehto: Ei ole.
    // Jälkiehto: Palauttaa listan kaikista ParkingHall:eista.
    virtual void updateAllParkingHalls() = 0;
};

}
#endif // TAMPEREPARKINGINTERFACE_H
