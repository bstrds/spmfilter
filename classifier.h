#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

#include "instancepool.h"
#include "instance.h"

using namespace std;

class Classifier							//afirimeni eikonikh me8odos
{
						
public:									
	virtual void train(const InstancePool& trainingPool) = 0;	//dhmosies eikonikes me9odoi
	virtual bool classify(const Instance& inst) const = 0;
	virtual ~Classifier() {}

};


#endif


//Den symperilavame arxeio cpp ka8ws den xreiazotan
