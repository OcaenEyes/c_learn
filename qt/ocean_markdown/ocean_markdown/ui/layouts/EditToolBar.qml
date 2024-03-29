import QtQuick 2.15
import QtQuick.Controls
import Qt.labs.platform
import QtWebEngine 1.9

Item {
    width:parent.width
    height:parent.height


    property string pdfUrl: ""

    property string picUrl: ""

    property string htmlFile: ""

    FolderDialog {
        id: _folderDialog
        folder: _window.defaltFolderUrl
        acceptLabel: "确定"
        rejectLabel: "取消"
        options: FileDialog.ShowDirsOnly
//        onAccepted: {
//            _window.defaltFolderUrl= currentFolder
//            console.log("当前路径：",_window.defaltFolderUrl)
//            _window.fileListModel.initItems(_window.defaltFolderUrl)

//        }
        onFolderChanged: {
            _window.defaltFolderUrl= _folderDialog.folder
            console.log("修改了folder以后当前路径：",_window.defaltFolderUrl)
            _window.fileListModel.initItems(_window.defaltFolderUrl)
        }
    }

    FileDialog{
        id :_fileDialog
        acceptLabel: "确定"
        rejectLabel: "取消"
        objectName: "readLocalFile"
//        onAccepted: {
//            _window.defaltFolderUrl= _fileDialog.folder
//            console.log("打开的新文档路径：",_fileDialog.file)
//        }
        onFileChanged:  {
            _window.defaltFolderUrl= _fileDialog.folder
            console.log("打开的新文档路径：",_fileDialog.file)
            console.log("Qt.platform.os:",Qt.platform.os)
            if(Qt.platform.os==="windows"){
                _window.curFileUrl = _fileDialog.file.toString().substr(8)
            }else if (Qt.platform.os==="osx"){
                _window.curFileUrl = _fileDialog.file.toString().substr(7)
            }else if (Qt.platform.os==="linux"){
                _window.curFileUrl = _fileDialog.file.toString().substr(7)
            }
            _window._mdcore.fileName = _window.curFileUrl

            if(_fileDialog.fileMode == FileDialog.OpenFile){
                _window.fileListModel.initItem(_fileDialog.file)
            }else if (_fileDialog.fileMode == FileDialog.SaveFile){
                _window.fileListModel.initItems(_window.defaltFolderUrl)
            }  
        }
    }

    FileDialog {
        id : _fileDialogToSave
        acceptLabel: "确定"
        rejectLabel: "取消"
        onFileChanged:  {
            _window.defaltFolderUrl= _fileDialogToSave.folder
            console.log("打开的新文档路径：",_fileDialogToSave.file)
            console.log("Qt.platform.os:",Qt.platform.os)
            if(Qt.platform.os==="windows"){
                _window.curFileUrl = _fileDialogToSave.file.toString().substr(8)
            }else if (Qt.platform.os==="osx"){
                _window.curFileUrl = _fileDialogToSave.file.toString().substr(7)
            }else if (Qt.platform.os==="linux"){
                _window.curFileUrl = _fileDialogToSave.file.toString().substr(7)
            }
            _window._mdcore.newFileName = _window.curFileUrl
            _window.fileListModel.initItems(_window.defaltFolderUrl)
        }
    }


    FileDialog{
        id:_savePdf
        acceptLabel: "确定"
        rejectLabel: "取消"
        fileMode: FileDialog.SaveFile
        nameFilters:["PDF (*.pdf)","All Files (*)"]
        onFileChanged:  {
            if(Qt.platform.os==="windows"){
                pdfUrl = _savePdf.file.toString().substr(8)
            }else if (Qt.platform.os==="osx"){
                pdfUrl = _savePdf.file.toString().substr(7)
            }else if (Qt.platform.os==="linux"){
                pdfUrl = _savePdf.file.toString().substr(7)
            }
            console.log(pdfUrl)
            _editContainerComponent.textOuts.printToPdf(pdfUrl)
        }
    }

    FileDialog{
        id:_savePng
        acceptLabel: "确定"
        rejectLabel: "取消"
        fileMode: FileDialog.SaveFile
        nameFilters:["PNG (*.png)","JPEG (*.jpeg)","All Files (*)"]
        onFileChanged:  {
            if(Qt.platform.os==="windows"){
                picUrl = _savePng.file.toString().substr(8)
            }else if (Qt.platform.os==="osx"){
                picUrl = _savePng.file.toString().substr(7)
            }else if (Qt.platform.os==="linux"){
                picUrl = _savePng.file.toString().substr(7)
            }
            console.log(picUrl)
            _editContainerComponent.textOuts.grabToImage(
                        function(res){
                            res.saveToFile(picUrl)
                        }
            )
        }
    }

    FileDialog{
        id:_saveHtml
        acceptLabel: "确定"
        rejectLabel: "取消"
        fileMode: FileDialog.SaveFile
        nameFilters:["Html (*.html)","All Files (*)"]
        onFileChanged:  {
            if(Qt.platform.os==="windows"){
                htmlFile = _saveHtml.file.toString().substr(8)
            }else if (Qt._saveHtml.os==="osx"){
                htmlFile = _saveHtml.file.toString().substr(7)
            }else if (Qt.platform.os==="linux"){
                htmlFile = _saveHtml.file.toString().substr(7)
            }
            console.log(htmlFile)
            // _editContainerComponent.textOuts.runJavaScript("document.documentElement.outerHTML",
            //                                                function(res){
            //                                                   console.log(res)
            //                                                }
            //                                               )
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
            id :equationAction
            onTriggered: {
                _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"\n```\n$$\n y=x+1 \n$$\n```\n")
            }
        }

        Action {
            id :picAction
            onTriggered: {
                _editContainerComponent.textIns.insert(_editContainerComponent.textIns.cursorPosition,"\n![图片名字](图片地址)\n")
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
        Action {
            id:inTableAction
            shortcut: "Ctrl+6"
            onTriggered: {
                _editContainerComponent.textIns.insert(
                            _editContainerComponent.textIns.cursorPosition,
                            "\n|  表头   | 表头  |\n|  ----    | ----   |\n| 单元格  | 单元格 |\n| 单元格  | 单元格 |\n")
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
                        _window._mdcore.mdRes = _editContainerComponent.textIns.text
                    }
                }
                MenuItem {
                    text: "另存为文档"
                    shortcut: "Ctrl+Shift+S"
                    onTriggered:{
                        console.log("测试另存为")
                        _fileDialogToSave.fileMode= FileDialog.SaveFile
                        _fileDialogToSave.nameFilters=["Markdown (*.md)","All Files (*)"]
                        _fileDialogToSave.open()
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
            id: _inTable
            text: "表格"
            action: inTableAction
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
            id: _equationBlock
            text: "公式"
            action: equationAction
        }

        ToolButton{
            id: _picBlock
            text: "插入图片"
            action: picAction
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
                Menu{
                    title:"桌面主题"
                    MenuItem {
                        text: "sspai"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(0)")
                        }
                    }
                    MenuItem {
                        text: "typora-han"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(1)")
                        }
                    }
                    MenuItem {
                        text: "markdownhere"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(2)")
                        }
                    }
                    MenuItem {
                        text: "github"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(3)")
                        }
                    }
                    MenuItem {
                        text: "科技蓝"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(4)")
                        }
                    }
                }
                Menu {
                    title:"微信公众号主题"
                    MenuItem {
                        text: "微信-全栈蓝"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(5)")
                        }
                    }
                    MenuItem {
                        text: "微信-天青"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(6)")
                        }
                    }
                    MenuItem {
                        text: "微信-极客黑"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(7)")
                        }
                    }
                    MenuItem {
                        text: "微信-墨水黑"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(8)")
                        }
                    }
                    MenuItem {
                        text: "微信-山吹"
                        onTriggered: {
                            _editContainerComponent.textOuts.runJavaScript("changeMarkDownStyle(9)")
                        }
                    }
                }
            }
        }

        ToolButton{
            id:_toOut
            text:"小工具"
            onClicked:{
                _toOutMenu.open()
            }
            Menu{
                id: _toOutMenu
                MenuItem {
                    text: "导出PDF"
                    onTriggered: {
                        _savePdf.open()
                    }
                }
//                MenuItem {
//                    text: "导出图片"
//                    onTriggered: {
//                        _savePng.open()
//                    }
//                }
                MenuItem {
                    text: "切换显示模式"
                    onTriggered: {
//                        _saveHtml.open()
                        _editContainerComponent.isShowSrcCode = !_editContainerComponent.isShowSrcCode
                        _editContainerComponent.textOuts.runJavaScript("document.getElementById('placeholder').outerHTML",
                                                                                                    function(res){
                                                                                                       console.log(res.toString())
                                                                                                      _editContainerComponent.codeSrc.text = res.toString()
                                                                                                    }
                                                                                                   )

                    }
                }
            }
        }

        ToolButton {
            id: _aboutModule
            text: "关于"
            onClicked: _aboutModuleMenu.open()
            Menu{
                id: _aboutModuleMenu
                MenuItem {
                    text: "关于作者"
                    onTriggered: {
                        _aboutmeWin.show()
                    }
                }
                MenuItem {
                    text: "关于软件"
                    onTriggered: {
                        _aboutsoftwareWin.show()
                    }
                }
            }
        }

        AboutMe{
            id: _aboutmeWin
        }

        AboutSoftWare{
            id: _aboutsoftwareWin
        }

    }

}
