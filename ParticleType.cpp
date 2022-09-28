#include <iostream>
#include "ParticleType.h"
using namespace std;

//costruttore
ParticleType::ParticleType (const char* name, double mass, int charge) : fName (name), fMass (mass), fCharge(charge) {}

void ParticleType::print (bool endline) {
	cout << "< Object 'ParticleType': name=\"" << fName << "\" mass=" << fMass << " charge=" << fCharge << ">";
	if (endline)
		cout << endl;
}