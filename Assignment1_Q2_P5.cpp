#include <iostream>
#include <cmath>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

// Inline functions to eliminate function call overhead in loop[cite: 4, 6]
inline double distanceBetween(double x1, double y1, double x2, double y2) { //[cite: 4]
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

inline double toRadians(double degrees) { //[cite: 4]
    return degrees * (M_PI / 180.0);
}

inline double clamp(double value, double minVal, double maxVal) { //[cite: 4]
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

inline bool isInSafeZone(double x, double y, double cx, double cy, double radius) { //[cite: 4]
    return distanceBetween(x, y, cx, cy) <= radius;
}

int main() {
    double homeX = 0.0, homeY = 0.0;
    double safeRadius = 50.0; //[cite: 4]

    // 3 Test Waypoints[cite: 4]
    double waypoints[3][2] = {
        {10.0, 20.0},
        {40.0, 35.0},
        {60.0, 10.0}
    };

    cout << fixed << setprecision(2);
    cout << "Home Position: (" << homeX << ", " << homeY << ") | Safe Radius: " << safeRadius << "\n\n";

    for (int i = 0; i < 3; i++) {
        double wx = waypoints[i][0];
        double wy = waypoints[i][1];
        double dist = distanceBetween(homeX, homeY, wx, wy);
        bool safe = isInSafeZone(wx, wy, homeX, homeY, safeRadius);

        cout << "Waypoint " << (i + 1) << " (" << wx << ", " << wy << "):" << endl;
        cout << "  Distance from Home : " << dist << " units" << endl;
        cout << "  Inside Safe Zone   : " << (safe ? "YES" : "NO") << endl;
    }

    return 0;
}