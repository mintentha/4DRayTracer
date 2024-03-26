#include "Import.h"
#include "Scene.h"
#include "V3.h"
#include "PointLight.h"
#include "Shape.h"
#include "Sphere.h"
#include "Quad.h"
#include "Triangle.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Scene *getSceneFromFile(const char* filename) {
	size_t antialias = 0;
	V3 bgrCol(0.0f);
	V3 ambientCol(0.0f);
	size_t maxDepth = 0;
	int w = 0;
	int h = 0;
	int hfov = 0;
	V3 ppcPos = V3(0.0f);
	V3 ppcLAP = V3(0.0f);
	V3 ppcUp = V3(0.0f, 1.0f, 0.0f);
	std::vector<PointLight *> *lights = new std::vector<PointLight *>();
	std::vector<Shape *> *shapes = new std::vector<Shape *>();


	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "Failed To Open File" << std::endl;
		return nullptr;
	}
	std::string str;
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		iss >> str;
		if (str == "ANTIALIAS") {
			iss >> antialias;
			continue;
		}
		if (str == "BACKGROUND") {
			iss >> bgrCol;
			continue;
		}
		if (str == "AMBIENT") {
			iss >> ambientCol;
			continue;
		}
		if (str == "MAXDEPTH") {
			iss >> maxDepth;
			continue;
		}
		if (str == "LIGHT") {
			V3 pos(0.0f);
			V3 diff(0.0f);
			V3 spec(0.0f);
			for (size_t i = 0; i < 4; i++) {
				std::getline(file, line);
				std::istringstream iss2(line);
				iss2 >> str;
				if (str == "POS") {
					iss2 >> pos;
					continue;
				}
				if (str == "DIFF") {
					iss2 >> diff;
					continue;
				}
				if (str == "SPEC") {
					iss2 >> spec;
					continue;
				}
			}
			lights->push_back(new PointLight(pos, diff, spec));
		}
		if (str == "SPHERE") {
			V3 pos(0.0f);
			float r = 0.0f;
			V3 diff(0.0f);
			V3 spec(0.0f);
			float shininess = 0.0f;
			float reflectivity = 0.0f;
			for (size_t i = 0; i < 5; i++) {
				std::getline(file, line);
				std::istringstream iss2(line);
				iss2 >> str;
				if (str == "POS") {
					iss2 >> pos;
					iss2 >> str;
					if (str == "RADIUS") {
						iss2 >> r;
					}
					continue;
				}
				if (str == "REF") {
					iss2 >> reflectivity;
					continue;
				}
				if (str == "DIFF") {
					iss2 >> diff;
					continue;
				}
				if (str == "SPEC") {
					iss2 >> spec;
					continue;
				}
				if (str == "SHININESS") {
					iss2 >> shininess;
					continue;
				}
			}
			shapes->push_back(new Sphere(pos, r, diff, spec, shininess, reflectivity));
			continue;
		}
		if (str == "QUAD") {
			size_t curPoint = 0;
			V3 abc[3];
			V3 diff;
			V3 spec;
			float shininess = 0.0f;
			float reflectivity = 0.0f;
			for (size_t i = 0; i < 7; i++) {
				std::getline(file, line);
				std::istringstream iss2(line);
				iss2 >> str;
				if (str == "POS") {
					iss2 >> abc[curPoint++];
					continue;
				}
				if (str == "REF") {
					iss2 >> reflectivity;
					continue;
				}
				if (str == "DIFF") {
					iss2 >> diff;
					continue;
				}
				if (str == "SPEC") {
					iss2 >> spec;
					continue;
				}
				if (str == "SHININESS") {
					iss2 >> shininess;
					continue;
				}
			}
			shapes->push_back(new Quad(abc[0], abc[1], abc[2], diff, spec, shininess, reflectivity));
			continue;
		}
		if (str == "TRIANGLE") {
			size_t curPoint = 0;
			V3 abc[3];
			V3 diff;
			V3 spec;
			float shininess = 0.0f;
			float reflectivity = 0.0f;
			for (size_t i = 0; i < 7; i++) {
				std::getline(file, line);
				std::istringstream iss2(line);
				iss2 >> str;
				if (str == "POS") {
					iss2 >> abc[curPoint++];
					continue;
				}
				if (str == "REF") {
					iss2 >> reflectivity;
					continue;
				}
				if (str == "DIFF") {
					iss2 >> diff;
					continue;
				}
				if (str == "SPEC") {
					iss2 >> spec;
					continue;
				}
				if (str == "SHININESS") {
					iss2 >> shininess;
					continue;
				}
			}
			shapes->push_back(new Triangle(abc[0], abc[1], abc[2], diff, spec, shininess, reflectivity));
			continue;
		}
		if (str == "CAMERA") {
			for (size_t i = 0; i < 4; i++) {
				std::getline(file, line);
				std::istringstream iss2(line);
				iss2 >> str;
				if (str == "POS") {
					iss2 >> ppcPos;
					continue;
				}
				if (str == "LAP") {
					iss2 >> ppcLAP;
					continue;
				}
				if (str == "UP") {
					iss2 >> ppcUp;
				}
				if (str == "FOV") {
					iss2 >> hfov;
					continue;
				}
			}
		}
		if (str == "RESOLUTION") {
			iss >> w >> h;
		}
	}
	/*for (size_t i = 0; i < shapes->size(); i++) {
		std::cout << *(shapes->at(i)) << std::endl;
	}*/
	FrameBuffer* fb = new FrameBuffer(w, h);
	PPC *ppc = new PPC(hfov, w, h);
	ppc->SetPose(ppcPos, ppcLAP, ppcUp);
	return new Scene(fb, ppc, ambientCol, bgrCol, maxDepth, shapes, lights);
}