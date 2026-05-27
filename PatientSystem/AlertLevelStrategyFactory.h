#pragma once

#include <memory>
#include <string>

#include "AlertLevelStrategy.h"

//Factory for creating the right AlertLevelStrategy for a given diagnosis.
//This keeps Patient decoupled from the concrete strategy classes.
class AlertLevelStrategyFactory
{
public:
	//Returns a new strategy instance appropriate for the given diagnosis.
	//Unrecognised diagnoses will return a default strategy that always returns Green.
	static std::unique_ptr<AlertLevelStrategy> createForDiagnosis(const std::string& diagnosis);
};

