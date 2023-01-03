#include "treenode.h"

TreeNode::TreeNode()
{

}

TreeNode* TreeNode::parent() const{
    return _mParent;
}

void TreeNode::setParent(TreeNode* _pNode){
    this->_mParent = _pNode;
}

void TreeNode::appendNode(TreeNode* _node){
    childs.append(_node);
}

void TreeNode::removeNode(int row){
    childs.removeAt(row);
}

QVariant TreeNode::data(int role){
    return _mRecord[role];
}

void TreeNode::setData(int role,QVariant value){
    _mRecord[role]=value;
}


