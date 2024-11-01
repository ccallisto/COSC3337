#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

fstream infile1, infile2, outfile;
string input;
vector<string> list1, list2;

// Function to load data from the files into vectors
void loadData() {
    infile1.open("input1.txt", ios::in);
    infile2.open("input2.txt", ios::in);

    // Read from input1.txt
    while (getline(infile1, input)) {
        list1.push_back(input);
    }
    infile1.close();

    // Read from input2.txt
    while (getline(infile2, input)) {
        list2.push_back(input);
    }
    infile2.close();
    int i = 0, j = 0;
    while (i < list1.size()){
        cout << list1[i] << "\n";
        i++;
    }
    cout << "_________________________\n";
    while (j < list2.size()){
        cout << list2[j] << "\n";
        j++;
    }

    
}

// Function to merge the two sorted lists into an output file
void mergeData() {

    outfile.open("output.txt", ios::out | ios::trunc);
    int i = 0, j = 0;

    // While there are more names in either list
    while (i < list1.size() && j < list2.size()) {
        if (list1[i] < list2[j]) {
            i++;  // Move to the next name in list1
        } else if (list1[i] > list2[j]) {
            j++;  // Move to the next name in list2
        } else if (list1[i] == list2[j]){
            // If names are equal, write the name and move both pointers
            outfile << list1[i] << std::endl;
            i++;
            j++;
        }
    }

    // Write remaining names from list1 if any
    while (i < list1.size()) {
        outfile << list1[i] << endl;
        i++;
    }

    // Write remaining names from list2 if any
    while (j < list2.size()) {
        outfile << list2[j] << endl;
        j++;
    }

    outfile.close();
}

int main() {
    // Load data from input files
    loadData();
    cout << "data loaded _________________________________";
    
    // Merge the data and write to output file
    mergeData();

    cout << "Merging complete. Check output.txt for results." << endl;

    return 0;
}
