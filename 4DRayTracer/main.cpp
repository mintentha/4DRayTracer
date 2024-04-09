#include "PPC.h"
#include "Scene.h"
#include "RTWindow.h"
#include "Tetrahedron.h"
#include "HyperSphere.h"
#include "HyperQuad.h"
#include "defines.h"

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

void main() {
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // OpenGL verison 4.6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    PPC* ppc = new PPC(120, WIDTH, HEIGHT);
    ppc->setPose(V4(0.0f), V4(0.0f, 0.0f, 1.0f, 0.0f), V4(0.0f, 1.0f, 0.0f, 0.0f), V4(0.0f, 0.0f, 0.0f, 1.0f));
    Material material;
    material.diffuse = V3(1.0f, 0.0f, 0.0f);
    material.specular = V3(0.0f);
    PointLight* l1 = new PointLight(V4(0.0f, 35.0f, 0.0f, 0.0f), V3(1.0f), V3(1.0f));

    // -X Cube
    HyperQuad* hq1 = new HyperQuad(
        V4(-150, -150, -150, -150),
        V4(-150,  150, -150, -150),
        V4(-150, -150,  150, -150),
        V4(-150, -150, -150,  150)
    );
    Material mat1;
    mat1.diffuse = V3(1, 0, 0);
    mat1.specular = V3(0.66f, 1.0f, 0.9f);
    mat1.shininess = 1.0f;
    mat1.reflectivity = 0.0f;
    hq1->material = &mat1;

    // +X Cube
    HyperQuad* hq2 = new HyperQuad(
        V4(150, -150, -150, -150),
        V4(150, -150,  150, -150),
        V4(150,  150, -150, -150),
        V4(150, -150, -150,  150)
    );
    Material mat2;
    mat2.diffuse = V3(1, 0.8f, 0.89);
    mat2.specular = V3(0.8f, 0.8f, 1.0f);
    mat2.shininess = 907.0f;
    mat2.reflectivity = 0.0f;
    hq2->material = &mat2;

    // -Y Cube
    HyperQuad* hq3 = new HyperQuad(
        V4(-150, -150, -150, -150),
        V4(-150, -150,  150, -150),
        V4( 150, -150, -150, -150),
        V4(-150, -150, -150,  150)
    );
    Material mat3;
    mat3.diffuse = V3(0.8f, 1.0f, 1.0f);
    mat3.specular = V3(0.89f, 1.0f, 0.8f);
    mat3.shininess = 666.0f;
    mat3.reflectivity = 0.2f;
    hq3->material = &mat3;

    // +Y Cube
    HyperQuad* hq4 = new HyperQuad(
        V4(-150,  150, -150, -150),
        V4( 150,  150, -150, -150),
        V4(-150,  150,  150, -150),
        V4(-150,  150, -150,  150)
    );
    Material mat4;
    mat4.diffuse = V3(1, 0.8, 0.8);
    mat4.specular = V3(1, 0.89, 0.8);
    mat4.shininess = 777.0f;
    mat4.reflectivity = 0.15f;
    hq4->material = &mat4;

    // -Z Cube
    HyperQuad* hq5 = new HyperQuad(
        V4(-150, -150, -150, -150),
        V4( 150, -150, -150, -150),
        V4(-150,  150, -150, -150),
        V4(-150, -150, -150,  150)
    );
    Material mat5;
    mat5.diffuse = V3(1, 1, 0);
    mat5.specular = V3(1, 0, 0.5);
    mat5.shininess = 2.0f;
    mat5.reflectivity = 0.05f;
    hq5->material = &mat5;

    // +Z Cube
    HyperQuad* hq6 = new HyperQuad(
        V4(-150, -150,  150, -150),
        V4(-150,  150,  150, -150),
        V4( 150, -150,  150, -150),
        V4(-150, -150,  150,  150)
    );
    Material mat6;
    mat6.diffuse = V3(0.62, 0.62, 0.62);
    mat6.specular = V3(0.6, 0.2, 1.0f);
    mat6.shininess = 123.0f;
    mat6.reflectivity = 0.3f;
    hq6->material = &mat6;

    // -W Cube
    HyperQuad* hq7 = new HyperQuad(
        V4(-150, -150, -150, -150),
        V4(-150,  150, -150, -150),
        V4( 150, -150, -150, -150),
        V4(-150, -150,  150, -150)
    );
    Material mat7;
    mat7.diffuse = V3(0, 0.8, 0);
    mat7.specular = V3(0.8f, 0.0f, 0.0f);
    mat7.shininess = 15.0f;
    mat7.reflectivity = 0.0f;
    hq7->material = &mat7;

    // +W Cube
    HyperQuad* hq8 = new HyperQuad(
        V4(-150, -150, -150,  150),
        V4( 150, -150, -150,  150),
        V4(-150,  150, -150,  150),
        V4(-150, -150,  150,  150)
    );
    Material mat8;
    mat8.diffuse = V3(1, 1, 1);
    mat8.specular = V3(0.0f);
    mat8.shininess = 69.0f;
    mat8.reflectivity = 0.35f;
    hq8->material = &mat8;

    // HyperSpheres
    HyperSphere* hs1 = new HyperSphere(V4(-25.0f, 85.0f, 100.0f, 20.0f), 25.0f);
    Material hsMat1;
    hsMat1.diffuse = V3(0.0f, 0.0f, 1.0f);
    hsMat1.specular = V3(0.0f, 1.0f, 0.0f);
    hsMat1.shininess = 100.0f;
    hsMat1.reflectivity = 0.8f;
    hs1->material = &hsMat1;
    HyperSphere* hs2 = new HyperSphere(V4(50.0f, -25.0f, 100.0f, 10.0f), 25.0f);
    Material hsMat2;
    hsMat2.diffuse = V3(1.0f, 0.0f, 1.0f);
    hsMat2.specular = V3(1.0f, 0.5f, 0.0f);
    hsMat2.shininess = 10.0f;
    hsMat2.reflectivity = 1.0f;
    hs2->material = &hsMat2;

    Scene* scene = new Scene(V3(0.0f), V3(0.0f), 4);
    scene->AddLight(l1);
    scene->AddShape(hq1);
    scene->AddShape(hq2);
    scene->AddShape(hq3);
    scene->AddShape(hq4);
    scene->AddShape(hq5);
    scene->AddShape(hq6);
    scene->AddShape(hq7);
    scene->AddShape(hq8);
    scene->AddShape(hs1);
    scene->AddShape(hs2);
    
    // cmdLineTest();
    RTWindow* window = new RTWindow(WIDTH, HEIGHT, 0.25, RTWindow::RATIO_LOCKED, ppc, scene);
    RTWindow::ERROR error = window->hasError();
    switch (error) {
        case RTWindow::CREATE_WINDOW:
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            delete scene;
            delete ppc;
            delete window;
            return;
        case RTWindow::LOAD_GL:
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            glfwTerminate();
            delete scene;
            delete ppc;
            delete window;
            return;
    }

    int i = 0;
    while (!window->shouldClose()) {
        if (window->draw()) {
            // Writing to console is actually slow but it is helpful to know whats going on
            //std::cout << "Frame " << ++i << std::endl;
        }
    }
    glfwTerminate();
}