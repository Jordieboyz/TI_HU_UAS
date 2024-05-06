#include <iostream>
#include <string>
using namespace std;

int main(){
	int getal;
	string teken = "*";
	cout << "Geef een positief getal: ";
	cin >> getal; 
	
	string ster(getal, '*');
	for(int i = 0; i < getal; i++){
	cout << ster << "\n";
	}
}