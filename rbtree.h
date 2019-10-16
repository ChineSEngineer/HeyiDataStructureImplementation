#ifndef RBTREE_H
#define RBTREE_H

#include <tree.h>

namespace heyi {

enum class RBColor {
    BLACK,
    RED
};

class RBTreeNode : public TreeNode {
  public:
    RBColor _color;
    RBTreeNode(int value) : TreeNode(value) {
        this->set_color(RBColor::BLACK);
    }
    RBTreeNode(int value, RBColor color) : TreeNode(value) {
        this->set_color(color);
    }
    virtual ~RBTreeNode() {}
    virtual RBTreeNode* left() override {
        return static_cast<RBTreeNode*>(TreeNode::left());
    }
    virtual RBTreeNode* right() override {
        return  static_cast<RBTreeNode*>(TreeNode::right());
    }
    virtual RBTreeNode* parent() override {
        return static_cast<RBTreeNode*>(TreeNode::parent());
    }
    RBColor color() {
        return _color;
    }
    void set_color(RBColor color) {
        _color = color;
    }
};

class RBTree : public Tree {
  public:
    RBTree();
    virtual ~RBTree();
    virtual void insert(int value);
    RBTreeNode* search(int value) override;
    //void rb_delete(RBTree* rbtree, int value);
  private:
    virtual RBTreeNode* root() override; 
    using Tree::set_root;
    void left_rotate(RBTreeNode* node1);
    void right_rotate(RBTreeNode* node1);
    void rb_insert_fixup(RBTreeNode* node);
    RBTreeNode* rb_search_helper(RBTreeNode*, int value);
    void rb_delete_fixup(RBTreeNode* node);
};

} //heyi

#endif //RBTREE_H
