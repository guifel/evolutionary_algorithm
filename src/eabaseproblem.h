#ifndef EABASEPROBLEM_H
#define EABASEPROBLEM_H

#include <QWidget>
#include"earepresentation.h"


class EABaseProblem : public QWidget
{

public:
    EABaseProblem();
    virtual void fitFct(EARepresentation* gen) =0;
    virtual void genotypeToPhenotype(EARepresentation* gen) =0;

protected:

};

#endif // EABASEPROBLEM_H
