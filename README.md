# C++ Library for LRU Cache
This is a C++ template library for LRU cache. Details about LRU caching mechanism
can be found in [this link](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_%28LRU%29).

## Usage
The header file for the LRU cache is  ```LRUCache.h``` and the template class is ```LRUCache<K, V>```,
where ```K``` and ```V``` are the key and value types respectively. Example usages can
be found in the unit test file ```tests/LRUCacheTest.cpp```. Below are the brief explanations
of some member functions:

* Constructor: This specifies the number of elements to be stored.

* ```void clear()```: This removes all the elements in the LRU cache.

* ```void erase(const K& key)```: This remove the element identified by the key ```key```.

* ```std::optional<V> get(const K& key)```: The returns the cached value
with the key ```key```. If such key does not exist in the cache, an empty ```optional```
object will be returned.

* ```size_t getNumElements()```: This returns the number of values stored in the cache.

* ```void put(const K& key, const V& value)```: This inserts/updates the value in the cache
of the key ```key```. After that, if the number of values exceeds the cache capacity,
the least recently accessed element will be removed by the cache automatically.

* ```void removeOldest()```: This removes the least recently accessed element in the
cache.

## Thread Safety
This LRU cache class is guaranteed to be thread-safe

## Unit Test
Unit test files can be found in the directory ```tests```. Googletest is used in this
case.
