#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "Password.h"
Password::Password() {
	LineCounter();
}

int Password::getlinenum(char operation) {
	static int line{ 1 };
	static int totalline{0};
	switch (operation) {
	case '+':
		line++;
		break;
	case '%':
		totalline++;
		break;
	case 'N':
		totalline = 0;
		break;
	case 'T':
		return totalline;
		break;
	case '=':
		return line;
		break;
	case '0':
		line = 1;
		break;
	}
	return 0;
}

bool Password::stringFind(std::string user) {
	getlinenum('0');
	std::ifstream info;
	std::string found_user;
	info.open("balance.txt");
	while (getline(info, found_user)) {
		std::string copy{ found_user };
		if(copy==user){
			info.close();
			return true;
		}
		else {
			getlinenum('+');
			getlinenum('+');
			getlinenum('+');
			getline(info, found_user);
			getline(info, found_user);
		}
	}
	info.close();
	return false;
}

bool Password::Passfind(std::string password) {
	std::ifstream info;
	std::string found_pass;
	std::string copy;
	info.open("balance.txt");
	int txtline{ getlinenum('=') };
	for (int i= 0; i <= txtline; i++) {
		getline(info, found_pass);
		copy = found_pass;
	}
	if (copy == password) {
		info.close();
		return true;
	}
	else {
		info.close();
		return false;
	}
}

void Password::writeBalance(double newbalance) {
	std::ostringstream convert;
	convert << newbalance;
	std::string replacement = convert.str();
	SaveAlgo(replacement);
}

void Password::SaveAlgo(std::string replacement) {
	int line = { getlinenum('=')+1 };//add 1 to point to line for balance
	std::vector<std::string>data;
	std::ifstream txt;
	txt.open("balance.txt");
	std::string a;
	while (getline(txt, a)) {
		data.push_back(a);
	}
	txt.close();
	std::ofstream write;
	write.open("balance.txt", std::ios::out);
	data[line] = replacement;
	int i=0;
	for (; i < static_cast<int>(data.size()-1); i++) {
		write << data[i] << "\n";
	}
	write << data[i];
	write.close();
}

double Password::readBalance(){
	std::ifstream blnce;
	std::string copy;
	double balance;
	blnce.open("balance.txt", std::ios::in);
	int txtline{ getlinenum('=')+2 };
	for (int i = 0; i < txtline; ++i) {
		getline(blnce,copy);
	}
	balance = atof(copy.c_str());
	blnce.close();
	return balance;
}

void Password::SaveNewAcc(std::string name, std::string password){
	std::fstream writeacc;
	double starterbalance = 0.0;
	writeacc.open("balance.txt", std::ios::app);
	int line{ getlinenum('T') };
	if (getlinenum('T') > 0) {
		line += 1;
		writeacc.seekg(line);
		writeacc << "\n" << name << "\n" << password << "\n" << starterbalance;
	}
	else {
		writeacc << name << "\n" << password << "\n" << starterbalance;
	}
	writeacc.close();
}

void Password::LineCounter() {
	std::ifstream countline;
	countline.open("balance.txt");
	std::string catcher;
	getlinenum('N');
	while (getline(countline, catcher)) {
		getlinenum('%');
	}
	countline.close();
}
