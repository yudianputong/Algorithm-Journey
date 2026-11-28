/**
 * @file 0347_Top_K_Frequent_Elements.cpp
 * @brief 347. 前 K 个高频元素
 * @link https://leetcode.cn/problems/top-k-frequent-elements/
 * 
 * @algorithm Hash Map + Min-Heap (小顶堆)
 * @time_complexity O(N log K) - N 为元素个数，堆维护成本为 log K
 * @space_complexity O(N)      - 哈希表存储所有不重复元素
 * 
 * @note 核心思路：
 * 1. 统计频率。
 * 2. 维护大小为 K 的小顶堆。堆顶是当前 Top K 中频率最低的。
 * 3. 遍历完后，堆中剩下的就是最高频的 K 个。
 */

#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 1. 统计频率：工业级优化，预留空间防止多次 Rehash
        unordered_map<int, int> counts;
        counts.reserve(nums.size()); 
        for (int num : nums) {
            counts[num]++;
        }

        // 2. 堆中每项是 {元素, 频率}，与 counts 的顺序一致。
        using pii = pair<int, int>;
        // 比较 second（频率）：让频率较小的元素排在堆顶。
        auto compare = [](const pii& a, const pii& b) {
            return a.second > b.second;
        };
        priority_queue<pii, vector<pii>, decltype(compare)> pq(compare);

        for (auto const& [val, freq] : counts) {
            if (pq.size() < k) {
                pq.push({val, freq});
            } else if (freq > pq.top().second) {
                pq.pop();
                pq.push({val, freq});
            }
        }

        // 3. 构造结果：堆内元素即为所求
        vector<int> res;
        res.reserve(k);
        while (!pq.empty()) {
            res.push_back(pq.top().first);
            pq.pop();
        }
        return res;
    }
};