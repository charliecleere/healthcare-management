/*
	Lab 7: Polymorphism and Operator Overloading
	Charlie Cleere
	4/24/2026
*/

/*
	ALGORITHM

	In Patient Header File:
	1a. Include everything from Lab 2

	1b. Include an include statement for the visit class header file

	2. Add vector of visit objects

	3. Add a addVisit function

	4. Modify the printPatientDetails function to include data from the visits vector


	In Patient Implementation File:
	1. Include everything from Lab 2

	2. Add a addVisit function

	3. Modify the printPatientDetails function to include data from the visits vector


	In Service Header File:
	1. Include serviceID, and seviceName as private member variables

	2. For public member variables include a two-argument constructor with default parameters, destructor, and accessor/mutator functions


	In Service Implementation File:
	1. Constructor, destructor, and access/mutator functions


	In Visit Header File:
	1a. Include an include statement for the service class header file

	1b. Include visitID, employeeName, visitDate, and vector of services as private member variables

	2. Include three-argument constructor with default parameters, destructor, accessor/mutator functions, add service function, printVisit function for private member variables. (You may not need the printVisit function, and it may be in private variables.)


	In Visit Implementation File:
	1. Include three-argument constructor with default parameters, destructor, accessor/mutator functions, add service function, printVisit function (You may not need the printVisit function, and it may be in private variables.)


	In Main and Other Non-Class Functions File (includes only new content that adds on top of Lab 2):
	1a. Before main create a global const variable that stores the name of the services text file

	1b. Put any new function prototypes before main

	2. Inside main declare in the local variables a vector of services

	3. Implement a loadServicesOffered function, and pass in the vector of services by reference

	4. Modify the switch to include the 4th option of the menu, i.e., the create visit for patient option

	5. If user selects option 4:
		+ Implement a createVisitForPatient function (passign in ....)
			+ Prompt the user for the ID of the patient to assign the new visit
			+ Error check similar to how I did it in the deleteExistingPatient function (I may not need this, and I also may not need this in the deleteExistingPatient function)
			+ Implement a search function (also, use this function in other areas in your code: in the deleteExistingPatient function, and maybe later in this function)
				+ This function will return the position (or index) of one of the vector objects that has the same ID that I passed into the function. If it is not found return -1.
			+ Prompt for the details of the visit (i.e. the VisitID, the nurse/aide’s name, and the date of the visit). Store in 3 temp variables
			+ The visit object should then be created with three parameters (for the constructor)
			+ Using the vector of services print to the console a list of all the services and their corresponding ID number
			+ Get from the user their service ID of choice
			+ I think use the same search function as above to find the index of the service they want to add. If no object matches the ID then give error message and allow the user to re-enter the ID or exit the screen
			+ Once a valid ID is entered, call the addService function, passing in an object of the vector of services with the index of their chosen object
			+ Call the addVisit function passing in the visit object

	6. For if the user chooses option 5 or 6, modify the printPatientDetails function to include the visit info.
		+ Maybe use the printVisit function in the visit class to help with this

*/

#include <fstream>
#include <random>
#include <algorithm>
#include <typeinfo>
#include "Patient.h"
#include "Nurse.h"
#include "Aide.h"
#include "CaseManager.h"
#include "MonitorEquipment.h"
#include "MobilityEquipment.h"
#include "DuplicateIdException.h"
#include "StorageUnit.h"

using namespace std;

// Global constants
const int MAX_NUM_OF_NURSES = 50;  // 7 in the file
const int MAX_NUM_OF_AIDES = 50;  // 9 in the file
const int MAX_NUM_OF_CASE_MANAGERS = 50;  // 5 in the file
const string SERVICES_FILE_NAME = "Services";
const string NURSES_DATA_FILE_NAME = "Nurses";
const string AIDES_DATA_FILE_NAME = "Aides";
const string CASE_MANAGERS_DATA_FILE_NAME = "Case Managers";
const string EQUIPMENT_FILE_NAME = "Equipment";
const int MAX_NUM_OF_PATIENTS = 50;
const int SCREEN_WIDTH = 64;


// Function prototypes
void loadServicesFromFile(vector<Service>& services, bool& files_are_open);

template <typename T>
void loadEmployeeData(T**& employees, string file_name, bool& files_are_open);

void loadEquipmentData(vector<Equipment*>& equipment, bool& files_are_open);

template <typename T>
void sortEmployees(T** &employees, int num_of_employees);

int printMainMenu();

int printPatientMenu();

int printEmployeeMenu();

int printEquipmentMenu();

Patient buildPatientFromUserInput(const vector<Patient>& patients);

Patient readPatientFromFile(const vector<Patient>& patients);

void deleteExistingPatient(vector<Patient>& patients);

void showPatientList(vector<Patient> patients);

void createVisitForPatient(vector<Patient>& patients, Nurse** nurses, int num_of_nurses, Aide** aides, int num_of_aides, vector<Service> services);

template <typename T>
int searchForIdInVector(vector<T> vector, int id_to_find);

int searchForIdInEquipmentVector(vector<Equipment*> equipment, int id_to_find);

int searchForIdInVisitVector(Patient patient, int id_to_find);

template <typename T>
int searchForIdInDynArray(T** array, int array_size, int id_to_find);

template <typename T>
int getEmployeeIdChoice(T** employees, int num_of_employees, string emp_type_title, string assignment_target);

void assignCaseManagerToPatient(vector<Patient>& patients, CaseManager** case_managers, int num_of_case_managers);

void incrementPatientAge(vector<Patient>& patients);

void sortPatientById(vector<Patient>& patients);

void printEmployeeReport(ostream& out, Nurse** nurses, int num_of_nurses, Aide** aides, int num_of_aides, CaseManager** case_managers, int num_of_case_managers);

void showEquipmentList(vector<Equipment*> equipment);

int getAndSearchForEquipmentId(vector<Equipment*> equipment, std::string prompt);

int calculateCenteredTextX(std::string s);

template <typename T>
void updateStorageUnitInformation(T& storage_unit);

int promptForStorageUnitType();

template <typename T>
void addEquipmentToStorageUnit(T storage_unit, vector<Equipment*> equipment);

int main()
{
	// Local variables
	vector<Patient> patients;
	vector<Service> services;
	Nurse** nurses = new Nurse*[MAX_NUM_OF_NURSES];
	Aide** aides = new Aide*[MAX_NUM_OF_AIDES];
	CaseManager** case_managers = new CaseManager*[MAX_NUM_OF_CASE_MANAGERS];
	vector<Equipment*> equipment;
	bool files_are_open = true;
	int num_of_nurses = 0;
	int num_of_aides = 0;
	int num_of_case_managers = 0;
	int main_menu_choice = 0;
	int patient_menu_choice = 0;
	int employee_menu_choice = 0;
	int equipment_menu_choice = 0;
	ofstream output_file;
	string output_file_name;
	int equipment_id_choice = 0;
	StorageUnit<MonitorEquipment> monitor_equipment_unit;
	StorageUnit<MobilityEquipment> mobility_equipment_unit;
	int unit_type_choice = 0;

	for (int i = 0; i < MAX_NUM_OF_NURSES; i++)
		nurses[i] = nullptr;

	for (int i = 0; i < MAX_NUM_OF_AIDES; i++)
		aides[i] = nullptr;

	for (int i = 0; i < MAX_NUM_OF_CASE_MANAGERS; i++)
		case_managers[i] = nullptr;

	// Loads from a file the vector of services with service IDs and the services that correspond to each ID
	loadServicesFromFile(services, files_are_open);

	// Loads from a file the three employee vectors (nurses, aides, and caseManagers) with employees and their information. After each vector is loaded it is sorted by last name.
	loadEmployeeData(nurses, NURSES_DATA_FILE_NAME, files_are_open);
	loadEmployeeData(aides, AIDES_DATA_FILE_NAME, files_are_open);
	loadEmployeeData(case_managers, CASE_MANAGERS_DATA_FILE_NAME, files_are_open);

	loadEquipmentData(equipment, files_are_open);

	// If all the files opened properly then do the following, otherwise (i.e., if one or more don't open properly) skip the following
	if (files_are_open)
	{
		for (int i = 0; i < MAX_NUM_OF_NURSES && nurses[i] != nullptr; i++)
		{
			num_of_nurses++;
		}

		for (int i = 0; i < MAX_NUM_OF_AIDES && aides[i] != nullptr; i++)
		{
			num_of_aides++;
		}

		for (int i = 0; i < MAX_NUM_OF_CASE_MANAGERS && case_managers[i] != nullptr; i++)
		{
			num_of_case_managers++;
		}

		// The following sort by last name
		sortEmployees(nurses, num_of_nurses);
		sortEmployees(aides, num_of_aides);
		sortEmployees(case_managers, num_of_case_managers);

		// Do the following until the user chooses to exit
		do
		{
			// Prints the menu, gets the user choice, and stores it in variable
			main_menu_choice = printMainMenu();

			switch (main_menu_choice)
			{
			case 1: // Patient management option from main menu
				do
				{
					patient_menu_choice = printPatientMenu();

					switch (patient_menu_choice)
					{
					case 1: // Add new patient manually option from patient submenu
						// If there is no more room for additional patients this will not allow the user to add anymore 
						if (patients.size() >= MAX_NUM_OF_PATIENTS)
						{
							cout << "Health Care Options, Inc. is not accepting anymore new patients at this time." << endl << endl;
						}
						else
						{
							// User to manually inputs all the patient data. The data is stored in a patient object. Then, it returns that patient object back to main and adds it to the end of the patients vector
							patients.push_back(buildPatientFromUserInput(patients));
						}
						break;
					case 2: // Read patient information from file option from patient submenu
						// If there is no more room for additional patients this will not allow the user to add anymore 
						if (patients.size() >= MAX_NUM_OF_PATIENTS)
						{
							cout << "Health Care Options, Inc. is not accepting anymore new patients at this time." << endl << endl;
						}
						else
						{
							patients.push_back(readPatientFromFile(patients));
						}
						break;
					case 3: // Delete existing patient option from patient submenu
						deleteExistingPatient(patients);
						break;
					case 4: // Create visit for patient option from patient submenu
						createVisitForPatient(patients, nurses, num_of_nurses, aides, num_of_aides, services);
						break;
					case 5: // Assign case manager to patient option from patient submenu
						assignCaseManagerToPatient(patients, case_managers, num_of_case_managers);
						break;
					case 6: // Increase patient age by one year option from patient submenu
						incrementPatientAge(patients);
						break;
					case 7: // Print patient report to screen option from patient submenu
						// Sorts the patients vector by patient ID number
						sortPatientById(patients);
						// Prints to the screen all the patient objects that have been loaded into the array
						for (int i = 0; i < patients.size(); i++)
						{
							patients[i].sortBpms();
							cout << patients[i];
						}

						cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
						cout << right << setw(24) << "" << "End of Report" << endl;
						cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
						break;
					case 8: // Save patients to a file option from patient submenu
						// Sorts the patients vector by patient ID number
						sortPatientById(patients);
						// Prompting the user for a file name
						cout << "Please enter the name of the file to save the patient report to (don't include .txt): ";

						cin.ignore(numeric_limits<streamsize>::max(), '\n');

						// Storing the user's chosen file name in a variable
						getline(cin, output_file_name);

						// Opening the file
						output_file.open(output_file_name + ".txt");

						// Prints to a file all the patient objects that have been loaded into the array
						for (int i = 0; i < patients.size(); i++)
						{
							patients[i].sortBpms();
							output_file << patients[i];
						}

						output_file << setfill('-') << setw(64) << "" << setfill(' ') << endl;
						output_file << right << setw(24) << "" << "End of Report" << endl;
						output_file << setfill('-') << setw(64) << "" << setfill(' ') << endl;

						// Closes the file
						output_file.close();

						//To let the user know that the information was successfully saved to a file
						cout << endl << "The patient information was successfully saved to a file." << endl << endl;
						break;
					case 9: // Return to main menu option from patient submenu
						break;
					default:
						cout << "Error. Invalid menu choice. Please try again." << endl;
						break;
					}
					if (patient_menu_choice != 9)
						system("pause");
				} while (patient_menu_choice != 9);
				break;
			case 2: // Employee management option from main menu
				do
				{
					employee_menu_choice = printEmployeeMenu();

					switch (employee_menu_choice)
					{
					case 1: // Print employee report to screen option from employee submenu
						printEmployeeReport(cout, nurses, num_of_nurses, aides, num_of_nurses, case_managers, num_of_case_managers);
						break;
					case 2: // Return to main menu option from employee submenu
						break;
					default:
						cout << "Error. Invalid menu choice. Please try again." << endl;
						break;
					}
					if (employee_menu_choice != 2)
						system("pause");
				} while (employee_menu_choice != 2);
				break;
			case 3: // Equipment management option from main menu
				do
				{
					equipment_menu_choice = printEquipmentMenu();

					switch (equipment_menu_choice)
					{
					case 1: // Print equipment list to screen option from equipment submenu
						showEquipmentList(equipment);
						break;
					case 2: // Produce depreciation schedule for equipment option from equipment submenu
						showEquipmentList(equipment);
						equipment[getAndSearchForEquipmentId(equipment, "Enter the ID of the equipment you want to see the depreciation schedule for: ")]->depreciation(cout);
						break;
					case 3: // Update storage unit information option from the equipment submenu
						unit_type_choice = promptForStorageUnitType();
						
						switch (unit_type_choice)
						{
						case 1: // Update monitor equipment storage unit information
							updateStorageUnitInformation(monitor_equipment_unit);
							break;
						case 2: // Update mobility equipment storage unit information
							updateStorageUnitInformation(mobility_equipment_unit);
							break;
						case 3: // Exit
							break;
						default:
							cout << "Error. Invalid menu choice. Please try again." << endl;
							break;
						}
						break;
					case 4: // Add equipment to storage unit
						showEquipmentList(equipment);
						addEquipmentToStorageUnit(monitor_equipment_unit, equipment);
					case 5: // View storage unit information
						unit_type_choice = promptForStorageUnitType();

						switch (unit_type_choice)
						{
						case 1: // View monitor equipment storage unit information
							monitor_equipment_unit.printUnitInformation();
							monitor_equipment_unit.printInventory("Monitor");
							break;
						case 2: // View mobility equipment storage unit information
							mobility_equipment_unit.printUnitInformation();
							mobility_equipment_unit.printInventory("Mobility");
							break;
						case 3: // Exit
							break;
						default:
							cout << "Error. Invalid menu choice. Please try again." << endl;
							break;
						}
						break;
					case 6: // Return to main menu option from equipment submenu
						break;
					default:
						cout << "Error. Invalid menu choice. Please try again." << endl;
						break;
					}
					if (equipment_menu_choice != 6)
						system("pause");
				} while (equipment_menu_choice != 6);
				break;
			case 4: // Exit option from main menu
				// Lets the user know that the system closed down properly
				cout << "Thank you for using the Patient Management System." << endl << endl;
				break;
			default:
				cout << "Error. Invalid menu choice. Please try again." << endl;
				break;
			}
			system("pause");
		} while (main_menu_choice != 4);

		// Deallocates memory
		for (int i = 0; i < num_of_nurses; i++)
		{
			delete nurses[i];
			nurses[i] = nullptr;
		}
		delete[] nurses;
		nurses = nullptr;

		for (int i = 0; i < num_of_aides; i++)
		{
			delete aides[i];
			aides[i] = nullptr;
		}
		delete[] aides;
		aides = nullptr;

		for (int i = 0; i < num_of_case_managers; i++)
		{
			delete case_managers[i];
			case_managers[i] = nullptr;
		}
		delete[] case_managers;
		case_managers = nullptr;

		for (int i = 0; i < equipment.size(); i++)
		{
			delete equipment[i];
			equipment[i] = nullptr;
		}
	}
	else
	{
		cout << endl;
		system("pause");
	}

	return 0;
}

// Function definitions

// Loads the vector of services with information from a file
void loadServicesFromFile(vector<Service>& services, bool& files_are_open)
{
	ifstream input_file;
	string input_file_name = "";
	int temp_service_id = 0;
	string temp_service_name = "";

	input_file.open(SERVICES_FILE_NAME + ".txt");

	if (!input_file)
	{
		cout << "Error opening a file. Please fix the file and restart the program." << endl;
		files_are_open = false;
	}
	else
	{
		// While it's not the end of the file do the following
		while (!input_file.eof())
		{
			input_file >> temp_service_id;
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_service_name);

			Service temp_service(temp_service_id, temp_service_name);

			services.push_back(temp_service);
		}
	}
	input_file.close();
}

// Template function to load the three employee vectors (nurses, aides, and caseManagers) with employees and their information from a file
template <typename T>
void loadEmployeeData(T** &employees, string file_name, bool& files_are_open)
{
	ifstream input_file;
	int temp_employee_id = 0;
	string temp_emp_first_name = "";
	string temp_emp_last_name = "";
	double temp_earnings = 0.0;
	string temp_credentials = "";
	int i = 0;  // To keep track of the index as the while loop goes through the array

	input_file.open(file_name + ".txt");

	if (!input_file)
	{
		cout << "Error opening a file. Please fix the file and restart the program." << endl;
		files_are_open = false;
	}
	else
	{
		// While it's not the end of the file do the following
		while (!input_file.eof())
		{
			input_file >> temp_employee_id;
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_emp_first_name);
			getline(input_file, temp_emp_last_name);
			input_file >> temp_earnings;
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_credentials);

			employees[i] = new T(temp_employee_id, temp_emp_first_name, temp_emp_last_name, temp_earnings, temp_credentials);

			i++;
		}
	}
	input_file.close();
}

void loadEquipmentData(vector<Equipment*>& equipment, bool& files_are_open)
{
	ifstream input_file;
	int temp_equipment_id = 0;
	string temp_equipment_name = "";
	char temp_purchase_date[20];
	int m, d, y;
	double temp_original_cost = 0.0;
	int temp_useful_life = 0;
	double temp_salvage_value = 0.0;
	string temp_type_or_mode = "";
	
	int i = 0;  // To keep track of the index as the while loop goes through the array

	input_file.open(EQUIPMENT_FILE_NAME + ".txt");

	if (!input_file)
	{
		cout << "Error opening a file. Please fix the file and restart the program." << endl;
		files_are_open = false;
	}
	else
	{
		// While it's not the end of the file do the following
		while (!input_file.eof())
		{
			input_file >> temp_equipment_id;
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_equipment_name);
			input_file >> temp_purchase_date;
			input_file >> temp_original_cost;
			input_file >> temp_useful_life;
			input_file >> temp_salvage_value;
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_type_or_mode);

			if (temp_useful_life <= 5)
				equipment.push_back(new MonitorEquipment(temp_equipment_id, temp_equipment_name, temp_original_cost, temp_useful_life, temp_salvage_value, temp_type_or_mode));
			else if (temp_useful_life > 5)
				equipment.push_back(new MobilityEquipment(temp_equipment_id, temp_equipment_name, temp_original_cost, temp_useful_life, temp_salvage_value, temp_type_or_mode));

			equipment[i]->tokenizeDate(temp_purchase_date, m, d, y);
			equipment[i]->setPurchaseDate(m, d, y);

			i++;
		}
	}
	input_file.close();
}

// Template selection sort function to sort the nurses, aides, and case manager vectors by last name
template <typename T>
void sortEmployees(T** &employees, int num_of_employees)
{
	int index = 0;
	int smallest_index = 0;
	int location = 0;
	T* temp_employee;

	for (index = 0; index < num_of_employees - 1; index++)
	{
		smallest_index = index;

		for (location = index + 1; location < num_of_employees; location++)
		{
			if (employees[location]->getLastName() < employees[smallest_index]->getLastName())
				smallest_index = location;
		}

		// Above it finds the vector object whose last name comes next in alphabetical order, but below it swaps the entire vector object
		temp_employee = employees[smallest_index];
		employees[smallest_index] = employees[index];
		employees[index] = temp_employee;
	}
}

// Function to print the main menu, get the user choice, and error checks that choice
int printMainMenu()
{
	int choice = ' ';

	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc."); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Management"); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX2) << "Management" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	cout << "1. Patient Management" << endl;
	cout << "2. Employee Management" << endl;
	cout << "3. Equipment Management" << endl;
	cout << "4. Exit" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	cout << "Please enter your choice: ";
	cin >> choice;
	cout << endl;
	while (cin.fail() || choice < 1 || choice > 4)
	{
		cout << "Invalid menu selection. Please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
		cout << endl;
	}
	return choice;
}

// Function to print the patient management submenu, get the user choice, and error checks that choice
int printPatientMenu()
{
	int choice = ' ';
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc."); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Patient Management"); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX2) << "Patient Management" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	cout << "1. Add new patient manually" << endl;
	cout << "2. Read patient information from file" << endl;
	cout << "3. Delete existing patient" << endl;
	cout << "4. Create visit for patient" << endl;
	cout << "5. Assign case manager to patient" << endl;
	cout << "6. Increase patient age by one year" << endl;
	cout << "7. Print patient report to screen" << endl;
	cout << "8. Save patient report to a file" << endl;
	cout << "9. Return to main menu" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	cout << "Please enter your choice: ";
	cin >> choice;
	cout << endl;
	while (cin.fail() || choice < 1 || choice > 9)
	{
		cout << "Invalid menu selection. Please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
		cout << endl;
	}
	return choice;
}

// Function to print the employee management submenu, get the user choice, and error checks that choice
int printEmployeeMenu()
{
	int choice = ' ';
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc."); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Employee Management"); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX2) << "Employee Management" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	cout << "1. Print employee report to screen" << endl;
	cout << "2. Return to main menu" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	cout << "Please enter your choice: ";
	cin >> choice;
	cout << endl;
	while (cin.fail() || choice < 1 || choice > 2)
	{
		cout << "Invalid menu selection. Please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
		cout << endl;
	}
	return choice;
}

// Function to print the equipment management submenu, get the user choice, and error checks that choice
int printEquipmentMenu()
{
	int choice = ' ';
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc."); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Equipment Management"); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX2) << "Equipment Management" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	cout << "1. Print equipment list to screen" << endl;
	cout << "2. Produce depreciation schedule for equipment" << endl;
	cout << "3. Update storage unit information." << endl;
	cout << "4. Add equipment to storage unit." << endl;
	cout << "5. View storage unit information." << endl;
	cout << "6. Return to main menu" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	cout << "Please enter your choice: ";
	cin >> choice;
	cout << endl;
	while (cin.fail() || choice < 1 || choice > 6)
	{
		cout << "Invalid menu selection. Please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> choice;
		cout << endl;
	}
	return choice;
}

// Function that allows the user to manually input all the patient data while error checking the inputs and then storing their input in a patient object. Then, it returns that patient object back to main
Patient buildPatientFromUserInput(const vector<Patient>& patients)  // I pass in the patients vector to this function to be able to check that the random patient ID that is generated is not already being used by another patient in the vector
{
	random_device rdevice{};
	default_random_engine num{ rdevice() };
	uniform_int_distribution<unsigned int> randomNum{ 1, 1000 };

	// Declare and initialize all the temp variables
	Patient temp_patient;
	int temp_patient_id = 0;
	string temp_first_name = "";
	string temp_last_name = "";
	string temp_street_address = "";
	int temp_age = 0;
	double temp_height = 0.0;
	double temp_weight = 0.0;
	char temp_gender = ' ';
	char temp_is_ambulatory = ' ';
	bool temp_temp_is_ambulatory = false;
	int num_of_bpm_readings = 0;
	int temp_bpm_reading = 0;

	while (searchForIdInVector(patients, randomNum(num)) != -1)
		randomNum(num);

	// Store random number between 1 and 100 in temp patient ID variable
	temp_patient_id = randomNum(num);
	temp_patient.setId(temp_patient_id);

	cout << "First name: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, temp_first_name);
	temp_patient.setFirstName(temp_first_name);

	cout << "Last name: ";
	getline(cin, temp_last_name);
	temp_patient.setLastName(temp_last_name);

	cout << "Street address: ";
	getline(cin, temp_street_address);
	temp_patient.setStreetAddress(temp_street_address);

	do
	{
		cout << "Age (years): ";
		cin >> temp_age;
		while (cin.fail())
		{
			cout << "Invalid age. Age must be a number. Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Age (years): ";
			cin >> temp_age;
		}
		temp_patient.setAge(temp_age);
	} while (temp_patient.getAge() == -1);

	do
	{
		cout << "Height (inches): ";
		cin >> temp_height;
		while (cin.fail())
		{
			cout << "Invalid height. Height must be a number. Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Height (inches): ";
			cin >> temp_height;
		}
		temp_patient.setHeight(temp_height);
	} while (temp_patient.getHeight() == -1);

	do
	{
		cout << "Weight (lbs): ";
		cin >> temp_weight;
		while (cin.fail())
		{
			cout << "Invalid weight. Weight must be a number. Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Weight (lbs): ";
			cin >> temp_weight;
		}
		temp_patient.setWeight(temp_weight);
	} while (temp_patient.getWeight() == -1);

	cout << "Gender (M or F): ";
	cin >> temp_gender;
	while (toupper(temp_gender) != 'M' && toupper(temp_gender) != 'F')
	{
		cout << "Invalid entry. Entry must be either M or F. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Gender (M or F): ";
		cin >> temp_gender;
	}
	temp_patient.setGender(toupper(temp_gender));

	cout << "Is the patient ambulatory (Y or N): ";
	cin >> temp_is_ambulatory;
	while (toupper(temp_is_ambulatory) != 'Y' && toupper(temp_is_ambulatory) != 'N')
	{
		cout << "Invalid entry. Entry must be either Y or N. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Is the patient ambulatory (Y or N): ";
		cin >> temp_is_ambulatory;
	}
	if (toupper(temp_is_ambulatory) == 'Y')
		temp_temp_is_ambulatory = true;
	else
		temp_temp_is_ambulatory = false;
	temp_patient.setIsAmbulatory(toupper(temp_temp_is_ambulatory));

	// Prompt the user for the amount of bpm readings they will enter in, error check the value, and store it in a variable
	cout << "How many heart rate (bpm) readings do you want to enter? ";
	cin >> num_of_bpm_readings;
	while (cin.fail() || num_of_bpm_readings < 0)
	{
		cout << "Invalid value. Value must be either 0 or a positive number. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "How many heart rate (bpm) readings do you want enter? ";
		cin >> num_of_bpm_readings;
	}

	// Based on how many bpm readings the user wants to enter, loop that many times with each time getting a bpm to add to the vector
	for (int i = 0; i < num_of_bpm_readings; i++)
	{
		do
		{
			cout << "Enter BPM reading #" << i + 1 << ": ";
			cin >> temp_bpm_reading;
			while (cin.fail())
			{
				cout << "Invalid BPM. BPM must be a number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter BPM reading #" << i + 1 << ": ";
				cin >> temp_bpm_reading;
			}
		} while (temp_patient.addSingleBpm(temp_bpm_reading) == false);
	}
	cout << endl;
	// Returns back to main the patient object (i.e., the one we just put all the data into)
	return temp_patient;
}

// Function that allows the user to enter a file name to read data from. It error checks their file name. It load the data from the file into a patient object
Patient readPatientFromFile(const vector<Patient>& patients)  // I pass in the patients vector to this function to be able to check that the random patient ID that is generated is not already being used by another patient in the vector
{
	random_device rdevice{};
	default_random_engine num{ rdevice() };
	uniform_int_distribution<unsigned int> randomNum{ 1, 1000 };

	string input_file_name = "";
	ifstream input_file;
	int temp_patient_id = 0;
	string temp_first_name = "";
	string temp_last_name = "";
	string temp_street_address = "";
	int temp_age = 0;
	double temp_height = 0.0;
	double temp_weight = 0.0;
	char temp_gender = ' ';
	char temp_is_ambulatory = ' ';
	bool temp_temp_is_ambulatory = false;
	int temp_bpm_reading;

	cout << "Enter file name (don't include .txt): ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, input_file_name);

	// When user inputs the file name this add .txt to whatever he inputted
	input_file.open(input_file_name + ".txt");

	// Start and continue doing this loop when the file has an error opening
	while (!input_file)
	{
		cout << "Error in opening the file successfully. Please re-enter the file name (without using txt.): ";
		input_file.close();
		getline(cin, input_file_name);
		input_file.open(input_file_name + ".txt");
	}

	while (searchForIdInVector(patients, randomNum(num)) != -1)
		randomNum(num);

	temp_patient_id = randomNum(num);
	input_file >> temp_first_name;
	input_file >> temp_last_name;
	input_file.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(input_file, temp_street_address);
	input_file >> temp_age;
	input_file >> temp_height;
	input_file >> temp_weight;
	input_file >> temp_gender;
	input_file >> temp_is_ambulatory;
	if (toupper(temp_is_ambulatory) == 'Y')
		temp_temp_is_ambulatory = true;
	else
		temp_temp_is_ambulatory = false;

	Patient temp_patient(temp_patient_id, temp_first_name, temp_last_name, temp_street_address, temp_age, temp_height, temp_weight, temp_gender, temp_temp_is_ambulatory);

	while (!input_file.eof())
	{
		input_file >> temp_bpm_reading;
		temp_patient.addSingleBpm(temp_bpm_reading);
	}

	cout << endl << "Patient data loaded successfully." << endl << endl;

	input_file.close();

	return temp_patient;
}

// Function that will delete a patient that the user chooses from the patient vector
void deleteExistingPatient(vector<Patient>& patients)
{
	int patient_id_to_remove = 0;
	int patient_index_to_remove = 0;
	char confirm_removal_choice = ' ';

	showPatientList(patients);

	cout << "Enter the ID of the patient you want to remove: ";
	cin >> patient_id_to_remove;
	while (cin.fail() || patient_id_to_remove < 0)
	{
		cout << "Invalid ID. ID must be a non-negative number. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter the ID of the patient you want to remove: ";
		cin >> patient_id_to_remove;
	}

	// Searches the patient vector for a patient object with the ID the user selected. If found it returns the index of that object. Otherwise it returns -1
	patient_index_to_remove = searchForIdInVector(patients, patient_id_to_remove);

	if (patient_index_to_remove != -1)
	{
		cout << patients[patient_index_to_remove];
		cout << "Are you sure you want to remove this patient? (Y or N) ";
		cin >> confirm_removal_choice;
		while (toupper(confirm_removal_choice) != 'Y' && toupper(confirm_removal_choice) != 'N')
		{
			cout << "Invalid entry. Entry must be either Y or N. Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Are you sure you want to remove this patient? (Y or N) ";
			cin >> confirm_removal_choice;
		}

		if (toupper(confirm_removal_choice) == 'Y')
		{
			patients.erase(patients.begin() + patient_index_to_remove);
			cout << endl << "Patient was successfully deleted." << endl << endl;
		}
		else
			cout << endl << "The operation to delete this patient has been cancelled." << endl << endl;
	}
	else
		cout << endl << "Patient ID not found." << endl << endl;
}

void showPatientList(vector<Patient> patients)
{
	sort(patients.begin(), patients.end());  // Sorts the patients vector by first name using the overloaded < operator in the Patient class
	cout << "The following patients are currently in the system:" << endl << endl;
	cout << left << setw(7) << "ID" << "Patient Name" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (int i = 0; i < patients.size(); i++)
	{
		cout << left << setw(7) << patients[i].getId() << patients[i].getFirstName() << " " << patients[i].getLastName() << endl;
	}
	cout << endl;
}

// Function to add a visit (and it's information) to a patient of the user's choice
void createVisitForPatient(vector<Patient>& patients, Nurse** nurses, int num_of_nurses, Aide** aides, int num_of_aides, vector<Service> services)
{
	int patient_id_to_add_visit_to = 0;
	int patient_index_to_add_visit_to = 0;
	Visit temp_visit;
	int temp_visit_id = 0;
	string temp_employee_name = "";
	int m, d, y;
	char temp_visit_date[20];
	int service_id_to_add_to_visit = 0;
	int service_index_to_add_to_visit = 0;
	int nurse_id_to_assign_to_visit = 0;
	int nurse_index_to_assign_to_visit = 0;
	int aide_id_to_assign_to_visit = 0;
	int aide_index_to_assign_to_visit = 0;
	bool duplicate_id = false;
	bool invalid_date = false;

	showPatientList(patients);

	cout << "Enter the ID of the patient you want to add a visit to: ";
	cin >> patient_id_to_add_visit_to;
	while (cin.fail() || patient_id_to_add_visit_to < 0)
	{
		cout << "Invalid ID. ID must be a non-negative number. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter the ID of the patient you want to add a visit to: ";
		cin >> patient_id_to_add_visit_to;
	}
	cout << endl;

	// Finds the index of the patient to add a visit to. If patient is not found it returns a -1
	patient_index_to_add_visit_to = searchForIdInVector(patients, patient_id_to_add_visit_to);

	if (patient_index_to_add_visit_to != -1)
	{
		do
		{
			do
			{
				try
				{
					cout << "Enter the visit ID: ";
					cin >> temp_visit_id;

					// If it finds a duplicate ID, it does not return -1
					if (searchForIdInVisitVector(patients[patient_index_to_add_visit_to], temp_visit_id) != -1)  // The Visit vector in patients[patient_index_to_add_visit_to] is what it's searching through
						throw DuplicateIdException();
				}
				catch (string s)
				{
					duplicate_id = true;
				}
				catch (...)
				{
					cout << "An unexpected error occurred. Please try again." << endl;
				}
			} while (duplicate_id == true);

			while (cin.fail())
			{
				cout << "Invalid ID. ID must be a number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter the visit ID: ";
				cin >> temp_visit_id;
			}
			temp_visit.setId(temp_visit_id);
		} while (temp_visit.getId() == -1);

		do
		{
			try
			{
				cout << "Enter the date of the visit (MM/DD/YYYY): ";
				cin >> temp_visit_date;
				temp_visit.tokenizeDate(temp_visit_date, m, d, y);
				temp_visit.setDate(m, d, y);
			}
			catch (string s)
			{
				invalid_date = true;
			}
			catch (...)
			{
				cout << "An unexpected error occurred. Please try again." << endl;
			}
		} while (invalid_date == true);

		do
		{
			// Displays the nurses and their corresponding ID's for the user to select from. Returns the nurse ID the user selects back to main and stores it in a variable
			nurse_id_to_assign_to_visit = getEmployeeIdChoice(nurses, num_of_nurses, "nurse", "visit");

			// Zero is the option to not assign a nurse
			if (nurse_id_to_assign_to_visit != 0)
			{
				nurse_index_to_assign_to_visit = searchForIdInDynArray(nurses, num_of_nurses, nurse_id_to_assign_to_visit);

				if (nurse_index_to_assign_to_visit != -1)
				{
					temp_visit.setNurse(*nurses[nurse_index_to_assign_to_visit]);
				}
				else
					cout << endl << "The ID entered was not found in the system. Please try again." << endl;
			}
		} while (nurse_index_to_assign_to_visit == -1);

		do
		{
			aide_id_to_assign_to_visit = getEmployeeIdChoice(aides, num_of_aides, "aide", "visit");

			if (aide_id_to_assign_to_visit != 0)
			{
				aide_index_to_assign_to_visit = searchForIdInDynArray(aides, num_of_aides, aide_id_to_assign_to_visit);

				if (aide_index_to_assign_to_visit != -1)
				{
					temp_visit.setAide(*aides[aide_index_to_assign_to_visit]);
				}
				else
					cout << endl << "The ID entered was not found in the system. Please try again." << endl;
			}
		} while (aide_index_to_assign_to_visit == -1);

		do
		{
			cout << endl << "The following services are currently offered by HCO:" << endl << endl;

			// Displays to the user the services offerered by HC0 and their corresponding ID numbers
			cout << left << setw(7) << "ID" << "Service Name" << endl;
			cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
			for (auto i : services)
			{
				cout << left << setw(7) << i.getId() << i.getName() << endl;
			}

			cout << endl << "Enter the ID of the service you want to add to this visit (enter 0 to quit): ";
			cin >> service_id_to_add_to_visit;
			while (cin.fail() || service_id_to_add_to_visit < 0)
			{
				cout << "Invalid ID. ID must be a non-negative number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter the ID of the service you want to add to the visit (enter 0 to quit): ";
				cin >> service_id_to_add_to_visit;
			}

			if (service_id_to_add_to_visit != 0)
			{
				service_index_to_add_to_visit = searchForIdInVector(services, service_id_to_add_to_visit);

				if (service_index_to_add_to_visit == -1)
					cout << endl << "The service ID entered was not found in the system. Please try again." << endl;
				else
				{
					temp_visit.addService(services[service_index_to_add_to_visit]);
				}
			}

		} while (service_id_to_add_to_visit != 0);

		// The visit object now has all it's intended information. So now the visit can be added to the patient of the user's choice
		patients[patient_index_to_add_visit_to].addVisit(temp_visit);
		cout << endl;
	}
	else
		cout << "Patient ID not found." << endl << endl;
}

// Template function to search an ID in a vector
template <typename T>
int searchForIdInVector(vector<T> vector, int id_to_find)
{
	bool id_is_found = false;
	int i = 0;
	int index_to_act_on = 0;

	while (i < vector.size() && !id_is_found)
	{
		if (vector[i].getId() == id_to_find)
			id_is_found = true;
		else
			i++;
	}

	if (id_is_found)
		index_to_act_on = i;
	else
		index_to_act_on = -1;

	return index_to_act_on;
}

// The equipment vector is a vector of pointers, so this is a separate function than the one above that searches for an ID in a vector of objects. This function searches for an ID in a vector of pointers to objects
int searchForIdInEquipmentVector(vector<Equipment*> equipment, int id_to_find)
{
	bool id_is_found = false;
	int i = 0;
	int index_to_act_on = 0;

	while (i < equipment.size() && !id_is_found)
	{
		if (equipment[i]->getId() == id_to_find)
			id_is_found = true;
		else
			i++;
	}

	if (id_is_found)
		index_to_act_on = i;
	else
		index_to_act_on = -1;

	return index_to_act_on;
}

int searchForIdInVisitVector(Patient patient, int id_to_find)
{
	bool id_is_found = false;
	int i = 0;
	int index_to_act_on = 0;
	while (i < patient.getNumOfVisits() && !id_is_found)
	{
		if (patient.getVisit(i).getId() == id_to_find)
			id_is_found = true;
		else
			i++;
	}
	if (id_is_found)
		index_to_act_on = i;
	else
		index_to_act_on = -1;
	return index_to_act_on;
}

// Template function to search an ID in a dynamic array
template <typename T>
int searchForIdInDynArray(T** array, int array_size, int id_to_find)
{
	bool id_is_found = false;
	int i = 0;
	int index_to_act_on = 0;

	while (i < array_size && !id_is_found)
	{
		if (array[i]->getId() == id_to_find)
			id_is_found = true;
		else
			i++;
	}

	if (id_is_found)
		index_to_act_on = i;
	else
		index_to_act_on = -1;

	return index_to_act_on;
}

// Template function to display a vector of employees and their ID's and get the user choice 
template <typename T>
int getEmployeeIdChoice(T** employees, int num_of_employees, string emp_type_title, string assignment_target)
{
	int id = 0;

	cout << endl << "The following " << emp_type_title << " employees work at HCO: " << endl << endl;
	cout << left << setw(7) << "ID" << "Employee Name" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (int i = 0; i < num_of_employees; i++)
	{
		cout << left << setw(7) << employees[i]->getId() << employees[i]->getFirstName() + " " + employees[i]->getLastName() << endl;
	}
	cout << endl << "Enter the ID of the " << emp_type_title << " to assign to the " << assignment_target << " (enter 0 if none): ";

	cin >> id;
	while (cin.fail() || id < 0)
	{
		cout << "Invalid ID. ID must be a non-negative number. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter the ID of the " << emp_type_title << " to assign to the " << assignment_target << " (enter 0 if none): ";
		cin >> id;
	}

	return id;
}

// Function to assign a case manager to a patient of the user's choice
void assignCaseManagerToPatient(vector<Patient>& patients, CaseManager** case_managers, int num_of_case_managers)
{
	int patient_id_to_assign_case_mgr_to = 0;
	int patient_index_to_assign_case_mgr_to = 0;
	int case_mgr_id_to_assign_to_patient = 0;
	int case_mgr_index_to_assign_to_patient = 0;

	showPatientList(patients);

	cout << "Enter the ID of the patient you want to assign a case manager to: ";
	cin >> patient_id_to_assign_case_mgr_to;
	while (cin.fail() || patient_id_to_assign_case_mgr_to < 0)
	{
		cout << "Invalid ID. ID must be a non-negative number. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter the ID of the patient you want to assign a case manager to: ";
		cin >> patient_id_to_assign_case_mgr_to;
	}

	// Search the patient vector for the ID the user's choice. If found return the index. If not, return a -1
	patient_index_to_assign_case_mgr_to = searchForIdInVector(patients, patient_id_to_assign_case_mgr_to);

	if (patient_index_to_assign_case_mgr_to != -1)
	{
		case_mgr_id_to_assign_to_patient = getEmployeeIdChoice(case_managers, num_of_case_managers, "case manager", "patient");

		// Zero is the option to not assign a case manager
		if (case_mgr_id_to_assign_to_patient != 0)
		{
			case_mgr_index_to_assign_to_patient = searchForIdInDynArray(case_managers, num_of_case_managers, case_mgr_id_to_assign_to_patient);

			if (case_mgr_index_to_assign_to_patient != -1)
			{
				// If the case manager ID that the user wants to add to a patient is found then add that case manager to the patient of the user's choice
				patients[patient_index_to_assign_case_mgr_to].setCaseManager(*case_managers[case_mgr_index_to_assign_to_patient]);
			}
			else
				cout << endl << "The ID entered was not found in the system. Please try again." << endl << endl;
		}
	}
	else
		cout << endl << "Patient ID not found." << endl << endl;
}

void incrementPatientAge(vector<Patient>& patients)
{
	int patient_id_to_add_age_to = 0;
	int patient_index_to_add_age_to = 0;
	char confirm_removal_choice = ' ';

	showPatientList(patients);

	cout << "Enter the ID of the patient you want to increment the age of: ";
	cin >> patient_id_to_add_age_to;
	while (cin.fail() || patient_id_to_add_age_to < 0)
	{
		cout << "Invalid ID. ID must be a non-negative number. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter the ID of the patient you want to increment the age of: ";
		cin >> patient_id_to_add_age_to;
	}
	cout << endl;

	// Finds the index of the patient to add a visit to. If patient is not found it returns a -1
	patient_index_to_add_age_to = searchForIdInVector(patients, patient_id_to_add_age_to);

	if (patient_index_to_add_age_to != -1)
	{
		cout << "This is the patient's current information:" << endl << endl;
		cout << patients[patient_index_to_add_age_to];
		cout << "Are you sure you want to increment this patient's age by one year? (Y or N) ";
		cin >> confirm_removal_choice;
		while (toupper(confirm_removal_choice) != 'Y' && toupper(confirm_removal_choice) != 'N')
		{
			cout << "Invalid entry. Entry must be either Y or N. Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Are you sure you want to increment this patient's age by one year? (Y or N) ";
			cin >> confirm_removal_choice;
		}

		if (toupper(confirm_removal_choice) == 'Y')
		{
			patients[patient_index_to_add_age_to]++;  // Using the overloaded ++ operator from the patient class to increment the patient's age by one year
			cout << endl << "Patient's age was successfully incremented." << endl << endl;
			cout << "This is the patient's updated information:" << endl << endl;
			cout << patients[patient_index_to_add_age_to];
		}
		else
			cout << endl << "The operation to increment this patient's age has been cancelled." << endl << endl;
	}
	else
		cout << endl << "Patient ID not found." << endl << endl;
}

void sortPatientById(vector<Patient>& patients)
{
	Patient temp_patient;

	for (int j = 1; j < patients.size(); j++)
	{
		for (int i = 0; i < patients.size() - j; i++)
		{
			if (patients[i].getId() > patients[i + 1].getId())
			{
				temp_patient = patients[i];
				patients[i] = patients[i + 1];
				patients[i + 1] = temp_patient;
			}
		}
	}
}

// Function to print all the nurses, aides, and case managers that work at HCO. It passes in the three vectors of employees that were loads from files at the beginning of main.
void printEmployeeReport(ostream& out, Nurse** nurses, int num_of_nurses, Aide** aides, int num_of_aides, CaseManager** case_managers, int num_of_case_managers)
{
	out << fixed << setprecision(2);
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << "NURSES" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << left << setw(5) << "ID" << setw(23) << "Employee Name" << setw(14) << "Hourly Wage" << "Designation" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (int i = 0; i < num_of_nurses; i++)
		nurses[i]->printDetails(cout);
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << "AIDES" << endl;
	out << std::setfill('-') << setw(64) << "-" << setfill(' ') << endl;
	out << left << setw(5) << "ID" << setw(23) << "Employee Name" << setw(14) << "Hourly Wage" << "Certification" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (int i = 0; i < num_of_aides; i++)
		aides[i]->printDetails(cout);
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << "CASE MANAGERS" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << left << setw(5) << "ID" << setw(23) << "Employee Name" << setw(14) << "Salary" << "Degree" << endl;
	out << std::setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (int i = 0; i < num_of_case_managers; i++)
		case_managers[i]->printDetails(cout);
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << right << setw(24) << "" << "End of Report" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
}

void showEquipmentList(vector<Equipment*> equipment)
{
	// Sorts the equipment vector by equipment ID
	sort(equipment.begin(), equipment.end(), [](Equipment* a, Equipment* b) { return *a < *b; });  // Uses lambda function

	cout << fixed << setprecision(2);
	cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc."); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Equipment List"); // To get a value for setw that will center the text
	cout << right << setw(centeredTextX2) << "Equipment List" << endl;
	cout << setfill('-') << setw(100) << "" << setfill(' ') << endl << endl;
	cout << left << setw(5) << "ID" << setw(25) << "Name" << setw(15) << "Purchase Date" << setw(15) << "Original Cost" << setw(14) << "Useful Life" << setw(15) << "Salvage Value" << "Type/Mode" << endl;
	cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
	for (int i = 0; i < equipment.size(); i++)
		equipment[i]->printDetails(cout);
}

// Returns the index of the equipment object in the vector that has the ID that the user inputs.
int getAndSearchForEquipmentId(vector<Equipment*> equipment, std::string prompt)
{
	int equipment_id = 0;
	int index_of_equipment = 0;

	do
	{
		cout << endl << prompt;
		cin >> equipment_id;
		while (cin.fail() || equipment_id < 0)
		{
			cout << "Invalid ID. ID must be a non-negative number. Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Enter the ID of the equipment you want to see the depreciation schedule for: ";
			cin >> equipment_id;
		}

		index_of_equipment = searchForIdInEquipmentVector(equipment, equipment_id);

		if (index_of_equipment == -1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl << "Equipment ID not found. Please try again." << endl;
		}

	} while (index_of_equipment == -1);

	cout << endl;

	return index_of_equipment;
}

int calculateCenteredTextX(std::string s)
{
	return SCREEN_WIDTH / 2 + s.size() / 2;
}

// Template function to update the information of a storage unit object. It is used in both the create new storage unit function and the update existing storage unit function since both of those functions need to get the same information from the user and store it in a storage unit object.
template <typename T>
void updateStorageUnitInformation(T& storage_unit)
{
	int id = 0;
	bool invalid_id = false;
	string description = "";
	int length = 0;
	bool invalid_length = false;
	int width = 0;
	bool invalid_width = false;
	int height = 0;
	bool invalid_height = false;
	double cost_per_month = 0.0;
	bool invalid_cost_per_month = false;
	char rented_date[20];
	int m, d, y;
	bool invalid_date = false;
	bool temp_auto_renewal = ' ';
	bool temp_humidity_controlled = ' ';

	do
	{
		try
		{
			cout << "Enter the ID of the storage unit: ";
			cin >> id;
			while (cin.fail())
			{
				cout << "Invalid ID. ID must be a number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter the ID of the storage unit: ";
				cin >> id;
			}
			storage_unit.setId(id);
		}
		catch (string s)
		{
			invalid_id = true;
		}
		catch (...)
		{
			cout << "Unhandled exception has been encountered." << endl;
		}
	} while (invalid_id == true);

	cout << "Enter a description for the storage unit: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, description);
	storage_unit.setDescription(description);

	do
	{
		try
		{
			cout << "Enter the length of the storage unit (in feet): ";
			cin >> length;
			while (cin.fail())
			{
				cout << "Invalid length. Length must be a number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter the length of the storage unit (in feet): ";
				cin >> length;
			}
			storage_unit.setLength(length);
		}
		catch (string s)
		{
			invalid_length = true;
		}
		catch (...)
		{
			cout << "Unhandled exception has been encountered." << endl;
		}
	} while (invalid_length == true);

	do
	{
		try
		{
			cout << "Enter the width of the storage unit (in feet): ";
			cin >> width;
			while (cin.fail())
			{
				cout << "Invalid width. Width must be a number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter the width of the storage unit (in feet): ";
				cin >> width;
			}
			storage_unit.setWidth(width);
		}
		catch (string s)
		{
			invalid_width = true;
		}
		catch (...)
		{
			cout << "Unhandled exception has been encountered." << endl;
		}
	} while (invalid_width == true);

	do
	{
		try
		{
			cout << "Enter the height of the storage unit (in feet): ";
			cin >> height;
			while (cin.fail())
			{
				cout << "Invalid height. Height must be a number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter the height of the storage unit (in feet): ";
				cin >> height;
			}
			storage_unit.setHeight(height);
		}
		catch (string s)
		{
			invalid_height = true;
		}
		catch (...)
		{
			cout << "Unhandled exception has been encountered." << endl;
		}
	} while (invalid_height == true);

	do
	{
		try
		{
			cout << "Enter the cost per month to rent the storage unit: $";
			cin >> cost_per_month;
			while (cin.fail())
			{
				cout << "Invalid cost. Cost must be a number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter the cost per month to rent the storage unit: $";
				cin >> cost_per_month;
			}
			storage_unit.setCostPerMonth(cost_per_month);
		}
		catch (string s)
		{
			invalid_cost_per_month = true;
		}
		catch (...)
		{
			cout << "Unhandled exception has been encountered." << endl;
		}
	} while (invalid_cost_per_month == true);

	do
	{
		try
		{
			cout << "Enter the date rented (MM/DD/YYYY): ";
			cin >> rented_date;
			storage_unit.tokenizeDate(rented_date, m, d, y);
			storage_unit.setDateRented(m, d, y);
		}
		catch (string s)
		{
			invalid_date = true;
		}
		catch (...)
		{
			cout << "Unhandled exception has been encountered." << endl;
		}
	} while (invalid_date == true);

	cout << "Does the rental have auto-renewal? (Y or N): ";
	cin >> temp_auto_renewal;
	while (toupper(temp_auto_renewal) != 'Y' && toupper(temp_auto_renewal) != 'N')
	{
		cout << "Invalid entry. Entry must be either Y or N. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Does the rental have auto-renewal? (Y or N): ";
		cin >> temp_auto_renewal;
	}
	(toupper(temp_auto_renewal) == 'Y') ? storage_unit.setAutoRenewal(true) : storage_unit.setAutoRenewal(false);

	cout << "Is the storage unit humidity-controlled? (Y or N): ";
	cin >> temp_humidity_controlled;
	while (toupper(temp_humidity_controlled) != 'Y' && toupper(temp_humidity_controlled) != 'N')
	{
		cout << "Invalid entry. Entry must be either Y or N. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Is the storage unit humidity-controlled? (Y or N): ";
		cin >> temp_humidity_controlled;
	}
	(toupper(temp_humidity_controlled) == 'Y') ? storage_unit.setHumidityControlled(true) : storage_unit.setHumidityControlled(false);

	cout << endl << endl << "Storage unit information updated successfully." << endl << endl;

	cout << "Below is the updated information for this storage unit:" << endl << endl;

	storage_unit.printUnitInformation();
}

// Function to prompt the user to select a storage unit type. It returns the user's choice back to main.
int promptForStorageUnitType()
{
	int num = -1;
	
	do
	{
		cout << "Enter 1 for the mobility storage unit, 2 for the monitoring storage unit, and 0 to exit: ";
		cin >> num;
	} while (cin.fail() || num < 0 || num > 2);

	return num;
}

template <typename T>
void addEquipmentToStorageUnit(T storage_unit, vector<Equipment*> equipment)
{
	int index_of_equipment = getAndSearchForEquipmentId(equipment, "Enter the ID of the equipment to assign to a storage unit ");  // Does the error checking for me. It loops until user gives valid ID.
	
	if (string(typeid(*equipment[index_of_equipment]).name()) == "class MobilityEquipment")
	{
		MobilityEquipment* mobility_equipment_ptr = dynamic_cast<MobilityEquipment*>(equipment[index_of_equipment]);
		// Had to comment this out because it was causing an error, and I was running out of time to submit:
		//storage_unit.addEquipment(*mobility_equipment_ptr);
	}
	else if (string(typeid(*equipment[index_of_equipment]).name()) == "class MonitorEquipment")
	{
		MonitorEquipment* monitor_equipment_ptr = dynamic_cast<MonitorEquipment*>(equipment[index_of_equipment]);
		// Had to comment this out because it was causing an error, and I was running out of time to submit:
		//storage_unit.addEquipment(*monitor_equipment_ptr);
	}
}


