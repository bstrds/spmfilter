#include "classifierevaluator.h"

using namespace std;


ClassifierEvaluator::ClassifierEvaluator(Classifier& classifier,const InstancePool& trainingPool, const InstancePool& testPool)
{

	tpos=0;
	tneg=0;
	fpos=0;
	fneg=0;
	total=0;
	classifier.train(trainingPool);
	this->total=testPool.getNumberOfInstances();
	for (unsigned i=0; i<total; i++)
	{
		if(testPool[i].getCategory())
		{
			if(classifier.classify(testPool[i]))
			{
				this->tpos++;
			}
			else
			{
				this->fneg++;
			}
		}
		else
		{
			if(classifier.classify(testPool[i]))
			{
				this->fpos++;
			}
			else
			{
				this->tneg++;
			}
		}
	}
}

float ClassifierEvaluator::getAccuracy() const
{
	float a = 0.0;
	a = ((float)(this->tpos + this->tneg) / this->total );
	return a;
}

float ClassifierEvaluator::getPrecision() const
{
	float a = 0.0;
	if (((float)tpos + (float)fpos)!=0)
	{
		a = (float)tpos / ((float)tpos + (float)fpos);
		return a;
	}
	else
	{
		return a;
	}

}

float ClassifierEvaluator::getRecall() const
{
	float a = 0.0;
	if (((float)(this->tpos + this->fneg))!=0)
	{
		a = ((float)this->tpos / (float)(this->tpos + this->fneg));
		return a;
	}
	else
	{
		return a;
	}
}
