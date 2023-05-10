#include "user.h"
#include<iostream>
#include<regex>
using namespace std;
//Add a new user
void user::AddUser(unordered_map<string, user>& Users, deque<user>& UserQueue)
{
	char wasVaccinated, gender, applyForvac, confirmRegistration;
	int dosesRecieved, age;
	bool correctData = true, applyForVaccine = false, isFULLYVaccined;
	unordered_map <string, user>::iterator it;
	string nationalId, password, FName, MName, LName, country, governorate;
	cout << "Enter ID\t";
	cin >> nationalId;
	validateNaID( nationalId);
	it = Users.find(nationalId);
	cout << "Enter Password\t";
	cin >> password;
	validatePassword(password);
	cout << "Enter Your First Name\t";
	cin >> FName;
	cout << "Enter Your Middle Name\t";
	cin >> MName;
	cout << "Enter Your Last Name\t";
	cin >> LName;
	cout << "Age\t";
	cin >> age;
	cout << "Gender\t";
	cin >> gender;
	cout << "Country\t";
	cin >> country;
	cout << "Governorate\t";
	cin >> governorate;//use enum function
	if (country != "Egypt" || country != "egypt")
	{
		cout << "please inter correct data\n";
		correctData = false;
	}
	if (gender == 'm' || gender == 'f' || gender == 'F' || gender == 'M')
	{


	}
	else
	{
		cout << "Gender incorrect,you netflix worshipper mother fucker\n";
		correctData = false;
	}
	if (it != Users.end())
	{

		cout << "dh 3ndha\n";
		correctData = false;

	}
	if (correctData) {
		cout << "Have you been Vaccinated before?(y/n)\n";
		cin >> wasVaccinated;
		if (wasVaccinated == 'y' || wasVaccinated == 'Y')
		{
			cout << "How many doses of the vaccine did you recieve?\n";
			cin >> dosesRecieved;
			if (dosesRecieved == 2)
			{
				cout << "\nYou Got All Doses..";
				isFULLYVaccined = true;
				applyForVaccine = false;
			}
			else
			{
				isFULLYVaccined = false;
				cout << "Would you like to apply for vaccination?\n";
				cin >> applyForvac;
				if (applyForvac == 'y' || applyForvac == 'Y')
				{
					applyForVaccine = true;
				}
				else {
					applyForVaccine = false;
					/*correctData = false;
					cout << "You must apply for Vaccine in order to register!";*/
				}

			}
		}
		else
		{

			dosesRecieved = 0;
			isFULLYVaccined = false;
			cout << "Would you like to apply for vaccination?\n";
			cin >> applyForvac;
			if (applyForvac == 'y' || applyForvac == 'Y')
			{
				applyForVaccine = true;
			}
			else {
				applyForVaccine = false;
				/*correctData = false;
				cout << "You must apply for Vaccine in order to register!";*/
			}
		}
	}
	if (correctData)
	{
		cout << "Confirm Registration?('y' or 'Y' to confirm)\t";
		cin >> confirmRegistration;
		if (confirmRegistration != 'y' && confirmRegistration != 'Y')
		{
			correctData = false;
			applyForVaccine = false;
			cout << "Registration Cancelled! \n";
		}
	}
	if (correctData)
	{
		Users.insert({ nationalId, user(FName,MName,LName, nationalId, password, gender, age, country, governorate,dosesRecieved,isFULLYVaccined,applyForVaccine) });
		cout << "Would you like to Edit your data?" << endl;
		cin >> confirmRegistration;
		if (confirmRegistration == 'Y' || confirmRegistration == 'y')
		{
			Users.at(nationalId).EditUserData();
		}
	}
	if (applyForVaccine && correctData)
	{
		AddToVaccineQueue(nationalId, Users, UserQueue);
	}
}
//Edit User
void user::EditUserData()
{
	char editAgain = 'y';
	while (editAgain == 'y' || editAgain == 'Y')
	{
		int EditChoice;
		string toEditString;
		unsigned short int ToEditNumbers;
		cout << "Please Select what would you like to edit: \n1)Name\n2)Password\n3)age\n4)Gender\n5)Vaccine Doses Recieved\n6)Governorate\n7)Country";
		cin >> EditChoice;
		switch (EditChoice)
		{
		case 1:
		{
			cout << "Enter the Name Correctly(First,then Middle,then Last): \t";
			cin >> toEditString;
			this->FirstName = toEditString;
			cin >> toEditString;
			this->MiddleName = toEditString;
			cin >> toEditString;
			this->LastName = toEditString;
			cout << "Want to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 2:
		{

			break;
		}
		case 3:
		{
			cout << "Enter the Age Correctly: \t";
			cin >> ToEditNumbers;
			this->age = ToEditNumbers;
			cout << "Want to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 4:
		{
			cout << "Enter the Gender Correctly(M/F): \t";
			cin >> toEditString;
			this->gender = toEditString[0];
			cout << "Want to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 5:
		{
			cout << "Enter how many Vaccine doses you recieved: \t";
			cin >> ToEditNumbers;
			if (ToEditNumbers <= 2 && ToEditNumbers >= 0)
			{
				this->vaccineDosesRecieved = ToEditNumbers;
			}
			else
			{
				cout << "Please enter a valid value (0,1,2)!" << endl;
			}
			cout << "Want to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 6:
		{

			cout << "Enter Your Governorate Correctly:  \t";
			cin >> toEditString;
			this->governorate = toEditString;
			cout << "Want to Edit  something else?(y/n)\n";
			cin >> editAgain;
			break;
		}
		case 7:
		{
			cout << "Enter Your Country Correctly:  \t";
			cin >> toEditString;
			if (toEditString == "Egypt")
			{
				this->country = toEditString;

			}
			else
			{
				cout << "Your Country must be Egypt!" << endl;
			}
			cout << "Want to Edit  something else?(y/n)\n";
			cin >> editAgain;

			break;
		}
		default:
			break;
		}
	}
}
//Display functions
void user::DisplayUser()
{
	cout << "ID: " << getID() << "\nName: " << FirstName << " " << MiddleName << " " << LastName << "\nGender: " << gender << "\nAge: " << age << endl;
}
void user::DisplayVaccineStatus()
{
	string applyForVac, fullyVac;
	if (isVaccined)
	{
		fullyVac = "Fully Vaccinated.";
	}
	else
	{
		fullyVac = "Not Fully Vaccinated";
	}
	if (applyForVaccine)
	{
		applyForVac = "Applied";
	}
	else
	{
		applyForVac = "Not Applied";
	}
	cout << "Number of Doses Left: " << 2 - vaccineDosesRecieved << "\nApplication for vaccine: " << applyForVac << "\nVaccination Status:" << fullyVac << endl;
}
//Queue Functions
int user::GetQueuePosition(deque<user>&UserQueue,user &currentUser)
{
	for (int i = 0; i < UserQueue.size(); i++)
		{
			if (UserQueue[i].getID() == currentUser.getID() && UserQueue[i].getPass() == currentUser.getPass())
			{
				return i + 1 ;
			}
		}
	return -1;
}
void user::AddToVaccineQueue(user IntoQueue, deque<user>& UserQueue)
{
	UserQueue.push_back(IntoQueue);
}
void user::AddToVaccineQueue(string id, unordered_map<string, user>& UserTable, deque<user>& UserQueue)
{




	UserQueue.push_back(UserTable.at(id));
}

bool user::validateNaID(string nationalId) {
	const regex pattern("^[0-9]{3}[0-9]{7}[0-9]{3}$");
	if (nationalId.empty()) {
		cout << "no thing input\n";
	}

	// Return true if the str
	// matched the ReGex
	if (regex_match(nationalId, pattern)) {
		return true;
	}
	else {
		cout << "is Not valid\n";
		cout << "Try agin please\n";
	}
	

}

bool user::validatePassword(string password)
{
	// regex pattern for password validation  
	regex pattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@#$%*^&+=]).{8,}");

	// check if the password matches the pattern  
	if (regex_match(password, pattern))
	{
		return true;
	}
	else
	{
		cout << "is  not valid\n";
	}
	
}

//setters
void user::setID(string ID)
{
	this->nationalId = ID;
}
void user::setPass(string Pass)
{
	this->password = Pass;
}
//getters
string user::getID()
{
	return nationalId;
}
string user::getPass()
{
	return password;
}
//constructors
user::user(string Firstname, string MiddleName, string LastName, string nationalIdNEW, string passwordNEW, char genderNEW, unsigned short int ageNEW, string countryNEW, string governorateNEW, unsigned short int timesVaccinatedNew, bool isVaccined, bool applyForVaccine)
{
	this->FirstName = Firstname;
	this->MiddleName = MiddleName;
	this->LastName = LastName;
	nationalId = nationalIdNEW;
	password = passwordNEW;
	gender = genderNEW;
	age = ageNEW;
	country = countryNEW;
	governorate = governorateNEW;
	vaccineDosesRecieved = timesVaccinatedNew;
	this->isVaccined = isVaccined;
	this->applyForVaccine = applyForVaccine;
}
user::user()
{
	FirstName = "-1";
	MiddleName = "-1";
	LastName = "-1";
	nationalId = "-1";
	password = "-1";
	gender = 'N';
	age = -1;
	country = "-1";
	governorate = "-1";
	vaccineDosesRecieved = -1;
	this->isVaccined = false;
	this->applyForVaccine = false;
}
//destructor
user::~user()
{

}
