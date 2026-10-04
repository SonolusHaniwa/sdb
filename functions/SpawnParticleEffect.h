#ifndef Functions_SpawnParticleEffect_H
#define Functions_SpawnParticleEffect_H

double SpawnParticleEffect(double id, SpawnParticleEffect_Group_x_y x_y0, SpawnParticleEffect_Group_x_y x_y1, SpawnParticleEffect_Group_x_y x_y2, SpawnParticleEffect_Group_x_y x_y3, double duration, double isLooped) {
	double x1 = x_y0.x * Get(RuntimeParticleTransformId, 0) + x_y0.y * Get(RuntimeParticleTransformId, 1) + Get(RuntimeParticleTransformId, 2) + Get(RuntimeParticleTransformId, 3);
	double y1 = x_y0.x * Get(RuntimeParticleTransformId, 4) + x_y0.y * Get(RuntimeParticleTransformId, 5) + Get(RuntimeParticleTransformId, 6) + Get(RuntimeParticleTransformId, 7);
	double x2 = x_y1.x * Get(RuntimeParticleTransformId, 0) + x_y1.y * Get(RuntimeParticleTransformId, 1) + Get(RuntimeParticleTransformId, 2) + Get(RuntimeParticleTransformId, 3);
	double y2 = x_y1.x * Get(RuntimeParticleTransformId, 4) + x_y1.y * Get(RuntimeParticleTransformId, 5) + Get(RuntimeParticleTransformId, 6) + Get(RuntimeParticleTransformId, 7);
	double x3 = x_y2.x * Get(RuntimeParticleTransformId, 0) + x_y2.y * Get(RuntimeParticleTransformId, 1) + Get(RuntimeParticleTransformId, 2) + Get(RuntimeParticleTransformId, 3);
	double y3 = x_y2.x * Get(RuntimeParticleTransformId, 4) + x_y2.y * Get(RuntimeParticleTransformId, 5) + Get(RuntimeParticleTransformId, 6) + Get(RuntimeParticleTransformId, 7);
	double x4 = x_y3.x * Get(RuntimeParticleTransformId, 0) + x_y3.y * Get(RuntimeParticleTransformId, 1) + Get(RuntimeParticleTransformId, 2) + Get(RuntimeParticleTransformId, 3);
	double y4 = x_y3.x * Get(RuntimeParticleTransformId, 4) + x_y3.y * Get(RuntimeParticleTransformId, 5) + Get(RuntimeParticleTransformId, 6) + Get(RuntimeParticleTransformId, 7);
	if (particleEffects.count(int(id)) == 0) return 0;
	ParticleDataEffect effect = particleEffects[int(id)];
	effect.freshVariable();
	effect.x1 = x1, effect.y1 = y1;
	effect.x2 = x2, effect.y2 = y2;
	effect.x3 = x3, effect.y3 = y3;
	effect.x4 = x4, effect.y4 = y4;
	effect.stTime = currTime;
	effect.duration = duration;
	effect.loop = isLooped;
	activeEffects[++particleCount] = effect;
	return particleCount;
}

#endif
