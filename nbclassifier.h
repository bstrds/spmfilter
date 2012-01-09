// Ζαχαρόπουλος Ερμής (Α.Μ 3100219)   &  Κυπριανίδης Γιώργος (Α.Μ 3100225) 

#ifndef NAIVEBAYESCLASSIFIER_H_
#define NAIVEBAYESCLASSIFIER_H_

#include "instancepool.h"
#include "classifier.h"
#include <set>

using namespace std;

class NaiveBayesClassifier : public Classifier
{

typedef struct cop					//dilosi struct gia na krataei tis desmeymenes pi8anotites
{
	float copspm;
	float copham;
}cop;

private:
	float pspm;
	float pham;
	cop *probs;
	set<unsigned> keyset;

public:
	NaiveBayesClassifier();
	void train(const InstancePool& trainingPool);
	bool classify(const Instance& inst) const;
	~NaiveBayesClassifier();

};


#endif 
