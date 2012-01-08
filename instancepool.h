
#ifndef INSTANCEPOOL_H_
#define INSTANCEPOOL_H_

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "instance.h"

using namespace std;


class InstancePool
{
private:
	unsigned insts;
	vector<Instance> instvec;

public:
	InstancePool();
	InstancePool(const InstancePool& original);
	~InstancePool();
	unsigned getNumberOfInstances() const;
	const Instance& operator[](unsigned index) const;
	InstancePool& operator=(const InstancePool& right);
	friend ostream& operator<<(ostream& out, const InstancePool& ip);
	friend istream& operator>>(istream& in, InstancePool& ip);


};



#endif
