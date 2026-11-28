/**
 * @file 0394_Decode_String.cpp
 * @brief 394. 字符串解码
 * @link https://leetcode.cn/problems/decode-string/
 *
 * @algorithm 用两个 vector 模拟栈，处理嵌套的括号
 * outer 保存进入括号前的字符串，counts 保存对应的重复次数。
 * 假设输入符合题目要求：括号匹配、数字后面跟着方括号。
 */

#include <cctype>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        vector<string> outer; // 每层括号前已解码的字符串
        vector<int> counts;   // 每层括号对应的重复次数
        string cur;           // 当前层正在构造的字符串
        int num = 0;

        for (char c : s) {
            if (isdigit(static_cast<unsigned char>(c))) {
                num = num * 10 + (c - '0'); // 处理多位数，例如 12
            } else if (c == '[') {
                outer.push_back(cur); // 保存当前层
                counts.push_back(num);
                cur.clear();          // 开始处理括号内的内容
                num = 0;
            } else if (c == ']') {
                string& prefix = outer.back();
                for (int k = counts.back(); k > 0; --k) {
                    prefix += cur; // 把括号内的内容追加指定次数
                }
                cur = move(prefix); // 回到上一层，得到拼接后的字符串
                outer.pop_back();   // 当前括号已处理完，两边都要出栈
                counts.pop_back();
            } else {
                cur.push_back(c);
            }
        }
        return cur;
    }
};
