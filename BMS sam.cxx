/* This is a Bank Management System program that is capable of performing the following functions:
    1. Creating a new account
    2. Updating an existing account 
    3. Depositing into an account
    4. Withdrawing from an account
    5. Displaying all existing accounts
    6. Transfering money across accounts within a bank
    7. Removing an account
    */
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class BankAccount {
    string firstname;
    string lastname;
    float money_deposit;
    int account_no;
    int pin_code;
    
public:
    BankAccount() {}
    BankAccount(int acc, string fname, string lname, int pin, float money): 
        account_no(acc), firstname(fname), lastname(lname), pin_code(pin), money_deposit(money) {}
    
    void create_account();
    void update_account();
    void delete_account();
    void deposit_money();
    void debit_money();
    void transfer_money();
    void display_all_accounts();
};

void BankAccount::create_account()
{
    cout << "Enter your first name: ";
    cin >> firstname;
    cout << "Enter your last name: ";
    cin >> lastname;
    bool valid_input = false;
    while (!valid_input)
    {
        cout << "Enter your PIN code (4 digits): ";
        cin >> pin_code;
        if (cin.fail() || pin_code < 1000 || pin_code > 9999)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a 4-digit PIN code." << endl;
        }
        else {
            valid_input = true;
        }
    }
    
    ifstream infile("accounts.txt");
    int max_account_no = 0;
    string line;
    while (getline(infile, line)) {
        int accno;
        stringstream(line) >> accno;
        if (accno > max_account_no) {
            max_account_no = accno;
        }
    }
    infile.close();
    
    account_no = max_account_no + 1;
    money_deposit = 0;
    
    ofstream outfile;
    outfile.open("accounts.txt", ios::app);
    outfile << account_no << " " << firstname << " " << lastname << " " << pin_code << " " << money_deposit << endl;
    outfile.close();
    
    cout << "Account created successfully!\n\t\tFirst name: " << firstname << "\n\t\tLast name: " << lastname << "\n\t\tAccount number: " << account_no << "\n\t\tPin code: " << pin_code << "\n\t\tCurrent Balance: " << money_deposit << "\n\n";
}

void BankAccount::update_account()
{
    int account_number;
    cout << "Enter account number: ";
    cin >> account_number;
    
    int pin;
    cout << "Enter PIN code: ";
    cin >> pin;

    ifstream infile("accounts.txt");
    ofstream outfile("temp.txt");

    string line;
    bool found = false;
    while (getline(infile, line)) {
        int accno;
        float money_deposit;
        string fname, lname;

        stringstream(line) >> accno >> fname >> lname >> pin_code >> money_deposit;

        if (accno == account_number && pin_code == pin) {
            found = true;
            string new_firstname, new_lastname;
            int new_pin_code;
            

            cout << "Enter new first name: ";
            cin >> new_firstname;
            cout << "Enter new last name: ";
            cin >> new_lastname;
            bool valid_input = false;
            while (!valid_input)
            {
                cout << "Enter new PIN code (4 digits): ";
                cin >> new_pin_code;
                if (cin.fail() || new_pin_code < 1000 || new_pin_code > 9999)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a 4-digit PIN code." << endl;
                }
                else {
                    valid_input = true;
                }
            }

            outfile << accno << " " << new_firstname << " " << new_lastname << " " << new_pin_code << " " << money_deposit << endl;
        }
        else {
            outfile << accno << " " << fname << " " << lname << " " << pin_code << " " << money_deposit << endl;
        }
    }

    infile.close();
    outfile.close();

    if (found) {
        remove("accounts.txt");
        if (rename("temp.txt", "accounts.txt") != 0) {
            cerr << "Error renaming file" << endl;
        }
        cout << "Account updated successfully!" << endl;
    }
    else {
        remove("temp.txt");
        cout << "Account not found or PIN incorrect." << endl;
    }
}




void BankAccount::delete_account()
{
    int account_number;
    cout << "Enter account number: ";
    cin >> account_number;
    
    int pin;
    cout << "Enter PIN code: ";
    cin >> pin;

    ifstream infile("accounts.txt");
    ofstream outfile("temp.txt");

    string line;
    bool found = false;
    while (getline(infile, line)) {
        int accno;
        float money_deposit;
        string fname, lname;

        stringstream(line) >> accno >> fname >> lname >> pin_code >> money_deposit;

        if (accno == account_number && pin_code == pin) {
            found = true;
        }
        else {
            outfile << accno << " " << fname << " " << lname << " " << pin_code << " " << money_deposit << endl;
        }
    }

    infile.close();
    outfile.close();

    if (found) {
        remove("accounts.txt");
        if (rename("temp.txt", "accounts.txt") != 0) {
            cerr << "Error renaming file" << endl;
        }
        cout << "Account deleted successfully!" << endl;
    }
    else {
        remove("temp.txt");
        cout << "Account not found or PIN incorrect." << endl;
    }
}







void BankAccount::deposit_money() {
    float amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    if (cin.fail()||amount < 0) {
        cout << "Invalid amount." << endl;
        cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    int accno, pin;
    cout << "Enter account number: ";
    cin >> accno;
    cout << "Enter PIN code: ";
    cin >> pin;
    
    ifstream infile("accounts.txt");
    ofstream outfile("temp.txt");
    string line;
    bool found = false;
    while (getline(infile, line)) {
        int file_accno, file_pin;     
         float file_money_deposit;
        string fname, lname;

        stringstream(line) >> file_accno >> fname >> lname >> file_pin >> file_money_deposit;

        if (file_accno == accno && file_pin == pin) {
            found = true;
            file_money_deposit += amount;
            outfile << file_accno << " " << fname << " " << lname << " " << file_pin << " " << file_money_deposit << endl;
            money_deposit = file_money_deposit;
        }
        else {
            outfile << file_accno << " " << fname << " " << lname << " " << file_pin << " " << file_money_deposit << endl;
        }
    }

    infile.close();
    outfile.close();

    if (found) {
        remove("accounts.txt");
        if (rename("temp.txt", "accounts.txt") != 0) {
            cerr << "Error renaming file" << endl;
        }
        cout << "Deposit successful! New balance: " << money_deposit<< endl;
    }
    else {
        remove("temp.txt");
        cout << "Account not found or PIN incorrect." << endl;
    }
}




void BankAccount::debit_money() {
    float amount;
    cout << "Enter amount to debit: ";
    cin >> amount;
    if (amount < 0 || cin.fail()) {
        cout << "Invalid amount." << endl;
        cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    int accno, pin;
    cout << "Enter account number: ";
    cin >> accno;
    cout << "Enter PIN code: ";
    cin >> pin;
    
    bool found = false;
    ifstream infile("accounts.txt");
    ofstream outfile("temp.txt");
    string line;
    while (getline(infile, line)) {
        int file_accno, file_pin; 
        float file_money_deposit;
        string fname, lname;

        stringstream(line) >> file_accno >> fname >> lname >> file_pin >> file_money_deposit;

        if (file_accno == accno && file_pin == pin) {
            found = true;
            if (amount > file_money_deposit) {
                cout << "Insufficient balance. Debit amount exceeds current balance." << endl;
                outfile << file_accno << " " << fname << " " << lname << " " << file_pin << " " << file_money_deposit << endl;
            }
            else {
                file_money_deposit -= amount;
                outfile << file_accno << " " << fname << " " << lname << " " << file_pin << " " << file_money_deposit << endl;
                cout << "Debit successful! New balance: " << file_money_deposit << endl;
                money_deposit = file_money_deposit;
            }
        }
        else {
            outfile << file_accno << " " << fname << " " << lname << " " << file_pin << " " << file_money_deposit << endl;
        }
    }
    
    infile.close();
    outfile.close();

    if (found) {
        remove("accounts.txt");
        if (rename("temp.txt", "accounts.txt") != 0) {
            cerr << "Error renaming file" << endl;
        }
    } else {
        remove("temp.txt");
        cout << "Account not found or PIN incorrect." << endl;
    }
}



void BankAccount::display_all_accounts() {
    ifstream infile("accounts.txt");
    string line;
    cout << "Account No.\tFirst name\tLast name\tBalance" << endl;
    while (getline(infile, line)) {
        int accno, pin_code; 
        float money_deposit;
        string fname, lname;

        stringstream(line) >> accno >> fname >> lname >> pin_code >> money_deposit;

        cout << accno << "\t\t" << fname << "\t\t" << lname <<  "\t\t" <<  money_deposit << " BIRR" << endl;
    }
    infile.close();
} 



void BankAccount::transfer_money() {
    float amount;
    cout << "Enter amount to transfer: ";
    cin >> amount;
    if (amount < 0 || cin.fail()) {
        cout << "Invalid amount." << endl;
        cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    int accnoSender, pinSender, accnoReceiver;
    cout << "Enter your account number: ";
    cin >> accnoSender;
    cout << "Enter your PIN code: ";
    cin >> pinSender;

	cout << "Enter receiver account number: ";
    cin >> accnoReceiver;
    if (accnoSender == accnoReceiver) {
	   cout << "You can not transfer to yourself." << endl;
	   return;
	}
    bool foundSender = false;
    bool foundReceiver = false;
    bool found = false;
    
    ifstream infile("accounts.txt");
    ofstream outfile("temp.txt");
    string line;
	while(getline(infile, line)) {
		int accno, pin_code;
		float money_deposit;
        string fname, lname;

        stringstream(line) >> accno >> fname >> lname >> pin_code >> money_deposit;
		if(accnoSender == accno && pinSender == pin_code){
			foundSender = true;
			if(amount > money_deposit) {
			    cout << "Your balance is insufficient to perform the transaction." << endl;
			    return;
			}
		}
		if (accnoReceiver == accno) {
			foundReceiver = true;
		}	
	}
	if (foundSender && foundReceiver) {
		found = true;
	}
	infile.clear(); 
	infile.seekg(0, ios::beg);
    while(getline(infile, line) && found) {
		int accno, pin_code;
		float money_deposit;
        string fname, lname;
        stringstream(line) >> accno >> fname >> lname >> pin_code >> money_deposit;
		if(accnoSender == accno){
			money_deposit -= amount;
			outfile << accno << " " << fname << " " << lname << " " << pin_code << " " << money_deposit << endl;
			cout << "Money transfer successful! Current Balance: " << money_deposit << endl;
		}
		else if (accnoReceiver == accno) {
			money_deposit += amount;
			outfile << accno << " " << fname << " " << lname << " " << pin_code << " " << money_deposit << endl;
		}
		else {
			outfile << accno << " " << fname << " " << lname << " " << pin_code << " " << money_deposit << endl;	
		}
	}
	infile.close();
    outfile.close();

    if (found) {
        remove("accounts.txt");
        if (rename("temp.txt", "accounts.txt") != 0) {
            cerr << "Error renaming file" << endl;
        }
        
    } else {
	
        remove("temp.txt");
        if (!foundSender) {
        cout << "Sender account not found or PIN incorrect." << endl;
    	} else {
    	cout << "Receiver account not found or PIN incorrect." << endl;
		}
    }
	}
	

int main()
{
    BankAccount new_acc;
    cout << "\t\tBANK MANAGEMENT SYSTEM" << endl;
    cout << "\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    while(true) {
    cout << "\t\t    ::MAIN MENU::" << endl;
    cout << "\n\t\t1. Creat a New Bank Account" << endl;
    cout << "\n\t\t2. Update Existing Bank Account" << endl;
    cout << "\n\t\t3. Deposit Into Account" << endl;    
	cout << "\n\t\t4. Withdraw From Account" << endl;
	cout << "\n\t\t5. Display All Accounts" << endl;
    cout << "\n\t\t6. Transfer Money" << endl;
    cout << "\n\t\t7. Delete Account" << endl;
    cout << "\n\t\t8. Exit" << endl;
    cout << "\n\t\tSelection (1-8): ";
    int n;
    cin >> n;
        switch(n) {
        case 1:
            new_acc.create_account();
            break;
        case 2:
            new_acc.update_account();
            break;
        case 3: 
            new_acc.deposit_money();
            break;
		case 4: 
			new_acc.debit_money();
			break;
		case 5:
		    new_acc.display_all_accounts();
		    break;
		case 6:
			new_acc.transfer_money();
			break;
		case 7:
		    new_acc.delete_account();
		    break;
		case 8: 
			return 0;
        default:
            cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\tInvalid input." << endl;
        }
}
    return 0;
}

