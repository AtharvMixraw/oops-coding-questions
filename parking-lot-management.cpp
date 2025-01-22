#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class ParkingSlot {
private:
    int slotNumber;
    bool occupied;
public:
    ParkingSlot(int num) : slotNumber(num), occupied(false) {}
    void occupySlot() { occupied = true; }
    void freeSlot() { occupied = false; }
    bool isOccupied() { return occupied; }
};

class Vehicle {
protected:
    string licensePlate;
public:
    Vehicle(string plate) : licensePlate(plate) {}
    virtual double calculateParkingFee(int hours) = 0;  // Pure virtual function (polymorphism)
    string getLicensePlate() { return licensePlate; }
};

// ParkingLot class definition
class ParkingLot {
private:
    unordered_map<string, Vehicle*> parkedVehicles;  // Maps license plate to Vehicle pointer
    vector<ParkingSlot> slots;  // Stores all parking slots

public:
    // Constructor to initialize parking slots with given capacity
    ParkingLot(int capacity) {
        for (int i = 0; i < capacity; i++) 
            slots.emplace_back(i + 1);  // Creates slots numbered 1 to 'capacity'
    }

    // Function to park a vehicle
    bool parkVehicle(Vehicle* v) {
        for (auto& slot : slots) {  // Iterate through all parking slots
            if (!slot.isOccupied()) {  // If a slot is available
                slot.occupySlot();  // Mark slot as occupied
                parkedVehicles[v->getLicensePlate()] = v;  // Store vehicle in map with license plate as key
                cout << "Vehicle parked: " << v->getLicensePlate() << endl;
                return true;  // Parking successful
            }
        }
        cout << "No available slots!" << endl;
        return false;  // Parking failed (no slots available)
    }

    // Function to exit (remove) a vehicle and calculate parking fee
    double exitVehicle(string plate, int hours) {
        // Check if the vehicle is present in the parking lot
        if (parkedVehicles.find(plate) != parkedVehicles.end()) {
            double fee = parkedVehicles[plate]->calculateParkingFee(hours);  // Calculate fee based on vehicle type
            parkedVehicles.erase(plate);  // Remove vehicle from the map
            cout << "Vehicle " << plate << " exited. Fee: $" << fee << endl;
            return fee;  // Return calculated fee
        }
        cout << "Vehicle not found!" << endl;
        return 0.0;  // Return 0 if vehicle not found
    }
};

// Example usage
class Car : public Vehicle {
public:
    Car(string plate) : Vehicle(plate) {}
    double calculateParkingFee(int hours) override {
        return hours * 20;  // Parking fee for cars: $20 per hour
    }
};

int main() {
    ParkingLot lot(3);  // Create a parking lot with 3 slots
    Vehicle* car1 = new Car("KA-01-1234");
    Vehicle* car2 = new Car("KA-02-5678");

    lot.parkVehicle(car1);  // Park the first car
    lot.parkVehicle(car2);  // Park the second car

    lot.exitVehicle("KA-01-1234", 3);  // Exit the first car after 3 hours

    delete car1;  // Clean up allocated memory
    delete car2;

    return 0;
}
