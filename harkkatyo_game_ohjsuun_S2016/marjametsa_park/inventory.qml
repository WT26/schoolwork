import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Item {
    id:inventory
    // Signaalit pelin aloittamiseksi ja lopettamiseksi
    signal toHeadquarters(bool status);
    signal itemEquipped(int characterIndex, string weaponName);

    property var itemName: "NONE"

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

    ApplicationWindow {
        objectName: "window"
        id: inventoryWindow
        visible: true

        width: 800
        minimumWidth: width
        maximumWidth: width

        height: 600
        minimumHeight: height
        maximumHeight: height
        title: qsTr("Berrywood Park")

        property var itemType: ["ARMORS", "WEAPONS", "IMPLANTS"]
        property var selectedItemType: "NONE"
        property var selectedItem: "NONE"
        property var selectedCharacter: 0

        property var playerNames: ["X", "Y", "Z", "0"]
        property var playerWeapons: ["X", "X", "X", "X"]
        property var playerArmors: ["X", "X", "X", "X"]
        property var playerImplants: ["X", "X", "X", "X"]


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
                id: imageMenuBackground
                anchors.fill: parent
                z: -1
                source: "qrc:/pics/syndicate_inventory_bg_2.png"
        }
        Rectangle {
            id: rectPaddingTop
            anchors.top: parent.top
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

        Button {
            id: buttonBack
            width: 200
            height: 100
            anchors.left: rectPaddingLeft.right
            anchors.bottom: rectPaddingBottom.top
            text: qsTr("BACK")
            onClicked: toHeadquarters(true)
        }

        Rectangle {
            id: rectPaddingLeftOfBack
            anchors.left: buttonBack.right
            width: 10
            color: "transparent"
        }
        Button {
            id: buttonEquip
            width: 200
            height: 100
            anchors.left: rectPaddingLeftOfBack.right
            anchors.bottom: rectPaddingBottom.top
            enabled: (((inventoryWindow.selectedItemType == "ARMORS") &&
                      (inventoryWindow.selectedItem != inventoryWindow.playerArmors[inventoryWindow.selectedCharacter])) && owned ||
                      ((inventoryWindow.selectedItemType == "WEAPONS") &&
                      (inventoryWindow.selectedItem != inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter])) && owned ||
                      ((inventoryWindow.selectedItemType == "IMPLANTS") &&
                      (inventoryWindow.selectedItem != inventoryWindow.playerImplants[inventoryWindow.selectedCharacter])) && owned) ? true : false


            text: qsTr("EQUIP")
            onClicked: {
                if(inventoryWindow.selectedItemType == "ARMORS" ){
                    if( (owned) && (inventoryWindow.selectedItem != inventoryWindow.playerArmors[inventoryWindow.selectedCharacter])){
                        itemEquipped(inventoryWindow.selectedCharacter, inventoryWindow.selectedItem);
                    }
                    else if(!owned){
                        // TODO warning;
                    }
                }
                else if(inventoryWindow.selectedItemType == "WEAPONS" ){
                    if( (owned) && (inventoryWindow.selectedItem != inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter])){
                        itemEquipped(inventoryWindow.selectedCharacter, inventoryWindow.selectedItem);
                    }
                    else if(!owned){
                        // TODO warning;
                    }
                }
                else if(inventoryWindow.selectedItemType == "IMPLANTS" ){
                    if( (owned) && (inventoryWindow.selectedItem != inventoryWindow.playerImplants[inventoryWindow.selectedCharacter])){
                        itemEquipped(inventoryWindow.selectedCharacter, inventoryWindow.selectedItem);
                    }
                    else if(!owned){
                        // TODO warning;
                    }
                }
            }
        }

        Text {
            id: textInventoryHeader
            anchors.left: rectPaddingLeft.right
            anchors.top: rectPaddingTop.bottom
            text: qsTr("INVENTORY")
            font.family: "Helvetica"
            font.pointSize: 30
            font.bold: true
            color: "white"
        }
        Rectangle {
            id: rectPaddingInventoryHeaderBottom
            anchors.top: textInventoryHeader.bottom
            height: 10
            color: "transparent"
        }

        Rectangle {
            id: rectResearchList
            width: 200
            height: 600
            anchors.left: rectPaddingLeft.right
            anchors.top: rectPaddingInventoryHeaderBottom.bottom
            color: "transparent"

            Column {
                id: columnResearchList
                spacing: 3

                Button {
                    id: buttonArmors
                    width: 200
                    height: 34
                    text: qsTr("ARMORS")
                    checkable: true
                    checked: (inventoryWindow.selectedItemType == "ARMORS" ? true : false)
                    onClicked:{
                       inventoryWindow.selectedItemType = "ARMORS"
                       inventoryWindow.selectedItem = inventoryWindow.armorsNames[0]
                       itemName = inventoryWindow.armorsNames[0]
                       owned = inventoryWindow.armorsOwned[0]
                       cost = inventoryWindow.armorsPrices[0]
                       inventoryWindow.armorDefence = inventoryWindow.armorsDefences[0]
                       showingWarning = false
                       showingBoughtMessage = false
                       imageSelectedItem.picChanged()

                    }
                }

                Button {
                    id: buttonWeapons
                    width: 200
                    height: 33
                    text: qsTr("WEAPONS")
                    checkable: true
                    checked: (inventoryWindow.selectedItemType == "WEAPONS" ? true : false)
                    onClicked:{
                       inventoryWindow.selectedItemType = "WEAPONS"
                       inventoryWindow.selectedItem = inventoryWindow.weaponsNames[0]
                       itemName = inventoryWindow.weaponsNames[0]
                       owned = inventoryWindow.weaponsOwned[0]
                       cost = inventoryWindow.weaponsPrices[0]
                       minDamaqe = inventoryWindow.weaponsMinDamage[0]
                       maxDamaqe = inventoryWindow.weaponsMaxDamage[0]
                       minRange = inventoryWindow.weaponsMinRange[0]
                       maxRange = inventoryWindow.weaponsMaxRange[0]
                       shootAp = inventoryWindow.weaponsShootAp[0]
                       reloadAp = inventoryWindow.weaponsReloadAp[0]
                       spread = inventoryWindow.weaponsSpread[0]
                       clipSize = inventoryWindow.weaponsClipsize[0]
                       showingWarning = false
                       showingBoughtMessage = false
                       imageSelectedItem.picChanged()

                    }
                }

                Button {
                    id: buttonImplants
                    width: 200
                    height: 33
                    text: qsTr("IMPLANTS")
                    checkable: true
                    checked: (inventoryWindow.selectedItemType == "IMPLANTS" ? true : false)
                    onClicked:{
                       inventoryWindow.selectedItemType = "IMPLANTS"
                       inventoryWindow.selectedItem = inventoryWindow.implantsNames[0]
                       itemName = inventoryWindow.implantsNames[0]
                       owned = inventoryWindow.implantsOwned[0]
                       cost = inventoryWindow.implantsPrices[0]
                       inventoryWindow.attackBoost = inventoryWindow.implantsAttackBoost[0]
                       inventoryWindow.defenceBoost = inventoryWindow.implantsDefenceBoost[0]
                       inventoryWindow.rangeBoost = inventoryWindow.implantsRangeBoost[0]
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
                visible: (inventoryWindow.selectedItemType == "WEAPONS" ? true : false)
                spacing: 3

                Repeater {
                    model: inventoryWindow.weaponsAmount
                    Button {
                        width: 200
                        height: 30
                        text: inventoryWindow.weaponsNames[index]
                        checkable: true
                        checked: (inventoryWindow.selectedItem == inventoryWindow.weaponsNames[index] ? true : false)
                        onClicked:{
                            inventoryWindow.selectedItem = inventoryWindow.weaponsNames[index]
                            itemName = inventoryWindow.selectedItem
                            cost = inventoryWindow.weaponsPrices[index]
                            owned = inventoryWindow.weaponsOwned[index]
                            minDamaqe = inventoryWindow.weaponsMinDamage[index]
                            maxDamaqe = inventoryWindow.weaponsMaxDamage[index]
                            minRange = inventoryWindow.weaponsMinRange[index]
                            maxRange = inventoryWindow.weaponsMaxRange[index]
                            shootAp = inventoryWindow.weaponsShootAp[index]
                            reloadAp = inventoryWindow.weaponsReloadAp[index]
                            spread = inventoryWindow.weaponsSpread[index]
                            clipSize = inventoryWindow.weaponsClipsize[index]
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
                visible: (inventoryWindow.selectedItemType == "ARMORS" ? true : false)
                spacing: 3

                Repeater {
                    model: inventoryWindow.armorsAmount
                    Button {
                        width: 200
                        height: 30
                        text: inventoryWindow.armorsNames[index]
                        checkable: true
                        checked: (inventoryWindow.selectedItem == inventoryWindow.armorsNames[index] ? true : false)
                        onClicked:{
                           inventoryWindow.selectedItem = inventoryWindow.armorsNames[index]
                           itemName = inventoryWindow.selectedItem
                           cost = inventoryWindow.armorsPrices[index]
                           owned = inventoryWindow.armorsOwned[index]
                           inventoryWindow.armorDefence = inventoryWindow.armorsDefences[index]
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
                visible: (inventoryWindow.selectedItemType == "IMPLANTS" ? true : false)
                spacing: 3

                Repeater {
                    model: inventoryWindow.implantsAmount
                    Button {
                        width: 200
                        height: 30
                        text: inventoryWindow.implantsNames[index]
                        checkable: true
                        checked: (inventoryWindow.selectedItem == inventoryWindow.implantsNames[index] ? true : false)
                        onClicked:{
                           inventoryWindow.selectedItem = inventoryWindow.implantsNames[index]
                           itemName = inventoryWindow.selectedItem
                           cost = inventoryWindow.implantsPrices[index]
                           owned = inventoryWindow.implantsOwned[index]
                           inventoryWindow.attackBoost = inventoryWindow.implantsAttackBoost[index]
                           inventoryWindow.defenceBoost = inventoryWindow.implantsDefenceBoost[index]
                           inventoryWindow.rangeBoost = inventoryWindow.implantsRangeBoost[index]
                           showingWarning = false
                           showingBoughtMessage = false
                           imageSelectedItem.picChanged()

                        }
                    }
                }
            }
        }

        Rectangle {
            id: rectPaddingResearchedItemsRight
            anchors.left: rectResearchList.right
            width: 10
            color: "transparent"
        }

        Rectangle {
            id: rectSelectedItem
            width: 200
            height: 160
            border.color: "white"
            anchors.left: rectPaddingResearchedItemsRight.right
            anchors.top: rectPaddingInventoryHeaderBottom.bottom
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

                source: "qrc:/pics/syndicate_none.png"
                function picChanged(){
                    if(inventoryWindow.selectedItem == "LIGHT ARMOR"){
                        imageSelectedItem.source = "qrc:/pics/syndicate_light_armor.png"
                    }
                    else if(inventoryWindow.selectedItem == "MEDIUM ARMOR") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_medium_armor.png"
                    }
                    else if(inventoryWindow.selectedItem == "HEAVY ARMOR") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_heavy_armor.png"
                    }
                    else if(inventoryWindow.selectedItem == "KNIFE") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_knife_2.png"
                    }
                    else if(inventoryWindow.selectedItem == "PISTOL") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_pistol_2.png"
                    }
                    else if(inventoryWindow.selectedItem == "SMG") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_smg.png"
                    }
                    else if(inventoryWindow.selectedItem == "ASSAULT RIFLE") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_assault_rifle.png"
                    }
                    else if(inventoryWindow.selectedItem == "MACHINE GUN") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_machine_gun.png"
                    }
                    else if(inventoryWindow.selectedItem == "SNIPER") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_sniper.png"
                    }
                    else if(inventoryWindow.selectedItem == "ATTACK BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_attack_boost.png"
                    }
                    else if(inventoryWindow.selectedItem == "SUPER ATTACK BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_super_attack_boost.png"
                    }
                    else if(inventoryWindow.selectedItem == "DEFENCE BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_defence_boost.png"
                    }
                    else if(inventoryWindow.selectedItem == "SUPER DEFENCE BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_super_defence_boost.png"
                    }
                    else if(inventoryWindow.selectedItem == "RANGE BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_range_boost.png"
                    }
                    else if(inventoryWindow.selectedItem == "SUPER RANGE BOOST") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_super_range_boost.png"
                    }
                    else if(inventoryWindow.selectedItem == "NONE") {
                        imageSelectedItem.source = "qrc:/pics/syndicate_none.png"
                    }
                }
            }
        }
        Rectangle {
            id: rectItemInfo
            anchors.top: rectSelectedItem.bottom
            anchors.left: rectSelectedItem.left
            border.color: "white"
            color: "transparent"

            width: 200
            height: 240
            //color: "#007210"
            opacity: 100

            Column{
                id: textGunItemInfo
                anchors.horizontalCenter: parent.horizontalCenter
                visible: (inventoryWindow.selectedItemType == "WEAPONS" ? true : false)
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
                visible: (inventoryWindow.selectedItemType == "IMPLANTS" ? true : false)
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
                    text: qsTr("Attack boost: ") + inventoryWindow.attackBoost
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textImplantRangeBoost
                    text: qsTr("Range boost: ") + inventoryWindow.rangeBoost
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
                Text {
                    id: textImplantDefenceBoost
                    text: qsTr("Defence boost: ") + inventoryWindow.defenceBoost
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
            }
            Column{
                id: textModItemInfo
                anchors.horizontalCenter: parent.horizontalCenter
                visible: (inventoryWindow.selectedItemType == "ARMORS" ? true : false)
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
                    text: qsTr("Defence: ") + inventoryWindow.armorDefence
                    font.family: "Helvetica"
                    font.pointSize: 13
                    color: "white"
                }
            }
            Text {
                id: textItemOwnership
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: textGunItemInfo.bottom
                text: (owned) ? qsTr("\nRESEARCHED") : qsTr("\nNOT RESEARCHED")
                font.family: "Helvetica"
                font.pointSize: 15
                color: (owned) ? "white" : "red"
                font.italic: true
            }
         }

        Rectangle {
            id: rectPaddingItemInfoRight
            anchors.left: rectItemInfo.right
            width: 10
            color: "transparent"
        }

        Rectangle {
            id: rectSelectedCharacter
            anchors.top: rectPaddingTop.bottom
            anchors.left: rectPaddingItemInfoRight.right
            anchors.right: rectPaddingRight.left
            anchors.bottom: rectPaddingBottom.top
            color: "transparent"
            Rectangle {
                id: rectPaddingTopOfCharacters
                anchors.top: parent.top
                height: 20
                color: "transparent"
            }
            Image {
                id: imageSelectedCharacter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: rectPaddingTopOfCharacters.bottom

                height: 200
                width: 150
                z: 3
                source: (inventoryWindow.selectedCharacter == 0) ? "qrc:/pics/syndicate_char_1_2.png" :
                        (inventoryWindow.selectedCharacter == 1) ? "qrc:/pics/syndicate_char_2_2.png" :
                        (inventoryWindow.selectedCharacter == 2) ? "qrc:/pics/syndicate_char_3_2.png" :
                                                   "qrc:/pics/syndicate_char_4_2.png"
            }
            Image {
                id: imageLeftCharacter
                anchors.verticalCenter: imageSelectedCharacter.verticalCenter
                x: imageSelectedCharacter.x - 65

                height: 100
                width: 75
                opacity: 0.7

                z: 2

                source: (inventoryWindow.selectedCharacter == 0) ? "qrc:/pics/syndicate_char_4_2.png" :
                        (inventoryWindow.selectedCharacter == 1) ? "qrc:/pics/syndicate_char_1_2.png" :
                        (inventoryWindow.selectedCharacter == 2) ? "qrc:/pics/syndicate_char_2_2.png" :
                                                   "qrc:/pics/syndicate_char_3_2.png"
            }
            Image {
                id: imageRightCharacter
                anchors.verticalCenter: imageSelectedCharacter.verticalCenter
                x: imageSelectedCharacter.x + 140

                height: 100
                width: 75
                opacity: 0.7

                z: 2

                source: (inventoryWindow.selectedCharacter == 0) ? "qrc:/pics/syndicate_char_2_2.png" :
                        (inventoryWindow.selectedCharacter == 1) ? "qrc:/pics/syndicate_char_3_2.png" :
                        (inventoryWindow.selectedCharacter == 2) ? "qrc:/pics/syndicate_char_4_2.png" :
                                                   "qrc:/pics/syndicate_char_1_2.png"
            }
            Rectangle {
                id: rectSelectedCharacterName
                anchors.top: imageSelectedCharacter.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 60
                border.color: "white"
                color: "transparent"
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: inventoryWindow.playerNames[inventoryWindow.selectedCharacter]
                    color: "white"
                    font.family: "Helvetica"
                    font.pointSize: 26
                    font.bold: true
                }
                Rectangle {
                    id: rectPaddingArrowLeft
                    anchors.left: parent.left
                    width: 10
                    color: "transparent"
                }
                Rectangle {
                    id: rectPaddingArrowRight
                    anchors.right: parent.right
                    width: 10
                    color: "transparent"
                }

                Image {
                    id: imageArrowLeftCharacter
                    anchors.left: rectPaddingArrowLeft.right

                    anchors.verticalCenter: parent.verticalCenter
                    height: 50
                    width: 50
                    source: "qrc:/pics/syndicate_button_left.png"

                    MouseArea {
                        id: mouseAreaArrowLeft
                        anchors.fill: parent
                        onClicked: {

                            if (inventoryWindow.selectedCharacter <= 0) {
                                inventoryWindow.selectedCharacter = 3;
                            }
                            else {
                                inventoryWindow.selectedCharacter -= 1;
                            }
                        }
                    }
                }
                Image {
                    id: imageArrowRightCharacter
                    anchors.right: rectPaddingArrowRight.left
                    anchors.verticalCenter: parent.verticalCenter

                    height: 50
                    width: 50
                    source: "qrc:/pics/syndicate_button_right.png"

                    MouseArea {
                        id: mouseAreaArrowRight
                        anchors.fill: parent
                        onClicked: {

                            if (inventoryWindow.selectedCharacter >= 3) {
                                inventoryWindow.selectedCharacter = 0;
                            }
                            else {
                                inventoryWindow.selectedCharacter += 1;
                            }
                        }
                    }
                }
            }
            Rectangle {
                id: rectPaddingCharacterNameBottom
                anchors.top: rectSelectedCharacterName.bottom
                height: 10
                color: "transparent"
            }
            Rectangle {
                id: rectEquippedItems
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: rectPaddingCharacterNameBottom.bottom
                anchors.bottom: parent.bottom

                color: "transparent"
                border.color: "white"
                Column {
                    id: columnEquippedItems
                    anchors.left: rectEquippedItems.left
                    anchors.right: rectEquippedItems.right
                    anchors.top: rectEquippedItems.top
                    padding: 15
                    spacing: 5
                    Text {
                        id: textEquipped
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "EQUIPPED\n"
                        color: "white"
                        font.family: "Helvetica"
                        font.pointSize: 18
                        font.underline: true
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: imageEquippedArmor
                            height: 65
                            width: 100
                            source: (inventoryWindow.playerArmors[inventoryWindow.selectedCharacter] == "LIGHT ARMOR") ?
                                    "qrc:/pics/syndicate_light_armor.png" :
                                    (inventoryWindow.playerArmors[inventoryWindow.selectedCharacter] == "MEDIUM ARMOR") ?
                                    "qrc:/pics/syndicate_medium_armor.png" :
                                    (inventoryWindow.playerArmors[inventoryWindow.selectedCharacter] == "HEAVY ARMOR") ?
                                    "qrc:/pics/syndicate_heavy_armor.png" :
                                    (inventoryWindow.playerArmors[inventoryWindow.selectedCharacter] == "ASSAULT RIFLE") ?
                                    "qrc:/pics/syndicate_assault_rifle.png" :
                                    (inventoryWindow.playerArmors[inventoryWindow.selectedCharacter] == "MACHINE GUN") ?
                                    "qrc:/pics/syndicate_machine_gun.png" :
                                    (inventoryWindow.playerArmors[inventoryWindow.selectedCharacter] == "SNIPER") ?
                                    "qrc:/pics/syndicate_sniper.png" : "qrc:/pics/syndicate_none.png"
                        }
                        Text {
                            id: textImageEquippedArmor

                            text: (inventoryWindow.playerArmors[inventoryWindow.selectedCharacter] == "NONE") ? "Armor: " :
                                  "Armor:\n" + inventoryWindow.playerArmors[inventoryWindow.selectedCharacter]
                            color: "white"
                            font.family: "Helvetica"
                            font.pointSize: 16
                        }
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: imageEquippedWeapon
                            height: 65
                            width: 100
                            source: (inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter] == "KNIFE") ?
                                    "qrc:/pics/syndicate_knife_2.png" :
                                    (inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter] == "PISTOL") ?
                                    "qrc:/pics/syndicate_pistol_2.png" :
                                    (inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter] == "SMG") ?
                                    "qrc:/pics/syndicate_smg.png" :
                                    (inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter] == "ASSAULT RIFLE") ?
                                    "qrc:/pics/syndicate_assault_rifle.png" :
                                    (inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter] == "MACHINE GUN") ?
                                    "qrc:/pics/syndicate_machine_gun.png" :
                                    (inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter] == "SNIPER") ?
                                    "qrc:/pics/syndicate_sniper.png" : "qrc:/pics/syndicate_none.png"
                        }
                        Text {
                            id: textImageEquippedWepon

                            text: (inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter]  == "NONE")  ? "Weapon: " :
                                   "Weapon:\n"+ inventoryWindow.playerWeapons[inventoryWindow.selectedCharacter]
                            color: "white"
                            font.family: "Helvetica"
                            font.pointSize: 16
                        }
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: imageEquippedImplant
                            z: 9
                            height: 65
                            width: 100
                            source: (inventoryWindow.playerImplants[inventoryWindow.selectedCharacter] == "ATTACK BOOST") ?
                                    "qrc:/pics/syndicate_attack_boost.png" :
                                    (inventoryWindow.playerImplants[inventoryWindow.selectedCharacter] == "SUPER ATTACK BOOST") ?
                                    "qrc:/pics/syndicate_super_attack_boost.png" :
                                    (inventoryWindow.playerImplants[inventoryWindow.selectedCharacter] == "DEFENCE BOOST") ?
                                    "qrc:/pics/syndicate_defence_boost.png" :
                                    (inventoryWindow.playerImplants[inventoryWindow.selectedCharacter] == "SUPER DEFENCE BOOST") ?
                                    "qrc:/pics/syndicate_super_defence_boost.png" :
                                    (inventoryWindow.playerImplants[inventoryWindow.selectedCharacter] == "RANGE BOOST") ?
                                    "qrc:/pics/syndicate_range_boost.png" :
                                    (inventoryWindow.playerImplants[inventoryWindow.selectedCharacter] == "SUPER RANGE BOOST") ?
                                    "qrc:/pics/syndicate_super_range_boost.png" : "qrc:/pics/syndicate_none.png"

                        }
                        Text {
                            id: textImageEquippedImplant
                            text: (inventoryWindow.playerImplants[inventoryWindow.selectedCharacter] == "NONE")  ? "Implant: " :
                                  "Implant:\n" + inventoryWindow.playerImplants[inventoryWindow.selectedCharacter]
                            color: "white"
                            font.family: "Helvetica"
                            font.pointSize: 16
                        }
                    }
                }
            }
        }
    }
}
