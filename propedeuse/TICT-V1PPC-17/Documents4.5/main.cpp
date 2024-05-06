#include <iostream>
#include <fstream>

using namespace std;

void compress(string src_filename, string dest_filename){
    string line;
    ifstream first_file;
    ofstream second_file;
    first_file.open(src_filename);
    second_file.open(dest_filename);
    
    while (getline(first_file, line)){
        int teller = 0;
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] != ' ' && line[i] != '\t') {
                line.erase(0, teller);
                second_file << line << endl;
                break;
            }
            else if(line[i] == '\n'){
                break;
            }
        teller++;
        }
    }
    first_file.close();
    second_file.close();
}

    
int main() {
    compress("lol.txt", "nieuwe_tekst.txt");
}


