// Copyright ChineSEngineer
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

void RBTree::del(RBTreeNode* to_delete) {
    if (to_delete == nullptr) {
        return;
    }

    RBTreeNode* real_delete;  //  The node which really disappears in term of color, to_delete's position&color may be taken over by the real_delete
    RBTreeNode* real_delete_successor;  //  The node which takes over real_delete's position
    RBTreeNode* real_delete_successor_new_parent;
    RBColor real_delete_color;

    real_delete = to_delete;
    real_delete_color = real_delete->color();
    if (to_delete->left() == nullptr) {
        real_delete_successor = to_delete->right();
        real_delete_successor_new_parent = real_delete->parent();
        this->transparent(to_delete, to_delete->right());
    } else if (to_delete->right() == nullptr) {
        real_delete_successor = to_delete->left();
        real_delete_successor_new_parent = real_delete->parent();
        this->transparent(to_delete, to_delete->left());
    } else {
        // node->left and node->right are not nullptr, thus successor should not be nullptr
        RBTreeNode* successor = minimum_subtree(to_delete->right());
        real_delete = successor;
        real_delete_color = real_delete->color();
        real_delete_successor = real_delete->right();
        if (successor->parent() == to_delete) {
            // real delete becomes real_delete_successor_new_parent after tranparent TODO(heyi): move this after transparent
            real_delete_successor_new_parent = real_delete;
            this->transparent(to_delete, successor);
            successor->set_left(to_delete->left());
            successor->left()->set_parent(successor);
            successor->set_color(to_delete->color());
        } else {
            real_delete_successor_new_parent = real_delete->parent();
            transparent(successor, successor->right());
            transparent(to_delete, successor);
            successor->set_left(to_delete->left());
            successor->left()->set_parent(successor);
            successor->set_right(to_delete->right());
            successor->right()->set_parent(successor);
            successor->set_color(to_delete->color());
        }
    }

    if (real_delete_color == RBColor::BLACK) {
        rb_delete_fixup(real_delete_successor_new_parent, real_delete_successor);
    }
    delete to_delete;
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
    if (node1 == nullptr || node1->right() == nullptr) {
        throw std::string(__FUNCTION__) + ":rotating node is nil";
    }

    RBTreeNode* node2 = node1->right();
    // node 1 adopt the node2's left child
    node1->set_right(node2->left());
    if (node2->left() != nullptr) {
        node2->left()->set_parent(node1);
    }
    // node1 release his parent to node2
    node2->set_parent(node1->parent());
    if (node1 == this->root()) {
        this->set_root(node2);
    } else {
        if (node1 == node1->parent()->left()) {
            node1->parent()->set_left(node2);
        } else {
            node1->parent()->set_right(node2);
        }
    }
    // relationship between node1 and node2
    node1->set_parent(node2);
    node2->set_left(node1);
}

void RBTree::right_rotate(RBTreeNode* node1) {
    if (node1 == nullptr || node1->left() == nullptr) {
        throw std::string(__FUNCTION__) + ":rotating node is nil";
    }

    RBTreeNode* node2 = node1->left();
    // node 1 adopt the node2's right child
    node1->set_left(node2->right());
    if (node2->right() != nullptr) {
        node2->right()->set_parent(node1);
    }
    // node1 release his parent to node2
    node2->set_parent(node1->parent());
    if (node1 == this->root()) {
        this->set_root(node2);
    } else {
        if (node1 == node1->parent()->left()) {
            node1->parent()->set_left(node2);
        } else {
            node1->parent()->set_right(node2);
        }
    }
    // relationship between node1 and node2
    node1->set_parent(node2);
    node2->set_right(node1);
}

void RBTree::rb_insert_fixup(RBTreeNode* node) {
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

// TODO(heyi): make search inheritance
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

// Make this static ?
bool is_red(RBTreeNode* node) {
    return node != nullptr && node->color() == RBColor::RED;
}

void RBTree::rb_delete_fixup(RBTreeNode* real_delete_successor_new_parent,
                             RBTreeNode* real_delete_successor) {
    RBTreeNode* node = real_delete_successor;
    RBTreeNode* node_parent;
    if (node != nullptr) {
        node_parent = node->parent();
    } else {
        node_parent = real_delete_successor_new_parent;
    }
    assert(node_parent != nullptr || node == root());

    while (node != root() && !is_red(node)) {
        if (node == node_parent->left()) {
            RBTreeNode* sibling = node_parent->right();
            assert(sibling != nullptr);   // Node is doubly black, its sibling cannot be nil
            if (sibling->color() == RBColor::RED) {
                sibling->set_color(RBColor::BLACK);
                node_parent->set_color(RBColor::RED);
                left_rotate(node_parent);
                sibling = node_parent->right();
                assert(sibling != nullptr);   // Color blance doesn't change, its sibling still cannot be nil
            }
            if (!is_red(sibling->left()) && !is_red(sibling->right())) {
                sibling->set_color(RBColor::RED);
                node = node_parent;
                node_parent = node->parent();
            } else {
                if (!is_red(sibling->right())) {
                    sibling->set_color(RBColor::RED);
                    sibling->left()->set_color(RBColor::BLACK);
                    right_rotate(sibling);
                    sibling = node_parent->right();
                    assert(sibling != nullptr);   // Color blance doesn't change, its sibling still cannot be nil
                }
                assert(is_red(sibling->right()));
                // assert(!is_red(sibling->left()));
                sibling->set_color(node_parent->color());
                node_parent->set_color(RBColor::BLACK);
                sibling->right()->set_color(RBColor::BLACK);
                left_rotate(node_parent);
                break;
            }
        } else {
            RBTreeNode* sibling = node_parent->left();
            assert(sibling != nullptr);
            if (sibling->color() == RBColor::RED) {
                sibling->set_color(RBColor::BLACK);
                node_parent->set_color(RBColor::RED);
                right_rotate(node_parent);
                sibling = node_parent->left();
                assert(sibling != nullptr);   // Color blance doesn't change, its sibling still cannot be nil
            }
            if (!is_red(sibling->left()) && !is_red(sibling->right())) {
                sibling->set_color(RBColor::RED);
                node = node_parent;
                node_parent = node_parent->parent();
            } else {
                if (!is_red(sibling->left())) {
                    sibling->set_color(RBColor::RED);
                    sibling->right()->set_color(RBColor::BLACK);
                    left_rotate(sibling);
                    sibling = node_parent->left();
                    assert(sibling != nullptr);   //  Color blance doesn't change, its sibling still cannot be nil
                }
                assert(is_red(sibling->left()));
                // assert(!is_red(sibling->right()));
                sibling->set_color(node_parent->color());
                node_parent->set_color(RBColor::BLACK);
                sibling->left()->set_color(RBColor::BLACK);
                right_rotate(node_parent);
                break;
            }
        }
    }
    if (node != nullptr) {
        node->set_color(RBColor::BLACK);
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

    while (node->parent() != nullptr) {
        if (node == node->parent()->left()) {
            return node->parent();
        } else {
            node = node->parent();
        }
    }
    return nullptr;
}


void RBTree::transparent(RBTreeNode* node1, RBTreeNode* node2) {
    assert(node1 != nullptr);

    if (node1 == root()) {
        set_root(node2);
        return;
    }
    if (node1 == node1->parent()->left()) {
        node1->parent()->set_left(node2);
    } else {
        node1->parent()->set_right(node2);
    }

    if (node2 != nullptr) {
        node2->set_parent(node1->parent());
    }
}

}  // namespace heyi
