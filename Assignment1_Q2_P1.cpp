#include <iostream>
using namespace std;

// V1: Call by Value (Buggy - swaps local copies only)[cite: 4, 6]
void resetSensorPairV1(int reading1, int reading2) {
    int temp = reading1;
    reading1 = reading2;
    reading2 = temp;
}

// Fix 1: Call by Reference[cite: 4, 6]
void resetSensorPairV2(int& reading1, int& reading2) {
    int temp = reading1;
    reading1 = reading2;
    reading2 = temp;
}

// Fix 2: Call by Pointer[cite: 4, 6]
void resetSensorPairV3(int* reading1, int* reading2) {
    int temp = *reading1;
    *reading1 = *reading2;
    *reading2 = temp;
}

int main() {
    /*
     * ROOT CAUSE EXPLANATION:
     * In V1 (Call by Value), copies of arguments are passed into the function's own stack frame[cite: 6].
     * Any swap operation modifies only those local copies inside resetSensorPairV1()[cite: 6].
     * The original variables in main() remain unaffected once the function returns[cite: 6].
     * In V2 and V3, we pass references (aliases) or memory addresses (pointers) to directly modify caller memory[cite: 5, 6].
     */

    // Test V1
    int a = 55, b = 12;
    cout << "--- V1: Call by Value ---" << endl;
    cout << "Before: A = " << a << "  B = " << b << endl;
    resetSensorPairV1(a, b);
    cout << "After : A = " << a << "  B = " << b << "  (values unchanged)" << endl;

    // Test V2
    cout << "\n--- V2: Call by Reference ---" << endl;
    cout << "Before: A = " << a << "  B = " << b << endl;
    resetSensorPairV2(a, b);
    cout << "After : A = " << a << "  B = " << b << "  (values swapped)" << endl;

    // Test V3
    cout << "\n--- V3: Call by Pointer ---" << endl;
    cout << "Before: A = " << a << "  B = " << b << endl;
    resetSensorPairV3(&a, &b);
    cout << "After : A = " << a << "  B = " << b << "  (values swapped back)" << endl;

    return 0;
}
