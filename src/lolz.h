#ifndef LOLZ_H
#define LOLZ_H

#include "eabaseproblem.h"
#include "eabinarystring.h"

class Lolz : public EABaseProblem
{
public:
    Lolz(int z);
    virtual void fitFct(EARepresentation* gen);
    virtual void genotypeToPhenotype(EARepresentation* gen);

private:
    int paramZ;
};

#endif // LOLZ_H
