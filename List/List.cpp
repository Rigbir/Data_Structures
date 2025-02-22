#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <ctime> 

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

#define WHITE_TEXT "\033[1;37m"
#define PURPLE_TEXT "\033[1;35m"

struct Node {
	int data;
	Node* next = nullptr;
	Node* prev = nullptr;
};

Node* createNode(int value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = nullptr;
	newNode->prev = nullptr;
	return newNode;
}

void appened(Node*& head, int value) {
	if (head == nullptr) {
		head = createNode(value);
		return;
	}

	Node* newNode = createNode(value);

	Node* current = head;

	while (current->next != nullptr) {
		current = current->next;
	}

	current->next = newNode;
	newNode->prev = current;
}

void reverseShow(Node*& head) {
	if (head != nullptr) {
		Node* current = head;
		while (current->next != nullptr){
			current = current->next;
		}

		Node* temp = current;
		while (temp->prev != nullptr) {
			std::cout << temp->data << " ";
			temp = temp->prev;
		}
		std::cout << temp->data << " ";
	}
	else {
		std::cout << RED_TEXT << "The list is empty" << RESET_TEXT;
	}
}

void insertValue(Node*& head, int userInsValue, int userInsFirst, int userInsSecond, int choiceForFunction) {
	if (head == nullptr) {
		std::cout << RED_TEXT << "The list is empty" << RESET_TEXT;
		return;
	}

	Node* current = head;
	Node* firstNode = nullptr;
	Node* secondNode = nullptr;

	switch (choiceForFunction) {
	case 1: {
		std::cout << WHITE_TEXT << "Your value: " << RESET_TEXT;
		std::cin >> userInsValue;

		Node* newNode = createNode(userInsValue);
		newNode->next = head;
		newNode->prev = nullptr;
		head->prev = newNode;
		head = newNode;

		break;
	}
	case 2: {
		std::cout << WHITE_TEXT << "First Value: " << RESET_TEXT;
		std::cin >> userInsFirst;
		std::cout << WHITE_TEXT << "Second Value: " << RESET_TEXT;
		std::cin >> userInsSecond;
		std::cout << WHITE_TEXT << "Your value: " << RESET_TEXT;
		std::cin >> userInsValue;

		if (userInsFirst < 0 || userInsSecond < 0) {
			std::cout << RED_TEXT << "Invalid input" << RESET_TEXT;
			return;
		}

		Node* newNode = createNode(userInsValue);

		while (current != nullptr) {
			if (current->data == userInsFirst)
				firstNode = current;
			if (current->data == userInsSecond)
				secondNode = current;
			current = current->next;
		}

		Node* firstNext = firstNode->next;
		Node* firstPrev = firstNode->prev;
		Node* secondNext = secondNode->next;
		Node* secondPrev = secondNode->prev;

		if (firstNode->prev != nullptr && secondNode->next != nullptr) {
			newNode->next = secondNode;
			newNode->prev = firstNode;

			secondNode->prev = newNode;
			firstNode->next = newNode;
		}
		break;
	}
	case 3: {
		std::cout << WHITE_TEXT << "Your value: " << RESET_TEXT;
		std::cin >> userInsValue;

		Node* newNode = createNode(userInsValue);

		while (current->next != nullptr) {
			current = current->next;
		}

		if (current->next == nullptr) {
			current->next = newNode;
			newNode->prev = current;
			newNode->next = nullptr;
		}

		break;
	}
	case 4: {
		std::cout << WHITE_TEXT << "Your value: " << RESET_TEXT;
		std::cin >> userInsValue;

		Node* newNode = createNode(userInsValue);

		newNode->next = head->next;
		newNode->prev = head;
		head->next = newNode;
		head->next->prev = newNode;

		break;
	}
	case 5: {
		std::cout << WHITE_TEXT << "Your value: " << RESET_TEXT;
		std::cin >> userInsValue;

		Node* newNode = createNode(userInsValue);

		while (current->next != nullptr) {
			current = current->next;
		}

		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;

		break;
	}
	}
}

void delValue(Node*& head, int userDelValue) {
	if (head == nullptr) {
		std::cout << RED_TEXT << "The list is empty" << RESET_TEXT;
		return;
	}

	if (head->data == userDelValue) {
		Node* temp = head;
		head = head->next;
		if (head != nullptr)
			head->prev = nullptr;
		delete temp;
		std::cout << WHITE_TEXT << "List item deleted" << RESET_TEXT;
		return;
	}

	Node* current = head;

	while (current != nullptr) {
		if (current->data == userDelValue) {
			Node* temp = current;
			current->prev->next = current->next;
			if (current->next != nullptr)
				current->next->prev = current->prev;
			current = current->next;
			delete temp;
			std::cout << WHITE_TEXT << "List item deleted" << RESET_TEXT;
			return;
		}
		else {
			current = current->next;
		}
	}

	std::cout << RED_TEXT << "List item not found" << RESET_TEXT;
}

void delIndex(Node*& head, int userDelIndex) {
	if (head == nullptr) {
		std::cout << RED_TEXT << "The list is empty" << RESET_TEXT;
		return;
	}

	int countIndex = 0;
	
	if (countIndex == userDelIndex) {
		Node* temp = head;
		head = head->next;
		if (head != nullptr) {
			head->prev = nullptr;
		}
		delete temp;
		std::cout << WHITE_TEXT << "List item deleted" << RESET_TEXT;
		return;
	}

	Node* current = head;

	while (current != nullptr) {
		if (countIndex == userDelIndex) {
			Node* temp = current;
			current->prev->next = current->next;
			if (current->next != nullptr) 
				current->next->prev = current->prev;
			current = current->next;
			delete temp;
			std::cout << WHITE_TEXT << "List item deleted" << RESET_TEXT;
			return;
		}
		else {
			++countIndex;
			current = current->next;
		}
	}
}

void gettingValue(Node*& head, int userGetValue) {
	Node* current = head;

	while (current != nullptr && current->data != userGetValue) {
		current = current->next;
	}

	if (current != nullptr) {
		std::cout << current->data;
	}
	else {
		std::cout << RED_TEXT << "Node with an index " << RESET_TEXT << userGetValue << RED_TEXT << " not found\n" << RESET_TEXT;
		return;
	}
}

void gettingIndex(Node*& head, int userGetIndex) {
	Node* current = head;
	int countIndex = 0;

	while (current != nullptr && countIndex < userGetIndex) {
		current = current->next;
		++countIndex;
	}

	if (current != nullptr) {
		std::cout << current->data;
	}
	else {
		std::cout << RED_TEXT << "Node with an index " << RESET_TEXT << userGetIndex << RED_TEXT << " not found\n" << RESET_TEXT;
		return;
	}
}

void shakerSort(Node*& head) {
	bool sort_or_not = false;
	Node* current = head;
	Node* next = nullptr;
	Node* tempHead = head;

	int countSize = 0;

	while (current != nullptr) {
		++countSize;
		current = current->next;
	}

	current = head;

	do {
		sort_or_not = false;

		for (int count = 0; count <= countSize; ++count) {
			if (current != nullptr && current->next != nullptr) {
				if (current->data > current->next->data) {
					int temp = current->data;
					current->data = current->next->data;
					current->next->data = temp;
					sort_or_not = true;
				}
			}
			if (current == nullptr)
				break;
			current = current->next;
		}

		if (!sort_or_not)
			break;

		current = head;
		while (current->next != nullptr) {
			current = current->next;
		}

		for (int count = countSize; count > 0; --count) {
			if (current != nullptr && current->prev != nullptr) {
				if (current->data < current->prev->data) {
					int temp = current->data;
					current->data = current->prev->data;
					current->prev->data = temp;
					sort_or_not = true;
				}
			}
			if (current == nullptr)
				break;
			current = current->prev;
		}

		current = head;

	} while (sort_or_not);
}

void swapValue(Node*& head, int firstUser, int secondUser) {
	if (head == nullptr) {
		std::cout << RED_TEXT << "The list is empty" << RESET_TEXT;
		return;
	}

	if (firstUser < 0 || secondUser < 0) {
		std::cout << RED_TEXT << "Invalid input" << RESET_TEXT;
		return;
	}

	Node* current = head;
	Node* firstNode = nullptr;
	Node* secondNode = nullptr;

	while (current != nullptr) {
		if (current->data == firstUser)
			firstNode = current;
		if (current->data == secondUser)
			secondNode = current;
		current = current->next;
	}

	if (firstNode == nullptr || secondNode == nullptr) {
		std::cout << RED_TEXT << "List item not found" << RESET_TEXT;
		return;
	}

	if (firstNode->next == secondNode || secondNode->next == firstNode) {
		if (firstNode->next == secondNode) {
			firstNode->next = secondNode->next;
			secondNode->prev = firstNode->prev;
			firstNode->prev = secondNode;
			secondNode->next = firstNode;
		}
		else {
			secondNode->next = firstNode->next;
			firstNode->prev = secondNode->prev;
			secondNode->prev = firstNode;
			firstNode->next = secondNode;
		}

		if (firstNode->prev != nullptr) {
			firstNode->prev->next = firstNode;
		}
		if (firstNode->next != nullptr) {
			firstNode->next->prev = firstNode;
		}
		if (secondNode->prev != nullptr) {
			secondNode->prev->next = secondNode;
		}
		if (secondNode->next != nullptr) {
			secondNode->next->prev = secondNode;
		}

		if (firstNode == head)
			head = secondNode;
		else if (secondNode == head)
			head = firstNode;

		return;
	}

	Node* firstNext = firstNode->next;
	Node* firstPrev = firstNode->prev;
	Node* secondNext = secondNode->next;
	Node* secondPrev = secondNode->prev;

	if ((secondNode->next != nullptr && secondNode->prev != nullptr) && (firstNode->next != nullptr && firstNode->prev != nullptr)) {
		if (firstNode == head)
			head = secondNode;
		else if (secondNode == head)
			head = firstNode;

		secondNode->next = firstNext;
		secondNode->prev = firstPrev;
		firstNode->next = secondNext;
		firstNode->prev = secondPrev;

		if (firstPrev != nullptr) {
			firstPrev->next = secondNode;
		}
		if (firstNext != nullptr) {
			firstNext->prev = secondNode;
		}
		if (secondPrev != nullptr) {
			secondPrev->next = firstNode;
		}
		if (secondNext != nullptr) {
			secondNext->prev = firstNode;
		}
	}

	if ((firstNode->prev == nullptr && secondNode->next == nullptr) || (secondNode->prev == nullptr && firstNode->next == nullptr)) {

		if (firstNode == head) {
			head = secondNode;
		}

		secondNode->next = firstNext;
		secondNode->prev = firstPrev;
		firstNode->next = secondNext;
		firstNode->prev = secondPrev;

		if (firstNext != nullptr) {
			firstNext->prev = secondNode;
		}
		if (secondPrev != nullptr) {
			secondPrev->next = firstNode;
		}
	}

	if ((firstNode->next != nullptr && secondNode->next == nullptr) || (firstNode->prev == nullptr && secondNode->next != nullptr)) {
		if (secondNode->next == nullptr) {
			firstNode->next = nullptr;
			firstNode->prev = secondPrev;
			secondNode->next = firstNext;
			secondNode->prev = firstPrev;

			if (firstNext != nullptr)
				firstNext->prev = secondNode;
			if (firstPrev != nullptr)
				firstPrev->next = secondNode;
			if (secondPrev != nullptr)
				secondPrev->next = firstNode;
		}
		
		if (firstNode->prev == nullptr) {
			head = secondNode;

			secondNode->prev = nullptr;
			secondNode->next = firstNext;
			firstNode->next = secondNext;
			firstNode->prev = secondPrev;

			if (secondNext != nullptr)
				secondNext->prev = firstNode;
			if (secondPrev != nullptr)
				secondPrev->next = firstNode;
			if (firstNext != nullptr)
				firstNext->prev = secondNode;
		}
	}
}

void show(Node*& head) {
	if (head != nullptr) {
		Node* current = head;
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
	}
	else {
		std::cout << RED_TEXT << "List is empty." << RESET_TEXT;
	}
}

void del(Node*& head) {
	if (head == nullptr) {
		return;
	}
	else {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
}

int main() {
	Node* List = nullptr;

	int size = 0;
	int value = 0;
	int userInsValue = 0;
	int userInsFirst = 0;
	int userInsSecond = 0;
	int userDelValue = 0;
	int userDelIndex = 0;
	int userGetValue = 0;
	int userGetIndex = 0;
	int firstUser = 0;
	int secondUser = 0;
	int numberOfRandomElement = 0;

	int choice = 0;

	std::cout << WHITE_TEXT << "Enter a number 1 - 12: " << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[1]" << RESET_TEXT << WHITE_TEXT << " Random List completion" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[2]" << RESET_TEXT << WHITE_TEXT << " Filling in the list manually" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[3]" << RESET_TEXT << WHITE_TEXT << " Reverse List" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[4]" << RESET_TEXT << WHITE_TEXT << " Insert in List" << '\n' << RESET_TEXT; 
	std::cout << PURPLE_TEXT << "[5]" << RESET_TEXT << WHITE_TEXT << " Delete element by Value" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[6]" << RESET_TEXT << WHITE_TEXT << " Delete element by Index" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[7]" << RESET_TEXT << WHITE_TEXT << " Swap value" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[8]" << RESET_TEXT << WHITE_TEXT << " Getting an element by Value" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[9]" << RESET_TEXT << WHITE_TEXT << " Getting an element by Index" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[10]" << RESET_TEXT << WHITE_TEXT << " Sort List" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[11]" << RESET_TEXT << WHITE_TEXT << " Show all List" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[12]" << RESET_TEXT << WHITE_TEXT << " Delete all List" << '\n' << RESET_TEXT;
	std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
	std::cin >> choice;
	std::cout << '\n';

	std::string cont;
	do {
		switch (choice) {
		case 1: {
			std::cout << WHITE_TEXT "Random element from Number: " << RESET_TEXT;
			std::cin >> numberOfRandomElement;
			srand(time(NULL));
			int N = 100;

			auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < numberOfRandomElement; ++i) {
				appened(List, rand() % N);
			}

			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double> duration = start - end;

			std::cout << '\n';
			show(List);
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "Time created List: " << RESET_TEXT << duration.count() << WHITE_TEXT << " second" << '\n' << RESET_TEXT;
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 2: {
			std::string input;
			std::getline(std::cin, input);
			int value = 0;
			int count = 0;

			while (true) {
				std::cout << WHITE_TEXT << "Enter value: " << RESET_TEXT;
				std::getline(std::cin, input);

				if (input.empty()) {
					break;
				}

				try {
					int data = std::stoi(input);
					appened(List, data);
					++count;
				}
				catch (const std::invalid_argument&) {
					std::cerr << RED_TEXT << "Error: input an integer \n" << RESET_TEXT;
				}
				catch (const std::out_of_range&) {
					std::cerr << RED_TEXT << "Error: your number is too large \n" << RESET_TEXT;
				}
			}

			std::cout << '\n';
			show(List);
			std::cout << '\n';
			std::cout << WHITE_TEXT << "The size of your List: " << count << RESET_TEXT;
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 3: {
			std::cout << WHITE_TEXT << "Your List: " << RESET_TEXT;
			show(List);
			std::cout << '\n';
			std::cout << '\n';
			std::cout << WHITE_TEXT << "Reverse List: " << RESET_TEXT;
			reverseShow(List);
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 4: {
			std::cout << WHITE_TEXT << "List: " << RESET_TEXT;
			show(List);

			std::cout << '\n';
			std::cout << '\n';

			int choiceForFunction = 0;
			std::cout << WHITE_TEXT << "Enter a number 1 - 3: " << '\n' << RESET_TEXT;
			std::cout << PURPLE_TEXT << "[1]" << RESET_TEXT << WHITE_TEXT << " Head of the list" << '\n' << RESET_TEXT;
			std::cout << PURPLE_TEXT << "[2]" << RESET_TEXT << WHITE_TEXT << " Middle of the list" << '\n' << RESET_TEXT;
			std::cout << PURPLE_TEXT << "[3]" << RESET_TEXT << WHITE_TEXT << " Final of the list" << '\n' << RESET_TEXT;
			std::cout << PURPLE_TEXT << "[4]" << RESET_TEXT << WHITE_TEXT << " Head and Next" << '\n' << RESET_TEXT;
			std::cout << PURPLE_TEXT << "[5]" << RESET_TEXT << WHITE_TEXT << " Final and Prev" << '\n' << RESET_TEXT;
			std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
			std::cin >> choiceForFunction;
			std::cout << '\n';

			insertValue(List, userInsValue, userInsFirst, userInsSecond, choiceForFunction);
			std::cout << '\n';

			std::cout << WHITE_TEXT << "List: " << RESET_TEXT;
			show(List);
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 5: {
			std::cout << WHITE_TEXT << "Enter Deleted value: " << RESET_TEXT;
			std::cin >> userDelValue;

			delValue(List, userDelValue);
			std::cout << '\n';
			show(List);
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 6: {
			std::cout << WHITE_TEXT << "Enter Deleted Index: " << RESET_TEXT;
			std::cin >> userDelIndex;

			delIndex(List, userDelIndex);
			std::cout << '\n';
			show(List);
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 7: {
			std::cout << WHITE_TEXT << "List: " << RESET_TEXT;
			show(List);

			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "First Value: " << RESET_TEXT;
			std::cin >> firstUser;
			std::cout << WHITE_TEXT << "Second Value: " << RESET_TEXT;
			std::cin >> secondUser;

			swapValue(List, firstUser, secondUser);
			std::cout << '\n';

			std::cout << WHITE_TEXT << "List: " << RESET_TEXT;
			show(List);
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 8: {
			std::cout << WHITE_TEXT << "Enter Value an element: " << RESET_TEXT;
			std::cin >> userGetValue;

			gettingValue(List, userGetValue);
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 9: {
			std::cout << WHITE_TEXT << "Enter Index an element: " << RESET_TEXT;
			std::cin >> userGetIndex;

			gettingIndex(List, userGetIndex);
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 10: {
			std::cout << WHITE_TEXT << "List: " << RESET_TEXT;
			show(List);
			std::cout << '\n';
			std::cout << '\n';
			std::cout << WHITE_TEXT << "Shaker Sorted: " << RESET_TEXT;
			shakerSort(List);
			std::cout << '\n';
			std::cout << '\n';
			std::cout << WHITE_TEXT << "List: " << RESET_TEXT;
			show(List);
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 11: {
			show(List);
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		case 12: {
			del(List);
			std::cout << WHITE_TEXT << "Your List was deleted" << RESET_TEXT;
			std::cout << '\n';
			std::cout << '\n';

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "Yes" || cont == "yes" || cont == "y") {
				std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
				std::cin >> choice;
				std::cout << '\n';
			}
			else {
				break;
			}

			break;
		}
		}
	} while (cont == "Yes" || cont == "yes" || cont == "y");

	del(List);

	return 0;
}