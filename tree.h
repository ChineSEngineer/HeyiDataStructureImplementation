// Copyright ChineSEngineer
#ifndef TREE_H_
#define TREE_H_
namespace heyi {
class TreeNode {
 private:
    TreeNode* _left;
    TreeNode* _right;
    TreeNode* _p;
    int _value;

 public:
    explicit TreeNode(int value) {
        this->set_value(value);
        this->set_left(nullptr);
        this->set_right(nullptr);
        this->set_parent(nullptr);
    }
    virtual ~TreeNode();
    virtual TreeNode* left() { return _left; }
    virtual TreeNode* right() { return _right; }
    virtual TreeNode* parent() { return _p; }
    int value() { return _value; }
    void set_left(TreeNode* node) { _left = node; }
    void set_right(TreeNode* node) { _right = node; }
    void set_parent(TreeNode* node) { _p = node; }
    void set_value(int value) { _value = value; }

    int height();
    int depth();
    TreeNode* successor(TreeNode* node);

 private:
    int height_helper(TreeNode*);
};

// TODO(heyi): destructor!!!
class Tree {
 private:
    TreeNode* _root;

 public:
    Tree();
    explicit Tree(TreeNode* root);
    virtual ~Tree();
    virtual TreeNode* root() { return _root; }
    void set_root(TreeNode* root);

    int height();
    virtual TreeNode* search(int value);

 private:
    TreeNode* search_subtree(TreeNode* node, int value);
    void delete_subtree(TreeNode* node);
};

}  // namespace heyi

#endif  // TREE_H_
