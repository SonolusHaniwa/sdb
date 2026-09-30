#ifndef Functions_Draw_H
#define Functions_Draw_H

double Draw(double id, Draw_Group_x_y x_y0, Draw_Group_x_y x_y1, Draw_Group_x_y x_y2, Draw_Group_x_y x_y3, double z1, double a, double z2, double z3, double z4) {
#ifdef EMSCRIPTEN
	EM_ASM({
		draw($0, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10);
	}, id, x_y0.x, x_y0.y, x_y1.x, x_y1.y, x_y2.x, x_y2.y, x_y3.x, x_y3.y, z, a);
#endif
	double x1 = x_y0.x * Get(RuntimeSkinTransformId, 0) + x_y0.y * Get(RuntimeSkinTransformId, 1) + Get(RuntimeSkinTransformId, 2) + Get(RuntimeSkinTransformId, 3);
	double y1 = x_y0.x * Get(RuntimeSkinTransformId, 4) + x_y0.y * Get(RuntimeSkinTransformId, 5) + Get(RuntimeSkinTransformId, 6) + Get(RuntimeSkinTransformId, 7);
	double x2 = x_y1.x * Get(RuntimeSkinTransformId, 0) + x_y1.y * Get(RuntimeSkinTransformId, 1) + Get(RuntimeSkinTransformId, 2) + Get(RuntimeSkinTransformId, 3);
	double y2 = x_y1.x * Get(RuntimeSkinTransformId, 4) + x_y1.y * Get(RuntimeSkinTransformId, 5) + Get(RuntimeSkinTransformId, 6) + Get(RuntimeSkinTransformId, 7);
	double x3 = x_y2.x * Get(RuntimeSkinTransformId, 0) + x_y2.y * Get(RuntimeSkinTransformId, 1) + Get(RuntimeSkinTransformId, 2) + Get(RuntimeSkinTransformId, 3);
	double y3 = x_y2.x * Get(RuntimeSkinTransformId, 4) + x_y2.y * Get(RuntimeSkinTransformId, 5) + Get(RuntimeSkinTransformId, 6) + Get(RuntimeSkinTransformId, 7);
	double x4 = x_y3.x * Get(RuntimeSkinTransformId, 0) + x_y3.y * Get(RuntimeSkinTransformId, 1) + Get(RuntimeSkinTransformId, 2) + Get(RuntimeSkinTransformId, 3);
	double y4 = x_y3.x * Get(RuntimeSkinTransformId, 4) + x_y3.y * Get(RuntimeSkinTransformId, 5) + Get(RuntimeSkinTransformId, 6) + Get(RuntimeSkinTransformId, 7);
	drawLists.push_back(DrawElement({
		int(id),
		x1, y1,
		x2, y2,
		x3, y3,
		x4, y4,
		z1,
		a
	}));
	return 0;
}

#endif
