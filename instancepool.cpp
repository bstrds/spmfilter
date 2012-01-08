#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "instancepool.h"
#include "instance.h"


using namespace std;

InstancePool::InstancePool()							//default κατασκευαστης
{
	insts = 0;								//μηδενιζει τον αριθμο instances και 
	instvec.clear();							//καθαριζει τον vector
}


InstancePool::InstancePool(const InstancePool& original)			//κατασκευαστης αντιγραφου
{
	this->insts = original.insts;							
	for (unsigned i=0; i<insts; i++)
	{
		this->instvec.push_back(original.instvec[i]);
	}
}

InstancePool::~InstancePool()
{
	instvec.clear();
}

unsigned InstancePool::getNumberOfInstances() const
{
	return this->insts;
}

const Instance& InstancePool::operator[](unsigned index) const
{
	return this->instvec[index];
}

InstancePool& InstancePool::operator=(const InstancePool& right)
{
	InstancePool *newIP;
	newIP = new InstancePool(right);
	return (*newIP);
}

istream& operator>>(istream& in, InstancePool& ip)
	{
		string word;
		string temp;
		unsigned i=1;
		while(in>>word)
		{
			if (word[0]=='"')
			{
				while (word[i] != '"')
				{
					temp.push_back(word[i]);
					i++;
				}
				break;
			}
		}
		ip.insts = (unsigned) atoi(temp.c_str());
		for (i = 0; i<ip.insts; i++)
		{
			ip.instvec.resize(i+1);
			in >> ip.instvec[i];
		}
		return in;
	}

ostream& operator<<(ostream& out, const InstancePool& ip)
{
	 out << "< messagecollection messages = \""
		 << ip.insts << "\" >"<< endl;
	 for (unsigned i=0; i<ip.insts; i++)
	 {
		 out << ip[i];
	 }
	 out << endl <<"</ messagecollection >" << endl;
	 return out;
}
