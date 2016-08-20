//
// Created by whiker on 16-8-6.
//

#include <iostream>
#include <vector>
#include <gtest/gtest.h>

using namespace std;

namespace PatchArray_330 {

    /*
     * 例子: nums = [1 5 10]，n = 20
     * 增加数字[2 4]，变成[1 2 4 5 10]，这5个数字可以组成1~20的和分解。
     * [1] [2] [1 2](3) [4] [5] [1 5](6) [2 5](7) [1 2 5](8) [4 5](9) [10] ...。
     */

    /* 若nums空，则至少需要log2(n)+1，由[1 2 4 8 16 ...]组成。
     * 若nums空，用M进制数组成，则至少需要(M-1)×logM(n)+1。
     * 如3进制是[1 2 10 20 100 200 ...]，其中数字是3进制表示。
     * 2进制需要的数最少，二分法最快的原因。
     */

    /*
     * 贪心法，2个状态量knownNum和needNum
     */
    class Solution {
    public:
        int minPatches(vector<int> &nums, int target) {
            const int len = (int) nums.size();
            int known = 1;  // 已知区域是[1, known]
            int addedNum = len > 0 && nums[0] == 1 ? 0 : 1;  // 需要增加的最少数
            for (int i = 1 - addedNum; known < target && known > 0; ) {  // 加"known > 0"防止known增大到负数
                if (i < len && nums[i] <= known + 1) {  // 每次尝试扩展1个单位
                    known = nums[i] + known;
                    i++;
                } else {
                    addedNum++;  // 补入(known+1)
                    known = (known << 1) + 1;  // known = (known + 1) + known;
                }
            }
            return addedNum;
        }
    };

    void test() {
        Solution solu;
        vector<int> input;
        int target;

        input = {1, 5, 10}, target = 20;
        EXPECT_EQ(2, solu.minPatches(input, target));

        input = {1, 2, 4, 13, 43}, target = 100;
        EXPECT_EQ(2, solu.minPatches(input, target));

        input = {}, target = 100;
        EXPECT_EQ(7, solu.minPatches(input, target));

        input = {1}, target = 100;
        EXPECT_EQ(6, solu.minPatches(input, target));

        input = {1, 2}, target = 100;
        EXPECT_EQ(5, solu.minPatches(input, target));

        input = {1, 2, 31, 33}, target = 2147483647;
        EXPECT_EQ(28, solu.minPatches(input, target));

        input = {1, 2, 4, 8}, target = 5;
        EXPECT_EQ(0, solu.minPatches(input, target));

        input = {1, 2, 2}, target = 5;
        EXPECT_EQ(0, solu.minPatches(input, target));
    }

}