import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("OceanMarkDown")

    Row {
        id: mainContainer
        x: 0
        y: 0
        width: 640
        height: 480

        TextEdit {
            id: textIn
            y: 10
            width: 320
            height: 460
            text: qsTr("Text Edit")
            font.pixelSize: 12
        }

        Text {
            id: textOut
            y: 10
            width: 320
            height: 460
            text: qsTr("Text")
            font.pixelSize: 12
            wrapMode: Text.WordWrap
        }
    }
}
