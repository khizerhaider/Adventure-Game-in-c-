#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    string description;
    bool canPickUp;
};

struct Room {
    string name;
    string description;
    map<string, int> exits;
    vector<Item> items;
};

void displayRoom(const Room& room) {
    cout << "You are in " << room.name << ". " << room.description << endl;
    cout << "Exits: ";
    for (const auto& exit : room.exits) {
        cout << exit.first << " ";
    }
    cout << endl;
}

void displayItems(const Room& room) {
    if (room.items.empty()) {
        cout << "There are no items in this room." << endl;
    } else {
        cout << "Items in this room:" << endl;
        for (const auto& item : room.items) {
            cout << "- " << item.name << ": " << item.description << endl;
        }
    }
}

bool itemExistsInRoom(const Room& room, const string& itemName) {
    for (const auto& item : room.items) {
        if (item.name == itemName && item.canPickUp) {
            return true;
        }
    }
    return false;
}

int main() {
    Item key = {"key", "A rusty old key.", true};
    Item sword = {"sword", "A sharp sword.", true};

    Room outside = {"Outside the Castle", "You are standing outside a dark castle.", {{"north", 1}}, {key}};
    Room hall = {"Castle Hall", "You are in a grand hall with torches on the walls.", {{"south", 0}, {"north", 2}}, {sword}};
    Room treasureRoom = {"Treasure Room", "You found the treasure room!", {{"south", 1}}, {}};

    vector<Room> rooms = {outside, hall, treasureRoom};

    int currentRoomIndex = 0;
    Room currentRoom = rooms[currentRoomIndex];

    while (true) {
        displayRoom(currentRoom);
        displayItems(currentRoom);

        cout << "What would you like to do? ";
        string action;
        cin >> action;

        if (action == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }

        if (currentRoom.exits.find(action) != currentRoom.exits.end()) {
            currentRoomIndex = currentRoom.exits[action];
            currentRoom = rooms[currentRoomIndex];
            continue;
        }

        if (action == "pickup") {
            cout << "Enter the name of the item you want to pick up: ";
            string itemName;
            cin >> itemName;

            bool itemFound = itemExistsInRoom(currentRoom, itemName);

            if (itemFound) {
                cout << "You picked up " << itemName << "." << endl;
                currentRoom.items.erase(remove_if(currentRoom.items.begin(), currentRoom.items.end(),
                                                  [&](const Item& item) { return item.name == itemName; }),
                                        currentRoom.items.end());
            } else {
                cout << "No such item available to pick up." << endl;
            }
            continue;
        }

        cout << "Invalid command. Try again." << endl;
    }

    return 0;
}
