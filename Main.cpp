#include <fstream>
#include <random>
#include <algorithm>
#include <cctype>
#include <limits>
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

// Capacity limits for the explicitly managed employee arrays.
const int MAX_NUM_OF_NURSES = 50;
const int MAX_NUM_OF_AIDES = 50;
const int MAX_NUM_OF_CASE_MANAGERS = 50;
const string SERVICES_FILE_NAME = "Services";
const string NURSES_DATA_FILE_NAME = "Nurses";
const string AIDES_DATA_FILE_NAME = "Aides";
const string CASE_MANAGERS_DATA_FILE_NAME = "Case Managers";
const string EQUIPMENT_FILE_NAME = "Equipment";
const int MAX_NUM_OF_PATIENTS = 50;
const int SCREEN_WIDTH = 64;


// Application workflow and reporting helpers.
void loadServicesFromFile(vector<Service>& services, bool& files_are_open);

template <typename T>
void loadEmployeeData(T**& employees, const string& file_name, bool& files_are_open);

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

void showPatientList(const vector<Patient>& patients);

void createVisitForPatient(vector<Patient>& patients, Nurse** nurses, int num_of_nurses, Aide** aides, int num_of_aides, const vector<Service>& services);

template <typename T>
int searchForIdInVector(const vector<T>& values, int id_to_find);

int searchForIdInEquipmentVector(const vector<Equipment*>& equipment, int id_to_find);

int searchForIdInVisitVector(const Patient& patient, int id_to_find);

template <typename T>
int searchForIdInDynArray(T** array, int array_size, int id_to_find);

template <typename T>
int getEmployeeIdChoice(T** employees, int num_of_employees, const string& emp_type_title, const string& assignment_target);

void assignCaseManagerToPatient(vector<Patient>& patients, CaseManager** case_managers, int num_of_case_managers);

void incrementPatientAge(vector<Patient>& patients);

void sortPatientById(vector<Patient>& patients);

void printEmployeeReport(ostream& out, Nurse** nurses, int num_of_nurses, Aide** aides, int num_of_aides, CaseManager** case_managers, int num_of_case_managers);

void showEquipmentList(const vector<Equipment*>& equipment);

int getAndSearchForEquipmentId(const vector<Equipment*>& equipment, const std::string& prompt);

int calculateCenteredTextX(const std::string& s);

// Clear the visible terminal before displaying the next workflow screen.
void clearScreen();

void waitForEnter(bool clear_after = true);

template <typename T>
void updateStorageUnitInformation(T& storage_unit);

int promptForStorageUnitType();

void addEquipmentToStorageUnit(StorageUnit<MonitorEquipment>& monitor_equipment_unit,
	StorageUnit<MobilityEquipment>& mobility_equipment_unit,
	const vector<Equipment*>& equipment);

int main()
{
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
	StorageUnit<MonitorEquipment> monitor_equipment_unit;
	StorageUnit<MobilityEquipment> mobility_equipment_unit;
	int unit_type_choice = 0;

	for (int i = 0; i < MAX_NUM_OF_NURSES; i++)
		nurses[i] = nullptr;

	for (int i = 0; i < MAX_NUM_OF_AIDES; i++)
		aides[i] = nullptr;

	for (int i = 0; i < MAX_NUM_OF_CASE_MANAGERS; i++)
		case_managers[i] = nullptr;

	loadServicesFromFile(services, files_are_open);

	loadEmployeeData(nurses, NURSES_DATA_FILE_NAME, files_are_open);
	loadEmployeeData(aides, AIDES_DATA_FILE_NAME, files_are_open);
	loadEmployeeData(case_managers, CASE_MANAGERS_DATA_FILE_NAME, files_are_open);

	loadEquipmentData(equipment, files_are_open);

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

		// Keep employee reports alphabetized by last name.
		sortEmployees(nurses, num_of_nurses);
		sortEmployees(aides, num_of_aides);
		sortEmployees(case_managers, num_of_case_managers);

		do
		{
			main_menu_choice = printMainMenu();

			switch (main_menu_choice)
			{
			case 1: // Patient management.
				do
				{
					patient_menu_choice = printPatientMenu();

					switch (patient_menu_choice)
					{
					case 1: // Add a patient manually.
						if (patients.size() >= MAX_NUM_OF_PATIENTS)
						{
							cout << "Health Care Options, Inc. is not accepting anymore new patients at this time." << endl << endl;
						}
						else
						{
							patients.push_back(buildPatientFromUserInput(patients));
						}
						break;
					case 2: // Import a patient from a file.
						if (patients.size() >= MAX_NUM_OF_PATIENTS)
						{
							cout << "Health Care Options, Inc. is not accepting anymore new patients at this time." << endl << endl;
						}
						else
						{
							patients.push_back(readPatientFromFile(patients));
						}
						break;
					case 3: // Delete a patient.
						deleteExistingPatient(patients);
						break;
					case 4: // Create a visit.
						createVisitForPatient(patients, nurses, num_of_nurses, aides, num_of_aides, services);
						break;
					case 5: // Assign a case manager.
						assignCaseManagerToPatient(patients, case_managers, num_of_case_managers);
						break;
					case 6: // Increment a patient's age.
						incrementPatientAge(patients);
						break;
					case 7: // Print the patient report.
						sortPatientById(patients);
						for (size_t i = 0; i < patients.size(); i++)
						{
							patients[i].sortBpms();
							cout << patients[i];
						}

						cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
						cout << right << setw(24) << "" << "End of Report" << endl;
						cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
						break;
					case 8: // Save the patient report to a file.
						sortPatientById(patients);
						cout << "Please enter the name of the file to save the patient report to (don't include .txt): ";

						cin.ignore(numeric_limits<streamsize>::max(), '\n');

						getline(cin, output_file_name);
						output_file.open(output_file_name + ".txt");

						for (size_t i = 0; i < patients.size(); i++)
						{
							patients[i].sortBpms();
							output_file << patients[i];
						}

						output_file << setfill('-') << setw(64) << "" << setfill(' ') << endl;
						output_file << right << setw(24) << "" << "End of Report" << endl;
						output_file << setfill('-') << setw(64) << "" << setfill(' ') << endl;

						output_file.close();

						cout << endl << "The patient information was successfully saved to a file." << endl << endl;
						break;
					case 9: // Return to the main menu.
						break;
					default:
						cout << "Error. Invalid menu choice. Please try again." << endl;
						break;
					}
					if (patient_menu_choice != 9)
						waitForEnter();
				} while (patient_menu_choice != 9);
				break;
			case 2: // Employee management.
				do
				{
					employee_menu_choice = printEmployeeMenu();

					switch (employee_menu_choice)
					{
					case 1: // Print the employee report.
						printEmployeeReport(cout, nurses, num_of_nurses, aides, num_of_aides, case_managers, num_of_case_managers);
						break;
					case 2: // Return to the main menu.
						break;
					default:
						cout << "Error. Invalid menu choice. Please try again." << endl;
						break;
					}
					if (employee_menu_choice != 2)
						waitForEnter();
				} while (employee_menu_choice != 2);
				break;
			case 3: // Equipment management.
				do
				{
					equipment_menu_choice = printEquipmentMenu();

					switch (equipment_menu_choice)
					{
					case 1: // Print the equipment list.
						showEquipmentList(equipment);
						break;
					case 2: // Print an equipment depreciation schedule.
						showEquipmentList(equipment);
						equipment[getAndSearchForEquipmentId(equipment, "Enter the ID of the equipment you want to see the depreciation schedule for: ")]->depreciate(cout);
						break;
					case 3: // Update storage-unit information.
						unit_type_choice = promptForStorageUnitType();
						
						switch (unit_type_choice)
						{
						case 1: // Update the mobility unit.
							updateStorageUnitInformation(mobility_equipment_unit);
							break;
						case 2: // Update the monitor unit.
							updateStorageUnitInformation(monitor_equipment_unit);
							break;
						case 0: // Cancel.
							break;
						default:
							cout << "Error. Invalid menu choice. Please try again." << endl;
							break;
						}
						break;
					case 4: // Add equipment to a storage unit.
						showEquipmentList(equipment);
						addEquipmentToStorageUnit(monitor_equipment_unit, mobility_equipment_unit, equipment);
						break;
					case 5: // View storage-unit information.
						unit_type_choice = promptForStorageUnitType();

						switch (unit_type_choice)
						{
						case 1: // View the mobility unit.
							mobility_equipment_unit.printUnitInformation();
							mobility_equipment_unit.printInventory("Mobility");
							break;
						case 2: // View the monitor unit.
							monitor_equipment_unit.printUnitInformation();
							monitor_equipment_unit.printInventory("Monitor");
							break;
						case 0: // Cancel.
							break;
						default:
							cout << "Error. Invalid menu choice. Please try again." << endl;
							break;
						}
						break;
					case 6: // Return to the main menu.
						break;
					default:
						cout << "Error. Invalid menu choice. Please try again." << endl;
						break;
					}
					if (equipment_menu_choice != 6)
						waitForEnter();
				} while (equipment_menu_choice != 6);
				break;
			case 4: // Exit the application.
				cout << "Thank you for using the Patient Management System." << endl << endl;
				break;
			default:
				cout << "Error. Invalid menu choice. Please try again." << endl;
				break;
			}
		} while (main_menu_choice != 4);

		// Release the explicitly managed employee and equipment objects.
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

		for (size_t i = 0; i < equipment.size(); i++)
		{
			delete equipment[i];
			equipment[i] = nullptr;
		}
	}
	else
	{
		cout << endl;
		waitForEnter(false);
	}

	return 0;
}

// Function definitions

// Load service identifiers and names from the bundled data file.
void loadServicesFromFile(vector<Service>& services, bool& files_are_open)
{
	ifstream input_file;
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
		while (input_file >> temp_service_id)
		{
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_service_name);
			services.emplace_back(temp_service_id, temp_service_name);
		}
	}
	input_file.close();
}

// Load one employee type into its explicitly managed pointer array.
template <typename T>
void loadEmployeeData(T** &employees, const string& file_name, bool& files_are_open)
{
	ifstream input_file;
	int temp_employee_id = 0;
	string temp_emp_first_name = "";
	string temp_emp_last_name = "";
	double temp_earnings = 0.0;
	string temp_credentials = "";
	int i = 0;

	input_file.open(file_name + ".txt");

	if (!input_file)
	{
		cout << "Error opening a file. Please fix the file and restart the program." << endl;
		files_are_open = false;
	}
	else
	{
		while (input_file >> temp_employee_id)
		{
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_emp_first_name);
			getline(input_file, temp_emp_last_name);
			if (!(input_file >> temp_earnings))
				break;
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_credentials);

			employees[i++] = new T(temp_employee_id, temp_emp_first_name, temp_emp_last_name, temp_earnings, temp_credentials);
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
	
	input_file.open(EQUIPMENT_FILE_NAME + ".txt");

	if (!input_file)
	{
		cout << "Error opening a file. Please fix the file and restart the program." << endl;
		files_are_open = false;
	}
	else
	{
		while (input_file >> temp_equipment_id)
		{
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_equipment_name);
			if (!(input_file >> temp_purchase_date >> temp_original_cost >> temp_useful_life >> temp_salvage_value))
				break;
			input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(input_file, temp_type_or_mode);

			Equipment* item = nullptr;
			if (temp_useful_life <= 5)
				item = new MonitorEquipment(temp_equipment_id, temp_equipment_name, temp_original_cost, temp_useful_life, temp_salvage_value, temp_type_or_mode);
			else
				item = new MobilityEquipment(temp_equipment_id, temp_equipment_name, temp_original_cost, temp_useful_life, temp_salvage_value, temp_type_or_mode);

			item->tokenizeDate(temp_purchase_date, m, d, y);
			item->setPurchaseDate(m, d, y);
			equipment.push_back(item);
		}
	}
	input_file.close();
}

// Sort an employee pointer array by last name.
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

		temp_employee = employees[smallest_index];
		employees[smallest_index] = employees[index];
		employees[index] = temp_employee;
	}
}

// Display the main menu and return a validated selection.
int printMainMenu()
{
	int choice = ' ';

	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc.");
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Management");
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
	clearScreen();
	return choice;
}

// Display patient-management actions and return a validated selection.
int printPatientMenu()
{
	int choice = ' ';
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc.");
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Patient Management");
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
	clearScreen();
	return choice;
}

// Display employee-management actions and return a validated selection.
int printEmployeeMenu()
{
	int choice = ' ';
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc.");
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Employee Management");
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
	clearScreen();
	return choice;
}

// Display equipment-management actions and return a validated selection.
int printEquipmentMenu()
{
	int choice = ' ';
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc.");
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Equipment Management");
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
	clearScreen();
	return choice;
}

// Collect and validate a new patient's data, including a unique generated ID.
Patient buildPatientFromUserInput(const vector<Patient>& patients)
{
	random_device rdevice{};
	default_random_engine num{ rdevice() };
	uniform_int_distribution<unsigned int> randomNum{ 1, 1000 };

	// Collect input in local values before constructing the patient.
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

	do
	{
		temp_patient_id = static_cast<int>(randomNum(num));
	} while (searchForIdInVector(patients, temp_patient_id) != -1);
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
	temp_patient.setGender(static_cast<char>(toupper(static_cast<unsigned char>(temp_gender))));

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
	temp_patient.setIsAmbulatory(temp_temp_is_ambulatory);

	// Validate the number of BPM readings to collect.
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

	// Collect each requested BPM reading.
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
	return temp_patient;
}

// Import a patient record from a named demo-data file and assign a unique ID.
Patient readPatientFromFile(const vector<Patient>& patients)
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

	input_file.open(input_file_name + ".txt");

	// Keep prompting until the requested file can be opened.
	while (!input_file)
	{
		cout << "Error in opening the file successfully. Please re-enter the file name (without using txt.): ";
		input_file.close();
		getline(cin, input_file_name);
		input_file.open(input_file_name + ".txt");
	}

	do
	{
		temp_patient_id = static_cast<int>(randomNum(num));
	} while (searchForIdInVector(patients, temp_patient_id) != -1);
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

	while (input_file >> temp_bpm_reading)
		temp_patient.addSingleBpm(temp_bpm_reading);

	cout << endl << "Patient data loaded successfully." << endl << endl;

	input_file.close();

	return temp_patient;
}

// Confirm and remove a patient selected by ID.
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

void showPatientList(const vector<Patient>& patients)
{
	vector<Patient> sorted_patients = patients;
	sort(sorted_patients.begin(), sorted_patients.end());  // Sorts the patients vector by first name using the overloaded < operator in the Patient class
	cout << "The following patients are currently in the system:" << endl << endl;
	cout << left << setw(7) << "ID" << "Patient Name" << endl;
	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (size_t i = 0; i < sorted_patients.size(); i++)
	{
		cout << left << setw(7) << sorted_patients[i].getId() << sorted_patients[i].getFirstName() << " " << sorted_patients[i].getLastName() << endl;
	}
	cout << endl;
}

// Create and attach a visit to a selected patient.
void createVisitForPatient(vector<Patient>& patients, Nurse** nurses, int num_of_nurses, Aide** aides, int num_of_aides, const vector<Service>& services)
{
	int patient_id_to_add_visit_to = 0;
	int patient_index_to_add_visit_to = 0;
	Visit temp_visit;
	int temp_visit_id = 0;
	int m, d, y;
	char temp_visit_date[20];
	int service_id_to_add_to_visit = 0;
	int service_index_to_add_to_visit = 0;
	int nurse_id_to_assign_to_visit = 0;
	int nurse_index_to_assign_to_visit = 0;
	int aide_id_to_assign_to_visit = 0;
	int aide_index_to_assign_to_visit = 0;

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

	patient_index_to_add_visit_to = searchForIdInVector(patients, patient_id_to_add_visit_to);

	if (patient_index_to_add_visit_to != -1)
	{
		bool duplicate_id = false;
		do
		{
			duplicate_id = false;
			cout << "Enter the visit ID: ";
			cin >> temp_visit_id;
			if (cin.fail() || temp_visit_id < 0)
			{
				cout << "Invalid ID. ID must be a non-negative number. Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				duplicate_id = true;
				continue;
			}

			try
			{
				if (patients[patient_index_to_add_visit_to].hasVisitId(temp_visit_id))
					throw DuplicateIdException();
			}
			catch (const DuplicateIdException& error)
			{
				cout << error.what() << " Please enter a different visit ID." << endl;
				duplicate_id = true;
			}
		} while (duplicate_id);
		temp_visit.setId(temp_visit_id);

		bool invalid_date = false;
		do
		{
			invalid_date = false;
			try
			{
				cout << "Enter the date of the visit (MM/DD/YYYY): ";
				cin >> temp_visit_date;
				temp_visit.tokenizeDate(temp_visit_date, m, d, y);
				temp_visit.setDate(m, d, y);
			}
			catch (const InvalidDateException& error)
			{
				cout << error.what() << " Please use MM/DD/YYYY." << endl;
				invalid_date = true;
			}
		} while (invalid_date);

		do
		{
			// Display available nurses and collect the selected ID.
			nurse_id_to_assign_to_visit = getEmployeeIdChoice(nurses, num_of_nurses, "nurse", "visit");

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

			// Display available services and collect the selected ID.
			cout << left << setw(7) << "ID" << "Service Name" << endl;
			cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
			for (const auto& i : services)
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

		// Attach the completed visit to the selected patient.
		patients[patient_index_to_add_visit_to].addVisit(temp_visit);
		cout << endl;
	}
	else
		cout << "Patient ID not found." << endl << endl;
}

// Return the index of a matching object ID, or -1 when absent.
template <typename T>
int searchForIdInVector(const vector<T>& values, int id_to_find)
{
	for (size_t i = 0; i < values.size(); ++i)
	{
		if (values[i].getId() == id_to_find)
			return static_cast<int>(i);
	}
	return -1;
}

// Search the pointer-based equipment collection by ID.
int searchForIdInEquipmentVector(const vector<Equipment*>& equipment, int id_to_find)
{
	for (size_t i = 0; i < equipment.size(); ++i)
	{
		if (equipment[i]->getId() == id_to_find)
			return static_cast<int>(i);
	}
	return -1;
}

int searchForIdInVisitVector(const Patient& patient, int id_to_find)
{
	for (int i = 0; i < patient.getNumVisits(); ++i)
	{
		if (patient.getVisit(i).getId() == id_to_find)
			return i;
	}
	return -1;
}

// Search an explicitly managed pointer array by ID.
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

// Display employee choices and return the selected ID.
template <typename T>
int getEmployeeIdChoice(T** employees, int num_of_employees, const string& emp_type_title, const string& assignment_target)
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

// Assign a selected case manager to a patient.
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

	patient_index_to_assign_case_mgr_to = searchForIdInVector(patients, patient_id_to_assign_case_mgr_to);

	if (patient_index_to_assign_case_mgr_to != -1)
	{
		case_mgr_id_to_assign_to_patient = getEmployeeIdChoice(case_managers, num_of_case_managers, "case manager", "patient");

		if (case_mgr_id_to_assign_to_patient != 0)
		{
			case_mgr_index_to_assign_to_patient = searchForIdInDynArray(case_managers, num_of_case_managers, case_mgr_id_to_assign_to_patient);

			if (case_mgr_index_to_assign_to_patient != -1)
			{
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
			patients[patient_index_to_add_age_to]++;
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

	for (size_t j = 1; j < patients.size(); j++)
	{
		for (size_t i = 0; i < patients.size() - j; i++)
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

// Write the nurse, aide, and case-manager report.
void printEmployeeReport(ostream& out, Nurse** nurses, int num_of_nurses, Aide** aides, int num_of_aides, CaseManager** case_managers, int num_of_case_managers)
{
	out << fixed << setprecision(2);
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << "NURSES" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << left << setw(5) << "ID" << setw(23) << "Employee Name" << setw(14) << "Hourly Wage" << "Designation" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (int i = 0; i < num_of_nurses; i++)
		nurses[i]->printDetails(out);
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << "AIDES" << endl;
	out << std::setfill('-') << setw(64) << "-" << setfill(' ') << endl;
	out << left << setw(5) << "ID" << setw(23) << "Employee Name" << setw(14) << "Hourly Wage" << "Certification" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (int i = 0; i < num_of_aides; i++)
		aides[i]->printDetails(out);
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << "CASE MANAGERS" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << left << setw(5) << "ID" << setw(23) << "Employee Name" << setw(14) << "Salary" << "Degree" << endl;
	out << std::setfill('-') << setw(64) << "" << setfill(' ') << endl;
	for (int i = 0; i < num_of_case_managers; i++)
		case_managers[i]->printDetails(out);
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
	out << right << setw(24) << "" << "End of Report" << endl;
	out << setfill('-') << setw(64) << "" << setfill(' ') << endl;
}

void showEquipmentList(const vector<Equipment*>& equipment)
{
	vector<Equipment*> sorted_equipment = equipment;
	sort(sorted_equipment.begin(), sorted_equipment.end(), [](Equipment* a, Equipment* b) { return *a < *b; });

	cout << fixed << setprecision(2);
	cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
	int centeredTextX1 = calculateCenteredTextX("Health Case Options, Inc.");
	cout << right << setw(centeredTextX1) << "Health Care Options, Inc." << endl;
	int centeredTextX2 = calculateCenteredTextX("Equipment List");
	cout << right << setw(centeredTextX2) << "Equipment List" << endl;
	cout << setfill('-') << setw(100) << "" << setfill(' ') << endl << endl;
	cout << left << setw(5) << "ID" << setw(25) << "Name" << setw(15) << "Purchase Date" << setw(15) << "Original Cost" << setw(14) << "Useful Life" << setw(15) << "Salvage Value" << "Type/Mode" << endl;
	cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
	for (Equipment* item : sorted_equipment)
		item->printDetails(cout);
}

// Return the selected equipment index, retrying until the ID is found.
int getAndSearchForEquipmentId(const vector<Equipment*>& equipment, const std::string& prompt)
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
			cout << endl << prompt;
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

int calculateCenteredTextX(const std::string& s)
{
	return SCREEN_WIDTH / 2 + static_cast<int>(s.size()) / 2;
}

void clearScreen()
{
	cout << "\x1B[2J\x1B[H" << flush;
}

void waitForEnter(bool clear_after)
{
	if (cin.fail())
		cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl << "Press Enter to continue...";
	cin.get();
	if (clear_after)
		clearScreen();
}

template <typename Value, typename T>
void promptAndSetStorageValue(T& storage_unit, const string& prompt, void (T::*setter)(Value))
{
	while (true)
	{
		Value value{};
		cout << prompt;
		cin >> value;
		if (cin.fail())
		{
			cout << "The value entered was not a number. Please try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		try
		{
			(storage_unit.*setter)(value);
			return;
		}
		catch (const NegativeNumberException& error)
		{
			cout << error.what() << " Please try again." << endl;
		}
	}
}

char promptForYesNo(const string& prompt)
{
	char choice{};
	while (true)
	{
		cout << prompt;
		cin >> choice;
		choice = static_cast<char>(toupper(static_cast<unsigned char>(choice)));
		if (choice == 'Y' || choice == 'N')
			return choice;

		cout << "Invalid entry. Entry must be either Y or N. Please try again." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

template <typename T>
void updateStorageUnitInformation(T& storage_unit)
{
	char rented_date[20];
	int month{};
	int day{};
	int year{};
	string description;

	promptAndSetStorageValue<int>(storage_unit, "Enter the ID of the storage unit: ", &T::setId);
	cout << "Enter a description for the storage unit: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, description);
	storage_unit.setDescription(description);
	promptAndSetStorageValue<int>(storage_unit, "Enter the length of the storage unit (in feet): ", &T::setLength);
	promptAndSetStorageValue<int>(storage_unit, "Enter the width of the storage unit (in feet): ", &T::setWidth);
	promptAndSetStorageValue<int>(storage_unit, "Enter the height of the storage unit (in feet): ", &T::setHeight);
	promptAndSetStorageValue<double>(storage_unit, "Enter the cost per month to rent the storage unit: $", &T::setCostPerMonth);

	while (true)
	{
		try
		{
			cout << "Enter the date rented (MM/DD/YYYY): ";
			cin >> rented_date;
			storage_unit.tokenizeDate(rented_date, month, day, year);
			storage_unit.setDateRented(month, day, year);
			break;
		}
		catch (const InvalidDateException& error)
		{
			cout << error.what() << " Please use MM/DD/YYYY." << endl;
		}
	}

	storage_unit.setAutoRenewal(promptForYesNo("Does the rental have auto-renewal? (Y or N): ") == 'Y');
	storage_unit.setHumidityControlled(promptForYesNo("Is the storage unit humidity-controlled? (Y or N): ") == 'Y');

	cout << endl << endl << "Storage unit information updated successfully." << endl << endl;

	cout << "Below is the updated information for this storage unit:" << endl << endl;

	storage_unit.printUnitInformation();
}

// Prompt for a storage-unit type or cancellation.
int promptForStorageUnitType()
{
	while (true)
	{
		int num = -1;
		cout << "Enter 1 for the mobility storage unit, 2 for the monitoring storage unit, and 0 to exit: ";
		cin >> num;
		if (!cin.fail() && num >= 0 && num <= 2)
		{
			clearScreen();
			return num;
		}

		cout << "Invalid selection. Please enter 0, 1, or 2." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void addEquipmentToStorageUnit(StorageUnit<MonitorEquipment>& monitor_equipment_unit,
	StorageUnit<MobilityEquipment>& mobility_equipment_unit,
	const vector<Equipment*>& equipment)
{
	const int index_of_equipment = getAndSearchForEquipmentId(equipment, "Enter the ID of the equipment to assign to a storage unit: ");
	Equipment* selected_equipment = equipment[static_cast<size_t>(index_of_equipment)];

	if (monitor_equipment_unit.containsEquipmentId(selected_equipment->getId()) || mobility_equipment_unit.containsEquipmentId(selected_equipment->getId()))
	{
		cout << "This item has already been added to a storage unit. Operation cancelled." << endl;
		return;
	}

	if (typeid(*selected_equipment) == typeid(MobilityEquipment))
	{
		auto* mobility_equipment = dynamic_cast<MobilityEquipment*>(selected_equipment);
		mobility_equipment_unit.addEquipment(*mobility_equipment);
		cout << "Equipment successfully added to the mobility storage unit." << endl;
		mobility_equipment_unit.printUnitInformation();
		mobility_equipment_unit.printInventory("Mobility");
	}
	else if (typeid(*selected_equipment) == typeid(MonitorEquipment))
	{
		auto* monitor_equipment = dynamic_cast<MonitorEquipment*>(selected_equipment);
		monitor_equipment_unit.addEquipment(*monitor_equipment);
		cout << "Equipment successfully added to the monitoring storage unit." << endl;
		monitor_equipment_unit.printUnitInformation();
		monitor_equipment_unit.printInventory("Monitor");
	}
}


