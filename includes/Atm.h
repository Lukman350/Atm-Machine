#ifndef ATM_H
#define ATM_H

#include <string>
using namespace std;

class ATM {
  public:
    ATM();
    void createAccount(string name, int pin);
    int getBalance(int accountNumber, int pin);
    int getBalanceFromFile(int accountNumber);
    string getNameFromFile(int accountNumber);
    int getPinFromFile(int accountNumber);
    void setPinToFile(int accountNumber, int newPin);
    void setBalance(int balance, int accountNumber, int pin);
    void setBalanceToFile(int balance, int accountNumber);
    void deposit(int amount, int accountNumber, int pin);
    void withdraw(int amount, int accountNumber, int pin);
    void printBalance(int accountNumber, int pin);
    void transfer(int amount, int accountNumber, int pin, int receiverAccountNumber);
    void saveAccount(int accountNumber);
    bool isAccountRegistered(int accountNumber);
    void printHelp();
    void changePin(int accountNumber, int oldPin, int newPin);
    string formatNumber(int number);
  
  private:
    int balance;
    int accountNumber, pin;
    string name;
};

#endif