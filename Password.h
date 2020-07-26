#ifndef PASSWORD_H
#define PASSWORD_H

class Password
{
private:


	
public:
	Password();
	int getlinenum(char operation);
	bool stringFind(std::string user);
	bool Passfind(std::string password);
	void writeBalance(double newbalance);
	double readBalance();
};

#endif 

