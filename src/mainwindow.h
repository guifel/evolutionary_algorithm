#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>

#include "ea.h"


#include "eabinarystring.h"
#include "eacharstring.h"

#include "onematrixproblem.h"
#include "onematrixproblemr.h"
#include "lolz.h"
#include "localsurprisingseq.h"
#include "globalsurprisingseq.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum ProblemType
    {
       OneMatrix,OneMatrixR,LOLZ,SurpriseSeq,SurpriseSeq2
    };

private:
    Ui::MainWindow *ui;

    EABaseProblem* myProblem;
    EARepresentation* myRepresentation;
    EA* myEA;

    int bestFit;
    int genBest;

public slots:

    void goButton();
    void graphPrint(const int, std::list<int> ,const int, const QString);
    void resultPrint(QString);


};

#endif // MAINWINDOW_H
