import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5

Item {
    id: _edit
    visible: true
    property bool isShowPreviw: true
    width: parent.width
    height: parent.height
    signal inputMd(string text)

    property string inputV: "欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~欢迎使用~"

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
            Row{
                id: _editToolBar
                spacing: 2
                anchors.verticalCenter: parent.verticalCenter


                Button{
                    id: _bold
                    text: "粗体"
                }

                Button{
                    id: _italitic
                    text: "斜体"
                }

                Button{
                    id: _leftAlign
                    text: "左对齐"
                }

                Button{
                    id: _centerAlign
                    text: "中对齐"
                }

                Button{
                    id: _rightAlign
                    text: "右对齐"
                }
            }
        }

        Rectangle {
            id: _editContainer
            width: parent.width
            height: parent.height - 28
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
                    clip: true
                    Keys.onUpPressed: _vbar.decrease()
                    Keys.onDownPressed: _vbar.increase()

                    TextEdit {
                        id: _textIn
                        text: inputV
                        focus: true
                        x: 8
                        y: -_vbar.position * _textIn.height
                        width: parent.width-8-_vbar.width
                        height:  contentHeight
                        wrapMode: TextEdit.Wrap
                        font.pixelSize: 12
                        selectByKeyboard: true
                        selectByMouse: true

                        MouseArea {
                            anchors.fill: parent
                            onWheel:(wheel)=>{
//                                console.log("w轮子滚动"+wheel.angleDelta.y)
                                if(wheel.angleDelta.y >0){
                                    _vbar.decrease()
//                                    console.log("y大于0_vbar.height"+_vbar.height)
//                                    console.log("y大于0 _vbar.width"+_vbar.width)
//                                    console.log("y大于0 _vbar.size"+_vbar.size)
//                                    console.log("y大于0 _vbar.position"+_vbar.position)
                                }
                                else {
                                    _vbar.increase()
                                }
                            }
                            onClicked: {
                                _textIn.forceActiveFocus()
                            }
                        }
                    }

                    ScrollBar {
                        id: _vbar
                        hoverEnabled: true
                        active: hovered || pressed
                        orientation: Qt.Vertical
                        size: _editContent.height / _textIn.height
                        width:4
                        anchors.top: parent.top
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom

                    }
                }

                Rectangle {
                    id: _previwContent
                    width: (parent.width-2)/2
                    height: parent.height
                    color: "#f2eada"
                    clip: true
                    Keys.onUpPressed: _vbar.decrease()
                    Keys.onDownPressed: _vbar.increase()

                    TextEdit {
                        id: _textOut
                        x: 8
                        y: -_vbar.position * _textOut.height
                        width: parent.width-8-_vbar.width
                        height:  contentHeight
                        selectByKeyboard: true
                        selectByMouse: true

                        text: inputV
                        wrapMode: TextEdit.Wrap
                        font.pixelSize: 12

                        MouseArea {
                            anchors.fill: parent
                            onWheel:(wheel)=>{
//                                console.log("w轮子滚动"+wheel.angleDelta.y)
                                if(wheel.angleDelta.y >0){
                                    _vbar.decrease()
//                                    console.log("y大于0_vbar.height"+_vbar.height)
//                                    console.log("y大于0 _vbar.width"+_vbar.width)
//                                    console.log("y大于0 _vbar.size"+_vbar.size)
//                                    console.log("y大于0 _vbar.position"+_vbar.position)
                                }
                                else {
                                    _vbar.increase()
                                }
                            }
                            onClicked: {
                                _textIn.forceActiveFocus()
                            }
                        }


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
