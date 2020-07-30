#ifndef PASSWORD_H
#define PASSWORD_H

class Password{
public:
	Password();
	int getlinenum(char operation);
	bool stringFind(std::string user);
	bool Passfind(std::string password);
	void writeBalance(double newbalance);
	void SaveAlgo(std::string replacement);
	double readBalance();
	void SaveNewAcc(std::string name,std::string password);
	void LineCounter();
};

#endif 

