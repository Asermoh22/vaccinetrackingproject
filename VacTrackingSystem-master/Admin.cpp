#include "Admin.h"
#include "user.h"
#include <algorithm>
//Display functions
void Admin::viewUser(unordered_map<string, user>& User, string id)
{

	User.at(id).DisplayUser();
	cout << endl;
	User.at(id).DisplayVaccineStatus();





}
void Admin::viewNextInQueue(deque<user>& UserQueue)
{
	UserQueue[0].DisplayUser();
	cout << "\n";
	UserQueue[0].DisplayVaccineStatus();
	cout << "\n";
}
void Admin::displayQueue(deque<user>& UsersInQueue)
{
	for (int i = 0; i < UsersInQueue.size(); i++)
	{
		UsersInQueue[i].DisplayUser();
	}

}
void Admin::displayAllUsers(unordered_map<string, user>& Users)
{
	unordered_map<string, user>::iterator iter;
	for (auto iter = Users.begin(); iter != Users.end(); iter++)
	{
		iter->second.DisplayUser();
		cout << endl;
		iter->second.DisplayVaccineStatus();
		cout << endl;
	}

}
void Admin::displayByDoses(int doses, unordered_map<string, user>& UserMap)
{
	if (doses == 1)
	{
		
		for (auto iter = UserMap.begin(); iter != UserMap.end(); iter++)
		{
			if (iter->second.vaccineDosesRecieved == 1)
			{
				iter->second.DisplayUser();
				cout << endl;
				iter->second.DisplayVaccineStatus();
				cout << endl;
			}
		}
	}
	else if (doses == 2)
	{
		unordered_map<string, user>::iterator iter;
		for (auto iter = UserMap.begin(); iter != UserMap.end(); iter++)
		{
			if (iter->second.vaccineDosesRecieved == 2)
			{
				iter->second.DisplayUser();
				cout << endl;
				iter->second.DisplayVaccineStatus();
				cout << endl;
			}
		}
	}
	else
	{
		cout << "Only those who received one or two doses can be viewed!" << endl;
	}
}
void Admin::DisplayByAge(unordered_map<string,user>&UserTable) {
	vector <pair<string, user>> SortedAgeVector(UserTable.begin(), UserTable.end());
	sort(SortedAgeVector.begin(), SortedAgeVector.end(), [](auto& a, auto& b) {
		return a.second.age < b.second.age;
		});
	for (auto& pair : SortedAgeVector)
	{

		pair.second.DisplayUser();
		pair.second.DisplayVaccineStatus();
	}
	
}
//User Deleting functions
void Admin::DeleteAllUsers(unordered_map<string, user>& Users, deque<user>& UserQueue)
{
	Users.clear();
	UserQueue.clear();
}
void Admin::DeleteUser(unordered_map<string, user>& Users, deque<user>& UserQueue, string id)
{
	unordered_map <string, user>::iterator it;

	it = Users.find(id);
	Users.erase(it);
	DeleteUserFromQueue(UserQueue, id);

}
void Admin::DeleteUserFromQueue(deque<user>& UserQueue, string ID)
{
	stack<user>UserStack;
	for (int i = 0; i < UserQueue.size(); i++)
	{
		if (UserQueue[i].getID() != ID)
		{
			UserStack.push(UserQueue[i]);
			UserQueue.pop_front();
		}
		else
		{
			UserQueue.pop_front();
			break;
		}
	}
	while (!UserStack.empty())
	{
		UserQueue.push_front(UserStack.top());
		UserStack.pop();
	}
}
//Add Admin
void Admin::addAdmin(unordered_map<string, Admin>& admins)
{
	string Fname, Mname, Lname, pass, id;
	unsigned short int age;
	char gender;
	//id=getID();
	bool rightdata = true;
	cout << "Please Enter Your First Name:" << endl;
	cin >> Fname;
	cout << "Please Enter Your Middle Name:" << endl;
	cin >> Mname;
	cout << "Please Enter Your Last Name:" << endl;
	cin >> Lname;
	cout << "Please Enter Your ID:" << endl;
	cin >> id;
	cout << "Please Enter Your Password:" << endl;
	cin >> pass;
	cout << "Please Enter Your Gender:" << endl;
	cin >> gender;
	cout << "Please Enter Your Age:" << endl;
	cin >> age;
	if (gender == 'm' || gender == 'f' || gender == 'F' || gender == 'M')
	{


	}
	else
	{
		cout << "WE DO NOT ACCEPT NETFLIX\n";
		rightdata = false;
	}

	if (age < 22)
	{

		cout << "Admin Must Be More Than 22 Years Old" << endl;
		rightdata = false;

	}

	if (rightdata)
	{
		admins.insert({ id, Admin(id,  pass,  Fname,  Mname,  Lname, gender, age) });
	}





}
//setters
void Admin::setPass(string Pass)
{
	this->password = Pass;

}
void Admin::setID(string ID)
{
	this->nationalId = ID;

}
//getters
string Admin::getID()
{
	return nationalId;
}
string Admin::getPass()
{
	return password;
}
//constructors
Admin::Admin(string id, string pass, string FName, string MName, string LName, char gender, unsigned short int age)
{
	this->age = age;
	this->gender = gender;
	this->nationalId = id;
	this->password = pass;
	this->FirstName = FName;
	this->MiddleName = MName;
	this->LastName = LName;
}
Admin::Admin()
{
	nationalId = "";
	password = "";
	FirstName = "";
	MiddleName = "";
	LastName = "";
	gender = 'N';
	age = -1;

}
//destructor
Admin::~Admin()
{
}
