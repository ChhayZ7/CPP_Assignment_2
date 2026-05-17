#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Patient.h"
#include "Vitals.h"

using namespace std;

// Split a string by a single-character delimiter and return the tokens as a vector of strings
static std::vector<std::string> splitString(const std::string& source, char delimiter)
{
    vector<std::string> tokens;
    std::istringstream stream(source);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& file)
{
	vector<Patient*> patients{};

    std::ifstream inFile(file);
    if (!inFile.is_open()) {
        std::cout << "Could not open patient file: " << file << std::endl;
        return patients;
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue; // skip empty lines
		}

		// Each line: uid|lastName, firstName|birthday|diagnosis|BT,BP,HR,RR
		const std::vector<std::string> fields = splitString(line, '|');

		// Must have at least uid, name, birthday, diagnosis (vitals are optional)
        if (fields.size() < 4) {
            continue;
        }

        // Parse "lastName, firstName"
		const std::string& nameField = fields[1];
		const auto commaPos = nameField.find(',');
        if (commaPos == std::string::npos) {
            continue;
        }
		const std::string lastName = nameField.substr(0, commaPos);
		const std::string firstName = nameField.substr(commaPos + 1);

		// Parse birthday "dd-mm-yyy"
		std::tm birthday{};
		std::istringstream dateStream(fields[2]);
        dateStream >> std::get_time(&birthday, "%d-%m-%Y");
        
		// Create the patient and assign the diagnosis (which sets the alert 
        // level strategy via the factory)
		Patient* p = new Patient(firstName, lastName, birthday);
		p->addDiagnosis(fields[3]);

        // Parse vitals section if present.
		// Format: BT, BP, HR,RR; BT, BP, HR, RR; ...
        if (fields.size() >= 5 && !fields[4].empty()) {
			const std::vector<std::string> vitalStrings = splitString(fields[4], ';');
            for (const std::string& vitalStr : vitalStrings) {
                if (vitalStr.empty()) {
                    continue;
				}
				const std::vector<std::string> parts = splitString(vitalStr, ',');
                if (parts.size() != 4) {
                    continue;
                }
                try {
					const float bt = std::stof(parts[0]);
					const int bp = std::stoi(parts[1]);
					const int hr = std::stoi(parts[2]);
                    const int rr = std::stoi(parts[3]);
					Vitals* v = new Vitals(bt, bp, hr, rr);
                    p->addVitals(v);
                }
                catch (const std::exception&) {
                    // Skip malformed vitals row but keep the patient
                }
            }
        }
		patients.push_back(p);
    }

    return patients;
}
