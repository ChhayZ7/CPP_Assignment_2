#include "CompositePatientLoader.h"

void CompositePatientLoader::addLoader(std::unique_ptr<AbstractPatientDatabaseLoader> loader) {
	_loaders.push_back(std::move(loader));
}

void CompositePatientLoader::initialiseConnection() {
	for (auto& loader : _loaders) {
		loader->initialiseConnection();
	}
}

void CompositePatientLoader::loadPatients(std::vector<Patient*>& patientIn) {
	//Delegate to each child loader in order
	//They all append to the same vector, giving the caller a merged paitent list
	for (auto& loader : _loaders) {
		loader->loadPatients(patientIn);
	}
}

void CompositePatientLoader::closeConnection() {
	for (auto& loader: _loaders){
		loader->closeConnection();
	}
}
