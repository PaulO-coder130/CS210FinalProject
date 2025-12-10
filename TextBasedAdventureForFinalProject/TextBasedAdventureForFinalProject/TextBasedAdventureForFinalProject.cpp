#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <unordered_map>

using namespace std;

struct ItemNode {
	string itemName;
	string itemType;
	int amount;
	ItemNode* next;
	ItemNode* previous;

	ItemNode(string name, string type, int numAmount = 1) : itemName(name), amount(numAmount), itemType(type), next(nullptr), previous(nullptr){}
};

class inventoryList {
private:
	ItemNode* head;
	ItemNode* tail;

	const int maxSize = 10;
	int size = 0;

public:
	inventoryList() : head(nullptr), tail(nullptr) {}

	void collectItem(string& name, const string& type = "typesnotincludedyet :/", int amount = 1) {

		if (head == nullptr) {
			ItemNode* newItem = new ItemNode(name, type, amount);
			head = newItem;
			tail = newItem;

			newItem->next = newItem;
			newItem->previous = newItem;
			size++;
			return;
		}

		ItemNode* current = head;

		do {
			if (current->itemName == name) {
				current->amount += amount;
				return;
			}
			current = current->next;
		} while (current != head);

		ItemNode* newItem = new ItemNode(name, type, amount);

		newItem->next = head;
		newItem->previous = tail;
		tail->next = newItem;
		head->previous = newItem;
		head = newItem;

		size++;

	}

	bool itemInList(const string& name) {
		if (head == nullptr) {
			return false;
		}

		ItemNode* current = head;
		do {
			if (current->itemName == name) {
				return true;
			}
			current = current->next;
		} while (current != head);
		return false;
	}
	
	void removeItem(const string& itemName){
		if (head == nullptr) {
			return;
		}
		ItemNode* current = head;
		ItemNode* item = nullptr;
		do {
			if (current->itemName == itemName) {
				item = current;
				break;
			}
			current = current->next;
		} while (current != head);

		if (item == nullptr) {
			return;
		}

		if (size == 1) {
			delete item;
			head = nullptr;
			tail = nullptr;
			size = 0;
			return;
		}
		
		if (item == head) {
			head = head->next;
		}

		if (item == tail) {
			tail = tail->previous;
		}

		item->previous->next = item->next;
		item->next->previous = item->previous;

		if (head == nullptr) {
			head = tail;
		}
		if (tail == nullptr) {
			tail = head;
		}
		delete item;
		size--;
	}

	void displayInventory(){
		cout << "Inventory: \n";

		if (head == nullptr) { 
			return;
		}

		ItemNode* current = head;

		do {
			cout << current->itemName << " | ";
			current = current->next;
		} while (current != head);

		cout << "\n";
	}
};

struct bstNode {
	int data;
	bstNode* left;
	bstNode* right;

	bstNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class bst {
private:
	bstNode* root;
	
	bstNode* insert(bstNode* node, int val) {
		if (node == nullptr) {
			return new bstNode(val);
		}
		if (val < node->data) {
			node->left = insert(node->left, val);
		}
		else if (val > node->data) {
			node->right = insert(node->right, val);
		}

		return node;
	}

	int sumOfSubtree(bstNode* node) {
		if (node == nullptr) {
			return 0;
		}

		return node->data + sumOfSubtree(node->left) + sumOfSubtree(node->right);
	}


public:
	bst(): root(nullptr){}

	void insert(int val) {
		root = insert(root, val);

	}

	int sumOfLeft() {
		if (root == nullptr) {
			return 0;
		}

		return sumOfSubtree(root->left);
	}

	int sumOfRight() {
		if (root == nullptr) {
			return 0;
		}

		return sumOfSubtree(root->right);
	}
};

struct roomNode {
	int pos;
	vector<roomNode*> adjacentRooms;
	string name;

	roomNode(int position, string roomName = "") : pos(position), name(roomName) {}
};

class roomGraph {
private:
	map<int, roomNode*> adjacencyList;

	unordered_map<int, string> roomItems;

public:

	roomNode* getRoom(int roomPos, string name = "") {
		if (adjacencyList.count(roomPos) == 0) {
			adjacencyList[roomPos] = new roomNode(roomPos, name);
		}
		return adjacencyList[roomPos];
	}

	int getRoomPosition(roomNode* room) {
		return room->pos;
	}

	void addEdge(int pos1, int pos2) {
		roomNode* node1 = getRoom(pos1);
		roomNode* node2 = getRoom(pos2);
		node1->adjacentRooms.push_back(node2);
		node2->adjacentRooms.push_back(node1);
	}

	void printMap(){
		cout << "Map of the world: \n";
		for (auto& pair : adjacencyList) {
			roomNode* room = pair.second;
			cout << room->name << " is next to: ";

			for (int i = 0; i < room->adjacentRooms.size(); i++) {
				cout << room->adjacentRooms[i]->name << ", ";
			}
			cout << "Finished\n";
		}
	}

	void printAdjacencyNode(int val) {
		if (adjacencyList.count(val) == 0) {
			cout << "You dream of a room that is not real.\n";
			return;
		}

		roomNode* room = adjacencyList[val];

		cout << room->name << " is adjacent to; ";

		for (roomNode* adjacent : room->adjacentRooms) {
			cout << adjacent->name << ", ";
		}
		cout << "Finished\n";
	}

	void placeItem(const vector<string>& item) {
		int roomCount = adjacencyList.size();
		if (roomCount == 0) {
			return;
		}

		vector<int> roomIndexes;
		for (auto iterator = adjacencyList.begin(); iterator != adjacencyList.end(); ++iterator) {
			roomIndexes.push_back(iterator->first);
		}

		srand(time(nullptr));

		for (int i = 0; i < item.size(); i++) {

				string items = item[i];
				int indexBegin = rand() % roomCount;

				for (int j = 0; j < roomCount; j++) {

					int roomIndex = (indexBegin + j) % roomCount;
					int roomPosition = roomIndexes[roomIndex];

					if (roomPosition == 0) {
						continue;
					}

					if (roomItems.count(roomPosition) == 0) {
						roomItems[roomPosition] = items;
						cout << "Testing: " << items << " added to " << roomPosition << "\n";
						break;
					}
				}
		}
	}

	string getItem(int roomPosition) {
		if (roomItems.count(roomPosition)) {
			cout << "You found " << roomItems[roomPosition] << "!\n";
			string item = roomItems[roomPosition];
			roomItems.erase(roomPosition);
			return item;
		}
		cout << "nothing found!\n";
		return "Item not found!!!";
	}
};

bool battleSystem(inventoryList& playerInventory) {
	cout << "An enemy appeared! Press any key to roll the dice!\n";

	if (playerInventory.itemInList("Sword")) {
		cout << "You appear to possess a sword, would you like to use it to win? y/n";

		char playerChoice;
		cin >> playerChoice;

		if (playerChoice == 'y') {
			playerInventory.removeItem("Sword");
			cout << "You defeated the boss!";
			return true;
		}
		else if(playerChoice == 'n'){
			cout << "Very well, press any key to roll!!";
		}
	}
	char roll;
	cin >> roll;

	bst ROLLS;
	ROLLS.insert(4);
	srand(time(nullptr));

	for (int i = 0; i < 10; i++) {
		int num = (rand() % 6) + 1;
		ROLLS.insert(num);
	}

	int monsterRoll = ROLLS.sumOfLeft();
	int yourRoll = ROLLS.sumOfRight();

	cout << "Monster rolled: " << monsterRoll << "\n";
	cout << "You rolled: " << yourRoll << "\n";

	if (monsterRoll > yourRoll) {
		cout << "Oh no! You lost!";
		return false;
	}
	else if (yourRoll > monsterRoll) {
		cout << "You won!";
		return true;
	}
	else if (yourRoll == monsterRoll) {
		cout << "You and the monster are evenly matched! Out of respect, it decides to let you go!";
		return true;
	}
	return false;
}

class RoomMap {
private:
	stack<roomNode*> roomHistory;

public:
	void addRoom(roomNode* room) {
		roomHistory.push(room);
	}

	roomNode* goBack() {
		if (roomHistory.empty()) {
			cout << "You've reached the beginning!!";
			return nullptr;
		}

		roomNode* previous = roomHistory.top();
		roomHistory.pop();
		return previous;
	}

	roomNode* peek() {
		if (roomHistory.empty()) {
			return nullptr;
		}
		return roomHistory.top();
	}
};

int main() {
	cout << "Welcome to my game! When you are ready, press any button to continue!";
	
	string unused;
	cin >> unused;

	roomGraph rooms;
	RoomMap playerSteps;
	inventoryList playerInventory;
	rooms.getRoom(0, "The Beginning");
	rooms.getRoom(1, "Hallway");
	rooms.getRoom(2, "Bedroom");
	rooms.getRoom(3, "Office");
	rooms.getRoom(4, "Staircase");
	rooms.getRoom(5, "Kitchen");
	rooms.getRoom(6, "LivingRoom");

	rooms.addEdge(0, 1);
	rooms.addEdge(1, 2);
	rooms.addEdge(1, 3);
	rooms.addEdge(1, 4);
	rooms.addEdge(4, 5);
	rooms.addEdge(4, 6);
	rooms.addEdge(5, 6);
	//rooms.printMap();
	roomNode* currentRoom = rooms.getRoom(0);
	playerSteps.addRoom(currentRoom);
	vector<string> items = { "Sword", "Bandage", "Flashlight", "Paper Towel"};
	rooms.placeItem(items);
	//rooms.getItem(currentRoom->pos);

	cout << "You are in " << currentRoom->name << "\n";
	cout << "Where would you like to go? "; 
	rooms.printAdjacencyNode(0);
	string nextRoom;
	cin >> nextRoom;
	currentRoom = rooms.getRoom(1);
	if (nextRoom == "Hallway") {
		currentRoom = rooms.getRoom(1);
		playerSteps.addRoom(currentRoom);
		while (true) {

			if (currentRoom->name == "LivingRoom") {
				bool battle = battleSystem(playerInventory);

				if (battle == true) {
					cout << "\nYou have defeated the final boss (of the demo)! Thank you for playing!";
					break;
				}if (battle == false) {
					cout << "\nYou died, why did you do that man.";
					break;
				}
				
			}

			cout << "You are now in the " << currentRoom->name << "! " << "Press n to see adjacent rooms, i to check for items, b to go back a room, and u to open your inventory!\n";

			cin >> nextRoom;

			if (nextRoom == "i") {
				string item = rooms.getItem(currentRoom->pos);
				if (!(item == "Item not found!!!")) {
					cout << "There was a " << item << " lying on the floor! Added to inventory.\n";
					string itemName = item;
					playerInventory.collectItem(itemName);
				}
				continue;
			}else if (nextRoom == "b") {
				if (currentRoom->name == "Hallway") {
					cout << "You cannot go back to the beginning.\n";
					continue;
				}
				roomNode* previous = playerSteps.goBack();
				if (previous != nullptr) {
					currentRoom = previous;
					cout << "you went backwards!";
				}
				continue;
			}
			else if (nextRoom == "u") {
				playerInventory.displayInventory();
				continue;
			}
			else if (nextRoom == "n") {
				rooms.printAdjacencyNode(currentRoom->pos);

				cout << "Where would you like to go?";
				string moveRoom;
				cin >> moveRoom;

				roomNode* next = nullptr;
				for (int i = 0; i < currentRoom->adjacentRooms.size(); i++) {
					if (currentRoom->adjacentRooms[i]->name == moveRoom) {
						next = currentRoom->adjacentRooms[i];
						break;
					}
				}

				if (next != nullptr) {
					playerSteps.addRoom(currentRoom);
					currentRoom = next;
				}
				else {
					cout << "That room doesn't exist!";
				}
				continue;
			}

		}
	}
	else {
		cout << "You went nowhere and just kinda sat around for all eternity. The end.";
	}

	//battleSystem();
	return 0;
}