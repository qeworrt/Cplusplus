#pragma once
#include "Builders.h"
#include <vector>

class CheckPointProcessor {
public:
    CheckPointProcessor(CheckPointBuilder* builder);
    void process(const std::vector<CheckPoint*>& points);

private:
    CheckPointBuilder* builder;
};
