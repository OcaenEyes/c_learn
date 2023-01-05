import QtQuick 2.15
import QtQuick.Controls
import Qt.labs.platform

Item {
    width:parent.width
    height:parent.height

    property string defaltFolderUrl: StandardPaths.standardLocations(StandardPaths.DocumentsLocation)[0]+"/oceanmarkdown_data"//默认打开Documents/oceanmarkdown_data文件夹

    FolderDialog {
        id: _folderDialog
        folder: defaltFolderUrl
        acceptLabel: "确定"
        rejectLabel: "取消"
        options: FileDialog.ShowDirsOnly
//        onAccepted: {
//            defaltFolderUrl= currentFolder
//            console.log("当前路径：",defaltFolderUrl)
//            _editContainerComponent.fileListModel.initItems(defaltFolderUrl)

//        }
        onFolderChanged: {
            defaltFolderUrl= _folderDialog.folder
            console.log("修改了folder以后当前路径：",defaltFolderUrl)
            _editContainerComponent.fileListModel.initItems(defaltFolderUrl)
        }
    }

    FileDialog{
        id :_fileDialog
        acceptLabel: "确定"
        rejectLabel: "取消"
//        onAccepted: {
//            defaltFolderUrl= _fileDialog.folder
//            console.log("打开的新文档路径：",_fileDialog.file)
//        }
        onFileChanged:  {
            defaltFolderUrl= _fileDialog.folder
            console.log("打开的新文档路径：",_fileDialog.file)
            if(_fileDialog.fileMode == FileDialog.OpenFile){
                 _editContainerComponent.fileListModel.initItem(_fileDialog.file)
            }else if (_fileDialog.fileMode == FileDialog.SaveFile){
                _mdcore.mdRes = ""
                _editContainerComponent.fileListModel.initItems(defaltFolderUrl)
            }
            console.log("Qt.platform.os:",Qt.platform.os)
            if(Qt.platform.os==="windows"){
                _mdcore.fileName=_fileDialog.file.toString().substr(8)
            }else if (Qt.platform.os==="osx"){
                _mdcore.fileName=_fileDialog.file.toString().substr(7)
            }else if (Qt.platform.os==="linux"){
                _mdcore.fileName=_fileDialog.file.toString().substr(7)
            }
        }
    }

    Row{
        id: _editToolBar
        spacing: 2
        anchors.verticalCenter: parent.verticalCenter

        Action {
            id: blodAction
            shortcut: "Ctrl+B"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"**"+_editContainerComponent.textIns.selectedText+"**")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"**粗体**")
                }
            }
        }

        Action {
            id: italicAction
            shortcut: "Ctrl+I"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"*"+_editContainerComponent.textIns.selectedText+"*")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"*斜体*")
                }
            }
        }

        Action {
            id: deleteLineAction
            shortcut: "Ctrl+D"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"~~"+_editContainerComponent.textIns.selectedText+"~~")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"~~删除线~~")
                }
            }
        }

        Action {
            id: codeAction
            shortcut: "Ctrl+Alt+P"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"\n```\n"+_editContainerComponent.textIns.selectedText+"\n```\n")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"\n```\n#插入代码\n```\n")
                }
            }
        }

        Action {
            id: numListAction
            shortcut: "Ctrl+L"
            onTriggered: {
                _editContainerComponent.textIns.append("\n1. 有序列表 \n2. \n")
            }
        }

        Action {
            id: noNumListAction
            shortcut: "Ctrl+Alt+L"
            onTriggered: {
                _editContainerComponent.textIns.append("\n- 无序列表 \n- \n")
            }
        }

        Action {
            id: h1Action
            shortcut: "Ctrl+1"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"# "+_editContainerComponent.textIns.selectedText+"\n")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"\n# 标题一\n")
                }
            }
        }

        Action {
            id: h2Action
            shortcut: "Ctrl+2"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"## "+_editContainerComponent.textIns.selectedText+"\n")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"\n## 标题二\n")
                }
            }
        }

        Action {
            id: h3Action
            shortcut: "Ctrl+3"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"### "+_editContainerComponent.textIns.selectedText+"\n")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"\n### 标题三\n")
                }
            }
        }

        Action {
            id: h4Action
            shortcut: "Ctrl+4"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"#### "+_editContainerComponent.textIns.selectedText+"\n")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"\n#### 标题四\n")
                }
            }
        }

        Action {
            id: h5Action
            shortcut: "Ctrl+5"
            onTriggered: {
                if(_editContainerComponent.textIns.selectedText !==""){
                    _editContainerComponent.textIns.text = _editContainerComponent.textIns.text.replace(_editContainerComponent.textIns.selectedText,"##### "+_editContainerComponent.textIns.selectedText+"\n")
                }else{
                    _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"\n##### 标题五\n")
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
                    shortcut: "Ctrl+N"
                    onTriggered: {
                        console.log("测试新建文档")
                        _fileDialog.fileMode= FileDialog.SaveFile
                        _fileDialog.nameFilters=["Markdown (*.md)","All Files (*)"]
                        _fileDialog.open()
                    }
                }

               MenuItem {
                    text: "打开文档"
                    shortcut: "Ctrl+O"
                    onTriggered: {
                        console.log("测试打开文档")
                        _fileDialog.fileMode= FileDialog.OpenFile
                        _fileDialog.open()
                    }

                }


               MenuItem {
                    text: "打开文件夹"
                    shortcut: "Ctrl+Shft+O"
                    onTriggered: {
                        console.log("测试打开文件夹")
                        _folderDialog.open()
                    }

                }

                MenuItem {
                    text: "保存文档"
                    shortcut: "Ctrl+S"
                    onTriggered:{
                        console.log("测试保存文档")
                        _mdcore.mdRes = _editContainerComponent.textIns.text
                    }
                }
                MenuItem {
                    text: "另存为文档"
                    shortcut: "Ctrl+Shift+S"
                    onTriggered:{
                        console.log("测试另存为")
                        _fileDialog.fileMode= FileDialog.SaveFile
                        _fileDialog.open()
                    }
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
                        _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(0)")
                    }
                }
                MenuItem {
                    text: "han"
                    onTriggered: {
                        _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(1)")
                    }
                }
                MenuItem {
                    text: "mdhere"
                    onTriggered: {
                        _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(2)")
                    }
                }
            }
        }
    }

}
