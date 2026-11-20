/**
 * @file 101_Symmetric_Tree.cpp
 * @algorithm 队列 BFS (镜像比较)，附递归 DFS 参考
 * @time_complexity O(N)
 * @space_complexity O(N) - 队列最坏情况下需要存储 O(N) 个节点
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// class Solution {
// public:
//     bool isSymmetric(TreeNode* root) {
//         if (!root) return true;
//         return check(root->left, root->right);
//     }

// private:
//     // 侯捷视角：递归函数的设计必须保证逻辑完备性
//     bool check(TreeNode* p, TreeNode* q) {
//         // 1. 终止条件：双空则镜像
//         if (!p && !q) return true;
//         // 2. 终止条件：一空一非空，或值不等，则非镜像
//         if (!p || !q || p->val != q->val) return false;
        
//         // 3. 递归：外侧比外侧，内侧比内侧
//         return check(p->left, q->right) && check(p->right, q->left);
//     }
// };

#include <queue>

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true; // 空树对称

        std::queue<TreeNode*> q;
        q.push(root->left);               // 第一对：左子树与右子树
        q.push(root->right);

        while (!q.empty()) {
            TreeNode* u = q.front(); q.pop(); // 每次取出一对节点
            TreeNode* v = q.front(); q.pop();

            if (!u && !v) continue; // 两个都是空节点
            if (!u || !v || u->val != v->val)
                return false;       // 只有一个为空，或节点值不同

            q.push(u->left);  q.push(v->right); // 外侧配对
            q.push(u->right); q.push(v->left);  // 内侧配对
        }
        return true; // 所有节点对都匹配
    }
};
