#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <sstream>

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

#define WHITE_TEXT "\033[1;37m"
#define PURPLE_TEXT "\033[1;35m"

struct Student {
    std::string FIO;
    std::string gender;
    int group;
    int self_number;
    int marks[8];
};

const int MAX_STUDENTS = 40;

void inputInFile(std::string& path, int num_students, Student student[]) {
    std::ofstream File(path, std::ios::app);

    if (!File.is_open()) {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }
    else {
        File << std::fixed;
        File.precision(2);

        for (int i = 0; i < num_students; ++i) {
            std::cout << "Enter information about student: " << i + 1 << std::endl;
            std::cin.ignore();
            std::cout << std::endl;
            std::cout << "FIO: ";
            std::getline(std::cin, student[i].FIO);
            std::cout << "Gender: ";
            std::cin >> student[i].gender;
            std::cout << "Group: ";
            std::cin >> student[i].group;
            std::cout << "Self number: ";
            std::cin >> student[i].self_number;
            std::cin.ignore();
            std::cout << "Marks: ";
            for (int j = 0; j < 8; ++j) {
                std::cin >> student[i].marks[j];
            }

            File << "FIO: " << student[i].FIO << std::endl;
            File << "Gender: " << student[i].gender << std::endl;
            File << "Group: " << student[i].group << std::endl;
            File << "SelfNumber: " << student[i].self_number << std::endl;
            File << "Marks: ";
            for (int j = 0; j < 8; ++j) {
                File << student[i].marks[j] << " ";
            }
            File << std::endl;
            File << std::endl;
            std::cout << std::endl;
        }
    }
    File.close();
}

int CountStudents(std::string& path) {
    std::ifstream File(path);
    if (File.is_open()) {
        int temp = 0;
        std::string data;
        while (!File.eof()) {
            std::getline(File, data);
            temp++;
        }
        File.close();
        int n;
        n = temp / 5;
        return n;
    }
    else return 0;
}

void readAllFile(std::string& path, Student student[]) {
    std::ifstream File(path);

    if (!File.is_open()) {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }
    else {
        int temp;
        temp = CountStudents(path);
        if (temp == 0)
            std::cout << "The File is empty";
        else {
            std::string data;
            while (!File.eof()) {
                std::getline(File, data);
                std::cout << data << '\n';
            }
        }
        File.close();
    }
}

void changeInformation(std::string& path, Student student[]) {
    std::ifstream File(path);
    std::vector<std::string> lines;

    std::string replaceThis;
    std::string replaceWith;

    std::cout << "Enter the replacement word: ";
    std::getline(std::cin >> std::ws, replaceThis);
    std::cout << '\n';
    std::cout << "Enter the word to replace: ";
    std::getline(std::cin >> std::ws, replaceWith);

    if (!File.is_open()) {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }
    else {
        std::string line;

        while (std::getline(File, line)) {
            std::istringstream iss(line);
            std::string word;
            std::string modernLine;

            while (iss >> word) {
                if (word == replaceThis) {
                    word = replaceWith;
                }
                modernLine += word + " ";
            }
            lines.push_back(modernLine);
        }
        File.close();
    }

    std::ofstream OutputFile(path);
    if (!OutputFile.is_open()) {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }

    for (const auto& l : lines) {
        OutputFile << l << "\n";
    }
    OutputFile.close();
}

void readStudentOfGroup(std::string& path, std::string number_group, Student student[]) {
    std::ifstream File(path, std::ios::in);

    if (!File.is_open()) {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }
    else {
        std::vector<std::string> appol;
        std::string line;
        std::string n = "Group: ";
        int size = 0;

        while (std::getline(File, line)) {
            std::istringstream iss(line);

            appol.push_back(line);

            if (line == "") {
                appol.clear();
            }
            else if (appol.size() == 5) {
                if (appol[2] == (n + number_group)) {
                    for (const auto& c : appol) {
                        std::cout << c << '\n';
                    }
                    std::cout << '\n';
                    size++;
                }
            }
        }

        if (size == 0) {
            std::cout << RED_TEXT << "No records were found" << RESET_TEXT << '\n';
        }
    }
}

void topScore(std::string& path, Student student[]) {
    std::ifstream File(path);

    if (!File.is_open()) {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }
    else {
        int mark;
        int size = 0;
        std::string temp;
        std::string line;
        std::vector<int> marks;
        std::vector<std::string> appol;

        while (std::getline(File, line)) {
            std::istringstream iss(line);

            appol.push_back(line);

            if (line == "") {
                appol.clear();
            }
            else {
                if (appol.size() == 5) {
                    iss >> temp;

                    while (iss >> mark) {
                        marks.push_back(mark);
                    }

                    int sum = 0;
                    for (const auto& c : marks) {
                        sum += c;
                    }

                    if ((sum / 8) == 5) {
                        for (const auto& c : appol) {
                            std::cout << c << '\n';
                        }
                        std::cout << '\n';
                    }
                    marks.clear();
                    size++;
                }
            }
        }

        if (size == 0) {
            std::cerr << RED_TEXT << "No records were found" << RESET_TEXT << '\n';
            std::cout << '\n';
        }
    }
}

void genderStatistic(std::string& path, Student student[]) {
    std::ifstream File(path);

    int count_m = 0;
    int count_w = 0;

    std::string line;
    std::string word_m = "male";
    std::string word_w = "female";

    if (File.is_open()) {
        while (std::getline(File, line)) {
            std::istringstream iss(line);
            std::string word;

            while (iss >> word) {
                std::string cleanedWord;
                for (char c : word) {
                    if (std::isalpha(c)) {
                        cleanedWord += std::tolower(c);
                    }
                }

                if (cleanedWord == word_m) {
                    count_m++;
                }
                else if (cleanedWord == word_w) {
                    count_w++;
                }
            }
        }

        std::cout << "male: " << count_m << '\n';
        std::cout << "female: " << count_w << '\n';
    }
    else {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }
}

void goodScore(std::string& path, Student student[]) {
    std::ifstream File(path);

    if (!File.is_open()) {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }
    else {
        int mark;
        int size = 0;
        std::string temp;
        std::string line;
        std::vector<int> marks;
        std::vector<std::string> appol;

        while (std::getline(File, line)) {
            std::istringstream iss(line);

            appol.push_back(line);

            if (line == "") {
                appol.clear();
            }
            else {
                if (appol.size() == 5) {
                    iss >> temp;

                    while (iss >> mark) {
                        marks.push_back(mark);
                    }

                    int sum = 0;
                    for (const auto& c : marks) {
                        sum += c;
                    }

                    if ((sum / 8) < 5 && (sum / 8) >= 4) {
                        for (const auto& c : appol) {
                            std::cout << c << '\n';
                        }
                        std::cout << '\n';
                    }
                    marks.clear();
                    size++;
                }
            }
        }

        if (size == 0) {
            std::cerr << RED_TEXT << "No records were found" << RESET_TEXT << '\n';
            std::cout << '\n';
        }
    }
}

void readStudentOfNumber(std::string& path, std::string self_number_in, Student student[]) {
    std::ifstream File(path, std::ios::in);

    if (!File.is_open()) {
        std::cerr << RED_TEXT << "File don't open" << RESET_TEXT;
    }
    else {
        std::vector<std::string> appol;
        std::string line;
        std::string n = "SelfNumber: ";
        int size = 0;

        while (std::getline(File, line)) {
            std::istringstream iss(line);
            std::string word;

            appol.push_back(line);

            if (line == "") {
                appol.clear();
            }
            else if (appol.size() == 5) {
                if (appol[3] == (n + self_number_in)) {
                    for (const auto& c : appol) {
                        std::cout << c << '\n';
                    }
                    std::cout << '\n';
                    size++;
                }
            }
        }

        if (size == 0) {
            std::cout << RED_TEXT << "No records were found" << RESET_TEXT << '\n';
        }
    }
}

int main() {

    std::string path = "myfile.txt";
    Student student[MAX_STUDENTS];
    std::string self_number_in;
    std::string number_group;
    int num_students = 0;

    int choice = 0;

    std::cout << WHITE_TEXT << "Enter a number 1 - 8: " << '\n' << RESET_TEXT;
    std::cout << PURPLE_TEXT << "[1]" << RESET_TEXT << WHITE_TEXT << " Input information about students" << '\n' << RESET_TEXT;
    std::cout << PURPLE_TEXT << "[2]" << RESET_TEXT << WHITE_TEXT << " Change some information" << '\n' << RESET_TEXT;
    std::cout << PURPLE_TEXT << "[3]" << RESET_TEXT << WHITE_TEXT << " Show all information" << '\n' << RESET_TEXT;
    std::cout << PURPLE_TEXT << "[4]" << RESET_TEXT << WHITE_TEXT << " Read information about students of Group" << '\n' << RESET_TEXT;
    std::cout << PURPLE_TEXT << "[5]" << RESET_TEXT << WHITE_TEXT << " Top Students by rating" << '\n' << RESET_TEXT;
    std::cout << PURPLE_TEXT << "[6]" << RESET_TEXT << WHITE_TEXT << " Gender statistics of student" << '\n' << RESET_TEXT;
    std::cout << PURPLE_TEXT << "[7]" << RESET_TEXT << WHITE_TEXT << " Students with good marks" << '\n' << RESET_TEXT;
    std::cout << PURPLE_TEXT << "[8]" << RESET_TEXT << WHITE_TEXT << " Read information about students of Self-Number" << '\n' << RESET_TEXT;
    std::cout << WHITE_TEXT << "Your choice: " << RESET_TEXT;
    std::cin >> choice;
    std::cout << '\n';

    std::string cont;
    do {
        switch (choice) {
        case 1:
            std::cout << "Enter Number of Students: ";
            std::cin >> num_students;
            inputInFile(path, num_students, student);

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
        case 2:
            readAllFile(path, student);
            changeInformation(path, student);

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
        case 3:
            readAllFile(path, student);

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
        case 4:
            std::cout << "Enter number of Group: ";
            std::cin >> number_group;
            std::cout << std::endl;
            readStudentOfGroup(path, number_group, student);

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
        case 5:
            topScore(path, student);

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
        case 6:
            std::cout << "Genger of group: " << '\n';
            std::cout << '\n';
            genderStatistic(path, student);
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
        case 7:
            goodScore(path, student);

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
        case 8:
            std::cout << "Enter number of list: ";
            std::cin >> self_number_in;
            std::cout << '\n';
            readStudentOfNumber(path, self_number_in, student);

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
    } while (cont == "Yes" || cont == "yes" || cont == "y");

    return 0;
}
