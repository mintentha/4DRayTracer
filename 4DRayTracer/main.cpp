#include "FrameBuffer.h"
#include "PPC.h"
#include "Scene.h"
#include "Shape.h"
#include "HyperSphere.h"
#include "Tetrahedron.h"
#include "Material.h"
#include "V3.h"
#include "V4.h"
#include "printTest.h"

#include <GLFW/glfw3.h>

void main() {
    glfwInit();
}

/*
void main() {
    PPC* ppc = new PPC(120, 1028, 1028);
    ppc->SetPose(V3(0.0f), V3(0.0f, 0.0f, 50.0f), V3(0.0f, 1.0f, 0.0f));
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
    Scene* scene = new Scene(ppc, V3(0.0f), 2);
    FrameBuffer* fb = new FrameBuffer(1028, 1028);
    scene->AddShape(hs);
    scene->AddShape(hs2);
    scene->AddShape(tet);
    scene->AddShape(tet2);
    scene->AddShape(tet3);
    scene->RenderRT(fb, 0.0f, 0.0f);
    fb->SaveAsTiff("output.tiff");

    //cmdLineTest();
}
*/