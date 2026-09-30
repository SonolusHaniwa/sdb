#ifndef Functions_HasParticleEffect_H
#define Functions_HasParticleEffect_H

double HasParticleEffect(double id) {
	return particleEffects.count(int(id));
}

#endif
