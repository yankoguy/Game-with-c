#include "stdafx.h"
#include <math.h>
#include <string.h>
#include <malloc.h>
double pos_or_neg(int num) {
	if (num > 0) {
		return 1.0;
	}
	return -1.0;
}


double create_shoot_angle(int x_target, int y_target, int x, int y) {
	const double PI = 3.1415926;
	double hypotenuse = sqrt(pow(x_target - x, 2) + pow(y_target - y, 2));
	return (acos((x_target - x) / hypotenuse) * 180 / PI);
}

char* concat(const char *s1, const char *s2)
{
	const size_t len1 = strlen(s1);
	const size_t len2 = strlen(s2);
	char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
											// in real code you would check for errors in malloc here
	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
	return result;
}


int get_absulute_distance(int x, int y, int target_x, int target_y) {
	float distance = 0;
	int x_dis = abs(x - target_x);
	int y_dis = abs(y - target_y);
	while (x_dis > 0 || y_dis > 0) {
		if (x_dis > 0 && y_dis > 0) {
			distance += 1.41f;
		}
		else {
			distance += 1;
		}
		x_dis -= 1;
		y_dis -= 1;
	}
	return (int)distance;
}