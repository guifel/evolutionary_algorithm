#include "lolz.h"

Lolz::Lolz(int z)
{
    paramZ = z;
}

void Lolz::fitFct(EARepresentation *gen)
{
    EABinaryString* stringGen(dynamic_cast<EABinaryString*>(gen));

    int fitScore(0);
    std::list<int> fitList;
    QBitArray test(0);
    int i(0);

    for(int k(0); k < stringGen->getPhenotypeSize();k++)
    {


        test = stringGen->getString(k);

        i = 0;

        if(test.testBit(0) == 1)
        {

            while (test.testBit(i) == 1 and i < stringGen->getBitLenght())
            {
                i++;
                fitScore++;

            }
        }
        else
        {

            while (test.testBit(i) == 0 and (i < paramZ or i == stringGen->getBitLenght()))
            {
                i++;
                fitScore++;

            }
        }
        fitList.push_back(fitScore);
        fitScore = 0;

    }

     gen->setFitList(fitList);

}

void Lolz::genotypeToPhenotype(EARepresentation* gen)
{
    EABinaryString* stringGen(dynamic_cast<EABinaryString*>(gen));

    for(int i(0);i < stringGen->getGenotypeSize();i++)
    {
       stringGen->addPhenotype(stringGen->getString(i));
    }
}
