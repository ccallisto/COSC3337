#include <iostream>
#include <fstream>
//update this to include steps A-D, comment where they are specifically
using namespace std;
int main(){
    fstream file1;
    fstream file2;
    fstream infile;
    string input;
    
    infile.open("names_list_no_comma.txt", ios::in);
    file1.open("file1.txt", ios::out | ios::trunc);
    file2.open("file2.txt", ios::out | ios::trunc);
    //cout << "Please input names to be reversed\n";
    while(!infile.fail()){
    
    getline(infile, input);      //using this over cin since by default it stops with whitespace   

    for(int i = input.size()-1; i >=0; i--)//initial name reverser
    {

        // cout << input[i]; //debugging output
        file1 << input[i];
    }                   
    file1 << "\n";
    
    }

    while(!infile.fail()){
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
    infile.close();
}                   