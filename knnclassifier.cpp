#include "knnclassifier.h"
#include <math.h>
#include <set>

using namespace std;


KNNClassifier::KNNClassifier(unsigned short kin)
{
	this->k = kin;
	this->check = true;
	(*ip) = InstancePool();
}

KNNClassifier::~KNNClassifier()
{
	delete[] this->dists;
	delete this->ip;
}

float KNNClassifier::distance(const Instance& inst1, const Instance& inst2)
{

	set<unsigned> keyset;

	for (unsigned i=0; i<inst1.getNumberOfFeatures(); i++)
	{
		keyset.insert(inst1.getFeatureID(i));
	}
	for (unsigned i=0; i<inst2.getNumberOfFeatures(); i++)
	{
		keyset.insert(inst2.getFeatureID(i));
	}
	unsigned size = keyset.size();
	unsigned check1[size];
	unsigned check2[size];
	for (unsigned i=0; i<size; i++)
	{
		check1[i] = 0;
		check2[i] = 0;
	}
	set<unsigned>::const_iterator it;
	unsigned counter = 0;
	for (it=keyset.begin(); it!=keyset.end(); it++)
	{
		for (unsigned i=0; i<inst1.getNumberOfFeatures(); i++)
		{
			if(*it==inst1.getFeatureID(i))
			{
				check1[counter] = inst1.getFrequency(i);
			}
		}
		for (unsigned i=0; i<inst2.getNumberOfFeatures(); i++)
		{
			if(*it==inst2.getFeatureID(i))
			{
				check2[counter] = inst2.getFrequency(i);
			}
		}
		counter++;
	}

	unsigned sum = 0;
	for(unsigned i=0; i<size; i++)
	{
		unsigned a = 0;
		if(check1[i]>check2[i])
		{
			a = check1[i]-check2[i];
		}
		else
		{
			a = check2[i]-check1[i];
		}
		sum = sum + pow(a,2);
	}
	float a = sqrt(sum);
	return a;
}

void KNNClassifier::train(const InstancePool& trainingPool)
{
	if((*ip).getNumberOfInstances()==0)
	{
		this->ip = new InstancePool(trainingPool);
	}
	else
	{
		(*ip) = InstancePool();
		this->ip = new InstancePool(trainingPool);
	}
	newboard();
	this->check=false;
}

bool KNNClassifier::classify(const Instance& inst) const
{
	if(this->check)
	{
		return false;
	}

	board temp;
	temp.dist = 0.0;
	unsigned spmcount = 0;
	unsigned hamcount = 0;
	for(unsigned i=0; i<(*ip).getNumberOfInstances(); i++)
	{
		dists[i].dist=distance(inst,(*ip)[i]);
		dists[i].category=(*ip)[i].getCategory();
	}
    for(unsigned i=1; (i<=(*ip).getNumberOfInstances()); i++)
	{
		for (unsigned j=0; j<((*ip).getNumberOfInstances()-1); j++)
		{
			if (dists[j+1].dist<dists[j].dist)
			{
				temp.dist = dists[j].dist;
				temp.category = dists[j].category;
				dists[j].dist = dists[j+1].dist;
				dists[j].category = dists[j+1].category;
				dists[j+1].dist = temp.dist;
				dists[j+1].category = temp.category;
			}
		}
	}
    for(unsigned i=0; i<k; i++)
    {
		if(dists[i].category)
		{
			spmcount=spmcount+1;
		}
		else
		{
			hamcount=hamcount+1;
		}
    }
    if(spmcount<hamcount)
    {
    	return false;
    }
    else
    {
    	return true;
    }
}

void KNNClassifier::newboard()
{
	dists = new board[(*ip).getNumberOfInstances()];
}


