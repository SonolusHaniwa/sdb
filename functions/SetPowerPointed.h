#ifndef Functions_SetPowerPointed_H
#define Functions_SetPowerPointed_H

double SetPowerPointed(double id, double index, double offset, double value) {
	return SetPower(Get(id, index), Get(id, index + 1) + offset, value);
}

#endif
