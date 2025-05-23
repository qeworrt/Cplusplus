#pragma once
#include "SetImpl.h"
#include <algorithm>

class ArraySetImpl : public SetImpl {
    std::vector<int> data;

public:
    void add(int value) override {
        if (!contains(value)) data.push_back(value);
    }

    void remove(int value) override {
        data.erase(std::remove(data.begin(), data.end(), value), data.end());
    }

    bool contains(int value) const override {
        return std::find(data.begin(), data.end(), value) != data.end();
    }

    std::unique_ptr<SetImpl> clone() const override {
        return std::make_unique<ArraySetImpl>(*this);
    }

    std::vector<int> getElements() const override {
        return data;
    }

    size_t size() const override {
        return data.size();
    }
};
