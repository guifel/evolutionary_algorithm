#ifndef EACHARSTRING_H
#define EACHARSTRING_H

#include "earepresentation.h"

#include <QString>
#include <qdebug.h>

class EACharString : public EARepresentation
{
public:
    EACharString(int lnt, int alpha);
    EACharString(EACharString const& cpy);

    virtual void mutation(double p);
    virtual void crossover(double p, int index1, int index2);
    virtual EARepresentation* newRepresentation();
    virtual void deletIndividuals(std::vector<int> list);
    virtual void addChildren(EARepresentation* fatherG, int fatherIndex);
    virtual QString getBestString();

    std::vector<int> getString(int index);
    void addGenotype(std::vector<int> add){genotype.push_back(add);}
    void addPhenotype(std::vector<int> add){phenotype.push_back(add);}
    int getPhenotypeSize() {return phenotype.size();}
    int getGenotypeSize() {return genotype.size();}
    void setFitList(std::list<int> fit) {fitList = fit;}
    int getLength(){return length;}
    int getAlphabet() {return alphabet;}

private:
    int length;
    int alphabet;
    std::list<std::vector<int> > genotype;
    std::list<std::vector<int> > phenotype;
};

#endif // EACHARSTRING_H
