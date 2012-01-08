#ifndef CLASSIFIEREVALUATOR_H_
#define CLASSIFIEREVALUATOR_H_

#include "classifier.h"

class ClassifierEvaluator
{
private:

	unsigned tpos;
	unsigned tneg;
	unsigned fpos;
	unsigned fneg;
	unsigned total;

public:
	ClassifierEvaluator(Classifier& classifier,const InstancePool& trainingPool, const InstancePool& testPool);
	float getAccuracy() const;
	float getPrecision() const;
	float getRecall() const;
};

#endif
