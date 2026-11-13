#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode* next;

    ListNode(int x) : val(x),next(nullptr){}
};

class Solution{
public:
    ListNode* reverseListNode(ListNode* head){
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while(curr){
            ListNode* tmp = curr->next; // ① 保存下一个节点
            curr->next = prev;         // ② 反转当前指向
            prev = curr;               // ③ prev 前进
            curr = tmp;                // ④ curr 前进
        }
        return prev;
    }
};
