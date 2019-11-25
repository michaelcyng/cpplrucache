//
// Created by Cho Yiu Ng on 26.09.19.
//

#ifndef CPPLRUCACHE_LRUCACHE_H
#define CPPLRUCACHE_LRUCACHE_H

#include <optional>
#include <shared_mutex>
#include <thread>

template <typename K, typename V>
class NonThreadSafeLRUCache;

template <typename K, typename V>
class LRUCache {
public:

    explicit LRUCache(size_t capacity);

    void             clear();
    void             erase(const K& key);
    std::optional<V> get(const K& key);
    size_t           getCapacity() const noexcept;
    size_t           getNumElements() const noexcept;
    void             put(const K& key, const V& value);
    void             removeOldest();
    void             setCapacity(size_t newCapacity);

private:

    typedef std::shared_lock<std::shared_mutex> ReadLock_t;
    typedef std::lock_guard<std::shared_mutex>  WriteLock_t;

    NonThreadSafeLRUCache<K, V> myInternalCache;
    mutable std::shared_mutex   myMutex;

};

#include <LRUCacheImpl.h>

#endif //CPPLRUCACHE_LRUCACHE_H
