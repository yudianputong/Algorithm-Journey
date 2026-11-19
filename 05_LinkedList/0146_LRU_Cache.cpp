/**
 * @file 0146_LRU_Cache.cpp
 * @brief 146. LRU 缓存
 * @link https://leetcode.cn/problems/lru-cache/
 * 
 * @algorithm Hash Table + Doubly Linked List
 * @time_complexity 平均 O(1) - get 和 put 使用哈希表查找
 * @space_complexity O(Capacity) - 存储 capacity 个键值对
 * 
 * @note 核心优化：
 * 1. 使用 std::list 存储数据，保持访问顺序。
 * 2. 使用 unordered_map 存储 key 到 list iterator 的映射，实现 O(1) 定位。
 * 3. 利用 list::splice 实现 O(1) 的节点移动（移动到头部），无需删除再插入。
 */

#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
private:
    // 链表头是最近使用的节点，尾部是最久未使用的节点。
    list<pair<int, int>> ls;
    // key -> 链表中对应节点的迭代器
    unordered_map<int, list<pair<int, int>>::iterator> mp;
    int capacity;

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (mp.count(key)) {
            auto it = mp[key]; // 链表节点的迭代器
            ls.splice(ls.begin(), ls, it);
            return it->second; // 链表节点中的 value
        } else {
            return -1;
        }
    }

    void put(int key, int value) {
        if (mp.count(key)) {
            // 已存在：更新值并移到头部
            auto it = mp[key];
            it->second = value;
            ls.splice(ls.begin(), ls, it);
        } else {
            // 已满：删除链表尾节点及 map 中对应的索引
            if (mp.size() >= capacity) {
                auto last = ls.back(); // 复制尾节点的 {key, value}
                ls.pop_back();
                mp.erase(last.first);
            }
            // 新节点放在头部，map 记录其位置
            ls.push_front({key, value});
            mp[key] = ls.begin();
        }
    }
};


// #include <iostream>
//   #include <unordered_map>
//   using namespace std;

//   class LRUCache {
//   private:
//       struct Node {
//           int key;
//           int value;
//           Node* prev;
//           Node* next;

//           Node(int k, int v) {
//               key = k;
//               value = v;
//               prev = nullptr;
//               next = nullptr;
//           }
//       };

//       int capacity;
//       unordered_map<int, Node*> cache;

//       Node* head;
//       Node* tail;

//   public:
//       LRUCache(int cap) {
//           capacity = cap;

//           head = new Node(0, 0);
//           tail = new Node(0, 0);

//           head->next = tail;
//           tail->prev = head;
//       }

//       int get(int key) {
//           if (cache.find(key) == cache.end()) {
//               return -1;
//           }

//           Node* node = cache[key];
//           moveToHead(node);

//           return node->value;
//       }

//       void put(int key, int value) {
//           if (cache.find(key) != cache.end()) {
//               Node* node = cache[key];
//               node->value = value;
//               moveToHead(node);
//               return;
//           }

//           Node* node = new Node(key, value);
//           cache[key] = node;
//           addToHead(node);

//           if (cache.size() > capacity) {
//               Node* old = removeTail();
//               cache.erase(old->key);
//               delete old;
//           }
//       }

//   private:
//       void removeNode(Node* node) {
//           node->prev->next = node->next;
//           node->next->prev = node->prev;
//       }

//       void addToHead(Node* node) {
//           node->next = head->next;
//           node->prev = head;

//           head->next->prev = node;
//           head->next = node;
//       }

//       void moveToHead(Node* node) {
//           removeNode(node);
//           addToHead(node);
//       }

//       Node* removeTail() {
//           Node* node = tail->prev;
//           removeNode(node);
//           return node;
//       }
//   };

//   ———

//   # 8. 最核心的四个辅助函数

//   你真正要记的是这四个：

//   removeNode(node)
//   addToHead(node)
//   moveToHead(node)
//   removeTail()

//   ## 删除节点

//   void removeNode(Node* node) {
//       node->prev->next = node->next;
//       node->next->prev = node->prev;
//   }

//   意思是：

//   让 node 前面的节点直接指向 node 后面的节点
//   让 node 后面的节点直接指向 node 前面的节点

//   ———

//   ## 插入头部

//   void addToHead(Node* node) {
//       node->next = head->next;
//       node->prev = head;

//       head->next->prev = node;
//       head->next = node;
//   }

//   意思是把节点插到：

//   head 和 head->next 中间

//   ———

//   ## 移动到头部

//   void moveToHead(Node* node) {
//       removeNode(node);
//       addToHead(node);
//   }

//   ———

//   ## 删除尾部

//   Node* removeTail() {
//       Node* node = tail->prev;
//       removeNode(node);
//       return node;
//   }

//   注意：
//   真正的尾部节点是虚拟节点 tail，所以要删的是：

//   tail->prev

