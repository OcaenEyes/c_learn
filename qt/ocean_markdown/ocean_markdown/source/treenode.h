#ifndef TREENODE_H
#define TREENODE_H

#include <QVariant>

//class TreeNode;
//typedef TreeNode* TreeNodePtr;

class TreeNode
{
public:
    TreeNode();
    TreeNode* parent() const;
    void setParent(TreeNode* _pNode);
    void appendNode(TreeNode* _node);
    void removeNode(int row);
    QVariant data(int role);
    void setData(int role,QVariant value);
    QList<TreeNode*> childs;

private:
    TreeNode* _mParent = NULL;
    QHash<int,QVariant> _mRecord;
};

#endif // TREENODE_H
