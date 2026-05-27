#include "Patient.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Vitals.h"
#include "AlertLevelStrategy.h"
#include "AlertLevelStrategyFactory.h"


using namespace std;

const std::string Diagnosis::CORDYCEPS_BRAIN_INFECTION = "Cordyceps Brain Infection";
const std::string Diagnosis::KEPRALS_SYNDROME = "Kepral’s Syndrome";
const std::string Diagnosis::ANDROMEDA_STRAIN= "Andromeda Strain";


Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	Person(firstName, lastName, birthday),
	_alertLevel(AlertLevel::Green),
	_alertStrategy(nullptr)
{
}

Patient::~Patient()
{
	// Clean up vitals owned by this patient
	for (const Vitals* v : _vitals) {
		delete v;
	}
}

int Patient::age() const
{	
	// an inaccurate age estimate but fine for assignment purposes
	return 2022 - (1900 + _birthday.tm_year);
}

std::string Patient::uid() const
{
	std::stringstream ss;
	ss << (char)std::tolower(_lastName.at(0)) 
	   << (char)std::tolower(_firstName.at(0))
	   << std::setfill('0') << std::setw(2) << (_birthday.tm_mon + 1) 
	   << _birthday.tm_year;
	return ss.str();
}

std::string Patient::humanReadableID() const
{
	return "" + _lastName + ", " + _firstName + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	os << p.uid() << "|" << p._lastName << "," << p._firstName << "|" << std::put_time(&p._birthday, "%d-%m-%Y") << "|" << p.primaryDiagnosis();
	
	os << "|";
	for (int i = 0; i < p.vitals().size(); ++i) {
		auto v = p.vitals()[i];
		os << *v;
		if (i != p.vitals().size() - 1) {
			os << ";";
		}
	}
	return os;
}

void Patient::addDiagnosis(const std::string& diagnosis)
{
	_diagnosis.push_back(diagnosis);

	//The primary diagnosis (first added) decides which alert level strategy is used. 
	//Set the strategy once via the factory.
	if (_diagnosis.size() == 1) {
		_alertStrategy = AlertLevelStrategyFactory::createForDiagnosis(diagnosis);
	}
}

const std::string& Patient::primaryDiagnosis() const
{
	return _diagnosis.front();
}

void Patient::addVitals(const Vitals* v) {
	//Historical add - does not recalculate alert level.
	_vitals.push_back(v);
}

void Patient::recordVitals(const Vitals* v)
{
	_vitals.push_back(v);
	if (_alertStrategy != nullptr) {
		const AlertLevel newLevel = _alertStrategy->calculate(*this, *v);
		setAlertLevel(newLevel);
	}
}

const std::vector<const Vitals*> Patient::vitals() const
{
	return _vitals;
}

void Patient::setAlertLevel(AlertLevel level)
{
	_alertLevel = level;
	if (_alertLevel > AlertLevel::Green) {
		cout << "Patient: " << humanReadableID() << "has an alert level: ";
		switch (_alertLevel) {
		case AlertLevel::Yellow:
			cout << "Yellow";
			break;
		case AlertLevel::Orange:
			cout << "Orange";
			break;
		case AlertLevel::Red:
			cout << "Red";
			break;
		}
		cout << endl;
	}
}
