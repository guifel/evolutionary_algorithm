#include "onematrixproblem.h"

OneMatrixProblem::OneMatrixProblem()
{


}

void OneMatrixProblem::fitFct(EARepresentation *gen)
{

    EABinaryString* stringGen(dynamic_cast<EABinaryString*>(gen));

    int fitScore(0);
    std::list<int> fitList;
    QBitArray test(0);

    for(int k(0); k < stringGen->getPhenotypeSize();k++)
    {

        test = stringGen->getString(k);
        for(int i = 0; i < stringGen->getBitLenght(); i++)
        {
            if(test.testBit(i))
            {
                fitScore++;

            }

        }
        fitList.push_back(fitScore);
        fitScore = 0;
    }

    gen->setFitList(fitList);
}

void OneMatrixProblem::genotypeToPhenotype(EARepresentation* gen)
{
    EABinaryString* stringGen(dynamic_cast<EABinaryString*>(gen));

    for(int i(0);i < stringGen->getGenotypeSize();i++)
    {
       stringGen->addPhenotype(stringGen->getString(i));
    }
}
