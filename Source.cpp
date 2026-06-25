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

void PrintClientCard(Client client);
void SaveUpdatedClientsToFile(vector<Client> clients);


string ConvertClientToRecordString(Client client) {

	string recordString = "";

	recordString += client.accountNumber + DELIM
		+ client.pincode + DELIM
		+ client.name + DELIM
		+ client.phoneNumber + DELIM
		+ to_string(client.balance);

	return recordString;


}

Client ReadClientData() {
	Client client;
	
	cout << "filling client data.. \n";

	cout << "\nenter Account number : ";
	getline(cin >> ws,client.accountNumber);

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
	system("pause");


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

	//cout << "press any key to go back to main menu screen...";
	system("pause");

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
	system("pause");

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
	system("pause");


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
					cout << "updated successfully \n";
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
	system("pause");


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
	cout << "\t" << "[6] Exit.\n";
	cout << "=======================================\n";



}

void StartBank() {
	

	int number;
	vector<Client> clients = LoadClientsFromFile(FILENAME);
	
	do {
		system("cls");
		ShowMainMenu();
		number = MyLib::ReadNumberInRange("choose what service you want ? 1-6", 1, 6);
		system("cls");

		switch (number) {
		case 1:
			ShowAllClients(clients);
			break;
		case 2:
			AddClients(clients);
			break;
		case 3:
			DeleteClient(clients);
			break;
		case 4:
			UpdateClient(clients);
			break;
		case 5:
			FindAndPrintClient(clients);
			break;
		case 6:
			system("cls");
			cout << "\nprogram ended\n";
			break;


		}

	} while (number != 6);
	


}


int main() {

	StartBank();

	return 0;


}