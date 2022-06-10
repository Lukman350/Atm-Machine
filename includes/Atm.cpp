#include "Atm.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <string>

using namespace std;

int random(int min, int max) {
  static bool first = true;
  if (first) {
    srand(time(NULL));
    first = false;
  }
  return min + rand() % ((max + 1) - min);
}

ATM::ATM() {
  balance = 0;
  accountNumber = 0;
  pin = 0;
  name = "";
}

void ATM::createAccount(string name, int pin) {
  int accNumber = random(10000000, 99999999);

  try {
    if (isAccountRegistered(accNumber))
      throw 400;
    else {
      this->name = name;
      this->pin = pin;
      this->accountNumber = accNumber;
      this->balance = 0;

      ofstream accountFile;
      accountFile.open("accounts/"+to_string(accountNumber)+".txt");
      accountFile << this->name << endl << this->balance << endl << this->accountNumber << endl << this->pin;
      accountFile.close();

      cout << "Akun berhasil dibuat, dengan data sebagai berikut: " << endl;
      cout << "Nama: " << this->name << endl;
      cout << "Saldo: " << this->balance << endl;
      cout << "Nomor Rekening: " << this->accountNumber << endl;
      cout << "PIN: " << this->pin << endl;
    }
  } catch(...) {
    cout << "Akun sudah terdaftar, silahkan coba lagi." << endl;
  }
}

int ATM::getBalance(int accountNumber, int pin) {
  if (this->accountNumber == accountNumber && this->pin == pin) {
    return this->balance;
  }
  else {
    if (isAccountRegistered(accountNumber)) {
      if (getPinFromFile(accountNumber) == pin) {
        int balance = getBalanceFromFile(accountNumber);
        return balance;
      }
      else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

int ATM::getBalanceFromFile(int accountNumber) {
  ifstream file;
  file.open("accounts/"+to_string(accountNumber)+".txt");

  string line[4];

  for (int i = 0; i < 4; i++) {
    getline(file, line[i]);
  }
  
  file.close();
  return stoi(line[1]);
}

string ATM::getNameFromFile(int accountNumber) {
  ifstream file;
  file.open("accounts/"+to_string(accountNumber)+".txt");

  string line[4];

  for (int i = 0; i < 4; i++) {
    getline(file, line[i]);
  }
  
  file.close();
  return line[0];
}

int ATM::getPinFromFile(int accountNumber) {
  ifstream file;
  file.open("accounts/"+to_string(accountNumber)+".txt");

  string line[4];

  for (int i = 0; i < 4; i++) {
    getline(file, line[i]);
  }
  
  file.close();
  return stoi(line[3]);
}

void ATM::setPinToFile(int accountNumber, int newPin) {
  string name = getNameFromFile(accountNumber);
  int balance = getBalanceFromFile(accountNumber);

  ofstream file;

  file.open("accounts/"+to_string(accountNumber)+".txt");

  file << name << endl << balance << endl << accountNumber << endl << newPin;

  file.close();
}

void ATM::setBalance(int balance, int accountNumber, int pin) {
  if (this->accountNumber == accountNumber && this->pin == pin) {
    this->balance = balance;

    saveAccount(accountNumber);
  } else {
    if (isAccountRegistered(accountNumber)) {
      if (getPinFromFile(accountNumber) == pin) {
        int blc = getBalanceFromFile(accountNumber);
        blc = balance;
        setBalanceToFile(blc, accountNumber);
      }
      else {
        cout << "PIN salah, silahkan coba lagi." << endl;
      }
    } else {
      cout << "No. Rekening atau pin yang dimasukkan tidak terdaftar." << endl;
    }
  }
}

void ATM::setBalanceToFile(int balance, int accountNumber) {
  string name = getNameFromFile(accountNumber);
  int pin = getPinFromFile(accountNumber);

  ofstream file;
  file.open("accounts/"+to_string(accountNumber)+".txt");

  file << name << endl << balance << endl << accountNumber << endl << pin;

  file.close();
}

void ATM::deposit(int amount, int accountNumber, int pin) {
  if (this->accountNumber == accountNumber && this->pin == pin) {
    this->balance += amount;

    saveAccount(accountNumber);

    cout << "Kamu telah setor tunai sejumlah Rp. " << formatNumber(amount) << endl;
    cout << "Saldo anda sekarang adalah Rp. " << formatNumber(balance) << endl;
  } else {
    if (isAccountRegistered(accountNumber)) {
      if (getPinFromFile(accountNumber) == pin) {
        int blc = getBalanceFromFile(accountNumber);
        blc += amount;

        setBalanceToFile(blc, accountNumber);

        cout << "Kamu telah setor tunai sejumlah Rp. " << formatNumber(amount) << endl;
        cout << "Saldo anda sekarang adalah Rp. " << formatNumber(blc) << endl;
      }
      else {
        cout << "PIN salah, silahkan coba lagi." << endl;
      }
    } else {
      cout << "No. Rekening atau pin yang dimasukkan tidak terdaftar." << endl;
    }
  }
}

void ATM::withdraw(int amount, int accountNumber, int pin) {
  if (this->accountNumber == accountNumber && this->pin == pin) {
    if (this->balance < amount) {
      cout << "Saldo anda tidak mencukupi untuk melakukan penarikan sebanyak itu." << endl;
    } else {
      this->balance -= amount;

      saveAccount(accountNumber);

      cout << "Kamu telah menarik tunai sejumlah Rp. " << formatNumber(amount) << endl;
      cout << "Saldo anda sekarang adalah Rp. " << formatNumber(this->balance) << endl;
    }
  } else {
    if (isAccountRegistered(accountNumber)) {
      if (getPinFromFile(accountNumber) == pin) {
        int blc = getBalanceFromFile(accountNumber);

        if (blc < amount) {
          cout << "Saldo anda tidak mencukupi untuk melakukan penarikan sebanyak itu." << endl;
        } else {
          blc -= amount;
          setBalanceToFile(blc, accountNumber);

          cout << "Kamu telah menarik tunai sejumlah Rp. " << formatNumber(amount) << endl;
          cout << "Saldo anda sekarang adalah Rp. " << formatNumber(blc) << endl;
        }
      }
      else {
        cout << "PIN salah, silahkan coba lagi." << endl;
      }
    } else {
      cout << "No. Rekening atau pin yang dimasukkan tidak terdaftar." << endl;
    }
  }
}

void ATM::printBalance(int accountNumber, int pin) {
  if (this->accountNumber == accountNumber && this->pin == pin) {
    cout << "Saldo pada rekening anda adalah Rp. " << formatNumber(this->balance) << endl;
  } else {
    if (isAccountRegistered(accountNumber)) {
      if (getPinFromFile(accountNumber) == pin) {
        int blc = getBalanceFromFile(accountNumber);

        cout << "Saldo pada rekening anda adalah Rp. " << formatNumber(blc) << endl;
      }
      else {
        cout << "PIN salah, silahkan coba lagi." << endl;
      }
    } else {
      cout << "No. Rekening atau pin yang dimasukkan tidak terdaftar." << endl;
    }
  }
}

void ATM::transfer(int amount, int accountNumber, int pin, int receiverAccountNumber) {
  if (this->accountNumber == accountNumber && this->pin == pin) {
    if (this->balance < amount) {
      cout << "Saldo anda tidak mencukupi untuk melakukan transfer sebanyak itu." << endl;
    } else {
      if (accountNumber == receiverAccountNumber) {
        cout << "Tidak dapat melakukan transfer ke rekening yang sama." << endl;
      } else {
        if (isAccountRegistered(receiverAccountNumber)) {
          this->balance -= amount;
          saveAccount(accountNumber);
          
          int blc = getBalanceFromFile(receiverAccountNumber);
          blc += amount;

          setBalanceToFile(blc, receiverAccountNumber);

          cout << "Kamu telah mentransfer uang sejumlah Rp. " << formatNumber(amount) << " ke rekening " << receiverAccountNumber << endl;
          cout << "Saldo anda sekarang adalah Rp. " << formatNumber(balance) << endl;
        } else {
          cout << "Rekening tujuan tidak terdaftar." << endl;
        }
      }
    }
  } else {
    if (isAccountRegistered(accountNumber)) {
      if (getPinFromFile(accountNumber) == pin) {
        int blc = getBalanceFromFile(accountNumber);

        if (blc < amount) {
          cout << "Saldo anda tidak mencukupi untuk melakukan transfer sebanyak itu." << endl;
        } else {
          if (accountNumber == receiverAccountNumber) {
            cout << "Tidak dapat melakukan transfer ke rekening yang sama." << endl;
          } else {
            if (isAccountRegistered(receiverAccountNumber)) {
              blc -= amount;

              setBalanceToFile(blc, accountNumber);

              int blcReceiver = getBalanceFromFile(receiverAccountNumber);
              blcReceiver += amount;

              setBalanceToFile(blcReceiver, receiverAccountNumber);

              cout << "Kamu telah mentransfer uang sejumlah Rp. " << formatNumber(amount) << " ke rekening " << receiverAccountNumber << endl;
              cout << "Saldo anda sekarang adalah Rp. " << formatNumber(blc) << endl;
            } else {
              cout << "Rekening tujuan tidak terdaftar." << endl;
            }
          }
        }
      }
      else {
        cout << "PIN salah, silahkan coba lagi." << endl;
      }
    } else {
      cout << "No. Rekening atau pin yang dimasukkan tidak terdaftar." << endl;
    }
  }
}

void ATM::saveAccount(int accountNumber) {
  string name = this->name;
  int pin = this->pin;
  int balance = this->balance;

  ofstream file;
  file.open("accounts/"+to_string(accountNumber)+".txt");

  file << name << endl << balance << endl << accountNumber << endl << pin;

  file.close();
}

bool ATM::isAccountRegistered(int accountNumber) {
  ifstream file("accounts/"+to_string(accountNumber)+".txt");

  if (file.is_open()) {
    return true;
  } else {
    return false;
  }
}

void ATM::printHelp() {
  cout << "===========================================================" << endl;
  cout << "|           --> Selamat Datang di ATM Bersama <--         |" << endl;
  cout << "|                                                         |" << endl;
  cout << "|  Berikut adalah perintah-perintah yang tersedia:        |" << endl;
  cout << "|                                                         |" << endl;
  cout << "|  Ketik \"1\" untuk membuat rekening baru                |" << endl;
  cout << "|  Ketik \"2\" untuk setor tunai ke rekening              |" << endl;
  cout << "|  Ketik \"3\" untuk tarik tunai dari rekening            |" << endl;
  cout << "|  Ketik \"4\" untuk transfer ke rekening lain            |" << endl;
  cout << "|  Ketik \"5\" untuk mengecek saldo pada rekening         |" << endl;
  cout << "|  Ketik \"6\" untuk mengganti PIN                        |" << endl;
  cout << "|  Ketik \"exit\" untuk keluar dari ATM                   |" << endl;
  cout << "|  Ketik \"help\" untuk menampilkan pesan ini             |" << endl;
  cout << "|                                                         |" << endl;
  cout << "|                               Dibuat pada: 10 Juni 2022 |" << endl;
  cout << "|                         Terakhir diupdate: 10 Juni 2022 |" << endl;
  cout << "|                                     Dibuat oleh: Lukman |" << endl;
  cout << "===========================================================" << endl;
}

void ATM::changePin(int accountNumber, int oldPin, int newPin) {
  if (this->accountNumber == accountNumber && this->pin == oldPin) {
    this->pin = newPin;
    saveAccount(accountNumber);
    cout << "PIN anda telah berhasil diganti." << endl;
  } else {
    if (isAccountRegistered(accountNumber)) {
      if (getPinFromFile(accountNumber) == oldPin) {
        this->pin = newPin;
        setPinToFile(accountNumber, newPin);

        cout << "PIN anda telah berhasil diganti." << endl;
      } else {
        cout << "PIN lama salah, silahkan coba lagi." << endl;
      }
    } else {
      cout << "No. Rekening atau pin yang dimasukkan tidak terdaftar." << endl;
    }
  }
}

string ATM::formatNumber(int number) {
  string result = to_string(number);
  int length = result.length();

  if (length > 3) {
    for (int i = length - 3; i > 0; i -= 3) {
      result.insert(i, ".");
    }
  }

  return result;
}