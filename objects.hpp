#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
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

    inline bool operator < (const Ride &other) const {
        return id < other.id;
    }
};


struct Vehicle {
    vector<Ride> rides;
    int id;

    int64 SimulateRide() {
        int current_time = 0;
        Point current_position({0, 0});
        int64 points = 0;

        for (auto& r : rides) {
            int arrival_time = current_time + current_position.Distance(r.start);
            points += r.Points(arrival_time);
            current_time = r.FinishTime(arrival_time);
            current_position = r.destination;
        }

        return points;
    }
};

#endif