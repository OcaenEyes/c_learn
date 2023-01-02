import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import QtWebChannel 1.0

Window {
    id : _window
    width: 1000
    height: 800
    visible: true
    title: qsTr("Ocean MarkDown")
    property int curPageIndex: 3

    WebChannel {
        id: _mainWindowChannel
        registeredObjects: [editPage]
    }

    // 1个主页+3个内容界面
    Item {
        id:page
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.right: parent.right

        HomePage {
            id: homePage
            anchors.centerIn: parent
            visible: curPageIndex ==3
        }

        FilePage {
            id: filePage
            anchors.centerIn: parent
            visible: curPageIndex == 0
        }

        EditPage {
            id: editPage
//            anchors.centerIn: parent
            WebChannel.id: "editPage"
            visible: curPageIndex == 1
        }

        SettingPage {
            id: settingPage
            anchors.centerIn: parent
            visible: curPageIndex == 2
        }
    }

    Rectangle {
        id: rectMenu
        width: 40
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
        color: "#f4f4f4"
//        border.color: "#999"
    }

    RepeaterMenu {
        id: repeaterMenu
        anchors.fill: rectMenu
        maxWidth: rectMenu.width
        maxHeight: rectMenu.height
        listMode: [
            {
                name: qsTr("文件"),
                iconSource:     "/assets/images/file.png"
            },
            {
                name: qsTr("编辑"),
                iconSource:     "/assets/images/edit.png"
            },
            {
                name: qsTr("设置"),
                iconSource:     "/assets/images/setting.png"
            },
        ]

        // 信号连接器
        Connections {
            target: repeaterMenu
            function onPageSig(idx) {
//                console.log("触发pageSig -idx:"+idx)
                curPageIndex = idx // idx为PageSig信号的输入参数
//                console.log("触发pageSig -当前curPageIndex:"+curPageIndex)
            }
        }
    }
}
