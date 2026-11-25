/**
 * @file 0039_Combination_Sum.cpp
 * @brief 39. 组合总和
 * @link https://leetcode.cn/problems/combination-sum/
 *
 * @algorithm 排序 + 回溯
 * 数字可以重复选，但组合的顺序不同不算新答案。
 * 本题保证 candidates 中的数字互不相同，且均为正整数。
 *
 * 时间复杂度：搜索分支随输入呈指数增长，具体取决于 target 和候选数字。
 * 辅助空间：O(target / min(candidates))，用于路径和递归栈，不包含结果。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // 排序后，数字太大时可以提前结束
        vector<vector<int>> result;
        vector<int> path;

        backtrack(candidates, target, 0, path, result);
        return result;
    }

private:
    // remaining：还需要凑出的和；start：本轮可以选择的起始下标。
    void backtrack(const vector<int>& candidates, int remaining, size_t start,
                   vector<int>& path, vector<vector<int>>& result) {
        if (remaining == 0) {
            result.push_back(path); // 恰好凑出目标，保存当前组合
            return;
        }

        for (size_t i = start; i < candidates.size(); ++i) {
            if (candidates[i] > remaining) break; // 后面的数更大，无需再试

            path.push_back(candidates[i]); // 选择当前数字
            // 传 i 而不是 i + 1：同一个数字可以继续使用。
            backtrack(candidates, remaining - candidates[i], i, path, result);
            path.pop_back(); // 撤销选择，再尝试其他数字
        }
    }
};
