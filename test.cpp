#include "Model.h"

using namespace std;

class Protein: public Model
{
	public:
	    Protein(): Model("Proteins") {}
	    
	    IntegerField * proteinID = integerField ("Protein_ID");
        CharField * proteinChain = charField ("Protein_Chain"); // Added for charField test
	    TextField * proteinName = textField ("Protein_Name");
};

//main method	
int main(int argc, const char* argv[] )
{
    Protein m;
    m.proteinID->setValue(1);
    m.proteinChain->setValue('A');
    m.proteinName->setValue("Name");
    
    cout << m.tableName << endl;
    cout << m.proteinID->getValue() << " " << m.proteinID->getName() << endl;
    cout << m.proteinName->getValue() << " " << m.proteinName->getName() << endl;
    cout << m.proteinChain->getValue() << " " << m.proteinChain->getName() << endl;
}