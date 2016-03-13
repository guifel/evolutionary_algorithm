#ifndef LOCALSURPRISINGSEQ_H
#define LOCALSURPRISINGSEQ_H

#include "eabaseproblem.h"

class LocalSurprisingSeq : public EABaseProblem
{
    Q_OBJECT
public:
    LocalSurprisingSeq(int len, int alpha);

    virtual void fitFct(EARepresentation* gen);
    virtual void genotypeToPhenotype(EARepresentation* gen);

signals:

    void resultFound(QString);

private:
    int length;
    int alphabet;
    bool firstOfGen;
};

#endif // LOCALSURPRISINGSEQ_H
