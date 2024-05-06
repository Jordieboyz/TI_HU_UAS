
#include <iostream>
#include <string>
using namespace std;

int main(){
	int getal;
	string teken = "*";
	cout << "Geef een positief getal: ";
	cin >> getal; 
	
	for(int i = 0; i <= getal; i++){
	string ster(i, '*');
	cout << ster << "\n";
	}
}