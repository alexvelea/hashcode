#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include <unistd.h> // getpid

#include "include/HashCode.hpp"
using namespace std;

typedef long long int64;

int h, w, num_vehicles;
int bonus_points_on_time;
int max_time;

struct Point {
    int x, y;

    int Distance(Point rhs) const {
        return abs(x - rhs.x) + abs(y - rhs.y);
    }
};

struct Ride {
    int id;

    Point start, destination;
    int t_start, t_end;

    int Distance() {
        return start.Distance(destination);
    }

    int Points(int arrival_time) {
        int bonus = 0;
        if (arrival_time <= t_start) {
            bonus += ::bonus_points_on_time;
        }

        if (arrival_time + Distance() <= t_end) {
            return bonus + Distance();
        } else {
            return 0;
        }
    }

    int FinishTime(int start_time) {
        start_time = max(start_time, t_start);
        return start_time + Distance();
    }
};


struct Vehicle {
    vector<Ride> rides;

    int64 SimulateRide() {
        int current_time = 0;
        Point current_position({0, 0});
        int64 points = 0;

        for (auto& r : rides) {
            int arrival_time = current_time + current_position.Distance(r.start);
            points += r.Points(arrival_time);
            current_time = r.FinishTime(arrival_time);
        }

        return points;
    }
};

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
        }
    }

    Input() { }
} input;


struct Output : BaseOutput {
    vector<Vehicle> vehicles;

    Output() : vehicles(num_vehicles) {
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
    Debug(h, w, max_time, num_vehicles, bonus_points_on_time);
}
