#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include <unistd.h> // getpid

#include "include/HashCode.hpp"
#include "objects.hpp"
#include "no_hurry.hpp"

using namespace std;

struct Input {
    vector<Ride> all_rides;

    Input(std::ifstream in) {
        in >> ::h >> ::w;
        in >> ::num_vehicles;
        int num_rides; in >> num_rides;
        in >> ::bonus_points_on_time;
        in >> max_time;

        for (int i = 0; i < num_rides; i += 1) {
            Ride r;
            r.id = i;
            in >> r.start.x >> r.start.y;
            in >> r.destination.x >> r.destination.y;
            in >> r.t_start >> r.t_end;
            all_rides.push_back(r);
        }
    }

    Input() { }
} input;


struct Output : BaseOutput {
    vector<Vehicle> vehicles;

    Output() : vehicles(num_vehicles) {
        for (int i = 0; i < vehicles.size(); ++ i) {
            vehicles[i].id = i;
        }
    }

    double Cost() {
        int64 cost = 0;
        for (auto& v : vehicles) {
            cost += v.SimulateRide();        
        }

        return cost;
    }

    void Dump(ostream& out) {
        for (auto v : vehicles) {
            out << v.rides.size() << ' ';
            for (auto r : v.rides) {
                out << r.id << ' ';
            }
            out << '\n';
        }
    }
};

int main(int argc, char** argv) {
    srand(time(0) + getpid());
    InitHashCode(argc, argv);

    input = Input(GetInputStream());
    Debug(h, w, max_time, num_vehicles, bonus_points_on_time, input.all_rides.size());
    Output output;
    work(input.all_rides, output);
}
