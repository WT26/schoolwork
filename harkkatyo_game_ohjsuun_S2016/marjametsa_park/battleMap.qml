import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
Item {
    signal toWorldMap(bool status);
    signal moveToTile(bool isPlayerCharacter, int index, int startTile, int targetTile);
    signal attackToTile(bool isPlayerCharacter, int index, int startTile, int targetTile);
    signal endTurn(bool status);
    signal checkGameStatus();

    property var isAttackSelected: false

    ApplicationWindow {
        objectName: "window"
        id: battleMap
        visible: true

        width: 800
        minimumWidth: width
        maximumWidth: width

        height: 600
        minimumHeight: height
        maximumHeight: height
        title: qsTr("Berrywood Park")

        property var enemiesLeft: (enemyCharactersAt.length > 0) ? true : false
        property var isPlayerTurn: false

        property var playerCharactersAt: [0, 0, 0, 0]
        property var enemyCharactersAt: [0]

        property var playerHealths: [0, 0, 0, 0]
        property var playerMaxHealths: [0, 0, 0, 0]
        property var playerApsLeft: [0, 0, 0, 0]
        property var playerApsFull: [0, 0, 0, 0]

        property var enemyHealths: [0,0,0,0]
        property var enemyApsLeft: [0]

        property var turn: 3 // 0-3 player characters turn
        property var nextTurn: true

        property var turnChanged: true
        property var currentTurnTile: 0

        property var attackingTile: -1
        property var attackedTile: -1
        property var enemyAttacked: false
        property var playExplosion: false
        property var playShot: false
        property var playShotDone: false

        property var showMovementWarning: !movePermission ? true : false
        property var movePermission: true

        property var showAttackWarning: !attackPermission ? true : false
        property var attackPermission: true

        property var battleEnded: false
        property var hallId: ""
        property var prizeMoney: 0

        property var escaped: false




        Rectangle {
            anchors.fill: parent
            color: "#262626"
        }

        Timer {
            id: timerMovementWarning
            interval: 2000; running: battleMap.showMovementWarning; repeat: false
            onTriggered: battleMap.movePermission = true
        }
        Timer {
            id: timerAttackWarning
            interval: 2000; running: battleMap.showAttackWarning; repeat: false
            onTriggered: battleMap.attackPermission = true
        }
        Timer {
            // TOIMII SLOTTINA->PAREMPI RATKAISU
            id: timerNextTurn
            interval: 30; running: battleMap.nextTurn; repeat: false
            onTriggered: {
                console.log("")
                if(battleMap.turn === 3){
                    battleMap.currentTurnTile = battleMap.playerCharactersAt[battleMap.turn];
                    battleMap.turn = 0;
                    battleMap.nextTurn = false;
                    battleMap.isPlayerTurn = false;
                    itemEnemyTurnBanner.visible = true;
                    battleMap.turnChanged = true;
                    endTurn(true);
                }
                else if (battleMap.playerHealths[battleMap.turn + 1] === 0) {
                    console.log("Current turn")
                    console.log(battleMap.turn + 1)
                    console.log("Current player health")
                    console.log(battleMap.playerHealths[battleMap.turn + 1])
                    console.log(battleMap.playerHealths[battleMap.turn + 1] / battleMap.playerMaxHealths[battleMap.turn + 1])
                    console.log(battleMap.playerMaxHealths[battleMap.turn + 1])
                    battleMap.nextTurn = true;
                    battleMap.turn += 1;
                    battleMap.turnChanged = true;

                } else {
                    console.log("Current turn")
                    console.log(battleMap.turn + 1)
                    console.log("Current player health")
                    console.log(battleMap.playerHealths[battleMap.turn + 1])
                    console.log(battleMap.playerHealths[battleMap.turn + 1] / battleMap.playerMaxHealths[battleMap.turn + 1])
                    console.log(battleMap.playerMaxHealths[battleMap.turn + 1])
                    battleMap.currentTurnTile = battleMap.playerCharactersAt[battleMap.turn];
                    battleMap.turn += 1;
                    battleMap.turnChanged = true;
                    battleMap.nextTurn = false;
                }
            }
        }
        Timer {
            id: timerExploded
            interval: 0; running: battleMap.playShotDone; repeat: false
            onTriggered: {
                battleMap.playExplosion = true;
                itemExplosion.x = repeaterGrid.itemAt(battleMap.attackedTile).x + 13
                itemExplosion.y = repeaterGrid.itemAt(battleMap.attackedTile).y + 15
                gifExplosion.currentFrame = 0;
                gifExplosion.playing = true;
                battleMap.playShotDone = false;
            }
        }
        Timer {
            id: timerExplosionOver
            interval: 0; running: gifExplosion.currentFrame >= 38; repeat: false
            onTriggered: {
                battleMap.playExplosion = false;
                gifExplosion.playing = false;
            }
        }
        Timer {
            id: timerShot
            interval: 0; running: battleMap.enemyAttacked; repeat: false
            onTriggered: {
                battleMap.playShot = true;
                itemShotRight.x = repeaterGrid.itemAt(battleMap.attackingTile).x + 13
                itemShotRight.y = repeaterGrid.itemAt(battleMap.attackingTile).y + 30
                gifShotRight.currentFrame = 0;
                gifShotRight.playing = true;
                battleMap.enemyAttacked = false;
            }
        }
        Timer {
            id: timerShotOver
            interval: 0; running: gifShotRight.currentFrame >= 9; repeat: false
            onTriggered: {
                battleMap.playShot = false;
                gifShotRight.playing = false;
                battleMap.playShotDone = true;
            }
        }
        Timer {
            id: timerIsPlayerTurn
            interval: 0; running: battleMap.isPlayerTurn; repeat: false
            onTriggered: {
                itemEnemyTurnBanner.visible = false;
                battleMap.turn = 0;
                battleMap.turnChanged = true;
            }
        }
        Timer {
            id: timerTurnChanged
            interval: 0; running: battleMap.turnChanged; repeat: false
            onTriggered: {
                if(battleMap.isPlayerTurn){
                    itemTurnSelection.x = repeaterGrid.itemAt(battleMap.playerCharactersAt[battleMap.turn]).x + 12
                    itemTurnSelection.y = repeaterGrid.itemAt(battleMap.playerCharactersAt[battleMap.turn]).y + 19
                }
                else {
                    itemTurnSelection.x = repeaterGrid.itemAt(battleMap.currentTurnTile).x + 12
                    itemTurnSelection.y = repeaterGrid.itemAt(battleMap.currentTurnTile).y + 19
                }
                battleMap.turnChanged = false;
            }
        }
        Timer {
            id: timerBattleEnded
            interval: 0; running: battleMap.battleEnded; repeat: false
            onTriggered: {
                if(battleMap.enemiesLeft){
                    itemBattleEndedMessage.visible = true;
                }
                else {
                    itemBattleEndedMessage.visible = true;
                }
                battleMap.battleEnded = false;
            }
        }
        Item {
            id: itemBattleEndedMessage
            anchors.fill: parent
            visible: false
            x: 50
            y: 50
            z: 20
            Image {
                id: imageDebriefing
                opacity: 0.8
                anchors.fill: parent
                source: "qrc:/pics/syndicate_debriefing.png"
            }
            Text {
                id: textMissionStatus
                x: 500
                y: 190
                text: (battleMap.escaped) ? qsTr("ESCAPED") : qsTr("COMPLETED")
                font.family: "Helvetica"
                font.pointSize: 15
                font.bold: true
                color: (battleMap.escaped) ? "red" : "#00ff00"
            }
            Text {
                id: textTotalKills
                x: 500
                y: 215
                text: qsTr("x")
                font.family: "Helvetica"
                font.pointSize: 15
                font.bold: true
                color: "#00ff00"
            }
            Text {
                id: textTotalLoot
                x: 500
                y: 240
                text: (battleMap.escaped) ? qsTr("0") : battleMap.prizeMoney
                font.family: "Helvetica"
                font.pointSize: 15
                font.bold: true
                color: "yellow"
            }
            Text {
                id: textHallControl
                x: 225
                y: 300
                text: (battleMap.escaped) ? "" : qsTr("You are now controlling: ") + battleMap.hallId
                font.family: "Helvetica"
                font.pointSize: 13
                font.bold: true
                color: "#00ff00"
            }
            MouseArea {
                z:99
                anchors.fill: parent
                onClicked: {
                }
                Rectangle {
                    id: rectAccept
                    anchors.horizontalCenter: parent.horizontalCenter
                    y: 350
                    width: 170
                    height: 50
                    color: "transparent"
                    Image {
                        id: imageSaveAndExit
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        z: 20
                        source: "qrc:/pics/syndicate_accept_button.png"
                    }

                    MouseArea {
                        z:100
                        anchors.fill: parent
                        onClicked: {
                            itemBattleEndedMessage.visible = false;
                            battleMap.escaped = false;
                            toWorldMap(true);
                            checkGameStatus();
                        }
                    }
                }
            }
        }
        Item {
            id: itemExplosion
            height: 50
            width: 50
            x: 50
            y: 50
            z: 10
            AnimatedImage {
                id: gifExplosion
                visible: battleMap.playExplosion ? true : false
                playing: false
                anchors.fill: parent
                source: "qrc:/pics/syndicate_explosion.gif"
            }
        }
        Item {
            id: itemShotRight
            height: 25
            width: 75
            x: 50
            y: 50
            z: 10
            AnimatedImage {
                id: gifShotRight
                visible: battleMap.playShot ? true : false
                playing: false
                anchors.fill: parent
                source: "qrc:/pics/syndicate_shoot_right.gif"
            }
        }
        Item {
            id: itemTurnSelection
            height: 48
            width: 48
            x: 50
            y: 50
            z: 11
            opacity: 0.2
            AnimatedImage {
                id: gifTurnSelection
                visible: true
                anchors.fill: parent
                source: "qrc:/pics/syndicate_battle_selection.gif"
            }
        }

        Rectangle {
            id: rectPaddingTop
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 10
            color: "transparent"
        }
        Rectangle {
            id: rectPaddingBottom
            anchors.bottom: rectCharacterMenu.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 10
            color: "transparent"
        }
        Rectangle {
            id: rectPaddingLeft
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: rectCharacterMenu.top
            width: 10
            color: "transparent"
        }
        Rectangle {
            id: rectPaddingRight
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: rectCharacterMenu.top
            height: 10
            width: 10
            color: "transparent"
        }

        Rectangle {
            id: rectBattleArea
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: rectCharacterMenu.top
            color: "white"
            Image {
                id: imageBattleAreaBg
                anchors.fill: parent
                source: "qrc:/pics/syndicate_battlemap_bg.png"
            }
            MouseArea {
                id: mouseAreaBattle
                anchors.fill: parent
                cursorShape: isAttackSelected ? Qt.CrossCursor : Qt.UpArrowCursor
                enabled: false

                readonly property bool containsMouse: {
                    var relativePos = mapFromItem(mouseAreaBattle, mouseAreaBattle.mouseX, mouseAreaBattle.mouseY);
                    return contains(Qt.point(relativePos.x, relativePos.y));
                }
            }
            Repeater {
                id: repeaterEnemyPlacements
                model: battleMap.enemyCharactersAt.length
                Image {
                    id: imageEnemyCharacter
                    x: repeaterGrid.itemAt(battleMap.enemyCharactersAt[index]).x + 18
                    y: repeaterGrid.itemAt(battleMap.enemyCharactersAt[index]).y + 27
                    width: 35
                    height: 35
                    source: "qrc:/pics/syndicate_battle_icon_enemy.png"
                    visible: {

                        if (battleMap.enemyHealths[index] < 1)
                            visible: false
                        else
                            visible: true
                        }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.top
                        text: battleMap.enemyHealths[index]
                        color: "white"
                        font.family: "Helvetica"
                        font.pointSize: 15
                        font.bold: true

                    }
                }
            }
            Grid {
                id: gridBattle
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                rows: 8
                columns: 15
                spacing: 4
                Repeater {
                    id: repeaterGrid
                    model: 120
                    Rectangle {
                        width: 48
                        height: 48
                        color: "transparent"
                        Rectangle {
                            anchors.fill: parent
                            color: "white"
                            opacity: 0.05
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter

                            //text: index
                            color: "white"
                            opacity: 0.2
                        }
                        MouseArea {
                            id: mouseAreaTile
                            cursorShape: isAttackSelected ? Qt.CrossCursor : Qt.UpArrowCursor

                            anchors.fill: parent
                            onClicked: {
                                if (isAttackSelected && battleMap.isPlayerTurn) {
                                    attackToTile(battleMap.isPlayerTurn,
                                                 battleMap.turn,
                                                 battleMap.playerCharactersAt[battleMap.turn],
                                                 index)
                                }
                                else if(!isAttackSelected && battleMap.isPlayerTurn){
                                    moveToTile(battleMap.isPlayerTurn,
                                                      battleMap.turn,
                                                      battleMap.playerCharactersAt[battleMap.turn],
                                                      index)
                                }
                            }
                        }
                        Rectangle {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter

                            height: 30
                            width: 30
                            visible:  (index == battleMap.playerCharactersAt[0]) ? true :
                                      (index == battleMap.playerCharactersAt[1]) ? true :
                                      (index == battleMap.playerCharactersAt[2]) ? true :
                                      (index == battleMap.playerCharactersAt[3]) ? true :
                                      false
                            Image {
                                anchors.fill: parent
                                source:     (index == battleMap.playerCharactersAt[0]) ? "qrc:/pics/syndicate_battle_icon_1.png" :
                                            (index == battleMap.playerCharactersAt[1]) ? "qrc:/pics/syndicate_battle_icon_2.png" :
                                            (index == battleMap.playerCharactersAt[2]) ? "qrc:/pics/syndicate_battle_icon_3.png" :
                                            (index == battleMap.playerCharactersAt[3]) ? "qrc:/pics/syndicate_battle_icon_4.png" :
                                            (index == battleMap.enemyCharactersAt[0]) ? "qrc:/pics/syndicate_questionmark.png" :
                                            (index == battleMap.enemyCharactersAt[1]) ? "qrc:/pics/syndicate_questionmark.png" :
                                            (index == battleMap.enemyCharactersAt[2]) ? "qrc:/pics/syndicate_questionmark.png" :
                                            (index == battleMap.enemyCharactersAt[3]) ? "qrc:/pics/syndicate_questionmark.png" : "qrc:/pics/syndicate_empty.png"
                            }

                        }
                    }
                }
            }
        }
        Text {
            id: textMoveIsNotPermitted
            anchors.horizontalCenter: rectBattleArea.horizontalCenter
            anchors.verticalCenter: rectBattleArea.verticalCenter
            text: "MOVE IS NOT PERMITTED"
            visible: battleMap.showMovementWarning ? true : false
            color: "red"
            font.family: "Helvetica"
            font.pointSize: 30
            font.bold: true
        }

        Text {
            id: textAttackIsNotPermitted
            anchors.horizontalCenter: rectBattleArea.horizontalCenter
            anchors.verticalCenter: rectBattleArea.verticalCenter
            text: "ATTACK IS NOT PERMITTED"
            visible: battleMap.showAttackWarning ? true : false
            color: "red"
            font.family: "Helvetica"
            font.pointSize: 30
            font.bold: true
        }

        Rectangle {
            id: rectCharacterMenu
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 150
            Image {
                id: imageCharacterMenuBg
                anchors.fill: parent
                source: "qrc:/pics/syndicate_battlemap_bg2.png"
            }
            Rectangle {
                id: rectPaddingLeftOfRow
                anchors.left: battleMap.left
                width: 10
                color: "transparent"
            }
            Rectangle {
                id: rectPaddingLeftOfColumn
                anchors.right: columnActions.left
                width: 10
                color: "transparent"
            }
            Row {
                anchors.top: rectPaddingCharMenuTop.bottom
                anchors.left: rectPaddingLeftOfRow.right

                id: rowCharacters
                spacing: 4
                Rectangle {
                    id: rectChar1
                    height: 100
                    width: 75
                    Image {
                        id: imageChar1
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_char_1_2.png"
                    }
                    ProgressBar {
                        id: progressHealthCharOne
                        anchors.top: imageChar1.bottom
                        value: battleMap.playerHealths[0] / battleMap.playerMaxHealths[0]

                        background: Rectangle {
                            id: healthLeftCharOne
                            implicitWidth: 75
                            implicitHeight: 4
                            x: progressHealthCharOne.leftPadding
                            y: parent.height / 2 - height / 2
                            color: "#e6e6e6"
                            radius: 2
                        }

                        contentItem: Item {
                            implicitWidth: healthLeftCharOne.implicitWidth
                            implicitHeight: healthLeftCharOne.implicitHeight
                            Rectangle {
                                width: progressHealthCharOne.visualPosition * healthLeftCharOne.width
                                height: parent.height
                                radius: 2
                                color: "#17a81a"
                            }
                        }
                    }
                    ProgressBar {
                        id: progressAmmoCharOne
                        anchors.top: progressHealthCharOne.bottom
                        value: battleMap.playerApsLeft[0] / battleMap.playerApsFull[0]

                        background: Rectangle {
                            id: ammoLeftCharOne
                            implicitWidth: 75
                            implicitHeight: 4
                            x: progressAmmoCharOne.leftPadding
                            y: parent.height / 2 - height / 2
                            color: "#e6e6e6"
                            radius: 2
                        }

                        contentItem: Item {
                            implicitWidth: ammoLeftCharOne.implicitWidth
                            implicitHeight: ammoLeftCharOne.implicitHeight
                            Rectangle {
                                width: progressAmmoCharOne.visualPosition * ammoLeftCharOne.width
                                height: parent.height
                                radius: 2
                                color: "#7b7a00"
                            }
                        }
                    }
                    Item {
                        id: itemCharacterOneSelection
                        anchors.top: progressAmmoCharOne.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: (battleMap.turn == 0 && battleMap.isPlayerTurn) ? true : false
                        height: 15
                        width: 30
                        AnimatedImage {
                            id: imageCharacterOneSelection
                            anchors.fill: parent
                            source: "qrc:/pics/syndicate_selection_gif.gif"
                        }
                    }

                }
                Rectangle {
                    id: rectChar2
                    height: 100
                    width: 75
                    Image {
                        id: imageChar2
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_char_2_2.png"
                    }
                    ProgressBar {
                        id: progressHealthCharTwo
                        anchors.top: imageChar2.bottom
                        value: battleMap.playerHealths[1] /  battleMap.playerMaxHealths[1]

                        background: Rectangle {
                            id: healthLeftCharTwo
                            implicitWidth: 75
                            implicitHeight: 4
                            x: progressHealthCharTwo.leftPadding
                            y: parent.height / 2 - height / 2
                            color: "#e6e6e6"
                            radius: 2
                        }

                        contentItem: Item {
                            implicitWidth: healthLeftCharTwo.implicitWidth
                            implicitHeight: healthLeftCharTwo.implicitHeight
                            Rectangle {
                                width: progressHealthCharTwo.visualPosition * healthLeftCharTwo.width
                                height: parent.height
                                radius: 2
                                color: "#17a81a"
                            }
                        }
                    }
                    ProgressBar {
                        id: progressAmmoCharTwo
                        anchors.top: progressHealthCharTwo.bottom
                        value: battleMap.playerApsLeft[1] / battleMap.playerApsFull[1]

                        background: Rectangle {
                            id: ammoLeftCharTwo
                            implicitWidth: 75
                            implicitHeight: 4
                            x: progressAmmoCharTwo.leftPadding
                            y: parent.height / 2 - height / 2
                            color: "#e6e6e6"
                            radius: 2
                        }

                        contentItem: Item {
                            implicitWidth: ammoLeftCharTwo.implicitWidth
                            implicitHeight: ammoLeftCharTwo.implicitHeight
                            Rectangle {
                                width: progressAmmoCharTwo.visualPosition * ammoLeftCharTwo.width
                                height: parent.height
                                radius: 2
                                color: "#7b7a00"
                            }
                        }
                    }

                    Item {
                        id: itemCharacterTwoSelection
                        anchors.top: progressAmmoCharTwo.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: (battleMap.turn == 1 && battleMap.isPlayerTurn) ? true : false
                        height: 15
                        width: 30
                        AnimatedImage {
                            id: imageCharacterTwoSelection
                            anchors.fill: parent
                            source: "qrc:/pics/syndicate_selection_gif.gif"
                        }
                    }

                }
                Rectangle {
                    id: rectChar3
                    height: 100
                    width: 75
                    Image {
                        id: imageChar3
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_char_3_2.png"
                    }
                    ProgressBar {
                        id: progressHealthCharThree
                        anchors.top: imageChar3.bottom
                        value: battleMap.playerHealths[2] / battleMap.playerMaxHealths[2]
                        background: Rectangle {
                            id: healthLeftCharThree
                            implicitWidth: 75
                            implicitHeight: 4
                            x: progressHealthCharThree.leftPadding
                            y: parent.height / 2 - height / 2
                            color: "#e6e6e6"
                            radius: 2
                        }

                        contentItem: Item {
                            implicitWidth: healthLeftCharThree.implicitWidth
                            implicitHeight: healthLeftCharThree.implicitHeight
                            Rectangle {
                                width: progressHealthCharThree.visualPosition * healthLeftCharThree.width
                                height: parent.height
                                radius: 2
                                color: "#17a81a"
                            }
                        }
                    }
                    ProgressBar {
                        id: progressAmmoCharThree
                        anchors.top: progressHealthCharThree.bottom
                        value: battleMap.playerApsLeft[2] / battleMap.playerApsFull[2]

                        background: Rectangle {
                            id: ammoLeftCharThree
                            implicitWidth: 75
                            implicitHeight: 4
                            x: progressAmmoCharThree.leftPadding
                            y: parent.height / 2 - height / 2
                            color: "#e6e6e6"
                            radius: 2
                        }

                        contentItem: Item {
                            implicitWidth: ammoLeftCharThree.implicitWidth
                            implicitHeight: ammoLeftCharThree.implicitHeight
                            Rectangle {
                                width: progressAmmoCharThree.visualPosition * ammoLeftCharThree.width
                                height: parent.height
                                radius: 2
                                color: "#7b7a00"
                            }
                        }
                    }

                    Item {
                        id: itemCharacterThreeSelection
                        anchors.top: progressAmmoCharThree.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: (battleMap.turn == 2 && battleMap.isPlayerTurn) ? true : false
                        height: 15
                        width: 30
                        AnimatedImage {
                            id: imageCharacterThreeSelection
                            anchors.fill: parent
                            source: "qrc:/pics/syndicate_selection_gif.gif"
                        }
                    }

                }
                Rectangle {
                    id: rectChar4
                    height: 100
                    width: 75
                    Image {
                        id: imageChar4
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_char_4_2.png"
                    }
                    ProgressBar {
                        id: progressHealthCharFour
                        anchors.top: rectChar4.bottom
                        value: battleMap.playerHealths[3] / battleMap.playerMaxHealths[3]
                        //to: battleMap.playerMaxHealths[3]
                        background: Rectangle {
                            id: healthLeftCharFour
                            implicitWidth: 75
                            implicitHeight: 4
                            x: progressHealthCharFour.leftPadding
                            y: parent.height / 2 - height / 2
                            color: "#e6e6e6"
                            radius: 2
                        }

                        contentItem: Item {
                            implicitWidth: healthLeftCharFour.implicitWidth
                            implicitHeight: healthLeftCharFour.implicitHeight
                            Rectangle {
                                width: progressHealthCharFour.visualPosition * healthLeftCharFour.width
                                height: parent.height
                                radius: 2
                                color: "#17a81a"
                            }
                        }
                    }
                    ProgressBar {
                        id: progressAmmoCharFour
                        anchors.top: progressHealthCharFour.bottom
                        value: battleMap.playerApsLeft[3] / battleMap.playerApsFull[3]

                        background: Rectangle {
                            id: ammoLeftCharFour
                            implicitWidth: 75
                            implicitHeight: 4
                            x: progressAmmoCharFour.leftPadding
                            y: parent.height / 2 - height / 2
                            color: "#e6e6e6"
                            radius: 2
                        }

                        contentItem: Item {
                            implicitWidth: ammoLeftCharFour.implicitWidth
                            implicitHeight: ammoLeftCharFour.implicitHeight
                            Rectangle {
                                width: progressAmmoCharFour.visualPosition * ammoLeftCharFour.width
                                height: parent.height
                                radius: 2
                                color: "#7b7a00"
                            }
                        }
                    }

                    Item {
                        id: itemCharacterFourSelection
                        anchors.top: progressAmmoCharFour.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: (battleMap.turn === 3 && battleMap.isPlayerTurn) ? true : false
                        height: 15
                        width: 30
                        AnimatedImage {
                            id: imageCharacterFourSelection
                            anchors.fill: parent
                            source: "qrc:/pics/syndicate_selection_gif.gif"
                        }
                    }

                }
            }
            Column {
                id: columnActions
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: rectPaddingCharMenuTop.bottom
                spacing: 4
                Button {
                    id: buttonMove
                    text: qsTr("MOVE")
                    height: 25
                    enabled: battleMap.isPlayerTurn ? true : false
                    checked: (!isAttackSelected ? true : false)
                    onClicked: isAttackSelected = false
                }
                Button {
                    id: buttonAttack
                    text: qsTr("ATTACK")
                    height: 25
                    enabled: battleMap.isPlayerTurn ? true : false
                    checked: (isAttackSelected ? true : false)
                    onClicked: isAttackSelected = true
                }
                Button {
                    id: buttonEndTurn
                    text: qsTr("END TURN")
                    height: 25
                    enabled: battleMap.isPlayerTurn ? true : false
                    onClicked: {
                        //battleMap.isPlayerTurn = false;
                        //itemEnemyTurnBanner.visible = true;
                        battleMap.nextTurn = true;
                    }
                }
                Button {
                    id: buttonEscape
                    text: qsTr("ESCAPE")
                    height: 25
                    enabled: battleMap.isPlayerTurn ? true : false
                    onClicked: {
                        battleMap.escaped = true;
                        itemBattleEndedMessage.visible = true;
                    }
                }
            }
            Rectangle {
                id: rectPaddingColumnRight
                anchors.left: columnActions.right
                anchors.top: parent.top
                width: 10
                color: "transparent"
            }
            Rectangle {
                id: rectPaddingCharMenuTop
                anchors.top: parent.top
                height: 10
                color: "transparent"
            }
            Item {
                id: itemEnemyTurnBanner
                anchors.top: rectPaddingCharMenuTop.bottom
                anchors.left: rectPaddingColumnRight.right
                visible: battleMap.isPlayersTurn ? true : false
                height: 120
                width: 330
                z: 10
                AnimatedImage {
                    id: gifEnemysTurn
                    anchors.fill: parent
                    source: "qrc:/pics/syndicate_enemy_turn.gif"
                }
            }
            Image {
                id: imageNotEnemysTurn
                anchors.top: rectPaddingCharMenuTop.bottom
                anchors.left: rectPaddingColumnRight.right
                visible: battleMap.isPlayersTurn ? false : true
                z: 9

                source: "qrc:/pics/syndicate_not_enemy_turn.png"

            }
        }
    }
}
