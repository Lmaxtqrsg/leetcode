// ============================================================
// 704. 二分查找
// https://leetcode.cn/problems/binary-search/
// 难度：简单 | 通过日期：2026-10-14
// ============================================================
//
// 思路：
//   用 left / right 圈住候选范围，每次取中点 mid 比较：
//     相等         -> 找到了，返回 mid
//     nums[mid] 小 -> 目标在右半边，left  = mid + 1
//     nums[mid] 大 -> 目标在左半边，right = mid - 1
//   范围空了还没找到，返回 -1
//
// 复杂度：时间 O(log n)，空间 O(1)
// ============================================================

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return -1;
    }
};