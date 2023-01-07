import QtQuick
import QtQuick.Controls
Window{
    width: 300
    height: 260
    title: qsTr("关于作者")

    Column{
        anchors.centerIn: parent


        Text{
            text:"作者:OCEANGZY"
            font.pixelSize: 16
        }

        ToolButton{
            text:"个人博客"
            font.pixelSize: 16
            onClicked: {
                Qt.openUrlExternally("http://oceaneyes.top")
            }
        }
        ToolButton{
            text:"一些AI应用"
            font.pixelSize: 16
            onClicked: {
                Qt.openUrlExternally("http://ai.oceangzy.top")
            }
        }
        ToolButton{
            text:"网页版Markdown"
            font.pixelSize: 16
            onClicked: {
                Qt.openUrlExternally("http://note.oceangzy.top")
            }
        }
        ToolButton{
            text:"好用的导航"
            font.pixelSize: 16
            onClicked: {
                Qt.openUrlExternally("http://pmhub.oceangzy.top")
            }
        }
    }
}
