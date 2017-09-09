#ifndef FILEFIELD_H
#define FILEFIELD_H

#include "Field.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

class FileField: public Field {

    private:
        string _fieldValue;
        string _defaultValue;
        string _folderPath;

    public:
        FileField(string fieldName, string folderPath="", string defaultValue="", bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true, bool isAutoFilled=false);

        void setValue(string value);
        void saveNewFile(string pathToFile, string newFileName);

        string getValue();
        void getFile(string pathToFile);

        void setParameter(int parameterNumber, DBConnection connection);
        string generateColumnSQL();
};

#endif
