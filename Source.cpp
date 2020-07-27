#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <limits>
#include "Password.h"

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


std::string NameHandling(const char msg[]) {
    std::string Name{ NULL };
    bool LoopEnder{ true };
    while (LoopEnder) {
        getline(std::cin, Name);
        if (Name.length() < 4) {
            std::cin.clear();
            std::cout << msg<<"\n";
        }
        else {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                LoopEnder = false;
            }
        }
    }
    return Name;
}

/*class BalanceFile
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

    
};*/

class bankaccount :private Password
{

private:
    
    Password Auth;
    double balance = NULL;



public:
    bankaccount()
        :balance(Auth.readBalance())
    {
    }
    double withdraw(double transmoney) {
        if (balance >= transmoney) {
            balance = balance - transmoney;
            Auth.writeBalance(balance);
            balance = Auth.readBalance();
            return balance;
        }

        else {
            std::cout << "You have insufficient balance to do the transaction" << std::endl;

            return balance;
        }
    };
    double deposit(double transmoney) {
        balance = Auth.readBalance() + transmoney;
        Auth.writeBalance(balance);
        return balance;
    };
    double balanceinquiry() {
        return Auth.readBalance();
    };

};



int main()
{
    //std::string a{ NameHandling() };
    constexpr char clearscreen[]{ "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" };
    constexpr char message[]{ "Press 1 for withdrawal\nPress 2 for money deposit\nPress 3 for Balance Inquiry\nPress 4 to logout\n" };
    constexpr char wrong_message[]{ "You typed the wrong number perhaps?\n" };
    constexpr char depmsg[]{ "How much would you like to deposit to your account?\n" };
    constexpr char withmsg[]{ "How much would you like to withdraw to your account?\n" };
    constexpr char invalnum[]{ "That's not a valid number\n" };
    constexpr char loginmsg[]{ "Press 1 for account transaction\nPress 2 for new account" };
    constexpr char askname[]{ "Enter your username\n" };
    constexpr char incompletemsg[]{"That functionality is inavailable as of now\n"};
    constexpr char wrongnamemsg[]{ "That username is incorrect or not available\n" };
    constexpr char rightnamemsg[]{ "Type your password\n" };
    constexpr char wrongpassmsg[]{ "That password is incorrect, Try Again\n" };
    constexpr char rightpassmsg[]{ "Success! Logging In...\n" };
    constexpr char invalnamemsg[]{ "Invalid Name!, Try Again\n" };
    constexpr char invalpassmsg[]{ "Invalid Password!\n" };
    constexpr char newaccmsg[]{ "Write a username\n" };
    constexpr char unavname[]{"That name has already been taken\n"};
    constexpr char newpassmsg[]{"Write a password(Dont forget it!)\n"};
    constexpr char verifymsg[]{ "Rewrite your password\n" };
    constexpr char wrongvermsg[]{ "That's not the same password, Try Again.\n" };
    constexpr char succvermsg[]{ "Success!, You can now login to your account\n" };

    constexpr double maxnum{ 1.8e307 };
    bool LoggedIn{ false };
    while (true) {
        std::cout << clearscreen;
        
        int Logging{ CinCheck<int>(1,2,loginmsg,invalnum) };
        if (Logging == 1) {
            Password* Auth = new Password;
            std::cout << askname;
            std::string username{ NameHandling(invalnamemsg) };
            bool isNameTrue = Auth->stringFind(username);
            if (isNameTrue == true) {
                std::cout << rightnamemsg;
                bool isPassTrue{ false };
                while (!isPassTrue) {
                    std::string password{ NameHandling(invalpassmsg) };
                    isPassTrue = Auth->Passfind(password);
                    if (isPassTrue == false) {
                        std::cout << wrongpassmsg;
                    }
                    else {
                        std::cout << rightpassmsg;
                        LoggedIn = true;
                    }
                }
            }
            else {
                std::cout << wrongnamemsg;
                
            }
            delete Auth;
        }
        else if (Logging == 2) {
            std::cout << newaccmsg;
            Password* Auth = new Password;
            std::string newname{ NameHandling(invalnamemsg) };
            bool isNameUnavailable{ Auth->stringFind(newname) };
            if (!isNameUnavailable){
                std::cout << newpassmsg;
                std::string newpass{ NameHandling(invalpassmsg) };
                bool PassVerified{ false };
                std::cout << verifymsg;
                while (!PassVerified) {
                    std::string verpass{ NameHandling(wrongvermsg) };
                    if(newpass == verpass) {
                        PassVerified = true;
                        Auth->SaveNewAcc(newname,newpass);
                        std::cout << succvermsg;
                    }
                    else{
                        std::cout << wrongvermsg;
                    }
                }

            }
            else {
                std::cout << unavname;
            }
            delete Auth;
            
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        
        while (LoggedIn) {
            bankaccount* myacc = new bankaccount;
            std::cout << clearscreen;
            int transaction{ CinCheck<int>(1,4,message,wrong_message) };
            double newbalance;
            if (transaction == 1) {
                double with{ CinCheck<double>(0,maxnum,withmsg,invalnum) };
                newbalance = myacc->withdraw(with);
                std::cout << "Your new balance is " << newbalance << "$" << std::endl;
            }
            else if (transaction == 2) {


                double dep{ CinCheck<double>(0,maxnum,depmsg,invalnum) };
                newbalance = myacc->deposit(dep);
                std::cout << "Your new balance is " << newbalance << "$" << std::endl;
            }
            else if (transaction == 3) {
                newbalance = myacc->balanceinquiry();
                std::cout << "Your current account balance is " << newbalance << "$" << std::endl;
            }
            else if (transaction == 4) {
                LoggedIn = false;
                std::cout << "Goodbye!!\n";
                delete myacc;
            }
            else {
                std::cout << "You typed the wrong number perhaps?" << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            
        }
    }

    
    return 0;
}