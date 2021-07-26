#pragma once

#include"math.h"
#include<cmath>

void rotateX(vec3& v1 ,float angle);
void matrix(vec3& v, float matrix[4][4]);

void rotateX(vec3& v1, float angle) {
	float ang = angle * 3.1456 / 180;
	float composite[4][4] = { {1,0,0,0},
							{0,cos(ang),-sin(ang),0},
							{0,sin(ang),cos(ang),0},
							{0,0,0,1}
	};
	matrix(v1, composite);

}

void matrix_product(vec3& v, float matrix[4][4])
{
	vec3 temp;
	temp.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3];
	temp.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3];
	temp.z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3];
	v = std::move(temp);
}
