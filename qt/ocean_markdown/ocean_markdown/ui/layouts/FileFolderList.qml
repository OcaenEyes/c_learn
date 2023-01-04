import QtQuick
import QtQuick.Controls

Item {
    width: parent.width
    height:parent.height
    TreeView {
        anchors.fill: parent
        model:_fileListModel
         //可以用预定义的TreeViewDelegate样式，也可以自定义
        //delegate: TreeViewDelegate { }
        delegate: Item {
            id: _fileLists
            implicitWidth: padding + label.x + label.implicitWidth + padding
            implicitHeight: label.implicitHeight * 1

            readonly property real indent: 5
            readonly property real padding: 2

            //标记为required的属性将由TreeView填充，与附加属性类似。
            //delegate间接通知TreeView它应该负责为它们分配值。可以将以下必需属性添加到delegate：
            //
            //指向包含delegate Item的TreeView
            required property TreeView treeView
            //项目是否代表树中的一个节点
            //视图中只有一列将用于绘制树，因此，只有该列中的delegate Item项才会将此属性设置为true。
            //树中的节点通常应根据其缩进，如果是则depth显示指示符。
            //其他列中的delegate Item将将此属性设置为，并将显示模型中其余列的数据（通常不缩进）。
            required property bool isTreeNode
            //绘制的model Item是否在视图中展开
            required property bool expanded
            //绘制的model Item是否在模型中有子项
            required property int hasChildren
            //包含delegate绘制的model Item的深度。model Item的深度与其在模型中的祖先数量相同
            required property int depth

            TapHandler {
                onTapped: treeView.toggleExpanded(row)
            }


            Text {
                id: indicator
                visible: isTreeNode && hasChildren
                x: padding + (depth * indent)
                y: label.implicitHeight * 0.2
                text: expanded ? "▼" : "▶"
                anchors.leftMargin: 8
            }
            MenuItem {
                id: label
                x: padding + (_fileLists.isTreeNode ? (_fileLists.depth + 1) * _fileLists.indent : 0)
                width: _fileLists.width - _fileLists.padding - x
                clip: true
                text: model.name
                onTriggered: {
                    if (!isTreeNode){
                        console.log(model.fPath)
                    }
                }
            }
        }
    }
}
