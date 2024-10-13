#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class employee {
    string firstName, lastName;
    int id, rating, age;

public:
    void setData(const string& firstName, const string& lastName, int id, int rating, int age) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->id = id;
        this->rating = rating;
        this->age = age;
    }

    string getFixedLengthRecord() const {
        stringstream record;

        // Pad or truncate each field to the required length
        record << right << setfill('0') << setw(3) << id  // Ensure ID is always 3 characters, with leading zeros
            << left << setfill(' ') << setw(25) << firstName
            << left << setw(25) << lastName
            << right << setw(1) << rating
            << right << setw(2) << age;
        // tot length is 56 
        return record.str();
    }

    void print() const {
        cout << "ID: " << id << ", First Name: " << firstName
            << ", Last Name: " << lastName << ", Rating: " << rating
            << ", Age: " << age << endl;
    }
};

class recordHandler {
    fstream records;
    int id = 99;

public:
    recordHandler() {
        ifstream indexIn("index.txt");  // Use ifstream for reading only
        if (indexIn.is_open()) {
            string lastLine;
            while (getline(indexIn, lastLine)) {
                id = stoi(lastLine);  // Increment the id based on the last line
            }
        }
        indexIn.close();  
    }

    void closefile() {
        records.close();
    }

    void addemp() {
        employee employee;
        string NameFir, NameLas;
        int rating, age;

        cout << "enter first name: ";
        cin >> NameFir;
        cout << "enter last name: ";
        cin >> NameLas;
        cout << "enter a rating: ";
        cin >> rating;
        cout << "enter employee age: ";
        cin >> age;
        ++id;

        employee.setData(NameFir, NameLas, id, rating, age);
        string fixedrecord = employee.getFixedLengthRecord();

        
        records.open("records.txt", ios::out | ios::app);
        if (!records.is_open()) {
            cerr << "Error: Unable to open records.txt for writing." << endl;
            return;
        }
        records << fixedrecord << endl;  // Append the new record
        records.close();

        // Write to index file
        ofstream indexOut("index.txt", ios::app);
        if (!indexOut.is_open()) {
            cerr << "Error: Unable to open index.txt for writing." << endl;
            return;
        }
        indexOut << to_string(id) << endl;  // Append the new ID to the index
        indexOut.flush();  
        indexOut.close();  
    }

    employee searchemp() {
        string EIN, EINCheck, line, emptyre;
        cout << "Enter Employee ID: ";
        cin >> EIN;
        bool found = false;

        
        ifstream indexIn("index.txt");
        indexIn.clear();
        indexIn.seekg(0, ios::beg);  

        // Search for the Employee ID in the index file
        while (getline(indexIn, EINCheck)) {
            if (EINCheck == EIN) {
                found = true;
                break;
            }
        }
        indexIn.close();

        if (!found) {
            cout << "Record not found" << endl;
            return employee();  // Return an empty employee object
        }

        // Calculate the offset for the records file
        records.open("records.txt", ios::in | ios::out);
        records.clear();  
        records.seekg(0, ios::beg); 
        int offset = stoi(EIN) - 100;  
        int position = offset * 58;    // Each record is 56 bytes and we account for \n and \r char

        // Seek to the correct position in the records file
        records.seekg(position);

        // Read the fixed-length record
        char buffer[57];
        records.read(buffer, 56);
        buffer[56] = '\0';
        line = buffer;

        // Extract the employee data from the fixed-length record
        string firstName = line.substr(3, 25);
        string lastName = line.substr(28, 25);
        int rating = stoi(line.substr(53, 1));
        int age = stoi(line.substr(54, 2));

        employee emp;
        emp.setData(firstName, lastName, stoi(EIN), rating, age);
        emp.print();
        records.close();
        return emp;
    }

    void deleteemp() {
        string EIN, EINCheck;
        cout << "Enter Employee ID to delete: ";
        cin >> EIN;

        ifstream indexIn("index.txt");
        indexIn.clear();
        indexIn.seekg(0, ios::beg);  // Reset pointer to the beginning

        bool found = false;
        while (getline(indexIn, EINCheck)) {
            if (EINCheck == EIN) {
                found = true;
                break;
            }
        }
        indexIn.close();

        if (!found) {
            cout << "Record not found" << endl;
            return;
        }

        records.open("records.txt", ios::in | ios::out);
        records.clear();
        int offset = stoi(EIN) - 100;
        int position = offset * 58;

        records.seekp(position);
        string deletedRecord = "-1" + string(55, ' ');
        records.write(deletedRecord.c_str(), 56);
        records.close();
        
        fstream index;

        index.open("index.txt", ios::in | ios::out);
        index.clear();
        offset = stoi(EIN) - 100;
        position = offset * 5;

        index.seekp(position);
        deletedRecord = "-1" + string(1, ' ');
        index.write(deletedRecord.c_str(), 1);
        index.close();

        cout << "Employee record deleted" << endl;

    }
};

int main() {
    recordHandler handler;

    int opt = 0;
    while (opt != 4) {
        cout << "select an option 1- add 2- search 3-delete 4-quit: ";
        cin >> opt;

        if (opt == 1) {
            handler.addemp();
        }
        else if (opt == 2) {
            handler.searchemp();
        }
        else if (opt == 3) {
            handler.deleteemp();
        }
        else if (opt == 4) {
            break;
        }
        else {
            cout << "enter option again";
        }
    }
    handler.closefile();
}
