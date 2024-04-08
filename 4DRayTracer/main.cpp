#include "PPC.h"
#include "Scene.h"
#include "RTWindow.h"
#include "Tetrahedron.h"
#include "HyperSphere.h"
#include "HyperQuad.h"

#include "PPC.h"

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define WIDTH 300
#define HEIGHT 240

void main() {
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // OpenGL verison 4.6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    PPC* ppc = new PPC(120, WIDTH, HEIGHT);
    ppc->setPose(V4(1.0f), V4(0.0f, 0.0f, 50.0f, 0.0f), V4(0.0f, 1.0f, 0.0f, 0.0f), V4(0.0f, 0.0f, 0.0f, 1.0f));
    Material material;
    material.diffuse = V3(1.0f, 0.0f, 0.0f);
    material.specular = V3(0.3f);
    material.reflectivity = 0.05f;
    material.shininess = 5;


    // I think this is a correct hyperquad
    // Hyperquad 1
    Tetrahedron* tet1 = new Tetrahedron(V4(-50.0f, -50.0f, -50.0f, -50.0f), V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(-50.0f, -50.0f, 500.0f, -50.0f), V4(50.0f, -50.0f, -50.0f, -50.0f));
    Tetrahedron* tet2 = new Tetrahedron(V4(-50.0f, -50.0f, 500.0f, 50.0f), V4(-50.0f, -50.0f, 500.0f, -50.0f), V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(50.0f, -50.0f, 500.0f, 50.0f));
    Tetrahedron* tet3 = new Tetrahedron(V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(-50.0f, -50.0f, 500.0f, -50.0f), V4(50.0f, -50.0f, -50.0f, -50.0f), V4(50.0f, -50.0f, 500.0f, 50.0f));
    Tetrahedron* tet4 = new Tetrahedron(V4(50.0f, -50.0f, -50.0f, 50.0f), V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(50.0f, -50.0f, -50.0f, -50.0f), V4(50.0f, -50.0f, 500.0f, 50.0f));
    Tetrahedron* tet5 = new Tetrahedron(V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(50.0f, -50.0f, 500.0f, 50.0f), V4(-50.0f, -50.0f, 500.0f, -50.0f), V4(50.0f, -50.0f, 500.0f, -50.0f));

    Material material2;
    material2.diffuse = V3(1.0f, 1.0f, 0.0f);
    material2.specular = V3(0.0f);
    material2.reflectivity = 0.05f;
    material2.shininess = 0;

    // Hyperquad 2
    Tetrahedron* tet6 = new Tetrahedron(V4(-50.0f, -50.0f, -50.0f, -50.0f), V4(-50.0f, -50.0f, 500.0f, -50.0f), V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(-50.0f, 50.0f, -50.0f, -50.0f));
    Tetrahedron* tet7 = new Tetrahedron(V4(-50.0f, -50.0f, 500.0f, 50.0f), V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(-50.0f, -50.0f, 500.0f, -50.0f), V4(-50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet8 = new Tetrahedron(V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(-50.0f, 50.0f, -50.0f, -50.0f), V4(-50.0f, -50.0f, 500.0f, -50.0f), V4(-50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet9 = new Tetrahedron(V4(-50.0f, 50.0f, -50.0f, 50.0f), V4(-50.0f, 50.0f, -50.0f, -50.0f), V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(-50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet10 = new Tetrahedron(V4(-50.0f, -50.0f, 500.0f, -50.0f), V4(-50.0f, 50.0f, 500.0f, 50.0f), V4(-50.0f, -50.0f, -50.0f, 50.0f), V4(-50.0f, 50.0f, 500.0f, -50.0f));

    Material material3;
    material3.diffuse = V3(1.0f, 0.0f, 1.0f);
    material3.specular = V3(0.8f);
    material3.reflectivity = 0.5f;
    material3.shininess = 20;

    // Hyperquad 3
    Tetrahedron* tet11 = new Tetrahedron(V4(50.0f, -50.0f, -50.0f, -50.0f), V4(50.0f, -50.0f, -50.0f, 50.0f), V4(50.0f, -50.0f, 500.0f, -50.0f), V4(50.0f, 50.0f, -50.0f, -50.0f));
    Tetrahedron* tet12 = new Tetrahedron(V4(50.0f, -50.0f, 500.0f, 50.0f), V4(50.0f, -50.0f, 500.0f, -50.0f), V4(50.0f, -50.0f, -50.0f, 50.0f), V4(50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet13 = new Tetrahedron(V4(50.0f, -50.0f, -50.0f, 50.0f), V4(50.0f, -50.0f, 500.0f, -50.0f), V4(50.0f, 50.0f, -50.0f, -50.0f), V4(50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet14 = new Tetrahedron(V4(50.0f, 50.0f, -50.0f, 50.0f), V4(50.0f, -50.0f, -50.0f, 50.0f), V4(50.0f, 50.0f, -50.0f, -50.0f), V4(50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet15 = new Tetrahedron(V4(50.0f, -50.0f, -50.0f, 50.0f), V4(50.0f, 50.0f, 500.0f, 50.0f), V4(50.0f, -50.0f, 500.0f, -50.0f), V4(50.0f, 50.0f, 500.0f, -50.0f));

    Material material4;
    material4.diffuse = V3(0.0f, 0.0f, 1.0f);
    material4.specular = V3(0.3f);
    material4.reflectivity = 0.0f;
    material4.shininess = 200;

    // Hyperquad 4
    Tetrahedron* tet16 = new Tetrahedron(V4(-50.0f, 50.0f, -50.0f, -50.0f), V4(-50.0f, 50.0f, 500.0f, -50.0f), V4(-50.0f, 50.0f, -50.0f, 50.0f), V4(50.0f, 50.0f, -50.0f, -50.0f));
    Tetrahedron* tet17 = new Tetrahedron(V4(-50.0f, 50.0f, 500.0f, 50.0f), V4(-50.0f, 50.0f, -50.0f, 50.0f), V4(-50.0f, 50.0f, 500.0f, -50.0f), V4(50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet18 = new Tetrahedron(V4(-50.0f, 50.0f, -50.0f, 50.0f), V4(50.0f, 50.0f, -50.0f, -50.0f), V4(-50.0f, 50.0f, 500.0f, -50.0f), V4(50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet19 = new Tetrahedron(V4(50.0f, 50.0f, -50.0f, 50.0f), V4(50.0f, 50.0f, -50.0f, -50.0f), V4(-50.0f, 50.0f, -50.0f, 50.0f), V4(50.0f, 50.0f, 500.0f, 50.0f));
    Tetrahedron* tet20 = new Tetrahedron(V4(-50.0f, 50.0f, 500.0f, -50.0f), V4(50.0f, 50.0f, 500.0f, 50.0f), V4(-50.0f, 50.0f, -50.0f, 50.0f), V4(50.0f, 50.0f, 500.0f, -50.0f));


    V4 n = tet16->getNormal();
    std::cout << "(" << n.x << ", " << n.y << ", " << n.z << ", " << n.w << ")\n";
    n = tet17->getNormal();
    std::cout << "(" << n.x << ", " << n.y << ", " << n.z << ", " << n.w << ")\n";
    n = tet18->getNormal();
    std::cout << "(" << n.x << ", " << n.y << ", " << n.z << ", " << n.w << ")\n";
    n = tet19->getNormal();
    std::cout << "(" << n.x << ", " << n.y << ", " << n.z << ", " << n.w << ")\n";
    n = tet20->getNormal();
    std::cout << "(" << n.x << ", " << n.y << ", " << n.z << ", " << n.w << ")\n";


    HyperSphere* hs1 = new HyperSphere(V4(0.0f, 20.0f, 25.0f, 1.0f), 10.0f);
    HyperSphere* hs2 = new HyperSphere(V4(-10.0f, 0.0f, 15.0f, 0.0f), 8.0f);

    PointLight* l1 = new PointLight(V4(25.0f, 40.0f, 5.0f, 1.0f), V3(1.0f), V3(1.0f));

    tet1->material = &material;
    tet2->material = &material;
    tet3->material = &material;
    tet4->material = &material;
    tet5->material = &material;

    tet6->material = &material2;
    tet7->material = &material2;
    tet8->material = &material2;
    tet9->material = &material2;
    tet10->material = &material2;

    tet11->material = &material3;
    tet12->material = &material3;
    tet13->material = &material3;
    tet14->material = &material3;
    tet15->material = &material3;

    tet16->material = &material4;
    tet17->material = &material4;
    tet18->material = &material4;
    tet19->material = &material4;
    tet20->material = &material4;

    hs1->material = &material;
    hs2->material = &material3;
    Scene* scene = new Scene(V3(0.0f), V3(0.0f), 14);
    scene->AddLight(l1);

    scene->AddShape(hs1);
    scene->AddShape(hs2);

    scene->AddShape(tet1);
    scene->AddShape(tet2);
    scene->AddShape(tet3);
    scene->AddShape(tet4);
    scene->AddShape(tet5);

    scene->AddShape(tet6);
    scene->AddShape(tet7);
    scene->AddShape(tet8);
    scene->AddShape(tet9);
    scene->AddShape(tet10);
    
    scene->AddShape(tet11);
    scene->AddShape(tet12);
    scene->AddShape(tet13);
    scene->AddShape(tet14);
    scene->AddShape(tet15);
    
    scene->AddShape(tet16);
    scene->AddShape(tet17);
    scene->AddShape(tet18);
    scene->AddShape(tet19);
    scene->AddShape(tet20);

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