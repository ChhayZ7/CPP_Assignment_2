#include "AlertLevelStrategyFactory.h"

#include "AndromedaAlertStrategy.h"
#include "CordycepsAlertStrategy.h"
#include "DefaultAlertStrategy.h"
#include "KepralsAlertStrategy.h"
#include "Patient.h"

std::unique_ptr<AlertLevelStrategy> AlertLevelStrategyFactory::createForDiagnosis(const std::string& diagnosis) {

	if (diagnosis == Diagnosis::ANDROMEDA_STRAIN) {
		return std::make_unique<AndromedaAlertStrategy>();
	}
	if (diagnosis == Diagnosis::CORDYCEPS_BRAIN_INFECTION) {
		return std::make_unique<CordycepsAlertStrategy>();
	}
	if (diagnosis == Diagnosis::KEPRALS_SYNDROME) {
		return std::make_unique<KepralsAlertStrategy>();
	}
	return std::make_unique<DefaultAlertStrategy>();
}
