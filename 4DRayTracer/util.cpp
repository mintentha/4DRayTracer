#include "V3.h"
#include "V4.h"
#include <math.h>
#include "util.h"


float det2(float a1, float a2, float b1, float b2) {

    return a1*b2 - a2*b1;

}

float det3(V3 a, V3 b, V3 c) {

    return a.x*(det2(b.y, b.z, c.y, c.z)) - a.y*(det2(b.x, b.z, c.x, c.z)) + a.z*(det2(b.x, b.y, c.x, c.y));

}

V3 pop(V4 a, int idx) {

    float e[3] = {};
    int j = 0;
    for (int i = 0; i < 4; i++) {
        if (i == idx) continue;
        e[j++] = a.xyzw[i];
    }

    return V3(e[0], e[1], e[2]);

}

V4 hypernormal(V4 a, V4 b, V4 c) {

    float e[4] = {};
    for (int i = 0; i < 4; i++) {
        e[i] = det3(pop(a, i), pop(b, i), pop(c, i));
    }

    return V4(e[0], -e[1], e[2], -e[3]);

}

float distToHyperplane(V4 o, V4 d, V4 n, V4 a) {

    V4 q = a - o;
    return (-q*n)/(d*n);

}

V3 sysEq3Var(V4 a, V4 b, V4 c) {

    float d = det3(pop(a, 3), pop(b, 3), pop(c, 3));
    float d1 = det3(V3(a[3], a[1], a[2]), V3(b[3], b[1], b[2]), V3(c[3], c[1], c[2]));
    float d2 = det3(V3(a[0], a[3], a[2]), V3(b[0], b[3], b[2]), V3(c[0], c[3], c[2]));
    float d3 = det3(V3(a[0], a[1], a[3]), V3(b[0], b[1], b[3]), V3(c[0], c[1], c[3]));

    if (d == 0) {
        return V3(0.0f);
    } else {
        return V3(d1/d, d2/d, d3/d);
    }

}

V4 bary4D(V4 p, V4 t1, V4 t2, V4 t3, V4 t4) {

    V4 a = V4(t2.x-t1.x, t3.x-t1.x, t4.x-t1.x, p.x-t1.x);
    V4 b = V4(t2.y-t1.y, t3.y-t1.y, t4.y-t1.y, p.y-t1.y);
    V4 c = V4(t2.z-t1.z, t3.z-t1.z, t4.z-t1.z, p.z-t1.z);

    V3 d = sysEq3Var(a, b, c);
    return V4((1 - d.x - d.y - d.z), d.x, d.y, d.z);

}