#ifndef SAES_HEADER_H
#define SAES_HEADER_H

#include <string>
#include <map>


#define DEFAULT_COMPANYNAME "SAES"
#define DEFAULT_PROJECT "__CAMBIA_PROJECT__"
#define DEFAULT_CSCI_NAME "__CAMBIA_CSCI_NAME__"
#define DEFAULT_CSCI_NUMBER "__CAMBIA_CSCI_NUMBER__"
#define DEFAULT_CSC_SU_NAME "__CAMBIA_CSC_SU_NAME_"
#define DEFAULT_CSC_SU_NUMBER "__CAMBIA_CSC_SU_NUMBER__"
#define DEFAULT_UNIT_NAME "__CAMBIA_UNIT_NAME__"
#define DEFAULT_UNIT_NUMBER "__CAMBIA_UNIT_NUMBER__"
#define DEFAULT_REPOSITORY "__CAMBIA_REPOSITORY__"
#define DEFAULT_DESIGN_CONSIDERATION "__CAMBIA_DESIGN_CONSIDERATION__"
#define DEFAULT_CONSTRAINTS "__CAMBIA_CONSTRAINTS__"
#define DEFAULT_DETAILED_DESIGN_REF "__CAMBIA_DETAILED_DESIGN_REF_"
#define DEFAULT_FULLFILLED_REQUIREMENTS "__CAMBIA_FULLFILLED_REQUIREMENTS__"
#define DEFAULT_UNIT_TEST_INFORMARTION "__CAMBIA_UNIT_TEST_INFORMARTION__"
#define DEFAULT_CSC_TEST_INFORMATION "__CAMBIA_CSC_TEST_INFORMATION_"
#define DEFAULT_CSCI_QUALIFICATION_TEST_INFORMATION "__CAMBIA_CSCI_QUALIFICATION_TEST_INFORMATION__"
#define DEFAULT_DATA_CREATED "__CAMBIA_DATA_CREATED__"
#define DEFAULT_AUTHOR "__CAMBIA_AUTHOR__"
#define DEFAULT_DESCRIPTION "__CAMBIA_DESCRIPITION__"
#define DEFAULT_REVISION_HISTORY "__CAMBIA_REVISION_HISTORY__"
#define DEFAULT_DATE "01/01/2000"
#define DEFAULT_CP "__CAMBIA_CP__"

using namespace std;


enum HeaderElement {
    COMPANY_NAME, PROJECT, CSCI_NAME, CSCI_NUMBER, CSC_SU_NAME, 
    CSC_SU_NUMBER, UNIT_NAME, UNIT_NUMBER, REPOSITORY, DESIGN_CONSIDERATIONS, 
    CONSTRAINTS, DETAILED_DESIGN_REF, FULFILLED_REQUIREMENTS, UNIT_TEST_INFORMATION, 
    CSC_TEST_INFORMATION, CSCI_QUALIFICATION_TEST_INFORMATION, DATA_CREATED, 
    AUTHOR, DESCRIPTION, FILE_NAME, REVISION_HISTORY, DATE, CP, NOELEMENTS
};

static std::map<HeaderElement, std::string> HeaderElementXMLMap = {
    {COMPANY_NAME, "companyName"},
    {PROJECT, "project"},
    {CSCI_NAME, "csciName"},
    {CSCI_NUMBER, "csciNumber"},
    {CSC_SU_NAME, "cscSuName"},
    {CSC_SU_NUMBER, "cscSuNumber"},
    {UNIT_NAME, "unitName"},
    {UNIT_NUMBER, "unitNumber"},
    {REPOSITORY, "repository"},
    {DESIGN_CONSIDERATIONS, "designConsiderations"},
    {CONSTRAINTS, "constraints"},
    {DETAILED_DESIGN_REF, "detailedDesignRef"},
    {FULFILLED_REQUIREMENTS, "fulfilledRequirements"},
    {UNIT_TEST_INFORMATION, "unitTestInformation"},
    {CSC_TEST_INFORMATION, "cscTestInformation"},
    {CSCI_QUALIFICATION_TEST_INFORMATION, "csciQualificationTestInformation"},
    {DATA_CREATED, "dataCreated"},
    {AUTHOR, "author"},
    {DESCRIPTION, "description"},
    {FILE_NAME, "fileName"},
    {REVISION_HISTORY, "revisionHistory"},
    {DATE, "date"},
    {CP, "cp"}
};

static std::map<HeaderElement, std::string> HeaderElementNameMap = {
    {COMPANY_NAME, "Company Name"},
    {PROJECT, "Project"},
    {CSCI_NAME, "CSCI Name"},
    {CSCI_NUMBER, "CSCI Number"},
    {CSC_SU_NAME, "CSC (SU) Name"},
    {CSC_SU_NUMBER, "CSC (SU) Number"},
    {UNIT_NAME, "Unit Name"},
    {UNIT_NUMBER, "Unit Number"},
    {REPOSITORY, "Repository"},
    {DESIGN_CONSIDERATIONS, "Design Considerations"},
    {CONSTRAINTS, "Constraints"},
    {DETAILED_DESIGN_REF, "Detailed Design Ref"},
    {FULFILLED_REQUIREMENTS, "Fullfilled Requirements"},
    {UNIT_TEST_INFORMATION, "Unit Tests Information"},
    {CSC_TEST_INFORMATION, "CSC Tests Information"},
    {CSCI_QUALIFICATION_TEST_INFORMATION, "CSCI Qualification Test Information"},
    {DATA_CREATED, "Data Created"},
    {AUTHOR, "Author"},
    {DESCRIPTION, "Description"},
    {FILE_NAME, "File Name"},
    {REVISION_HISTORY, "Revision History"},
    {DATE, "Date"},
    {CP, "CP (Change Proposal Reference)"}
};

/**
 * @class SaesHeader
 * @brief Clase que representa la cabecera de un archivo en un proyecto de SAES.
*/
class SaesHeader {
private:
    string elements[NOELEMENTS];
    string fillWithPoints(string str);

public:
    SaesHeader() {};
    SaesHeader(string _fileName);
    ~SaesHeader() {};

    string getHeaderElement(HeaderElement element);
    void setHeaderElement(HeaderElement element, const string &value);

    string toString();
    
    
};

#endif // SAES_HEADER_H

    
// Company Name..............................SAES
// Project...................................__CAMBIA_PROJECT__
// CSCI Name.................................__CAMBIA_CSCI_NAME__
// CSCI Number...............................__CAMBIA_CSCI_NUMBER__
// CSC (SU) Name.............................__CAMBIA_CSC_SU_NAME_
// CSC (SU) Number...........................__CAMBIA_CSC_SU_NUMBER__
// Unit Name.................................__CAMBIA_UNIT_NAME__
// Unit Number...............................__CAMBIA_UNIT_NUMBER__
// Repository................................__CAMBIA_REPOSITORY__
// Design Considerations.....................__CAMBIA_DESIGN_CONSIDERATION__
// Constraints...............................__CAMBIA_CONSTRAINTS__
// Detailed Design Ref.......................__CAMBIA_DETAILED_DESIGN_REF_
// Fullfilled Requirements...................__CAMBIA_FULLFILLED_REQUIREMENTS__
// Unit Tests Information....................__CAMBIA_UNIT_TEST_INFORMARTION__
// CSC Tests Information.....................__CAMBIA_CSC_TEST_INFORMATION_
// CSCI Qualification Test Information.......__CAMBIA_CSCI_QUALIFICATION_TEST_INFORMATION__
// Data Created..............................__CAMBIA_DATA_CREATED__
// Author....................................__CAMBIA_AUTHOR__
// Description...............................__CAMBIA_DESCRIPITION__

// File Name.................................__CAMBIA_FILE_NAME__
// Revision History..........................__CAMBIA_REVISION_HISTORY__
// Date......................................__CAMBIA_DATE__
// CP (Change Proposal Reference)............__CAMBIA_CP__
