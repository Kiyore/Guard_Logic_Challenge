#include <iostream>
#include <unordered_map>
#include <thread>
#include <chrono>
using namespace std;

enum class DoorID { 
    GREEN = 1, RED, YELLOW 
};
enum class DoorResult { 
    SAFE_EXIT, TRAP, START_POINT 
};

struct Door {
    DoorID id;
    string label;
    DoorResult result;
};

struct SystemState {
    int securityCode;
    bool hasKeycard;
    bool alarmTriggered;
};

// CORE SYSTEM
class GuardSystem {
public:
    DoorID decide(const SystemState& state) const {
        //Trap
        if (state.securityCode == 3)
            return DoorID::RED;

        //Alarm condition
        if (state.alarmTriggered)
            return DoorID::YELLOW;

        // Safe condition
        if (state.hasKeycard && state.securityCode == 7)
            return DoorID::GREEN;

        // fallback
        return DoorID::YELLOW;
    }
};

string resultToString(DoorResult r) {
    if (r == DoorResult::SAFE_EXIT) return "Safe Exit";
    if (r == DoorResult::TRAP) return "Trap";
    return "Back to Start";
}

int main() {
    unordered_map<DoorID, Door> doors = {
        {DoorID::GREEN,  {DoorID::GREEN,  "Green Door",  DoorResult::SAFE_EXIT}},
        {DoorID::RED,    {DoorID::RED,    "Red Door",    DoorResult::TRAP}},
        {DoorID::YELLOW, {DoorID::YELLOW, "Yellow Door", DoorResult::START_POINT}}
    };

    GuardSystem guard;
    SystemState state;

    while (true) {
        cout << "\nEnter Security Code: ";
        cin >> state.securityCode;

        cout << "Has Keycard (1/0): ";
        cin >> state.hasKeycard;

        cout << "Alarm Triggered (1/0): ";
        cin >> state.alarmTriggered;
      
        // Alarm has HIGHEST priority
        if (state.alarmTriggered) {
        cout << "\nAlarm triggered! You cannot proceed.\n";
        cout << "Redirecting to start...\n";
        cout << "System resetting...\n";

        std::this_thread::sleep_for(std::chrono::seconds(3));

        cout << "Alarm cleared. Please re-enter details.\n";
        continue;
        }
  
        // Access control
        if (!state.hasKeycard) {
            cout << "\nAccess Denied: You cannot access doors without a keycard.\n";
            cout << "Please obtain a keycard first.\n";
            continue;
        }

        // Decide door
        DoorID decision = guard.decide(state);

        // Trap
        if (decision == DoorID::RED) {
            cout << "\nChosen Door: Red Door\n";
            cout << "Outcome: Trap\n";
            break;
        }

        // Alarm handling
        if (state.alarmTriggered) {
            cout << "\nAlarm triggered! Redirecting to start...\n";
            cout << "System resetting...\n";

            std::this_thread::sleep_for(std::chrono::seconds(3));

            cout << "Alarm cleared. Please re-enter details.\n";
            continue;
        }

        // Safe exit
        if (decision == DoorID::GREEN) {
            cout << "\nChosen Door: Green Door\n";
            cout << "Outcome: Safe Exit\n";
            break;
        }

        // Yellow → retry
        if (decision == DoorID::YELLOW) {
            cout << "\nChosen Door: Yellow Door\n";
            cout << "Outcome: Back to Start\n";
            cout << "Retrying from start...\n";
            continue;
        }
    }

    return 0;
}
