#pragma once

#include"math.h"
#include"Coord.h"
#include<cmath>


void rotateY(Point& v1 ,float angle);
void rotateX(Point& v1, float angle);
void matrix_product(Point& v, float matrix[4][4]);
Point GetNormal(Point v0, Point v1, Point v2);
float dot(Point a, Point b);
Point cross(Point a, Point b);
Point normalize(Point in);
Point mul(mat4f matrix, Point& p);
float deg_to_radians(float a);

float deg_to_radians(float a) {
	return float(a * 3.1456 / 180);
}

//Point normalize(Point in) {
//	float temp = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
//	return Point(in * 1 / temp);
//}

void matrix_product(Point& p, float matrix[4][4])
{
	Point temp;
	temp.x = matrix[0][0] * p.x + matrix[0][1] * p.y + matrix[0][2] * p.z + matrix[0][3];
	temp.y = matrix[1][0] * p.x + matrix[1][1] * p.y + matrix[1][2] * p.z + matrix[1][3];
	temp.z = matrix[2][0] * p.x + matrix[2][1] * p.y + matrix[2][2] * p.z + matrix[2][3];
	p = std::move(temp);
}

float dot(Point a, Point b) {
	float c = a.x * b.x + a.y * b.y + a.z * b.z;
	return c;
}

Point GetNormal(Point v0, Point v1, Point v2) {
	Point a, b;
	a.x = v0.x - v1.x;
	a.y = v0.y - v1.y;
	a.z = v0.z - v1.z;
	b.x = v0.x - v2.x;
	b.y = v0.y - v2.y;
	b.z = v0.z - v2.z;
	Point ret;
	ret.x = a.y * b.z - b.y * a.z;
	ret.y = b.x * a.z - a.x * b.z;
	ret.z = a.x * b.y - b.x * a.y;

	std::cout << ret.x << " " << ret.y << " " << ret.z << std::endl;
	return ret;

}

Point cross(Point a, Point b) {
	Point ret;
	ret.x = a.y * b.z - b.y * a.z;
	ret.y = b.x * a.z - a.x * b.z;
	ret.z = a.x * b.y - b.x * a.y;
	return ret;
}


void rotateY(Point& v1, float angle) {
	float ang = angle * 3.1456 / 180;
	float composite[4][4] = { {1,0,0,0},
							{0,cos(ang),-sin(ang),0},
							{0,sin(ang),cos(ang),0},
							{0,0,0,1}
	};
	v1.x = v1.x*cos(ang)+v1.z*sin(ang);
	v1.y = v1.y;
	v1.z = v1.z*cos(ang)-v1.x*sin(ang);

	//std::cout <<v1.x<<" "<<v1.y<<" "<<v1.z <<std::endl;

}

void rotateX(Point& v1, float angle) {
	float ang = angle * 3.1456 / 180;
	float composite[4][4] = { {1,0,0,0},
							{0,cos(ang),-sin(ang),0},
							{0,sin(ang),cos(ang),0},
							{0,0,0,1}
	};
	v1.x = v1.x;
	v1.y = v1.y * cos(ang) - v1.z * sin(ang);
	v1.z = v1.y * sin(ang) + v1.z * cos(ang);

	//std::cout << v1.x << " " << v1.y << " " << v1.z << std::endl;

}

void translate(Point& v1, Point& points){
	v1.x += points.x;
	v1.y += points.y;
	v1.z += points.z;
	//std::cout << v1.x << " " << v1.y << " " << v1.z << std::endl;

}

vec3 mul(mat4f matrix, vec3& p){
	// float homogenous_b[] = {b[0], b[1], b[2], 1};
	vec3 temp;
	temp.x = matrix.matrix4[0][0] * p.x + matrix.matrix4[0][1] * p.y + matrix.matrix4[0][2] * p.z + matrix.matrix4[0][3];
	temp.y = matrix.matrix4[1][0] * p.x + matrix.matrix4[1][1] * p.y + matrix.matrix4[1][2] * p.z + matrix.matrix4[1][3];
	temp.z = matrix.matrix4[2][0] * p.x + matrix.matrix4[2][1] * p.y + matrix.matrix4[2][2] * p.z + matrix.matrix4[2][3];
	//temp.w = p.w;
	return temp;
}



void transate_polygon(Point& pt, Point translate)
{
	pt = pt + translate;
}

void scale_polygon(Point& pt, Point scale)
{

	pt = pt.scaleProduct(scale);
}