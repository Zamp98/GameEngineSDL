#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "ObjLoader.h"
#include <SDL.h>
#include "Matrix.h"
#define X -1
#define Y 0
#define Z 1
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 600;

using namespace std;

typedef struct position {
	float x;
	float y;
	float z;
}Position;
typedef struct speed {
	float x;
	float y;
	float z;
}Speed;


class Object {
	public:
		Position pos;
		Entity body;
		float mass;
		Speed speed;
		float sc;
		Entity shape;
		Object(Entity e) {
			shape = e;
		}
		void rotate(float degX, float degY, float degZ) {
		}
		void translate(float x, float y, float z) {

		}
		void scale(float s) {
			
		}
};

class Resolution {
	public:
		int width;
		int height;
		Resolution() {
			width = SCREEN_WIDTH;
			height = SCREEN_HEIGHT;
		}
};

class Perspective: public Position {
	public:
		float matrix[DIMENSION][DIMENSION];
		bool isSet;
		float Z0;
		Perspective() {
			int i;
			int j;
			for (i = 0; i < DIMENSION; i++)
				for (j = 0; j < DIMENSION; j++)
					matrix[i][j] = 0;
			isSet = false;
		}

		void setProjectionMatrix(const float& angleOfView, const float& near, const float& far)
		{
			// set the basic projection matrix
			Z0 = (SCREEN_WIDTH) / tan((angleOfView * 0.5) * 3.14159265 / 180.0);
			float a = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
			float q = far / (far - near);
			float fov = 1 / tan(angleOfView * 0.5 * M_PI / 180);
			matrix[0][0] = a * fov;
			matrix[1][1] = fov;
			matrix[2][2] = q;
			matrix[3][2] = (-far*near) / (far - near);
			matrix[2][3] = 1;
			matrix[3][3] = 0;
			isSet = true;
		}
};

typedef struct angle{
	float x;
	float y;
	float z;
}Angle;

class Camera{
	public:
		int fov;
		Perspective perspective;
		Position pos;
		Angle angle;
		Camera() {
			fov = 45.0;
			perspective.setProjectionMatrix(fov, 0.1, 1000);
			pos.x = pos.y = pos.z = 0.0;
			angle.x = angle.z = angle.y = 0.0;
		}
		void resetAngle() {
			//pos.x = pos.y = pos.z = 0.0;
			angle.x = angle.z = angle.y = 0.0;
		}
		void translateX(float s) {
			pos.x += s;
		}
		void translateY(float s) {
			pos.y += s;
		}
		void translateZ(float s) {
			pos.z += s;
		}
		void rotateX(float s) {
			angle.x += s;
		}
		void rotateY(float s) {
			angle.y += s;
		}
		void rotateZ(float s) {
			angle.z += s;
		}
};

class DisplayList {
	public:
		vector<Entity> objects;

		void insert(Entity object) {
			objects.push_back(object);
		}
		void removeLast(Entity object) {
			objects.pop_back();
		}
		void sort(Camera c) {
		}
	
};

DisplayList applyDelta(Camera c, DisplayList l);
DisplayList scale(float s, DisplayList l);
void renderWireframe(SDL_Renderer* gRenderer, DisplayList l);
void render(SDL_Renderer* gRenderer, DisplayList l);
DisplayList applyPerspective(DisplayList l, Perspective p);
DisplayList rotateObjects(DisplayList l, float angle, int axis);  
DisplayList translate(DisplayList l, int axis, float delta);