/* ============================================================
 * 力扣 59. 螺旋矩阵 II
 * https://leetcode.cn/problems/spiral-matrix-ii/
 * 难度：中等 | 2026-10-19
 * ------------------------------------------------------------
 * 思路：坚持「左闭右开」的边界规则，一圈一圈填
 *
 *   每一圈走四条边，每条边都「只处理起点、不处理终点」：
 *     上边：左 -> 右    j in [starty, n-offset)
 *     右边：上 -> 下    i in [startx, n-offset)
 *     下边：右 -> 左    j in (starty, n-offset]
 *     左边：下 -> 上    i in (startx, n-offset]
 *
 *   每转完一圈：startx++、starty++、offset++
 *   n 为奇数时，最后中心那个格子单独填。
 *
 * 复杂度：
 *   时间 O(n^2)  每个格子填一次
 *   空间 O(1)    除返回的矩阵外
 *
 * 易错点：
 *   四条边的边界一定要统一成「左闭右开」，否则会重复填或漏填。
 * ============================================================ */

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));

        int startx = 0, starty = 0;   /* 每一圈的起点 */
        int offset = 1;               /* 每一圈右/下边界的收缩量 */
        int count  = 1;               /* 要填的数字 */

        for (int loop = 0; loop < n / 2; ++loop) {
            int i = startx, j = starty;

            for (; j < n - offset; j++) res[i][j] = count++;   /* 上边 */
            for (; i < n - offset; i++) res[i][j] = count++;   /* 右边 */
            for (; j > starty;     j--) res[i][j] = count++;   /* 下边 */
            for (; i > startx;     i--) res[i][j] = count++;   /* 左边 */

            ++startx, ++starty, ++offset;
        }

        if (n % 2 == 1) res[n / 2][n / 2] = count;   /* 奇数：中心 */

        return res;
    }
};

/* ------------------------------------------------------------
 * n = 3                      n = 4
 *   1 2 3                    1  2  3  4
 *   8 9 4                    12 13 14 5
 *   7 6 5                    11 16 15 6
 *                            10 9  8  7
 * ------------------------------------------------------------ */