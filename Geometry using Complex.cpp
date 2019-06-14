#include <bits/stdc++.h>
using namespace std;


/********** struct point **********/
typedef complex<double> Point;
#define x real()
#define y imag()
#define PI 3.14159265358979323846

Point scale(Point p, Point o, double factor) { return o + (p-o)*factor; }
Point rotate(Point p, double a) { return p * polar(1.0, a); }
Point perp(Point p) { return {-p.y, p.x}; }
Point linearTrans(Point x, Point p, Point fp, Point q, Point fq) {
	return fp + (x-p) * (fq-fp) / (q-p);
}
double sq(Point v) { return v.x*v.x + v.y*v.y; }
double dot(Point v, Point w) { return (conj(v) * w).x; }
double cross(Point v, Point w) { return (conj(v) * w).y; }
double angle(Point v, Point w) {
	double cosA = dot(v, w) / abs(v) / abs(w);
	return acos(max(-1.0, min(1.0, cosA)));
}

double orient(Point o, Point a, Point b) { return cross(a-o, b-o); }
bool inAngle(Point p, Point o, Point a, Point b) {
	assert(orient(o, a, b) != 0);
	if(orient(o, a, b) < 0) swap(a, b);
	return orient(o, a, p) >= 0 && orient(o, b, p) <= 0;
}
double orientedAngle(Point o, Point a, Point b) {
	if(orient(o, a, b) >= 0) return angle(a-o, b-o);
	else return 2*PI - angle(a-o, b-o);
}

bool half(Point p) {
	assert(p.x != 0 || p.y != 0);
	return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<Point> &v, Point o) {
	sort(v.begin(), v.end(), [o](Point v, Point w) {
		return make_tuple(half(v-o), 0) < make_tuple(half(w-o), cross(v-o, w-o));
	});
}
// make some vector become first angle
Point branch = {/*what ever you want*/};
bool half2(Point p) {
	return cross(branch, p) < 0 || (cross(branch, p) == 0 && dot(branch, p) < 0);
}




/********** struct line ***********/
struct Line {
	Point v;	// gradient vector
	double c;	// value of y-intercept
	Line(Point v, double c) : v(v), c(c) {}
	Line(double a, double b, double c) : v({b, -a}), c(c) {}
	Line(Point p, Point q) : v(q-p), c(cross(v, p)) {}

	double side(Point p) { return cross(v, p) - c; }
	double dist(Point p) { return abs(side(p)) / abs(v); }
	double sqDist(Point p) { return side(p)*side(p) / sq(v); }
	Line perpThrough(Point p) { return {p, p + perp(v)}; }
	bool cmpProj(Point p, Point q) { return dot(v, p) < dot(v, q); }
	Line translate(Point t) { return {v, c + cross(v, t)}; }
	Line shiftLeft(double d) { return {v, c + d*abs(v)}; }
	Point proj(Point p) { return p - perp(v)*side(p)/sq(v); }
	Point refl(Point p) { return p - perp(v)*2.0*side(p)/sq(v); }
};

bool intersect(Line l1, Line l2, Point &out) {
	double d = cross(l1.v, l2.v);
	if(d == 0) return false;
	out = (l2.v * l1.c - l1.v * l2.c) / d;
	return true;
}

Line bisector(Line l1, Line l2, bool interior) {
	assert(cross(l1.v, l2.v) != 0);
	double sign = interior ? 1 : -1;
	return {l2.v/abs(l2.v) + l1.v/abs(l1.v)*sign, l2.c/abs(l2.v) + l1.c/abs(l1.v)*sign};
}




/********** segments ***********/
bool inDisk(Point p, Point a, Point b) { return dot(a-p, b-p) <= 0; }
bool onSegment(Point p, Point a, Point b) {
	return orient(p, a, b) == 0 && inDisk(p, a, b);
}

bool properInter(Point a, Point b, Point c, Point d, Point &out) {
	double oa = orient(c, d, a), ob = orient(c, d, b);
	double oc = orient(a, b, c), od = orient(a, b, d);
	if(oa*ob < 0 && oc*od < 0) {
		out = (a*ob - b*oa) / (ob-oa);
		return true;
	}
	return false;
}
struct cmpX {
	bool operator()(Point a, Point b) {
		return make_tuple(a.x, a.y) < make_tuple(b.x, b.y);
	}
};
set<Point, cmpX> inters(Point a, Point b, Point c, Point d) {
	Point out;
	if(properInter(a, b, c, d, out)) return {out};
	set<Point, cmpX> s;
	if(onSegment(a, c, d)) s.insert(a);
	if(onSegment(b, c, d)) s.insert(b);
	if(onSegment(c, a, b)) s.insert(c);
	if(onSegment(d, a, b)) s.insert(d);
	return s;
}

double pointToSeg(Point p, Point a, Point b) {
	if(a != b) {
		Line l(a, b);
		if(l.cmpProj(a, p) && l.cmpProj(p, b)) return l.dist(p);
	}
	return min(abs(p-a), abs(p-b));
}

double segToSeg(Point a, Point b, Point c, Point d) {
	Point out;
	if(properInter(a, b, c, d, out)) return 0.0;
	return min({pointToSeg(c, a, b), pointToSeg(d, a, b),
				pointToSeg(a, c, d), pointToSeg(b, c, d)});
}




/********** polygons ***********/
double areaTriangle(Point a, Point b, Point c) {
	return abs(cross(b-a, c-a)) / 2.0;
}
double areaPolygon(vector<Point> &p) {
	double area = 0.0;
	for(int i = 0, n = (int)p.size(); i < n; i++)
		area += cross(p[i], p[(i+1)%n]);
	return abs(area) / 2.0;
}
