#ifndef TREE_H
#define TREE_H
namespace heyi {
class TreeNode {
  private:
    TreeNode* _left;
    TreeNode* _right;
    TreeNode* _p;
    int _value;
  public:
    TreeNode(int value) {
        this->set_value(value);
        this->set_left(nullptr);
        this->set_right(nullptr);
        this->set_parent(nullptr);
    }
    virtual ~TreeNode() {}
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

  private:
    int height_helper(TreeNode*);
};

//TODO: destructor!!!
class Tree {
  private:
    TreeNode* _root;
  public:
    Tree();
    virtual ~Tree() {}
    virtual TreeNode* root() { return _root; }
    void set_root(TreeNode* root) {_root = root;}

    int height();
    TreeNode* dfs_search(int value);
  private:
    TreeNode* dfs_search_helper(TreeNode* node, int value);
};

}//heyi

#endif //TREE_H
