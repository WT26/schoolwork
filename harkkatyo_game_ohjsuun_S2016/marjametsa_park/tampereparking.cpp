#include "tampereparking.hh"

#include <math.h>
#include <QDebug>

namespace Parking {

QList<QString> USEFUL_HALLS ({"TRE.S.17475", "TRE.S.17473", "TRE.S.17477", "FNPK.11", "FNPK.12", "TRE.S.113350",
                              "TRE.S.113351", "FNPK.16", "FNPK.26", "FNPK.25", "TRE.S.113385", "TRE.S.108059",
                              "TRE.S.18239", "TRE.S.18237", "TRE.S.18300", "TRE.S.18304", "FNPK.8", "FNPK.9",
                              "FNPK.3", "TRE.S.100519", "TRE.S.11115248", "TRE.S.18306", "TRE.S.20512", "TRE.S.15652",
                              "TRE.S.18125", "TRE.S.113402", "TRE.S.18296", "TRE.S.20986", "TRE.S.18146", "TRE.S.20979",
                              "TRE.S.113395", "TRE.S.103097", "TRE.S.109334", "TRE.S.18271"});


TampereParking::TampereParking():
    parsija_(std::make_shared<XmlParser>(new XmlParser(false))),
    parkingHalls_()
{
}

// Parsii xml tiedostosta pelin alustusdatan.
void TampereParking::initGameData() {
    QList<ParkingHall> listOfHalls = parsija_->createListOfParkingHalls();
    QList<std::shared_ptr<ParkingHall>> shortList;
    parkingHalls_ = useUsefulParkingHalls(listOfHalls);
    //shortList.append(parkingHalls_[0]);
    //shortList.append(parkingHalls_[1]);
    //shortList.append(parkingHalls_[2]);
    //parkingHalls_ = shortList;
}

QList<std::shared_ptr<ParkingHall> > TampereParking::getParkingHalls() {
    return parkingHalls_;
}

// Päivittää parametrina saadun parkkihallin tiedot(occupied ja vacant arvot).
void TampereParking::updateParkingHall(ParkingHall &p) {
    parsija_.get()->updateParkingHall(p);
}

// Päivittää kaikkien parkkihallien tiedot.
void TampereParking::updateAllParkingHalls() {
    parkingHalls_ = useUsefulParkingHalls(parsija_->updateAllParkingHalls());
    //QList<std::shared_ptr<ParkingHall>> shortList;
    //shortList.append(parkingHalls_[0]);
    //shortList.append(parkingHalls_[1]);
    //shortList.append(parkingHalls_[2]);
    //parkingHalls_ = shortList;
}

// Tulostaa kaikkien hallien tiedot. Käytössä debuggausta varten.
void TampereParking::debugPrintData() {
    for (int i = 0; i != parkingHalls_.length(); i++){
        qDebug()<< "Hall number: " + QString::number(i + 1);
        qDebug()<< "NIMI: " + parkingHalls_[i]->getName() + "   ID: " + parkingHalls_[i]->getId();

        qDebug()<< "coords: x = " + QString::number(parkingHalls_[i]->getCoordinates().first) +
                   "  y = " + QString::number(parkingHalls_[i]->getCoordinates().second);

        qDebug()<< "Occupation: " + QString::number(parkingHalls_[i]->getOccupied()) +
                   "  Vacant spots: " + QString::number(parkingHalls_[i]->getVacant());

        qDebug()<< "\n";
    }
}

// Kerää ja tulostaa ne parkkihallit, joista ei ole tietoa niiden vapaista/käytetyistä
// paikoista tai jos niiden koordinaatit ovat (0,0)-(800,600) rajojen ulkopuolella.
void TampereParking::debugGatherUselessParks() {
    QList<QString> useless;
    QList<QString> useful;
    QList<std::pair<int,int>> alreadyMappedCoords;

    for (int i = 0; i != parkingHalls_.length(); i++){
        bool add = true;
        if(parkingHalls_[i]->getOccupied() == -1 || parkingHalls_[i]->getVacant() == -1
                || parkingHalls_[i]->getCoordinates().first < 50 || parkingHalls_[i]->getCoordinates().first > 750
                || parkingHalls_[i]->getCoordinates().second < 50 || parkingHalls_[i]->getCoordinates().second > 650) {
            useless.append(parkingHalls_[i]->getId());
            add = false;
        }

        // Tarkistetaan ettei parkkihallit ole täysin toisten päällä.
        if (add){
            for(auto coords : alreadyMappedCoords){
                if((abs(coords.first - parkingHalls_[i]->getCoordinates().first) < 35) && ((abs(coords.second - parkingHalls_[i]->getCoordinates().second))< 35)){
                    useless.append(parkingHalls_[i]->getId());
                    add = false;
                }
            }
        }
        if (add) {
            alreadyMappedCoords.append(parkingHalls_[i]->getCoordinates());
            useful.append(parkingHalls_[i]->getId());
        }
    }
    qDebug()<<useless;
    //qDebug()<<useful;
}


// Luo shared_ptr:t Qlistassa olevista halleista ja palauttaa listan QList<Shared_ptr<ParkingHall>>.
QList<std::shared_ptr<ParkingHall> > TampereParking::createPointersToHalls(QList<ParkingHall> halls) {
    QList<std::shared_ptr<ParkingHall>> list_of_pointers;
    for (int i = 0; i != halls.length();i++){
        list_of_pointers.push_back(std::make_shared<ParkingHall>(halls[i]));
    }
    return list_of_pointers;
}


// Metodi poistaa turhat parkkihallit joita ei käytetä pelissä.
QList<std::shared_ptr<ParkingHall> > TampereParking::useUsefulParkingHalls(QList<ParkingHall> halls) {
    QList<ParkingHall> parkingHalls;

    for (int i = 0; i != halls.length(); i++){
        for (auto hall : USEFUL_HALLS){
            if(halls[i].getId() == hall) {
                parkingHalls.append(halls[i]);
            }
        }
    }
    return createPointersToHalls(parkingHalls);
}


}

