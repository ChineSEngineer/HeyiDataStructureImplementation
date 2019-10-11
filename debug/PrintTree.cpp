#include <tree.h>

#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>


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
        while (!queue.empty()) {
            int sz = queue.size();
            for (int i = 0; i < sz; i++) {
                TreeNode* old = queue.front();
                queue.pop();
                if (old != nullptr) {
                    queue.push(old->left());
                    queue.push(old->right());
                    if (old->left() != nullptr) {
                        cout << setw(ele_length * ump[old->left()]) << "";
                    }
                    cout << setw(ele_length) << old->value();
                    if (old->right() != nullptr) { 
                        cout << setw(ele_length * ump[old->right()]) << "";
                    }
                    cout << setw(ele_length) << "";
                } else {
                    cout << setw(ele_length) << "";
                }
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
    //void print_node(TreeNode* node, int depth) {
    //    int h = node->height();
    //}


};

} //heyi
