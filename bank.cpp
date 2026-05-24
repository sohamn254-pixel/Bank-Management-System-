#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Account {
private:
    int accNo;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;

        cout << "Enter Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() const {
        cout << "\nAccount No: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    int getAccNo() const {
        return accNo;
    }

    void deposit(float amount) {
        balance += amount;
    }

    void withdraw(float amount) {
        if (amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient Balance!" << endl;
    }
};

void writeAccount() {
    Account acc;
    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    outFile.write(reinterpret_cast<char*>(&acc), sizeof(acc));
    outFile.close();

    cout << "Account Created Successfully!\n";
}

void displayAll() {
    Account acc;
    ifstream inFile("bank.dat", ios::binary);

    if (!inFile) {
        cout << "File not found!\n";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(acc))) {
        acc.showAccount();
        cout << "---------------------\n";
    }

    inFile.close();
}

void modifyAccount(int accNo, int option) {
    Account acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(acc)) && !found) {
        if (acc.getAccNo() == accNo) {

            acc.showAccount();

            float amt;
            cout << "Enter amount: ";
            cin >> amt;

            if (option == 1)
                acc.deposit(amt);
            else if (option == 2)
                acc.withdraw(amt);

            int pos = -1 * sizeof(acc);
            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&acc), sizeof(acc));

            cout << "Transaction Successful!\n";

            found = true;
        }
    }

    if (!found)
        cout << "Account not found!\n";

    file.close();
}

int main() {
    int choice, accNo;

    do {
        cout << "\n===== BANK MENU =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            writeAccount();
            break;

        case 2:
            displayAll();
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 1);
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 2);
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
