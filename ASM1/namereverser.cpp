#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//----------------------------Structures for assignment, Q1 is below------------------------------------------------------//
struct listNode {
    string data;
    listNode* next;
};

class singlyLinkedList {
public:
    listNode* head;
    listNode* p1 = head;

    singlyLinkedList() {
        head = nullptr;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void sortedInsert(string str) {
        listNode* newNode = new listNode();
        newNode->data = str;
        newNode->next = nullptr;

        if (isEmpty()) {
            head = newNode; // Empty case
            return;
        } 
        else if (str <= head->data) {
            newNode->next = head;
            head = newNode; // Case for if the first node string is less than the head
            return;
        } 
        else {
            p1 = head;
            while (p1->next != nullptr && p1->next->data < str) {
                p1 = p1->next; // Standard (middle or end) case
            }
        }

        newNode->next = p1->next;
        p1->next = newNode;
    }

    void printlist() {
        // Prints the list
        listNode* current = head;
        while (current != nullptr) {
            cout << current->data << "\n";
            current = current->next;
        }
    }
};

int main() {
    //-------------------------------------------Question 1 ------------------------------------------------------//
    char c;
    fstream infile;
    string filename;
    cout << "enter file name to read text from; try inputfile.txt\n";
    cin >> filename;
    
    infile.open(filename, ios::in);
    infile.unsetf(ios::skipws);
    infile >> c;
    
    while (!infile.fail()) {
        cout << c;
        infile >> c;
    }
    cout << "\n";

    //-------------------------------------------Question 2 ------------------------------------------------------//
    
    //-------------------------------------------Part A ------------------------------------------------------//
    // Part A: Take inputs from the terminal and output them back to the terminal in reverse
    string input;
    cout << "Please input names to be reversed, exit by writing 'end'\n";
    while (getline(cin, input)) {
        if (input == "end") {
            break;
        }

        // Reverse the string and output to console
        for (int i = input.size() - 1; i >= 0; i--) {
            cout << input[i];
        }
        cout << "\n";
    }

    //-------------------------------------------Part B ------------------------------------------------------//
    // Part B: Take inputs from the terminal and output them reversed into a file, file1
    fstream file1;
    file1.open("file1.txt", ios::out | ios::trunc);
    
    cout << "Please input names to be reversed and put into file1, exit by writing 'end'\n";
    while (getline(cin, input)) {
        if (input == "end") {
            break;
        }

        // Reverse the string and output to file
        for (int i = input.size() - 1; i >= 0; i--) {
            file1 << input[i];
        }
        file1 << "\n";
    }
    file1.close(); // Close the file

    //-------------------------------------------Part C ------------------------------------------------------//
    // Part C: Reopen file1 and reverse the names again into file2.
    fstream file2;
    file1.open("file1.txt", ios::in);
    file2.open("file2.txt", ios::out | ios::trunc);

    while (!file1.fail()) {
        getline(file1, input);
        for (int i = input.size() - 1; i >= 0; i--) {
            file2 << input[i]; // secondary name re-reverser
        }
        file2 << "\n";
    }
    file1.close();
    file2.close();

    //-------------------------------------------Part D ------------------------------------------------------//
    // Output the re-reversed names in alphabetical order
    file2.open("file2.txt", ios::in);
    singlyLinkedList* strList = new singlyLinkedList();

    while (!file2.fail()) {
        string str = "";
        getline(file2, input);
        for (int i = input.size() - 1; i >= 0; i--) {
            str += input[i];
        }
        strList->sortedInsert(str);
    }

    strList->printlist();
    file2.close();

    return 0;
}
