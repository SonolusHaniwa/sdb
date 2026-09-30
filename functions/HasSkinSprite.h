#ifndef Functions_HasSkinSprite_H
#define Functions_HasSkinSprite_H

double HasSkinSprite(double id) {
	return textures.count(int(id));
}

#endif
