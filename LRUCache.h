//
// Created by Cho Yiu Ng on 26.09.19.
//

#ifndef CPPLRUCACHE_LRUCACHE_H
#define CPPLRUCACHE_LRUCACHE_H

#include <list>
#include <optional>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

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

private:

    void removeOldestImpl(); // This is run without worrying about thread safety issues

    typedef std::shared_lock<std::shared_mutex>          ReadLock_t;
    typedef typename std::list<typename std::pair<K, V>> ValueList_t;
    typedef typename ValueList_t::iterator               ValueListIter_t;
    typedef std::lock_guard<std::shared_mutex>           WriteLock_t;

    size_t                                 myCapacity;
    std::unordered_map<K, ValueListIter_t> myKeyValueMap;
    mutable std::shared_mutex              myMutex;
    ValueList_t                            myValueList;

};

#include <LRUCacheImpl.h>

#endif //CPPLRUCACHE_LRUCACHE_H
