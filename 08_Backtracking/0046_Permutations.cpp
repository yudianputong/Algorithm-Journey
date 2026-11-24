/**
 * @file 0046_Permutations.cpp
 * @brief 46. 全排列
 * @link https://leetcode.cn/problems/permutations/
 * 
 * @algorithm 回溯 (Backtracking)
 * @time_complexity O(n * n!) - n 个元素全排列有 n! 种，每种解拷贝需要 O(n)
 * @space_complexity O(n) - 递归栈深度和 path 存储开销
 */

#include <vector>
#include <utility> // std::swap

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        // used 数组：记录哪些元素已被放入路径，避免重复选择
        vector<bool> used(nums.size(), false);
        
        backtracking(nums, used, path, result);
        return result;
    }

private:
    void backtracking(const vector<int>& nums, vector<bool>& used, 
                      vector<int>& path, vector<vector<int>>& result) {
        // 1. 终止条件：路径长度等于数组长度，说明找到一个解
        if (path.size() == nums.size()) {
            // 发生一次深拷贝，将 path 内容转移至结果集
            result.push_back(path);
            return;
        }

        // 2. 遍历选择列表
        for (int i = 0; i < nums.size(); ++i) {
            // 如果该元素已被使用，跳过（本层剪枝）
            if (used[i]) continue;

            // --- 关键：修改现场 ---
            used[i] = true;
            path.push_back(nums[i]);

            // --- 递归：深入下一层 ---
            backtracking(nums, used, path, result);

            // --- 核心：恢复现场 (回溯) ---
            // 撤销刚才的操作，让当前循环能尝试 nums[i+1]
            path.pop_back();
            used[i] = false;
        }
    }
};

// 方法二：交换回溯。提交此方法时，将类名改为 Solution。
// [0, first) 的位置已经确定，[first, nums.size()) 是待选择的元素。
class SolutionSwap {
public:
    vector<vector<int>> res;

    void backtrack(vector<int>& nums, int first) {
        if (first == static_cast<int>(nums.size())) {
            res.push_back(nums); // 每个位置都已确定，保存一个排列
            return;
        }

        for (int i = first; i < static_cast<int>(nums.size()); ++i) {
            swap(nums[first], nums[i]); // 选择：让 nums[i] 放到当前位置
            backtrack(nums, first + 1); // 继续确定下一个位置
            swap(nums[first], nums[i]); // 撤销：恢复数组，尝试其他选择
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        res.clear(); // 同一个对象再次调用时，从空结果开始
        backtrack(nums, 0);
        return res;
    }
};
