import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Item {
    id:mainWindow
    // Signaalit pelin aloittamiseksi ja lopettamiseksi
    signal startGame(bool start)
    signal exitGame(bool exit)

    ApplicationWindow {
        objectName: "window"
        id:mainView
        visible: true

        width: 800
        minimumWidth: width
        maximumWidth: width

        height: 600
        minimumHeight: height
        maximumHeight: height
        title: qsTr("Berrywood Park")

        // Signaalit pelin aloittamiseksi ja lopettamiseksi
        signal startGame(bool start)
        signal exitGame(bool exit)

        Image {
                id: imageMenuBackground
                anchors.fill: parent
                z: -1
                source: "qrc:/pics/syndicate_main_menu.jpg"
            }

        Column {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                spacing: 20

                Rectangle {
                    id: rectStart
                    width: 400
                    height: 70
                    color: "#00cd00"
                    Text {
                        id: textStart
                        anchors.centerIn: parent
                        text: qsTr("PLAY THE GAME")
                        font.pixelSize: 22
                    }
                    MouseArea {
                        id: areaStart
                        width: 400
                        height: 70
                        visible: true
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: startGame(true)
                    }
                }

                Rectangle {
                    id: rectExit
                    width: 400
                    height: 70
                    color: "#00cd00"
                    Text {
                        id: textExit
                        anchors.centerIn: parent
                        text: qsTr("EXIT")
                        font.pixelSize: 22
                    }

                    MouseArea {
                        id: areaExit
                        width: 400
                        height: 70
                        visible: true
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: exitGame(true)
                    }
                }

        }
    }
}
