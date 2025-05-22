#include "CheckPoint.h"
#include "Builders.h"
#include "Processor.h"
#include <iostream>


int main() {
    std::vector<CheckPoint*> cps = {
        new RequiredCheckPoint("Start", {55.75, 37.61}),
        new OptionalCheckPoint("River", {55.78, 37.65}, 0.5),
        new RequiredCheckPoint("Hill", {55.80, 37.70}),
        new OptionalCheckPoint("Forest", {55.82, 37.72}, 1.2)
    };

    // Выводим список
    TextReportBuilder textBuilder;
    CheckPointProcessor printer(&textBuilder);
    printer.process(cps);
    textBuilder.print();

    std::cout << std::endl;

    // Подсчёт штрафа
    PenaltyCalculatorBuilder penaltyBuilder;
    CheckPointProcessor calculator(&penaltyBuilder);
    calculator.process(cps);
    std::cout << "Суммарный штраф: " << penaltyBuilder.getTotalPenalty() << " ч." << std::endl;

    for (auto* cp : cps) delete cp;
    return 0;
}
