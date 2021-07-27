#pragma once

#include"math.h"
#include<cmath>

void rotateY(vec3& v1 ,float angle);
vec4 matrix(vec4& v, float matrix[4][4]);

void rotateY(vec3& v1, float angle) {
	float ang = angle * 3.1456 / 180;
	float composite[4][4] = { {1,0,0,0},
							{0,cos(ang),-sin(ang),0},
							{0,sin(ang),cos(ang),0},
							{0,0,0,1}
	};
	v1.x = v1.x*cos(ang)+v1.z*sin(ang);
	v1.y = v1.y;
	v1.z = v1.z*cos(ang)-v1.x*sin(ang);

	std::cout <<v1.x<<" "<<v1.y<<" "<<v1.z <<std::endl;

}

void translate(vec3& v1, vec3& points){
	v1.x += points.x;
	v1.y += points.y;
	v1.z += points.z;
	std::cout << v1.x << " " << v1.y << " " << v1.z << std::endl;

}
//vec4 matrix_product(vec4& v, float matrix[4][4])
//{
//	vec3 temp;
//	temp.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3];
//	temp.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3];
//	temp.z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3];
//	return temp;
//}
