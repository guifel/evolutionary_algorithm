#include "eacharstring.h"

EACharString::EACharString(int lnt, int alpha)
{

    length = lnt;
    alphabet = alpha;
}

EACharString::EACharString(const EACharString &cpy)
{
    this->length = cpy.length;
    this->alphabet = cpy.alphabet;
}

void EACharString::mutation(double p)
{
    int mutChar;
    double randn;

    for(std::list<std::vector<int> >::iterator it = genotype.begin(); it!=genotype.end(); ++it)
        {
            randn = ((double)rand())/RAND_MAX;

            if( randn < p) //Mutation !
            {
                mutChar = rand()%(length);

                (*it)[mutChar] = rand()%alphabet;

            }
        }
}

void EACharString::crossover(double p, int index1, int index2)
{
    if(rand()/RAND_MAX < p)
    {

    std::vector<int> guy1;
    std::vector<int> guy2;



    int cutPoint(rand()%length);

    std::list<std::vector<int> >::iterator it1 = genotype.begin();
    std::advance(it1,index1);
    guy1 = *it1;

    std::list<std::vector<int> >::iterator it2 = genotype.begin();
    std::advance(it2,index2);
    guy2 = *it2;

    for(int i(0);i < cutPoint; i++)
        (*it1)[i] = guy2[i];

    for(int i(0);i < cutPoint; i++)
        (*it2)[i] = guy1[i];


    }

}

EARepresentation* EACharString::newRepresentation()
{
    EARepresentation* copy = new EACharString(*this);

    if(!copy) qDebug() << "MEMORY FAIL !!!!!!!!";

    return copy;
}

void EACharString::deletIndividuals(std::vector<int> list)
{
    std::sort(list.begin(),list.end());

    std::list<std::vector<int> >::iterator itg;
    std::list<int>::iterator itf;

    for(int i =0;i<list.size();i++)
    {
        itg = genotype.begin();
        itf = fitList.begin();

        std::advance(itg,list[i] - i);
        genotype.erase(itg);

        std::advance(itf,list[i] - i);
        fitList.erase(itf);
    }
}

void EACharString::addChildren(EARepresentation *fatherG, int fatherIndex)
{
    EACharString* fatherCasted;
    fatherCasted = dynamic_cast<EACharString*>(fatherG);
    genotype.push_back(fatherCasted->getString(fatherIndex));
}

std::vector<int> EACharString::getString(int index)
{
    std::list<std::vector<int> >::iterator it = genotype.begin();
    std::advance(it,index);
    return (*it);
}


QString EACharString::getBestString()
{
    int i(0);
    std::list<int>::iterator mit = std::max_element(fitList.begin(),fitList.end());
    std::list<int>::iterator itt = fitList.begin();
    while(itt != mit) {itt++;i++;}

    std::list<std::vector<int> >::iterator myit = phenotype.begin();
    std::advance(myit,i);

    QString ret;
    ret.clear();
    for(int j(0); j < length ;j++)
        ret += (QString::number((*myit)[j]) + ", ");


    return ret;
}
