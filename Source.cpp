#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>

using namespace std;

class BalanceFile :public fstream
{
public:
    double readbalance() {
        ifstream blnce;
        blnce.open("balance.txt", ios::in);
        blnce >> balance;
        return balance;
    }

    void writeBalance(double newbalance) {
        ofstream write;
        write.open("balance.txt", ios::out);
        write << newbalance << endl;
        write.close();
    }

    double balance;
};

class bankaccount :private BalanceFile
{
private:

    BalanceFile bln;
    double balance = bln.readbalance();;



public:

    double withdraw(double transmoney) {
        if (balance >= transmoney) {
            balance = balance - transmoney;
            writeBalance(balance);
            return balance;
        }

        else {
            cout << "You have insufficient balance to do the transaction" << endl;

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
    string transaction;
    bankaccount* myacc = new bankaccount;

    while (true) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "Press 1 for withdrawal" << endl << "Press 2 for money deposit" << endl << "Press 3 for Balance Inquiry" << endl;

        string transaction;
        double newbalance;
        cin >> transaction;
        if (transaction == "1") {
            cout << "How much would you like to withdraw to your account?" << endl;
            int with;
            cin >> with;
            newbalance = myacc->withdraw(with);
            cout << "Your new balance is "<< newbalance << "$" << endl;
        }
        else if (transaction == "2") {
            cout << "How much would you like to deposit to your account?" << endl;
            int dep;
            cin >> dep;
            newbalance = myacc->deposit(dep);
            cout << "Your new balance is "<< newbalance << "$" << endl;
        }
        else if (transaction == "3") {
            newbalance = myacc->balanceinquiry();
            cout << "Your current account balance is "<< newbalance<< "$" << endl;
        }
        else {
            cout << "You typed the wrong number perhaps?" << endl;
        }

        Sleep(2000);
    }
    return 0;
}
