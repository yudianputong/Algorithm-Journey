/**
 * @file 0437_Path_Sum_III.cpp
 * @brief 437. 路径总和 III
 * @link https://leetcode.cn/problems/path-sum-iii/
 *
 * 路径不必从根节点开始，也不必到叶子节点结束，但必须从父节点向下。
 *
 * 方法一（Solution）：从每个节点出发，统计以它为起点的路径。
 * 时间复杂度最坏 O(N²)，递归栈 O(H)，H 是树高。
 *
 * 方法二（SolutionPrefixSum）：前缀和 + 哈希表。
 * 平均时间复杂度 O(N)，哈希表和递归栈最坏空间 O(N)。
 */

#include <unordered_map>
using namespace std;

// 力扣已提供 TreeNode 定义，提交时无需复制本定义。
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

// 方法一：先理解双层递归
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;

        // 路径的起点可以是当前节点，也可以在左子树或右子树。
        return countFrom(root, targetSum)
             + pathSum(root->left, targetSum)
             + pathSum(root->right, targetSum);
    }

private:
    // 统计必须从 node 出发、向下走，且路径和为 remaining 的路径。
    int countFrom(TreeNode* node, long long remaining) {
        if (node == nullptr) return 0;

        // 从起点走到当前节点，若总和恰好等于目标，找到一条。
        int count = (remaining == node->val) ? 1 : 0;
        long long nextRemaining = remaining - node->val;

        // 即使当前已经满足，也要继续找：后面可能有 0 或负数。
        count += countFrom(node->left, nextRemaining);
        count += countFrom(node->right, nextRemaining);
        return count;
    }
};

// 方法二：理解方法一之后再看。提交此方法时，将类名改为 Solution。
class SolutionPrefixSum {
public:
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, int> prefixCount;
        prefixCount[0] = 1; // 从根节点之前开始，累计和为 0
        return dfs(root, 0, targetSum, prefixCount);
    }

private:
    int dfs(TreeNode* node, long long sum, int target,
            unordered_map<long long, int>& prefixCount) {
        if (node == nullptr) return 0;

        sum += node->val; // 从根到当前节点的累计和

        // 若之前的累计和为 sum - target，两者之差就是目标路径和。
        auto it = prefixCount.find(sum - target);
        int count = (it == prefixCount.end()) ? 0 : it->second;

        ++prefixCount[sum]; // 当前累计和供子节点使用
        count += dfs(node->left, sum, target, prefixCount);
        count += dfs(node->right, sum, target, prefixCount);

        // 离开当前节点时撤销，避免另一条分支使用这条路径的累计和。
        if (--prefixCount[sum] == 0) prefixCount.erase(sum);
        return count;
    }
};
