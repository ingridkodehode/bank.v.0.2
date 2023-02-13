#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;



class account
{
	int accnr;
	char name[50];
	int deposit;
	char type;
public:
	void createAccount();           // creates account
	void showAccount() const;       // shows account data
	void modify();                  // function to add new data
	void dep(int);                  // deposits amount
	void draw(int);                 // withdraws amount
	void report() const;            // shows data in tab format
	int returnAccnr() const;        // return account number
	int returnDeposit() const;      // return balance
	char returnType() const;        // return type of account
};



void account::createAccount()
{
	cout << "\nPlease enter account number :";
	cin >> accnr;
	cout << "\n\nPlease enter name of account holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout << "\nWould you like a checking or savings account? (C/S) ";
	cin >> type;
	type=toupper(type);
	cout << "\nPlease enter amount to deposit : ";
	cin >> deposit;
	cout << "\n\n\nYour account has been created. Thank you for choosing Very Real Bank(tm)";
}



void account::showAccount() const
{
	cout << "\nAccount number : "<<accnr;
	cout << "\nAccount holder name : ";
	cout << name;
	cout << "\nType of account : "<<type;
	cout << "\nBalance : "<<deposit;
}



void account::modify()
{
	cout << "\nAccount number : "<<accnr;
	cout << "\nModify account holder name : ";
	cin.ignore();
	cin.getline(name,50);
	cout << "\nModify type of account : ";
	cin >> type;
	type=toupper(type);
	cout << "\nModify balance : ";
	cin >> deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout << accnr<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int account::returnAccnr() const
{
	return accnr;
}

int account::returnDeposit() const
{
	return deposit;
}

char account::returnType() const
{
	return type;
}


int bats()
{
    std::cout << R"(
    =/\                 /\=
    / \'._   (\_/)   _.'/ \       (_                   _)
   / .''._'--(o.o)--'_.''. \       /\                 /\
  /.' _/ |`'=/ " \='`| \_ `.\     / \'._   (\_/)   _.'/ \
 /` .' `\;-,'\___/',-;/` '. '\   /_.''._'--('.')--'_.''._\
/.-'       `\(-V-)/`       `-.\  | \_ / `;=/ " \=;` \ _/ |
             "   "               \/  `\__|`\___/`|__/`  \/
                                  `       \(/|\)/       `
                                           " ` "
)" << '\n';

    return 0;
}

void writeAccount();                // writes record in file
void displayBalance(int);           // display details given by user
void modifyAccount(int);            // modifies file
void deleteAccount(int);            // deletes file
void displayAll();                  // displays all account details
void depositWithdraw(int, int);     // deposit/withdraw given amount
void intro();                       // intro screen
void bats(int);


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t1. NEW ACCOUNT";
		cout << "\n\n\t2. DEPOSIT AMOUNT";
		cout << "\n\n\t3. WITHDRAW AMOUNT";
		cout << "\n\n\t4. BALANCE ENQUIRY";
		cout << "\n\n\t5. ACCOUNT HOLDER LIST";
		cout << "\n\n\t6. CLOSE AN ACCOUNT";
		cout << "\n\n\t7. MODIFY AN ACCOUNT";
		cout << "\n\n\t8. EXIT";
		cout << "\n\n\t9. BATS";
		cout << "\n\n\tPlease select your option (1-9) ";
		cin >> ch;
		system("cls");
		switch(ch)
		{
		case '1':
			writeAccount();
			break;
		case '2':
			cout << "\n\n\tEnter the account number : "; cin >> num;
			depositWithdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEnter the account number : "; cin >> num;
			depositWithdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEnter the account number : "; cin >> num;
			displayBalance(num);
			break;
		case '5':
			displayAll();
			break;
		case '6':
			cout << "\n\n\tEnter the account number : "; cin >> num;
			deleteAccount(num);
			break;
		 case '7':
			cout << "\n\n\tEnter the account number : "; cin >> num;
			modifyAccount(num);
			break;
		 case '8':
			cout << "\n\n\tThank you for using Very Real Bank(tm)";
			break;
		 default :cout << "\a";
		 case '9':
			bats();
			break;
		}
		cin.ignore();
		cin.get();
	}while(ch!='9');
	return 0;
}



void writeAccount()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.createAccount();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}



void displayBalance(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout << "File could not be opened. Press any key.";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.returnAccnr()==n)
		{
			ac.showAccount();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout << "\n\nAccount number does not exist.";
}




void modifyAccount(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout << "File could not be opened. Press any key.";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.returnAccnr()==n)
		{
			ac.showAccount();
			cout << "\n\nPlease enter new account information." << endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record updated.";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout << "\n\n Record Not Found.";
}




void deleteAccount(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout << "File could not be opened. Press any key.";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.returnAccnr()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout << "\n\n\tRecord Deleted.";
}



void displayAll()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout << "File could not be opened. Press any key.";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "Account nr.    Name       Type    Balance\n";
	cout << "====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}



void depositWithdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout << "File could not be opened. Press any key.";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.returnAccnr()==n)
		{
			ac.showAccount();
			if(option==1)
			{
				cout << "\n\n\tDeposit";
				cout << "\n\nPlease enter the amount to be deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout << "\n\n\tWithdraw";
				cout << "\n\nPlease enter the amount to be withdrawn";
				cin >> amt;
				int bal=ac.returnDeposit()-amt;
				if((bal<500 && ac.returnType()=='S') || (bal<1000 && ac.returnType()=='C'))
					cout << "Insufficient funds.";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated.";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout << "\n\n Record Not Found.";
}



void intro()
{
	cout << "\n\n\n\t  VERY";
	cout << "\n\n\t  REAL";
	cout << "\n\n\t  BANK(tm)";
	cout << "\n\n\n\nPlease press enter.";
	cin.get();
}
