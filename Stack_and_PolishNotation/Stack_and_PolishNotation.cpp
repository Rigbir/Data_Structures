#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"
#define WHITE_TEXT "\033[1;37m"
#define PURPLE_TEXT "\033[1;35m"

int size = 0;

struct Node {
	long data;
	Node* next = nullptr;
};

Node* createStack() {
	return nullptr;
}

bool isEmpty(Node* top) {
	return top == nullptr;
}

bool isOperator(char symbol) {
	return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(');
}

bool isOperand(char symbol) {
	return ('a' <= symbol && symbol <= 'z');
}

bool isValue(char symbol) {
	return ('0' <= symbol && symbol <= '9');
}

bool onlyOperator(char symbol) {
	return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
}

void push(Node*& top, int value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = top;
	top = newNode;

	++size;
};

void pop(Node*& top) {
	if (isEmpty(top)) {
		std::cout << "Stack is Empty";
		std::cout << '\n';
		return;
	}

	Node* temp = top;
	top = top->next;
	delete temp;

	--size;
};

int peek(Node*& top) {
	return top->data;
}

int priority(char symbol) {
	switch (symbol) {
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': return 3;
	default: return 0;
	}
}

bool test(std::string& inputLine) {
	if (inputLine.empty()) {
		std::cout << "Invalid Input\n";
		return false;
	}

	char ch = ' ';

	for (auto symbol : inputLine) {
		if (symbol == ' ' || symbol == ')')
			continue;
		if (!isOperator(symbol) && !isOperand(symbol)) {
			std::cout << "Invalid Input\n";
			return false;
		}
		ch = symbol;
	}

	for (int i = 0; i <= inputLine.size(); ++i) {
		if (i == inputLine.size() && isOperator(ch)) {
			std::cout << "Invalid Input\n";
			return false;
		}
	}

	int count = 0;
	for (auto symbol : inputLine) {

		if (isOperator(symbol))
			++count;
		if (count == inputLine.size()) {
			std::cout << "Invalid Input\n";
			return false;
		}
	}

	int countFirst = 0;
	int countSecond = 0;
	for (auto symbol : inputLine) {
		if (symbol == '(')
			++countFirst;
		if (symbol == ')')
			++countSecond;
	}
	if ((countFirst != 0 || countSecond != 0) && (countFirst != countSecond)) {
		std::cout << "Invalid Input\n";
		return false;
	}

	std::string tempInput = "";
	for (char symbol : inputLine) {
		if (symbol != ' ') {
			tempInput += symbol;
		}
	}

	for (size_t i = 0; i < tempInput.size() - 1; ++i) {
		if (onlyOperator(tempInput[i]) && onlyOperator(tempInput[i + 1])) {
			std::cout << "Invalid Input\n";
			return false;
		}
	}

	return true;
}

void determinate(Node*& top, std::string& inputLine, std::string& outputLine) {
	std::istringstream iss(inputLine);
	std::string word;

	if (!test(inputLine))
		return;

	char current = ' ';
	char head = ' ';

	while (iss >> word) {
		for (auto symbol : word) {
			if (isOperator(symbol)) {

				current = symbol;
				if (!isEmpty(top))
					head = peek(top);

				if (isEmpty(top) || priority(head) < priority(current) || current == '(') {
					push(top, symbol);
				}
				else if (priority(head) >= priority(current)) {
					while (!isEmpty(top) && priority(head) >= priority(current)) {
						if (peek(top) != '(' || peek(top) != ')')
							outputLine += peek(top);
						pop(top);
						if (!isEmpty(top))
							head = peek(top);
					}
					push(top, symbol);
				}
			}
			else if (symbol == ')') {
				while (!isEmpty(top) && peek(top) != '(') {
					outputLine += peek(top);
					pop(top);
				}
				pop(top);
			}
			else {
				outputLine += symbol;
			}
		}
	}

	while (!isEmpty(top)) {
		outputLine += peek(top);
		pop(top);
	}
}

int calculateNotation(Node*& top, std::string& inputLine) {
	std::istringstream iss(inputLine);
	std::string word;

	while (iss >> word) {
		try {
			if (word == "+") {
				int second = peek(top);
				pop(top);
				int first = peek(top);
				pop(top);
				int result = first + second;
				push(top, result);
			}
			else if (word == "-") {
				int second = peek(top);
				pop(top);
				int first = peek(top);
				pop(top);
				int result = first - second;
				push(top, result);
			}
			else if (word == "*") {
				int second = peek(top);
				pop(top);
				int first = peek(top);
				pop(top);
				int result = first * second;
				push(top, result);
			}
			else if (word == "/") {
				int second = peek(top);
				pop(top);
				int first = peek(top);
				pop(top);
				if (second == 0) {
					throw std::runtime_error("Division by zero");
				}
				int result = first / second;
				push(top, result);
			}
			else {
				int data = std::stoi(word);
				push(top, data);
			}
		}
		catch (const std::invalid_argument& e) {
			std::cout << RED_TEXT << "Invalid input. Please enter a valid integer." << RESET_TEXT << std::endl;
		}
	}

	return peek(top);
}

void show(Node*& top) {
	if (isEmpty(top)) {
		std::cout << "Stack is Empty";
		std::cout << '\n';
		return;
	}

	Node* current = top;
	while (current != nullptr) {
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << '\n';
};

int main() {
	Node* stack = createStack();

	int userValue = 0;
	int data = 0;
	std::string inputLine = "";
	std::string outputLine;

	int choice = 0;

	std::cout << WHITE_TEXT << "Enter a number 1 - 2: " << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[1]" << RESET_TEXT << WHITE_TEXT << " Converting an expression to Polish notation" << '\n' << RESET_TEXT;
	std::cout << PURPLE_TEXT << "[2]" << RESET_TEXT << WHITE_TEXT << " Calculating Polish notation" << '\n' << RESET_TEXT;
	std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
	std::cin >> choice;
	std::cin.ignore();
	std::cout << '\n';

	std::string cont;
	do {
		switch (choice) {
		case 1: {
			std::cout << "Input your expression: ";
			std::getline(std::cin, inputLine);

			determinate(stack, inputLine, outputLine);

			std::cout << "OutputLine: " << outputLine << '\n' << '\n';

			inputLine = " ";

			std::cout << "You want calculate this expression?" << '\n';
			std::getline(std::cin, inputLine);

			if (inputLine == "y" || inputLine == "YES" || inputLine == "yes") {
				std::cout << "Enter values Notation with signs: ";
				std::string input;
				std::getline(std::cin, input);

				int result = calculateNotation(stack, input);

				std::cout << "Result: " << result << '\n';
			}
			else {
				continue;
			}

			while (!isEmpty(stack)) {
				pop(stack);
			}

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			std::cin.ignore();
			if (cont == "y" || cont == "yes" || cont == "Yes") {
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
			std::cout << "Input your expression: ";
			std::getline(std::cin, inputLine);

			int result = calculateNotation(stack, inputLine);

			std::cout << "Result: " << result << '\n';

			while (!isEmpty(stack)) {
				pop(stack);
			}

			std::cout << WHITE_TEXT << "You want continue?" << '\n' << RESET_TEXT;
			std::cin >> cont;
			if (cont == "y" || cont == "yes" || cont == "Yes") {
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
	} while (cont == "y" || cont == "yes" || cont == "Yes");

	return 0;
}