#pragma once

#include "AlertLevelStrategy.h"

class DefaultAlertStrategy : public AlertLevelStrategy
{
public:
	virtual AlertLevel calculate(const Patient& patient, const Vitals& vitals) const override;
};

