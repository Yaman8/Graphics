#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<gl/glut.h>
using namespace std;
class modelLoader
{
public:
	struct vertex
	{
		float x;
		float y;
		float z;
	};
	modelLoader(string filename);//Read function
	void Draw();//Drawing function
private:
	vector<vector<GLfloat>> v;//Store vertex (x,y,z) coordinates
	vector<vector<GLint>> f;//Store the three vertex indexes of the face
};

