import QtQuick
import QtQuick.Controls

Window{
    width: 300
    height: 260
    title: qsTr("关于作者")

    ToolButton{
        anchors.centerIn: parent
        font.pixelSize: 18
        text:"😀 \nOCEAN MARKDOWN V0.0.1"
    }
}
