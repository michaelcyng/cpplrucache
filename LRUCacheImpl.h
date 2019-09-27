//
// Created by Cho Yiu Ng on 26.09.19.
//

#ifndef LRUCACHE_LRUCACHEIMPL_H
#define LRUCACHE_LRUCACHEIMPL_H

#include <utility>

template <typename K, typename V>
LRUCache<K, V>::LRUCache(size_t capacity) : myCapacity(capacity) {
}

template <typename K, typename V>
std::optional<V> LRUCache<K, V>::get(const K& key) {
    std::lock_guard<std::mutex> lockGuard(myMutex);

    auto keyValueIter = myKeyValueMap.find(key);

    // Return nothing as the key is not found
    if (keyValueIter == myKeyValueMap.end()) {
        return std::optional<V>();
    }

    // The key exists. The corresponding value returns and it will be moved to the back of the value list
    auto valueListIter = keyValueIter->second;
    myValueList.splice(myValueList.end(), myValueList, valueListIter);
    return valueListIter->second;
}

template <typename K, typename V>
void LRUCache<K, V>::put(const K &key, const V &value) {
    std::lock_guard<std::mutex> lockGuard(myMutex);

    // If the key is present:
    // 1. Replace the old value in the corresponding value list node
    // 2. Move that list node to the back of the value list
    auto keyValueIter = myKeyValueMap.find(key);
    if (keyValueIter != myKeyValueMap.end()) {
        auto valueListIter = keyValueIter->second;
        valueListIter->second = value;
        myValueList.splice(myValueList.end(), myValueList, valueListIter);
        return;
    }

    // Now, the key is not present. We add it to the back of the value list
    myValueList.emplace_back(std::make_pair(key, value));
    auto newValueIter = std::prev(myValueList.end());
    myKeyValueMap.insert(std::make_pair(key, newValueIter));

    // If the number of the elements exceeds the capacity, remove the oldest one (i.e. the one at the front of the
    // value list.
    if (myValueList.size() > myCapacity) {
        auto oldestValueListIter = myValueList.begin();
        myKeyValueMap.erase(oldestValueListIter->first);
        myValueList.erase(oldestValueListIter);
    }

}

#endif //LRUCACHE_LRUCACHEIMPL_H
