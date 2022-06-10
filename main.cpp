#include <iostream>
#include <typeinfo>

#include "includes/Atm.h"

using namespace std;

string getErrorCode(int errorCode) {
  switch (errorCode) {
    case 400:
      return "Invalid input!";
    case 404:
      return "Perintah yang Anda masukkan tidak dikenali!";
    
    default:
      return "Unknown error!";
  }
}

int main() {
  ATM atm;

  atm.printHelp();

  string command;

  try {
    while (true) {
      cout << "Masukkan perintah yang ingin Anda lakukan: ";
      cin >> command;

      if (command == "exit") {
        cout << "Terima kasih telah menggunakan ATM Bersama." << endl;
        break;
      } else if (command == "1") {
        string name;
        int pin;
        cout << "Masukkan nama Anda: ";
        cin >> name;

        cout << "Masukkan PIN yang diinginkan: ";
        cin >> pin;

        if (pin < 100000 || pin > 999999) {
          throw 400;
        }

        atm.createAccount(name, pin);
        continue;
      } else if (command == "2") {
        int accountNumber;
        int pin;
        int amount;
        cout << "Masukkan nomor rekening Anda: ";
        cin >> accountNumber;

        if (accountNumber < 10000000 || accountNumber > 99999999) {
          throw 400;
        }

        cout << "Masukkan PIN Anda: ";
        cin >> pin;

        if (pin < 100000 || pin > 999999) {
          throw 400;
        }

        cout << "Masukkan jumlah uang yang ingin Anda setor: ";
        cin >> amount;

        if (amount < 1) {
          throw 400;
        }

        atm.deposit(amount, accountNumber, pin);

        continue;
      } else if (command == "3") {
        int accountNumber;
        int pin;
        int amount;
        cout << "Masukkan nomor rekening Anda: ";
        cin >> accountNumber;

        if (accountNumber < 10000000 || accountNumber > 99999999) {
          throw 400;
        }

        cout << "Masukkan PIN Anda: ";
        cin >> pin;

        if (pin < 100000 || pin > 999999) {
          throw 400;
        }

        cout << "Masukkan jumlah uang yang ingin Anda tarik: ";
        cin >> amount;

        if (amount < 1) {
          throw 400;
        }

        atm.withdraw(amount, accountNumber, pin);

        continue;
      } else if (command == "4") {
        int accountNumber;
        int pin;
        int amount;
        int receiverAccountNumber;
        cout << "Masukkan nomor rekening Anda: ";
        cin >> accountNumber;

        if (accountNumber < 10000000 || accountNumber > 99999999) {
          throw 400;
        }

        cout << "Masukkan PIN Anda: ";
        cin >> pin;

        if (pin < 100000 || pin > 999999) {
          throw 400;
        }

        cout << "Masukkan jumlah uang yang ingin Anda transfer: ";
        cin >> amount;

        if (amount < 1) {
          throw 400;
        }

        cout << "Masukkan nomor rekening tujuan: ";
        cin >> receiverAccountNumber;

        if (receiverAccountNumber < 10000000 || receiverAccountNumber > 99999999) {
          throw 400;
        }

        atm.transfer(amount, accountNumber, pin, receiverAccountNumber);

        continue;
      } else if (command == "5") {
        int accountNumber;
        int pin;
        cout << "Masukkan nomor rekening Anda: ";
        cin >> accountNumber;

        if (accountNumber < 10000000 || accountNumber > 99999999) {
          throw 400;
        }

        cout << "Masukkan PIN Anda: ";
        cin >> pin;

        if (pin < 100000 || pin > 999999) {
          throw 400;
        }

        int balance = atm.getBalance(accountNumber, pin);

        if (balance == -1) {
          cout << "Nomor rekening atau PIN yang Anda masukkan salah." << endl;
        } else {
          cout << "Saldo yang tersedia pada rekening Anda: " << endl << "\tRp. " << atm.formatNumber(balance) << endl;
        }

        continue;
      } else if (command == "6") {
        int accountNumber;
        int pin;
        int newPin;

        cout << "Masukkan nomor rekening Anda: ";
        cin >> accountNumber;

        if (accountNumber < 10000000 || accountNumber > 99999999) {
          throw 400;
        }

        cout << "Masukkan PIN Anda: ";
        cin >> pin;

        if (pin < 100000 || pin > 999999) {
          throw 400;
        }
        
        cout << "Masukkan PIN baru Anda: ";
        cin >> newPin;

        if (newPin < 100000 || newPin > 999999) {
          cout << "PIN harus berupa angka 6 digit!" << endl;
          continue;
        }

        atm.changePin(accountNumber, pin, newPin);

        continue;
      } else if (command == "help") {
        atm.printHelp();
        continue;
      } else {
        throw 404;
      }
    }
  } catch (int e) {
    cout << getErrorCode(e) << endl;
  }
  return 0;
}