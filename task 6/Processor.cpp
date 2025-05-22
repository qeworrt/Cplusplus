#include "Processor.h"

CheckPointProcessor::CheckPointProcessor(CheckPointBuilder* builder)
    : builder(builder) {}

void CheckPointProcessor::process(const std::vector<CheckPoint*>& points) {
    builder->reset();
    for (CheckPoint* cp : points) {
        builder->addCheckPoint(cp);
    }
}
