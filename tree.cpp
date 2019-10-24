#include <tree.h>

namespace heyi {

TreeNode::~TreeNode() {
}

int TreeNode::height() {
    if(this->left() == nullptr && this->right() == nullptr) {
        return 0;
    }
    
    int lh = 0, rh = 0;
    if (this->left() != nullptr) {
        lh = this->left()->height();
    }
    if (this->right() != nullptr) {
        rh = this->right()->height();
    } 
    if (lh > rh) {
        return lh + 1;
    } else {
        return rh + 1;
    }
}

int TreeNode::depth() {
    TreeNode* cur = this;
    int depth = 0;
    while(cur->parent() != nullptr) {
        cur = cur->parent();
        depth += 1;
    }
    return depth;
}

Tree::Tree() {
    this->set_root(nullptr);
}

Tree::Tree(TreeNode* root) {
    this->set_root(root);
}

Tree::~Tree() {
    delete_subtree(this->root());
}

void Tree::set_root(TreeNode* root) {
    _root = root; 
    if (root != nullptr) {
        root->set_parent(nullptr);
    }
}

int Tree::height() {
    if (this->root() == nullptr) {
        return 0;
    }
    return this->root()->height();
}

TreeNode* Tree::search(int value) {
    return search_subtree(root(), value);
}

TreeNode* Tree::search_subtree(TreeNode* node, int value) {
    return nullptr;
}

void Tree::delete_subtree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    if (node->left() != nullptr) {
        delete_subtree(node->left());
    }
    if (node->right() != nullptr) {
        delete_subtree(node->right());
    }

    delete node;
}

} //heyi
