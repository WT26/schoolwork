import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
Item {
    signal toResearchCenter(bool status);
    signal toWorldMap(bool status);
    signal toInventory(bool status);
    signal saveAndExit();
    signal healTeam(int cost);
    signal healCharacter(int index, int cost);

    property var playerSelected: 1

    property var ammoCost: 20
    property var healthCost: 1

    property var showingWarning: false

    ApplicationWindow {
        objectName: "window"
        id:headquarters
        visible: true

        width: 800
        minimumWidth: width
        maximumWidth: width

        height: 600
        minimumHeight: height
        maximumHeight: height
        title: qsTr("Berrywood Park")

        property var playerNames: ["X", "X", "X", "X"]
        property var playerHealths: []
        property var playerMaxHealths: []
        property var playerApsLeft: []
        property var playerApsFull: []
        property var playerWeapons: []
        property var playerArmors: []
        property var playerImplants: []

        property var money: 0

        property var gameCompletion: 0

        property var totalPlaytime: 0

        property var enemiesKilled: 0

        property var itemsTotal: 0
        property var itemsResearched: 0

        property var weaponsResearched: 0
        property var weaponsTotal: 0

        property var controllingParkinghalls: 0
        property var totalParkinghalls: 0

        property var armorsResearched: 0
        property var armorsTotal: 0

        property var implantsResearched:0
        property var implantsTotal: 0

        property var secretsFound: 0
        property var secretsTotal: 0


        Image {
                id: imageMenuBackground
                anchors.fill: parent
                z: -1
                source: "qrc:/pics/syndicate_base_bg.png"
        }
        Text {
            id: textNotEnoughmoney
            z: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: (showingWarning) ? qsTr("WARNING! Not enough money") : qsTr("")
            font.family: "Helvetica"
            font.pointSize: 25
            font.bold: true
            color: "red"
            Timer {
                    id: warningTimer
                    interval: 2000; running: false; repeat: false
                    onTriggered: showingWarning = false
            }
        }
        Item{
            id: itemToMap
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50

            Image {
                    id: imageToMap
                    anchors.fill: parent
                    z: -1
                    source: "qrc:/pics/syndicate_base_to_map_button.png"
            }
            Text {
                id: textToMap
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("TO MAP")
                font.family: "Helvetica"
                font.pointSize: 18
                font.bold: true
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    toWorldMap(true)
                }
            }
        }
        Rectangle {
            id: rectPaddingTop
            anchors.top: itemToMap.bottom
            height: 10
            color: "transparent"
        }
        Rectangle {
            id: rectPaddingBottom
            anchors.bottom: parent.bottom
            height: 10
            color: "transparent"
        }
        Rectangle {
            id: rectPaddingLeft
            anchors.left: parent.left
            width: 10
            color: "transparent"
        }
        Rectangle {
            id: rectPaddingRight
            anchors.right: parent.right
            width: 10
            color: "transparent"
        }

        Rectangle {
            id: rectSaveAndExit
            anchors.left: rectPaddingLeft.right
            anchors.bottom: rectPaddingBottom.top
            height: 168
            width: 200
            color: "transparent"
            border.color: "white"
            Image {
                id: imageSaveAndExit
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                z: -1
                source: "qrc:/pics/syndicate_save_and_exit_hq.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    saveAndExit()
                }
            }
        }
        Rectangle {
            id: rectPaddingTopOfSave
            anchors.bottom: rectSaveAndExit.top
            height: 10
            color: "transparent"
        }
        Rectangle {
            id: rectStatistics
            anchors.top: rectPaddingTop.bottom
            anchors.left: rectPaddingLeft.right
            anchors.bottom: rectPaddingTopOfSave.top
            width: 200
            color: "transparent"
            border.color: "white"
            Rectangle {
                id: rectPaddingStatisticsLeft
                color: "transparent"
                anchors.left: parent.left
                width: 5
            }
            Text {
                id: textStatisticsHeader
                anchors.horizontalCenter: rectStatistics.horizontalCenter
                text: qsTr("STATISTICS")
                font.family: "Helvetica"
                font.pointSize: 18
                font.underline: true
                color: "white"
            }
            Column {
                id: columnStatistics
                anchors.left: rectPaddingStatisticsLeft.right
                anchors.top: textStatisticsHeader.bottom
                spacing: 5
                Text {
                    id: textStatisticsGameCompletion
                    text: qsTr("\nGame Completion: ") +
                          headquarters.gameCompletion + qsTr("%")
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textStatisticsParkinghallControl
                    text: qsTr("Parking Hall Control: ") +
                          headquarters.controllingParkinghalls + qsTr("/") +
                          headquarters.totalParkinghalls
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textStatisticsItemsResearched
                    text: qsTr("Items Researched: ") +
                          headquarters.itemsResearched + qsTr("/") +
                          headquarters.itemsTotal
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textStatisticsWeaponsResearched
                    text: qsTr("Weapons Researched: ") +
                          headquarters.weaponsResearched + qsTr("/") +
                          headquarters.weaponsTotal
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textStatisticsArmorsResearched
                    text: qsTr("Armors Researched: ") +
                          headquarters.armorsResearched + qsTr("/") +
                          headquarters.armorsTotal
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textStatisticsImplantsResearched
                    text: qsTr("Implants Researched: ") +
                          headquarters.implantsResearched + qsTr("/") +
                          headquarters.implantsTotal
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textStatisticsSecretsFound
                    text: qsTr("Secrets Found: ") +
                          headquarters.secretsFound + qsTr("/") +
                          headquarters.secretsTotal
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textStatisticsEnemiesKilled
                    text: qsTr("Total Enemies Killed: ") +
                          headquarters.enemiesKilled
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textStatisticsTotalPlaytime
                    text: qsTr("Total Playtime: ") +
                          headquarters.totalPlaytime + qsTr(" min")
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
            }
        }
        Rectangle {
            id: rectPaddingStatistics
            anchors.left: rectStatistics.right
            width: 10
            color: "transparent"
        }
        Row {
            id: rowCharacters
            anchors.left: rectPaddingStatistics.right
            anchors.top: rectPaddingTop.bottom
            spacing: 10

            Column {
                id: columnCharacterOne
                Text {
                    id: textCharacterOne
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: headquarters.playerNames[0]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14

                }
                Item {
                    id: itemCharacterOne
                    height: 100
                    width: 75
                    Image {
                        id: imageCharacterOne
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_char_1_2.png"
                    }
                    MouseArea {
                        id: mouseareaCharacterOne
                        anchors.fill: parent
                        onClicked: {
                            playerSelected = 1
                        }
                    }
                }
                ProgressBar {
                    id: progressHealthCharOne
                    value: headquarters.playerHealths[0] / headquarters.playerMaxHealths[0]

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
                    value: headquarters.playerApsLeft[0] / headquarters.playerApsFull[0]

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
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: (playerSelected == 1) ? true : false
                    height: 15
                    width: 30
                    AnimatedImage {
                        id: imageCharacterOneSelection
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_selection_gif.gif"
                    }
                }
            }
            Column {
                id: columnCharacterTwo
                Text {
                    id: textCharacterTwo
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: headquarters.playerNames[1]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14

                }
                Item {
                    id: itemCharacterTwo
                    height: 100
                    width: 75
                    Image {
                        id: imageCharacterTwo
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_char_2_2.png"
                    }
                    MouseArea {
                        id: mouseareaCharacterTwo
                        anchors.fill: parent
                        onClicked: {
                            playerSelected = 2
                        }
                    }
                }
                ProgressBar {
                    id: progressHealthCharTwo
                    value: headquarters.playerHealths[1] / headquarters.playerMaxHealths[1]

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
                    value: headquarters.playerApsLeft[1] / headquarters.playerApsFull[1]

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
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: (playerSelected == 2) ? true : false
                    height: 15
                    width: 30
                    AnimatedImage {
                        id: imageCharacterTwoSelection
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_selection_gif.gif"
                    }
                }
            }
            Column {
                id: columnCharacterThree
                Text {
                    id: textCharacterThree
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: headquarters.playerNames[2]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14

                }
                Item {
                    id: itemCharacterThree
                    height: 100
                    width: 75
                    Image {
                        id: imageCharacterThree
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_char_3_2.png"
                    }
                    MouseArea {
                        id: mouseareaCharacterThree
                        anchors.fill: parent
                        onClicked: {
                            playerSelected = 3
                        }
                    }
                }
                ProgressBar {
                    id: progressHealthCharThree
                    value: headquarters.playerHealths[2] / headquarters.playerMaxHealths[2]

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
                    value: headquarters.playerApsLeft[2] / headquarters.playerApsFull[2]

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
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: (playerSelected == 3) ? true : false
                    height: 15
                    width: 30
                    AnimatedImage {
                        id: imageCharacterThreeSelection
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_selection_gif.gif"
                    }
                }

            }
            Column {
                id: columnCharacterFour
                Text {
                    id: textCharacterFour
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: headquarters.playerNames[3]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14

                }
                Item {
                    id: itemCharacterFour
                    height: 100
                    width: 75
                    Image {
                        id: imageCharacterFour
                        anchors.fill: parent
                        source: "qrc:/pics/syndicate_char_4_2.png"
                    }
                    MouseArea {
                        id: mouseareaCharacterFour
                        anchors.fill: parent
                        onClicked: {
                            playerSelected = 4
                        }
                    }
                }
                ProgressBar {
                    id: progressHealthCharFour
                    value: headquarters.playerHealths[3] / headquarters.playerMaxHealths[3]

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
                    value: headquarters.playerApsLeft[3] / headquarters.playerApsFull[3]

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
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: (playerSelected == 4) ? true : false
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
        Rectangle {
            id: rectPaddingCharactersRight
            anchors.left: rowCharacters.right
            width: 10
            color: "transparent"
        }
        Rectangle {
            id: rectQuickButtons
            anchors.top: rectPaddingTop.bottom
            anchors.left: rectPaddingCharactersRight.right
            anchors.right: rectPaddingRight.left
            height: 350
            color: "transparent"
            border.color: "white"

            Column {
                id: columnQuickButtons
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 5

                Rectangle {
                    id: rectColumnQuickButtonsPadding
                    height: 5
                    width: 5
                    color: "transparent"
                }
                Button {
                    id: buttonFillEveryonesHealth
                    width: 200
                    height: 30
                    text: qsTr("FILL EVERYONE'S HEALTH: $") +
                          healthCost *
                          ((headquarters.playerMaxHealths[0] - headquarters.playerHealths[0]) +
                           (headquarters.playerMaxHealths[1]  - headquarters.playerHealths[1]) +
                           (headquarters.playerMaxHealths[2]  - headquarters.playerHealths[2]) +
                           (headquarters.playerMaxHealths[3]  - headquarters.playerHealths[3]))
                    onClicked:{

                        if(headquarters.money >= healthCost *
                                ((headquarters.playerMaxHealths[0]  - headquarters.playerHealths[0]) +
                                 (headquarters.playerMaxHealths[1]  - headquarters.playerHealths[1]) +
                                 (headquarters.playerMaxHealths[2]  - headquarters.playerHealths[2]) +
                                 (headquarters.playerMaxHealths[3]  - headquarters.playerHealths[3]))){
                            var index = 0
                            while(index < 4) {
                                headquarters.money -= healthCost *
                                        (100 -
                                         headquarters.playerHealths[index])
                                headquarters.playerHealths[index] = headquarters.playerMaxHealths[index]
                                playerSelected = playerSelected
                                headquarters.playerHealths = headquarters.playerHealths
                                index += 1
                            }
                            healTeam(healthCost *
                                     ((100 - headquarters.playerHealths[0]) +
                                      (100 - headquarters.playerHealths[1]) +
                                      (100 - headquarters.playerHealths[2]) +
                                      (100 - headquarters.playerHealths[3])))

                        }
                        else {
                            showingWarning = true;
                            warningTimer.start();
                        }

                    }
                }
            }
        }
        Rectangle {
            id: rectPaddingCharactersBottom
            anchors.top: rowCharacters.bottom
            height: 10
            color: "transparent"
        }
        Rectangle {
            id: rectCharactersState
            anchors.top: rectPaddingCharactersBottom.bottom
            anchors.left: rectPaddingStatistics.right
            anchors.right: rowCharacters.right
            anchors.bottom: rectPaddingBottom.top
            color: "transparent"
            border.color: "white"
            Rectangle {
                id: rectCash
                anchors.top: parent.top
                anchors.right: parent.right
                color: "transparent"
                border.color: "white"
                width: 200
                height: 30
                Text {
                    id: textDollar
                    anchors.top: parent.top
                    text: qsTr(" $ ")
                    font.family: "Helvetica"
                    font.pointSize: 18
                    font.bold: true
                    color: "white"
                }
                Text {
                    id: textCash
                    anchors.right: parent.right
                    anchors.top: parent.top
                    text: qsTr("") + headquarters.money + " "
                    font.family: "Helvetica"
                    font.pointSize: 18
                    font.bold: true
                    color: "white"
                }
            }
            Rectangle {
                id: rectPaddingCharacterStateLeft
                anchors.left: rectCharactersState.left
                width: 5
                color: "transparent"
            }
            Rectangle {
                id: rectPaddingCharacterStateRight
                anchors.right: rectCharactersState.right
                width: 5
                color: "transparent"
            }

            Text {
                id: textCharName
                anchors.top: rectCash.bottom
                anchors.left: rectPaddingCharacterStateLeft.right
                text: headquarters.playerNames[playerSelected - 1]
                color: "white"
                font.family: "Helvetica"
                font.pointSize: 17
                font.bold: true
                font.underline: true
            }
            Button {
                anchors.top: textCharName.verticalCenter
                anchors.right: rectPaddingCharacterStateRight.left
                id: buttonToInventory
                width: 150
                height: 50
                text: qsTr("INVENTORY")
                onClicked: {
                    toInventory(true)
                }
            }
            Column {
                id: columnCharacterState
                anchors.top: buttonToInventory.bottom
                anchors.left: rectPaddingCharacterStateLeft.right
                spacing: 5
                Text {
                    id: textCharHealth
                    text: qsTr("Health: ") + headquarters.playerHealths[playerSelected - 1] + qsTr("/") + headquarters.playerMaxHealths[playerSelected - 1]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14
                }
                Text {
                    id: textCharAmmo
                    text: qsTr("AP: ") + headquarters.playerApsLeft[playerSelected - 1] + qsTr("/") + headquarters.playerApsFull[playerSelected - 1]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14
                }
                Text {
                    id: textCharWeapon
                    text: qsTr("Weapon: ") + headquarters.playerWeapons[playerSelected - 1]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14
                }
                Text {
                    id: textCharArmor
                    text: qsTr("Armor: ") + headquarters.playerArmors[playerSelected - 1]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14
                }
                Text {
                    id: textCharImplant
                    text: qsTr("Implant: ") + headquarters.playerImplants[playerSelected - 1] + qsTr("\n")
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 14
                }
            }
            Column {
                id: columnCharacterStateButtons
                anchors.top: columnCharacterState.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10
                Button {
                    id: buttonFillHealth
                    width: 150
                    height: 35
                    text: qsTr("FILL HEALTH: $") +
                          healthCost * (headquarters.playerMaxHealths[playerSelected - 1] - headquarters.playerHealths[playerSelected - 1])
                    onClicked: {
                        if(headquarters.money >= healthCost *
                                (headquarters.playerMaxHealths[playerSelected - 1] - headquarters.playerHealths[playerSelected - 1])){
                            headquarters.money -= healthCost *
                                    (headquarters.playerMaxHealths[playerSelected - 1] - headquarters.playerHealths[playerSelected - 1])
                            headquarters.playerHealths[playerSelected - 1] = headquarters.playerMaxHealths[playerSelected - 1]
                            headquarters.playerHealths = headquarters.playerHealths
                            playerSelected = playerSelected
                            healCharacter(playerSelected - 1, healthCost * (100 - headquarters.playerHealths[playerSelected - 1]));
                        }
                        else {
                            showingWarning = true;
                            warningTimer.start();
                        }
                    }
                }
            }
        }
        Rectangle {
            id: rectPaddingQuickButtonsBottom
            anchors.top: rectQuickButtons.bottom
            height: 10
            color: "transparent"
        }
        Rectangle {
            id: rectToResearchCenter
            anchors.top: rectPaddingQuickButtonsBottom.bottom
            anchors.left: rectPaddingCharactersRight.right
            anchors.right: rectPaddingRight.left
            anchors.bottom: rectPaddingBottom.top
            color: "transparent"
            border.color: "white"
            Image {
                    id: imageToResearchCenter
                    anchors.fill: parent
                    z: -1
                    source: "qrc:/pics/syndicate_to_research_center_button.png"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    toResearchCenter(true)
                }
            }
        }
    }
}
