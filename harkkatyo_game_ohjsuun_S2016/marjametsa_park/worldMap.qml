import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
Item {
    signal toMainMenu(bool status);
    signal toHeadquarters(bool status);
    signal toBattleMap(bool status, int parkinghall_index);
    signal saveAndExit();

    ApplicationWindow {
        objectName: "window"
        id:worldMap
        visible: true

        width: 800
        minimumWidth: width
        maximumWidth: width

        height: 600
        minimumHeight: height
        maximumHeight: height
        title: qsTr("Berrywood Park")

        property var closedX: []
        property var closedY: []
        property var closedLength: 0

        property var openedX: []
        property var openedY: []
        property var openedLength: 0

        property var hoveredHall: 0
        property var hallsNames: []
        property var hallsIds: []
        property var hallsVacant: []
        property var hallsOccupied: []
        property var hallsControlled: []

        property var showGameWonMessage: false
        property var gameWonMessage: ""

        property var showGameLostMessage: false
        property var gameLostMessage: ""

        Image {
                id: imageMenuBackground
                anchors.fill: parent
                z: -1
                source: "qrc:/pics/syndicate_tampere_map_2.png"
        }
        Timer {
            id: timerGameWonMessage
            interval: 0; running: worldMap.showGameWonMessage; repeat: false
            onTriggered: {
                textGameWonMessage.visible = true;
            }
        }
        Timer {
            id: timerGameLostMessage
            interval: 0; running: worldMap.showGameLostMessage; repeat: false
            onTriggered: {
                rectGameOver.visible = true
            }
        }
        Text {
            id: textGameWonMessage
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
            y: 40
            z: 99
            text: worldMap.gameWonMessage
            font.family: "Helvetica"
            font.pointSize: 18
            font.bold: true
            color: "white"
        }
        Rectangle {
           id: rectGameOver
           anchors.horizontalCenter:  parent.horizontalCenter
           anchors.verticalCenter:  parent.verticalCenter
           height: 200
           width: 300
           visible: false
           z: 20
           color: "transparent"
           border.color: "white"
           Rectangle {
              id: rectGameOverInside
              anchors.fill: parent
              color: "black"
              opacity: 0.7
           }
           Text {
               id: textGameOver
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.top: parent.top
               text: qsTr("GAME OVER!")
               font.family: "Helvetica"
               font.pointSize: 16
               font.underline: true
               color: "white"
           }
           Text {
               id: textGameOverMessage
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.top: textGameOver.bottom
               text: worldMap.gameLostMessage
               font.family: "Helvetica"
               font.pointSize: 16
               font.underline: true
               color: "white"
           }
           MouseArea {
               z:99
               height: 2000
               width: 1500
               x: -500
               y: -500
               onClicked: {
               }
               Button {
                   id: buttonReturnMainMenu
                   x: 600
                   y: 610
                   text: qsTr("Return Main Menu")
                   onClicked: toMainMenu(true)
               }
           }
        }
        Repeater {
            id: repeaterOpenHalls
            model: worldMap.openedLength
            Image {
                source: "qrc:/pics/syndicate_parking_icon_green.png"
                x: worldMap.openedX[index]
                y: worldMap.openedY[index]
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        toHeadquarters(true)
                    }
                    hoverEnabled: true
                    onEntered: {
                        worldMap.hoveredHall = index;
                        columnHallInfo.visible = true;
                    }
                    onExited: {
                        worldMap.hoveredHall = 0;
                        columnHallInfo.visible = false;
                    }
                }
            }
        }
        Repeater {
            id: repeaterClosedHalls
            model: worldMap.closedLength
            Image {
                source: "qrc:/pics/syndicate_parking_icon_red.png"
                x: worldMap.closedLength > 0 ? worldMap.closedX[index] : -100
                y:  worldMap.closedLength > 0 ? worldMap.closedY[index] : -100
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        toBattleMap(true, index)
                    }
                    hoverEnabled: true
                    onEntered: {
                        worldMap.hoveredHall = index;
                        columnHallInfo.visible = true;
                    }
                    onExited: {
                        worldMap.hoveredHall = 0;
                        columnHallInfo.visible = false;
                    }
                }
            }
        }


        Image {
                id: imageClouds1
                z: 10
                x:0
                opacity: 0.7
                source: "qrc:/pics/syndicate_clouds.png"
                Timer {
                        id: timerClouds1
                        interval: 100; running: true; repeat: true

                        function resetClouds(){
                            if(imageClouds1.x >= -850){
                                    imageClouds1.x -= 1
                            }
                            else {
                                imageClouds1.x = 1550
                            }
                        }
                        onTriggered: {
                            resetClouds()
                        }
                }
        }
        Image {
                id: imageClouds2
                z: 10
                x: imageClouds1.x + 800
                opacity: 0.7
                source: "qrc:/pics/syndicate_clouds_2.png"
                Timer {
                        id: timerClouds2
                        interval: 100; running: true; repeat: true

                        function resetClouds2(){
                            if(imageClouds2.x >= -850){
                                    imageClouds2.x -= 1
                            }
                            else {
                                imageClouds2.x = 1550
                            }
                        }
                        onTriggered: {
                            resetClouds2()
                        }
                }
        }
        Image {
                id: imageClouds3
                z: 10
                x: imageClouds1.x + 1600
                opacity: 0.7
                source: "qrc:/pics/syndicate_clouds.png"
                Timer {
                        id: timerClouds
                        interval: 100; running: true; repeat: true

                        function resetClouds3(){
                            if(imageClouds3.x >= -850){
                                    imageClouds3.x -= 1
                            }
                            else {
                                imageClouds3.x = 1550
                            }
                        }
                        onTriggered: {
                            resetClouds3()
                        }
                }
        }



        Rectangle {
           id: rectPaddingRight
           anchors.right: parent.right
           width: 10
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
           id: rectPaddingTop
           anchors.top: parent.top
           height: 15
           color: "transparent"
        }
        Rectangle {
           id: rectPaddingTopOfHq
           anchors.bottom: itemToHq.top
           width: 10
           height: 10
           color: "transparent"
        }
        Rectangle {
            id: itemSaveAndExit
            anchors.left: rectPaddingLeft.right
            anchors.top: rectPaddingTop.bottom
            height: 85
            width: 130
            color: "transparent"
            border.color: "white"
            Image {
                id: imageSaveAndExit
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                z: -1
                source: "qrc:/pics/syndicate_save_and_exit_map.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    saveAndExit()
                }
            }
        }


         Rectangle {
            id: rectInfoBox
            anchors.right: rectPaddingRight.left
            anchors.bottom: rectPaddingTopOfHq.top
            height: 300
            width: 200
            z: 20
            color: "transparent"
            border.color: "white"
            Rectangle {
               id: rectInfoBoxInside
               anchors.fill: parent
               color: "black"
               opacity: 0.7
            }
            Text {
                id: textHallInfoHeader
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                text: qsTr("INFORMATION")
                font.family: "Helvetica"
                font.pointSize: 16
                font.underline: true
                color: "white"
                visible: true
            }
            Rectangle {
               id: rectPaddingBottomInfo
               anchors.top: textHallInfoHeader.bottom
               width: 10
               height: 10
               color: "transparent"
            }
            Rectangle {
               id: rectPaddingLeftInfo
               anchors.left: rectInfoBox.left
               width: 10
               height: 10
               color: "transparent"
            }
            Rectangle {
               id: rectPaddingBottomInfoBox
               anchors.bottom: rectInfoBox.bottom
               width: 10
               height: 20
               color: "transparent"
            }
            Column {
                id: columnHallInfo
                anchors.top: rectPaddingBottomInfo.bottom
                anchors.left: rectPaddingLeftInfo.right

                visible: false

                spacing: 2
                Text {
                    id: textHallInfoName
                    text: qsTr("Name: ") + worldMap.hallsNames[worldMap.hoveredHall]
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textHallInfoId
                    text: qsTr("Id: ") + worldMap.hallsIds[worldMap.hoveredHall]
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: "white"
                }
                Text {
                    id: textHallInfoControl
                    text: (worldMap.hallsControlled[worldMap.hoveredHall]) ? qsTr("CONTROLLED") : qsTr("NOT CONTROLLED")
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: (worldMap.hallsControlled[worldMap.hoveredHall]) ? "green" : "red"
                }
                Text {
                    id: textHallInfoDanger
                    text: ((worldMap.hallsOccupied[worldMap.hoveredHall] /
                           (worldMap.hallsOccupied[worldMap.hoveredHall] +
                            worldMap.hallsVacant[worldMap.hoveredHall])) < 0.25) ? qsTr("DANGER: !") :
                            ((worldMap.hallsOccupied[worldMap.hoveredHall] /
                             (worldMap.hallsOccupied[worldMap.hoveredHall] +
                              worldMap.hallsVacant[worldMap.hoveredHall])) < 0.5) ? qsTr("DANGER: !!") : qsTr("DANGER: !!!")
                    font.family: "Helvetica"
                    font.pointSize: 10
                    color: ((worldMap.hallsOccupied[worldMap.hoveredHall] /
                             (worldMap.hallsOccupied[worldMap.hoveredHall] +
                              worldMap.hallsVacant[worldMap.hoveredHall])) < 0.25) ? "green" :
                              ((worldMap.hallsOccupied[worldMap.hoveredHall] /
                               (worldMap.hallsOccupied[worldMap.hoveredHall] +
                                worldMap.hallsVacant[worldMap.hoveredHall])) < 0.5) ? "yellow" : "red"
                }

            }
            Text {
                id: textHallInfoLoot
                visible: columnHallInfo.visible
                anchors.bottom: rectPaddingBottomInfoBox.top
                anchors.horizontalCenter: parent.horizontalCenter
                text: ((worldMap.hallsVacant[worldMap.hoveredHall] ) /
                       ((worldMap.hallsOccupied[worldMap.hoveredHall] +
                        worldMap.hallsVacant[worldMap.hoveredHall])) > 0.80) ? qsTr("LOOT: $") :
                        ((worldMap.hallsVacant[worldMap.hoveredHall]) /
                         ((worldMap.hallsOccupied[worldMap.hoveredHall] +
                          worldMap.hallsVacant[worldMap.hoveredHall])) > 0.60) ? qsTr("LOOT: $$") : qsTr("LOOT: $$$")
                font.family: "Helvetica"
                font.pointSize: (text == qsTr("LOOT: $")) ? 10 :
                                  (text == qsTr("LOOT: $$")) ? 13 : 16
                color: "yellow"
            }


         }
         Item{
             id: itemToHq
             anchors.bottom: parent.bottom
             anchors.left: parent.left
             anchors.right: parent.right
             height: 50
             z: 20

             Image {
                     id: imageToHq
                     anchors.fill: parent
                     z: -1
                     source: "qrc:/pics/syndicate_base_to_hq_button.png"
             }
             Text {
                 id: textToMap
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.verticalCenter: parent.verticalCenter
                 text: qsTr("TO HERVANTA HQ")
                 font.family: "Helvetica"
                 font.pointSize: 18
                 font.bold: true
                 color: "white"
             }
             MouseArea {
                 anchors.fill: parent
                 z: 10
                 onClicked: {
                     if(!worldMap.showGameLostMessage){
                         toHeadquarters(true)

                     }
                 }
             }
         }
    }
}
