#include <iostream>
#include <string>

std::string translate(std::string line, std::string argument){
        std::string result = "";
        for(unsigned int i = 0; i < line.size();i++){
            char letter = line[i];
            if(letter >= 'a' && letter <= 'z'){
                char tmp = letter+stoi(argument);
                if(tmp > 'z'){
                    tmp -= 26;
                    result += tmp;
                }
                else{
                    result += tmp;
                }
            }
            else if(letter >= 'A' && letter <= 'Z'){
                char tmp = letter+stoi(argument);
                if(tmp > 'Z'){
                    tmp -= 26;
                    result += tmp;
                }
                else{
                    result += tmp;
                }
            }
            else{
                result += " ";
            }
        }
    return result;
}

int main(int argc, char* argv[]) {
        std::string line;
        if(argc != 2){
		std::cout << "Je moet exact 1 getal opgeven!" << std::endl; 
		return -1;
	}; 
	while(std::getline(std::cin, line)){
		if(std::cin.eof()){
			break;
		}
		std::cout << "Tekst om te bewerken: " << line << std::endl;
        	std::cout << "De versleutelde tekst: " << translate(line, argv[1]) << std::endl << std::endl;
		
		
        }
return 0;
}

