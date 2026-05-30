#pragma once

//forward declare the Patient class
class Patient;

//Observer interface for the Observer pattern.
//Concreate observer (HosptialAlertSystemFacade, GPNotificationSystemFacade)
//implement onPatientAlertLevelChanged() and are notified whena patient's
//alert level changes.
class PatientAlertObserver {
public:
	virtual ~PatientAlertObserver() = default;

	//Called by the Patient (subject) whenever its alert level changes.
	virtual void onPatientAlertLevelChanged(const Patient& patient) = 0;
};
