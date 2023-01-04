import QtQuick
import QtQuick.Controls
import QtWebEngine 1.9
import QtWebChannel 1.0
import FileListModel 1.0

Item {
    width: parent.width
    height:parent.height

    property alias textIns: _textIn
    property alias textOuts: _textOut
    property alias fileListModel: _fileListModel

    WebChannel {
        id: _textEditWebChannel
        registeredObjects: [_textIn]
    }

    FileListModel{
        id: _fileListModel
    }

    SplitView {
        id: _editItem
        anchors.fill: parent
        orientation: Qt.Horizontal

        handle: Rectangle {
            id: handleDelegate
            implicitWidth: 1
            implicitHeight: 1
            color: SplitHandle.pressed ? "#333"
             : (SplitHandle.hovered ? "#33333350" : "#33333380")
        }

        Rectangle {
            id: _filesView
            implicitWidth: parent.width*0.12
            height: parent.height
            color: "#e9e9e9"
            visible: true
            FileFolderList{
                id:_filesViewComponent
                x:10
                y:10
            }
        }

        Rectangle {
            id: _editContent
            implicitWidth: parent.width*0.44
            height: parent.height
            clip: true
            Rectangle{
               x:10
               y:10
               width: parent.width-10
               height: parent.height-20
               Flickable {
                    id: _flick
                    width: parent.width
                    height: parent.height
                    contentHeight: _textIn.contentHeight
                    clip: true
                    function ensureVisible(r)
                    {
                        if (contentX >= r.x)
                            contentX = r.x;
                        else if (contentX+width <= r.x+r.width)
                            contentX = r.x+r.width-width;
                        if (contentY >= r.y)
                            contentY = r.y;
                        else if (contentY+height <= r.y+r.height)
                            contentY = r.y+r.height-height;
                    }

                    TextEdit {
                        signal inputMd(string text)
                        id: _textIn
                        WebChannel.id: "_textInObj"
                        text: _mdcore.mdRes
                        focus: true
                        width: parent.width
                        height:  contentHeight
                        wrapMode: TextEdit.Wrap
                        font.pixelSize: 14
                        selectByKeyboard: true
                        selectByMouse: true
                        onCursorRectangleChanged: _flick.ensureVisible(cursorRectangle)
                        onTextChanged: {
                            _textIn.inputMd(_textIn.text)
                        }
                    }
                }

               //添加一个滚动条按钮
               Rectangle
               {
                   id: _srect;
                   width: 3;
                   anchors.right: _flick.right;
                   color: "#99999990";

                   //flick.visibleArea.heightRatio = flick.height / flick.contentHeight
                   height: _flick.visibleArea.heightRatio * _flick.height;

                   //滚动条会随着图片移动而移动，因为图片和滚动条应该都是等比例下降，所以换算如下
                   y: _flick.visibleArea.yPosition * _flick.height;

                   //给滚动条按钮添加槽函数，可以拖动按钮移动图片
                   MouseArea
                   {
                       id: mouseA;
                       anchors.fill: _srect;
                       //让滚动条可以在垂直方向拖动
                       drag.target: _srect;
                       drag.axis: Drag.YAxis;
                       drag.minimumY: 0;
                       drag.maximumY: _flick.height - _srect.height;

                       onPressed:
                       {
                          _srect.color = "#99999950";
                       }

                       onReleased:
                       {
                          _srect.color = "#99999990";
                       }

                       //不可以用flick.visibleArea.yPosition,因为是只读属性
                       onMouseYChanged:
                       {
                           console.log("_flick.contentHeight:"+_flick.contentHeight)
                           console.log("_flick.height :"+_flick.height )
                          _flick.contentY = _srect.y / _flick.height * _flick.contentHeight;
                       }
                   }

                   Component.onCompleted:
                   {
                       console.log("QML MouseArea\'s C++ type - ", mouseA);
                   }
               }

           }
        }

        Rectangle {
            id: _previwContent
            implicitWidth: parent.width * 0.44
            height: parent.height
            clip: true
            Keys.onUpPressed: _vbar.decrease()
            Keys.onDownPressed: _vbar.increase()

            WebEngineView {
                id: _textOut
                anchors.fill: parent
                visible: true
                url:"qrc:/assets/static/index.html"
                webChannel: _textEditWebChannel
           }
        }
    }
}
