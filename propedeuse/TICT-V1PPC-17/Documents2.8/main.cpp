#include <iostream>
#include <string>
using namespace std;

int langereString(string a, string b){
    if(a.size() > b.size()) {
        return a.size();
    }
    else {
         return b.size();
    }
}

int index_same(string a, string b){
    int maxSize = langereString(a , b);
    for(unsigned int i = 0; i <= maxSize; i++){
        if(a[i] != b[i]){
            return i+1;
        }
        else if(a == b){
            return 0;
        }
    }
    
}


int main(){
    string a;
    string b;
    
    cout << "Geef een string: ";
    getline(cin, a);
    cout << "Geef de tweede string: ";
    getline(cin, b);
    
    int zelfde_index = index_same(a, b);
    
    if(zelfde_index == 0) {
            cout << endl << "De strings zijn hetzelfde!" << endl;
    }
    else {
        cout << endl << "Het eerste verschil zit op het " << zelfde_index << "e character!" << endl;
    }
}



