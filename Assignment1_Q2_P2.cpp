#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// No arr[i] used anywhere; pure pointer arithmetic[cite: 4, 5]

double computeRMS(double* signal, int n) {
    double sumSq = 0.0;
    for (int i = 0; i < n; i++) {
        sumSq += (*(signal + i)) * (*(signal + i));
    }
    return sqrt(sumSq / n);
}

void normalise(double* signal, int n) {
    double maxAbs = 0.0;
    for (int i = 0; i < n; i++) {
        double val = fabs(*(signal + i));
        if (val > maxAbs) {
            maxAbs = val;
        }
    }
    if (maxAbs != 0.0) {
        for (int i = 0; i < n; i++) {
            *(signal + i) = *(signal + i) / maxAbs;
        }
    }
}

int countZeroCrossings(double* signal, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        double current = *(signal + i);
        double next = *(signal + i + 1);
        if ((current >= 0 && next < 0) || (current < 0 && next >= 0)) {
            count++;
        }
    }
    return count;
}

void applyGain(double* signal, int n, double gainFactor) {
    for (int i = 0; i < n; i++) {
        *(signal + i) = (*(signal + i)) * gainFactor;
    }
}

void printSignal(const double* signal, int n) {
    for (int i = 0; i < n; i++) {
        cout << *(signal + i) << " ";
    }
    cout << endl;
}

int main() {
    const int N = 7;
    double rawSignal[N] = {0.5, 1.2, 0.8, 0.3, 1.0, -0.9, 0.1}; // Test signal

    cout << fixed << setprecision(4);
    cout << "Original Signal: ";
    printSignal(rawSignal, N);

    cout << "Initial RMS: " << computeRMS(rawSignal, N) << endl;
    cout << "Zero Crossings: " << countZeroCrossings(rawSignal, N) << endl;

    normalise(rawSignal, N);
    cout << "\nAfter Normalise: ";
    printSignal(rawSignal, N);

    applyGain(rawSignal, N, 2.0);
    cout << "After Apply Gain (x2): ";
    printSignal(rawSignal, N);

    return 0;
}