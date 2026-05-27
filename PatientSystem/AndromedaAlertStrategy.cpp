#include "AndromedaAlertStrategy.h"

#include "Vitals.h"

AlertLevel AndromedaAlertStrategy::calculate(const Patient& patient, const Vitals& vitals) const
{
	const int bp = vitals.BP();
	if (bp > 140) {
		return AlertLevel::Red;
	}
	if (bp > 130) {
		return AlertLevel::Orange;
	}
	if (bp > 110) {
		return AlertLevel::Yellow;
	}
	return AlertLevel::Green;
}
