#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "instance.h"

using namespace std;

Instance::Instance(unsigned feats)  							//default κατασκευαστης
{
	this->features=feats;								//περνιεται ο αριθμος features που
	if (feats == 0)									//πηρε ο κατασκευαστης σαν
	{										//argument και γινεται ελεγχος για
		this->elements=NULL;							//το αν θα δημιουργηθει η οχι
	}										//καινουργιο struct (message)
	else										//το οποιο περιεχει τις 3 πληροφοριες
	{										//που χρειαζεται καθε keyword σε καθε θεση
		this->elements=new message[feats];					//(freq,id,και το ιδιο το keyword)
	}
	return;
}

Instance::Instance(const Instance& original)						//κατασκευαστης αντιγραφου
{
	size_t temp = original.fileName.length();					//εκχωρουνται στο αντιγραφο τα
	this->features=original.features;						//features και category του original
	this->category=original.category;
	for(unsigned i=0 ; i<temp ; i++)						//εκχωρειται το path του αρχειου
	{										//χαρακτηρα-χαρακτηρα
		this->fileName.push_back(original.fileName[i]);
	}	
	if (original.features==0)							//ελεγχος για το αν περιεχει
	{										//keyword το μηνυμα και μηδενισμος
		this->elements=NULL;							//του struct αν δεν περιεχει
	}
	else										//δημιουργια νεου struct για να
	{										//εχει ακριβως τοσες θεσεις οσα ειναι
		this->elements=new message[features];					//και τα keywords
		for (unsigned i=0; i<features; i++)					//επαναληψη για το γεμισμα του struct
		{
			this->elements[i].id = original.elements[i].id;
			this->elements[i].frequency = original.elements[i].frequency;
			for(unsigned j=0 ; j<temp ; j++)
			{
				this->elements[i].keyword.push_back(original.elements[i].keyword[j]);
			}
		}
	}
}

Instance::~Instance() 									//καταστροφεας
{

	if (this->features!=0)								//αν το struct δεν ειναι αδειο
	{
		delete[] this->elements;						//καταστρεφεται το struct, που ειχε 
	}										//φτιαχτει με new
}

unsigned Instance::getNumberOfFeatures() const						//δημοσια μεθοδος, που οταν καλειται
{											//επιστρεφει τον αριθμο features
	return this->features;

}

void Instance::setFeature(unsigned i, const string& feature, unsigned featureID,	//δημοσια μεθοδος, που οταν καλειται,
unsigned frequency)									//αν το i δεν υπερβαινει τον αριθμο
{											//λεξεων-κλειδιων του μηνυματος, αποθηκευει
	if (i>=features)								//στην θεση i του struct message
	{										//το keyword(arg: feature), 
		return;									//το id(arg: featureID) και το 
	}										//frequency που παιρνει σαν arguments
	size_t temp=feature.length();
	for(unsigned j=0; j<temp; j++)

	{
		this->elements[i].keyword[j]=feature[j];
	}
	this->elements[i].id=featureID;
	this->elements[i].frequency=frequency;
}

string Instance:: getFeature(unsigned i) const						//δημοσια μεθοδος, που οταν καλειται
{											//επιστρεφει το string keyword (λεξη κλειδι) 
	return this->elements[i].keyword;						//που βρισκεται στην θεση i του struct
}

void Instance::setCategory(bool cat)							//δημοσια μεθοδος, που οταν καλειται
{											//αποθηκευει την bool τιμη που παιρνει ως
	this->category=cat;								//argument στην μεταβλητη category του αντικειμενου
}

bool Instance::getCategory() const							//δημοσια μεθοδος, που οταν καλειται
{											//επιστρεφει την τιμη της μεταβλητης category
	return this->category;								//του αντικειμενου
}

void Instance::setFileName(const string& filename)					//δημοσια μεθοδος, που οταν καλειται
{											//αποθηκευει στην μεταβλητη fileName του
	size_t temp=filename.length();							//αντικειμενου το string που παιρνει ως 
	for (unsigned i=0; i<temp; i++)							//argument
	{
		this->fileName.push_back(filename[i]);
	}
}

string Instance::getFileName() const							//δημοσια μεθοδος, που οταν καλειται
{											//επιστρεφει την τιμη της μεταβλητης fileName
	return this->fileName;								//του αντικειμενου
}

unsigned Instance::getFeatureID(unsigned i) const					//δημοσια μεθοδος, που οταν καλειται
{											//επιστρεφει την τιμη της μεταβλητης id 
	return this->elements[i].id;							//στην θεση i του struct 
}

unsigned Instance::getFrequency(unsigned i) const					//δημοσια μεθοδος, που οταν καλειται
{											//επιστρεφει την τιμη της μεταβλητης frequency
	return this->elements[i].frequency;						//στην θεση i του struct
}


Instance&  Instance::operator=(const Instance& right)					//υπερφορτωση του τελεστη '=' για την Instance.
{											//χρησιμοποιειαι ο κατασκευαστης αντιγραφου 
	Instance *newInstance;								//για να εκχωρηθει στο αντικειμενο στην 
	newInstance = new Instance(right);						//αριστερη πλευρα του '=' ενα αντιγραφο του
	return (*newInstance);								//αντικειμενου που ειναι στην δεξια πλευρα
}

ostream& operator<<(ostream& out, const Instance& inst)					//υπερφορτωση του τελεστη '<<' για την Instance.
{											//οταν χρησιμοποιειται ο '<<', τυπονωνται στο 
	out << endl << "< message file = \""<< inst.fileName << "\" category = \"";	//out (καποιο output oπως αρχ.κειμενου ή οθονη)
	if (inst.category!=0)								//ολες οι πληροφοριες για το μηνυμα που υπαρχουν 
	{										//αποθηκευμενες στο inst, με τη μορφη που τυπονωνταν 
		out << "spam\"";							//και στην πρωτη εργασια.
	}
	else
	{
		out << "ham\"";
	}
    out << " features = \"" << inst.features << "\" >" << endl;
    for (unsigned i = 0; i < inst.features; i++)
    {
	   out << "< feature token = \"" << inst.elements[i].keyword.c_str() << "\" id = \""
	   << inst.elements[i].id << "\" freq = \"" << inst.elements[i].frequency <<
	   "\" />" << endl;
    }
    out << "</ message >" << endl;
    return out;
}

istream& operator>>(istream& in, Instance& inst)					//υπερφορτωση του τελεστη '>>' για την Instance.
{											//οταν χρησιμοποιειται σε ενα αντικειμενο Ιnstance,
	string word;									//συλλεγει απο ενα istream ολες τις πληροφοριες 
	string temp;									//που χρειαζομαστε να αποθηκευσουμε για ενα ακριβως μηνυμα. 
	unsigned i = 1;									//η υλοποιηση αυτης της μεθοδου εγινε με το σκεπτικο
	unsigned linechanges=0;								//πως θα διαβαζει αρχεια που ειναι ακριβως του ιδιου 												//στυλ με την εξοδο της πρωτης εργασιας.
	unsigned tempFeatures;								
	while(in>>word)									//διαβαζει λεξεις μεχρι να συναντησουμε '"'
	{										//σαν πρωτο χαρακτηρα.
		if (word[0]=='"')
		{
			while (word[i] != '"')						//διαβαζει την λεξη μεσα στα εισαγωγικα και
			{								//την εκχωρει στο fileName 
				inst.fileName.push_back(word[i]);			//χαρακτηρα-χαρακτηρα.
				i++;
			}
		break;									//εφ'οσον διαβασουμε την λεξη προχωραμε στον 
		}									//υπολοιπο κωδικα χωρις να ξαναμπουμε στην while.
	}
	for(i=0; i<3; i++) { in>>word; }						//περναμε 2 λεξεις και σταματαμε στην τριτη.
	if (word=="\"spam\"")								
	{
		inst.category=true;							//οριζουμε την κατηγορια συμφωνα με τη λεξη που διαβαστηκε.
	}
	else
	{
		inst.category=false;
	}
	for(i=0; i<3; i++) { in>>word; }						//περναμε αλλες 2 λεξεις, σταματαμε στην τριτη.
	i=1;

		while (word[i] != '"')
		{
			temp.push_back(word[i]);					//γεμιζουμε το string temp με τον αριθμο features
			i++;
		}
	tempFeatures = (unsigned) atoi(temp.c_str());					//μετατροπη του string σε unsigned
		if (tempFeatures != inst.features)					//ελεγχος για την χωρητικοτητα του struct
		{
			delete[] inst.elements;						//διαγραφη του struct αν ο αριθμος θεσεων του ειναι διαφορος
			inst.elements = new message[tempFeatures];			//απο τα features, και δημιουργια νεου struct με ακριβως
			inst.features = tempFeatures;					//tempFeatures(features μηνυματος) θεσεις.
		}

	for (linechanges=0; linechanges<inst.features; linechanges++)			//επαναληψη για να γεμισει το struct, τρεχει features φορες.
	{
		for (i=0; i<6; i++) { in>>word; }					//περναμε 5 λεξεις, σταματαμε στην 6η.
		i=1;
			while (word[i] != '"')						//γεμιζουμε την linechanges θεση του struct με το keyword
			{								//που διαβασαμε. 
				inst.elements[linechanges].keyword.push_back(word[i]);
				i++;
			}
		for (i=0; i<3; i++) { in>>word; }					
		i=1;
		temp.clear();								//καθαριζουμε το temp
			while (word[i] != '"')						//περναμε το id στο temp string
			{
				temp.push_back(word[i]);
				i++;
			}
		inst.elements[linechanges].id = (unsigned) atoi(temp.c_str());		//μετατροπη string σε unsigned και εκχωρηση του id στο struct 
		for (i=0; i<3; i++) { in>>word; }					//περναμε 2 λεξεις, σταματαμε στην 3η.
		i=1;
		temp.clear();								//καθαριζουμε το temp
			while (word[i] != '"')						//περναμε το frequency στο temp string
			{
				temp.push_back(word[i]);
				i++;
			}
			inst.elements[linechanges].frequency = (unsigned) atoi(temp.c_str());	//μετατροπη string σε unsigned και 
												//εκχωρηση τoυ frequency στο struct.
	}
		return in;
}

