#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    const int FLOORS = 3;
    const int ROOMS = 3;
    double grid[FLOORS][ROOMS];

    cout << "Enter temperature for 3 floors (3 rooms per floor):\n";
    for (int i = 0; i < FLOORS; i++) {
        for (int j = 0; j < ROOMS; j++) {
            cin >> grid[i][j];
        }
    }

    // 1. Formatted Table Display
    cout << fixed << setprecision(1);
    cout << "\n\tRoom1\tRoom2\tRoom3\n";
    for (int i = 0; i < FLOORS; i++) {
        cout << "Floor " << (i + 1) << " : ";
        for (int j = 0; j < ROOMS; j++) {
            cout << grid[i][j] << "\t";
        }
        cout << "\n";
    }

    // 2. Hottest Room, Warning Count, aur Floor Averages
    double maxTemp = -1e9;
    int hotFloor = -1, hotRoom = -1;

    int warningCount = 0;

    double maxFloorAvg = -1e9;
    int hottestFloorIdx = -1;

    for (int i = 0; i < FLOORS; i++) {
        double floorSum = 0;
        for (int j = 0; j < ROOMS; j++) {
            double current = grid[i][j];
            floorSum += current;

            // Check Hottest Room
            if (current > maxTemp) {
                maxTemp = current;
                hotFloor = i + 1;
                hotRoom = j + 1;
            }

            // Check Warning Threshold (>= 30.0)
            if (current >= 30.0) {
                warningCount++;
            }
        }

        // Floor average calculate
        double currentFloorAvg = floorSum / ROOMS;
        if (currentFloorAvg > maxFloorAvg) {
            maxFloorAvg = currentFloorAvg;
            hottestFloorIdx = i + 1;
        }
    }

    // 3. Report Summary Display
    cout << setprecision(2);
    cout << "\nHottest Room             : Floor " << hotFloor << ", Room " << hotRoom << " -> " << maxTemp << "°C" << endl;
    cout << "Hottest Floor            : Floor " << hottestFloorIdx << " (avg -> " << maxFloorAvg << "°C)" << endl;
    cout << "Rooms at WARNING or above: " << warningCount << endl;

    return 0;
}