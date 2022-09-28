#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Particle.h"
using namespace std;

int Particle::fNParticleType = 0;
ParticleType* Particle::fParticleType[Particle::fMaxNumParticleType];

int Particle::FindParticle (const char* name) {
	for (int i = 0; i < fNParticleType; i ++) {
		if (fParticleType[i]->GetName() == name)
		return i;
	}
	return -1;
}


void Particle::AddParticleType ( const char* name, double mass, int charge, double width){
	if(FindParticle(name) == -1 && fNParticleType <= fMaxNumParticleType) {
    if(width!=0) fParticleType [fNParticleType] = new ResonanceType(name, mass, charge, width);
		else fParticleType [fNParticleType] = new  ParticleType(name, mass, charge);
    fNParticleType++;
	}

}

//costruttori

Particle::Particle () : fIParticle(-1), fPx(0), fPy(0), fPz(0) {}
Particle::Particle (const char* name, double px, double py, double pz) : fPx(px), fPy(py), fPz(pz) {
	int index = FindParticle(name);
	if (index == -1)
		cout << "No particle found with this name." << endl;
	else
		fIParticle = index;
}

void Particle::SetIParticle (int index) {
	if (index < fNParticleType)
		fIParticle = index;
	else
		cout << "Particle ID not valid." << endl;
}

void Particle::SetIParticle (const char* name) {
	int index = FindParticle(name);
	if (index == -1)
		cout << "Partice type name not valid." << endl;
	else
		fIParticle = index;
}

void Particle::printParticleTypes () {
	cout << "index\tobject" << endl;
	for (int i = 0; i < fNParticleType; i ++) {
		cout << i << '\t';
		fParticleType[i]->print();
	}
}

void Particle::SetP (double px, double py, double pz) {
	fPx = px;
	fPy = py;
	fPz = pz;
}

void Particle::print () const {
	cout << "Index: " << fIParticle << ", name: " << fParticleType[fIParticle]->GetName() <<
	", P = (" << fPx << ", " << fPy << ", " << fPz << ")" << endl;
}
//Getters
const char* Particle::GetName() const {
	return fParticleType[fIParticle]->GetName();
}

double Particle::GetMass () const {
	return fParticleType[fIParticle]->GetMass();
}

int Particle::GetCharge () const {
	return fParticleType[fIParticle]->GetCharge();
}

double Particle::GetEnergy () const {
	return sqrt(pow(GetMass(), 2) + fPx*fPx + fPy*fPy + fPz*fPz);
}

double Particle::InvMass (Particle& particle) const {
	double e = pow(GetEnergy() + particle.GetEnergy(), 2);
	double p = pow(fPx + particle.fPx, 2) + pow(fPy + particle.fPy, 2) + pow(fPz + particle.fPz, 2);
	return sqrt(e - p);
}

int Particle::decay2body (Particle &dau1, Particle &dau2) const {
	if (GetMass() == 0.0) {
		cout << "Decayment cannot be preformed if mass is zero." << endl;
		return 1;
	}

	double massMot = GetMass();
	double massDau1 = dau1.GetMass();
	double massDau2 = dau2.GetMass();

	if (fIParticle > -1) {
		float x1, x2, w, y1, y2;
		double invnum = 1./RAND_MAX;
		do {
			x1 = 2.0 * rand()*invnum - 1.0;
			x2 = 2.0 * rand()*invnum - 1.0;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);

		w = sqrt((-2.0 * log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;

		massMot += fParticleType[fIParticle]->GetWidth() * y1;
	}

	if(massMot < massDau1 + massDau2){
		cout << "Decayment cannot be preformed because mass is too low in this channel." << endl;
		return 2;
	}

	double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

	double norm = 2*M_PI/RAND_MAX;

	double phi = rand()*norm;
	double theta = rand()*norm*0.5 - M_PI/2.;
	dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
	dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

	double energy = sqrt(fPx*fPx + fPy*fPy + fPz*fPz + massMot*massMot);

	double bx = fPx/energy;
	double by = fPy/energy;
	double bz = fPz/energy;

	dau1.boost(bx,by,bz);
	dau2.boost(bx,by,bz);

	return 0;
}

void Particle::boost (double bx, double by, double bz) {
	double energy = GetEnergy();

	double b2 = bx*bx + by*by + bz*bz;
	double gamma = 1.0 / sqrt(1.0 - b2);
	double bp = bx*fPx + by*fPy + bz*fPz;
	double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

	fPx += gamma2*bp*bx + gamma*bx*energy;
	fPy += gamma2*bp*by + gamma*by*energy;
	fPz += gamma2*bp*bz + gamma*bz*energy;
}