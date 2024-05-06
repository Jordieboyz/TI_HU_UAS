#include <iostream>
#include <string>
using namespace std;

int main(){
	string vertaal_zin;
	cout << "Geef een zin/woord die je vertaald wil hebben: ";
	getline(cin, vertaal_zin);

	for(int i = 0; vertaal_zin[i]; i++){
		int op =  char(vertaal_zin[i])-32;
		
		switch(vertaal_zin[i]){
			case 'e': vertaal_zin[i] = '3';
			break;
			case 'o': vertaal_zin[i] = '0';
			break;
			case 't': vertaal_zin[i] = '7';
			break;
			case 'i': vertaal_zin[i] = '1';
			break;
			default: vertaal_zin[i] = char(op) ;
			break;
			}
		}
	cout << "\n" << vertaal_zin << "\n";
}