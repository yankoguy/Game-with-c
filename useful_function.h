#ifndef USEFUL_FUNCTIONS_H
#define USEFUL_FUNCTIONS_H

double pos_or_neg(int num);
double create_shoot_angle(int x_target, int y_target, int x, int y);
char* concat(const char *s1, const char *s2);
int get_absulute_distance(int x, int y, int target_x, int target_y);
#endif