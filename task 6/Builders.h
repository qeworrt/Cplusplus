#pragma once
#include "CheckPoint.h"
#include <vector>
#include <string>

class CheckPointBuilder {
public:
    virtual ~CheckPointBuilder() = default;
    virtual void reset() = 0;
    virtual void addCheckPoint(CheckPoint* cp) = 0;
};

class TextReportBuilder : public CheckPointBuilder {
public:
    void reset() override;
    void addCheckPoint(CheckPoint* cp) override;
    void print() const;

private:
    std::vector<std::string> lines;
};

class PenaltyCalculatorBuilder : public CheckPointBuilder {
public:
    void reset() override;
    void addCheckPoint(CheckPoint* cp) override;
    double getTotalPenalty() const;

private:
    double totalPenalty = 0.0;
};
