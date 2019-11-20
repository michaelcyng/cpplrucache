//
// Created by Cho Yiu Ng on 26.09.19.
//

#ifndef LRUCACHE_LRUCACHEIMPL_H
#define LRUCACHE_LRUCACHEIMPL_H

#include <utility>

#include <Exceptions.h>

template <typename K, typename V>
LRUCache<K, V>::LRUCache(size_t capacity) : myCapacity(capacity) {
}

template <typename K, typename V>
void LRUCache<K, V>::clear() {
    WriteLock_t lockGuard(myMutex);

    myKeyValueMap.clear();
    myValueList.clear();
}

template <typename K, typename V>
void LRUCache<K, V>::erase(const K &key) {
    WriteLock_t lockGuard(myMutex);

    auto keyValueIter = myKeyValueMap.find(key);

    // Do nothing if the key does not exist
    if (keyValueIter == myKeyValueMap.end()) {
        return;
    }

    auto ValueListIter = keyValueIter->second;
    myValueList.erase(ValueListIter);
    myKeyValueMap.erase(keyValueIter);

}

template <typename K, typename V>
std::optional<V> LRUCache<K, V>::get(const K& key) {
    WriteLock_t lockGuard(myMutex);

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
size_t LRUCache<K, V>::getCapacity() const noexcept {
    ReadLock_t sharedLock(myMutex);
    return myCapacity;
}

template <typename K, typename V>
size_t LRUCache<K, V>::getNumElements() const noexcept {
    ReadLock_t sharedLock(myMutex);
    return myValueList.size();
}

template <typename K, typename V>
void LRUCache<K, V>::put(const K &key, const V &value) {
    WriteLock_t lockGuard(myMutex);

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
        removeOldestImpl();
    }

}

template <typename K, typename V>
void LRUCache<K, V>::removeOldest() {
    WriteLock_t lockGuard(myMutex);

    removeOldestImpl();
}

template <typename K, typename V>
void LRUCache<K, V>::setCapacity(size_t newCapacity) {
    WriteLock_t lockGuard(myMutex);

    // Capacity remains unchanged
    if (myCapacity == newCapacity) {
        return;
    }

    // Enlarge the cache
    if (myCapacity < newCapacity) {
        myCapacity = newCapacity;
        return;
    }

    // Disallow zero newCapacity
    if (newCapacity == 0) {
        throw ZeroCapacityException();
    }

    // Shrink the cache
    size_t numItemsToRemove = myCapacity - newCapacity;
    for (size_t i = 0; i < numItemsToRemove; ++i) {
        removeOldestImpl();
    }
    myCapacity = newCapacity;
}

template <typename K, typename V>
void LRUCache<K, V>::removeOldestImpl() {
    if (myValueList.size() > 0) {
        auto oldestValueListIter = myValueList.begin();
        myKeyValueMap.erase(oldestValueListIter->first);
        myValueList.erase(oldestValueListIter);
    }
}

#endif //LRUCACHE_LRUCACHEIMPL_H
