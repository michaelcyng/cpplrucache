//
// Created by Cho Yiu Ng on 25.11.19.
//

#ifndef LRUCACHE_NONTHREADSAFELRUCACHE_H
#define LRUCACHE_NONTHREADSAFELRUCACHE_H

#include <list>
#include <optional>
#include <unordered_map>

template <typename K, typename V>
class NonThreadSafeLRUCache {
public:

    explicit NonThreadSafeLRUCache(size_t capacity);

    void                clear();
    void                erase(const K& key);
    std::optional<V>    get(const K& key);
    [[nodiscard]]size_t getCapacity() const noexcept;
    [[nodiscard]]size_t getNumElements() const noexcept;
    void                put(const K& key, const V& value);
    void                removeOldest();
    void                setCapacity(size_t newCapacity);

private:

    typedef typename std::list<typename std::pair<K, V>> ValueList_t;
    typedef typename ValueList_t::iterator               ValueListIter_t;

    size_t                                 myCapacity;
    std::unordered_map<K, ValueListIter_t> myKeyValueMap;
    ValueList_t                            myValueList;

};

#include <internal/NonThreadSafeLRUCacheImpl.h>

#endif //LRUCACHE_NONTHREADSAFELRUCACHE_H
