#ifndef Functions_Print_H
#define Functions_Print_H

double Print(double value, double format, double decimalPlaces, double anchorX, double anchorY, double pivotX, double pivotY, double width, double height, double rotation, double color, double alpha, double horizontalAlign, double background) {
	cerr << "\e[31mCalled not implemented function \"Print(";
	cerr << "value: " << value;
	cerr << ", " << "format: " << format;
	cerr << ", " << "decimalPlaces: " << decimalPlaces;
	cerr << ", " << "anchorX: " << anchorX;
	cerr << ", " << "anchorY: " << anchorY;
	cerr << ", " << "pivotX: " << pivotX;
	cerr << ", " << "pivotY: " << pivotY;
	cerr << ", " << "width: " << width;
	cerr << ", " << "height: " << height;
	cerr << ", " << "rotation: " << rotation;
	cerr << ", " << "color: " << color;
	cerr << ", " << "alpha: " << alpha;
	cerr << ", " << "horizontalAlign: " << horizontalAlign;
	cerr << ", " << "background: " << background;
	cerr << ")\"!\e[0m" << endl;
	return 0;
}

#endif
