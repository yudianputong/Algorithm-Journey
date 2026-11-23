/**
 * @file 0105_Construct_Binary_Tree_from_Preorder_and_Inorder_Traversal.cpp
 * @brief 105. 从前序与中序遍历序列构造二叉树
 * @link https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 *
 * @algorithm 递归分治 + 哈希表
 * @time_complexity 平均 O(N)：每个节点构造一次，哈希表查找平均 O(1)。
 * @space_complexity O(N)：哈希表和递归调用栈；不计返回的树。
 *
 * 前序：根、左、右；中序：左、根、右。
 * 前序序列依次提供根节点；在中序序列中找到根，就能分出左右子树。
 * 题目保证节点值互不相同，两个遍历序列对应同一棵树。
 *
 * 例如 preorder = [3,9,20,15,7]，inorder = [9,3,15,20,7]：
 * 前序第一个数 3 是根；中序中 3 的左边 [9] 是左子树，
 * 右边 [15,20,7] 是右子树。对左右子树重复这个过程。
 */

#include <vector>
#include <unordered_map>
using namespace std;

// 力扣已提供 TreeNode 定义，提交时只需复制 Solution。
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> position; // 节点值 -> 其在中序序列中的下标
        for (int i = 0; i < static_cast<int>(inorder.size()); ++i) {
            position[inorder[i]] = i;
        }

        int preIndex = 0; // 下一个要取的前序节点
        return build(preorder, position, preIndex, 0,
                     static_cast<int>(inorder.size()) - 1);
    }

private:
    // 构造中序下标 [left, right] 对应的子树，并返回它的根节点。
    TreeNode* build(const vector<int>& preorder,
                    const unordered_map<int, int>& position,
                    int& preIndex, int left, int right) {
        if (left > right) return nullptr; // 这段范围为空，没有子节点

        int rootValue = preorder[preIndex++]; // 前序中下一个节点是当前子树的根
        TreeNode* root = new TreeNode(rootValue);
        int mid = position.at(rootValue); // 在中序序列中定位根

        // 前序顺序是根、左、右，因此必须先构造左子树。
        root->left = build(preorder, position, preIndex, left, mid - 1);
        root->right = build(preorder, position, preIndex, mid + 1, right);
        return root;
    }
};
