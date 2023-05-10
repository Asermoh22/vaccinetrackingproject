#pragma warning(disable : 4996)
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_map>
#include <string.h>
#include "user.h"
#include "Admin.h"
#include <fstream>
#include<algorithm>
using namespace std;
deque<user>UserQueue;
unordered_map<string, Admin>AdminTable;
unordered_map<string, user>UserTable;
user selectedUser = user();
Admin currentAdmin = Admin();
user currentUser = user();
bool isUser = false;
bool isAdmin = false;

void Register();
void Login();
void LogOut();
void LoadUserMap();
void LoadQueue();
void LoadAdminMap();
void SaveUserMap();
void SaveAdminMap();
void SaveQueue();
void main()
{
	LoadQueue();
	LoadUserMap();
	LoadAdminMap();
	
	cout << "WELCOME TO VACCINE TRACKING SYSTEM" << endl;
	cout << "----------------------------------" << endl;
	Login();
	int choice;
	char agree;

start:while (isUser == false && isAdmin == false)
{

	cout << "Would you like to Register or Try Logging in Again?\n";
	cout << "1 to Register and 2 to Log In!\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		Register();
		break;
	}
	case 2:
	{
		Login();

		break;
	}
	default:
		break;
	}
}


while (isUser)
{
	cout << "Enter your choice:\n1)Display or Edit your Data\n2)display position in Queue\n3)Apply for Vaccine\n4)Log Out\n5)to Exit\n";
	cin >> choice;
	switch (choice)
	{


	case 1:
	{
		cout << "Pleaes enter your ID and password again to confirm!";
		string tempID, tempPass;
		cin >> tempID >> tempPass;
		if (currentUser.getID() == tempID && currentUser.getPass() == tempPass)
		{
			currentUser.DisplayUser();
			cout << "Would you like to display your Vaccine Status?\n";
			cin >> agree;
			if (agree == 'y' || agree == 'Y')
			{
				currentUser.DisplayVaccineStatus();
			}
			cout << "Would you like to Edit your Data?\n";
			cin >> agree;
			if (agree == 'y' || agree == 'Y')
			{
				UserTable.at(currentUser.getID()).EditUserData();
				if (currentUser.applyForVaccine==true)
				{
					UserQueue.at(currentUser.GetQueuePosition(UserQueue, currentUser)-1) = UserTable.at(currentUser.getID());
					cout << "Data edited in map and Queue\n";
				}
				else
				{
					cout << "Data Edited in MAP ONLY\n";
				}
			}

		}

		break;

	}
	case 2:
	{
		for (int i = 0; i < UserQueue.size(); i++)
		{
			if (UserQueue[i].getID() == currentUser.getID() && UserQueue[i].getPass() == currentUser.getPass())
			{
				cout << "Current position in Queue is: " << i + 1 << endl;
			}
		}
		break;
	}
	case 3:
	{
		if (currentUser.applyForVaccine == true)
		{
			cout << "You Already Applied for Vaccine MF!\n";
		}
		else
		{
			currentUser.AddToVaccineQueue(currentUser, UserQueue);
		}
		break;
	}
	case 4:
	{
		LogOut();
		goto start;
		break;
	}
	case 5:
	{
		SaveQueue();
		SaveAdminMap();
		SaveUserMap();
		exit(0);
	}

	default:
		break;
	}
}
while (isAdmin)
{

	cout << "Press 1 to display a specific user by ID: ";
	cout << "\nPress 2 to display all users\n";
	cout << "Press 3 to Display the Queue(Vaccine Waiting List): \n";
	cout << "Press 4 to display all user by a Filter\n";
	cout << "\t\tPress 5 to Log Out\n";
	cout << "\tPress 6 to add a new Admin \n";
	cout << "\t\tPress 7 to Exit \n";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{	char delUser;
	char searchAgain = 0;
	string id;
	do {

		cout << "Enter the ID you wanna display its user: ";
		cin >> id;
		currentAdmin.viewUser(UserTable, id);
		selectedUser = UserTable.at(id);
		cout << "Would you like to erase this user's data?(y/n)";

		cin >> delUser;
		if (delUser == 'y' || delUser == 'Y')
		{
			currentAdmin.DeleteUser(UserTable, UserQueue, selectedUser.getID());
			selectedUser = user();
		}
		cout << "Would you like to search for another user?\n";
		cin >> searchAgain;
	} while (searchAgain == 'y' || searchAgain == 'Y');
	break;
	}
	case 2:
	{

		currentAdmin.displayAllUsers(UserTable);
		char delAll;
		cout << "Would you like to Delete all the Database?\n";
		cin >> delAll;
		if (delAll=='y'|| delAll == 'Y')
		{
				cout << "Are you SURE??? This will erase everything!\n";
				cin >> delAll;
				if (delAll == 'Y' || delAll == 'y')
				{
					currentAdmin.DeleteAllUsers(UserTable, UserQueue);

				}
		}
		else 
		{
			cout << "Delete all process was cancelled." << endl;
		}
		break;
	}
	case 3:
	{
		currentAdmin.displayQueue(UserQueue);
		break;
	}
	case 4:
	{
		cout << "How would you like to filter the users?" << endl;
		cout << "1)by dose number\n2)By Age Ascendingly\n";
		cin >> agree;
		if (agree=='1')
		{
			cout << "Enter the dose filter(1/2)" << endl;
			cin >> choice;
			currentAdmin.displayByDoses(choice,UserTable);
			cout << "\n";
			
		}
		else if (agree=='2')
		{
			currentAdmin.DisplayByAge(UserTable);

		}
		break;
	}
	case 5:
	{
		LogOut();
		goto start;
		break;
	}
	case 6:
	{
		cout << "Please confirm you are an admin." << endl;
		cout << "Enter your ID and Password\n";
		string id, pass;
		cin >> id >> pass;
		if (currentAdmin.getID() == id && currentAdmin.getPass() == pass)
		{
			currentAdmin.addAdmin(AdminTable);
		}
		else
		{
			cout << "Error in entered data\n";
		}
		break;
	}
	case 7:
	{
		SaveQueue();
		SaveAdminMap();
		SaveUserMap();
		exit(0);
	}
	default:
		break;
	}

}
}
void Register()
{
	selectedUser.AddUser(UserTable, UserQueue);
}
void Login()
{
	unordered_map<string, Admin>::iterator iter;
	unordered_map <string, user>::iterator it;
	string id, password;
	cout << "PLEASE enter your ID followed by passowrd!\n";
	cin >> id >> password;
	for (auto iter = AdminTable.begin(); iter != AdminTable.end(); iter++)
	{
		if (password == iter->second.getPass())
		{
			isAdmin = true;
			currentAdmin = iter->second;
			isUser = false;
			break;
		}
	}
	it = UserTable.find(id);
	if (isAdmin == false)
	{
		if (it != UserTable.end())
		{
			if (UserTable.at(id).getPass() == password)
			{
				currentUser = UserTable.at(id);
				cout << "Login Successful!\n";
				isUser = true;
				isAdmin = false;
			}
			else {
				cout << "Incorrect Password \n";
			}
		}
		else
		{
			cout << "Incorrect National ID\n";
		}


	}
}
void LogOut()
{
	isUser = false;
	isAdmin = false;
	currentUser = user();
	currentAdmin = Admin();
}
void LoadUserMap()
{
	

	// read from file into program
	ifstream UserTableFile; //input file
	UserTableFile.open("UserMap.txt");
	if (!UserTableFile.is_open())
	{
		cout << "\ncan't Load file! ";
	}
	else
	{
		string tempID, tempPass;
		while (UserTableFile >> tempID >> tempPass )
		{
			user readingFromFile;//reads user from file to add copy in the user map
			readingFromFile.setID(tempID);
			readingFromFile.setPass(tempPass);
			UserTableFile>>readingFromFile.FirstName >>
				readingFromFile.MiddleName >> readingFromFile.LastName
				>> readingFromFile.country >> readingFromFile.governorate
				>> readingFromFile.gender >> readingFromFile.applyForVaccine
				>> readingFromFile.isVaccined >> readingFromFile.age
				>> readingFromFile.vaccineDosesRecieved;
			
			UserTable.insert({ readingFromFile.getID(),readingFromFile });
		}
		cout << "Loading Data Complete!\n";
	}
	UserTableFile.close(); // closing file
}
void SaveUserMap()
{
	user writingToFile = user();//writes user to file from the unordered map

	/*write from program to file */
	ofstream UserTableFile;
	UserTableFile.open("UserMap.txt"); // open file
	// check if file is open
	if (!UserTableFile.is_open())
	{
		cout << "\ncan't Save file! ";
	}
	else
	{
		unordered_map<string, user>::iterator iter;
		for (auto iter = UserTable.begin(); iter != UserTable.end(); iter++)
		{
			writingToFile = iter->second;
			UserTableFile << writingToFile.getID() << " " << writingToFile.getPass() << " " << writingToFile.FirstName << " "
				<< writingToFile.MiddleName << " " << writingToFile.LastName << " "
				<< writingToFile.country << " " << writingToFile.governorate << " " << writingToFile.gender << " "
				<< writingToFile.applyForVaccine << " " << writingToFile.isVaccined
				<< " " << writingToFile.age << " " << writingToFile.vaccineDosesRecieved << "\n";
		}
		cout << "\nSaving Succesful!";
	}
	UserTableFile.close();


}
void LoadAdminMap()
{
	ifstream AdminTableFile; //input file
	AdminTableFile.open("AdminMap.txt");
	if (!AdminTableFile.is_open())
	{
		cout << "\ncan't Load file! ";
	}
	else
	{
		string tempID, tempPass;
		while (AdminTableFile >> tempID >> tempPass)
		{
			Admin readingFromFile = Admin();
			readingFromFile.setID(tempID);
			readingFromFile.setPass(tempPass);
			AdminTableFile >> readingFromFile.FirstName >> readingFromFile.MiddleName >> readingFromFile.LastName
				>> readingFromFile.gender >> readingFromFile.age;
			AdminTable.insert({ tempID,readingFromFile });
		}
		cout << "Loading Data Complete!\n";
		AdminTableFile.close(); // closing file
	}

}
void SaveAdminMap()
{
	Admin writingToFile = Admin();//writes Admin from the Admin map to file 

	/*write from program to file */
	ofstream AdminTableFile;
	AdminTableFile.open("AdminMap.txt"); // open file
	// check if file is open
	if (!AdminTableFile.is_open())
	{
		cout << "\ncan't Save file! ";
	}
	else
	{
		
		for (auto iter = AdminTable.begin(); iter != AdminTable.end(); iter++)
		{
			writingToFile = iter->second;
			AdminTableFile << writingToFile.getID() << " " << writingToFile.getPass()
				<< " " << writingToFile.FirstName << " " << writingToFile.MiddleName << " "
				<< writingToFile.LastName << " " << writingToFile.gender << " " << writingToFile.age << "\n";
		}
		cout << "\nSaving Succesful!";
	}
	AdminTableFile.close();


}
void SaveQueue()
{
	user writingToFile = user();//writes user to file from the unordered map

	/*write from program to file */
	ofstream UserQueueFile;
	UserQueueFile.open("UserQueue.txt"); // open file
	// check if file is open
	if (!UserQueueFile.is_open())
	{
		cout << "\ncan't Save file! ";
	}
	else
	{
		//deque<user>::iterator iter;
		//for (auto iter = UserQueue.begin(); iter != UserQueue.end(); iter++)
		for (const auto& user : UserQueue) {
			writingToFile = user;
			UserQueueFile << writingToFile.getID() << " "
				<< writingToFile.getPass() << " " << writingToFile.FirstName << " "
				<< writingToFile.MiddleName << " " << writingToFile.LastName << " "
				<< writingToFile.country << " " << writingToFile.governorate << " "
				<< writingToFile.gender << " " << writingToFile.applyForVaccine << " "
				<< writingToFile.isVaccined << " " << writingToFile.age << " "
				<< writingToFile.vaccineDosesRecieved << "\n";
		}
		cout << "\nSaving Succesful!";
	}
	UserQueueFile.close();

}
void LoadQueue()
{
	

	// read from file into program
	ifstream UserQueueFile; //input file
	UserQueueFile.open("UserQueue.txt");
	if (!UserQueueFile.is_open())
	{
		cout << "\ncan't Load file! ";
	}
	else
	{
		string tempID, tempPass;
		while (UserQueueFile >> tempID >> tempPass )
		{	
			user readingFromFile = user();//reads user from file to add copy in the user map
			UserQueueFile >> readingFromFile.FirstName >>
				readingFromFile.MiddleName >> readingFromFile.LastName
				>> readingFromFile.country >> readingFromFile.governorate
				>> readingFromFile.gender >> readingFromFile.applyForVaccine
				>> readingFromFile.isVaccined >> readingFromFile.age
				>> readingFromFile.vaccineDosesRecieved;
			readingFromFile.setID(tempID);
			readingFromFile.setPass(tempPass);
			UserQueue.push_back(readingFromFile);
		}
		cout << "Loading Data Complete!\n";
	}
	UserQueueFile.close(); // closing file

}
