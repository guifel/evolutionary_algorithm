#include "eabinarystring.h"



EABinaryString::EABinaryString(int length)
{
    bitLength = length;
}

EABinaryString::EABinaryString(const EABinaryString &cpy)
{
    this->bitLength = cpy.bitLength;

}

void EABinaryString::addGenotype(QString str)
{
    QBitArray toPush(bitLength);

    if(str.size() != bitLength)
    {
        qDebug()<<"SIZE GENE ERROR!";
    }
    else
    {

        for(int i = 0; i < bitLength; i++)
        {

            if(str.at(i) == QChar('1'))
                toPush.setBit(i,true);
            else if(str.at(i) == QChar('0'))
                toPush.setBit(i,false);
            else
                qDebug() << "ERROR CHARACTER";

        }
        genotype.push_back(toPush);

    }

}



void EABinaryString::mutation(double p)
{
    int mutBit;
    double randn;

    for(std::list<QBitArray>::iterator it = genotype.begin(); it!=genotype.end(); ++it)
        {
            randn = ((double)rand())/RAND_MAX;

            if( randn < p) //Mutation !
            {
                mutBit = rand()%(bitLength);


                //flip a bit
                if((*it).testBit(mutBit))
                    (*it).setBit(mutBit, false);
                else
                   (*it).setBit(mutBit, true);
            }
        }
}

void EABinaryString::crossover(double p, int index1, int index2)
{
    if(rand()/RAND_MAX < p)
    {

    QBitArray guy1;
    QBitArray guy2;

    guy1.resize(bitLength);
    guy2.resize(bitLength);



    int cutPoint(rand()%bitLength);

    std::list<QBitArray>::iterator it1 = genotype.begin();
    std::advance(it1,index1);
    guy1 = *it1;

    std::list<QBitArray>::iterator it2 = genotype.begin();
    std::advance(it2,index2);
    guy2 = *it2;

    for(int i(0);i < cutPoint; i++)
        (*it1).setBit(i,guy2.at(i));

    for(int i(0);i < cutPoint; i++)
        (*it2).setBit(i,guy1.at(i));


    }



}

EARepresentation* EABinaryString::newRepresentation()
{
    EARepresentation* copy = new EABinaryString(*this);
    return copy;

}
void EABinaryString::deletIndividuals(std::vector<int> list)
{
    std::sort(list.begin(),list.end());

    std::list<QBitArray>::iterator itg;
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

void EABinaryString::addChildren(EARepresentation* fatherG, int fatherIndex)
{
    EABinaryString* fatherCasted;
    fatherCasted = dynamic_cast<EABinaryString*>(fatherG);
    genotype.push_back(fatherCasted->getString(fatherIndex));
}

QBitArray EABinaryString::getString(int index)
{
    std::list<QBitArray>::iterator it = genotype.begin();
    std::advance(it,index);
    return (*it);
}

QString EABinaryString::getBestString()
{
    int i(0);
    std::list<int>::iterator mit = std::max_element(fitList.begin(),fitList.end());
    std::list<int>::iterator itt = fitList.begin();
    while(itt != mit) {itt++;i++;}

    QBitArray toReturn(this->getString(i));
    QString ret;
    for(int i(0);i<toReturn.size();i++) ret.append(QString::number(toReturn.testBit(i)));
    return ret;
}


