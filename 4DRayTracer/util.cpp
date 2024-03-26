#include "V3.h"
#include "V4.h"
#include <math.h>


float det2(float a1, float a2, float b1, float b2) {

    return a1*b2 - a2*b1;

}

float det3(V3 a, V3 b, V3 c) {

    return a.x*(det2(b.y, b.z, c.y, c.z)) - a.y*(det2(b.x, b.z, c.x, c.z) + a.z*(det2(b.x, b.y, c.x, c.y)));

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

float distToHypersphere(V4 o, V4 d, V4 c, float r) {

	float a = d.x * d.x + d.y * d.y + d.z * d.z + d.w * d.w;
	float b = 2 * (d.x * (o.x - c.x) + d.y * (o.y - c.y) + d.z * (o.z - c.z) + d.w * (o.w - c.w));
	float cc = (o.x - c.x) * (o.x - c.x) + (o.y - c.y) * (o.y - c.y) + (o.z - c.z) * (o.z - c.z) + (o.w - c.w) * (o.w - c.w) - (r * r);
	float disc = b * b - 4 * a * cc;

    if (disc < 0) {
        return NULL;
    }
    else if (disc == 0) {
        if (-b < 0) return NULL;
        else return -b;
    }
    else {
        float t1 = (-b + sqrt(disc)) / (2 * a);
		float t2 = (-b - sqrt(disc)) / (2 * a);

        if (t1 > t2 && t1 > 0) return t1;
        else if (t2 > t1 && t2 > 0) return t2;
    }

}