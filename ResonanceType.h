#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H
#include "ParticleType.h"

class ResonanceType : public ParticleType {
public:
	ResonanceType (const char* name, double mass, int charge, double width);
	ResonanceType (ParticleType particle, double width);
	double GetWidth () const { return fWidth; }
	void print (bool endline=true);
private:
	const double fWidth;
};

#endif
