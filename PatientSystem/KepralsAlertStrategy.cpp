#include "KepralsAlertStrategy.h"

#include "Vitals.h"
#include "Patient.h"

AlertLevel KepralsAlertStrategy::calculate(const Patient& patient, const Vitals& vitals) const
{
	const int age = patient.age();
	const int hr = vitals.HR();

	if (age < 12 && hr > 120) {
		return AlertLevel::Red;
	}
	if (age >= 12 && hr > 100) {
		return AlertLevel::Red;
	}
	return AlertLevel::Green;
}
