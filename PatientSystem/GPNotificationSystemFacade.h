#pragma once

#include "Patient.h"
#include "PatientAlertObserver.h"


class GPNotificationSystemFacade : public PatientAlertObserver {
public:
	GPNotificationSystemFacade();
	virtual ~GPNotificationSystemFacade();

	// Inherited via PatientAlertObserver
	virtual void onPatientAlertLevelChanged(const Patient& patient) override;
private: 
	void sendGPNotificationForPatient(const Patient& patient);
};


