#include <rbtree.h>

#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>

#define UNDERLINE_OUTPUT "\033[4m"
#define NORMAL_OUTPUT "\033[0m"
#define RED_UNDERLINE_OUTPUT "\033[4;31m"


std::ostream& operator<<(std::ostream& os, heyi::TreeNode* node) {
    if (node == nullptr) {
        return os;
    }
    heyi::RBTreeNode* rb_node = dynamic_cast<heyi::RBTreeNode*>(node);
    if (rb_node  != nullptr && rb_node->color() == heyi::RBColor::RED) {
        os << RED_UNDERLINE_OUTPUT << rb_node->value() << NORMAL_OUTPUT;
    } else {
        os << UNDERLINE_OUTPUT << node->value() << NORMAL_OUTPUT;
    }
    return os;
}


namespace heyi{

using namespace std;



class PrintTree {
  public:

    static void print_tree(Tree* tree, int ele_length) {
        print_subtree(tree->root(), ele_length);
    }

    static void print_subtree(TreeNode* node, int ele_length) {
        unordered_map<TreeNode*, int> ump;
        calculate_subtree_width(node, ump);

        queue<TreeNode*> queue;
        queue.push(node);

        int i = 0;
        while (i <= node->height()) {
            i++;
            int sz = queue.size();
            for (int i = 0; i < sz; i++) {
                TreeNode* old = queue.front();
                queue.pop();
                if (old != nullptr) {
                    queue.push(old->left());
                    queue.push(old->right());
                } else {
                    queue.push(nullptr);
                }
                print_node(old, ele_length, ump);
            }
            cout << endl;
        }
        
    }

    static int calculate_subtree_width(TreeNode* node, unordered_map<TreeNode*, int>& ump) {
        int width = 0;

        if (node == nullptr) {
            width = 0;
        } else if (node->left() == nullptr && node->right() == nullptr) {
            width = 1;
        } else {
            width = 1 + calculate_subtree_width(node->left(), ump) + calculate_subtree_width(node->right(), ump);
        }

        ump[node] = width; 
        return width; 
    }

  private:
    void static print_node(TreeNode* old, int ele_length, unordered_map<TreeNode*, int>& ump) {
        if (old == nullptr) {
            cout << setw(ele_length) << "";
            return; 
        }
        if (old->left() != nullptr) {
            if (old->left()->left() != nullptr) {
                cout << setw(ele_length * ump[old->left()->left()]) << "";
            } 
            cout << UNDERLINE_OUTPUT 
                 << setw(ele_length) << "" 
                 << NORMAL_OUTPUT;
            if (old->left()->right() != nullptr) {
                cout << UNDERLINE_OUTPUT 
                     << setw(ele_length * ump[old->left()->right()]) << "" 
                     << NORMAL_OUTPUT;
            } 
        }
        int val_length = std::to_string(old->value()).length();
        cout << UNDERLINE_OUTPUT << left
             << setw((ele_length - val_length) / 2) << "" 
             << NORMAL_OUTPUT << right;
        cout << old;  // ostream overload
        cout << UNDERLINE_OUTPUT
             << setw((ele_length - val_length + 1) / 2) << "" 
             << NORMAL_OUTPUT;
        if (old->right() != nullptr) { 
            if (old->right()->left() != nullptr) {
                cout << UNDERLINE_OUTPUT 
                     << setw(ele_length * ump[old->right()->left()]) << "" 
                     << NORMAL_OUTPUT;
            } 
            cout << UNDERLINE_OUTPUT 
                 << setw(ele_length) << "" 
                 << NORMAL_OUTPUT;
            if (old->right()->right() != nullptr) {
                cout << setw(ele_length * ump[old->right()->right()]) << "";
            } 
        }
        cout << NORMAL_OUTPUT;
        cout << setw(ele_length) << "";
    }


};

} //heyi
