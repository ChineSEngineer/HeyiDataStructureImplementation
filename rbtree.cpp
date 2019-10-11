#include <rbtree.h>
#include <string>


namespace heyi {

RBTree::RBTree() : Tree() {}

void RBTree::rb_insert(int value) {
    RBTreeNode* pre = nullptr;
    RBTreeNode* cur = root();
    if (root() == nullptr) {
        this->set_root(new RBTreeNode(value));
        return;
    }

    while(cur != nullptr) {
        if (cur->value() <= value) {
            cur = cur->left();
        } else {
            cur = cur->right();
        }
        pre = cur;
    }
    if(cur == pre->left()) {
        pre->set_left(new RBTreeNode(value));
        pre->left()->set_parent(pre);
        rb_insert_fixup(pre->left());
    } else {
        if(cur != pre->right())
            throw std::string(__FUNCTION__) + ": Wrong Pointer";
        pre->set_right(new RBTreeNode(value));
        pre->right()->set_parent(pre);
        rb_insert_fixup(pre->right());
    }
}

RBTreeNode* RBTree::rb_search(int value) {
    return rb_search_helper(root(), value);
}

/* Assume node1 is not null */
void RBTree::left_rotate(RBTreeNode* node1) {
    if(node1 == nullptr || node1->right() == nullptr) {
        throw std::string(__FUNCTION__) + ":rotating node is nil";
    }

    RBTreeNode* node2 = node1->right();
    //node 1 adopt the node2's left child
    node1->set_right(node2->left());
    if(node2->left()->parent() != nullptr) {
        node2->left()->set_parent(node1->right());
    }
    //node1 release his parent to node2
    if(node1 == this->root()) {
        this->set_root(node2);
    } else {
        node2->set_parent(node1->parent());
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

    RBTreeNode* node2 = (RBTreeNode*) node1->right();
    //node 1 adopt the node2's right child
    node1->set_left(node2->right());
    if(node2->right()->parent() != nullptr) {
        node2->right()->set_parent(node1->left());
    }
    //node1 release his parent to node2
    if(node1 == this->root()) {
        this->set_root(node2);
    } else {
        node2->set_parent(node1->parent());
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

}

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

} //heyi
