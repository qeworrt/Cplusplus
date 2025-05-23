#pragma once
#include "ArraySetImpl.h"
#include "HashSetImpl.h"
#include <memory>
#include <iostream>

class Set {
    std::unique_ptr<SetImpl> impl;
    static const size_t SWITCH_THRESHOLD = 10;

    void checkAndSwitch() {
        if (impl->size() > SWITCH_THRESHOLD && dynamic_cast<ArraySetImpl*>(impl.get())) {
            auto newImpl = std::make_unique<HashSetImpl>();
            for (int val : impl->getElements()) {
                newImpl->add(val);
            }
            impl = std::move(newImpl);
        }
    }

public:
    Set() : impl(std::make_unique<ArraySetImpl>()) {}

    void add(int value) {
        impl->add(value);
        checkAndSwitch();
    }

    void remove(int value) {
        impl->remove(value);
    }

    bool contains(int value) const {
        return impl->contains(value);
    }

    Set unionWith(const Set& other) const {
        Set result;
        for (int val : impl->getElements())
            result.add(val);
        for (int val : other.impl->getElements())
            result.add(val);
        return result;
    }

    Set intersectWith(const Set& other) const {
        Set result;
        for (int val : impl->getElements()) {
            if (other.contains(val))
                result.add(val);
        }
        return result;
    }

    void print() const {
        for (int val : impl->getElements()) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};
