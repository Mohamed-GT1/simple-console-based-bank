#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include"MyLib.h"

using namespace std;

const string FILENAME = "clientData.txt";
const string DELIM = "#//#";
struct Client {
	string accountNumber;
	string pincode;
	string name;
	string phoneNumber;
	double balance;
	bool markForDelete = false;

};

enum MenuChoice {
	eShowAllClient = 1,
	eAddClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eTransactions =6,
	eExit = 7

};

enum TransactionMenu {
	Deposit =1,
	Withdraw =2,
	TotalBalance =3,
	Exit =4

};

void PrintClientCard(Client client);
void SaveUpdatedClientsToFile(vector<Client> clients);
vector <Client> LoadClientsFromFile(string fileName);


string ConvertClientToRecordString(Client client) {

	string recordString = "";

	recordString += client.accountNumber + DELIM
		+ client.pincode + DELIM
		+ client.name + DELIM
		+ client.phoneNumber + DELIM
		+ to_string(client.balance);

	return recordString;


}
bool CheckClientExist(string accountNumber) {

	vector<Client> clients = LoadClientsFromFile(FILENAME);
	for (const Client& c : clients) {
		if (c.accountNumber == accountNumber)
		{
			cout << "account number already exists for a client \n";
			return true;
			
		}
	}
	return false;

}

Client ReadClientData() {
	Client client;
	
	cout << "filling client data.. \n";
	do {
		cout << "\nenter Account number : ";
		getline(cin >> ws, client.accountNumber);
			
	} while (CheckClientExist(client.accountNumber));



	cout << "\nenter pincode : ";
	getline(cin, client.pincode);

	cout << "\nenter Name : ";
	getline(cin, client.name);

	cout << "\nenter phone number : ";
	getline(cin, client.phoneNumber);

	cout << "\nenter balance : ";
	cin >> client.balance;


	cout << endl;
	return client;


}

void SaveClientToFile(Client client, string fileName) {

	string recordString;
	recordString = ConvertClientToRecordString(client);

	fstream myFile;
	myFile.open(fileName, ios::out | ios::app);

	if (myFile.is_open()) {

		myFile << recordString << endl;

		cout << "successfully added \n";
		myFile.close();

	}


}

vector<string> SplitString(string text, string delim) {
	int pos;
	string word;
	vector<string> words;

	while ((pos = text.find(delim)) != string::npos) {

		word = text.substr(0, pos);
		words.push_back(word);
		text.erase(0, pos + delim.size());

	}

	if (text != "")
		words.push_back(text);

	return words;

}

Client ConvertRecordStringToClient(string text ) {

	Client client;

	vector<string> data = SplitString(text, DELIM);

	client.accountNumber = data[0];
	client.pincode = data[1];
	client.name = data[2];
	client.phoneNumber = data[3];
	client.balance = std::stod(data[4]);

	return client;



}



void AddClients(vector<Client> &clients) {

	char answer = 'n';
	Client client;

	do {
		system("cls");

		client = ReadClientData();
		SaveClientToFile(client,FILENAME);

		clients.push_back(client);
		
		cout << "do you want to add more clients ? [y] [n]\n";
		cin >> answer;

	} while (tolower(answer) == 'y');

	cout << "press any key to go back to main menu screen...";
	system("pause>0");


}

vector <Client> LoadClientsFromFile(string fileName) {

	vector<Client> clients;
	Client client;

	fstream myfile;
	myfile.open(fileName, ios::in);
	string line;

	if (myfile.is_open()) {

		while (getline(myfile, line)) {

			if (line != "") {
				client = ConvertRecordStringToClient(line);
				clients.push_back(client);
			}
		}

		myfile.close();

	}

	return clients;

}

void PrintClient(Client client) {

	cout << left << setw(15) << client.accountNumber << setw(2) << "|" << setw(8) << client.pincode << setw(2) << "|"
		<< setw(20) << client.name << setw(2) << "|" << setw(20) << client.phoneNumber << setw(2) << "|"
		<< setw(15) << client.balance << setw(2) << "|";


}

void ShowAllClients(const vector<Client> & clients) {

	 

	cout << "				list of (" << clients.size() << ") clients\n";
	cout << "---------------------------------------------------------------------------------------\n";
	cout << left << setw(15) << "account number" << setw(2) << "|" << setw(8) << "pincode" << setw(2) << "|"
		<< setw(20) << "Name" << setw(2) << "|" << setw(20) << "phone number" << setw(2) << "|"
		<< setw(15) << "balance" << setw(2) << "|";
	cout << "\n---------------------------------------------------------------------------------------\n";

	for (Client client : clients) {

		PrintClient(client);
		cout << endl;


	}
	cout << "---------------------------------------------------------------------------------------\n";

	cout << "press any key to go back to main menu screen...";
	system("pause>0");

}

void PrintClientCard(Client client) {
	cout << "---------------------------------------\n";
	cout << left << setw(15) << "account number" << " : " << client.accountNumber << endl
		<< setw(15) << "pincode" << " : " << client.pincode << endl
		<< setw(15) << "name" << " : " << client.name << endl
		<< setw(15) << "phone number" << " : " << client.phoneNumber << endl
		<< setw(15) << "balance" << " : " << client.balance << endl;
	cout << "---------------------------------------\n";



}

bool FindClientByAccountNumber(const vector<Client> &clients, string accountNumber,Client &client) {
	for (Client c : clients) {
		if (c.accountNumber == accountNumber)
		{
			client = c;
			return true;
		}
	}
	return false;


}

void FindAndPrintClient(const vector<Client> &clients) {

	string accountNumber = MyLib::ReadString("enter account number to find");
	Client client;
	if (FindClientByAccountNumber(clients, accountNumber, client)) {
		PrintClientCard(client);
	}
	else {
		cout << "\naccount not found\n";
		
	}

	cout << "press any key to go back to main menu screen...";
	system("pause>0");

}

void DeleteClient(vector<Client>& clients) {

	string accountNumber = MyLib::ReadString("enter account number to delete ");
	 
	char answer;
	Client client;
	if (FindClientByAccountNumber(clients, accountNumber, client)) {
		PrintClientCard(client);
		cout << "are you sure you want to delete the account ? [y] [n] ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {

			for (Client &c : clients) {
				if (c.accountNumber == accountNumber)
				{
					c.markForDelete = true;
					SaveUpdatedClientsToFile(clients);
					clients = LoadClientsFromFile(FILENAME);
					break;
				}
			}

		}
		else {
			cout << "\naccount not deleted\n";

		}

	}
	else {
		cout << "\naccount not found \n";

	}

	cout << "press any key to return to main menu...";
	system("pause>0");


}

void ChangeClientData(Client& client) {
	
	
	cout << "enter account pincode : ";
	cin >> client.pincode;
	cout << "\nenter Name : ";
	getline(cin >> ws, client.name);
	cout << "\nenter phone number : ";
	cin >> client.phoneNumber;
	cout << "\nenter balance : ";
	cin >> client.balance; 
	

}

void UpdateClient(vector<Client> &clients) {

	string accountNumber = MyLib::ReadString("enter account number to update ");

	
	Client client;
	char answer;

	if (FindClientByAccountNumber(clients, accountNumber, client)) {
		PrintClientCard(client);
		cout << "are you sure you want to update this client ? [y] [n]  ";
		cin >> answer;
		if (tolower(answer) == 'y') {
			for (Client& c : clients) {
				if (c.accountNumber == accountNumber) {
					ChangeClientData(c);
					SaveUpdatedClientsToFile(clients);
					break;
				}
			}

		}
		else {
			cout << "account not updated \n";
		}


	}
	else {
		cout << "account not found ";
	}

	cout << "enter anykey to go back to main menu ";
	system("pause>0");


}

void SaveUpdatedClientsToFile(vector<Client> clients) {
	fstream myfile;
	string recordString;
	myfile.open(FILENAME, ios::out);

	if (myfile.is_open())
	{
		for (Client client : clients) {

			if (client.markForDelete == false)
			{
				recordString = ConvertClientToRecordString(client);
				myfile << recordString << endl;
			}

		}
		myfile.close();
		cout << "\nfile updated\n";
	}


}



void ShowMainMenu() {

	cout << "=======================================\n";
	cout << "\tMAIN MENU \n";
	cout << "=======================================\n";
	cout << "\t" << "[1] Show all clients.\n";
	cout << "\t" << "[2] Add new client.\n";
	cout << "\t" << "[3] Delete client.\n";
	cout << "\t" << "[4] Update client.\n";
	cout << "\t" << "[5] Find client.\n";
	cout << "\t" << "[6] Transactions.\n";
	cout << "\t" << "[7] Exit.\n";
	cout << "=======================================\n";



}
void ShowTransactionMenu() {

	cout << "=======================================\n";
	cout << "\tTransaction Menu \n";
	cout << "=======================================\n";
	cout << "\t" << "[1] Deposit.\n";
	cout << "\t" << "[2] Withdraw.\n";
	cout << "\t" << "[3] Total Balances.\n";
	cout << "\t" << "[4] Exit.\n";
	cout << "=======================================\n";

}
void AddAmountToAccountBalance(vector<Client> & clients,string accountNumber,double amount) {

	for (Client& c : clients) {
		if (c.accountNumber == accountNumber) {
			c.balance += amount;
			SaveUpdatedClientsToFile(clients);
			cout << "successfully updated , the new balance : " << c.balance << endl;
			break;
		}
	}

}

void DepositAccount(vector<Client> &clients) {


	string accountNumber = MyLib::ReadString("enter account number : ");
	Client client;
	char answer;
	double amount;
	if (FindClientByAccountNumber(clients, accountNumber, client)) {
		PrintClientCard(client);
		cout << "enter deposit amount you want : ";
		cin >> amount;
		cout << "are you sure you want to deposit : " << amount << " ? [y] [n]\n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			AddAmountToAccountBalance(clients, accountNumber, amount);
		}
		else {
			cout << "balance not updated \n";

		}


	}
	else {
		cout << "account doesnt exist";
	}


	cout << "press any key to go back . . .";
	system("pause > nul");       

}

void WithdrawAccount(vector<Client>& clients) {
	string accountNumber = MyLib::ReadString("enter account number : ");
	Client client;
	char answer;
	double amount;
	if (FindClientByAccountNumber(clients, accountNumber, client)) {
		PrintClientCard(client);
		cout << "enter withdraw amount you want : ";
		cin >> amount;
		while (amount > client.balance) {
			cout << "amount exceeds the balance , you can withdraw up to : " << client.balance << endl;
			cin >> amount;
		}

		cout << "are you sure you want to withdraw : " << amount << " ? [y] [n]\n";
		cin >> answer;
		if (tolower(answer) == 'y') {
			AddAmountToAccountBalance(clients, accountNumber, -amount);
		}
		else {
			cout << "balance not updated \n";

		}


	}
	else {
		cout << "account doesnt exist";
	}

	cout << "press any key to go back . . .";
	system("pause > nul");

}
void ShowTotalBalances(vector<Client> &clients) {
	cout << "				list of (" << clients.size() << ") clients\n";
	cout << "-------------------------------------------------------\n";
	cout << left << setw(15) << "account number" << setw(2) << "|"
		<< setw(20) << "Name" << setw(2) << "|"
		<< setw(15) << "balance" << setw(2) << "|";
	cout << "\n-------------------------------------------------------\n";

	double total = 0;

	for (const Client &client : clients) {
		cout << left << setw(15) << client.accountNumber << setw(2) << "|"
			<< setw(20) << client.name << setw(2) << "|"
			<< setw(15) << client.balance << setw(2) << "|\n";
		total += client.balance;


	}
	cout << "-------------------------------------------------------\n";
	cout << "\t\ttotal balance : " << total<<endl;

	cout << "press any key to go back . . .";
	system("pause > nul");



}

void GoToTransactionsMenu(vector<Client> &clients) {

	TransactionMenu choice;
	
	do {
		system("cls");
		ShowTransactionMenu();
		choice = (TransactionMenu)MyLib::ReadNumberInRange("enter which transaction option you want to perfrom? 1-4", 1, 4);
		system("cls");
		switch (choice) {
		case TransactionMenu::Deposit :
			DepositAccount(clients);
			break;
		case TransactionMenu::Withdraw :
			WithdrawAccount(clients);
			break;
		case TransactionMenu::TotalBalance :
			ShowTotalBalances(clients);
			break;
		case TransactionMenu::Exit:
			return;

		}

	} while (choice!=TransactionMenu::Exit);
	

}

void PerformMainMenuOption(MenuChoice menuChoice ,vector<Client> &clients) {

	switch (menuChoice) {
	case MenuChoice::eShowAllClient:
		ShowAllClients(clients);
		break;
	case MenuChoice::eAddClient:
		AddClients(clients);
		break;
	case MenuChoice::eDeleteClient:
		DeleteClient(clients);
		break;
	case MenuChoice::eUpdateClient:
		UpdateClient(clients);
		break;
	case MenuChoice::eFindClient:
		FindAndPrintClient(clients);
		break;
	case MenuChoice::eTransactions:
		GoToTransactionsMenu(clients);
		break;
	case MenuChoice::eExit:
		system("cls");
		cout << "\nprogram ended\n";
		break;


	}



}


void StartBank() {
	

	
	MenuChoice menuChoice;
	vector<Client> clients = LoadClientsFromFile(FILENAME);
	
	do {
		system("cls");
		ShowMainMenu();

		menuChoice = (MenuChoice)MyLib::ReadNumberInRange("choose what service you want ? 1-7", 1, 7);
		system("cls");

		PerformMainMenuOption(menuChoice, clients);

		

	} while (menuChoice != MenuChoice::eExit);
	


}


int main() {

	StartBank();

	return 0;


}