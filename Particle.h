#ifndef PARTICLE_H
#define PARTICLE_H
#include "ParticleType.h"
#include "ResonanceType.h"

class Particle {
public:
	Particle ();
	Particle (const char* name, double px=0, double py=0, double pz=0);

	int GetIParticle () const { return fIParticle; }
	void SetIParticle (int index);
	void SetIParticle (const char* name);

	int GetPx () const { return fPx; }
	int GetPy () const { return fPy; }
	int GetPz () const { return fPz; }
	void SetP (double px, double py, double pz);

	static void AddParticleType (const char* name, double mass, int charge, double width=0);
	static void printParticleTypes ();

	void print () const;
	const char* GetName () const;
	double GetMass () const;
	int GetCharge () const;
	double GetEnergy () const;
	double InvMass (Particle& p) const;

	int decay2body(Particle &dau1, Particle &dau2) const;
	void boost(double bx, double by, double bz);
private:
	static const int fMaxNumParticleType = 10;
	static ParticleType* fParticleType[fMaxNumParticleType];
	static int fNParticleType;
	int fIParticle;
	double fPx, fPy, fPz;
	static int FindParticle (const char* name);
};

#endif