#include "gameprogress.h"

#include <string>
#include <fstream>
#include <ostream>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QDir>

GameProgress::GameProgress():
    money_(0),
    enemiesKilled_(0),
    gameCompletition_(0),
    allWeapons_(),
    allArmors_(),
    allImplants_(),
    allEnemies_(),
    charactersProgress_(),
    listOfCharacters_(),
    researchedItems_(),
    parkinghallsControlled_(),
    currentSessionTime_(),
    elapsedBeforeCurrentSession_(0)
{
}

void GameProgress::initEntitys() {
    initWeapons();
    initArmors();
    initImplants();
    initEnemies();
}

void GameProgress::loadGame(int saveSlot) {

    // Avataan tiedosto parametrinä saadun saveSlotin perusteella.
    QString saveFile = "save_slot_" + QString::number(saveSlot) + ".txt";
    QList<QString> objects;
    QFile inputFile(saveFile);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       while (!in.atEnd())
       {
          QString line = in.readLine();
          objects = line.split('/');
       }
       inputFile.close();
    }

    if(objects.empty()){
        qDebug()<<"Tallennus tiedosto tyhjä, aloitetaan uusi peli.";
        money_ = 500;
        enemiesKilled_ = 0;
        researchedItems_.push_back("PISTOL");

        // Alustetaan uudet characterit

        newGameCharactersProgress();
        updateCharactersProgress();

        parkinghallsControlled_;
        elapsedBeforeCurrentSession_ = 0;
        currentSessionTime_.start();
        gameCompletition_ = 0;
    }
    else {
        qDebug()<<"Tallennustiedosto löytyi. Ladataan tiedot.";
        money_ = objects[0].toInt();
        enemiesKilled_ = objects[1].toInt();

        QList<QString> charactersInfo = objects[2].split('#');
        for (auto info : charactersInfo){
            charactersProgress_.push_back(info.split(','));
        }

        researchedItems_ = objects[3].split(',');
        parkinghallsControlled_ = objects[4].split(',');
        elapsedBeforeCurrentSession_ = objects[5].toInt();
        currentSessionTime_.start();
        gameCompletition_ = objects[6].toInt();

        loadCharactersProgress();
        updateCompletition();
    }
}


void GameProgress::saveGame(int saveSlot) {
    updateCharactersProgress();
    updateCompletition();
    QString saveData = generateSaveFile();
    QString saveFile = "save_slot_" + QString::number(saveSlot) + ".txt";

    QFile outputFile(saveFile);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!outputFile.isOpen()) {
        qDebug()<<"Tiedoston luominen/avaaminen epäonnistui.";
    }
    QTextStream outStream(&outputFile);
    outStream << saveData;
}


QList<QList<QString> > GameProgress::getCharactersProgress() {
    return charactersProgress_;
}


QList<std::shared_ptr<PlayableCharacter> > GameProgress::getListOfCharacters() {
    return listOfCharacters_;
}


int GameProgress::getMoney() {
    return money_;
}


void GameProgress::addMoney(int moneySum){
    money_ += moneySum;
}


void GameProgress::useMoney(int cost) {
    money_ -= cost;
}


void GameProgress::updateCompletition() {
    double completed = researchedItems_.length() + parkinghallsControlled_.length();
    double all = allWeapons_.length() + allArmors_.length() + allImplants_.length();
    all += 34; // Parkkihallien määrä.
    gameCompletition_ = ((completed / all) * 100);
}


int GameProgress::getCompletion() {
    return gameCompletition_;
}


int GameProgress::getTotalPlaytime() {
    return elapsedMinutes();
}


int GameProgress::getEnemiesKilled() {
    return enemiesKilled_;
}


QList<QString> GameProgress::getResearchedItems() {
    return researchedItems_;
}


QList<QString> GameProgress::getControlledHalls() {
    return parkinghallsControlled_;
}


void GameProgress::takeHall(QString hallId){
    parkinghallsControlled_.append(hallId);

}


std::vector<QStringList> GameProgress::parseIniFile(QString ini_file) {
    std::vector<QStringList> objects;

    QFile inputFile(ini_file);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList object;
          object = line.split(',');
          objects.push_back(object);
       }
       inputFile.close();
    }
    return objects;
}


void GameProgress::newItemResearched(QString name, int cost) {
    researchedItems_.append(name);

    money_ -= cost;
}


void GameProgress::equipItem(int characterIndex, QString itemName) {
    if(!(findWeapon(itemName).get()->getName() == "NONE")) {
        listOfCharacters_[characterIndex].get()->equipWeapon(findWeapon(itemName));
        qDebug()<<"Weapon equipped: " + itemName;
    }
    else if(!(findArmor(itemName).get()->getName() == "NONE")){
        listOfCharacters_[characterIndex].get()->equipArmor(findArmor(itemName));
        qDebug()<<"Armor equipped: " + itemName;
    }
    else if(!(findImplant(itemName).get()->getName() == "NONE")){
        listOfCharacters_[characterIndex].get()->equipImplant(findImplant(itemName));
    }
}


// Päivittää characterien:
// name, maxHp, currenHp, maxAp, currentAp, equippedWeapon, equippedArmor, equippedImplant
void GameProgress::updateCharactersProgress() {
    QList<QList<QString>>allCharactersProgress;
    for(auto ptrToChar : listOfCharacters_){
        QList<QString> character;
        character.append(ptrToChar.get()->getName());

        character.append(QString::number(ptrToChar.get()->getMaxHP()));
        character.append(QString::number(ptrToChar.get()->getCurrentHP()));
        character.append(QString::number(ptrToChar.get()->getMaxActionPoints()));
        character.append(QString::number(ptrToChar.get()->getCurrentActionPoints()));

        character.append(ptrToChar.get()->getEquippedWeapon()->getName());
        character.append(ptrToChar.get()->getEquippedArmor()->getName());
        character.append(ptrToChar.get()->getEquippedImplant()->getName());

        allCharactersProgress.append(character);
    }
    charactersProgress_ = allCharactersProgress;
}


QVector<std::shared_ptr<Weapon> > GameProgress::getAllWeapons() {
    return allWeapons_;
}


QVector<std::shared_ptr<Armor> > GameProgress::getAllArmors() {
    return allArmors_;
}


QVector<std::shared_ptr<Implant> > GameProgress::getAllImplants() {
    return allImplants_;
}


QVector<std::shared_ptr<Enemy> > GameProgress::getAllEnemies() {
    return allEnemies_;
}


void GameProgress::debugPrintCurrentProgress() {
    qDebug()<<"\nGAME PROGRESS\n";
    qDebug()<<"Money: " + QString::number(money_);
    qDebug()<<"Enemies killed: " + QString::number(enemiesKilled_);
    qDebug()<<"Game Completition: " + QString::number(gameCompletition_);
    qDebug()<<"Gameplay time: " + QString::number(elapsedMinutes()) + "min";

    for (QList<QString> character: charactersProgress_){
        qDebug()<<"\n";
        int hp_min = character[2].toInt();
        int hp_max = character[1].toInt();
        int ap_min = character[4].toInt();
        int ap_max = character[3].toInt();
        qDebug()<<character[0] + "     Hp: " + QString::number(hp_min) + "/" + QString::number(hp_max);
        qDebug()<<"Ap: " + QString::number(ap_min) + "/" + QString::number(ap_max);
        qDebug()<<"Equipped Weapon: " + character[5];
        qDebug()<<"Equipped Armor: " + character[6];
        qDebug()<<"Equipped Implant: " + character[7];
    }
    qDebug()<<"\n";

    QString items;
    for (auto item : researchedItems_){
        items += item + ", ";
    }
    qDebug()<<"Researched Items: " + items;

    QString halls;
    for (auto hall : parkinghallsControlled_){
        halls += hall + ", ";
    }
    qDebug()<<"Parkinghalls Controlled: " + halls;
}


void GameProgress::initWeapons() {
    std::vector<QStringList> weaponIni = parseIniFile(":/ini_files/weapons.ini");
    for (std::vector<QStringList>::iterator it = weaponIni.begin();
         it != weaponIni.end(); ++it) {
        QStringList singleWeapon = *it;

        // Tässä voisi tarkistaa että lista on oikean pituinen
        QString name = singleWeapon[0];
        int price = singleWeapon[1].toInt();

        QString weaponTypeQstr = singleWeapon[2];
        Weapon::WeaponType weaponType;
        if (weaponTypeQstr == "RANGED"){
            weaponType = Weapon::WeaponType::RANGED;
        }

        int minDamage = singleWeapon[3].toInt();
        int maxDamage = singleWeapon[4].toInt();
        int minRange = singleWeapon[5].toInt();
        int maxRange = singleWeapon[6].toInt();
        int shootAp = singleWeapon[7].toInt();
        int reloadAp = singleWeapon[8].toInt();
        int spread = singleWeapon[9].toInt();
        int clipsize = singleWeapon[10].toInt();
        int bulletsPerShot = 1;

        std::shared_ptr<Weapon> newWeapon(new Weapon(name, price, weaponType, minDamage,
                                      maxDamage, minRange, maxRange,
                                      shootAp, reloadAp, spread, clipsize, bulletsPerShot));
        allWeapons_.push_back(newWeapon);
    }
}


void GameProgress::initArmors() {
    // Armorit
    std::vector<QStringList> armorIni = parseIniFile(":/ini_files/armors.ini");
    for (std::vector<QStringList>::iterator it = armorIni.begin();
         it != armorIni.end(); ++it) {
        QStringList singleArmor = *it;
        // Tässä voisi tarkistaa että lista on oikean pituinen
        QString name = singleArmor[0];
        int price = singleArmor[1].toInt();
        int defence = singleArmor[2].toInt();

        std::shared_ptr<Armor> newArmor(new Armor(name, price, defence));
        allArmors_.push_back(newArmor);
    }
}


void GameProgress::initImplants() {
    // Implantit
    std::vector<QStringList> implantIni = parseIniFile(":/ini_files/implants.ini");
    for (std::vector<QStringList>::iterator it = implantIni.begin();
         it != implantIni.end(); ++it) {
        QStringList singleImplant = *it;
        // Tässä voisi tarkistaa että lista on oikean pituinen
        QString name = singleImplant[0];
        int price = singleImplant[1].toInt();

        int range = singleImplant[2].toInt();
        int attack = singleImplant[3].toInt();
        int defence = singleImplant[4].toInt();

        std::shared_ptr<Implant> newImplant(new Implant(name, price,
                                                        range, attack, defence));
        allImplants_.push_back(newImplant);
    }
}


void GameProgress::initEnemies() {
    // Enemies
    std::vector<QStringList> enemiesIni = parseIniFile(":/ini_files/enemies.ini");
    for (std::vector<QStringList>::iterator it = enemiesIni.begin();
         it != enemiesIni.end(); ++it) {
        QStringList singleEnemy = *it;
        // Tässä voisi tarkistaa että lista on oikean pituinen
        QString name = singleEnemy[0];
        int max_hp = singleEnemy[1].toInt();
        int current_hp = singleEnemy[2].toInt();
        int max_ap = singleEnemy[3].toInt();
        int current_ap = singleEnemy[4].toInt();
        std::shared_ptr<Weapon> weapon = findWeapon(singleEnemy[5]);
        std::shared_ptr<Armor> armor = findArmor(singleEnemy[6]);
        std::shared_ptr<Implant> implant = findImplant(singleEnemy[7]);

        std::shared_ptr<Enemy> newEnemy(new Enemy(name, max_hp, current_hp, max_ap,
                                                  current_ap, weapon, armor, implant));
        allEnemies_.push_back(newEnemy);
    }
}


QString GameProgress::generateSaveFile() {

    QString saveFile;
    /*  Save file:t koostuvat:

        0. Money
        1. Enemies killed
        2. Characters progress
        3. Researched Items
        4. Parkinghalls Controlled
        5. Total Gameplay Time
        6. Game Completition

        Tiedot tallennetaan yksittäiseen QStringiin.
        Numeroitujen ryhmien välissä on merkki '/'
        ja yksittäisten tietojen välissä merkki ','.
        Characterit erotellaan toisistaan merkillä '#'.
    */

    // 0. Money
    QString strMoney = QString::number(money_);
    saveFile.append(strMoney);
    saveFile.append("/");

    // 1. Enemies killed
    QString strEnemiesKilled = QString::number(enemiesKilled_);
    saveFile.append(strEnemiesKilled);
    saveFile.append("/");

    // 2. Characters progress
    for(auto character : charactersProgress_) {
        for(auto info : character) {
            saveFile.append(info);
            saveFile.append(",");
        }
        saveFile.remove(saveFile.length() - 1, 1);
        saveFile.append("#");
    }
    saveFile.remove(saveFile.length() - 1, 1);
    saveFile.append("/");


    // 3. Researched Items
    for(auto item : researchedItems_) {
        saveFile.append(item);
        saveFile.append(",");
    }
    saveFile.remove(saveFile.length() - 1, 1);
    saveFile.append("/");

    // 4. ParkingHalls Controlled
    if (parkinghallsControlled_.length() == 0) {
        saveFile.append("/");
    }
    else {
        for(auto id : parkinghallsControlled_) {
            saveFile.append(id);
            saveFile.append(",");
        }
        saveFile.remove(saveFile.length() - 1, 1);
        saveFile.append("/");
    }

    // 5. Gameplay Time
    elapsedBeforeCurrentSession_ += currentSessionTime_.restart();
    QString strElapsed = QString::number(elapsedBeforeCurrentSession_);
    saveFile.append(strElapsed);
    saveFile.append("/");


    // 6. Game Completition
    QString strCompletition = QString::number(gameCompletition_);
    saveFile.append(strCompletition);

    return saveFile;
}


void GameProgress::loadCharactersProgress() {
    QList<std::shared_ptr<PlayableCharacter>> listOfCharacters;
    for(auto info : charactersProgress_){

        QList<QString> charInfo = info;
        QString name = charInfo[0];
        int max_hp = charInfo[1].toInt();
        int current_hp = charInfo[2].toInt();
        int max_ap = charInfo[3].toInt();
        int current_ap = charInfo[4].toInt();

        QString wep_name = charInfo[5];
        QString armor_name = charInfo[6];
        QString implant_name = charInfo[7];

        std::shared_ptr<Weapon> wep = findWeapon(wep_name);
        std::shared_ptr<Armor> armor = findArmor(armor_name);
        std::shared_ptr<Implant> implant = findImplant(implant_name);

        PlayableCharacter loadedCharacter(name, max_hp, current_hp, max_ap, current_ap, wep, armor, implant);

        listOfCharacters.push_back(std::make_shared<PlayableCharacter>(loadedCharacter));

    }
    listOfCharacters_ = listOfCharacters;
}


void GameProgress::newGameCharactersProgress() {

    // TODO: Vai sittenkin lataa vain save_filen alustusarvoilla?
    // Jolloin tätä metodia ei tarvittaisi.
    QList<std::shared_ptr<PlayableCharacter>> listOfCharacters;
    for (int i = 0; i < 4; i++){

        QList<QString> names = {"Laura", "Kyborg X", "Big eye", "Tank"};

        QString name = names[i];
        int maxHp = 20;
        int currentHp = 20;
        int maxAp = 20;
        int currentAp = 20;

        // TODO: Etsi oikeat Itemit nimien perusteella ja aseta wep, armor ja implant oikeiksi.
        QString wepName = "PISTOL";
        QString armorName = "NONE";
        QString implantName = "NONE";

        std::shared_ptr<Weapon> wep = findWeapon(wepName);
        std::shared_ptr<Armor> armor = findArmor(armorName);
        std::shared_ptr<Implant> implant = findImplant(implantName);

        PlayableCharacter loadedCharacter(name, maxHp, currentHp, maxAp, currentAp, wep, armor, implant);
        listOfCharacters.push_back(std::make_shared<PlayableCharacter>(loadedCharacter));
    }
    listOfCharacters_ = listOfCharacters;
}


std::shared_ptr<Weapon> GameProgress::findWeapon(QString weaponName) {
    for(auto wep : allWeapons_) {
        if (wep.get()->getName() == weaponName){
            return wep;
        }
    }
    for(auto wep : allWeapons_) {
        if (wep.get()->getName() == "NONE"){
            return wep;
        }
    }
    // Ei löytynyt edes tyhjää asetta
    qDebug()<<"Aseen alustus epäonnistui";
    return nullptr;
}


std::shared_ptr<Armor> GameProgress::findArmor(QString armorName) {
    for(auto armor : allArmors_) {
        if (armor.get()->getName() == armorName){
            return armor;
        }
    }
    qDebug()<<"Ei löytynyt armoria halutulla nimellä, palautetaa NONE armor";
    for(auto armor : allArmors_) {
        if (armor.get()->getName() == "NONE"){
            return armor;
        }
    }
    // Ei löytynyt edes tyhjää armoria
    qDebug()<<"Armorin alustus epäonnistui";
    return nullptr;
}


std::shared_ptr<Implant> GameProgress::findImplant(QString implantName) {
    for(auto implant : allImplants_) {
        if (implant.get()->getName() == implantName){
            return implant;
        }
    }
    qDebug()<<"Ei löytynyt implanttia halutulla nimellä, palautetaa NONE implantti";
    for(auto implant : allImplants_) {
        if (implant.get()->getName() == "NONE"){
            return implant;
        }
    }
    // Ei löytynyt edes tyhjää implanttia
    qDebug()<<"Implantin alustus epäonnistui";
    return nullptr;
}


int GameProgress::elapsedMinutes() {
    elapsedBeforeCurrentSession_ += currentSessionTime_.restart();

    // Millisekunnit minuuteiksi: ms/1000/60
    return (elapsedBeforeCurrentSession_ / 1000 / 60);
}
