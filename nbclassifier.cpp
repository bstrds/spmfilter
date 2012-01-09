// Ζαχαρόπουλος Ερμής (Α.Μ 3100219)   &  Κυπριανίδης Γιώργος (Α.Μ 3100225) 

#include "nbclassifier.h"
#include <set>
#include <string>
#include <math.h>

using namespace std;

NaiveBayesClassifier::NaiveBayesClassifier()				//kataskeyastis nbc
{
	this->pspm=0.0;
	this->probs=NULL;
	this->pham=0.0;
}

void NaiveBayesClassifier::train(const InstancePool& trainingPool)	//methodos train tou nbc
{
	unsigned spmc=0;
	unsigned hamc=0;
	unsigned numofkeys;
	unsigned counter = 0;
	set<unsigned>::const_iterator it;
	for(unsigned i=0; i<trainingPool.getNumberOfInstances(); i++)			//metrisi pli8os spam/ham
	{
		if(trainingPool[i].getCategory())
		{
			spmc++;
		}
		else
		{
			hamc++;
		}
		for(unsigned j=0; j<trainingPool[i].getNumberOfFeatures(); j++)			//eisagogi olwn twn monadikwn id se ena set
		{
			{
				this->keyset.insert(trainingPool[i].getFeatureID(j));
			}
		}
	}
	numofkeys = this->keyset.size();
	unsigned Mspm[numofkeys];					//pinakas me ton ari8mo emfanisewn se spam minimata gia ka8e keyword
	unsigned Mham[numofkeys];					//antostixa gia ham
	for (unsigned i=0; i<numofkeys; i++)
	{
		Mspm[i]=0;
		Mham[i]=0;
	}

	for (it=this->keyset.begin(); it!=this->keyset.end(); it++)				//gemizoume tous pinakes Mham/Mspam
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
	this->pspm = ((float)spmc / trainingPool.getNumberOfInstances());	//P(spam)
	this->pham = 1 - this->pspm;						//P(ham)
	this->probs = new cop[numofkeys];
	for (unsigned i=0; i<numofkeys; i++)
	{
		this->probs[i].copspm = ((float)(1 + Mspm[i]) / (2 + spmc));		//euresh P(i | spam) gia ka8e keyword i
		this->probs[i].copham = ((float)(1 + Mham[i]) / (2 + hamc));		//to idio gia ham
	}
}

bool NaiveBayesClassifier::classify(const Instance& inst) const			//methodos taksinomisis enos agnwstou instance
{
	if (keyset.empty())						//elegxos gia to an exei kli8ei i train
	{
		return false;
	}

	unsigned counter=0;
	float spamsum=0.0;
	float hamsum=0.0;
	unsigned instfeats = inst.getNumberOfFeatures();
	unsigned numofkeys=this->keyset.size();
	unsigned flagger[numofkeys];					//pinakas me ta xi apo to P(ti | spam)^xi

	for (unsigned i=0; i<numofkeys; i++)
	{
		flagger[i]=0;
	}

	set<unsigned>::const_iterator it;

	for (it=this->keyset.begin(); it!=this->keyset.end(); it++)		//ypologismos tou xi gia kathe i
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
	for (unsigned i=0; i<numofkeys; i++)			//ypologismos tou a8roismatos tis polymetavlitis bernoulli gia spam/ham
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

NaiveBayesClassifier::~NaiveBayesClassifier()				//katastrofeas 
{
	delete[] this->probs;						//diagrafei to struct
}

