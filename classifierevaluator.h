// Ζαχαρόπουλος Ερμής (Α.Μ 3100219)   &  Κυπριανίδης Γιώργος (Α.Μ 3100225) 

#ifndef CLASSIFIEREVALUATOR_H_
#define CLASSIFIEREVALUATOR_H_

#include "classifier.h"

class ClassifierEvaluator				//o sxoliasmos einai peritos :/		
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
