#include "V3.h"
#include "V4.h"
#include <math.h>

V4 hypernormal(V4 a, V4 b, V4 c);
float distToHyperplane(V4 o, V4 d, V4 n, V4 a);
V4 bary4D(V4 p, V4 t1, V4 t2, V4 t3, V4 t4);