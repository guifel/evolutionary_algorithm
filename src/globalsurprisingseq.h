#ifndef GLOBALSURPRISINGSEQ_H
#define GLOBALSURPRISINGSEQ_H

#include "eabaseproblem.h"
#include "eacharstring.h"

class GlobalSurprisingSeq : public EABaseProblem
{
    Q_OBJECT
public:
    GlobalSurprisingSeq(int len, int alpha);

    virtual void fitFct(EARepresentation* gen);
    virtual void genotypeToPhenotype(EARepresentation* gen);

signals:

    void resultFound(QString);

private:
    int length;
    int alphabet;
    bool firstOfGen;
};

#endif // GLOBALSURPRISINGSEQ_H
