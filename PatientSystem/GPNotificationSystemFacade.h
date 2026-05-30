#pragma once

#include "Patient.h"
#include "PatientAlertObserver.h"


class GPNotificationSystemFacade : public PatientAlertObserver {
public:
	GPNotificationSystemFacade();
	virtual ~GPNotificationSystemFacade();

	void sendGPNotificationForPatient(const Patient& patient);

	// Inherited via PatientAlertObserver
	virtual void onPatientAlertLevelChanged(const Patient& patient) override;
};

