#include "view.h"

#include <map>
#include <QQuickView>
#include <QQmlProperty>
#include <QObject>
#include <QUrl>
#include <QObject>
#include <QDebug>


View::View(){
}

View::~View(){

}

void View::setUpWorldMap(QObject *requestedWindow, GameProgress progress, QList<std::shared_ptr<ParkingHall> > parkinghalls) {
    // Alustetaan listat joihin kerätään tieto.
    QList<QVariant> closedXList;
    QList<QVariant> closedYList;

    QList<QVariant> listOfOpenedX;
    QList<QVariant> listOfOpenedY;

    QList<QVariant> hallsNamesList;
    QList<QVariant> hallsIdsList;
    QList<QVariant> hallsVacantList;
    QList<QVariant> hallsOccupiedList;
    QList<QVariant> hallsControlledList;



    // Kerätään tiedot halleista ja sijoitetaan listoihin.
    for(auto ptrToHall : parkinghalls){
        bool hallControlled = false;
        for(auto controlled : progress.getControlledHalls()){
            if(ptrToHall.get()->getId() == controlled){
                hallControlled = true;
            }
        }
        hallsControlledList.append(hallControlled);
        if(!hallControlled){
            std::pair<int,int> coords = ptrToHall.get()->getCoordinates();
            closedXList.append(coords.first);
            closedYList.append(coords.second);
        }
        else {
            std::pair<int,int> coords = ptrToHall.get()->getCoordinates();
            listOfOpenedX.append(coords.first);
            listOfOpenedY.append(coords.second);
        }
        hallsNamesList.append(ptrToHall.get()->getName());
        hallsIdsList.append(ptrToHall.get()->getId());
        hallsVacantList.append(ptrToHall.get()->getVacant());
        hallsOccupiedList.append(ptrToHall.get()->getOccupied());
    }
    // Luodaan QVariantit(Joita QML:tiedostot voivat käyttää) ja sijoitetaan ne
    // requestedWindowiin.
    QVariant closed_x(closedXList);
    QVariant closed_y(closedYList);
    QVariant closed_length(closedXList.length());
    QVariant opened_x(listOfOpenedX);
    QVariant opened_y(listOfOpenedY);
    QVariant opened_length(listOfOpenedX.length());
    requestedWindow->setProperty("closedX", closed_x);
    requestedWindow->setProperty("closedY", closed_y);
    requestedWindow->setProperty("closedLength", closed_length);
    requestedWindow->setProperty("openedX", opened_x);
    requestedWindow->setProperty("openedY", opened_y);
    requestedWindow->setProperty("openedLength", opened_length);

    QVariant hallsNames(hallsNamesList);
    QVariant hallsIds(hallsIdsList);
    QVariant hallsVacant(hallsVacantList);
    QVariant hallsOccupied(hallsOccupiedList);
    QVariant hallsControlled(hallsControlledList);
    requestedWindow->setProperty("hallsNames", hallsNames);
    requestedWindow->setProperty("hallsIds", hallsIds);
    requestedWindow->setProperty("hallsVacant", hallsVacant);
    requestedWindow->setProperty("hallsOccupied", hallsOccupied);
    requestedWindow->setProperty("hallsControlled", hallsControlled);
}


void View::setUpHeadquarters(QObject *requestedWindow, GameProgress* progress,
                             QList<std::shared_ptr<ParkingHall> > parkinghalls) {
    QList<QVariant> playerNamesList;
    QList<QVariant> playerHealthsList;
    QList<QVariant> playerMaxHealthsList;
    QList<QVariant> playerApsLeftList;
    QList<QVariant> playerApsFullList;
    QList<QVariant> playerWeaponsList;
    QList<QVariant> playerArmorsList;
    QList<QVariant> playerImplantsList;

    QVariant money(progress->getMoney());
    QVariant gameCompletion(progress->getCompletion());
    QVariant totalPlaytime(progress->getTotalPlaytime());
    QVariant enemiesKilled(progress->getEnemiesKilled());
    QVariant researchedItems(progress->getResearchedItems().length());

    QVariant controllingParkinghalls(progress->getControlledHalls().length());
    QVariant allParkinghalls(parkinghalls.length());

    QVariant weaponsTotal(progress->getAllWeapons().length() - 1);
    QVariant implantsTotal(progress->getAllImplants().length() - 1);
    QVariant armorsTotal(progress->getAllArmors().length() - 1);
    QVariant itemsTotal(progress->getAllWeapons().length() + progress->getAllImplants().length() + progress->getAllArmors().length() - 3);

    int researchedWeapons = 0;
    int researchedArmors = 0;
    int researchedImplants = 0;

    // Päivitetään hahmojen tiedot ajan tasalle
    progress->updateCharactersProgress();

    for (auto item : progress->getResearchedItems()) {
        for (auto ptrToWeapon : progress->getAllWeapons()){
            if(item == ptrToWeapon.get()->getName()){
                researchedWeapons += 1;
                break;
            }
        }

        for (auto ptrToArmor : progress->getAllArmors()){
            if(item == ptrToArmor.get()->getName()){
                researchedArmors += 1;
                break;
            }
        }

        for (auto ptrToImplant : progress->getAllImplants()){
            if(item == ptrToImplant.get()->getName()){
                researchedImplants += 1;
                 break;
            }
        }
    }
    QVariant weaponsResearched(researchedWeapons);
    QVariant armorsResearched(researchedArmors);
    QVariant implantsResearched(researchedImplants);

    //name, maxHp, currenHp, maxAp, currentAp, equippedGun, equippedArmor, equippedImplant
    for (auto character : progress->getCharactersProgress()){
        playerNamesList.append(character[0]);
        playerMaxHealthsList.append(character[1]);
        playerHealthsList.append(character[2]);
        playerApsFullList.append(character[3]);
        playerApsLeftList.append(character[4]);
        playerWeaponsList.append(character[5]);
        playerArmorsList.append(character[6]);
        playerImplantsList.append(character[7]);
    }
    QVariant playerNames(playerNamesList);
    QVariant playerHealths(playerHealthsList);
    QVariant playerMaxHealths(playerMaxHealthsList);
    QVariant playerApsFull(playerApsFullList);
    QVariant playerApsLeft(playerApsLeftList);
    QVariant playerWeapons(playerWeaponsList);
    QVariant playerArmors(playerArmorsList);
    QVariant playerImplants(playerImplantsList);

    requestedWindow->setProperty("playerNames", playerNames);
    requestedWindow->setProperty("playerHealths", playerHealths);
    requestedWindow->setProperty("playerMaxHealths", playerMaxHealths);
    requestedWindow->setProperty("playerApsLeft", playerApsLeft);
    requestedWindow->setProperty("playerApsFull", playerApsFull);
    requestedWindow->setProperty("playerWeapons", playerWeapons);
    requestedWindow->setProperty("playerArmors", playerArmors);
    requestedWindow->setProperty("playerImplants", playerImplants);

    requestedWindow->setProperty("money", money);
    requestedWindow->setProperty("gameCompletion", gameCompletion);
    requestedWindow->setProperty("enemiesKilled", enemiesKilled);
    requestedWindow->setProperty("totalPlaytime", totalPlaytime);
    requestedWindow->setProperty("itemsResearched", researchedItems);
    requestedWindow->setProperty("weaponsResearched", weaponsResearched);
    requestedWindow->setProperty("armorsResearched", armorsResearched);
    requestedWindow->setProperty("implantsResearched", implantsResearched);

    requestedWindow->setProperty("itemsTotal", itemsTotal);
    requestedWindow->setProperty("controllingParkinghalls", controllingParkinghalls);
    requestedWindow->setProperty("totalParkinghalls", allParkinghalls);

    requestedWindow->setProperty("weaponsTotal", weaponsTotal);
    requestedWindow->setProperty("armorsTotal", armorsTotal);
    requestedWindow->setProperty("implantsTotal", implantsTotal);

}


void View::setUpResearchCenter(QObject *requestedWindow, GameProgress progress, QList<std::shared_ptr<ParkingHall> > parkinghalls) {
    QList<QVariant> weaponNamesList;
    QList<QVariant> weaponPricesList;
    QList<QVariant> weaponTypesList;
    QList<QVariant> weaponMinDamageList;
    QList<QVariant> weaponMaxDamageList;
    QList<QVariant> weaponMinRangeList;
    QList<QVariant> weaponMaxRangeList;
    QList<QVariant> weaponShootApList;
    QList<QVariant> weaponReloadApList;
    QList<QVariant> weaponSpreadList;
    QList<QVariant> weaponClipsizeList;
    QList<QVariant> weaponOwnedList;

    QList<QString> researchedItems = progress.getResearchedItems();

    for(auto ptrToWep : progress.getAllWeapons() ){
        if (ptrToWep.get()->getName() == "NONE"){
            break;
        }
        weaponNamesList.append(ptrToWep.get()->getName());
        weaponPricesList.append(ptrToWep.get()->getPrice());
        if (ptrToWep.get()->getType() == Weapon::WeaponType::ANTI_ARMOR){
            weaponTypesList.append("ANTI ARMOR");
        }
        else if (ptrToWep.get()->getType() == Weapon::WeaponType::RANGED){
            weaponTypesList.append("RANGED");
        }
        else {
            weaponTypesList.append("MELEE");
        }
        weaponMinDamageList.append(ptrToWep.get()->getMinDamage());
        weaponMaxDamageList.append(ptrToWep.get()->getMaxDamage());
        weaponMinRangeList.append(ptrToWep.get()->getMinRange());
        weaponMaxRangeList.append(ptrToWep.get()->getMaxRange());
        weaponShootApList.append(ptrToWep.get()->getShootAp());
        weaponReloadApList.append(ptrToWep.get()->getReloadAp());
        weaponSpreadList.append(ptrToWep.get()->getSpread());
        weaponClipsizeList.append(ptrToWep.get()->getClipsize());

        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToWep.get()->getName()) {
                owned = true;
            }
        }
        weaponOwnedList.append(owned);
    }

    requestedWindow->setProperty("weaponsNames", weaponNamesList);
    requestedWindow->setProperty("weaponsPrices", weaponPricesList);
    requestedWindow->setProperty("weaponsTypes", weaponTypesList);
    requestedWindow->setProperty("weaponsMinDamage", weaponMinDamageList);
    requestedWindow->setProperty("weaponsMaxDamage", weaponMaxDamageList);
    requestedWindow->setProperty("weaponsMinRange", weaponMinRangeList);
    requestedWindow->setProperty("weaponsMaxRange", weaponMaxRangeList);
    requestedWindow->setProperty("weaponsShootAp", weaponShootApList);
    requestedWindow->setProperty("weaponsReloadAp", weaponReloadApList);
    requestedWindow->setProperty("weaponsSpread", weaponSpreadList);
    requestedWindow->setProperty("weaponsClipsize", weaponClipsizeList);
    requestedWindow->setProperty("weaponsOwned", weaponOwnedList);


    QList<QVariant> armorsNamesList;
    QList<QVariant> armorsPricesList;
    QList<QVariant> armorsDefencesList;
    QList<QVariant> armorsOwnedList;
    for(auto ptrToArmor : progress.getAllArmors() ){
        if (ptrToArmor.get()->getName() == "NONE"){
            break;
        }
        armorsNamesList.append(ptrToArmor.get()->getName());
        armorsPricesList.append(ptrToArmor.get()->getPrice());
        armorsDefencesList.append(ptrToArmor.get()->getDefence());

        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToArmor.get()->getName()) {
                owned = true;
            }
        }
        armorsOwnedList.append(owned);
    }
    requestedWindow->setProperty("armorsNames", armorsNamesList);
    requestedWindow->setProperty("armorsPrices", armorsPricesList);
    requestedWindow->setProperty("armorsDefences", armorsDefencesList);
    requestedWindow->setProperty("armorsOwned", armorsOwnedList);

    QList<QVariant> implantsNamesList;
    QList<QVariant> implantsPricesList;
    QList<QVariant> implantsAttackBoostList;
    QList<QVariant> implantsRangeBoostList;
    QList<QVariant> implantsDefenceBoostList;
    QList<QVariant> implantsOwnedList;
    for(auto ptrToImplant : progress.getAllImplants() ){
        if (ptrToImplant.get()->getName() == "NONE"){
            break;
        }
        implantsNamesList.append(ptrToImplant.get()->getName());
        implantsPricesList.append(ptrToImplant.get()->getPrice());
        implantsAttackBoostList.append(ptrToImplant.get()->getAttackBonus());
        implantsRangeBoostList.append(ptrToImplant.get()->getRangeBonus());
        implantsDefenceBoostList.append(ptrToImplant.get()->getDefenceBonus());
        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToImplant.get()->getName()) {
                owned = true;
            }
        }
        implantsOwnedList.append(owned);
    }
    requestedWindow->setProperty("implantsNames", implantsNamesList);
    requestedWindow->setProperty("implantsPrices", implantsPricesList);
    requestedWindow->setProperty("implantsAttackBoost", implantsAttackBoostList);
    requestedWindow->setProperty("implantsRangeBoost", implantsRangeBoostList);
    requestedWindow->setProperty("implantsDefenceBoost", implantsDefenceBoostList);
    requestedWindow->setProperty("implantsOwned", implantsOwnedList);

    QVariant money(progress.getMoney());
    requestedWindow->setProperty("money", money);
}


void View::setUpBattleMap(QObject *requestedWindow, GameProgress progress,
                          QList<std::shared_ptr<ParkingHall> > parkinghalls) {
    QList<QVariant> playerHealthsList;
    QList<QVariant> playerApsLeftList;
    QList<QVariant> playerApsFullList;
    QList<QVariant> playerMaxHealthsList;

    for (auto character : progress.getCharactersProgress()){
        playerMaxHealthsList.append(character[1]);
        playerHealthsList.append(character[2]);
        playerApsFullList.append(character[3]);
        playerApsLeftList.append(character[4]);
    }

    QVariant playerHealths(playerHealthsList);
    QVariant playerApsFull(playerApsFullList);
    QVariant playerApsLeft(playerApsLeftList);
    QVariant playerMaxHealths(playerMaxHealthsList);

    requestedWindow->setProperty("playerMaxHealths", playerMaxHealths);
    requestedWindow->setProperty("playerHealths", playerHealths);
    requestedWindow->setProperty("playerApsLeft", playerApsLeft);
    requestedWindow->setProperty("playerApsFull", playerApsFull);
}


void View::setUpInventory(QObject *requestedWindow, GameProgress progress,
                          QList<std::shared_ptr<ParkingHall> > parkinghalls) {

    QList<QVariant> weaponNamesList;
    QList<QVariant> weaponPricesList;
    QList<QVariant> weaponTypesList;
    QList<QVariant> weaponMinDamageList;
    QList<QVariant> weaponMaxDamageList;
    QList<QVariant> weaponMinRangeList;
    QList<QVariant> weaponMaxRangeList;
    QList<QVariant> weaponShootApList;
    QList<QVariant> weaponReloadApList;
    QList<QVariant> weaponSpreadList;
    QList<QVariant> weaponClipsizeList;
    QList<QVariant> weaponOwnedList;

    QList<QString> researchedItems = progress.getResearchedItems();

    for(auto ptrToWep : progress.getAllWeapons() ){
        if (ptrToWep.get()->getName() == "NONE"){
            break;
        }
        weaponNamesList.append(ptrToWep.get()->getName());
        weaponPricesList.append(ptrToWep.get()->getPrice());
        if (ptrToWep.get()->getType() == Weapon::WeaponType::ANTI_ARMOR){
            weaponTypesList.append("ANTI ARMOR");
        }
        else if (ptrToWep.get()->getType() == Weapon::WeaponType::RANGED){
            weaponTypesList.append("RANGED");
        }
        else {
            weaponTypesList.append("MELEE");
        }
        weaponMinDamageList.append(ptrToWep.get()->getMinDamage());
        weaponMaxDamageList.append(ptrToWep.get()->getMaxDamage());
        weaponMinRangeList.append(ptrToWep.get()->getMinRange());
        weaponMaxRangeList.append(ptrToWep.get()->getMaxRange());
        weaponShootApList.append(ptrToWep.get()->getShootAp());
        weaponReloadApList.append(ptrToWep.get()->getReloadAp());
        weaponSpreadList.append(ptrToWep.get()->getSpread());
        weaponClipsizeList.append(ptrToWep.get()->getClipsize());

        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToWep.get()->getName()) {
                owned = true;
            }
        }
        weaponOwnedList.append(owned);
    }

    requestedWindow->setProperty("weaponsNames", weaponNamesList);
    requestedWindow->setProperty("weaponsPrices", weaponPricesList);
    requestedWindow->setProperty("weaponsTypes", weaponTypesList);
    requestedWindow->setProperty("weaponsMinDamage", weaponMinDamageList);
    requestedWindow->setProperty("weaponsMaxDamage", weaponMaxDamageList);
    requestedWindow->setProperty("weaponsMinRange", weaponMinRangeList);
    requestedWindow->setProperty("weaponsMaxRange", weaponMaxRangeList);
    requestedWindow->setProperty("weaponsShootAp", weaponShootApList);
    requestedWindow->setProperty("weaponsReloadAp", weaponReloadApList);
    requestedWindow->setProperty("weaponsSpread", weaponSpreadList);
    requestedWindow->setProperty("weaponsClipsize", weaponClipsizeList);
    requestedWindow->setProperty("weaponsOwned", weaponOwnedList);


    QList<QVariant> armorsNamesList;
    QList<QVariant> armorsPricesList;
    QList<QVariant> armorsDefencesList;
    QList<QVariant> armorsOwnedList;
    for(auto ptrToArmor : progress.getAllArmors() ){
        if (ptrToArmor.get()->getName() == "NONE"){
            break;
        }
        armorsNamesList.append(ptrToArmor.get()->getName());
        armorsPricesList.append(ptrToArmor.get()->getPrice());
        armorsDefencesList.append(ptrToArmor.get()->getDefence());

        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToArmor.get()->getName()) {
                owned = true;
            }
        }
        armorsOwnedList.append(owned);
    }
    requestedWindow->setProperty("armorsNames", armorsNamesList);
    requestedWindow->setProperty("armorsPrices", armorsPricesList);
    requestedWindow->setProperty("armorsDefences", armorsDefencesList);
    requestedWindow->setProperty("armorsOwned", armorsOwnedList);

    QList<QVariant> implantsNamesList;
    QList<QVariant> implantsPricesList;
    QList<QVariant> implantsAttackBoostList;
    QList<QVariant> implantsRangeBoostList;
    QList<QVariant> implantsDefenceBoostList;
    QList<QVariant> implantsOwnedList;
    for(auto ptrToImplant : progress.getAllImplants() ){
        if (ptrToImplant.get()->getName() == "NONE"){
            break;
        }
        implantsNamesList.append(ptrToImplant.get()->getName());
        implantsPricesList.append(ptrToImplant.get()->getPrice());
        implantsAttackBoostList.append(ptrToImplant.get()->getAttackBonus());
        implantsRangeBoostList.append(ptrToImplant.get()->getRangeBonus());
        implantsDefenceBoostList.append(ptrToImplant.get()->getDefenceBonus());
        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToImplant.get()->getName()) {
                owned = true;
            }
        }
        implantsOwnedList.append(owned);
    }
    requestedWindow->setProperty("implantsNames", implantsNamesList);
    requestedWindow->setProperty("implantsPrices", implantsPricesList);
    requestedWindow->setProperty("implantsAttackBoost", implantsAttackBoostList);
    requestedWindow->setProperty("implantsRangeBoost", implantsRangeBoostList);
    requestedWindow->setProperty("implantsDefenceBoost", implantsDefenceBoostList);
    requestedWindow->setProperty("implantsOwned", implantsOwnedList);

    QVariant money(progress.getMoney());
    requestedWindow->setProperty("money", money);


    QList<QVariant> playerNamesList;
    QList<QVariant> playerWeaponsList;
    QList<QVariant> playerArmorsList;
    QList<QVariant> playerImplantsList;

    //name, maxHp, currenHp, maxAp, currentAp, equippedGun, equippedArmor, equippedImplant
    for (auto character : progress.getCharactersProgress()){
        playerNamesList.append(character[0]);
        playerWeaponsList.append(character[5]);
        playerArmorsList.append(character[6]);
        playerImplantsList.append(character[7]);
    }
    QVariant playerNames(playerNamesList);
    QVariant playerWeapons(playerWeaponsList);
    QVariant playerArmors(playerArmorsList);
    QVariant playerImplants(playerImplantsList);

    requestedWindow->setProperty("playerNames", playerNames);
    requestedWindow->setProperty("playerWeapons", playerWeapons);
    requestedWindow->setProperty("playerArmors", playerArmors);
    requestedWindow->setProperty("playerImplants", playerImplants);

}


void View::setController(Controller* controllerInstance) {
    controller_ = controllerInstance;
}


void View::setEngine(QQmlApplicationEngine* engineInstance) {
    engine_ = engineInstance;
    return;
}


bool View::switchView(View::ActiveView requestedView, GameProgress progress, QList<std::shared_ptr<ParkingHall>> parkinghalls) {        

    std::map<View::ActiveView, QQuickItem*>::iterator it = views_.find(requestedView);

    // Tarkistetaan mitä näkymää pyydettiin
    if (requestedView == View::ActiveView::MAIN_MENU){
        // Tarkistetaan onko näkymä olemassa ja luodaan jos ei ole
        if (it == views_.end()){
                // Luodaan koponentti ja muunnetaan QQuickItemiksi
                QQmlComponent component(engine_, QUrl(QStringLiteral("qrc:/main.qml")));
                QObject *object = component.create();

                QQuickItem *mainMenu = qobject_cast<QQuickItem*>(object);

                // Yhdistetään signaalit ja slotit
                QObject::connect(mainMenu, SIGNAL(exitGame(bool)),
                                 controller_, SLOT(exitRequested(bool)));
                QObject::connect(mainMenu, SIGNAL(startGame(bool)),
                                 controller_, SLOT(newGameRequested(bool)));

                // Tallennetaan viite näkymään
                views_.insert(std::pair<ActiveView, QQuickItem*>(requestedView, mainMenu));
                currentView_ = View::ActiveView::MAIN_MENU;
        }

    } else if (requestedView==View::ActiveView::WORLD_MAP) {
        if (it == views_.end()){
            QQmlComponent component(engine_, QUrl(QStringLiteral("qrc:/worldMap.qml")));
            if (component.isError()){

            }
            QObject *object = component.create();
            QQuickItem *viewItem = qobject_cast<QQuickItem*>(object);

            // Yhdistetään signaalit ja slotit tässä kohtaa
            QObject::connect(viewItem, SIGNAL(toMainMenu(bool)),
                             controller_, SLOT(mainMenuRequested(bool)));
            QObject::connect(viewItem, SIGNAL(toHeadquarters(bool)),
                             controller_, SLOT(headquartersRequested(bool)));
            QObject::connect(viewItem, SIGNAL(toBattleMap(bool,int)),
                             controller_, SLOT(battleMapRequested(bool, int)));
            QObject::connect(viewItem, SIGNAL(saveAndExit()),
                             controller_, SLOT(saveAndExitRequested()));


            views_.insert(std::pair<ActiveView, QQuickItem*>(requestedView, viewItem));
        }
    } else if (requestedView==View::ActiveView::RESEARCH_CENTER) {
        if (it == views_.end()){
            QQmlComponent component(engine_, QUrl(QStringLiteral("qrc:/researchCenter.qml")));
            if (component.isError()){

            }
            QObject *object = component.create();
            QQuickItem *viewItem = qobject_cast<QQuickItem*>(object);

            // Yhdistetään signaalit ja slotit tässä kohtaa
            QObject::connect(viewItem, SIGNAL(toHeadquarters(bool)),
                             controller_, SLOT(headquartersRequested(bool)));
            QObject::connect(viewItem, SIGNAL(itemResearched(QString, int)),
                             controller_, SLOT(itemResearched(QString, int)));

            views_.insert(std::pair<ActiveView, QQuickItem*>(requestedView, viewItem));
        }
    } else if (requestedView==View::ActiveView::HEADQUARTERS) {
        if (it == views_.end()){
            QQmlComponent component(engine_, QUrl(QStringLiteral("qrc:/base.qml")));
            if (component.isError()){

            }
            QObject *object = component.create();
            QQuickItem *viewItem = qobject_cast<QQuickItem*>(object);

            // Yhdistetään signaalit ja slotit tässä kohtaa
            QObject::connect(viewItem, SIGNAL(toResearchCenter(bool)),
                             controller_, SLOT(researchCenterRequested(bool)));
            QObject::connect(viewItem, SIGNAL(toWorldMap(bool)),
                             controller_, SLOT(worldMapRequested(bool)));
            QObject::connect(viewItem, SIGNAL(toInventory(bool)),
                             controller_, SLOT(inventoryRequested(bool)));
            QObject::connect(viewItem, SIGNAL(saveAndExit()),
                             controller_, SLOT(saveAndExitRequested()));
            QObject::connect(viewItem, SIGNAL(healTeam(int)),
                             controller_, SLOT(healTeam(int)));
            QObject::connect(viewItem, SIGNAL(healCharacter(int, int)),
                             controller_, SLOT(healCharacter(int, int)));


            views_.insert(std::pair<ActiveView, QQuickItem*>(requestedView, viewItem));
        }
    } else if (requestedView==View::ActiveView::BATTLE_MAP) {

        QQmlComponent component(engine_, QUrl(QStringLiteral("qrc:/battleMap.qml")));
        if (component.isError()){

        }
        QObject *object = component.create();
        QQuickItem *viewItem = qobject_cast<QQuickItem*>(object);

        // Yhdistetään signaalit ja slotit tässä kohtaa
        QObject::connect(viewItem, SIGNAL(toWorldMap(bool)),
                         controller_, SLOT(worldMapRequested(bool)));
        QObject::connect(viewItem, SIGNAL(moveToTile(bool, int, int, int)),
                         controller_, SLOT(moveToTileRequested(bool, int, int, int)));
        QObject::connect(viewItem, SIGNAL(attackToTile(bool, int, int, int)),
                         controller_, SLOT(attackToTileRequested(bool, int, int, int)));
        QObject::connect(viewItem, SIGNAL(endTurn(bool)),
                         controller_, SLOT(endTurnRequested(bool)));
        QObject::connect(viewItem, SIGNAL(checkGameStatus()),
                         controller_, SLOT(checkGameStatusRequested()));

        std::map<View::ActiveView, QQuickItem*>::iterator it = views_.find(requestedView);
        if (!(it == views_.end())){
            delete views_[View::ActiveView::BATTLE_MAP];
            views_[View::ActiveView::BATTLE_MAP] = nullptr;
            views_[View::ActiveView::BATTLE_MAP] = viewItem;
        } else {
            views_.insert(std::pair<ActiveView, QQuickItem*>(requestedView, viewItem));
        }

    } else if (requestedView==View::ActiveView::INVENTORY) {
        if (it == views_.end()){
            QQmlComponent component(engine_, QUrl(QStringLiteral("qrc:/inventory.qml")));
            if (component.isError()){

            }
            QObject *object = component.create();
            QQuickItem *viewItem = qobject_cast<QQuickItem*>(object);

            QObject::connect(viewItem, SIGNAL(toHeadquarters(bool)),
                             controller_, SLOT(headquartersRequested(bool)));
            QObject::connect(viewItem, SIGNAL(itemEquipped(int, QString)),
                             controller_, SLOT(itemEquipped(int, QString)));

            views_.insert(std::pair<ActiveView, QQuickItem*>(requestedView, viewItem));
        }
    }

    // Jos pyydetty näkymä ei ole nykyinen näkymä, näytetään uusi näkymä ja piilotetaan edellinen
    if (currentView_ != requestedView){
        QObject* requestedWindow = views_[requestedView]->findChild<QObject*>("window");
        requestedWindow->setProperty("enabled", true);
        requestedWindow->setProperty("visible", true);

        // Asetetaan tiedot näkymälle käyttäen GameProgressia.
        if(requestedView == View::ActiveView::MAIN_MENU){
        }
        else if (requestedView == View::ActiveView::WORLD_MAP) {
            setUpWorldMap(requestedWindow, progress, parkinghalls);
        }
        else if (requestedView == View::ActiveView::HEADQUARTERS){
            setUpHeadquarters(requestedWindow, &progress, parkinghalls);
        }
        else if (requestedView == View::ActiveView::RESEARCH_CENTER){
            setUpResearchCenter(requestedWindow, progress, parkinghalls);
        }
        else if (requestedView == View::ActiveView::BATTLE_MAP){
            setUpBattleMap(requestedWindow, progress, parkinghalls);
        }
        else if (requestedView == View::ActiveView::INVENTORY){
            setUpInventory(requestedWindow, progress, parkinghalls);
        }

        QObject* window = views_[currentView_]->findChild<QObject*>("window");
        window->setProperty("enabled", false);
        window->setProperty("visible", false);
    }
    currentView_ = requestedView;
    return true;
}


bool View::logMessage(){
    return true;
}


void View::closeAll(){
    views_[View::MAIN_MENU]->setVisible(false);
    views_[View::MAIN_MENU]->setEnabled(false);
    //views_[View::MAIN_MENU]->window()->setVisible(true);
    QObject* mainView =  views_[View::MAIN_MENU]->findChild<QObject*>("window");
    mainView->setProperty("visible", false);
    return;
}


void View::initializeCharactersToMap(QList<int> playableCharactersLocations,
                                     QList<int> enemyCharactersLocations,
                                     QList<int> enemyCharactersHealth) {
    // Etsitään BattleMap.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");

    // Luodaan QVariant pelattavien hahmojen sijainneista.
    QList<QVariant> playableCharLocationsList;
    for (auto location : playableCharactersLocations){
        playableCharLocationsList.append(location);
    }
    QVariant playableCharacsLocations(playableCharLocationsList);

    // Sijoitetaan sijainnit QML:län propertyyn playerCharactersAt.
    battleMapQml->setProperty("playerCharactersAt", playableCharacsLocations);


    // Sama vihulaisille.
    QList<QVariant> enemyCharLocationsList;
    for (auto location : enemyCharactersLocations){
        enemyCharLocationsList.append(location);
    }

    QList<QVariant> enemyHealthsList;
    for (auto health: enemyCharactersHealth){
        enemyHealthsList.append(health);
    }



    QVariant enemyCharacsLocations(enemyCharLocationsList);
    battleMapQml->setProperty("enemyCharactersAt", enemyCharacsLocations);
    battleMapQml->setProperty("enemyHealths", enemyHealthsList);
}


void View::isMovePermitted(bool permission) {
    // Etsitään BattleMap.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");
    QVariant isMovePermitted(permission);
    battleMapQml->setProperty("movePermission", isMovePermitted);
    battleMapQml->setProperty("moveAnswered", true);

}


void View::isAttackPermitted(bool permission) {
    // Etsitään BattleMap.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");
    QVariant isAttackPermitted(permission);
    battleMapQml->setProperty("attackPermission", isAttackPermitted);

}


void View::updateCharactersLocations(QList<int> playableCharactersLocations, QList<int> enemyCharactersLocations) {

    // Etsitään BattleMap.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");

    // Luodaan QVariant pelattavien hahmojen sijainneista.
    QList<QVariant> playableCharLocationsList;
    for (auto location : playableCharactersLocations){
        playableCharLocationsList.append(location);
    }
    QVariant playableCharacsLocations(playableCharLocationsList);
    battleMapQml->setProperty("playerCharactersAt", playableCharacsLocations);


    // Sama vihulaisille.
    QList<QVariant> enemyCharLocationsList;
    for (auto location : enemyCharactersLocations){
        enemyCharLocationsList.append(location);
    }
    QVariant enemyCharacsLocations(enemyCharLocationsList);
    battleMapQml->setProperty("enemyCharactersAt", enemyCharacsLocations);

}


void View::updateEnemyTurnLocation(int tile) {
    // Etsitään BattleMap.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");

    QVariant turnTile(tile);
    battleMapQml->setProperty("currentTurnTile", turnTile);
    battleMapQml->setProperty("turnChanged", true);
}


void View::characterAttacking(QList<int> playableCharactersHealths,
                              QList<int> playableCharactersMaxHealths,
                              QList<int> playableCharactersAps,
                              QList<int> enemyCharactersAps,
                              QList<int> enemyCharactersHealths,
                              int attackingTile, int attackedTile) {

    // Etsitään BattleMap.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");

    QList<QVariant> playerHealthsList;

    for(auto health : playableCharactersHealths){

        if (health < 0){
            health = 0;
        }

        playerHealthsList.append(health);

    }

    QList<QVariant> playerMaxHealthsList;
    for(auto maxHealth : playableCharactersMaxHealths){
        playerMaxHealthsList.append(maxHealth);
    }


    QVariant playerHealths(playerHealthsList);
    battleMapQml->setProperty("playerHealths", playerHealths);
    battleMapQml->setProperty("playerMaxHealths", playerMaxHealthsList);


    QList<QVariant> playerApsLeftList;
    for(auto ap : playableCharactersAps){
        playerApsLeftList.append(ap);
    }
    QVariant playerApsLeft(playerApsLeftList);
    battleMapQml->setProperty("playerApsLeft", playerApsLeft);


    QList<QVariant> enemyApsLeftList;
    for(auto ap : enemyCharactersAps){
        enemyApsLeftList.append(ap);
    }

    QVariant enemyApsLeft(enemyApsLeftList);
    battleMapQml->setProperty("enemyApsLeft", enemyApsLeft);

    QList<QVariant> enemyHealthLeftList;
    for(auto hp : enemyCharactersHealths){
        enemyHealthLeftList.append(hp);
    }
    QVariant enemyHealthLeft(enemyHealthLeftList);
    battleMapQml->setProperty("enemyHealths", enemyHealthLeft);


    QVariant attackingTileNumber(attackingTile);
    QVariant targetTileNumber(attackedTile);
    battleMapQml->setProperty("attackedTile", targetTileNumber);
    battleMapQml->setProperty("attackingTile", attackingTileNumber);

    battleMapQml->setProperty("enemyAttacked", true);
}

void View::nextTurn() {
    // Etsitään BattleMap.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");
    battleMapQml->setProperty("nextTurn", true);
}

void View::enemyTurnOver() {
    // Etsitään BattleMap.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");
    battleMapQml->setProperty("isPlayerTurn", true);

}

void View::battleOver(QString hallName, int prizeMoney) {
    // Etsitään ResearchCenter.qmllän QObject nimeltä window.
    QObject* battleMapQml = views_[currentView_]->findChild<QObject*>("window");

    QVariant parkinghallName(hallName);
    QVariant prize(prizeMoney);

    battleMapQml->setProperty("hallId", parkinghallName);
    battleMapQml->setProperty("prizeMoney", prize);
    battleMapQml->setProperty("battleEnded", true);
}

void View::gameOver(QString reason) {
    // Etsitään ResearchCenter.qmllän QObject nimeltä window.
    QObject* worldMapQml = views_[currentView_]->findChild<QObject*>("window");

    QVariant gameOverReason(reason);

    worldMapQml->setProperty("gameLostMessage", gameOverReason);
    worldMapQml->setProperty("showGameLostMessage", true);

}

void View::gameWon(QString message) {
    // Etsitään ResearchCenter.qmllän QObject nimeltä window.
    QObject* worldMapQml = views_[View::ActiveView::WORLD_MAP]->findChild<QObject*>("window");

    QVariant gameWon(message);

    worldMapQml->setProperty("gameWonMessage", gameWon);
    worldMapQml->setProperty("showGameWonMessage", true);
}


void View::updateResearchCenterPropertys(GameProgress progress) {
    // Etsitään ResearchCenter.qmllän QObject nimeltä window.
    QObject* researchCenterQml = views_[currentView_]->findChild<QObject*>("window");

    QList<QVariant> weaponOwnedList;

    QList<QString> researchedItems = progress.getResearchedItems();

    for(auto ptrToWep : progress.getAllWeapons() ){
        if (ptrToWep.get()->getName() == "NONE"){
            break;
        }

        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToWep.get()->getName()) {
                owned = true;
            }
        }
        weaponOwnedList.append(owned);
    }
    researchCenterQml->setProperty("weaponsOwned", weaponOwnedList);


    QList<QVariant> armorsOwnedList;
    for(auto ptrToArmor : progress.getAllArmors() ){
        if (ptrToArmor.get()->getName() == "NONE"){
            break;
        }
        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToArmor.get()->getName()) {
                owned = true;
            }
        }
        armorsOwnedList.append(owned);
    }
    researchCenterQml->setProperty("armorsOwned", armorsOwnedList);


    QList<QVariant> implantsOwnedList;
    for(auto ptrToImplant : progress.getAllImplants() ){
        if (ptrToImplant.get()->getName() == "NONE"){
            break;
        }
        bool owned = false;
        for(auto item : researchedItems){
            if (item == ptrToImplant.get()->getName()) {
                owned = true;
            }
        }
        implantsOwnedList.append(owned);
    }
    researchCenterQml->setProperty("implantsOwned", implantsOwnedList);

    QVariant money(progress.getMoney());
    researchCenterQml->setProperty("money", money);
}


void View::updateInventoryPropertys(GameProgress progress) {
    // Etsitään inventory.qmllän QObject nimeltä window.
    QObject* inventoryQml = views_[currentView_]->findChild<QObject*>("window");

    QList<QVariant> playerNamesList;
    QList<QVariant> playerWeaponsList;
    QList<QVariant> playerArmorsList;
    QList<QVariant> playerImplantsList;

    //name, maxHp, currenHp, maxAp, currentAp, equippedGun, equippedArmor, equippedImplant
    for (auto character : progress.getCharactersProgress()){
        playerNamesList.append(character[0]);
        playerWeaponsList.append(character[5]);
        playerArmorsList.append(character[6]);
        playerImplantsList.append(character[7]);
    }
    QVariant playerNames(playerNamesList);
    QVariant playerWeapons(playerWeaponsList);
    QVariant playerArmors(playerArmorsList);
    QVariant playerImplants(playerImplantsList);

    inventoryQml->setProperty("playerNames", playerNames);
    inventoryQml->setProperty("playerWeapons", playerWeapons);
    inventoryQml->setProperty("playerArmors", playerArmors);
    inventoryQml->setProperty("playerImplants", playerImplants);
}


