#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

class  Ride{
protected:
    string source;
    string destination;
    double baseFare;
public:
    Ride(string src, string dest, double fare) : source(src), destination(dest), baseFare(fare) {}
    virtual double calculateFare(int distance) = 0;
    virtual void rideDetails(){
        cout << "Source: " << source << ", Destination: " << destination;
    }
    virtual ~Ride() {}
};

class RegularRide : public Ride{
    public:
        RegularRide(string src, string dest) : Ride(src,dest,5.0){}
        double calculateFare(int distance) override{
            return baseFare*distance;
        }
};

class PremiumRide : public Ride{
    public:
        PremiumRide(string src, string dest) : Ride(src,dest,10.0){}
        double calculateFare(int distance) override{
            return baseFare*distance + 20;
        }
};

class PoolRide : public Ride{
    public:
        PoolRide(string src, string dest) : Ride(src,dest,3.0){}
        double calculateFare(int distance) override{
            return (baseFare*distance)/2;
        }
};

class Driver{
protected:
    string name;
    string licenseNum;
public:
    Driver(string name, string license) : name(name), licenseNum(license){}
    void showDetails() {
        cout << "Driver: " << name << ", License: " << licenseNum << endl;
    }
};

class BookingSystem{
protected:
    vector<Ride*> rides;
public:
    void bookRide(Ride* ride, int distance){
        ride->rideDetails();
        cout<<"Fare: "<<ride->calculateFare(distance)<<endl;
        rides.push_back(ride);
    }
    ~BookingSystem(){
        for(auto r : rides){
            delete r;
        }
    }
};

int main() {
    BookingSystem system;
    
    Ride* ride1 = new RegularRide("Home", "Office");
    Ride* ride2 = new PremiumRide("Mall", "Airport");
    Ride* ride3 = new PoolRide("Station", "Hotel");

    system.bookRide(ride1, 10);
    system.bookRide(ride2, 15);
    system.bookRide(ride3, 20);

    delete ride1;
    delete ride2;
    delete ride3;

    return 0;
}