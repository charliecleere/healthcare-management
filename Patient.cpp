#include "Patient.h"

// Multi-argument constructor with default parameters
Patient::Patient(int i, std::string fn, std::string ln, std::string sa, int a, double h, double w, char g, bool ia, CaseManager cm)
{
	setId(i);
	setFirstName(fn);
	setLastName(ln);
	setStreetAddress(sa);
	setAge(a);
	setHeight(h);
	setWeight(w);
	setGender(g);
	setIsAmbulatory(ia);
	setCaseManager(cm);
}

// Destructor
Patient::~Patient()
{

}

// Set functions
void Patient::setId(int i)
{
	if (i < 0)
	{
		std::cout << "Invalid ID. ID cannot be negative. Please try again." << std::endl;
		id = -1;
	}
	else
		id = i;
}

void Patient::setFirstName(std::string fn)
{
	first_name = fn;
}

void Patient::setLastName(std::string ln)
{
	last_name = ln;
}

void Patient::setStreetAddress(std::string sa)
{
	street_address = sa;
}

void Patient::setAge(int a)
{
	if (a < 0 || a > 120)
	{
		std::cout << "Invalid age. Age must be a number between 1 and 120 (inclusive). Please try again." << std::endl;
		age = -1;
	}
	else
		age = a;
}

void Patient::setHeight(double h)
{
	if (h < 0)
	{
		std::cout << "Invalid height. Height cannot be negative. Please try again." << std::endl;
		height = -1;
	}
	else
		height = h;
}

void Patient::setWeight(double w)
{
	if (w < 0)
	{
		std::cout << "Invalid weight. Weight cannot be negative. Please try again." << std::endl;
		weight = -1;
	}
	else
		weight = w;
}

void Patient::setGender(char g)
{
	gender = g;
}

void Patient::setIsAmbulatory(bool ia)
{
	is_ambulatory = ia;
}

void Patient::setCaseManager(CaseManager cm)
{
	case_manager = cm;
}

// Get functions
int Patient::getId() const
{
	return id;
}

std::string Patient::getFirstName() const
{
	return first_name;
}

std::string Patient::getLastName() const
{
	return last_name;
}

std::string Patient::getStreetAddress() const
{
	return street_address;
}

int Patient::getAge() const
{
	return age;
}

double Patient::getHeight() const
{
	return height;
}

double Patient::getWeight() const
{
	return weight;
}

char Patient::getGender() const
{
	return gender;
}

bool Patient::getIsAmbulatory() const
{
	return is_ambulatory;
}

CaseManager Patient::getCaseManager() const
{
	return case_manager;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient)
{
	// I use "out" here instead of something like "cout" so that in my program both cout and output_file can be used when passed in as a parameter
	std::string display_gender = "";
	std::string display_is_ambulatory = "";
	out << std::setfill('-') << std::setw(64) << "" << std::setfill(' ') << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Patient ID:" << patient.getId() << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Name:" << patient.getFirstName() << " " << patient.getLastName() << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Address:" << patient.getStreetAddress() << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Age:" << patient.getAge() << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Height:" << patient.getHeight() << std::endl;
	out << std::setw(12) << "" << std::left << std::setw(26) << "Weight:" << patient.getWeight() << std::endl;
	(toupper(patient.getGender() == 'M')) ? (display_gender = "Male") : (display_gender = "Female");
	out << std::setw(12) << "" << std::left << std::setw(26) << "Gender:" << display_gender << std::endl;
	out << std::endl;
	// Translates the bool variable into the correct text that it should output
	(patient.getIsAmbulatory() == true) ? (display_is_ambulatory = "Patient is ambulatory") : (display_is_ambulatory = "Patient is not ambulatory");
	out << std::setw(12) << "" << "**** " << display_is_ambulatory << " ****" << std::endl << std::endl;
	if (patient.getBpmCount() > 0)
	{
		out << std::fixed << std::setprecision(2);
		out << std::setw(12) << "" << "Heart rate (bpm) readings:" << std::endl;
		out << std::setw(12) << "";
		for (int i = 0; i < patient.getBpmCount(); i++)
			out << patient.getSingleBpm(i) << "  ";
		out << std::endl << std::endl;
		out << std::setw(19) << "" << "Patient Statistics" << std::endl << std::endl;
		out << std::setw(12) << "" << std::left << std::setw(26) << "Number of bpm readings: " << patient.getBpmCount() << std::endl;
		out << std::setw(12) << "" << std::left << std::setw(26) << "Average heart rate (bpm): " << patient.calculateAvgBpm() << std::endl;
		out << std::setw(12) << "" << std::left << std::setw(26) << "Minimum heart rate (bpm): " << patient.findMinBpm() << std::endl;
		out << std::setw(12) << "" << std::left << std::setw(26) << "Maximum heart rate (bpm): " << patient.findMaxBpm() << std::endl << std::endl;
	}
	// Print the case manager's name if there is one
	out << std::setw(12) << "" << "Case manager: " << patient.getCaseManager().getFirstName() << " " << patient.getCaseManager().getLastName() << std::endl << std::endl;
	// Prints all the visits (if there are any) and the data for each visit for this patient
	if (patient.visits.size() > 0)
	{
		out << std::setw(19) << "" << "Visit Information" << std::endl << std::endl;
		for (int j = 0; j < patient.visits.size(); j++)
		{
			patient.visits[j].printVisit(out);
		}
	}
	return out;
}

// Overloaded less-than operator to compare patients by first name for sorting
bool Patient::operator<(const Patient& other) const
{
	if (this->getFirstName() < other.getFirstName())
		return true;
	else
		return false;
}

// Pre-increment operator to increment the patient's age by 1 year
Patient Patient::operator++()
{
	setAge(getAge() + 1);
	return *this;
}

// Post-increment operator to increment the patient's age by 1 year
Patient Patient::operator++(int)
{
	Patient temp = *this;
	setAge(getAge() + 1);
	return temp;
}

// For this function we need to pass in the bpm reading so we can add that reading to the bpms vector
bool Patient::addSingleBpm(int temp_bpm_reading)
{
	bool is_valid = true;
	if (temp_bpm_reading < 0)
	{
		std::cout << "Invalid BPM. BPM cannot be negative. Please try again." << std::endl;
		is_valid = false;
	}
	else
		bpms.push_back(temp_bpm_reading);
	return is_valid;
}

int Patient::getSingleBpm(int index) const
{
	int temp_bpm = 0;

	if (index < 0 || index >= bpms.size())
		temp_bpm = -1;
	else
		temp_bpm = bpms[index];
	return temp_bpm;
}

int Patient::getBpmCount() const
{
	return bpms.size();
}

// Bubble sort to sort the bpms vector in my class
void Patient::sortBpms()
{
	int temp_bpm;

	for (int j = 1; j < bpms.size(); j++)
	{
		for (int i = 0; i < bpms.size() - j; i++)
		{
			if (bpms.at(i) > bpms.at(i + 1))
			{
				temp_bpm = bpms.at(i);
				bpms.at(i) = bpms.at(i + 1);
				bpms.at(i + 1) = temp_bpm;
			}
		}
	}
}

// Returns back the smallest bpm in the bpms vector
int Patient::findMinBpm() const
{
	int temp_min_bpm = 0;

	if (bpms.size() != 0)
	{
		int minIndex = 0;
		for (int i = 1; i < bpms.size(); i++)
			if (bpms[minIndex] > bpms[i])
				minIndex = i;

		temp_min_bpm = bpms[minIndex];
	}
	else
		temp_min_bpm = -1;
	return temp_min_bpm;
}

// Returns back the largest bpm in the bpms vector
int Patient::findMaxBpm() const
{
	int temp_max_bpm = 0;

	if (bpms.size() != 0)
	{
		int maxIndex = 0;
		for (int i = 1; i < bpms.size(); i++)
			if (bpms[maxIndex] < bpms[i])
				maxIndex = i;

		temp_max_bpm = bpms[maxIndex];
	}
	else
		temp_max_bpm = -1;
	return temp_max_bpm;

}

// Returns the average bpm of the bpms vector
double Patient::calculateAvgBpm() const
{
	int temp_avg_bpm = 0;

	if (bpms.size() != 0)
	{
		int sum = 0;

		for (int i = 0; i < bpms.size(); i++)
			sum = sum + bpms[i];

		temp_avg_bpm = static_cast<double>(sum) / bpms.size();
	}
	else
		temp_avg_bpm = -1;
	return temp_avg_bpm;
}

// Function to add a visit to a patient
void Patient::addVisit(Visit v)
{
	visits.push_back(v);
}

Visit Patient::getVisit(int index) const
{
	Visit temp_visit;
	if (index < 0 || index >= visits.size())
		temp_visit = Visit();
	else
		temp_visit = visits[index];
	return temp_visit;
}

int Patient::getNumOfVisits() const
{
	return visits.size();
}
