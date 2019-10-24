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

    RBTreeNode* rbn_1 = rb_tree->search(1);
    cout << "Search 1 in rbtree, got: " << rbn_1->value() << endl;
    RBTreeNode* rbn_3 = rb_tree->search(3);
    cout << "Search 3 in rbtree, got: " << rbn_3->value() << endl;
    RBTreeNode* rbn_500 = rb_tree->search(500);
    cout << "Search 500 in rbtree, got: " << rbn_500->value() << endl;
    RBTreeNode* rbn_n100 = rb_tree->search(-100);
    cout << "Search -100 in rbtree, got: " << rbn_n100->value() << endl;
    
    RBTreeNode* rbn1_suc = rb_tree->successor(rbn_1);
    cout << "Search successor of 1 in rbtree, got: " << rbn1_suc->value() << endl;
    RBTreeNode* rbn3_suc = rb_tree->successor(rbn_3);
    cout << "Search successor of 3 in rbtree, got: " << rbn3_suc->value() << endl;
    RBTreeNode* rbn500_suc = rb_tree->successor(rbn_500);
    cout << "Search successor of 500 in rbtree, got: 0x" << static_cast<void*>(rbn500_suc) << endl;
    RBTreeNode* rbnn100_suc = rb_tree->successor(rbn_n100);
    cout << "Search successor of -100 in rbtree, got: " << rbnn100_suc->value() << endl;

    cout << "Delete -100 from rbtree" << endl;
    rb_tree->del(rbn_n100);
    PrintTree::print_tree(rb_tree, 4);

    RBTreeNode* rbn_n50 = rb_tree->search(-50);
    cout << "Delete -50 from rbtree" << endl;
    rb_tree->del(rbn_n50);
    PrintTree::print_tree(rb_tree, 4);

    RBTreeNode* rbn_n1 = rb_tree->search(-1);
    cout << "Delete -1 from rbtree" << endl;
    rb_tree->del(rbn_n1);
    PrintTree::print_tree(rb_tree, 4);

    RBTreeNode* rbn_4 = rb_tree->search(4);
    cout << "Delete 4 from rbtree" << endl;
    rb_tree->del(rbn_4);
    PrintTree::print_tree(rb_tree, 4);

    RBTreeNode* rbn_5 = rb_tree->search(5);
    cout << "Delete 5 from rbtree" << endl;
    rb_tree->del(rbn_5);
    PrintTree::print_tree(rb_tree, 4);

    RBTreeNode* rbn_50 = rb_tree->search(50);
    cout << "Delete 50 from rbtree" << endl;
    rb_tree->del(rbn_50);
    PrintTree::print_tree(rb_tree, 4);

    RBTreeNode* rbn_400 = rb_tree->search(400);
    cout << "Delete 400 from rbtree" << endl;
    rb_tree->del(rbn_400);
    PrintTree::print_tree(rb_tree, 4);
    
}

