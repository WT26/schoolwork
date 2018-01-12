#include "motor.h"

#include <QDebug>
#include <fstream>
#include <string>
#include <time.h>
#include <QCoreApplication>
#include <QEventLoop>

Motor::Motor():
    updateHallDataTimer_(new QTimer),
    datex2Api_(new Parking::TampereParking),
    viewInstance(nullptr),
    battleMap_(nullptr),
    battleAi_(new BattleAI),
    saveSlot_(2),
    gameLost_(false),
    gameWon_(false)
{
}

Motor::~Motor()
{
}

// Funktio näkymäpointterin asettamiseksi
void Motor::setView(ViewInterface* view) {
    viewInstance = view;
}

void Motor::initializeGame() {
    qDebug() << "Luetaan alustustiedostot";
    progress_.initEntitys();

    loadGame();

    // Alustetaan tiedot parkkihalleista.
    datex2Api_->initGameData();
    totalHalls_ = datex2Api_->getParkingHalls().size();

    // Yhdistetään timeri slottiin ja käynnistetään se. Minuutin päästä parkkihallidata
    // päivitetään.
    QObject::connect(updateHallDataTimer_, SIGNAL(timeout()), this, SLOT(updateHallsRequested()));
    updateHallDataTimer_->start(60000);

    viewInstance->switchView(ViewInterface::ActiveView::MAIN_MENU, progress_, datex2Api_->getParkingHalls());
    return;
}

void Motor::initializeBattleMap(int parkingHallIndex){
    // Castataan PlayableCharactereista charactereita battlemappiin.
    QList<std::shared_ptr<PlayableCharacter>> playableCharacters = \
            progress_.getListOfCharacters();
    QList<std::shared_ptr<Character>> characters;

    for (auto playable : playableCharacters) {
        std::shared_ptr<Character> charac = playable;
        characters.append(playable);

    }

    // Määritetään taistelun vaikeus parkkihallidatan perusteella
    auto chosenHall = datex2Api_->getParkingHalls()[parkingHallIndex];
    activeHall_ = parkingHallIndex;
    double occupied = chosenHall->getOccupied();
    double percentOccupied = occupied /\
            (occupied + chosenHall->getVacant());

    // Asetetaan vaikeustaso, joka vaikuttaa vihollisten määrään
    // (1-8 vihollista)
    int difficulty = ceil(percentOccupied * 10)/2;
    if (difficulty < 1){
        difficulty = 1;
    } else if (difficulty > 8) {
        difficulty = 8;
    }

    // Luodaan uusi taistelukartta
    battleMap_ = new BattleMap(characters, difficulty, progress_.getAllEnemies());
    battleAi_ = new BattleAI();

    // Annetaan tekoälylle pääsy taistelukarttaan
    battleAi_->setBattleMap(battleMap_);

    QObject::connect(battleMap_, SIGNAL(enemyMoved()),
            this, SLOT(enemyMoved()));
    QObject::connect(battleMap_, SIGNAL(enemyAttacking(int, int)),
            this, SLOT(enemyAttacking(int, int)));
    QObject::connect(battleMap_, SIGNAL(enemyTurnOver()),
            this, SLOT(enemyTurnOver()));
    QObject::connect(battleMap_, SIGNAL(updateEnemyTurnLocation(int)),
                   this, SLOT(updateEnemyTurnLocation(int)));
    QObject::connect(battleMap_, SIGNAL(delaySeconds(int)),
            this, SLOT(delaySeconds(int)));
    QObject::connect(battleMap_, SIGNAL(battleFinished(int)),
                     this, SLOT(battleFinished(int)));
    QObject::connect(battleMap_, SIGNAL(playerLost()),
                     this, SLOT(playerLost()));

}



// Päävalikon ja kartan toimintoihin liittyvät slotit
// Aloita uusi peli
void Motor::newGame() {
    switchView(MotorInterface::ActiveView::WORLD_MAP);
    return;
}

// Sulje peli
void Motor::quitGame() {
    // Tässä kohtaa voidaan kysyä onko pelaaja varma ja purkaa
    // asioita hallitusti
    this->viewInstance->closeAll();

    emit quitApplication();
}

// Vaihda näkymää
void Motor::switchView(MotorInterface::ActiveView nextView) {

    if (nextView == MotorInterface::ActiveView::RESEARCH_CENTER){
        viewInstance->switchView(ViewInterface::ActiveView::RESEARCH_CENTER,
                                 progress_, datex2Api_->getParkingHalls() );
    }
    else if (nextView == MotorInterface::ActiveView::MAIN_MENU){
        viewInstance->switchView(ViewInterface::ActiveView::MAIN_MENU, progress_,
                                 datex2Api_->getParkingHalls());
    }
    else if (nextView == MotorInterface::ActiveView::HEADQUARTERS){
        progress_.updateCompletition();
        viewInstance->switchView(ViewInterface::ActiveView::HEADQUARTERS, progress_,
                                 datex2Api_->getParkingHalls());
    }
    else if (nextView == MotorInterface::ActiveView::WORLD_MAP){
        viewInstance->switchView(ViewInterface::ActiveView::WORLD_MAP, progress_,
                                 datex2Api_->getParkingHalls());
    }
    else if (nextView == MotorInterface::ActiveView::BATTLE_MAP){

        viewInstance->switchView(ViewInterface::ActiveView::BATTLE_MAP, progress_,
                                 datex2Api_->getParkingHalls());
        // Ukkelit kartalle
        QList<int> playableCharactersLocations;
        QList<int> enemyCharactersLocations;
        QList<int> enemyCharactersHealth;

        for (auto character : *(battleMap_->listPlayerCharacters())) {
            playableCharactersLocations.append(battleMap_->getCharacterTile(character));
        }

        for (auto enemy : *(battleMap_->listEnemyCharacters())) {
            enemyCharactersLocations.append(battleMap_->getCharacterTile(enemy));
            enemyCharactersHealth.append(enemy->getMaxHP());
        }

        viewInstance->initializeCharactersToMap(playableCharactersLocations,
                                                enemyCharactersLocations,
                                                enemyCharactersHealth);

    }
    else if (nextView == MotorInterface::ActiveView::INVENTORY){
        viewInstance->switchView(ViewInterface::ActiveView::INVENTORY, progress_,
                                 datex2Api_->getParkingHalls());
    }
    return;
}

// Lataa talletus
void Motor::loadGame() {
    // Ladataan peli.
    qDebug() << "Peli ladattu saveslotista " + QString::number(saveSlot_);
    progress_.loadGame(saveSlot_ + 1);
}

void Motor::saveAndExit() {
    qDebug() << "Peli tallennettu saveslottiin " + QString::number(saveSlot_);
    progress_.saveGame(saveSlot_);
    switchView(MotorInterface::ActiveView::MAIN_MENU);
}

// Taisteluruudun metodit
// Valitse aktiivinen hahmo
void Motor::selectCharacter() {
    return;
}

// Yritä hyökkäystä kohteeseen
void Motor::attackTarget() {
    return;
}

// Vaihda aktiivista esinettä
void Motor::changeItem() {
    return;
}

// Yritä liikkua kohteeseen
void Motor::moveTo(bool isPlayerCharacter, int index, int startTile, int targetTile) {
    if (battleMap_->moveCharacter(isPlayerCharacter, index, startTile, targetTile)) {
        viewInstance->isMovePermitted(true);

        QList<int> playableCharactersLocations;
        QList<int> enemyCharactersLocations;
        for (auto character : *(battleMap_->listPlayerCharacters())) {
            playableCharactersLocations.append(battleMap_->getCharacterTile(character));
        }
        for (auto enemy : *(battleMap_->listEnemyCharacters())) {
            enemyCharactersLocations.append(battleMap_->getCharacterTile(enemy));
        }

        viewInstance->updateCharactersLocations(playableCharactersLocations,
                                                enemyCharactersLocations);
        viewInstance->nextTurn();
    }

    else {
        viewInstance->isMovePermitted(false);
    }
}

void Motor::attackTo(bool isPlayerCharacter, int index, int startTile, int targetTile) {
    if(battleMap_->performAttack((*battleMap_->listPlayerCharacters())[index],
                                 startTile, targetTile)){
        viewInstance->isAttackPermitted(true);
    }

    else {
        viewInstance->isAttackPermitted(true);
    }
}

// Lopeta vuoro
void Motor::endTurn() {
    delay();
    battleAi_->performTurn();
    battleMap_->nextTurn();

    return;
}

void Motor::healTeam(int cost) {
    progress_.useMoney(cost);

    for(auto character : progress_.getListOfCharacters()){
        character.get()->fillHealth();
    }
    progress_.updateCharactersProgress();
}

void Motor::healCharacter(int index, int cost) {
    progress_.useMoney(cost);
    progress_.getListOfCharacters()[index].get()->fillHealth();
    progress_.updateCharactersProgress();

}

void Motor::battleFinished(int battleScore) {
    qDebug()<< "TAISTELU VOITETTU";
    progress_.addMoney(battleScore * 100);
    datex2Api_->getParkingHalls()[activeHall_]->setTaken(true);
    auto takenHallId = datex2Api_->getParkingHalls()[activeHall_]->getId();

    progress_.takeHall(takenHallId);

    // Tuhotaan taisteluinstanssi ja AI
    delete battleMap_;
    battleMap_ = nullptr;
    delete battleAi_;
    battleAi_ = nullptr;

    viewInstance->battleOver(takenHallId, battleScore*100);

    if(checkWinningCondition()){
        gameWon_ = true;
    }

}

void Motor::enemyMoved() {
    QList<int> playableCharactersLocations;
    QList<int> enemyCharactersLocations;

    for (auto character : *(battleMap_->listPlayerCharacters())) {
        playableCharactersLocations.append(battleMap_->getCharacterTile(character));
    }

    for (auto enemy : *(battleMap_->listEnemyCharacters())) {
        enemyCharactersLocations.append(battleMap_->getCharacterTile(enemy));
    }

    viewInstance->updateCharactersLocations(playableCharactersLocations,
                                            enemyCharactersLocations);

    delay();
    return;
}

void Motor::enemyAttacking(int attackingTile, int attackedTile) {
    QList<int> playableCharactersHealths;
    QList<int> playableCharactersMaxHealths;
    QList<int> playableCharactersAps;
    QList<int> enemyCharactersHealths;
    QList<int> enemyCharactersAps;

    for (auto character : *(battleMap_->listPlayerCharacters())) {    
        playableCharactersHealths.append(character->getCurrentHP());
        playableCharactersAps.append(character->getCurrentActionPoints());
        playableCharactersMaxHealths.append(character->getMaxHP());
    }

    for (auto enemy : *(battleMap_->listEnemyCharacters())) {
        enemyCharactersHealths.append(enemy->getCurrentHP());
        enemyCharactersAps.append(enemy->getCurrentActionPoints());
    }

    viewInstance->characterAttacking(playableCharactersHealths,playableCharactersMaxHealths,
                                     playableCharactersAps,
                                     enemyCharactersAps,
                                     enemyCharactersHealths, attackingTile,
                                     attackedTile);

    delay();
    delay();

    return;
}

void Motor::enemyTurnOver() {
    viewInstance->enemyTurnOver();
}

void Motor::updateEnemyTurnLocation(int tile) {
    viewInstance->updateEnemyTurnLocation(tile);
}

void Motor::delaySeconds(int seconds) {
    for(int i = 0; i != seconds; i++){
        delay();
    }
}


void Motor::itemResearched(QString name, int cost) {
    progress_.newItemResearched(name, cost);
    viewInstance->updateResearchCenterPropertys(progress_);
    progress_.updateCompletition();
}


void Motor::itemEquipped(int characterIndex, QString itemName) {
    progress_.equipItem(characterIndex, itemName);
    progress_.updateCharactersProgress();
    viewInstance->updateInventoryPropertys(progress_);
}

void Motor::checkGameStatus() {
    if(gameWon_ == true){
        viewInstance->gameWon("The city is liberated!");
    }
    else if(gameLost_ == true){
        switchView(MotorInterface::ActiveView::WORLD_MAP);
        viewInstance->gameOver("\nYou died. Game over");
    }
}


void Motor::updateHallsRequested() {
    datex2Api_->updateAllParkingHalls();
    updateHallDataTimer_->start(60000);

}


void Motor::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool Motor::checkWinningCondition(){
    if (progress_.getControlledHalls().size() == totalHalls_){
        return true;
    } else {
        return false;
    }
}

void Motor::battleOver(QString hallName, int prizeMoney) {
    viewInstance->battleOver(hallName, prizeMoney);
}

void Motor::playerLost(){
    gameLost_ = true;
    checkGameStatus();
}
