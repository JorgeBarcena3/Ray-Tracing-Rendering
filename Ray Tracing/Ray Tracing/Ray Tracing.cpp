// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "pch.h"
#include "Source/ImageFile.h"
#include "Source/Ray.h"
#include "Source/Camera.h"
#include "Source/Render.h"


double getRandomNumber(float max, float min) {

	return  (max - (-min)) * ((double)rand() / (double)RAND_MAX) + -min;
}

int main()
{

	ImageFile myFile;
	myFile.openImage("OutputRenders/Week6_04.ppm", "overwrite");

	const int xResolution = 600;
	const int yResolution = 300;
	const int antialsing = 100;
	
	myFile.addText("P3\n" + to_string(xResolution) + " " + to_string(yResolution) + "\n255\n");

	vector<objectToTrace*> listToTrace;
	vec3 blue(0, 0, 255);
	vec3 green(0, 255, 0);
	vec3 red(255, 0, 0);
	vec3 grey(127, 127, 127);
	vec3 floorColor(63, 122, 77);
	
//	listToTrace.push_back(new Sphere(vec3(0.f, 0.5f, -1.5f), 0.5f, blue));
	listToTrace.push_back(new Sphere(vec3(0.f, 0.2f, -1.f), 0.5f, green));
	listToTrace.push_back(new Sphere(vec3(-0.5f, 0.0f, -1.f), 0.25f, red));
	listToTrace.push_back(new Plane(vec3(0, 1, 0), vec3(0, -1, 0), floorColor, true));
	listToTrace[0]->myMaterial.reflection = 0.25;
	//listToTrace[2]->myMaterial.reflection = 0.25;

	Camera* camera = new Camera(vec3(0, 0, 0));
	Light* light = new Light(vec3(-3, 2, 5));

	Render render;
	render.objectsToTrace = listToTrace;
	render.light = light;


	for (int i = yResolution - 1; i > 0; i--)
		for (int j = 0; j < xResolution; j++) {

			vec3 currentColor;

			for (int p = 0; p < antialsing; p++) {
				
				float x = (float)(j + getRandomNumber(0.5, -0.5)) / (float)xResolution;
				float y = (float)(i + getRandomNumber(0.5, -0.5)) / (float)yResolution;
				hit_record record;
				Ray r = camera->getRay(x, y);
				currentColor += render.getColor(r, record);
			}

			currentColor /= antialsing;

			cout << 100 - ((i * 100) / yResolution) << "%" << endl;
			myFile.addText(to_string((int)currentColor.r) + " " + to_string((int)currentColor.g) + " " + to_string((int)currentColor.b) + "\n");

		}


	delete camera;
	delete light;
	for (objectToTrace* list : listToTrace)
		delete list;

	cout << "Image completed, press enter...";

}

