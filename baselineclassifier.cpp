#include "baselineclassifier.h"

using namespace std;

BaselineClassifier::BaselineClassifier()
{
	this->spmc=0;
	this->hamc=0;
}

void BaselineClassifier::train(const InstancePool& trainingPool)
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
	if (spmc==0&&hamc==0)
	{
		return false;
	}
	if (spmc>hamc)
	{
		return true;
	}
	else
	{
		return false;
	}
}

