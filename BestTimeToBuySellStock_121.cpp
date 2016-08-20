//
// Created by whiker on 16-8-6.
//

#include <vector>
#include <gtest/gtest.h>

using namespace std;

namespace BestTimeToBuySellStock_121 {

    /*
     * 对于第i天, 找左边最小值与之相减, 得到第i天卖出的最大收益(localMaxProfit)
     * 计算全局最大收益(maxProfit)
     */
    class Solution {
    public:
        int maxProfit(vector<int> &prices) {
            if (prices.size() <= 0) {
                return 0;
            }
            int maxProfit = 0, localMaxProfit;
            int min = prices[0];
            for (int i = 1; i < prices.size(); i++) {
                localMaxProfit = prices[i] - min;
                if (localMaxProfit > maxProfit) {
                    maxProfit = localMaxProfit;
                }
                if (prices[i] < min) {
                    min = prices[i];
                }
            }
            return maxProfit;
        }
    };

    void test() {
        Solution solu;
        vector<int> input;

        input = {7, 1, 5, 3, 6, 4};
        EXPECT_EQ(5, solu.maxProfit(input));

        input = {7, 6, 4, 3, 1};
        EXPECT_EQ(0, solu.maxProfit(input));

        input = {};
        EXPECT_EQ(0, solu.maxProfit(input));
    }

}