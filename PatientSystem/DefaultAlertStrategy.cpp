#include "DefaultAlertStrategy.h"

AlertLevel DefaultAlertStrategy::calculate(const Patient& patient, const Vitals& vitals) const
{
	return AlertLevel::Green;
}