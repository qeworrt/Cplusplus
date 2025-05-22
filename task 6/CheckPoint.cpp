#include "CheckPoint.h"
#include <string>

CheckPoint::CheckPoint(const std::string& name, Coordinates coord)
    : name(name), coord(coord) {}

RequiredCheckPoint::RequiredCheckPoint(const std::string& name, Coordinates coord)
    : CheckPoint(name, coord) {}

bool RequiredCheckPoint::isOptional() const {
    return false;
}

double RequiredCheckPoint::getPenalty() const {
    return 0.0;
}

std::string RequiredCheckPoint::getInfo(size_t index) const {
    return std::to_string(index) + ". " + name +
           " (" + std::to_string(coord.latitude) + ", " +
           std::to_string(coord.longitude) + ") - незачёт СУ";
}

OptionalCheckPoint::OptionalCheckPoint(const std::string& name, Coordinates coord, double penalty)
    : CheckPoint(name, coord), penalty(penalty) {}

bool OptionalCheckPoint::isOptional() const {
    return true;
}

double OptionalCheckPoint::getPenalty() const {
    return penalty;
}

std::string OptionalCheckPoint::getInfo(size_t index) const {
    return std::to_string(index) + ". " + name +
           " (" + std::to_string(coord.latitude) + ", " +
           std::to_string(coord.longitude) + ") - штраф: " +
           std::to_string(penalty) + " ч.";
}
