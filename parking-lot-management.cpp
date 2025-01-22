#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
using namespace std;

class Vehicle {
protected:
    string licensePlate;
    time_t entryTime;
public:
    Vehicle(string licensePlate) {
        this->licensePlate = licensePlate;
        this->entryTime = time(0);
    }
    virtual double calculateFee(int hours) = 0;
    string getLicensePlate() {
        return licensePlate;
    }
    time_t getEntryTime() {
        return entryTime;
    }
};