#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// ==========================================
// Part A - Entity Class with this Pointer & Method Chaining
// ==========================================
class Entity {
private:
    string name;
    int health;
    int level;
    string type; // "Player", "Enemy", "Item"

public:
    // Default constructor
    Entity() : name("Unknown"), health(100), level(1), type("Player") {}

    // Setters returning Entity& for method chaining using *this[cite: 1, 3]
    Entity& setName(const string& name) {
        this->name = name; //[cite: 1, 3]
        return *this; //[cite: 1, 3]
    }

    Entity& setHealth(int health) {
        this->health = health; //[cite: 1, 3]
        return *this; //[cite: 1, 3]
    }

    Entity& setLevel(int level) {
        this->level = level; //[cite: 1, 3]
        return *this; //[cite: 1, 3]
    }

    Entity& setType(const string& type) {
        this->type = type; //[cite: 1, 3]
        return *this; //[cite: 1, 3]
    }

    // Getters (all marked const)[cite: 3]
    string getName() const { return name; } //[cite: 3]
    int getHealth() const { return health; } //[cite: 3]
    int getLevel() const { return level; } //[cite: 3]
    string getType() const { return type; } //[cite: 3]

    void displayInfo() const {
        cout << left << setw(15) << name 
             << setw(10) << type 
             << setw(10) << health 
             << setw(8) << level << "\n";
    }
};

// ==========================================
// Part B - Namespaces & Overloaded Math Functions
// ==========================================
namespace Physics {
    double clamp(double val, double min, double max) { //[cite: 3]
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    double lerp(double a, double b, double t) { //[cite: 3]
        return a + t * (b - a);
    }
}

namespace GameMath {
    int clamp(int val, int min, int max) { //[cite: 3]
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    double lerp(double a, double b, double t) { //[cite: 3]
        return a + t * (b - a);
    }
}

// Global variable for Scope Resolution Demo[cite: 3]
int level = 1; // Game difficulty level[cite: 3]

// Nested Namespace for Bonus Question[cite: 1, 3]
namespace Engine::Audio {
    void playSound(string name) { //[cite: 3]
        cout << "Playing: " << name << "\n"; //[cite: 3]
    }
}

// ==========================================
// Main Function
// ==========================================
int main() {
    srand(time(0));

    // --- Part A: Method Chaining Demo ---[cite: 3]
    cout << "===== PART A: ENTITY SYSTEM (METHOD CHAINING) =====\n";
    Entity player, enemy, item;
    player.setName("Aragorn").setHealth(100).setLevel(10).setType("Player"); //[cite: 3]
    enemy.setName("Orc").setHealth(60).setLevel(5).setType("Enemy"); //[cite: 3]
    item.setName("HealthPotion").setHealth(0).setLevel(1).setType("Item"); //[cite: 3]

    cout << left << setw(15) << "Name" << setw(10) << "Type" << setw(10) << "Health" << setw(8) << "Level" << "\n";
    cout << "---------------------------------------------\n";
    player.displayInfo();
    enemy.displayInfo();
    item.displayInfo();

    // --- Part B: Namespaces Demo ---[cite: 1, 3]
    cout << "\n===== PART B: NAMESPACES =====\n";
    cout << "Physics::clamp (Velocity: 125.5 in [0, 100]) : " << Physics::clamp(125.5, 0.0, 100.0) << "\n"; //[cite: 3]
    cout << "GameMath::clamp (Health: -15 in [0, 100])    : " << GameMath::clamp(-15, 0, 100) << "\n"; //[cite: 3]
    cout << "Physics::lerp (0 to 100 at t=0.5)            : " << Physics::lerp(0.0, 100.0, 0.5) << "\n"; //[cite: 3]

    // Limited Block Scope using directive demonstration[cite: 1, 3]
    {
        using namespace GameMath; //[cite: 1, 3]
        cout << "[Block Scope GameMath] lerp(10, 50, 0.25)  : " << lerp(10.0, 50.0, 0.25) << "\n"; //[cite: 3]
    }

    // --- Scope Resolution & Nested Namespace Bonus ---[cite: 1, 3]
    int level = 50; // Local player level inside main()[cite: 3]
    cout << "\nLocal Player Level (main)       : " << level << "\n"; //[cite: 3]
    cout << "Global Game Difficulty (::level) : " << ::level << "\n"; //[cite: 3]
    Engine::Audio::playSound("sword_clash"); //[cite: 3]

    // --- Part C: Dynamic 2D Game Map ---[cite: 1, 3]
    cout << "\n===== PART C: DYNAMIC 2D GAME MAP =====\n";
    int R, C;
    cout << "Enter Map Rows (R): ";
    cin >> R;
    cout << "Enter Map Columns (C): ";
    cin >> C;

    if (R <= 0 || C <= 0) {
        cout << "Invalid map dimensions!\n";
        return 1;
    }

    // 1. Allocate dynamic 2D array on heap[cite: 1, 3]
    int** map = new int*[R]; //[cite: 1, 3]
    for (int i = 0; i < R; i++) {
        map[i] = new int[C]; //[cite: 1, 3]
    }

    // 2. Fill grid with random tiles (0: Grass, 1: Water, 2: Mountain, 3: Forest, 4: Dungeon)[cite: 3]
    int counts[5] = {0};
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            map[i][j] = rand() % 5; //[cite: 3]
            counts[map[i][j]]++;
        }
    }

    // 3. Display Grid[cite: 3]
    cout << "\n===== GAME MAP (" << R << " x " << C << ") =====\n"; //[cite: 3]
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }

    // Legend[cite: 3]
    cout << "\nLegend: 0 = Grass  1 = Water  2 = Mountain  3 = Forest  4 = Dungeon\n"; //[cite: 3]

    // 4. Print Tile Counts[cite: 3]
    cout << "\nTile Count:\n";
    cout << "  Grass   : " << counts[0] << "\n";
    cout << "  Water   : " << counts[1] << "\n";
    cout << "  Mountain: " << counts[2] << "\n";
    cout << "  Forest  : " << counts[3] << "\n";
    cout << "  Dungeon : " << counts[4] << "\n";

    // 5. Deallocate Dynamic 2D Array[cite: 1, 3]
    for (int i = 0; i < R; i++) {
        delete[] map[i]; //[cite: 1, 3]
    }
    delete[] map; //[cite: 1, 3]

    return 0;
}