#ifndef EABINARYSTRING_H
#define EABINARYSTRING_H

#include "EARepresentation.h"
#include <list>
#include <stdlib.h>
#include <algorithm>
#include <vector>

#include <qdebug.h>
#include <QString>
#include <QBitArray>


class EABinaryString : public EARepresentation
{
public:

    EABinaryString(int length);
    EABinaryString(EABinaryString const& cpy);

    void addGenotype(QString str);
    void addPhenotype(QBitArray str){phenotype.push_back(str);}
    QBitArray getString(int index);
    int getBitLenght() {return bitLength;}
    int getPhenotypeSize() {return phenotype.size();}
    int getGenotypeSize() {return genotype.size();}
    void setFitList(std::list<int> fit) {fitList = fit;}

    virtual void mutation(double p);
    virtual void crossover(double p, int index1, int index2);
    virtual EARepresentation* newRepresentation();
    virtual void deletIndividuals(std::vector<int> list);
    virtual void addChildren(EARepresentation* fatherG, int fatherIndex);
    virtual QString getBestString();




private:

    int bitLength;
    std::list<QBitArray> genotype;
    std::list<QBitArray> phenotype;

};

#endif // EABINARYSTRING_H
