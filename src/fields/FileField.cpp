#include "FileField.h"

using namespace std;

FileField::FileField(string fieldName, string folderPath, string defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable, bool isAutoFilled):
    Field(fieldName, FILEFIELD, isPrimaryKey, isUnique, isNullable, isAutoFilled), _fieldValue(defaultValue), _defaultValue(defaultValue), _folderPath(folderPath) {}

//Not sure if we should change this to setName or setFileName instead?
void FileField::setValue(string value) {

    //Note, in Djago they limit the file name length to 100 characters
    setNull(false);

    string pathToFile = _folderPath + "/" + _fieldValue;
    string pathToNewFile = _folderPath + "/" + value;
    rename(pathToFile.c_str(), pathToNewFile.c_str());

    _fieldValue = value;
}

//Will save a copy of user-specified file to _folderPath directory
//  File name will be stored in the database
void FileField::saveNewFile(string pathToFile, string newFileName) {

    ifstream inFile(pathToFile, ios::binary);

    string newFilePath = _folderPath + "/" + newFileName;
    ofstream newFile(newFilePath, ios::binary);
    newFile << inFile.rdbuf();

    _fieldValue = newFileName;
}

//Again, couldn't work out how to return a stream, so this just copies the
//  saved file to wherever the user specifies
void FileField::getFile(string pathToNewFile) {

    string pathToOldFile = _folderPath + "/" + _fieldValue;
    ifstream inFile(pathToOldFile, ios::binary);

    ofstream newFile(pathToNewFile, ios::binary);
    newFile << inFile.rdbuf();
}

string FileField::getValue() {
    return _fieldValue;
}

void FileField::setParameter(int parameterNumber, DBConnection connection) {
    connection.setString(parameterNumber, getValue());
}

//Have set maxlenth to 100 for now
string FileField::generateColumnSQL() {
    string fieldType = " VARCHAR(100)";

    string defaultValue = "";
    if (isAutoFilled() == true) {
         defaultValue = " DEFAULT '" + _defaultValue + "'";
    }

    return getName() + fieldType + defaultValue;
}
