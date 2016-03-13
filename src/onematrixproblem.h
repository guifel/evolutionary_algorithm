#ifndef ONEMATRIXPROBLEM_H
#define ONEMATRIXPROBLEM_H

#include "eabaseproblem.h"
#include "eabinarystring.h"

class OneMatrixProblem : public EABaseProblem
{
public:
    OneMatrixProblem();
    virtual void fitFct(EARepresentation* gen);
    virtual void genotypeToPhenotype(EARepresentation* gen);

protected:

};

#endif // ONEMATRIXPROBLEM_H
