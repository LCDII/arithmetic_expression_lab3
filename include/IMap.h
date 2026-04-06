#pragma once

template <typename K, typename V>
class IMap {
public:
    virtual ~IMap() = default;
    virtual void insert(const K& key, const V& value) = 0;
    virtual V& operator[](const K& key) = 0;
    virtual bool contains(const K& key) const = 0;
    virtual V* get(const K& key) = 0;
    virtual void erase(const K& key) = 0;
    virtual void clear() = 0;
};