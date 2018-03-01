#ifndef SOLVE_E
#define SOLVE_E

#include "objects.hpp"

#include <algorithm>
#include <set>
#include <iostream>
#include "include/random.hpp"
#include "include/Output.hpp"
using namespace std;

void PopulateRides(vector<Ride> &all_rides, auto &output) {
    set<Ride> available_rides(all_rides.begin(), all_rides.end());
    vector<int> available_vehicle_ids;
    map<int, pair<Point, int>> vehicle_location;
    map<int, vector<Ride>> vehicle_id_assigned_rides;
    for (int i = 0; i < num_vehicles; ++ i) {
        available_vehicle_ids.push_back(i);
        vehicle_location[i] = {Point({0, 0}), 0};
    }

    int totalPoints = 0;

    while (!available_rides.empty() && !available_vehicle_ids.empty()) {
        bool ok = false;

        sort(available_vehicle_ids.begin(), available_vehicle_ids.end(), [&](const int v1, const int v2) {
            return vehicle_location[v1].second < vehicle_location[v2].second;
        });

        int vehicle_id;
        if (available_vehicle_ids.size() > 1) {
            vehicle_id = available_vehicle_ids[RandLog(1, (int)available_vehicle_ids.size()) - 1];
        } else {
            vehicle_id = available_vehicle_ids[0];
        }

        vector<Ride> ok_rides;

        for (Ride ride : available_rides) {
            pair<Point, int> current_location = vehicle_location[vehicle_id];
            int startTime = current_location.second + current_location.first.Distance(ride.start);
            int points = ride.Points(startTime);
            if (points > 0) {
                ok_rides.push_back(ride);
                ok = true;
            }
        }

        if (ok) {
            sort(ok_rides.begin(), ok_rides.end(), [&](const Ride &r1, const Ride &r2) {
                pair<Point, int> current_location = vehicle_location[vehicle_id];
                return current_location.first.Distance(r1.start) < current_location.first.Distance(r2.start);
            });

            Ride selected_ride;
            if (ok_rides.size() >= 2) {
                selected_ride = ok_rides[RandLog(1, (int)ok_rides.size()) - 1];
            } else {
                selected_ride = ok_rides[0];
            }
            available_rides.erase(selected_ride);
            vehicle_id_assigned_rides[vehicle_id].push_back(selected_ride);
            pair<Point, int> current_location = vehicle_location[vehicle_id];
            int startTime = current_location.second + current_location.first.Distance(selected_ride.start);
            totalPoints += selected_ride.Points(startTime);
            vehicle_location[vehicle_id] = {selected_ride.destination, selected_ride.FinishTime(startTime)};
        } else {
            available_vehicle_ids.erase(find(available_vehicle_ids.begin(), available_vehicle_ids.end(), vehicle_id));
        }
    }
    for (int i = 0; i < num_vehicles; ++ i) {
        output.vehicles[i].rides = vehicle_id_assigned_rides[i];
    }
    cerr << totalPoints << " " << output.Cost() << endl;
    Dump(output);
}

void work(vector<Ride> &all_rides, auto &output) {
    while(true) {
        PopulateRides(all_rides, output);
    }
}

#endif
