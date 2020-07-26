#include <string>
#include <fstream>
#include <iostream>
#include "Password.h"
Password::Password() {

}

int Password::getlinenum(char operation) {
	static int line{ 1 };
	switch (operation) {
	case '+':
		line++;
		break;
	case '=':
		return line;
		break;
	case '0':
		line = 1;
		break;
	}
}

bool Password::stringFind(std::string user) {
	
	getlinenum(0);
	std::ifstream info;
	std::string found_user;
	info.open("balance.txt");
	while (getline(info, found_user)) {
		std::string copy{ found_user };
		getlinenum('+');
		if(copy==user){
			
			return true;
		}
		else {
			getlinenum('+');
			getlinenum('+');
			getline(info, found_user);
			getline(info, found_user);
		}
	}
	return false;
	
	
}
bool Password::Passfind(std::string password) {
	std::ifstream info;
	std::string found_pass;
	info.open("balance.txt");
	int txtline{ getlinenum('=') };
	for (int i= 0; i < txtline; i++) {
		getline(info, found_pass);
	}
	if (found_pass == password) {
		return true;
	}
	else {
		return false;
	}
}

double Password::readBalance(){
	std::ifstream blnce;
	double balance;
	std::string buffer;
	blnce.open("balance.txt", std::ios::in);
	int txtline{ getlinenum('=') };
	for (int i = -1; i < txtline ; i++) {
		 
		
		getline(blnce,buffer);
	}
	balance = std::stod(buffer);
	blnce.close();
	return balance;
}
void Password::writeBalance(double newbalance) {
	std::fstream write;
	std::string buffer;
	int txtline{ getlinenum('=') };
	write.open("balance.txt", std::ios::out|std::ios::in);
	for (int i = -1; i < txtline; i++) {
		
		getline(write,buffer);
	}
	write << newbalance;
	write.close();
}
