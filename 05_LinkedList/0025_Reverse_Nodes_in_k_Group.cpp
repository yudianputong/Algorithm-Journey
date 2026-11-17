/**
 * @file 0025_Reverse_Nodes_in_k_Group.cpp
 * @brief 25. K 个一组翻转链表
 * @link https://leetcode.cn/problems/reverse-nodes-in-k-group/
 *
 * @algorithm 迭代 + 虚拟头节点 + 分组反转
 * @time_complexity O(N) - 每个节点至多被寻找和反转各访问一次。
 * @space_complexity O(1) - 只使用固定数量的指针。
 */

// 力扣提交时使用题目提供的 ListNode 定义，只需提交 Solution。
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* groupPrev = &dummy; // 当前组前一个节点

        while (true) {
            // 从 groupPrev 出发，找到当前组的第 k 个节点。
            ListNode* kth = groupPrev;
            for (int i = 0; i < k && kth != nullptr; ++i) {
                kth = kth->next;
            }
            if (kth == nullptr) break; // 不足 k 个，保留原顺序

            ListNode* groupNext = kth->next;       // 下一组的第一个节点
            ListNode* groupHead = groupPrev->next; // 当前组的第一个节点
            ListNode* prev = groupNext;
            ListNode* curr = groupHead;

            // 与第 206 题相同，逐个反转；遇到下一组时停止。
            while (curr != groupNext) {
                ListNode* tmp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = tmp;
            }

            groupPrev->next = kth; // 上一部分连接到反转后的组头
            groupPrev = groupHead; // 原组头变成组尾，准备处理下一组
        }
        return dummy.next;
    }
};

