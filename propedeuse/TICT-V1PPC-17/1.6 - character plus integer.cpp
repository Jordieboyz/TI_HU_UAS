#include <iostream>
using namespace std;

int main(){
	char letter;
	
	cout << "Geef een caharacter: ";
	cin >> letter;
	
	int kleine_letter = int(letter) + 32 ;
	cout << letter << " + " << "32 = " << int(kleine_letter) << "\n";
	cout << letter << " + " << "32 = " << char(kleine_letter) << "\n";
}