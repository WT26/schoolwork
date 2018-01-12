#include "parkinghall.hh"
#include "math.h"

ParkingHall::ParkingHall() :
    id_(""),
    name_(""),
    geoCoordinates_(0.0, 0.0),
    coordinates_(0, 0),
    isTaken_(false),
    occupiedSpaces_(0),
    vacantSpaces_(0)
{
}


void ParkingHall::setId(QString id) {
    id_ = id;
}


void ParkingHall::setName(QString name) {
    name_ = name;
}


void ParkingHall::setGeoCoordinates(float x, float y) {
    geoCoordinates_.first = x;
    geoCoordinates_.second = y;
    convertCoordinates();
}


void ParkingHall::setOccupied(int amount) {
    occupiedSpaces_ = amount;
}


void ParkingHall::setVacant(int amount) {
    vacantSpaces_ = amount;
}

void ParkingHall::setTaken(bool isTaken){
    isTaken_ = isTaken;
}


QString ParkingHall::getName() {
    return name_;
}


QString ParkingHall::getId() {
    return id_;
}


std::pair<float, float> ParkingHall::getGeoCoordinates() {
    return geoCoordinates_;
}


std::pair<int, int> ParkingHall::getCoordinates() {
    return coordinates_;
}


int ParkingHall::getOccupied() {
    return occupiedSpaces_;
}


int ParkingHall::getVacant() {
    return vacantSpaces_;
}


bool ParkingHall::isTaken() {
    return isTaken_;
}


void ParkingHall::convertCoordinates() {
    // Luodaan näkyvmälle yhteensopivat koordinaatit x ja y.
    // Eli karttanäkymän vasen yläkulma on koordinaatit: 61.5085  23.7427
    // ja oikea alakulma: 61.485  23.811

    // Luodaan funktiot jotka muokkaavat koordinaateista geo_koordinaatteja:
    // coords_to_geo_y(coord) = (coord * -0.00004272727) + 61.5085
    // coords_to_geo_x(coord) = coord * 0.000085375 + 23.7427

    // Ja geo_koordinaateista koordinaatteja
    // geo_to_coords_y(geo) = (1.43956×10^6)-(23404.3*geo)
    // geo_to_coords_x(geo) = (800/683)*(10000*geo-237427)

    coordinates_.first = geoToCoordsX(geoCoordinates_.first);
    coordinates_.second = geoToCoordsY(geoCoordinates_.second);
}


int ParkingHall::geoToCoordsY(float geoY) {
    return (int)(1.43956*pow(10,6))-(23404.3*geoY);
}


int ParkingHall::geoToCoordsX(float geoX) {
    return (int)(800/683)*(10000*geoX-237427);
}


float ParkingHall::coordsToGeoY(int coordY) {
    return (float)(coordY * -0.00004272727) + 61.5085;
}


float ParkingHall::coordsToGeoX(int coordX) {
    return (float)(coordX * 0.000085375 + 23.7427);
}

