#pragma once
#include "Person.h"

#include <memory>
#include <vector>

#include "PatientAlertLevels.h"


// forward declare classes
class AlertLevelStrategy;
class Vitals;
class PatientAlertObserver;

class Diagnosis {
public:
	static const std::string CORDYCEPS_BRAIN_INFECTION;
	static const std::string KEPRALS_SYNDROME;
	static const std::string ANDROMEDA_STRAIN;
};

class Patient : public Person {
public:

	Patient(const std::string& firstName, const std::string& lastName, std::tm birthday);
	virtual ~Patient();

	// return a calculated age for the patient
	// this calculation is not accurate, but is suitable for assignment purposes
	int age() const;

	// return a "unique" ID generated for the patient
	// this id is generated purely from patient details, and as such may have collisions
	std::string uid() const;
	
	// returns a "nice" ID for humans to interpret: lastname, firstname (UID)
	std::string humanReadableID() const;

	// patients have diagnoses of a disease
	// Note: the initial design consider multiple diagnoses added using addDiagnosis.
	// This was refactored to only consider the primary (i.e. the first) diagnosis.
	void addDiagnosis(const std::string& diagnosis);
	const std::string& primaryDiagnosis() const;

	//Add a historical vitals measurement for the patient
	//Used by laoders for historical data: this does NOT recalculate
	// the alert level
	void addVitals(const Vitals* v);

	//Record a new vitals measurement for the patient
	//This recalculates the alert level using the strategy and
	//notifies observers if the alert level changes
	void recordVitals(const Vitals* v);

	const std::vector<const Vitals*> vitals() const;

	// patients have an alert level (green, yellow, orange, red) calculated from their disease and and their last vitals
	void setAlertLevel(AlertLevel level);
	AlertLevel alertLevel() const { return _alertLevel; }

	//Observer registration. The patient does NOT own its observers
	//The caller is responsible for their lifetime
	void attachObserver(PatientAlertObserver* observer);

protected:
	std::vector<std::string> _diagnosis;
	std::vector<const Vitals*> _vitals;
	AlertLevel _alertLevel;

	//Strategy for calculating alert levels
	std::unique_ptr<AlertLevelStrategy> _alertStrategy;

	std::vector<PatientAlertObserver*> _observers;

	//Notify all attached observers of an alert level change
	void notifyObservers() const;

	friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

