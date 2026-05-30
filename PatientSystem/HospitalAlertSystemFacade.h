#pragma once

#include "Patient.h"
#include "PatientAlertObserver.h"

//Hospital alert system facade. Wraps the (mocked) hospital alert backend
//behind a simple interface. Also acts as a PatientAlertObserver so it can be
//attached to a Patient and notified whenever the alert level changes (FR4).
class HospitalAlertSystemFacade: public PatientAlertObserver
{
public:
	HospitalAlertSystemFacade();
	virtual ~HospitalAlertSystemFacade();

	void sendAlertForPatient(const Patient& patient);

	// Inherited via PatientAlertObserver
	virtual void onPatientAlertLevelChanged(const Patient& patient) override;

};

