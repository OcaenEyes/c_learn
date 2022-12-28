import QtQuick 2.15
import QtQuick.Window 2.15

Item {
    id: _edit
    visible: true
    property bool isShowPreviw: true
    width: parent.width
    height: parent.height

    Column {
        id : _editView
        width: parent.width
        height: parent.height
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        spacing: 2


        Rectangle {
            id: _editTools
            width: parent.width
            height: 40
            border.color: "#999"
            border.width: 1
        }

        Rectangle {
            id: _editContainer
            width: parent.width
            height: parent.height - 44
//            color: "red"
            Row {
                id: _editItem
                spacing: 2
                width: parent.width
                height: parent.height

                Rectangle {
                    id: _editContent
                    width: (parent.width-2)/2
                    height: parent.height
//                    color: "#e95d5d"
                    border.color: "#999"
                    border.width: 1

                    TextEdit {
                        id: textEdit
                        x: 8
                        y: 8
                        width: parent.width-16
                        height:  parent.height-16
                        text: qsTr("Text Edit")
                        font.pixelSize: 12

                    }
                }

                Rectangle {
                    id: _previwContent
                    width: (parent.width-2)/2
                    height: parent.height
//                    color: "#36e632"
                    border.color: "#999"
                    border.width: 1

                    TextEdit {
                        id: textEdit1
                        x: 8
                        y: 8
                        width: parent.width-16
                        height: parent.height-16
                        text: qsTr("Text Edit")
                        font.pixelSize: 12
                    }
                }

            }

        }
   }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.66;height:480;width:640}
}
##^##*/
