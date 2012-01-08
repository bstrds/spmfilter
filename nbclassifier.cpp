/*				*
 *				*
 *				*
 *				*/

#include "nbclassifier.h"
#include <set>
#include <string>
#include <math.h>

using namespace std;

NaiveBayesClassifier::NaiveBayesClassifier()
{
	this->pspm=0.0;
	this->probs=NULL;
	this->pham=0.0;
}

void NaiveBayesClassifier::train(const InstancePool& trainingPool)
{
	unsigned spmc=0;
	unsigned hamc=0;
	unsigned numofkeys;
	unsigned counter = 0;
	set<unsigned>::const_iterator it;
	for(unsigned i=0; i<trainingPool.getNumberOfInstances(); i++)
	{
		if(trainingPool[i].getCategory())
		{
			spmc++;
		}
		else
		{
			hamc++;
		}
		for(unsigned j=0; j<trainingPool[i].getNumberOfFeatures(); j++)
		{
			{
				this->keyset.insert(trainingPool[i].getFeatureID(j));
			}
		}
	}
	numofkeys = this->keyset.size();
	unsigned Mspm[numofkeys];
	unsigned Mham[numofkeys];
	for (unsigned i=0; i<numofkeys; i++)
	{
		Mspm[i]=0;
		Mham[i]=0;
	}

	for (it=this->keyset.begin(); it!=this->keyset.end(); it++)
	{
		for(unsigned i=0; i<trainingPool.getNumberOfInstances(); i++)
		{
			for(unsigned j=0; j<trainingPool[i].getNumberOfFeatures(); j++)
			{
				if (*it==trainingPool[i].getFeatureID(j))
				{
					if(trainingPool[i].getCategory())
					{
						Mspm[counter]++;
					}
					else
					{
						Mham[counter]++;
					}
				}
			}
		}
		counter++;
	}
	this->pspm = ((float)spmc / trainingPool.getNumberOfInstances());
	this->pham = 1 - this->pspm;
	this->probs = new cop[numofkeys];
	for (unsigned i=0; i<numofkeys; i++)
	{
		this->probs[i].copspm = ((float)(1 + Mspm[i]) / (2 + spmc));
		this->probs[i].copham = ((float)(1 + Mham[i]) / (2 + hamc));
	}
}

bool NaiveBayesClassifier::classify(const Instance& inst) const
{
	if (keyset.empty())
	{
		return false;
	}

	unsigned counter=0;
	float spamsum=0.0;
	float hamsum=0.0;
	unsigned instfeats = inst.getNumberOfFeatures();
	unsigned numofkeys=this->keyset.size();
	unsigned flagger[numofkeys];

	for (unsigned i=0; i<numofkeys; i++)
	{
		flagger[i]=0;
	}

	set<unsigned>::const_iterator it;

	for (it=this->keyset.begin(); it!=this->keyset.end(); it++)
	{
		for (unsigned i=0; i<instfeats; i++)
		{
			if (*it==inst.getFeatureID(i))
			{
				flagger[counter]=1;
			}
		}
		counter++;
	}
	for (unsigned i=0; i<numofkeys; i++)
	{
		float a1 = pow(probs[i].copspm,flagger[i]);
		float a2 = pow(1-probs[i].copspm,(1-flagger[i]));
		float a3 = pow(probs[i].copham,flagger[i]);
		float a4 = pow(1-probs[i].copham,(1-flagger[i]));
		spamsum = spamsum + log(a1) + log(a2);
		hamsum = hamsum + log(a3) + log(a4);

	}
	float c = log(pspm);
	float d = log(pham);
	if ((c + spamsum) > (d + hamsum))
	{
		return true;
	}
	else
	{
		return false;
	}
}

NaiveBayesClassifier::~NaiveBayesClassifier()
{
	delete[] this->probs;
}

