#include <stdio.h>
#include "V4.h"
#include "Material.h"
#include "Tetrahedron.h"
#include "HyperSphere.h"
#include "printTest.h"


void cmdLineTest() {

    printf("Before\n");
    V4 o = V4(0, 0, 0, 0);
    V4 dir = V4(0, 0, 1, 0);
    V4 a = V4(0, 0, 10, 0);
    V4 b = V4(0, 10, 10, 0);
    V4 c = V4(0, 10, 5, 10);
    V4 d = V4(10, 10, 20, 10);
    Material mat = Material();

    Tetrahedron tet = Tetrahedron(a, b, c, d);
    tet.material = &mat;

    V4 n = tet.getNormal();
    printf("Normal: (%f, %f, %f, %f)\n\n", n.x, n.y, n.z, n.w);

    float t = 0;
    V4 pt = tet.getIntersection(o, dir, &t);
    printf("Tetrahedron intersections:\n");
    printf("t: %f\n", t);
    if (t > 0) {
        printf("Pt: (%f, %f, %f, %f)\n\n", pt.x, pt.y, pt.z, pt.w);
    }
    else printf("No intersection\n\n");

    dir = V4(0, 0.2, 1, 0);
    pt = tet.getIntersection(o, dir, &t);
    printf("t: %f\n", t);
    if (t > 0) {
        printf("Pt: (%f, %f, %f, %f)\n\n", pt.x, pt.y, pt.z, pt.w);
    }
    else printf("No intersection\n\n");

    dir = V4(0.1, 0.2, 1, 0.1);
    pt = tet.getIntersection(o, dir, &t);
    printf("t: %f\n", t);
    if (t > 0) {
        printf("Pt: (%f, %f, %f, %f)\n\n", pt.x, pt.y, pt.z, pt.w);
    }
    else printf("No intersection\n\n");

    a = V4(0, 0, 1, 0);
    HyperSphere s = HyperSphere(a, 0.2f);
    s.material = &mat;

    printf("Hypersphere intersections:\n");
    dir = V4(0.3, 0.4, 0.3, 1);
    pt = s.getIntersection(o, dir, &t);
    printf("t: %f\n", t);
    if (t > 0) {
        printf("Pt: (%f, %f, %f, %f)\n\n", pt.x, pt.y, pt.z, pt.w);
    }
    else printf("No intersection\n\n");

    dir = V4(0, 0, 1, 0.2);
    pt = s.getIntersection(o, dir, &t);
    printf("t: %f\n", t);
    if (t > 0) {
        printf("Pt: (%f, %f, %f, %f)\n\n", pt.x, pt.y, pt.z, pt.w);
    }
    else printf("No intersection\n\n");

    dir = V4(0.05, 0.1, 1, 0.1);
    pt = s.getIntersection(o, dir, &t);
    printf("t: %f\n", t);
    if (t > 0) {
        printf("Pt: (%f, %f, %f, %f)\n\n", pt.x, pt.y, pt.z, pt.w);
    }
    else printf("No intersection\n\n");

    dir = V4(0, 0, 1, 0);
    pt = s.getIntersection(o, dir, &t);
    printf("t: %f\n", t);
    if (t > 0) {
        printf("Pt: (%f, %f, %f, %f)\n\n", pt.x, pt.y, pt.z, pt.w);
    }
    else printf("No intersection\n\n");


    return;
}