#ifndef Functions_SetPowerShifted_H
#define Functions_SetPowerShifted_H

double SetPowerShifted(double id, double x, double y, double s, double value) {
	return SetPower(id, x + y * s, value);
}

#endif
