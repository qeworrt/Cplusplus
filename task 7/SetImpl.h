#pragma once
#include <memory>
#include <vector>

class SetImpl {
public:
    virtual ~SetImpl() = default;
    virtual void add(int value) = 0;
    virtual void remove(int value) = 0;
    virtual bool contains(int value) const = 0;
    virtual std::unique_ptr<SetImpl> clone() const = 0;
    virtual std::vector<int> getElements() const = 0;
    virtual size_t size() const = 0;
};
