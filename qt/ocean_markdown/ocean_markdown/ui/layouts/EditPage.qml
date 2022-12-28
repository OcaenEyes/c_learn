import QtQuick 2.15

Item {
    id: _edit
    visible: true

    property bool isShowPreviw: true

    Row {
        id: _editItem
        spacing: 10
        width: parent.width
        height: parent.height
        Rectangle {
            id: _editContent
            width: parent.width /2
            height: parent.height

            Text {
                id: _left
                text: "这是编辑模块"
            }
        }

        Rectangle {
            id: _previewContent
            visible: isShowPreviw
            width: parent.width /2
            height: parent.height

            Text {
                id: _right
                text: "这是预览模块"
            }

        }
    }


}
