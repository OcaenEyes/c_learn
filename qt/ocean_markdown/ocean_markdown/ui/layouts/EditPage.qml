import QtQuick
import QtQuick.Window 2.15
import QtQuick.Controls
import MarkDownCore 1.0
import QtWebEngine 1.9
import QtWebChannel 1.0
import Qt.labs.folderlistmodel 2.4

import "../3rdparty/showdown.js" as ShowDown


Item {
    id: _edit
    visible: true
    property bool isShowPreviw: true
    width: parent.width
    height: parent.height

    MarkDownCore {
        id : _mdcore
        onHasMarkdownIn: console.log(_mdcore.mdRes)

    }

    WebChannel {
        id: _textEditWebChannel
        registeredObjects: [_textIn]
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
            Row{
                id: _editToolBar
                spacing: 2
                anchors.verticalCenter: parent.verticalCenter

                Action {
                    id: blodAction
                    shortcut: "Ctrl+B"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"**"+_textIn.selectedText+"**")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"**粗体**")
                        }
                    }
                }

                Action {
                    id: italicAction
                    shortcut: "Ctrl+I"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"*"+_textIn.selectedText+"*")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"*斜体*")
                        }
                    }
                }

                Action {
                    id: deleteLineAction
                    shortcut: "Ctrl+D"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"~~"+_textIn.selectedText+"~~")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"~~删除线~~")
                        }
                    }
                }

                Action {
                    id: codeAction
                    shortcut: "Ctrl+Alt+P"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"\n```\n"+_textIn.selectedText+"\n```\n")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"\n```\n#插入代码\n```\n")
                        }
                    }
                }

                Action {
                    id: numListAction
                    shortcut: "Ctrl+L"
                    onTriggered: {
                        _textIn.append("\n1. 有序列表 \n2. \n")
                    }
                }

                Action {
                    id: noNumListAction
                    shortcut: "Ctrl+Alt+L"
                    onTriggered: {
                        _textIn.append("\n- 无序列表 \n- \n")
                    }
                }

                Action {
                    id: h1Action
                    shortcut: "Ctrl+1"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"# "+_textIn.selectedText+"\n")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"\n# 标题一\n")
                        }
                    }
                }

                Action {
                    id: h2Action
                    shortcut: "Ctrl+2"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"## "+_textIn.selectedText+"\n")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"\n## 标题二\n")
                        }
                    }
                }

                Action {
                    id: h3Action
                    shortcut: "Ctrl+3"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"### "+_textIn.selectedText+"\n")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"\n### 标题三\n")
                        }
                    }
                }

                Action {
                    id: h4Action
                    shortcut: "Ctrl+4"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"#### "+_textIn.selectedText+"\n")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"\n#### 标题四\n")
                        }
                    }
                }

                Action {
                    id: h5Action
                    shortcut: "Ctrl+5"
                    onTriggered: {
                        if(_textIn.selectedText !==""){
                            _textIn.text = _textIn.text.replace(_textIn.selectedText,"##### "+_textIn.selectedText+"\n")
                        }else{
                            _textIn.insert(_textIn.cursorPosition,"\n##### 标题五\n")
                        }
                    }
                }

                ToolButton {
                    id: _fileTool
                    text: "文件"
                    onClicked: _fileToolMenu.open()
                    Menu {
                        id: _fileToolMenu
                        MenuItem {
                            text: "新建文档"
                            action: _newDocAction
                        }

                        MenuItem {
                            text: "打开文档"
                            action: _openDocAction
                        }

                        MenuItem {
                            text: "打开文件夹"
                            action: _openFoldercAction
                        }

                        MenuItem {
                            text: "保存文档"
                            action: _saveDocAction
                        }
                    }
                }


                Action {
                    id: _openDocAction
                    shortcut: "Ctrl+O"
                    onTriggered: {
                        console.debug("测试打开文档")
                    }
                }

                Action {
                    id: _newDocAction
                    shortcut: "Ctrl+N"
                    onTriggered: {
                        console.debug("测试新建文档")
                    }
                }

                Action {
                    id: _saveDocAction
                    shortcut: "Ctrl+S"
                    onTriggered: {
                        console.debug("保存文档")
                    }
                }

                Action {
                    id: _openFoldercAction
                    onTriggered: {
                        console.log("_folders:"+_folders)
                        console.log("_folders.folders:"+_folders.folders)
                        if(_folders.folders.length > 0)
                        {
                            _folders.folder = _folders.folders[_folders.folders.length-1];
                            _folders.folders.splice(_folders.folders.length-1,1);
                        }
                        else
                        {
                            console.debug("root")
                        }
                    }
                }



                ToolButton{
                    id: _h1
                    text: "H1"
                    action: h1Action
                }
                ToolButton{
                    id: _h2
                    text: "H2"
                    action: h2Action
                }
                ToolButton{
                    id: _h3
                    text: "H3"
                    action: h3Action
                }
                ToolButton{
                    id: _h4
                    text: "H4"
                    action: h4Action
                }
                ToolButton{
                    id: _h5
                    text: "H5"
                    action: h5Action
                }

                ToolButton{
                    id: _bold
                    text: "粗体"
                    action: blodAction
                }

                ToolButton{
                    id: _italic
                    text: "斜体"
                    action: italicAction

                }

                ToolButton{
                    id: _deleteLine
                    text: "删除线"
                    action: deleteLineAction


                }

                ToolButton{
                    id: _codeBlock
                    text: "代码块"
                    action: codeAction


                }

                ToolButton{
                    id: _numList
                    text: "有序列表"
                    action: numListAction


                }

                ToolButton{
                    id: _noNumList
                    text: "无序列表"
                    action: noNumListAction
                }

                ToolButton {
                    id: _changeMdStyle
                    text: "主题样式"
                    onClicked: _changeMdStyleMenu.open()

                    Menu {
                        id: _changeMdStyleMenu
                        MenuItem {
                            text: "sspai"

                            onTriggered: {
                                _textOut.runJavaScript("changeMarkDownStyle(0)")
                            }
                        }
                        MenuItem {
                            text: "han"
                            onTriggered: {
                                _textOut.runJavaScript("changeMarkDownStyle(1)")
                            }
                        }
                        MenuItem {
                            text: "mdhere"
                            onTriggered: {
                                _textOut.runJavaScript("changeMarkDownStyle(2)")
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: _editContainer
            width: parent.width
            height: parent.height - 28
//            color: "red"

            SplitView {
                id: _editItem
                anchors.fill: parent
                orientation: Qt.Horizontal
//                spacing: 2
//                width: parent.width
//                height: parent.height
                Rectangle {
                    id: _filesView
                    implicitWidth: parent.width*0.12
                    height: parent.height
                    visible: true

                    TreeView {
                        anchors.fill: parent
                        // The model needs to be a QAbstractItemModel
                        // model: yourTreeModel

                        delegate: Item {
                            id: treeDelegate

                            implicitWidth: padding + label.x + label.implicitWidth + padding
                            implicitHeight: label.implicitHeight * 1.5

                            readonly property real indent: 20
                            readonly property real padding: 5

                            // Assigned to by TreeView:
                            required property TreeView treeView
                            required property bool isTreeNode
                            required property bool expanded
                            required property int hasChildren
                            required property int depth

                            TapHandler {
                                onTapped: treeView.toggleExpanded(row)
                            }

                            Text {
                                id: indicator
                                visible: treeDelegate.isTreeNode && treeDelegate.hasChildren
                                x: padding + (treeDelegate.depth * treeDelegate.indent)
                                anchors.verticalCenter: label.verticalCenter
                                text: "▸"
                                rotation: treeDelegate.expanded ? 90 : 0
                            }

                            Text {
                                id: label
                                x: padding + (treeDelegate.isTreeNode ? (treeDelegate.depth + 1) * treeDelegate.indent : 0)
                                width: treeDelegate.width - treeDelegate.padding - x
                                clip: true
                                text: model.display
                            }
                        }
                    }

                    TreeViewModel
                    {
                            id:treeViewModel
                    }


//                    ListView {
//                        id: _filesListView
//                        anchors.fill: parent
//                        spacing: 10
//                        model: _folders
//                        delegate:_fileDelegate
//                        Component {
//                            id: _fileDelegate
//                            Text {
//                                text: fileName
//                                MouseArea {
//                                    enabled: fileIsDir
//                                    anchors.fill: parent
//                                    onClicked: {
//                                        _folders.folders.push(_folders.folder)
//                                        _folders.folder += fileName+"/"
//                                    }
//                                }
//                            }
//                        }
//                        FolderListModel {
//                            id:_folders
//                            property var folders:[]
//                            folder: "file:///" + "E:/GitHub/c_learn/qt/ocean_markdown/ocean_markdown/ui"
//                            nameFilters: ["*"]
//                            showDirs: true
//                            showFiles: true
//                            showDotAndDotDot: true
//                        }
//                    }

                }

                Rectangle {
                    id: _editContent
                    implicitWidth: parent.width*0.44
//                    width: parent.width * 0.5
                    height: parent.height
                    clip: true
//                    Keys.onUpPressed: _vbar.decrease()
//                    Keys.onDownPressed: _vbar.increase()

                    Flickable {
                         id: _flick
                         width: parent.width
                         height: parent.height-6
//                         contentWidth: _textIn.contentWidth
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
                                 contentY = r.y+r.height-height+18;

//                             console.log("r.x"+r.x)
//                             console.log("r.y"+r.y)
//                             console.log("r.width"+r.width)
//                             console.log("r.height"+r.height)
//                             console.log("height"+height)
//                             console.log("contentX"+contentX)
//                             console.log("contentY"+contentY)
//                             console.log(""+"=========******=====")
                         }

                         TextEdit {
                             signal inputMd(string text)
                             id: _textIn
                             WebChannel.id: "_textInObj"
                             text: _mdcore.mdRes
                             focus: true
                             x: 6
                             y: 6
                             width: parent.width-12
                             height:  contentHeight
                             wrapMode: TextEdit.Wrap
                             font.pixelSize: 14
                             selectByKeyboard: true
                             selectByMouse: true
                             onCursorRectangleChanged: _flick.ensureVisible(cursorRectangle)
                             onTextChanged: {
//                                 console.log("_textIn.text:"+_textIn.text.toString())
     //                           _textOut.text = Marked.marked.parse(_textIn.text)
     //                            var _tmp = ShowDown.markdown2Html(_textIn.text)
     //                            _textOut.loadHtml(_tmp,"index.html")
                                 _textIn.inputMd(_textIn.text)
                             }

//                             MouseArea {
//                                 anchors.fill: _textIn
//                                 hoverEnabled: true
//                                 propagateComposedEvents: true
//                                 onWheel:(wheel)=>{
//         //                                console.log("w轮子滚动"+wheel.angleDelta.y)
//                                     if(wheel.angleDelta.y >0){
//                                         _vbar.decrease()
//         //                                    console.log("y大于0_vbar.height"+_vbar.height)
//         //                                    console.log("y大于0 _vbar.width"+_vbar.width)
//         //                                    console.log("y大于0 _vbar.size"+_vbar.size)
//         //                                    console.log("y大于0 _vbar.position"+_vbar.position)
//                                     }
//                                     else if((wheel.angleDelta.y <0)) {
//                                         _vbar.increase()
//                                     }
//                                 }
//                                 onClicked:(mouse)=> {
//                                     _textIn.forceActiveFocus();
//                                     mouse.accepted = false;
//                                     _textIn.cursorPosition = _textIn.selectionEnd

//                                 }
//                                 onPressed:(mouse)=> {
//                                    mouse.accepted = false;
//                                 }
//                                 onReleased: (mouse)=>{
//                                     mouse.accepted = false;
//                                 }
//                                 onDoubleClicked:(mouse)=> {
//                                     mouse.accepted = false;
//                                 }
//                                 onPositionChanged: (mouse)=>{
//                                     mouse.accepted = false;
//                                 }
//                                 onPressAndHold:(mouse)=> {
//                                     mouse.accepted = false;
//                                 }
//                             }

                         }


                     }




                    //                    ScrollBar {
                    //                        id: _vbar
                    //                        hoverEnabled: true
                    //                        active: hovered || pressed
                    //                        orientation: Qt.Vertical
                    //                        size: _editContent.height / _textIn.height
                    //                        width:4
                    //                        anchors.top: parent.top
                    //                        anchors.right: parent.right
                    //                        anchors.bottom: parent.bottom
                    //                        y:_editContent.y

                    //                    }
                }

                Rectangle {
                    id: _previwContent
                    implicitWidth: parent.width * 0.44
                    height: parent.height
//                    color: "#f2eada"
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

//                    TextEdit {
//                        id: _textOut
//                        x: 8
//                        y: -_vbar.position * _textOut.height
//                        width: parent.width-8-_vbar.width
//                        height:  contentHeight
//                        selectByKeyboard: true
//                        selectByMouse: true

////                        text: _mdcore.mdRes
//                        wrapMode: TextEdit.Wrap
//                        textFormat: Text.RichText
//                        font.pixelSize: 12

//                        MouseArea {
//                            anchors.fill: parent
//                            propagateComposedEvents: true
//                            hoverEnabled: true
//                            onWheel:(wheel)=>{
////                                console.log("w轮子滚动"+wheel.angleDelta.y)
//                                if(wheel.angleDelta.y >0){
//                                    _vbar.decrease()
////                                    console.log("y大于0_vbar.height"+_vbar.height)
////                                    console.log("y大于0 _vbar.width"+_vbar.width)
////                                    console.log("y大于0 _vbar.size"+_vbar.size)
////                                    console.log("y大于0 _vbar.position"+_vbar.position)
//                                }
//                                else {
//                                    _vbar.increase()
//                                }
//                            }
//                            onClicked:(mouse)=> {
//                                _textIn.forceActiveFocus();
//                                mouse.accepted = false;
//                            }
//                            onPressed:(mouse)=> {
//                               mouse.accepted = false;
//                            }
//                            onReleased: (mouse)=>{
//                                mouse.accepted = false;
//                            }
//                            onDoubleClicked:(mouse)=> {
//                                mouse.accepted = false;
//                            }
//                            onPositionChanged: (mouse)=>{
//                                mouse.accepted = false;
//                            }
//                            onPressAndHold:(mouse)=> {
//                                mouse.accepted = false;
//                            }
//                        }


//                    }


            }

        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.66;height:480;width:640}
}
##^##*/
