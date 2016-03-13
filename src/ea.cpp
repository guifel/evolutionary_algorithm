#include "ea.h"

struct sort_pred {
    bool operator()(const std::pair<int,double> &left, const std::pair<int,double> &right) {
        return left.second < right.second;
    }
};

EA::EA(EARepresentation* representation, EABaseProblem* pb)
{
    initialGeneration = representation;
    problem = pb;
    curentGeneration = representation;
    mutRate = 0;
    crossoverRate = 0;
    poolSize = 0;
    generationNumber = 100;
    overProduction = 0;
    adultSel = FitnessProportional;
    childSel = FitnessProportional;
}

void EA::evolv()
{

    curentGeneration = initialGeneration;
    curentGeneration->clearList();
    abort = false;

    for(int g = 0; g < generationNumber; g++)
    {
        if(abort) break;

        problem->genotypeToPhenotype(curentGeneration);

        problem->fitFct(curentGeneration);

        emit logReport(g,curentGeneration->getFitList(),generationNumber,curentGeneration->getBestString());

        adultSelection();

        //Creat a copy of the last generation
        newGeneration = curentGeneration->newRepresentation();

        // PARENT SELECTION
        parentsSelection();

        EARepresentation* todel;
        todel = curentGeneration;
        curentGeneration = newGeneration;

        delete todel;

        newGeneration->mutation(mutRate);



    }
}

void EA::setMut(double rate)
{
    mutRate = rate;
}

void EA::setCrossover(double rate)
{
    crossoverRate = rate;
}

void EA::setPoolSize(int n)
{
    poolSize = n;
}

void EA::setGenerationNumber(int n)
{
    generationNumber = n;
}

void EA::adultSelection()
{

    std::list<int> fitList(curentGeneration->getFitList());

    //If the pool already have the right size (No overproduction)
    if(fitList.size() <= poolSize) {return;}

    //Turn the wheel to fill the pool
    std::list<int>::iterator it = fitList.begin();

    int selected(0);
    for(int i; i<poolSize ; i++)
    {
        switch(adultSel)
        {
        case FitnessProportional:
            selected = fitnessProportional(fitList);
            break;
        case SigmaScaling:
            selected = sigmaScaling(fitList);
            break;
        case RankSelection:
            selected = rankSelection(fitList);
            break;
        case Tournament:
            tournamentSize = tournamentSizeA;
            tournamentp = tournamentpA;
            selected = tournament(fitList);
            break;
        }


        std::advance(it,selected);
        *it = -1;
        it = fitList.begin();
    }


    //Delete non selected phenotype
    std::vector<int> deletList;
    int i(0);
    for(std::list<int>::iterator it = fitList.begin(); it!=fitList.end(); ++it)
    {
        if((*it) != -1) deletList.push_back(i);
        i++;
    }

    curentGeneration->deletIndividuals(deletList);

}

void EA::parentsSelection()
{

    if(mixing)
        for(int i(0); i < curentGeneration->getFitList().size(); i++)
            newGeneration->addChildren(curentGeneration,i);


    std::list<int> fitList(curentGeneration->getFitList());

    //Turn the wheel to fill the pool of children
    int selected1(0);
    int selected2(0);
    int round = ((double)poolSize*(1 +(((double)overProduction)/100)));

    for(int i(0); i<round/2; i++)
    {


        switch(childSel)
        {
        case FitnessProportional:
            selected1 = fitnessProportional(fitList);
            selected2 = fitnessProportional(fitList);
            break;
        case SigmaScaling:
            selected1 = sigmaScaling(fitList);
            selected2 = sigmaScaling(fitList);
            break;
        case RankSelection:
            selected1 = rankSelection(fitList);
            selected2 = rankSelection(fitList);
            break;
        case Tournament:
            tournamentSize = tournamentSizeC;
            tournamentp = tournamentpC;
            selected1 = tournament(fitList);
            selected2 = tournament(fitList);
            break;
        }


        curentGeneration->crossover(crossoverRate,selected1,selected2);

        newGeneration->addChildren(curentGeneration,selected1);
        newGeneration->addChildren(curentGeneration,selected2);

    }

}


int EA::fitnessProportional(std::list<int> fitList)
{
    //Calculate the total fit value sum
    int fitSum(0);
    for(std::list<int>::iterator it = fitList.begin(); it!=fitList.end(); ++it)
        fitSum += (*it);
    fitSum -= std::count(fitList.begin(),fitList.end(),-1);

    //Calculate the wheel (range)
    int i(1);
    std::vector<double> range;
    range.push_back(0); 
    for(std::list<int>::iterator it = fitList.begin(); it!=fitList.end(); ++it)
    {

        if ((*it) == -1)range.push_back(range[i-1]);
        else
        {
            range.push_back(range[i-1] + (((double)(*it))/(double)fitSum));
        }

        i++;
    }

    //Spin the wheel and return the index of the winner
    double wheel(((double)rand())/RAND_MAX);
    for(int i = 1;i < range.size();i++)
    {
        if(wheel < range[i] and wheel > range[i-1])
            return i-1;

    }


}

int EA::sigmaScaling(std::list<int> fitList)
{

    int fakeGuy(std::count(fitList.begin(),fitList.end(),-1));
    int realSize(fitList.size() - fakeGuy);

            int fitSum(0);
    for(std::list<int>::iterator it = fitList.begin(); it!=fitList.end(); ++it)
    {
        if((*it) == -1) continue;
        else fitSum += (*it);
    }

    double avg = ((double)fitSum)/((double)realSize);

    double etype(0);
    for(std::list<int>::iterator it = fitList.begin(); it!=fitList.end(); ++it)
    {
       if((*it) == -1) continue;
       else etype += pow((((double)(*it)) - avg),2);
    }

    etype = sqrt(etype);

    int i(1);
    std::vector<double> range;
    range.push_back(0);
    for(std::list<int>::iterator it = fitList.begin(); it!=fitList.end(); ++it)
    {

        if ((*it) == -1)range.push_back(range[i-1]);
        else
        {
            range.push_back(range[i-1] + (1 + ((((double)(*it)) - avg)/(2*etype)))/((double)realSize));
            //qDebug() << "       RANGE" << range[i] << avg << etype << realSize << (*it);
        }

        i++;
    }

    double wheel(((double)rand())/RAND_MAX);
    for(int i = 1;i < range.size();i++)
    {
        if(wheel < range[i] and wheel > range[i-1])
            return i-1;

    }

}

int EA::rankSelection(std::list<int> fitList)
{

    int fakeGuy(std::count(fitList.begin(),fitList.end(),-1));
    int realSize(fitList.size() - fakeGuy);

    std::list<int>::iterator it1 = fitList.begin();
    std::vector<std::pair<int,double> > ranked;

    // creat a list wich save the index to sort
    for(int i(0); i < fitList.size();i++)
    {
        ranked.push_back(std::make_pair(i,(*it1)));
        it1++;
    }
    std::sort(ranked.begin(),ranked.end(),sort_pred());


    // kick the -1
    for(std::vector<std::pair<int,double> >::iterator it = ranked.begin(); it!=ranked.end(); ++it)
        if((*it).second == -1) ranked.erase(it);



    // creat the wheel    
    double min = rankSP;
    double max = 2 - min;
    int i(0);

    ranked[0].second = 0;
    ranked.push_back(std::make_pair(-123,0));



    for(int i(1);i < ranked.size();i++)
    {


            ranked[i].second = ranked[i-1].second  + ( (min + ((max - min) * ((i - 1)/(((double)ranked.size()) - 2)) ) ) /(((double)ranked.size())-1) );



    }



    double wheel(((double)rand())/RAND_MAX);
    for(int i = 1;i < ranked.size();i++)
    {

        if(wheel < ranked[i].second and wheel > ranked[i-1].second)
        {
            return ranked[i-1].first;
        }

    }

}





int EA::tournament(std::list<int> fitList)
{
    int best(-1);
    int bestValue(0);
    std::vector<int> group;
    int selector(0);

    if(tournamentSize > poolSize) tournamentSize = poolSize;


    std::list<int>::iterator it = fitList.begin();

    for(int i(0); i < tournamentSize; i++)
    {
        selector = rand() %fitList.size();

        while(std::count(group.begin(),group.end(),selector))
            selector = rand() %fitList.size();

       group.push_back(selector);
       std::advance(it,selector);

       if((*it) > bestValue)
       {
           best = selector;
           bestValue = (*it);
       }

       it = fitList.begin();
    }


    std::vector<int>::iterator it2 = group.begin();

    if(((double)rand())/RAND_MAX < tournamentp)
    {
        return best;
    }
    else
    {
      std::advance(it2,rand() % group.size());
      return (*it2);
    }

}


