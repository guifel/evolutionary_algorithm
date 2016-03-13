#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));

    ui->plot->addGraph();
    ui->plot->xAxis->setLabel("Generation");
    ui->plot->yAxis->setLabel("Value");
    ui->plot->replot();
    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->axisRect()->setRangeZoom(Qt::Vertical);


    ui->plot->graph(0)->setPen(QPen(Qt::yellow));
    ui->plot->addGraph();
    ui->plot->graph(1)->setPen(QPen(Qt::blue));

    ui->plot->addGraph();
    ui->plot->graph(2)->setPen(QPen(Qt::red));

   connect(ui->goButton,SIGNAL(clicked(bool)),this,SLOT(goButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::graphPrint(const int generation , std::list<int> fitList, const int genMax, const QString beststr)
{
    //Best element
    int best = *std::max_element(fitList.begin(),fitList.end());
    if(best > bestFit){bestFit = best; genBest = generation;}

    // Average
    int sum(0);    
    for(std::list<int>::iterator it = fitList.begin(); it!=fitList.end(); ++it)
        sum += (*it);
    double avg = ((double)sum)/fitList.size();

    //Standard derivation
    double etype(0);
    for(std::list<int>::iterator it = fitList.begin(); it!=fitList.end(); ++it)
       etype += pow((((double)(*it)) - avg),2);
    etype = sqrt(etype);

    //Output
    ui->plot->xAxis->setRange(0, genMax + 1);
    ui->plot->yAxis->setRange(0, bestFit*1.3);
    ui->plot->graph(0)->addData(generation,etype);
    ui->plot->graph(1)->addData(generation,avg);
    ui->plot->graph(2)->addData(generation,best);
    ui->plot->replot();
    ui->listWidget->addItem(QString("Generation : %1  Best Fit value : %2  Average Fit value: %3  Deviation: %4").arg(generation+1).arg(best).arg(avg).arg(etype));
    if(generation == genMax -1)
    {
        ui->listWidget->addItem(QString("Simulation completed ! Best fit value: %1  First appeared at generation: %2").arg(bestFit).arg(genBest));
        ui->listWidget->addItem(QString("Best individual: ") + beststr);
        ui->plot->saveJpg( "lol.jpeg",  0, 0, 1.0, -1  );

    }
    ui->listWidget->scrollToBottom();
    qApp->processEvents();

}

void MainWindow::resultPrint(QString str)
{

    ui->listWidget->addItem(QString("Solution sequence found ! : ") + str);
}


void MainWindow::goButton()
{
    //Include big switch for problems
    if(ui->oneMatrix->isChecked())
    {
        int length (ui->bitLength->value());
        myRepresentation = new EABinaryString(length);
        EABinaryString* defaultRep(dynamic_cast<EABinaryString*>(myRepresentation));
        QString gene;
        gene.reserve(length);
        for(int i(0);i <ui->adultPoolSize->value();i++)
        {
           for(int j(0); j < length;j++)
             gene.append(QString::number(rand()%2));
           defaultRep->addGenotype(gene);
           gene = "";
        }
        myProblem = new OneMatrixProblem;
        myEA = new EA(defaultRep,myProblem);
    }
    else if(ui->oneMatrixR->isChecked())
    {
        int length (ui->bitLength->value());
        myRepresentation = new EABinaryString(length);
        EABinaryString* defaultRep(dynamic_cast<EABinaryString*>(myRepresentation));
        QString gene;
        gene.reserve(length);
        for(int i(0);i <ui->adultPoolSize->value();i++)
        {
           for(int j(0); j < length;j++)
             gene.append(QString::number(rand()%2));
           defaultRep->addGenotype(gene);
           gene = "";
        }
        myProblem = new OneMatrixProblemR;
        myEA = new EA(defaultRep,myProblem);
    }
    else if(ui->lolz->isChecked())
    {
        int length (ui->bitLength->value());
        myRepresentation = new EABinaryString(length);
        EABinaryString* defaultRep(dynamic_cast<EABinaryString*>(myRepresentation));
        QString gene;
        gene.reserve(length);
        for(int i(0);i < ui->adultPoolSize->value();i++)
        {
           for(int j(0); j < length;j++)
             gene.append(QString::number(rand()%2));
           defaultRep->addGenotype(gene);
           gene = "";
        }
        myProblem = new Lolz(ui->lolzZ->value());
        myEA = new EA(defaultRep,myProblem);
    }
    else if(ui->surpriseSeqGlob->isChecked())
    {
        int length(ui->lengthSuprise->value());
        int alphabet(ui->alphabetSize->value());

        myRepresentation = new EACharString(length,alphabet);
        EACharString* defaultRep(dynamic_cast<EACharString*>(myRepresentation));
        std::vector<int> gene;
        for(int i(0);i < ui->adultPoolSize->value();i++)
        {
            for(int j(0); j < length;j++)
                gene.push_back(rand()%alphabet);
            defaultRep->addGenotype(gene);
            gene.clear();
        }
        myProblem = new GlobalSurprisingSeq(length,alphabet);
        myEA = new EA(defaultRep,myProblem);

        GlobalSurprisingSeq* myProblemCasted(dynamic_cast<GlobalSurprisingSeq*>(myProblem));
        connect(myProblemCasted,SIGNAL(resultFound(QString)),this,SLOT(resultPrint(QString)));


    }
    else if(ui->surpriseSeqLoc->isChecked())
    {
        int length(ui->lengthSuprise->value());
        int alphabet(ui->alphabetSize->value());

        myRepresentation = new EACharString(length,alphabet);
        EACharString* defaultRep(dynamic_cast<EACharString*>(myRepresentation));
        std::vector<int> gene;
        for(int i(0);i < ui->adultPoolSize->value();i++)
        {
            for(int j(0); j < length;j++)
                gene.push_back(rand()%alphabet);
            defaultRep->addGenotype(gene);
            gene.clear();
        }
        myProblem = new LocalSurprisingSeq(length,alphabet);
        myEA = new EA(defaultRep,myProblem);

        LocalSurprisingSeq* myProblemCasted(dynamic_cast<LocalSurprisingSeq*>(myProblem));
        connect(myProblemCasted,SIGNAL(resultFound(QString)),this,SLOT(resultPrint(QString)));


    }


    qRegisterMetaType<std::list<int> >("std::list<int>");
    connect(myEA,SIGNAL(logReport(const int, std::list<int> ,const int, const QString)),this,SLOT(graphPrint(const int, std::list<int> ,const int, const QString)));
    connect(ui->abort,SIGNAL(clicked(bool)),myEA,SLOT(setAbort()));

    ui->plot->graph(0)->clearData();
    ui->plot->graph(1)->clearData();
    ui->plot->graph(2)->clearData();
    ui->listWidget->clear();
    bestFit = 0;
    genBest = 0;

    myEA->setMut(ui->mutationRate->value());
    myEA->setCrossover(ui->crossOverRate->value());
    myEA->setPoolSize(ui->adultPoolSize->value());
    myEA->setGenerationNumber(ui->numberOfGeneration->value());
    myEA->setOverProduction(ui->overProduction->value());
    myEA->setMixing(ui->mixingCheckBox->isChecked());
    myEA->setTournament(ui->tournamentGroupSizeAdult->value(),ui->tournamentSigmaAdult->value(),ui->tournamentGroupSizeChild->value(),ui->tournamentSigmaChild->value());
    myEA->setRankSP(ui->rankSP->value());

    if(ui->localStratAdult->isChecked())
        myEA->setAdultSelStrat(EA::Tournament);
    else myEA->setAdultSelStrat((EA::SelectionStrategy)ui->comboBox->currentIndex());

    if(ui->localStratChild->isChecked())
        myEA->setChildSelStrat(EA::Tournament);
    else myEA->setChildSelStrat((EA::SelectionStrategy)ui->comboBox_2->currentIndex());


    myEA->evolv();
}
