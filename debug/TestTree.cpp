#include <iostream>
#include <rbtree.h>
#include <tree.h>
#include "PrintTree.cpp"

using namespace heyi;
using namespace std;

int main(int argc, char **argv) {

    TreeNode* root = new TreeNode(1);
    root->set_left(new TreeNode(2));
    root->set_right(new TreeNode(3));
    root->left()->set_left(new TreeNode(4));
    root->left()->set_right(new TreeNode(5));
    root->right()->set_left(new TreeNode(6));
    root->right()->set_right(new TreeNode(7));
    root->left()->left()->set_left(new TreeNode(8));
    root->left()->left()->set_right(new TreeNode(9));
    root->left()->right()->set_left(new TreeNode(10));
    root->left()->right()->set_right(new TreeNode(11));
    root->right()->left()->set_left(new TreeNode(12));
    root->right()->left()->set_right(new TreeNode(13));
    root->right()->right()->set_left(new TreeNode(14));
    root->right()->right()->set_right(new TreeNode(15));
    Tree* tree = new Tree(root);
    PrintTree::print_tree(tree, 2);
    
    RBTree* rb_tree = new RBTree();
    rb_tree->insert(1);
    rb_tree->insert(3);
    rb_tree->insert(2);
    rb_tree->insert(4);
    rb_tree->insert(5);
    rb_tree->insert(10);
    rb_tree->insert(30);
    rb_tree->insert(20);
    rb_tree->insert(40);
    rb_tree->insert(50);
    rb_tree->insert(100);
    rb_tree->insert(300);
    rb_tree->insert(200);
    rb_tree->insert(400);
    rb_tree->insert(500);
    PrintTree::print_tree(rb_tree, 3);
    rb_tree->insert(-1);
    rb_tree->insert(-3);
    rb_tree->insert(-2);
    rb_tree->insert(-4);
    rb_tree->insert(-5);
    rb_tree->insert(-10);
    rb_tree->insert(-30);
    rb_tree->insert(-20);
    rb_tree->insert(-40);
    rb_tree->insert(-50);
    rb_tree->insert(-100);
    rb_tree->insert(-300);
    rb_tree->insert(-200);
    rb_tree->insert(-400);
    rb_tree->insert(-500);
    PrintTree::print_tree(rb_tree, 4);

    TreeNode* tn = tree->search(1);
    RBTreeNode* rbn = rb_tree->search(1);
    
}

