#include "baselineclassifier.h"

using namespace std;

BaselineClassifier::BaselineClassifier() 					//kataskeyastis
{
	this->spmc=0;
	this->hamc=0;
}

void BaselineClassifier::train(const InstancePool& trainingPool)		//ekpedeysi tou baseline
{
	for (unsigned i=0; i<trainingPool.getNumberOfInstances(); i++)
	{
		if(trainingPool[i].getCategory())
		{
			spmc++;
		}
		else
		{
			hamc++;
		}
	}
}

bool BaselineClassifier::classify(const Instance& inst) const
{
	if (spmc==0&&hamc==0)						//elegxos gia to an exei kli8ei i train
	{
		return false;
	}
	if (spmc>hamc)							//katataksi minimatos
	{
		return true;
	}
	else
	{
		return false;
	}
}

