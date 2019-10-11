#include <iostream>
#include <tree.h>
#include "PrintTree.cpp"

using namespace heyi;
using namespace std;

int main(int argc, char **argv) {
    cout << "Hello World!" <<endl;
    TreeNode* root = new TreeNode(1);
    root->set_left(new TreeNode(2));
    root->set_right(new TreeNode(3));
    root->left()->set_left(new TreeNode(4));
    //root->left()->set_right(new TreeNode(5));
    //root->right()->set_left(new TreeNode(6));
    root->right()->set_right(new TreeNode(7));
    Tree* tree = new Tree(root);
    PrintTree::print_tree(tree, 1);
}

