#ifndef EA_H
#define EA_H
#include <QWidget>
#include "earepresentation.h"
#include "eabaseproblem.h"

#include<vector>
#include <stdlib.h>
#include <math.h>
#include<qdebug.h>

#define RANK_PARAMETER 0.5


class EA : public QWidget
{
   Q_OBJECT
public:
    EA(EARepresentation* representation, EABaseProblem* pb);

    void evolv();

    enum SelectionStrategy
    {
        FitnessProportional,SigmaScaling,RankSelection,Tournament
    };

public slots:

    void setMut(double rate);
    void setCrossover(double rate);
    void setPoolSize(int n);
    void setGenerationNumber(int n);
    void setOverProduction(int n) {overProduction = n;}
    void setMixing(bool set) {mixing = set;}
    void setAdultSelStrat(SelectionStrategy strat){adultSel = strat;}
    void setChildSelStrat(SelectionStrategy strat) {childSel = strat;}
    void setAbort() {abort = true;}
    void setTournament(int sizeA, double pA, int sizeC, double pC) {tournamentSizeA = sizeA; tournamentpA = pA; tournamentSizeC = sizeC; tournamentpC = pC;}
    void setRankSP(double sp) {rankSP = sp;}

signals:

    void logReport(const int, std::list<int> ,const int, const QString);

private :
    double mutRate;
    double crossoverRate;
    int poolSize;
    int generationNumber;
    int overProduction;
    bool mixing;
    bool abort;
    int tournamentSizeA;
    double tournamentpA;
    int tournamentSizeC;
    double tournamentpC;
    int tournamentSize;
    double tournamentp;
    SelectionStrategy adultSel;
    SelectionStrategy childSel;
    double rankSP;


    EABaseProblem* problem;
    EARepresentation* initialGeneration;
    EARepresentation* curentGeneration;
    EARepresentation* newGeneration;

    void adultSelection();
    void parentsSelection();
    int fitnessProportional(std::list<int> fitList);
    int sigmaScaling(std::list<int> fitList);
    int rankSelection(std::list<int> fitList);
    int tournament(std::list<int> fitList);
};

#endif // EA_H
