#include "shell.hh"

int main(){ 
	std::string input;
	std::string prompt;
		
	int pdOpen = syscall(SYS_open, "prompt" , O_RDONLY, 0755);
	char buffer[1];
	while(syscall(SYS_read, pdOpen, buffer, 1)){
		prompt += buffer;
	}
	
while(true){ 
	std::cout << prompt;			// Print het prompt
	std::getline(std::cin, input);		// Lees een regel
    	if (input == "new_file") new_file();   // Kies de functie
  	else if (input == "ls") list();        //   op basis van
  	else if (input == "find") find();	//de invoer
	else if (input == "seek") seek();
    	else if (input == "exit") return 0;
    	else if (input == "quit") return 0;
    	else if (input == "error") return 1;
	
	if (std::cin.eof()) 
		return 0;
		      // EOF is een exit
	}
}
void new_file(){ 
	std::string filename;
	std::cout << "kies een bestandsnaam:  ";
	std::cin >> filename;
	const char* name = filename.c_str();
	int fd = syscall(SYS_creat, name, 0755);
	//int fd = syscall(SYS_open, name, O_CREAT | O_WRONLY, 0755); 
	std::string write;
	std::cout << "Welke tekst wil je naar \e[32m"  << filename << "\e[0m wil schrijven! " << std::endl;
	while(std::getline(std::cin, write)){
		if(std::cin.eof() | write == "<EOF>"){
			break;
		}
		else{
			if(write != ""){
				std::string writeEnter = write + "\n";
				const char* lines = writeEnter.c_str();
				syscall(SYS_write, fd, lines, strlen(lines));
			}
				else{
			
			}
		}
	}
};




void list() {
	int pd = syscall(SYS_fork);
        const char* args[] = { "/bin/ls", "-la", NULL};
	if(pd == 0){
                syscall(SYS_execve, args[0], args, NULL);

	}
        else{
                syscall(SYS_wait4, pd, NULL, NULL, NULL);
        }
};

void find() {
	int fd[2];
	syscall(SYS_pipe, &fd);

	std::string searchString;
	std::cin >> searchString;


	int pd1 = syscall(SYS_fork);
	if(pd1 == 0){
		syscall(SYS_close, fd[0]);
		syscall(SYS_dup2, fd[1], 1);
		const char *argsFind[] = { "/usr/bin/find", ".", NULL};
		syscall(SYS_execve, argsFind[0], argsFind, NULL);
	}
	else{
		int pd2 = syscall(SYS_fork);
		if(pd2 == 0){
			syscall(SYS_close, fd[1]);
			syscall(SYS_dup2, fd[0], 0);
			const char *argsGrep[] = {"/bin/grep" , searchString.c_str(), NULL };
			syscall(SYS_execve, argsGrep[0], argsGrep, NULL);
		}
		else{
			syscall(SYS_close, fd[0]);
			syscall(SYS_close, fd[1]);
			syscall(SYS_wait4, pd1, NULL, NULL, NULL);
			syscall(SYS_wait4, pd2, NULL, NULL,  NULL);
		}	
	}
}

void seek() { 
	clock_t start, end;
	const char x = 'x';

	start = clock();
	int pdLOOP = syscall(SYS_open, "loop", O_CREAT | O_WRONLY, 0755);
	syscall(SYS_write, pdLOOP, x, 1);	
	for(int i = 0; i<5000000;i++){
		syscall(SYS_write, pdLOOP, "\0", 1);
	}
	syscall(SYS_write, pdLOOP, "x", strlen("x"));
	end = clock();

	double time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("de for-loop duurde %f seconden \n", time_taken);


	start = clock();
	int pdSEEK = syscall(SYS_open, "seek",O_CREAT | O_WRONLY, 0755);
	syscall(SYS_write, pdSEEK, x, strlen("x"));
	syscall(SYS_lseek, pdSEEK, 5000000 , SEEK_END);
	syscall(SYS_write, pdSEEK, "x", strlen("x"));
	end = clock();

	double time_takenSEEK = ((double)(end-start))/CLOCKS_PER_SEC;
	printf("de lseek duurde %f seconden \n", time_takenSEEK);
};
