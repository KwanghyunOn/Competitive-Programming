// https://codeforces.com/problemset/problem/106/E

#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;
 
#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)
 
#define INF 987654321
#define IINF 2987654321987654321
#define MOD 1000000009

const double phi = (sqrt(5) + 1.0) / 2.0;
const int itnum = 80;

inline double sq(double x) {
	return x*x;
}



const int MAXN = 105;
double X[MAXN], Y[MAXN], Z[MAXN];
int n;
void readInput() {
	scanf("%d", &n);
	repp(i, n) scanf("%lf%lf%lf", &X[i], &Y[i], &Z[i]);
}



double find(double x, double y, double z) {
	double mx = 0;
	repp(i, n) mx = max(mx, sq(x - X[i]) + sq(y - Y[i]) + sq(z - Z[i]));
	return mx;
}

double findZ(double x, double y, double &zz) {
	double L = -1e4, R = 1e4, mx = 0, C1, C2;
	int bm = 3;
	rep(t, itnum) {
		double D = (R - L) / phi;
		if(bm & 1) C1 = find(x, y, R-D);
		if(bm & 2) C2 = find(x, y, L+D);
		if(C1 < C2) {
			mx = C1, zz = R-D;
			C2 = C1, bm = 1;
			R = L+D;
		} else {
			mx = C2, zz = L+D;
			C1 = C2, bm = 2;
			L = R-D;
		}
	}
	return mx;
}

double findYZ(double x, double &yy, double &zz) {
	double L = -1e4, R = 1e4, mx = 0, C1, C2, Z1, Z2;
	int bm = 3;
	rep(t, itnum) {
		double D = (R - L) / phi;
		if(bm & 1) C1 = findZ(x, R-D, Z1);
		if(bm & 2) C2 = findZ(x, L+D, Z2);
		if(C1 < C2) {
			mx = C1, zz = Z1, yy = R-D;
			C2 = C1, bm = 1;
			R = L+D;
		} else {
			mx = C2, zz = Z2, yy = L+D;
			C1 = C2, bm = 2;
			L = R-D;
		}
	}
	return mx;
}

double findXYZ(double &xx, double &yy, double &zz) {
	double L = -1e4, R = 1e4, mx = 0, C1, C2, Z1, Z2, Y1, Y2;
	int bm = 3;
	rep(t, itnum) {
		double D = (R - L) / phi;
		if(bm & 1) C1 = findYZ(R-D, Y1, Z1);
		if(bm & 2) C2 = findYZ(L+D, Y2, Z2);
		if(C1 < C2) {
			mx = C1, zz = Z1, yy = Y1, xx = R-D;
			C2 = C1, bm = 1;
			R = L+D;
		} else {
			mx = C2, zz = Z2, yy = Y2, xx = L+D;
			C1 = C2, bm = 2;
			L = R-D;
		}
	}
	return mx;
}



int main() {
	readInput();
	double xx, yy, zz;
	double mx = findXYZ(xx, yy, zz);
	printf("%.11f %.11f %.11f\n", xx, yy, zz);
}
