#pragma once
#include "AlertLevelStrategy.h"

//Concrete strategy for Kepral's Syndrome
//Alert level depends on patient age and heart rate (HR):
// age < 12 and HR > 120 -> Red
// age >= 12 and HR > 100 -> Red
// else -> Green
class KepralsAlertStrategy: public AlertLevelStrategy	
{
public:
	virtual AlertLevel calculate(const Patient& patient, const Vitals& vitals) const override;
};

