/*lol*/

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

typedef struct message			//αντι για 3 πινακες , φτιαχνουμε ενα struct-πινακα που περιεχει
{					//3 στοιχεια στην καθε θεση.
	string keyword;
	unsigned id;
	unsigned frequency;
}message;

class Instance {

private:				//δηλωσεις μεταβλητων
	unsigned features;		
	bool category;
	string fileName;
	message *elements;



public:					//δηλωσεις μεθοδων

	Instance(unsigned features=0);
	unsigned getNumberOfFeatures() const;
	Instance(const Instance& original);
	~Instance();
	void setCategory(bool category);
	bool getCategory() const;
	void setFileName(const string& fileName);
	string getFileName() const;
	void setFeature(unsigned i, const string& feature, unsigned featureID,unsigned frequency);
	string getFeature(unsigned i) const;
	unsigned getFeatureID(unsigned i) const;
	unsigned getFrequency(unsigned i) const;
	Instance& operator=(const Instance& right);
	friend ostream& operator<<(ostream& out, const Instance& inst);
	friend istream& operator>>(istream& in, Instance& inst);

};

#endif
