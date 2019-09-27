//
// Created by Cho Yiu Ng on 26.09.19.
//

#ifndef CPPLRUCACHE_LRUCACHE_H
#define CPPLRUCACHE_LRUCACHE_H

#include <list>
#include <unordered_map>

#include <optional>

template <typename K, typename V>
class LRUCache {
public:

    explicit LRUCache(size_t capacity);

    std::optional<V> get(const K& key);
    void put(const K& key, const V& value);

private:

    typedef typename std::list<typename std::pair<K, V>> ValueList_t;

    size_t                                                myCapacity;
    std::unordered_map<K, typename ValueList_t::iterator> myKeyValueMap;
    ValueList_t                                           myValueList;

};

#include <LRUCacheImpl.h>

#endif //CPPLRUCACHE_LRUCACHE_H
