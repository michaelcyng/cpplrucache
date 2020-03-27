//
// Created by Cho Yiu Ng on 26.09.19.
//

#ifndef LRUCACHE_LRUCACHEIMPL_H
#define LRUCACHE_LRUCACHEIMPL_H

#include <utility>

#include <Exceptions.h>
#include <internal/NonThreadSafeLRUCache.h>

namespace LRUCache {

    template<typename K, typename V>
    LRUCache<K, V>::LRUCache(size_t capacity) : myInternalCache(capacity) {
    }

    template<typename K, typename V>
    void LRUCache<K, V>::clear() {
        WriteLock_t lockGuard(myMutex);
        myInternalCache.clear();
    }

    template<typename K, typename V>
    void LRUCache<K, V>::erase(const K &key) {
        WriteLock_t lockGuard(myMutex);
        myInternalCache.erase(key);
    }

    template<typename K, typename V>
    std::optional<V> LRUCache<K, V>::get(const K &key) {
        WriteLock_t lockGuard(myMutex);
        return myInternalCache.get(key);
    }

    template<typename K, typename V>
    size_t LRUCache<K, V>::getCapacity() const noexcept {
        ReadLock_t sharedLock(myMutex);
        return myInternalCache.getCapacity();
    }

    template<typename K, typename V>
    size_t LRUCache<K, V>::getNumElements() const noexcept {
        ReadLock_t sharedLock(myMutex);
        return myInternalCache.getNumElements();
    }

    template<typename K, typename V>
    void LRUCache<K, V>::put(const K &key, const V &value) {
        WriteLock_t lockGuard(myMutex);
        myInternalCache.put(key, value);
    }

    template<typename K, typename V>
    void LRUCache<K, V>::removeOldest() {
        WriteLock_t lockGuard(myMutex);
        myInternalCache.removeOldest();
    }

    template<typename K, typename V>
    void LRUCache<K, V>::setCapacity(size_t newCapacity) {
        WriteLock_t lockGuard(myMutex);
        myInternalCache.setCapacity(newCapacity);
    }

}

#endif //LRUCACHE_LRUCACHEIMPL_H
