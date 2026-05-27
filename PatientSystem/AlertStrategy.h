#pragma once

#include "PatientAlertLevels.h"

// forward declare classes
class Patient;
class  Vitals;

// Strategy interface (FR3)
// Each disease has its own algorithms for calculating an AlertLevel from a patient's vitals
class AlertStrategy {
public:
	virtual ~AlertStrategy() = default;

	// Calculate the alert level for a patient given a new vitals reading
	virtual AlertLevel calculate(const Patient& patient, const Vitals& vitals) const = 0;
};
