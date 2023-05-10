#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_map>
#include <string.h>
using namespace std;
class user
{
	//Private members
	string nationalId;
	string password;
public:
	string FirstName, MiddleName, LastName, country, governorate;
	char gender;// M for male F for female
	unsigned short int age;//Age of the user
	unsigned short int vaccineDosesRecieved;// number of vaccine doses the user has taken
	bool isVaccined;// true if user got vaccined | false if user haven't 
	bool applyForVaccine;// true if user is applying for vaccine | false is user isn't applying
	static unsigned long long FNumber;// number of female users
	static unsigned long long MNumber;// number of male users
	static unsigned long long TotalNumber;// total number of users
	//Getters
	string getID();
	string getPass();
	//Setters
	void setPass(string Pass);
	void setID(string ID);
	//Display Methods
	void DisplayUser();
	void  DisplayVaccineStatus();
	int GetQueuePosition(deque<user>& UserQueue, user& currentUser);
	//Methods to Add user to the database
	void AddUser(unordered_map<string, user>& Users, deque<user>& UserQueue);
	void AddToVaccineQueue(string id, unordered_map<string, user>& Users, deque<user>& UserQueue);//called when the user is registering and wants to apply for vaccine
	void AddToVaccineQueue(user IntoQueue, deque<user>& UserQueue);//Called when the user is already registered and wants to apply for vaccine
	bool validateNaID(string str);
	bool validatePassword(string password);
	//Edit Method
	void EditUserData();
	//Constructors
	user();
	user(string Fisrtname, string MiddleName, string LastName, string nationalIdNEW, string passwordNEW, char genderNEW, unsigned short int ageNEW, string countryNEW, string governorateNEW, unsigned short int timesVaccinatedNew, bool isVaccined, bool applyForVaccine);
	//Destructors
	~user();
};
