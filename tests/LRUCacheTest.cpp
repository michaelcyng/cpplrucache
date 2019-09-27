//
// Created by Cho Yiu Ng on 26.09.19.
//

#include <gtest/gtest.h>
#include <LRUCache.h>

class LRUCacheTests : public ::testing::Test {
protected:

    LRUCacheTests() = default;
    ~LRUCacheTests() override = default;
    void SetUp() override {}
    void TearDown() override {}

};

TEST_F(LRUCacheTests, TestErase) {

    LRUCache<int, int> testCache(2);

    testCache.put(1, 10);
    testCache.put(2, 20);
    ASSERT_TRUE(testCache.get(1).has_value());
    ASSERT_TRUE(testCache.get(2).has_value());
    testCache.erase(1);
    ASSERT_FALSE(testCache.get(1).has_value());
    ASSERT_TRUE(testCache.get(2).has_value());

}

TEST_F(LRUCacheTests, TestGetNothing) {

    LRUCache<int, int> testCache(1);
    ASSERT_FALSE(testCache.get(1).has_value());

}

TEST_F(LRUCacheTests, TestPutLogic) {

    LRUCache<int, int> testCache(3);

    testCache.put(1, 10);
    ASSERT_EQ(testCache.get(1), 10);

    testCache.put(2, 20);
    ASSERT_EQ(testCache.get(1), 10);
    ASSERT_EQ(testCache.get(2), 20);

    testCache.put(3, 30);
    ASSERT_EQ(testCache.get(1), 10);
    ASSERT_EQ(testCache.get(2), 20);
    ASSERT_EQ(testCache.get(3), 30);

    testCache.put(4, 40);
    ASSERT_FALSE(testCache.get(1).has_value());
    ASSERT_EQ(testCache.get(2), 20);
    ASSERT_EQ(testCache.get(3), 30);
    ASSERT_EQ(testCache.get(4), 40);

    testCache.put(2, 21);
    ASSERT_FALSE(testCache.get(1).has_value());
    ASSERT_EQ(testCache.get(2), 21);
    ASSERT_EQ(testCache.get(3), 30);
    ASSERT_EQ(testCache.get(4), 40);

    testCache.put(5, testCache.get(2).value() + 1);
    ASSERT_FALSE(testCache.get(1).has_value());
    ASSERT_FALSE(testCache.get(3).has_value());
    ASSERT_EQ(testCache.get(4), 40);
    ASSERT_EQ(testCache.get(2), 21);
    ASSERT_EQ(testCache.get(5), 22);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
