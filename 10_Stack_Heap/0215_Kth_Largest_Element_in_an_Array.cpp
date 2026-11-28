/**
 * @file 0215_Kth_Largest_Element_in_an_Array.cpp
 * @brief 215. 数组中的第 K 个最大元素
 * @link https://leetcode.cn/problems/kth-largest-element-in-an-array/
 *
 * @algorithm 小顶堆
 * 小顶堆的堆顶是堆中最小的数；始终让堆里保留目前最大的 k 个数。
 * 遍历结束后，堆顶就是这 k 个数中最小的，也就是第 k 大的数。
 *
 * 例如 nums = [3,2,1,5,6,4], k = 2：
 * 最后堆里保留 5 和 6，堆顶是 5，所以第 2 大的数是 5。
 * 相同的数也算不同的元素，例如 [3,3,2] 的第 2 大是 3。
 *
 * @time_complexity O(N log(K+1))
 * @space_complexity O(K)
 */

#include <functional>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // greater<int> 使堆顶成为堆中最小的元素。
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (int num : nums) {
            minHeap.push(num);

            if (minHeap.size() > static_cast<size_t>(k)) {
                minHeap.pop(); // 超过 k 个时，移除堆中最小的数
            }
        }

        return minHeap.top();
    }
};
