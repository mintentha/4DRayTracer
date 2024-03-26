#include "FrameBuffer.h"
#include "PPC.h"
#include "Scene.h"
#include "Shape.h"
#include "HyperSphere.h"
#include "Material.h"
#include "V3.h"
#include "V4.h"

void main() {
	PPC *ppc = new PPC(120, 1028, 1028);
	ppc->SetPose(V3(0.0f), V3(0.0f, 0.0f, 50.0f), V3(0.0f, 1.0f, 0.0f));
	HyperSphere* hs = new HyperSphere(V4(0.0f, 0.0f, 50.0f, 0.0f), 10.0f);
	HyperSphere* hs2 = new HyperSphere(V4(0.0f, 20.0f, 50.0f, 9.0f), 10.0f);
	Material material;
	material.diffuse = V3(1.0f, 0.0f, 0.0f);
	hs->material = &material;
	hs2->material = &material;
	Scene *scene = new Scene(ppc, V3(0.0f), 1);
	FrameBuffer* fb = new FrameBuffer(1028, 1028);
	scene->AddShape(hs);
	scene->AddShape(hs2);
	scene->RenderRT(fb, 0.0f, 0.0f);
	fb->SaveAsTiff("output.tiff");
}