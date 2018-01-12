#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include "weapon.h"
#include "implant.h"
#include "armor.h"
#include "parkinghall.hh"
#include "memory"
#include "enemy.h"
#include "playablecharacter.h"

#include <QTime>
#include <QFile>
#include <fstream>
#include <QVector>

// Pelin tilaa ja siihen liittyvää dataa ylläpitävä luokka.
// Luokka voi myös ladata ja tallentaa pelin tilan
// tallennustiedostoihin.
class GameProgress
{

public:
    GameProgress();
    ~GameProgress(){}

    // Alustaa tavarat ja vastustajat ini-tiedostoista.
    void initEntitys();

    // Metodeilla voi ladata ja tallentaa pelin tilan.
    // Saveslot 1-3.
    void loadGame(int saveSlot);
    void saveGame(int saveSlot);

    // Palauttaa listan characterien tiloista(name, maxHp, currenHp,
    // maxAp, currentAp, equippedWeapon, equippedArmor,
    // equippedImplant) Käytetään näkymien alustuksessa.
    QList<QList<QString>> getCharactersProgress();

    // Palauttaa listan shared_pointtereista itse PlayableCharacter olioihin.
    QList<std::shared_ptr<PlayableCharacter>> getListOfCharacters();

    // Rahan määrän muokkaamiseen ja hakemiseen käytettävät metodit.
    int getMoney();
    void addMoney(int moneySum);
    void useMoney(int cost);

    // Päivittää gameCompletition_ arvon.
    void updateCompletition();

    // Nämä metodit palauttavat pelin tilaan liittyviä muuttujia.
    int getCompletion();
    int getTotalPlaytime();
    int getEnemiesKilled();
    QList<QString> getResearchedItems();
    QList<QString> getControlledHalls();

    // Metodi tallentaa tiedon uudesta vallatusta parkkihallista.
    void takeHall(QString hallId);

    // Parsi alustustiedosto. Aloitustiedosto sisältää rivejä, joiden
    // kentät erotettu pilkulla.
    std::vector<QStringList> parseIniFile(QString iniFile);

    // Metodi päivittää researchedItems_ uudella tavaralla,
    // ja vähentää rahoista sen hinnan verran.
    void newItemResearched(QString itemName, int cost);

    // Varustaa valitun hahmon tavaralla.
    void equipItem(int characterIndex, QString itemName);

    // Päivittää charactersProgress_:n viimeisimmillä tiedoilla
    // hahmojen tiloista.
    void updateCharactersProgress();

    // Metodit palauttavat vektorit kaikista pelissä olevista
    // erilaisista tavaroista ja vastustajista.
    QVector<std::shared_ptr<Weapon>> getAllWeapons();
    QVector<std::shared_ptr<Armor>> getAllArmors();
    QVector<std::shared_ptr<Implant>> getAllImplants();
    QVector<std::shared_ptr<Enemy>> getAllEnemies();

    void debugPrintCurrentProgress();

private:
    int money_;
    int enemiesKilled_;
    int gameCompletition_;

    // Listat kaikista pelissä olevista tavaroista ja vastustajista.
    QVector<std::shared_ptr<Weapon>> allWeapons_;
    QVector<std::shared_ptr<Armor>> allArmors_;
    QVector<std::shared_ptr<Implant>> allImplants_;
    QVector<std::shared_ptr<Enemy>> allEnemies_;

    // Lista pelihahmojen tallennustiedoista:
    // name, maxHp, currenHp, maxAp, currentAp, equippedGun, equippedMod, equippedTool
    QList<QList<QString>> charactersProgress_;

    // Lista pelihahmoista, joita moottori yms hyödyntää.
    QList<std::shared_ptr<PlayableCharacter>> listOfCharacters_;

    // Lista tutkittujen tavaroiden nimistä.
    QList<QString> researchedItems_;

    // Lista vallattujen parkkihallien Id:eistä.
    QList<QString> parkinghallsControlled_;

    // Peliajan laskuun käytettävät muuttujat.
    QTime currentSessionTime_;
    int elapsedBeforeCurrentSession_;

    // Alustaa tavarat ja vastustajat ini-tiedostoista.
    void initWeapons();
    void initArmors();
    void initImplants();
    void initEnemies();

    // Generoi tallennustiedoston pelintilasta.
    QString generateSaveFile();

    // Lataa hahmon tallennustietojen perusteella.
    void loadCharactersProgress();

    // Alustaa hahmon uuteen peliin.
    void newGameCharactersProgress();

    // Etsii tavaran nimen perusteella pointterin tavara-olioon.
    std::shared_ptr<Weapon> findWeapon(QString weaponName);
    std::shared_ptr<Armor> findArmor(QString armorName);
    std::shared_ptr<Implant> findImplant(QString implantName);

    // Palauttaa tiedon kauvanko peli on ollut käynnissä.
    int elapsedMinutes();

};

#endif // GAMEPROGRESS_H
