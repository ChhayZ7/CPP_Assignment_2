#include "PatientFileLoaderAdapter.h"
#include "Patient.h"

PatientFileLoaderAdapter::PatientFileLoaderAdapter(const std::string& filePath):
	_fileLoader(),
	_filePath(filePath)
{
}

void PatientFileLoaderAdapter::initialiseConnection() {
	// File-based loader doesn't have a connection to initialise, so this is a no-op.
}

void PatientFileLoaderAdapter::loadPatients(std::vector<Patient*>& patientIn) {

	// Adapt the incompatible interface: call the file loader's method and 
	// transfer its results into the caller-supplied vector.
	const std::vector<Patient*> loadedPatients = _fileLoader.loadPatientFile(_filePath);
	for (Patient* p : loadedPatients) {
		patientIn.push_back(p);
	}
}

void PatientFileLoaderAdapter::closeConnection() {
	// File-based loader doesn't have a connection to close, so this is a no-op.
}