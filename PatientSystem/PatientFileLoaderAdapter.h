#pragma once

#include "AbstractPatientDatabaseLoader.h"
#include "PatientFileLoader.h"

// Adapter (FR1).
// PatientFileLoader has an incompatible interface (loadPatientFile returns
// a vector by value). This adapter wraps it and exposes the same interface
// as AbstractPatientDatabaseLoader, so it can be used wherever the system
// expects a database loader.
class PatientFileLoaderAdapter : public AbstractPatientDatabaseLoader {
public:
	PatientFileLoaderAdapter(const std::string& filePath);
	virtual ~PatientFileLoaderAdapter() = default;

	// Inherited via AbstractPatientDatabaseLoader
	virtual void initialiseConnection() override;
	virtual void loadPatients(std::vector<Patient*>& patientIn) override;
	virtual void closeConnection() override;

protected:
	PatientFileLoader _fileLoader;
	std::string _filePath;
};
