#ifndef EAREPRESENTATION_H
#define EAREPRESENTATION_H

#include <list>
#include <vector>
#include <qstring.h>



class EARepresentation
{
public:
    EARepresentation();

    virtual void mutation(double p) =0;
    virtual void crossover(double p, int index1, int index2)=0;
    virtual EARepresentation* newRepresentation() =0;
    virtual void deletIndividuals(std::vector<int> list) =0;
    virtual void addChildren(EARepresentation* fatherG, int fatherIndex) =0;
    virtual QString getBestString() =0;

    std::list<int> getFitList() {return fitList;}
    void setFitList(std::list<int> fit){fitList = fit;}

    void clearList() {fitList.clear();}

protected:
    std::list<int> fitList;
};

#endif // EAREPRESENTATION_H
