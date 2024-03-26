#include "V3.h"
#include "M33.h"

#include "Triangle.h"
#include "Import.h"

void main(int argc, char *argv[]) {
	std::string inputFile("../Input/cornell1.txt");
	std::string outputFile("../Output/output.tiff");
	if (argc >= 2) {
		std::cout << argv[1];
		inputFile = argv[1];
	}
	if (argc >= 3) {
		outputFile = argv[2];
	}
	Scene *scene = getSceneFromFile(inputFile.c_str());
	scene->RenderRT();
	scene->SaveAsTIFF(outputFile.c_str());
}