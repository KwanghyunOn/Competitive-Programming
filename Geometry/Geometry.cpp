#include <bits/stdc++.h>
using namespace std;

template <typename T> int sgn(T x) {
	return (T(0) < x) - (x < T(0));
}



/********** struct point **********/
typedef complex<double> Point;
#define x real()
#define y imag()
#define M_PI 3.14159265358979323846

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

double ccw(Point a, Point b, Point o) { return cross(a-o, b-o); }
bool inAngle(Point p, Point a, Point b, Point o) {
	assert(ccw(a, b, o) != 0);
	if(ccw(a, b, o) < 0) swap(a, b);
	return ccw(a, p, o) >= 0 && ccw(b, p, o) <= 0;
}
double orientedAngle(Point o, Point a, Point b) {
	if(ccw(a, b, o) >= 0) return angle(a-o, b-o);
	else return 2*M_PI - angle(a-o, b-o);
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

bool lineAndLine(Line l1, Line l2, Point &out) {
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
	return ccw(a, b, p) == 0 && inDisk(p, a, b);
}

bool properInter(Point a, Point b, Point c, Point d, Point &out) {
	double oa = ccw(c, d, a), ob = ccw(c, d, b);
	double oc = ccw(a, b, c), od = ccw(a, b, d);
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
set<Point, cmpX> segAndSeg(Point a, Point b, Point c, Point d) {
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

// cutting-ray test
bool above(Point a, Point p) {
	return p.y >= a.y;
}
bool crossesRay(Point a, Point p, Point q) {
	return (above(a, q) - above(a, p)) * ccw(p, q, a) > 0;
}
// if strict, returns false when A is on the boundary
bool inPolygon(vector<Point> &p, Point a, bool strict = true) {
	int crossNum = 0;
	for(int i = 0, n = (int)p.size(); i < n; i++) {
		if(onSegment(a, p[i], p[(i+1)%n]))
			return !strict;
		if(crossesRay(a, p[i], p[(i+1)%n])) crossNum++;
	}
	return crossNum & 1;
}

// another method is using winding number
double angleTravelled(Point a, Point p, Point q) {
	return (ccw(p, q, a) > 0) ? angle(p-a, q-a) : -angle(p-a, q-a);
}
int windingNumber(vector<Point> &p, Point a) {
	double ampli = 0;
	for(int i = 0, n = (int)p.size(); i < n; i++)
		ampli += angleTravelled(a, p[i], p[(i+1)%n]);
	return round(ampli / (2*M_PI));
}

// finding convex hull
vector<Point> convexHull(vector<Point> p) {
	sort(p.begin(), p.end(), [](Point a, Point b) {
		return make_tuple(a.x, a.y) < make_tuple(b.x, b.y);
	});
	vector<Point> hull;
	hull.reserve(p.size() + 1);
	for(int phase = 0; phase < 2; phase++) {
		auto start = hull.size();
		for(auto v : p) {
			while(hull.size() >= start+2 && ccw(v, hull.back(), hull[hull.size()-2]) <= 0)
				hull.pop_back();
			hull.push_back(v);
		}
		hull.pop_back();
		reverse(p.begin(), p.end());
	}
	if(hull.size() == 2 && hull[0] == hull[1]) hull.pop_back();
	return hull;
}




/********** circles ***********/
Point circumCenter(Point a, Point b, Point c) {
	b = b-a, c = c-a;
	assert(cross(b, c) != 0);
	return a + perp(b*sq(c) - c*sq(b)) / (2.0 * cross(b, c));
}

int circleAndLine(Point o, double r, Line l, pair<Point, Point> &out) {
	double h2 = r*r - l.sqDist(o);
	if(h2 >= 0.0) {
		Point p = l.proj(o);
		Point h = l.v*sqrt(h2)/abs(l.v);
		out = {p-h, p+h};
	}
	return 1 + sgn(h2);
}

int circleAndCircle(Point o1, double r1, Point o2, double r2, pair<Point, Point> &out) {
	Point d = o2-o1;
	double d2 = sq(d);
	if(d2 == 0.0) { assert(r1 != r2); return 0; }
	double pd = (d2 + r1*r1 - r2*r2) / 2.0;
	double h2 = r1*r1 - pd*pd/d2;
	if(h2 >= 0) {
		Point p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
		out = {p-h, p+h};
	}
	return 1 + sgn(h2);
}

// inner, outer tangents of two circles
// can find tangent from a point by setting r2 to 0
int tangents(Point o1, double r1, Point o2, double r2, bool inner, vector<pair<Point, Point>> &out) {
	if(inner) r2 = -r2;
	Point d = o2-o1;
	double dr = r1-r2, d2 = sq(d), h2 = d2 - dr*dr;
	if(d2 == 0.0 || h2 < 0.0) { assert(h2 != 0); return 0; }
	for(double sign : {-1.0, 1.0}) {
		Point v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
		out.push_back({o1 + v*r1, o2 + v*r2});
	}
	return 1 + (h2 > 0.0);
}
