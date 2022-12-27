import QtQuick 2.15
import QtPositioning 5.2
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.5

Item {
    id: menu
    visible: true

    property real maxHeight
    property real maxWidth
    property alias listMode: _repeater.model

    signal getListIndex(int idx)
    signal pageSig(int idx)

    Column {
        id: rowItem
        spacing: 20
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height*0.6

        Repeater {
            id: _repeater
            anchors.left: parent.left
            delegate: listDelegate
        }
    }

    Component {
        id : listDelegate
        Rectangle {
            id: listItem
            property bool checked: false
            property bool oldChecked: false
            property int clickCnt: 0

            width:30
            height: 30

            Connections {
                target: menu
                function onGetListIndex(idx) {
                    console.log("点击了"+index)
                    if (idx === index) {
                        if (idx !== 0) {
                            if (!listItem.oldChecked) {
                                listItem.checked = true
                                pageSig(idx)
                            }
                            else {
                                listItem.checked = false
                                pageSig(0)
                            }
                        }
                        else {
                            listItem.checked = true
                            pageSig(idx)
                        }
                    }
                    else {
                        listItem.checked = false
                    }
                    listItem.oldChecked = listItem.checked
                }
            }



            Rectangle {
                id: innerRect
                width: maxWidth * 0.8
                height: width

                Text {
                    id: _label
                    text: modelData.name
                    color: "#000"
                }
            }

            MouseArea {
               onEntered: {
                   innerRect.visible = true
               }

               onExited: {
                   innerRect.visible = false
               }

               onClicked: {
                   getListIndex(index)
               }
            }

        }
    }
}
