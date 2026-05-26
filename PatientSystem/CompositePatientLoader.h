#pragma once

#include <memory>
#include <vector>

#include "AbstractPatientDatabaseLoader.h"

// Composite loader (FR2)
// Holds a collection of AbstractPatientDatabaseloader children and delegates
// each operation to all of them in order. To clients, this looks identical to 
// a single loader, so the system can transparently load from a database, a file,
// or both, with a one-line change in PatientManagementSystem.
class CompositePatientLoader : public AbstractPatientDatabaseLoader
{
public:
	CompositePatientLoader() = default;
	virtual ~CompositePatientLoader() = default;

	// Add a child loader. The composite takes ownership
	void addLoader(std::unique_ptr<AbstractPatientDatabaseLoader> loader);

	// Inherited via AbstractPatientDatabaseLoader
	virtual void initialiseConnection() override;
	virtual void loadPatients(std::vector<Patient*>& patientIn) override;
	virtual void closeConnection() override;

protected:
	std::vector<std::unique_ptr<AbstractPatientDatabaseLoader>> _loaders;

};

