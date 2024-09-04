#include <iostream>
#include <fstream>

using namespace std;
int main(){
    fstream outfile;
    fstream infile;
    string input;
    
    infile.open("names_list_no_comma.txt", ios::in);
    outfile.open("outputfile.txt", ios::out | ios::trunc);
    //cout << "Please input names to be reversed\n";
    while(!infile.fail()){
    
    getline(infile, input);      //using this over cin since by default it stops with whitespace   

    int i = input.size();

    for(i = input.size()-1; i >=0; i--)//initial name reverser
    {

        // cout << input[i]; //debugging output
        outfile << input[i];
    }                   
    cout << "\n";
    }
    outfile.close();
    infile.close();
}                   