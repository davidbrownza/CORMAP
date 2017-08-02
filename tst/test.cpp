#include "../src/model/Model.h"

using namespace std;

class Protein: public Model {

    public:
        Protein(): Model("Proteins") {}

        IntegerField * proteinID = integerField ("Protein_ID");
        CharField * proteinChain = charField ("Protein_Chain", 5);
        TextField * proteinName = textField ("Protein_Name");
        BooleanField * proteinIsDrugTarget = booleanField ("Protein_IsDrugTarget");
};

//main method
int main(int argc, const char* argv[] ) {
    Protein m;
    m.proteinID->setValue(1);
    //m.proteinChain->setValue("charactergreaterthan5"); //should throw an exception
    m.proteinChain->setValue("A");
    m.proteinName->setValue("Name");
    m.proteinIsDrugTarget->setValue(true);


    cout << m.tableName << endl;
    cout << m.proteinID->getValue() << " " << m.proteinID->getName() << endl;
    cout << m.proteinName->getValue() << " " << m.proteinName->getName() << endl;
    cout << m.proteinChain->getValue() << " " << m.proteinChain->getName() << " " << m.proteinChain->getMaxLength() << endl;
    cout << m.proteinIsDrugTarget->getValue() << " " << m.proteinIsDrugTarget->getName() << endl;
}
