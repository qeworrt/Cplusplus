#include "Builders.h"
#include <iostream>

void TextReportBuilder::reset() {
    lines.clear();
}

void TextReportBuilder::addCheckPoint(CheckPoint* cp) {
    lines.push_back(cp->getInfo(lines.size() + 1));
}

void TextReportBuilder::print() const {
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
}

void PenaltyCalculatorBuilder::reset() {
    totalPenalty = 0.0;
}

void PenaltyCalculatorBuilder::addCheckPoint(CheckPoint* cp) {
    if (cp->isOptional()) {
        totalPenalty += cp->getPenalty();
    }
}

double PenaltyCalculatorBuilder::getTotalPenalty() const {
    return totalPenalty;
}
