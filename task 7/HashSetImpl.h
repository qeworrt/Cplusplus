#pragma once
#include "SetImpl.h"
#include <unordered_set>

class HashSetImpl : public SetImpl {
    std::unordered_set<int> data;

public:
    void add(int value) override {
        data.insert(value);
    }

    void remove(int value) override {
        data.erase(value);
    }

    bool contains(int value) const override {
        return data.find(value) != data.end();
    }

    std::unique_ptr<SetImpl> clone() const override {
        return std::make_unique<HashSetImpl>(*this);
    }

    std::vector<int> getElements() const override {
        return std::vector<int>(data.begin(), data.end());
    }

    size_t size() const override {
        return data.size();
    }
};
