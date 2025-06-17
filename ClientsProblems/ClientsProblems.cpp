#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const string fileName = "clientsList.txt";

struct stClient {
	string accNum;
	string name;
	string pinCode;
	string phone;
	double balance;
	bool mark = false;
};

enum enChoice {
	showClients = 1, addClient = 2, deleteClient = 3,
	updateClient = 4, findClient = 5,transactionMenu = 6, Exit = 7
};

enum enTransaction {
	deposit = 1, withdraw = 2, totalBalances = 3, backToMain = 4
};

vector<string> Split(string str, string delm = "#//#") {

	vector<string> words;
	string word;
	short pos = 0;

	while ((pos = str.find(delm)) != string::npos) {
		word = str.substr(0, pos);
		if (word != " ") {
			words.push_back(word);
		}
		str.erase(0, pos + delm.length());
	}
	if (str != " ") {
		words.push_back(str);
	}

	return words;

}

stClient ConvertLineToRecord(string str, string delm = "#//#") {
	
	stClient client;
	vector<string> lines = Split(str, delm);

	if (lines.size() == 5) {
		client.accNum = lines[0];
		client.pinCode = lines[1];
		client.name = lines[2];
		client.phone = lines[3];
		client.balance = stod(lines[4]);
	}
	else {
		cerr << "Error: Invalid data format in file!" << endl;
	}
	return client;

}

string ConvertRecordToLine(stClient client, string delm = "#//#") {

	string line = "";

	line += client.accNum + delm + client.pinCode + delm + client.name+ delm 
		+ client.phone + delm + to_string(client.balance);

	return line;

}

vector<stClient> LoadDataFromFile(string file_name) {

	vector<stClient> clients;

	fstream MyFile;
	MyFile.open(file_name, ios::in);

	if (MyFile.is_open()) {

		string line;
		stClient client;

		while (getline(MyFile, line)) {
			client = ConvertLineToRecord(line);
			clients.push_back(client);
		}

		MyFile.close();

	}

	return clients;

}

bool SearchClientFromAccNum(string accNum, stClient& client, vector<stClient> clients) {

	for (stClient& c : clients) {
		if (c.accNum == accNum) {
			client = c;
			return true;
		}
	}
	return false;

}


void SaveDataToFile(string file_name, vector<stClient>& clients) {
	
	fstream MyFile;
	MyFile.open(file_name, ios::out);

	if (MyFile.is_open()) {

		string line;

		for (stClient c : clients) {

			if (c.mark == false) {
				line = ConvertRecordToLine(c);
				MyFile << line << endl;
			}

		}

		MyFile.close();
	}


}

string ReadAccNumber() {
	string accNum;
	cout << "Enter Account Number: ";
	cin >> accNum;
	return accNum;
}


void ShowMenue() {

	system("cls");
	cout << "===========================================================\n";
	cout << setw(34) << "\t\tMain Menue" << endl;
	cout << "===========================================================\n";
	cout << "\t\t  [1] Show Client List." << endl;
	cout << "\t\t  [2] Add New Client." << endl;
	cout << "\t\t  [3] Delete Client." << endl;
	cout << "\t\t  [4] Update Client Info." << endl;
	cout << "\t\t  [5] Find Client." << endl;
	cout << "\t\t  [6] Tarnsaction menu screen." << endl;
	cout << "\t\t  [7] Exit." << endl;
	cout << "===========================================================\n";

}

void PrintClientCard(stClient client) {

	system("cls");
	cout << "===========================================================\n";
	cout << setw(40) << "Client Info" << endl;
	cout << "===========================================================\n";
	cout << "Account Number: " << client.accNum << endl;
	cout << "Pin Code: " << client.pinCode << endl;
	cout << "Name: " << client.name << endl;
	cout << "Phone Number: " << client.phone << endl;
	cout << "Balance: " << client.balance << endl;
	cout << "===========================================================\n";

}

short ReadNum(int n) {
	short num;
	cout << "Choose what do you want to do? [1 - " << n << "]\nYour Choice : ";
	cin >> num;
	return num;
}

enTransaction ChoiceTransaction() {

	short num = ReadNum(4);

	switch (num) {
	case 1: 
		return enTransaction::deposit;

	case 2: 
		return enTransaction::withdraw;

	case 3:
		return enTransaction::totalBalances;

	case 4: 
		return enTransaction::backToMain;

	default:
		cout << "Wrong number, please try again.\n";
		return ChoiceTransaction();

	}
}


enChoice ChoiceNum() {

	short num = ReadNum(7);

	switch (num) {

	case 1:
		return enChoice::showClients;

	case 2:
		return enChoice::addClient;

	case 3:
		return enChoice::deleteClient;

	case 4:
		return enChoice::updateClient;

	case 5:
		return enChoice::findClient;

	case 6:
		return enChoice::transactionMenu;

	case 7: 
		return enChoice::Exit;

	default :
		cout << "Wrong number, please try again.\n";
		return ChoiceNum();
	}
}

void PrintClientRecordLine(stClient Client)
{
	cout << "| " << setw(15) << left << Client.accNum;
	cout << "| " << setw(10) << left << Client.pinCode;
	cout << "| " << setw(40) << left << Client.name;
	cout << "| " << setw(12) << left << Client.phone;
	cout << "| " << setw(12) << left << Client.balance;
}


void ShowClientList(vector <stClient> Clients)
{
	if (Clients.empty()) {
		cout << "\nNo Clients Available In the System!\n";
		return;
	}

	cout << "\n\t\t\t\t\tClient List (" << Clients.size() << ") Client(s).";
		cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<	 "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (Clients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (stClient Client : Clients)
		{
			PrintClientRecordLine(Client);
			cout << endl;
		}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

stClient ReadClientInfo() {

	system("cls");

	stClient client;

	string accNum;;
	cout << "Enter Account Number: ";
	getline(cin >> ws, accNum);
	if (SearchClientFromAccNum(accNum, client, LoadDataFromFile(fileName))) {
		cout << "This Account Number is already exist.\n";
		return ReadClientInfo();
	}
	client.accNum = accNum;

	cout << "Enter Pin Code: ";
	getline(cin, client.pinCode);

	cout << "Enter Name: ";
	getline(cin, client.name);

	cout << "Enter Phone Number: ";
	getline(cin, client.phone);

	cout << "Enter Balance: ";
	cin >> client.balance;
	return client;

}

void AddNewClient(vector<stClient> clients) {

	stClient client = ReadClientInfo();
	
	cout << "Are You Sure You Want to Add This Client? [Y/N]\n";
	char choice;
	cin >> choice;

	if (choice == 'Y' || choice == 'y') {

		clients.push_back(client);
		SaveDataToFile(fileName, clients);

		cout << "Client Added Successfully.\n";

	}

	else
	{
		cout << "Client Not Added.\n";
	}

}

bool MarkClient(string accNum, vector<stClient>& clients) {
	
	
	for (stClient& c : clients) {
		if (c.accNum == accNum) {
			c.mark = true;
			return true;
		}
	}
	return false;
}

bool DeleteClient(string accNum, vector<stClient>& clients) {

	stClient client;

	if (SearchClientFromAccNum(accNum, client, clients)) {

		PrintClientCard(client);
		cout << "Are You Sure You Want to Delete This Client? [Y/N]\n";
		char ch;
		cin >> ch;

		if (ch == 'Y' || ch == 'y') {

			MarkClient(accNum, clients);
			SaveDataToFile(fileName, clients);

			clients = LoadDataFromFile(fileName);

			cout << "Client Deleted Successfully.\n";
			return true;

		}
		
	}
	else {
		cout << "Client Not Found.\n";
		return false;
	}


}

stClient ChangeClientRecord(string accNum) {

	stClient client;

	client.accNum = accNum;

	cout << "Enter New Pin Code: ";
	getline(cin >> ws, client.pinCode);

	cout << "Enter New Name: ";
	getline(cin, client.name);

	cout << "Enter New Phone Number: ";
	getline(cin, client.phone);

	cout << "Enter New Balance: ";
	cin >> client.balance;

	return client;

}

bool UpdateClient(string accNum, vector<stClient>& clients) {

	stClient client;
	char ch = 'n';

	if (SearchClientFromAccNum(accNum, client, clients)) {

		PrintClientCard(client);
		cout << "Are You Sure You Want to Update This Client? [Y/N]\n";
		cin >> ch;

		if (ch == 'Y' || ch == 'y') {
			for (stClient& c : clients) {
				if (c.accNum == accNum) {
					c = ChangeClientRecord(accNum);
					break;
				}
			}

		}
		SaveDataToFile(fileName, clients);
		cout << "Client Updated Successfully.\n";
		return true;
	}
	else {
		cout << "Client Not Found.\n";
		return false;
	}

	system("pause");

}

void FindClient(string accNum, vector<stClient> clients) {

	stClient client;

	if (SearchClientFromAccNum(accNum, client, clients)) {
		PrintClientCard(client);
	}
	else {
		cout << "Client Not Found.\n";
	}

}


bool DepositBalanceToClientByAccountNumber(double amount, vector<stClient>& clients, string accNum) {

	char ch = 'n';
	cout << "Are You Sure You Want to perform this transaction? [Y/N]\n";
	cin >> ch;

	if (ch == 'Y' || ch == 'y') {

		for (stClient& c : clients) {
			if (accNum == c.accNum) {
				c.balance += amount;
				SaveDataToFile(fileName, clients);
				cout << "\n\nDone Successfully. New balance is: "
					<< c.balance;
				return true;
			}
		}
		return false;
	}

}



void Deposit(string accNum, vector<stClient> clients) {

	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";

	stClient client;
	double amount;

	if (SearchClientFromAccNum(accNum, client, clients)) {
		
		cout << "This is the client info: \n";
		PrintClientCard(client);

		cout << "Enter Amount to Deposit: ";
		cin >> amount;
		DepositBalanceToClientByAccountNumber(amount, clients, accNum);
	}
	else {
		cout << "Client Not Found.\n";
	}

}

void Withdraw(string accNum, vector<stClient> clients) {

	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";

	stClient client;
	double amount;

	if (SearchClientFromAccNum(accNum, client, clients)) {

		cout << "This is the client info: \n";
		PrintClientCard(client);

		cout << "Enter Amount to Withdraw: ";
		bool flag;
		do {
			flag = true;
			cin >> amount;
			if (amount > client.balance) {
				cout << "Sorry, You Don't Have Enough Balance.\n"
					<< "Please enter a valid amount.\n";
				flag = false;
			}
		} while (flag == false);
		DepositBalanceToClientByAccountNumber(amount * -1, clients, accNum);
	}
	else {
		cout << "Client Not Found.\n";
	}
}

void PrintClientRecordBalanceLine(stClient Client)
{
	cout << "| " << setw(15) << left << Client.accNum;
	cout << "| " << setw(40) << left << Client.name;
	cout << "| " << setw(12) << left << Client.balance;
}

void ShowTotalBalances(vector<stClient> clients){

	cout << "\n\t\t\t\t\tBalances List (" << clients.size() << ") Client(s).";
		cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double TotalBalances = 0;
	if (clients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (stClient Client : clients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.balance;
			cout << endl;
		}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}

void BackToMain() {
	ShowMenue();
}

void ShowTransactionRes(enTransaction choice){

	vector<stClient> clients = LoadDataFromFile(fileName);
	string accNum;

	switch (choice) {

	case enTransaction::deposit:
		system("cls");
		accNum = ReadAccNumber();
		Deposit(accNum, clients);
		break;

	case enTransaction::withdraw:
		system("cls");
		accNum = ReadAccNumber();
		Withdraw(accNum, clients);
		break;

	case enTransaction::totalBalances:
		system("cls");
		ShowTotalBalances(clients);
		break;

	case enTransaction::backToMain:
		system("cls");
		BackToMain();
		break;

	default:
		cout << "Wrong Choice.\n";
		cout << "Press any key to go back to transaction menu.\n";
		system("pause > 1");

	}

}

void ShowTransactionMenue() {

	system("cls");
	cout << "===========================================================\n";
	cout << setw(34) << "\tTransaction Menue" << endl;
	cout << "===========================================================\n";
	cout << "\t\t  [1] Deposit." << endl;
	cout << "\t\t  [2] Withdraw." << endl;
	cout << "\t\t  [3] Total Balances." << endl;
	cout << "\t\t  [4-] Main Menue." << endl;
	cout << "===========================================================\n";

	enTransaction choice = ChoiceTransaction();
	ShowTransactionRes(choice);


}

void ShowResults(enChoice choice) {

	vector<stClient> clients = LoadDataFromFile(fileName);
	string accNum;

	switch (choice) {

	case enChoice::showClients:
		ShowClientList(clients);
		break;

	case enChoice::addClient:
		AddNewClient(clients);
		break;

	case enChoice::deleteClient:
		accNum = ReadAccNumber();
		DeleteClient(accNum,clients);
		break;

	case enChoice::updateClient:
		accNum = ReadAccNumber();
		UpdateClient(accNum, clients);
		break;

	case enChoice::findClient:
		accNum = ReadAccNumber();
		FindClient(accNum, clients);
		break;

	case enChoice::transactionMenu:
		ShowTransactionMenue();
		break;

	default:
		cout << "Wrong Choice.\n";
	}

}



void ShowEndScreen()
{
	cout << "\n-------------------------------------------------------------------\n";
	cout << "\tProgram Ends, and your life nah nah nah :-)";
	cout << "\n-------------------------------------------------------------------\n";
}

void BankStart() {

	enChoice choice;

	do {

		system("cls");

		ShowMenue();
		choice = ChoiceNum();

		system("cls");

		if (choice == enChoice::Exit) break;

		ShowResults(choice);

		cout << "Press any key to go back to menu.\n";
		system("pause > 1");

	} while (true);

	ShowEndScreen();

}


int main() {


	BankStart();

	return 0;
}