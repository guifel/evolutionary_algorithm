#include "localsurprisingseq.h"
#include "eacharstring.h"

LocalSurprisingSeq::LocalSurprisingSeq(int len, int alpha)
{
    length = len;
    alphabet = alpha;

}

void LocalSurprisingSeq::fitFct(EARepresentation *gen)
{
    EACharString* stringGen(dynamic_cast<EACharString*>(gen));
    int fitScore(0);
    std::list<int> fitList;
    std::vector<int> test;
    std::vector<std::pair<int,int> >symbols;

    firstOfGen = true;

    for(int k(0); k < stringGen->getPhenotypeSize();k++)
    {
        test = stringGen->getString(k);
        for(int i = 1; i < stringGen->getLength(); i++)
        {
           symbols.push_back(std::make_pair(test[i-1],test[i]));
        }


        int beforSize(symbols.size());
        std::sort(symbols.begin(),symbols.end());
        symbols.erase(std::unique(symbols.begin(),symbols.end()),symbols.end());

        if(beforSize == symbols.size())
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

        fitList.push_back(symbols.size()+1);
        symbols.clear();

    }

    gen->setFitList(fitList);
}

void LocalSurprisingSeq::genotypeToPhenotype(EARepresentation *gen)
{
    EACharString* stringGen(dynamic_cast<EACharString*>(gen));


    for(int i(0);i < stringGen->getGenotypeSize();i++)
    {
       stringGen->addPhenotype(stringGen->getString(i));
    }


}
