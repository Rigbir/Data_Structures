#include <iostream>
#include <stack>
#include <queue>
#include <chrono>
#include <string>
#include <random>

#define RED_TEXT "\033[1;31m"
#define WHITE_TEXT "\033[1;37m"
#define PURPLE_TEXT "\033[1;35m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT "\033[1;34m"

#define RESET_TEXT "\033[0m"

struct Node {
	int data;
	Node* left;
	Node* right;
};

Node* TreeCreate(int value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

void add(Node*& root, int value) {
	if (root == nullptr) {
		root = TreeCreate(value);
	}
	else if (value < root->data) {
		add(root->left, value);
	}
	else {
		add(root->right, value);
	}
}

Node* findMin(Node*& root) {
	while (root->left != nullptr) {
		root = root->left;
	}
	return root;
}

Node* remove(Node*& root, int value) {
	if (root == nullptr)
		return root;

	if (value < root->data) {
		root->left = remove(root->left, value);
	}
	else if (value > root->data) {
		root->right = remove(root->right, value);
	}
	else {

		//No child or one child
		if (root->left == nullptr) {
			Node* temp = root->right;
			delete root;
			return temp;
		}
		if (root->right == nullptr) {
			Node* temp = root->left;
			delete root;
			return temp;
		}

		//Root have 2 child
		Node* temp = findMin(root->right);
		
		root->data = temp->data;

		root->right = remove(root->right, temp->data);
	}
	return root;
}

void DFS(Node*& root) {
	if (root == nullptr) 
		return;
	
	auto start_time = std::chrono::steady_clock::now();
	std::stack<Node*> stack;
	stack.push(root);

	while (!stack.empty()) {
		Node* current = stack.top();
		stack.pop();

		std::cout << WHITE_TEXT << current->data << " " << RESET_TEXT;

		if (current->right != nullptr)
			stack.push(current->right);
		if (current->left != nullptr)
			stack.push(current->left);
	}
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	std::cout << YELLOW_TEXT << "--> " << elapsed_ns.count() << " ns\n" << RESET_TEXT;
}

void BFS(Node*& root) {
	if (root == nullptr)
		return;

	auto start_time = std::chrono::steady_clock::now();
	std::deque<Node*> queue;
	queue.push_back(root);

	while (!queue.empty()) {
		Node* current = queue.front();
		queue.pop_front();

		std::cout << WHITE_TEXT << current->data << " " << RESET_TEXT;

		if (current->left != nullptr) {
			queue.push_back(current->left);
		}
		if (current->right != nullptr) {
			queue.push_back(current->right);
		}
	}
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	std::cout << YELLOW_TEXT << "--> " << elapsed_ns.count() << " ns\n" << RESET_TEXT;
}

void printTree(const std::string& prefix, const Node* node, bool isLeft) {
	if (node != nullptr) {
		std::cout << YELLOW_TEXT << prefix << RESET_TEXT;
		std::cout << YELLOW_TEXT << (isLeft ? "|--" : "|__") << RESET_TEXT;
		std::cout << BLUE_TEXT << node->data << RESET_TEXT << std::endl;

		printTree(prefix + (isLeft ? "|   " : "    "), node->left, true);
		printTree(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}

void printTree(const Node* node) {
	printTree("", node, false);
}

void directOrder(Node*& root) {
	if (root != nullptr) {
		std::cout << WHITE_TEXT << root->data << " " << RESET_TEXT;
		directOrder(root->left);
		directOrder(root->right);
	}
}

void symmetricalOrder(Node*& root) {
	if (root != nullptr) {
		symmetricalOrder(root->left);
		std::cout << WHITE_TEXT << root->data << " " << RESET_TEXT;
		symmetricalOrder(root->right);
	}
}

void reverseOrder(Node*& root) {
	if (root != nullptr) {
		reverseOrder(root->left);
		reverseOrder(root->right);
		std::cout << WHITE_TEXT << root->data << " " << RESET_TEXT;
	}
}

void deleteTree(Node*& root) {
	if (root != nullptr) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
		root = nullptr;
	}
}

int main() {
	Node* Tree = nullptr;
	int value = 0;
	int numberOfRandomElement = 0;

	int choice = 0;

	std::cout << WHITE_TEXT << "Enter a number 1 - 10: " << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[1]" << RESET_TEXT << WHITE_TEXT << " Random Tree completion" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[2]" << RESET_TEXT << WHITE_TEXT << " Filling in the Tree manually" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[3]" << RESET_TEXT << WHITE_TEXT << " DFS (Depth-first search)" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[4]" << RESET_TEXT << WHITE_TEXT << " BFS (Breadth-first search)" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[5]" << RESET_TEXT << WHITE_TEXT << " Direct Order" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[6]" << RESET_TEXT << WHITE_TEXT << " Symmetrical Order" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[7]" << RESET_TEXT << WHITE_TEXT << " Reverse Order" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[8]" << RESET_TEXT << WHITE_TEXT << " Delete Element" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[9]" << RESET_TEXT << WHITE_TEXT << " Print Tree" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[10]" << RESET_TEXT << WHITE_TEXT << " Delete Tree" << '\n' << RESET_TEXT;
	std::cout << WHITE_TEXT << "\nYour choice: " << RESET_TEXT;
	std::cin >> choice;
	std::cout << '\n';

	std::string cont;
	do {
		switch (choice) {
		case 1: {
			std::cout << WHITE_TEXT "The number of Random elements: " << RESET_TEXT;
			std::cin >> numberOfRandomElement;

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(-99, 99);
			
			for (int i = 0; i < numberOfRandomElement; ++i) {
				int randomElement = dis(gen);
				add(Tree, randomElement);
			}

			std::cout << WHITE_TEXT << "\nYour Tree: \n" << RESET_TEXT;
			symmetricalOrder(Tree);

			std::cout << WHITE_TEXT << "\n\nYou want continue?\n" << RESET_TEXT;
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
			std::string inputElement;
			std::getline(std::cin, inputElement);
			bool flag = true;
			int count = 0;

			while (flag) {
				std::cout << WHITE_TEXT << "Enter value: " << RESET_TEXT;
				std::getline(std::cin, inputElement);

				if (inputElement.empty())
					break;

				try {
					int data = std::stoi(inputElement);
					add(Tree, data);
					++count;
				}
				catch (const std::invalid_argument&) {
					std::cerr << RED_TEXT << "Error: input an integer \n" << RESET_TEXT;
				}
				catch (const std::out_of_range&) {
					std::cerr << RED_TEXT << "Error: your number is too large \n" << RESET_TEXT;
				}
			}

			std::cout << WHITE_TEXT << "\nYour Tree: \n" << RESET_TEXT;
			symmetricalOrder(Tree);
			std::cout << WHITE_TEXT << "\nCount your Elements: " << count  << '\n' << RESET_TEXT;

			std::cout << WHITE_TEXT << "\nYou want continue?\n" << RESET_TEXT;
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
			std::cout << WHITE_TEXT << "DFS traversal: " << RESET_TEXT;
			DFS(Tree);

			std::cout << WHITE_TEXT << "\nYou want continue?\n" << RESET_TEXT;
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
			std::cout << WHITE_TEXT << "BFS traversal: " << RESET_TEXT;
			BFS(Tree);

			std::cout << WHITE_TEXT << "\nYou want continue?\n" << RESET_TEXT;
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
			std::cout << WHITE_TEXT << "Tree: " << RESET_TEXT;
			directOrder(Tree);

			std::cout << WHITE_TEXT << "\n\nYou want continue?\n" << RESET_TEXT;
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
			std::cout << WHITE_TEXT << "Tree: " << RESET_TEXT;
			symmetricalOrder(Tree);

			std::cout << WHITE_TEXT << "\n\nYou want continue?\n" << RESET_TEXT;
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
			std::cout << WHITE_TEXT << "Tree: " << RESET_TEXT;
			reverseOrder(Tree);
			
			std::cout << WHITE_TEXT << "\n\nYou want continue?\n" << RESET_TEXT;
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
			std::cout << WHITE_TEXT << "Enter value for remove: " << RESET_TEXT;
			std::cin >> value;
			remove(Tree, value);

			std::cout << WHITE_TEXT << "\nYour Tree: \n" << RESET_TEXT;
			symmetricalOrder(Tree);

			std::cout << WHITE_TEXT << "\n\nYou want continue?\n" << RESET_TEXT;
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
			std::cout << WHITE_TEXT << "\nYour Tree: \n '--' it's left, '__' it's right \n" << RESET_TEXT;
			printTree(Tree); 

			std::cout << WHITE_TEXT << "\nYou want continue?\n" << RESET_TEXT;
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
			deleteTree(Tree);
			std::cout << WHITE_TEXT << "Tree deleted\n" << RESET_TEXT;

			std::cout << WHITE_TEXT << "\nYou want continue?\n" << RESET_TEXT;
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
	} while (cont == "yes" || cont == "YES" || cont == "y");

	return 0;
}