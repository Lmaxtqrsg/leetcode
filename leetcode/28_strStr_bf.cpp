/* ============================================================
 * 力扣 28. 找出字符串中第一个匹配项的下标
 * https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
 * 难度：简单 | 2026-10-19
 * ------------------------------------------------------------
 * 思路：BF（Brute Force，暴力匹配）
 *
 *   用 i 指向 haystack、j 指向 needle，都从 1 开始（1-based）。
 *     · 相等   -> i++、j++ 一起往后
 *     · 不相等 -> i 回退到「这一轮起点的下一个位置」，j 归 1
 *                 回退公式： i = i - j + 2
 *     · j > l2 -> needle 全部匹配完，返回起点 i - l2 - 1
 *
 * 复杂度：
 *   时间 O(n*m)  最坏情况每次都要重新比
 *   空间 O(1)
 *
 * 注意：这是 BF，不是 KMP。KMP 的时间复杂度是 O(n+m)。
 * ============================================================ */

class Solution {
public:
    int strStr(string haystack, string needle) {
        int l1 = (int)haystack.size();
        int l2 = (int)needle.size();

        int i = 1, j = 1;                 /* 1-based 下标 */

        while (i <= l1 && j <= l2) {
            if (haystack[i - 1] == needle[j - 1]) {
                i++;
                j++;
            } else {
                i = i - j + 2;            /* 回退到下一个起点 */
                j = 1;
            }
        }

        if (j > l2) return i - l2 - 1;    /* 匹配成功，返回起点 */
        else        return -1;
    }
};

/* ------------------------------------------------------------
 * 测试用例：
 *   "sadbutsad", "sad"   ->  0
 *   "leetcode",  "leeto" ->  -1
 *   "a",         "a"      ->  0
 *   "a",         ""       ->  0
 * ------------------------------------------------------------ */