#pragma once

#include "AlertStrategy.h"

// Concrete strategy for Cordyceps Brain Infection
// Alert level is determined by respiratory rate (RR):
// RR > 40 -> Red
// RR > 30 -> Orange
// RR > 20 -> Yellow
// else -> Green
class CordycepsAlertStrategy
{
public: 
	virtual AlertLevel calculate(const Patient& patient, const Vitals& vitals) const override;
};

