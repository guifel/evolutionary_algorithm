#include "globalsurprisingseq.h"

GlobalSurprisingSeq::GlobalSurprisingSeq(int len, int alpha)
{
    length = len;
    alphabet = alpha;
}

void GlobalSurprisingSeq::fitFct(EARepresentation *gen)
{
    EACharString* stringGen(dynamic_cast<EACharString*>(gen));
    std::list<int> fitList;
    std::vector<int> test;

    std::vector<std::vector<int> >symbolsList;
    std::vector<int> symbol;

    firstOfGen = true;

    for(int k(0); k < stringGen->getPhenotypeSize();k++)
    {
        test = stringGen->getString(k);
        for(int i = 0; i < stringGen->getLength(); i++)
        {
           for(int j(i+1); j < stringGen->getLength(); j++)
           {
                       symbol.push_back(test[j]);
                       symbol.push_back(test[i]);
                       symbol.push_back(i-j-1);

//

                   symbolsList.push_back(symbol);
                   symbol.clear();
            }
        }

        // Save the size to check if it's surprising
        int beforSize(symbolsList.size());

        // Eliminate duplicates
        std::sort(symbolsList.begin(),symbolsList.end());
        symbolsList.erase(std::unique(symbolsList.begin(),symbolsList.end()),symbolsList.end());



        // Push fit value
        fitList.push_back(symbolsList.size());

        //Surprising test
        if(beforSize == symbolsList.size())
        {

            QString ret;
            ret.clear();
            for(int j(0); j < length ;j++)
                ret += (QString::number(test[j]) + ", ");

            if(firstOfGen == true)
            {
                firstOfGen = false;
                emit resultFound(ret);
            }
        }


        symbolsList.clear();

    }
    gen->setFitList(fitList);
}

void GlobalSurprisingSeq::genotypeToPhenotype(EARepresentation *gen)
{
    EACharString* stringGen(dynamic_cast<EACharString*>(gen));


    for(int i(0);i < stringGen->getGenotypeSize();i++)
    {
       stringGen->addPhenotype(stringGen->getString(i));
    }

}
