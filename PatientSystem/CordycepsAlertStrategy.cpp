#include "CordycepsAlertStrategy.h"

#include "Vitals.h"

AlertLevel CordycepsAlertStrategy::calculate(const Patient& patient, const Vitals& vitals) const
{
	const int rr = vitals.RR();
	if (rr > 40) {
		return AlertLevel::Red;
	} 
	if (rr > 30) {
		return AlertLevel::Orange;
	}
	if (rr > 20) {
		return AlertLevel::Yellow;
	}
	return AlertLevel::Green;
}