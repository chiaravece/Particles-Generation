#include <iostream>
#include "ResonanceType.h"
using namespace std;

ResonanceType::ResonanceType (const char* name, double mass, int charge, double width) : ParticleType(name, mass, charge), fWidth(width) {}

ResonanceType::ResonanceType (ParticleType particle, double width) : ParticleType(particle.GetName(), particle.GetMass(), particle.GetCharge()), fWidth(width) {}

void ResonanceType::print (bool endline) {
	cout << "<Object 'ResonanceType': name=\"" << GetName() << "\" mass=" << GetMass() << " charge=" << GetCharge() << " width=" << fWidth << ">";
	if (endline)
		cout << endl;
}