#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

// information struct used for handling data fields after reading from file
struct Person {
    string firstname;
    string lastname;
    int age;
    string job;

    // Combine firstname and lastname for easier comparisons and searches
    string getFullName() const {
        return firstname + ", " + lastname;
    }
    
    bool operator<(const Person& other) const {
        return getFullName() < other.getFullName();
    }
};

class FileSearcher {
public:
    fstream infile;
    string filename, input;
    char answer;
    bool found;

    vector<Person> persons;

    // Helper function to split a line by a delimiter
    vector<string> split(const string& line, char delimiter) {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    void loadData() {
        cout << "Enter the name of the data file to search (default: file1.txt): ";
        cin >> filename;
        infile.open(filename, ios::in);

        // Clear the vector before loading new data
        persons.clear();
        //originally just manually allocated array space. Vector map is flexible and wantd to try it out

        while (getline(infile, input)) {
            vector<string> tokens = split(input, '|');
            if (tokens.size() == 4) {
                Person p;
                p.lastname = tokens[0];
                p.firstname = tokens[1];
                p.age = stoi(tokens[2]);
                p.job = tokens[3];
                persons.push_back(p);
            }
        }

        // Sort the vector by full name
        sort(persons.begin(), persons.end());
        infile.close();
    }

    void sequentialSearch() {
        while (true) {
            string firstname, lastname;
            cout << "Enter last name: ";
            cin >> lastname;
            cout << "Enter first name: ";
            cin >> firstname;

            string fullname = firstname + ", " + lastname;
            bool found = false;

            for (const auto& person : persons) {
                if (person.getFullName() == fullname) {
                    cout << "Found: " << person.getFullName() << ", Age: " << person.age << ", Job: " << person.job << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << fullname << " not found in file." << endl;
            }

            cout << "Would you like to search another name (y/n)? ";
            cin >> answer;
            if (answer != 'y') {
                break;
            }
        }
    }

    void binarySearch() {
        while (true) {
            string firstname, lastname;
            cout << "Enter last name: ";
            cin >> lastname;
            cout << "Enter first name: ";
            cin >> firstname;

            string fullname = firstname + ", " + lastname;

            // Binary search
            int low = 0;
            int high = persons.size() - 1;
            bool found = false;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (persons[mid].getFullName() == fullname) {
                    cout << "Found: " << persons[mid].getFullName() << ", Age: " << persons[mid].age << ", Job: " << persons[mid].job << endl;
                    found = true;
                    break;
                }

                if (persons[mid].getFullName() < fullname) {
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }

            if (!found) {
                cout << fullname << " not found in file." << endl;
            }

            cout << "Would you like to search another name (y/n)? ";
            cin >> answer;
            if (answer != 'y') {
                break;
            }
        }
    }
};

int main() {
    FileSearcher searcher;
    searcher.loadData(); // Load data from file

    cout << "-------------------------SEQUENTIAL SEARCH PORTION-------------------------\n";
    searcher.sequentialSearch();

    cout << "---------------------------BINARY SEARCH PORTION---------------------------\n";
    searcher.binarySearch();
}
