#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

#include "instancepool.h"
#include "instance.h"

using namespace std;

class Classifier
{

public:
	virtual void train(const InstancePool& trainingPool) = 0;
	virtual bool classify(const Instance& inst) const = 0;
	virtual ~Classifier() {}

};


#endif
