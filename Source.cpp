#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <limits>
//#include "Password.h"

template<class T,class V> 
T CinCheck(T minimum, T maximum, V message[], V wrong_message[]) {
    T number;
    while ((std::cout << message )<< "\n"&& (!(std::cin >> number) || number > maximum || number < minimum )){
        std::cout << wrong_message<<"\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return number;
}

class BalanceFile
{
    double balance{ NULL };
public:
    double readbalance() {
        std::ifstream blnce;
        blnce.open("balance.txt", std::ios::in);
        blnce >> balance;
        blnce.close();
        return balance;
    }

    void writeBalance(double newbalance) {
        std::ofstream write;
        write.open("balance.txt", std::ios::out);
        write << newbalance << std::endl;
        write.close();
    }

    
};

class bankaccount :private BalanceFile
{

private:
    
    BalanceFile bln;
    double balance = NULL;



public:
    bankaccount()
        :balance(bln.readbalance())
    {
    }
    double withdraw(double transmoney) {
        if (balance >= transmoney) {
            balance = balance - transmoney;
            writeBalance(balance);
            return balance;
        }

        else {
            std::cout << "You have insufficient balance to do the transaction" << std::endl;

            return balance;
        }
    };
    double deposit(double transmoney) {
        balance = balance + transmoney;
        writeBalance(balance);
        return balance;
    };
    double balanceinquiry() {
        return balance;
    };

};



int main()
{
    constexpr char message[]{ "Press 1 for withdrawal\nPress 2 for money deposit\nPress 3 for Balance Inquiry" };
    constexpr char wrong_message[]{ "You typed the wrong number perhaps?\n" };
    constexpr char depmsg[]{ "How much would you like to deposit to your account?\n" };
    constexpr char withmsg[]{ "How much would you like to withdraw to your account?\n" };
    constexpr char invalnum[]{ "That's not a valid number\n" };
    constexpr double maxnum{ 1.8e307 };
    
    std::string transaction;
    bankaccount* myacc = new bankaccount;

    while (true) {
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        
        int transaction{ CinCheck<int>(1,3,message,wrong_message) };
        double newbalance;
        if (transaction == 1) {
            double with{CinCheck<double>(0,maxnum,withmsg,invalnum)};
            newbalance = myacc->withdraw(with);
            std::cout << "Your new balance is "<< newbalance << "$" << std::endl;
        }
        else if (transaction == 2) {
            
            
            double dep{ CinCheck<double>(0,maxnum,depmsg,invalnum) };
            newbalance = myacc->deposit(dep);
            std::cout << "Your new balance is "<< newbalance << "$" << std::endl;
        }
        else if (transaction == 3) {
            newbalance = myacc->balanceinquiry();
            std::cout << "Your current account balance is "<< newbalance<< "$" << std::endl;
        }
        else {
            std::cout << "You typed the wrong number perhaps?" << std::endl;
        }

       std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    return 0;
}





