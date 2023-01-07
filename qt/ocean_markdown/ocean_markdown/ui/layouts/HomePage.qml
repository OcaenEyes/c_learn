import QtQuick 2.15

Item {
    id: _home
    visible: true
    width: parent.width
    height: parent.height

    Text {
        id: _title
        anchors.centerIn: parent
        text: "欢迎使用~😀 \n点击左侧“编辑”按钮开始~📕"
        font.pixelSize: 18
    }
}
