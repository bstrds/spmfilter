#ifndef KNNCLASSIFIER_H_
#define KNNCLASSIFIER_H_

#include "instancepool.h"
#include "classifier.h"

using namespace std;

typedef struct board					// Struct pou krataei ena bool category kai to distance se float
{
	bool category;
	float dist;
}board;

class KNNClassifier : public Classifier {

private:
	unsigned short k;
	board *dists;			//dilosi pinaka apo structs typou board
	bool check;
	InstancePool *ip;		

public:

	KNNClassifier(unsigned short kin = 5);
	static float distance(const Instance& inst1, const Instance& inst2);
	void train(const InstancePool& trainingPool);
	void newboard(void);
	bool classify(const Instance& inst) const;
	~KNNClassifier();

};


#endif
