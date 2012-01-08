#ifndef BASELINECLASSIFIER_H_
#define BASELINECLASSIFIER_H_

#include "instancepool.h"
#include "classifier.h"

using namespace std;

class BaselineClassifier : public Classifier
{

private:
	unsigned spmc;
	unsigned hamc;

public:
	BaselineClassifier();
	void train(const InstancePool& trainingPool);
	bool classify(const Instance& inst) const;
	~BaselineClassifier() {}
};

#endif
