#pragma once

#include "AlertLevelStrategy.h"

class AndromedaAlertStrategy : public AlertLevelStrategy
{
public: 
	virtual AlertLevel calculate(const Patient& patient, const Vitals& vitals) const override;
};

