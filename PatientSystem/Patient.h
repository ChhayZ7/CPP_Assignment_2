#pragma once
#include "Person.h"

#include <memory>
#include <vector>

#include "PatientAlertLevels.h"


// forward declare classes
class AlertLevelStrategy;
class Vitals;

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
	const AlertLevel alertLevel() const { return _alertLevel; }

protected:
	std::vector<std::string> _diagnosis;
	std::vector<const Vitals*> _vitals;
	AlertLevel _alertLevel;

	//Strategy for calculating alert levels (FR3)
	std::unique_ptr<AlertLevelStrategy> _alertStrategy;

	friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

