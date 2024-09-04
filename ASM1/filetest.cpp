#include<fstream>
#include<iostream>

using namespace std;
int main(){
char c;
fstream infile;
string filename;
cout << "enter file name to read text from";
cin >> filename;

infile.open(filename, ios::in);
infile.unsetf(ios::skipws);
infile >> c;    

while(!infile.fail()){
	cout<< c;
	infile >> c;
}
	infile.close();
	return 0;
}