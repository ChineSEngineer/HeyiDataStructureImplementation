#include <rbtree.h>
#include <string>
#include <iostream>
#include <cassert>

namespace heyi {

RBTree::RBTree() : Tree() {}

RBTree::~RBTree() {}

void RBTree::insert(int value) {
    RBTreeNode* pre = nullptr;
    RBTreeNode* cur = root();

    while (cur != nullptr) {
        pre = cur;
        if (value < cur->value()) {
            cur = cur->left();
        } else {
            cur = cur->right();
        }
    }
    
    RBTreeNode* node = new RBTreeNode(value, RBColor::RED); 
    if (pre == nullptr) {
        this->set_root(node);
    } else {
        if (value < pre->value()) {
            pre->set_left(node);
        } else {
            pre->set_right(node);
        }
        node->set_parent(pre);
    }

    rb_insert_fixup(node);    
}

RBTreeNode* RBTree::search(int value) {
    return rb_search_helper(root(), value);
}

int RBTree::minimum() {
    assert(root() != nullptr);
    TreeNode* minimum_node = minimum_subtree(root());
    return minimum_node->value();
}

RBTreeNode* RBTree::root() {
    return static_cast<RBTreeNode*>(Tree::root());
}

/* Assume node1 and node1->right is not null */
void RBTree::left_rotate(RBTreeNode* node1) {
    if(node1 == nullptr || node1->right() == nullptr) {
        throw std::string(__FUNCTION__) + ":rotating node is nil";
    }

    RBTreeNode* node2 = node1->right();
    //node 1 adopt the node2's left child
    node1->set_right(node2->left());
    if(node2->left() != nullptr) {
        node2->left()->set_parent(node1);
    }
    //node1 release his parent to node2
    node2->set_parent(node1->parent());
    if(node1 == this->root()) {
        this->set_root(node2);
    } else {
        if(node1 == node1->parent()->left()) {
            node1->parent()->set_left(node2);
        } else {
            node1->parent()->set_right(node2);
        }
    }
    //relationship between node1 and node2
    node1->set_parent(node2);
    node2->set_left(node1);

}

void RBTree::right_rotate(RBTreeNode* node1) {
    if(node1 == nullptr || node1->left() == nullptr) {
        throw std::string(__FUNCTION__) + ":rotating node is nil";
    }

    RBTreeNode* node2 = (RBTreeNode*) node1->left();
    //node 1 adopt the node2's right child
    node1->set_left(node2->right());
    if(node2->right() != nullptr) {
        node2->right()->set_parent(node1);
    }
    //node1 release his parent to node2
    node2->set_parent(node1->parent());
    if(node1 == this->root()) {
        this->set_root(node2);
    } else {
        if(node1 == node1->parent()->left()) {
            node1->parent()->set_left(node2);
        } else {
            node1->parent()->set_right(node2);
        }
    }
    //relationship between node1 and node2
    node1->set_parent(node2);
    node2->set_right(node1);
}

void RBTree::rb_insert_fixup(RBTreeNode* node) {
    //TODO
    while (node != root()
           && node->parent()->color() == RBColor::RED) {
        if (node->parent() == node->parent()->parent()->left()) {
            RBTreeNode* uncle = node->parent()->parent()->right();
            if (uncle != nullptr && uncle->color() == RBColor::RED) {
                uncle->set_color(RBColor::BLACK);
                node->parent()->set_color(RBColor::BLACK);
                node->parent()->parent()->set_color(RBColor::RED);
                node = node->parent()->parent();
            } else {
                if (node == node->parent()->right()) {
                    node = node->parent();
                    left_rotate(node);
                }
                node->parent()->set_color(RBColor::BLACK);
                node->parent()->parent()->set_color(RBColor::RED);
                right_rotate(node->parent()->parent());
            }
        } else {
            RBTreeNode* uncle = node->parent()->parent()->left();
            if (uncle != nullptr && uncle->color() == RBColor::RED) {
                uncle->set_color(RBColor::BLACK);
                node->parent()->set_color(RBColor::BLACK);
                node->parent()->parent()->set_color(RBColor::RED);
                node = node->parent()->parent();
            } else {
                if (node == node->parent()->left()) {
                    node = node->parent();
                    right_rotate(node);
                }
                node->parent()->set_color(RBColor::BLACK);
                node->parent()->parent()->set_color(RBColor::RED);
                left_rotate(node->parent()->parent());
            }
        }
    }

    root()->set_color(RBColor::BLACK);
}

//TODO: make search inheritance
RBTreeNode* RBTree::rb_search_helper(RBTreeNode* node, int value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value == node->value()) {
        return node;
    } else if (value < node->value()) {
        return rb_search_helper(node->left(), value);
    } else {
        return rb_search_helper(node->right(), value);
    }
}

RBTreeNode* RBTree::minimum_subtree(RBTreeNode* node) {
    assert(node != nullptr);
    while (node->left() != nullptr) {
        node = node->left();
    }
    return node;
}

RBTreeNode* RBTree::successor(RBTreeNode* node) {
    assert(node != nullptr);
    if (node->right() != nullptr) {
        return minimum_subtree(node->right());
    }

    while(node->parent() != nullptr) {
        if (node == node->parent()->left()) {
            return node->parent();
        } else {
            node = node->parent();
        }
    }
    return nullptr;
}

} //heyi
