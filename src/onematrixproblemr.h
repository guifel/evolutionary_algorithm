#ifndef ONEMATRIXPROBLEMR_H
#define ONEMATRIXPROBLEMR_H

#include "eabaseproblem.h"
#include "eabinarystring.h"

class OneMatrixProblemR : public EABaseProblem
{
public:
    OneMatrixProblemR();
    virtual void fitFct(EARepresentation* gen);
    virtual void genotypeToPhenotype(EARepresentation* gen);

private:
    QBitArray target;
};

#endif // ONEMATRIXPROBLEMR_H
