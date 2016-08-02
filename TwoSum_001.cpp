//
// Created by whiker on 16-8-1.
//

#include <vector>
#include <map>
#include <iostream>

using namespace std;

namespace TwoSum_001 {

    class Solution {
    public:
        vector<int> twoSum(vector<int> &nums, int target) {
            HashMap numMap(8);
            int i, j;
            for (i = 0; i < nums.size(); i++) {
                j = numMap.get(nums[i]);
                if (j != 0) {
                    return vector<int>({j - 1, i});
                } else {
                    numMap.put(target - nums[i], i + 1);
                }
            }
            return vector<int>({-1, -1});
        }

    private:
        class HashMap {
        private:
            enum HashMapElementType {
                Empty, Single, Multi
            };

            struct HashMapElement {
                union {
                    pair<int, int> *kv;
                    map<int, int> *kvs;
                };
                HashMapElementType type = HashMapElementType::Empty;
            };

        private:
            int mSize;
            HashMapElement *mSpace;

        public:
            HashMap(int sizeShift) {
                sizeShift = min(max(sizeShift, 0), 16);
                mSize = (1 << sizeShift) - 1;
                mSpace = new HashMapElement[mSize + 1];
            }

            ~HashMap() {
                for (int i = 0; i < mSize; i++) {
                    if (mSpace[i].type == Single) {
                        delete mSpace[i].kv;
                    } else if (mSpace[i].type == Multi) {
                        delete mSpace[i].kvs;
                    }
                }
                delete[] mSpace;
            }

            int getIndex(int key) {
                if (key < 0) key = -key;
                return (key & mSize);
            }

            void put(int key, int value) {
                HashMapElement &e = mSpace[getIndex(key)];
                if (e.type == Empty) {
                    e.kv = new pair<int, int>(key, value);
                    e.type = Single;
                } else if (e.type == Single) {
                    if (e.kv->first == key) {
                        e.kv->second = value;
                    } else {
                        map<int, int> *kvs = new map<int, int>();
                        (*kvs)[e.kv->first] = e.kv->second;
                        (*kvs)[key] = value;
                        delete e.kv;
                        e.kvs = kvs;
                        e.type = HashMapElementType::Multi;
                    }
                } else if (e.type == Multi) {
                    (*e.kvs)[key] = value;
                }
            }

            int get(int key, bool *isExist = NULL) {
                HashMapElement &e = mSpace[getIndex(key)];
                if (e.type == Empty) {
                    if (isExist) *isExist = false;
                    return 0;
                } else if (e.type == Single) {
                    if (e.kv->first == key) {
                        if (isExist) *isExist = true;
                        return e.kv->second;
                    } else {
                        if (isExist) *isExist = false;
                        return 0;
                    }
                } else if (e.type == Multi) {
                    auto it = e.kvs->find(key);
                    if (isExist) *isExist = it != e.kvs->end();
                    return it != e.kvs->end() ? it->second : 0;
                }
                return 0;
            }
        };
    };

    void test() {
        Solution solu;
        vector<int> input;
        vector<int> ret;

        input = {0, -4, 3, -6};
        ret = solu.twoSum(input, -6);
        cout << ret[0] << " " << ret[1] << endl;  // 0 3

        input = {3, -7, -4, 3, 10};
        ret = solu.twoSum(input, 3);
        cout << ret[0] << " " << ret[1] << endl;  // 1 4

        input = {3, -7, -4, 3, 3, 3, 3, 4, 10};
        ret = solu.twoSum(input, 7);
        cout << ret[0] << " " << ret[1] << endl;  // 6 7

        input = {3, -7, -4, 2, 3, 10};
        ret = solu.twoSum(input, 6);
        cout << ret[0] << " " << ret[1] << endl;  // 0 4
    }

}