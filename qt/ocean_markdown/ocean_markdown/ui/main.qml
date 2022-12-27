import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("OceanMarkDown")
    property int curPageIndex: 3

    // 1个主页+3个内容界面
    Item {
        id:page
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.right: parent.right

        Text{
            id: mainPage
            anchors.centerIn: parent
            text: "这是主页"
            visible: curPageIndex ==3
        }

        Text{
            id: firstPage
            anchors.centerIn: parent
            text: "这是页面1"
            visible: curPageIndex == 0
        }

        Text{
            id: secondPage
            anchors.centerIn: parent
            text: "这是页面2"
            visible: curPageIndex == 1
        }

        Text{
            id: thirdPage
            anchors.centerIn: parent
            text: "这是页面3"
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
                name: qsTr("文件")
            },
            {
                name: qsTr("编辑")
            },
            {
                name: qsTr("设置")
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
