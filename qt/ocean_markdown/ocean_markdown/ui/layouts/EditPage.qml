import QtQuick
import QtQuick.Window 2.15
import QtQuick.Controls
import MarkDownCore 1.0


Item {
    id: _edit
    visible: true
    property bool isShowPreviw: true
    width: parent.width
    height: parent.height

    MarkDownCore {
        id : _mdcore
        onTextInChanged: console.log(_mdcore.mdRes)
    }

    Column {
        id : _editView
        width: parent.width
        height: parent.height
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.leftMargin: 0


        Rectangle {
            id: _editTools
            width: parent.width
            height: 28
            color: "#ededed"
            EditToolBar{
                id:_editToolComponent
            }
        }

        Rectangle {
            id: _editContainer
            width: parent.width
            height: parent.height - 28
//            color: "red"
            EditContainer{
                id:_editContainerComponent
            }
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.66;height:480;width:640}
}
##^##*/
