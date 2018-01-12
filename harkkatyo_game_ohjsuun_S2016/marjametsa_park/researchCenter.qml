import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Item {
    signal toHeadquarters(bool status);
    signal itemResearched(string name, int cost);

    property var itemName: "LIGHT ARMOR"

    property var owned: false

    property var cost: 0

    property var minDamaqe: 7
    property var maxDamaqe: 25

    property var minRange: 1
    property var maxRange: 10

    property var shootAp: 15
    property var reloadAp: 5

    property var clipSize: 15
    property var spread: 10

    property var timerVal: 0
    property var timerTimer: 1

    property var showingWarning: false
    property var showingBoughtMessage: false
    property var showingOwnedWarning: false



    ApplicationWindow {
        objectName: "window"
        id:researchCenter
        visible: true

        width: 800
        minimumWidth: width
        maximumWidth: width

        height: 600
        minimumHeight: height
        maximumHeight: height
        title: qsTr("Berrywood Park")

        property var money: 0

        property var itemType: ["ARMORS", "WEAPONS", "IMPLANTS"]
        property var selectedItemType: "ARMORS"
        property var selectedItem: "LIGHT ARMOR"

        property var weaponsNames: ["KNIFE", "KNIFE", "KNIFE", "KNIFE", "KNIFE", "KNIFE"]
        property var weaponsPrices: [0,0,0,0,0,0]
        property var weaponsTypes: ["MELEE", "MELEE", "MELEE", "MELEE", "MELEE", "MELEE"]
        property var weaponsMinDamage: [0,0,0,0,0,0]
        property var weaponsMaxDamage: [0,0,0,0,0,0]
        property var weaponsMinRange: [0,0,0,0,0,0]
        property var weaponsMaxRange: [0,0,0,0,0,0]
        property var weaponsShootAp: [0,0,0,0,0,0]
        property var weaponsReloadAp: [0,0,0,0,0,0]
        property var weaponsSpread: [0,0,0,0,0,0]
        property var weaponsClipsize: [0,0,0,0,0,0]
        property var weaponsOwned: [true, false, false, false, false, false]
        property var weaponsAmount: weaponsNames.length

        property var armorsNames: ["LIGHT ARMOR", "LIGHT ARMOR", "LIGHT ARMOR"]
        property var armorsPrices: [0,0,0]
        property var armorsDefences: [0,0,0]
        property var armorsOwned: [false, false, false]
        property var armorsAmount: armorsNames.length

        property var implantsNames: ["RANGE BOOST", "RANGE BOOST", "RANGE BOOST"]
        property var implantsPrices: [0,0,0]
        property var implantsRangeBoost: [0,0,0]
        property var implantsAttackBoost: [0,0,0]
        property var implantsDefenceBoost: [0,0,0]
        property var implantsOwned: [false, false, false]
        property var implantsAmount: implantsNames.length

        property var armorDefence: 0
        property var attackBoost: 0
        property var rangeBoost: 0
        property var defenceBoost: 0

        Image {
                id: imageResearchCenterBackground
                anchors.fill: parent
                z: -2
                source: "qrc:/pics/temp_research_center_bg.png"
        }
        Image {
                id: imageResearchCenterBgGlow
                anchors.fill: parent
                z: -1
                opacity: timerVal
                source: "qrc:/pics/temp_research_center_bg_glow.jpg"
                Timer {
                        interval: 100; running: true; repeat: true
                        onTriggered: timerVal += timerTimer * 0.01
                }
                Timer {
                        interval: 2000; running: true; repeat: true
                        onTriggered: timerTimer = timerTimer * -1
                }

        }

        Rectangle {
            id: rectSelectedItem
            width: 200
            height: 160
            border.color: "white"
            anchors.left: parent.left
            anchors.top: parent.top
            color: "gray"
            Rectangle {
                id: rectSelectedItemTextRect
                width: 200
                height: 30
                border.color: "white"
                anchors.left: parent.left
                anchors.top: parent.top
                color: "gray"
                Text {
                    id: textSelectedItem
                    z: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    text: itemName
                    font.family: "Helvetica"
                    font.pointSize: 13
                    font.bold: true
                    color: "white"
                }
            }


            Image {
                id: imageSelectedItem
                z: 9
                anchors.bottom: rectSelectedItem.bottom

                source: "qrc:/pics/syndicate_light_armor.png"
                function picChanged(){
                    if(researchCenter.selectedItem == "LIGHT ARMOR"){
                        imageSelectedItem.source = "qrc:/pics/syndicate_light_armor.png"
                    }
                    else if(researchCenter.selectedItem == "MEDIUM ARMOR") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_medium_armor.png"
                    }
                    else if(researchCenter.selectedItem == "HEAVY ARMOR") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_heavy_armor.png"
                    }
                    else if(researchCenter.selectedItem == "KNIFE") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_knife_2.png"
                    }
                    else if(researchCenter.selectedItem == "PISTOL") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_pistol_2.png"
                    }
                    else if(researchCenter.selectedItem == "SMG") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_smg.png"
                    }
                    else if(researchCenter.selectedItem == "ASSAULT RIFLE") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_assault_rifle.png"
                    }
                    else if(researchCenter.selectedItem == "MACHINE GUN") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_machine_gun.png"
                    }
                    else if(researchCenter.selectedItem == "SNIPER") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_sniper.png"
                    }
                    else if(researchCenter.selectedItem == "ATTACK BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_attack_boost.png"
                    }
                    else if(researchCenter.selectedItem == "SUPER ATTACK BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_super_attack_boost.png"
                    }
                    else if(researchCenter.selectedItem == "DEFENCE BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_defence_boost.png"
                    }
                    else if(researchCenter.selectedItem == "SUPER DEFENCE BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_super_defence_boost.png"
                    }
                    else if(researchCenter.selectedItem == "RANGE BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_range_boost.png"
                    }
                    else if(researchCenter.selectedItem == "SUPER RANGE BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_super_range_boost.png"
                    }
                    else {
                        imageSelectedItem.source = "qrc:/pics/syndicate_questionmark.png"
                    }
                }
            }
        }

        Rectangle {
            id: rectItemInfo
            anchors.top: rectSelectedItem.bottom
            anchors.left: parent.left
            border.color: "white"
            color: "transparent"

            width: 200
            height: 340
            //color: "#007210"
            opacity: 100

            Column{
                id: textGunItemInfo
                anchors.horizontalCenter: parent.horizontalCenter
                visible: (researchCenter.selectedItemType == "WEAPONS" ? true : false)
                spacing: 1

                Text {
                    id: textGunItemInfoHeader
                    text: qsTr("SPECIFICATION")
                    font.family: "Helvetica"
                    font.pointSize: 14
                    color: "white"
                    font.underline: true
                }
                Text {
                    id: textGunItemDamage
                    text: qsTr("Damage: " + minDamaqe + "-" +  maxDamaqe)
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textGunItemRange
                    text: qsTr("Range: " + minRange + "-" +  maxRange)
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textGunItemShootAp
                    text: qsTr("Shoot AP: " + shootAp)
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textGunItemReloadAp
                    text: qsTr("Reload AP: " + reloadAp)
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textGunItemSpread
                    text: qsTr("Spread: " + spread)
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textGunItemClipsize
                    text: qsTr("Clip size: " + clipSize)
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
            }
            Column{
                id: textToolItemInfo
                anchors.horizontalCenter: parent.horizontalCenter
                visible: (researchCenter.selectedItemType == "IMPLANTS" ? true : false)
                spacing: 1

                Text {
                    id: textToolItemInfoHeader
                    text: qsTr("SPECIFICATION")
                    font.family: "Helvetica"
                    font.pointSize: 14
                    color: "white"
                    font.underline: true
                }
                Text {
                    id: textImplantAttackBoost
                    text: qsTr("Attack boost: ") + researchCenter.attackBoost
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textImplantRangeBoost
                    text: qsTr("Range boost: ") + researchCenter.rangeBoost
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textImplantDefenceBoost
                    text: qsTr("Defence boost: ") + researchCenter.defenceBoost
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
            }
            Column{
                id: textModItemInfo
                anchors.horizontalCenter: parent.horizontalCenter
                visible: (researchCenter.selectedItemType == "ARMORS" ? true : false)
                spacing: 1

                Text {
                    id: textModItemInfoHeader
                    text: qsTr("SPECIFICATION")
                    font.family: "Helvetica"
                    font.pointSize: 14
                    color: "white"
                    font.underline: true
                }
                Text {
                    id: textArmorDefence
                    text: qsTr("Defence: ") + researchCenter.armorDefence
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
            }
            Text {
                id: textItemOwnership
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: textGunItemInfo.bottom
                text: (owned) ? qsTr("\n\nYou already own this item") : qsTr("")
                font.family: "Helvetica"
                font.pointSize: 10
                color: "white"
                font.italic: true
            }
         }
         Rectangle {
             id: rectBackButton
             anchors.left: parent.left
             anchors.top: rectItemInfo.bottom
             width: 200
             height: 100
             Image {
                     id: imageBackButton
                     anchors.fill: parent
                     z: 10
                     source: "qrc:/pics/syndicate_research_center_back_button.png"
             }
             MouseArea {
                 anchors.fill: parent
                 onClicked: toHeadquarters(true)
             }
         }
         Rectangle {
             id: rectHeader
             width: 400
             height: 100
             anchors.top: parent.top
             anchors.left: rectSelectedItem.right
             color: "transparent"
             border.color: "white"

             Text {
                 id: textResearchCenterHeader
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.verticalCenter: parent.verticalCenter
                 text: qsTr("RESEARCH CENTER")
                 font.family: "Helvetica"
                 font.pointSize: 20
                 font.bold: true
                 color: "white"
             }

         }

         Rectangle {
             id: rectResearch
             width: 400
             height: 500
             anchors.left: rectSelectedItem.right
             anchors.top: rectHeader.bottom
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
                     text: qsTr("") + researchCenter.money + " "
                     font.family: "Helvetica"
                     font.pointSize: 18
                     font.bold: true
                     color: "white"
                 }

             }

             Rectangle {
                 id: rectResearchPadding
                 anchors.top: parent.top
                 anchors.right: parent.right
                 anchors.left: parent.left
                 height: 100
                 z: -100
                 color: "transparent"

             }

             Text {
                 id: textFunding
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.top: rectResearchPadding.bottom
                 text: qsTr("Total Research cost:")
                 font.family: "Helvetica"
                 font.pointSize: 18
                 font.bold: true
                 color: "white"
             }

             Text {
                 id: textResearchCost
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.top: textFunding.bottom
                 text: qsTr("$ ") + cost

                 font.family: "Helvetica"
                 font.pointSize: 16
                 color: "white"
             }

             Text {
                 id: textResearchNotEnoughmoney
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.verticalCenter: parent.verticalCenter
                 text: (showingWarning) ? qsTr("WARNING! Not enough money") : qsTr("")
                 font.family: "Helvetica"
                 font.pointSize: 15
                 font.bold: true
                 color: "red"
                 Timer {
                         id: warningTimer
                         interval: 2000; running: false; repeat: false
                         onTriggered: showingWarning = false
                 }
             }
             Text {
                 id: textResearchAlreadyOwned
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.verticalCenter: parent.verticalCenter
                 text: (showingOwnedWarning) ? qsTr("You already own this item.") : qsTr("")
                 font.family: "Helvetica"
                 font.pointSize: 15
                 font.bold: true
                 color: "yellow"
                 Timer {
                         id: warningOwnedTimer
                         interval: 2000; running: false; repeat: false
                         onTriggered: showingOwnedWarning = false
                 }
             }
             Text {
                 id: textResearchItemBought
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.verticalCenter: parent.verticalCenter
                 text: (showingBoughtMessage) ? qsTr("You bought ") + itemName : qsTr("")
                 font.family: "Helvetica"
                 font.pointSize: 15
                 font.bold: true
                 color: "green"
                 Timer {
                         id: boughtMessageTimer
                         interval: 2000; running: false; repeat: false
                         onTriggered: showingBoughtMessage = false
                 }
             }


             Rectangle {
                 id: rectResearchButton
                 anchors.horizontalCenter: parent.horizontalCenter
                 color: "transparent"
                 width: 200
                 height: 100
                 y:350
                 Image {
                         id: imageResearchButon
                         anchors.fill: parent
                         z: -1
                         source: "qrc:/pics/syndicate_research_button.png"
                 }
                 MouseArea {
                     anchors.fill: parent
                     onClicked: {
                         function researchItem(){
                             if(owned){
                                 showingOwnedWarning = true
                                 showingWarning = false
                                 showingBoughtMessage = false
                                 warningOwnedTimer.start()

                             }
                             else if(cost > researchCenter.money){
                                 showingWarning = true
                                 showingBoughtMessage = false
                                 showingOwnedWarning = false
                                 warningTimer.start()
                             }
                             else {
                                 researchCenter.money -= cost
                                 owned = true
                                 itemResearched(researchCenter.selectedItem, cost)
                                 boughtMessageTimer.start()
                                 showingBoughtMessage = true
                                 showingWarning = false
                                 showingOwnedWarning = false
                             }
                         }
                         researchItem()
                     }
                 }
             }
         }
         Rectangle {
             id: rectResearchList
             width: 200
             height: 600
             anchors.left: rectResearch.right
             anchors.top: parent.top
             color: "transparent"

             Column {
                 id: columnResearchList
                 spacing: 3

                 Button {
                     id: buttonArmors
                     width: 200
                     height: 66
                     text: qsTr("ARMORS")
                     checkable: true
                     checked: (researchCenter.selectedItemType == "ARMORS" ? true : false)
                     onClicked:{
                        researchCenter.selectedItemType = "ARMORS"
                        researchCenter.selectedItem = researchCenter.armorsNames[0]
                        itemName = researchCenter.armorsNames[0]
                        owned = researchCenter.armorsOwned[0]
                        cost = researchCenter.armorsPrices[0]
                        researchCenter.armorDefence = researchCenter.armorsDefences[0]
                        showingWarning = false
                        showingBoughtMessage = false
                        imageSelectedItem.picChanged()

                     }
                 }

                 Button {
                     id: buttonWeapons
                     width: 200
                     height: 67
                     text: qsTr("WEAPONS")
                     checkable: true
                     checked: (researchCenter.selectedItemType == "WEAPONS" ? true : false)
                     onClicked:{
                        researchCenter.selectedItemType = "WEAPONS"
                        researchCenter.selectedItem = researchCenter.weaponsNames[0]
                        itemName = researchCenter.weaponsNames[0]
                        owned = researchCenter.weaponsOwned[0]
                        cost = researchCenter.weaponsPrices[0]
                        minDamaqe = researchCenter.weaponsMinDamage[0]
                        maxDamaqe = researchCenter.weaponsMaxDamage[0]
                        minRange = researchCenter.weaponsMinRange[0]
                        maxRange = researchCenter.weaponsMaxRange[0]
                        shootAp = researchCenter.weaponsShootAp[0]
                        reloadAp = researchCenter.weaponsReloadAp[0]
                        spread = researchCenter.weaponsSpread[0]
                        clipSize = researchCenter.weaponsClipsize[0]
                        showingWarning = false
                        showingBoughtMessage = false
                        imageSelectedItem.picChanged()

                     }
                 }

                 Button {
                     id: buttonImplants
                     width: 200
                     height: 66
                     text: qsTr("IMPLANTS")
                     checkable: true
                     checked: (researchCenter.selectedItemType == "IMPLANTS" ? true : false)
                     onClicked:{
                        researchCenter.selectedItemType = "IMPLANTS"
                        researchCenter.selectedItem = researchCenter.implantsNames[0]
                        itemName = researchCenter.implantsNames[0]
                        owned = researchCenter.implantsOwned[0]
                        cost = researchCenter.implantsPrices[0]
                        researchCenter.attackBoost = researchCenter.implantsAttackBoost[0]
                        researchCenter.defenceBoost = researchCenter.implantsDefenceBoost[0]
                        researchCenter.rangeBoost = researchCenter.implantsRangeBoost[0]
                        showingWarning = false
                        showingBoughtMessage = false
                        imageSelectedItem.picChanged()

                     }
                 }
             }

             Text {
                 id: textItemList
                 anchors.horizontalCenter: parent.horizontalCenter
                 anchors.top: columnResearchList.bottom
                 text: qsTr("\nLIST:")
                 font.bold: true
                 font.family: "Helvetica"
                 font.pointSize: 18
                 color: "white"
             }

             Column {
                 id: columnGunList
                 anchors.top: textItemList.bottom
                 visible: (researchCenter.selectedItemType == "WEAPONS" ? true : false)
                 spacing: 3

                 Repeater {
                     model: researchCenter.weaponsAmount
                     Button {
                         width: 200
                         height: 30
                         text: researchCenter.weaponsNames[index]
                         checkable: true
                         checked: (researchCenter.selectedItem == researchCenter.weaponsNames[index] ? true : false)
                         onClicked:{
                             researchCenter.selectedItem = researchCenter.weaponsNames[index]
                             itemName = researchCenter.selectedItem
                             cost = researchCenter.weaponsPrices[index]
                             owned = researchCenter.weaponsOwned[index]
                             minDamaqe = researchCenter.weaponsMinDamage[index]
                             maxDamaqe = researchCenter.weaponsMaxDamage[index]
                             minRange = researchCenter.weaponsMinRange[index]
                             maxRange = researchCenter.weaponsMaxRange[index]
                             shootAp = researchCenter.weaponsShootAp[index]
                             reloadAp = researchCenter.weaponsReloadAp[index]
                             spread = researchCenter.weaponsSpread[index]
                             clipSize = researchCenter.weaponsClipsize[index]
                             showingWarning = false
                             showingBoughtMessage = false
                             imageSelectedItem.picChanged()

                        }
                    }
                 }
             }
             Column {
                 id: columnModList
                 anchors.top: textItemList.bottom
                 visible: (researchCenter.selectedItemType == "ARMORS" ? true : false)
                 spacing: 3

                 Repeater {
                     model: researchCenter.armorsAmount
                     Button {
                         width: 200
                         height: 30
                         text: researchCenter.armorsNames[index]
                         checkable: true
                         checked: (researchCenter.selectedItem == researchCenter.armorsNames[index] ? true : false)
                         onClicked:{
                            researchCenter.selectedItem = researchCenter.armorsNames[index]
                            itemName = researchCenter.selectedItem
                            cost = researchCenter.armorsPrices[index]
                            owned = researchCenter.armorsOwned[index]
                            researchCenter.armorDefence = researchCenter.armorsDefences[index]
                            showingWarning = false
                            showingBoughtMessage = false
                            imageSelectedItem.picChanged()
                         }
                     }
                 }


             }
             Column {
                 id: columnToolList
                 anchors.top: textItemList.bottom
                 visible: (researchCenter.selectedItemType == "IMPLANTS" ? true : false)
                 spacing: 3

                 Repeater {
                     model: researchCenter.implantsAmount
                     Button {
                         width: 200
                         height: 30
                         text: researchCenter.implantsNames[index]
                         checkable: true
                         checked: (researchCenter.selectedItem == researchCenter.implantsNames[index] ? true : false)
                         onClicked:{
                            researchCenter.selectedItem = researchCenter.implantsNames[index]
                            itemName = researchCenter.selectedItem
                            cost = researchCenter.implantsPrices[index]
                            owned = researchCenter.implantsOwned[index]
                            researchCenter.attackBoost = researchCenter.implantsAttackBoost[index]
                            researchCenter.defenceBoost = researchCenter.implantsDefenceBoost[index]
                            researchCenter.rangeBoost = researchCenter.implantsRangeBoost[index]
                            showingWarning = false
                            showingBoughtMessage = false
                            imageSelectedItem.picChanged()

                         }
                     }
                 }
             }
         }
    }
}
