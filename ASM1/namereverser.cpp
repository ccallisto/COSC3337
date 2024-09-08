#include <iostream>
#include <fstream>
//update this to include steps A-D, comment where they are specifically
using namespace std;

int main(){
    //-------------------------------------------Question 1 ------------------------------------------------------//

        char c;
    fstream infile;
    string filename;
    cout << "enter file name to read text from";
    cin >> filename;
    //example file in directory will be called q1.txt
    infile.open(filename, ios::in);
    infile.unsetf(ios::skipws);
    infile >> c;    

    while(!infile.fail()){
        cout<< c;
        infile >> c;
    }
    //-------------------------------------------Question 2 ------------------------------------------------------//

    //-------------------------------------------Part A & B------------------------------------------------------//
    // Part A: Read names from file and reverse them into file1.
    // Part B: Output reversed names to console as well.
    fstream file1;
    fstream file2;
    fstream infilepart2;
    string input;
    
    infilepart2.open("names_list_no_comma.txt", ios::in);
    file1.open("file1.txt", ios::out | ios::trunc);
    //cout << "Please input names to be reversed\n";
    while(!infilepart2.fail()){
    
        getline(infilepart2, input);      //using this over cin since by default it stops with whitespace   

        for(int i = input.size()-1; i >=0; i--)//initial name reverser
        {

            cout << input[i]; //part A output
            file1 << input[i]; //part B File writing
        }                   
        cout <<"\n";
        file1 << "\n";
    
    }
    file1.close();

    //-------------------------------------------Part C ------------------------------------------------------//
    // Part C: Reopen file1 and reverse the names again into file2.
    file1.open("file1.txt", ios::in);
    file2.open("file2.txt", ios::out | ios::trunc);

    while(!file1.fail()){
        getline(file1, input);
            for(int i = input.size()-1; i >=0; i--)//secondary name re-reverser
            {
                // cout << input[i]; //debugging output
                file2 << input[i];
            }                   
            file2 << "\n";
    }    
    file1.close();
    file2.close();
    infilepart2.close();
}                   