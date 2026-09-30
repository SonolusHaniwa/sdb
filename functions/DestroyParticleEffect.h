#ifndef Functions_DestroyParticleEffect_H
#define Functions_DestroyParticleEffect_H

double DestroyParticleEffect(double particleId) {
	int id = particleId;
	if (activeEffects.count(id) == 0) return 0;
	activeEffects.erase(id);
	return 0;
}

#endif
