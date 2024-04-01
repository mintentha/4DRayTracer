#include "PPC.h"
#include "Scene.h"
#include "RTWindow.h"
#include "Tetrahedron.h"
#include "HyperSphere.h"

#include "PPC.h"

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define WIDTH 200
#define HEIGHT 140

void main() {
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // OpenGL verison 4.6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    PPC* ppc = new PPC(120, WIDTH, HEIGHT);
    ppc->setPose(V4(0.0f), V4(0.0f, 0.0f, 50.0f, 0.0f), V4(0.0f, 1.0f, 0.0f, 0.0f), V4(0.0f, 0.0f, 0.0f, 1.0f));
    Material material;
    material.diffuse = V3(1.0f, 0.0f, 0.0f);
    HyperSphere* hs = new HyperSphere(V4(0.0f, 0.0f, 50.0f, 0.0f), 10.0f);
    HyperSphere* hs2 = new HyperSphere(V4(0.0f, 20.0f, 50.0f, 9.0f), 10.0f);
    Tetrahedron* tet = new Tetrahedron(V4(20.0f, 0.0f, 50.0f, 0.0f), V4(20.0f, 4.0f, 50.0f, -10.0f), V4(20.0f, 4.0f, 40.0f, 10.0f), V4(24.0f, 4.0f, 40.0f, 10.0f));
    Tetrahedron* tet2 = new Tetrahedron(V4(25.0f, -40.0f, 50.0f, 10.0f), V4(50.0f, -20.0f, 50.0f, -1.0f), V4(20.0f, -30.0f, 40.0f, -10.0f), V4(24.0f, -40.0f, 40.0f, -10.0f));
    Tetrahedron* tet3 = new Tetrahedron(V4(-18.0f, 7.0f, 50.0f, -10.0f), V4(-18.0f, 30.0f, 50.0f, -10.0f), V4(-35.0f, 24.0f, 40.0f, 10.0f), V4(-30.0f, 14.0f, 40.0f, 10.0f));

    tet->material = &material;
    tet2->material = &material;
    tet3->material = &material;
    hs->material = &material;
    hs2->material = &material;
    Scene* scene = new Scene(V3(0.0f), 2);
    scene->AddShape(hs);
    scene->AddShape(hs2);
    scene->AddShape(tet);
    scene->AddShape(tet2);
    scene->AddShape(tet3);
    // cmdLineTest();
    RTWindow* window = new RTWindow(WIDTH, HEIGHT, 1, RTWindow::TRUE, ppc, scene);
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

    // We are actually fully capable of running multiple instances
    // of our raytracer simultaneously bc of how we abstracted it
    // and they keyboard controls are separate for each of them
    /*
    PPC* ppc2 = new PPC(120, WIDTH, HEIGHT);
    ppc2->SetPose(V3(0.0f), V3(0.0f, 0.0f, 50.0f), V3(0.0f, 1.0f, 0.0f));
    RTWindow* window2 = new RTWindow(WIDTH, HEIGHT, ppc2, scene);
    */

    int i = 0;
    while (!window->shouldClose()) {
        window->ppc->updateC();
        window->draw();

        //window2->draw();
        
        // Writing to console is actually slow but it is helpful to know whats going on
        std::cout << "\rFrame " << ++i << "\n" << std::flush;
    }
    glfwTerminate();
}