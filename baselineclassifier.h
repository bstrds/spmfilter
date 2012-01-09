#ifndef BASELINECLASSIFIER_H_
#define BASELINECLASSIFIER_H_

#include "instancepool.h"
#include "classifier.h"

using namespace std;

class BaselineClassifier : public Classifier		//Dilosi ypoklasis baseline tis klasis classifier
{

private:						//dilosi idiotikwn metavlitwn
	unsigned spmc;
	unsigned hamc;

public:							//dilosi dimosiwn me8odwn
	BaselineClassifier();
	void train(const InstancePool& trainingPool);
	bool classify(const Instance& inst) const;
	~BaselineClassifier() {}				//katastrofeas pou den periexete sto cpp giati ylopoieitai edw.
};

#endif
