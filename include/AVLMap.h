#pragma once
#include "IMap.h"
#include "AVLTree.h"

template <typename Key, typename Value>
struct MapPair {
    Key key;
    Value value;

    MapPair(const Key& Key, const Value& Value) : key(Key), value(Value) {}

    bool operator<(const MapPair& other) const {
        return key < other.key;
    }

    bool operator>(const MapPair& other) const {
        return key > other.key;
    }

    bool operator==(const MapPair& other) const {
        return key == other.key;
    }
};

template <typename Key, typename Value>
class AVLMap : public IMap<Key, Value> {
private:
    AVLTree<MapPair<Key, Value>> tree;
    using NodeT = Node<MapPair<Key, Value>>;

    NodeT* find(NodeT* cur, const Key& key) const {
        if (!cur) return nullptr;

        if (key < cur->val.key)
            return find(cur->left, key);
        else if (key > cur->val.key)
            return find(cur->right, key);
        else
            return cur;
    }

public:
    AVLMap() = default;
    ~AVLMap() override = default;
    void insert(const Key& key, const Value& value) override {
        NodeT* node = find(tree.root, key);

        if (node) {
            node->val.value = value;
        }
        else {
            tree.insert(MapPair<Key, Value>(key, value));
        }
    }
    Value& operator[](const Key& key) override {
        NodeT* node = find(tree.root, key);

        if (!node) {
            tree.insert(MapPair<Key, Value>(key, Value()));
            node = find(tree.root, key);
        }

        return node->val.value;
    }
    bool contains(const Key& key) const override {
        return find(tree.root, key) != nullptr;
    }
    Value* get(const Key& key) override {
        NodeT* node = find(tree.root, key);
        if (node) return &node->val.value;
        return nullptr;
    }
    void erase(const Key& key) override {
        tree.erase(MapPair<Key, Value>(key, Value()));
    }
    void clear() override {
        tree.destroy(tree.root);
        tree.root = nullptr;
    }
};