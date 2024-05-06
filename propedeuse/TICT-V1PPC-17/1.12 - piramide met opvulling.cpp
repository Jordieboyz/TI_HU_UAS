#include <iostream>
#include <string>
using namespace std;

int main(){
	int getal;
	string teken = "*";
	cout << "Geef een positief getal: ";
	cin >> getal; 
	
	
	for(int i = 1; i < getal; i++){
	string ster(i, '*');
	string spaties(getal-i, ' ');
	cout << spaties << ster << "\n";
	}
	
	

	for(int i = getal; i > 0; i--){
	string ster(i, '*');
	string spaties(getal-i, ' ');
	cout << spaties << ster << "\n";
	}
}