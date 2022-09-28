#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

class ParticleType {
public:
	ParticleType (const char* name, double mass, int charge);
	//Dichiarazione e implementazione dei "getters"
	const char* GetName () const { return fName; }
	double GetMass () const { return fMass; }
	int GetCharge () const { return fCharge; }
	virtual void print (bool endline=true);
	virtual double GetWidth () const { return 0; };
private:
	const char* fName;
	const double fMass;
	const int fCharge;
};

#endif