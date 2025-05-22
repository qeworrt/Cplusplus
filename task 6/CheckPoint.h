#pragma once
#include <string>

struct Coordinates {
    double latitude;
    double longitude;
};

class CheckPoint {
public:
    CheckPoint(const std::string& name, Coordinates coord);
    virtual ~CheckPoint() = default;

    virtual bool isOptional() const = 0;
    virtual double getPenalty() const = 0;
    virtual std::string getInfo(size_t index) const = 0;

protected:
    std::string name;
    Coordinates coord;
};

class RequiredCheckPoint : public CheckPoint {
public:
    RequiredCheckPoint(const std::string& name, Coordinates coord);
    bool isOptional() const override;
    double getPenalty() const override;
    std::string getInfo(size_t index) const override;
};

class OptionalCheckPoint : public CheckPoint {
public:
    OptionalCheckPoint(const std::string& name, Coordinates coord, double penalty);
    bool isOptional() const override;
    double getPenalty() const override;
    std::string getInfo(size_t index) const override;

private:
    double penalty;
};
