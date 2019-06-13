// https://codeforces.com/problemset/problem/106/E
// source code by wRabbits_AlMag

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <memory.h>

using namespace std;

#define FOR(i, a, b) for(int i=(a), _b(b); i<_b; ++i)
#define FORD(i, b, a) for(int i=(b)-1, _a(a); i>=_a; --i)
#define SZ(a) (int)(a).size()
#define FILL(a, b) memset(a, b, sizeof(a))
#define SQR(a) ((a)*(a))

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;

template<typename T>
void Out(T res)
{
	cout << res << endl;
	exit(0);
}

double phi = 1.618033989;

int n;
int X[111], Y[111], Z[111];

double Find(double x, double y, double z)
{
	double res = 0;
	FOR(i, 0, n)
		res = max(res, SQR(x-1.*X[i])+SQR(y-1.*Y[i])+SQR(z-1.*Z[i]));
	return res;
}

double FindZ(double x, double y, double& zz)
{
	double L = -10000, R = +10000, res, C1, C2;
	int need = 3;
	FOR(i, 0, 75)
	{
		double D = (R-L)/phi;
		if (need&1) C1 = Find(x, y, L+D);
		if (need&2) C2 = Find(x, y, R-D);
		if (C1 < C2)
		{
			L = R-D, res = C1, zz = L+D;
			C2 = C1; need = 1;
		}
		else
		{
			R = L+D, res = C2, zz = R-D;
			C1 = C2; need = 2;
		}
	}
	return res;
}

double FindYZ(double x, double& yy, double& zz)
{
	double L = -10000, R = +10000, res, Z1, Z2, C1, C2;
	int need = 3;
	FOR(i, 0, 75)
	{
		double D = (R-L)/phi;
		if (need&1) C1 = FindZ(x, L+D, Z1);
		if (need&2) C2 = FindZ(x, R-D, Z2);
		if (C1 < C2)
		{
			L = R-D, res = C1, yy = L+D, zz = Z1;
			C2 = C1; need = 1;
		}
		else
		{
			R = L+D, res = C2, yy = R-D, zz = Z2;
			C1 = C2; need = 2;
		}
	}
	return res;
}

double FindXYZ(double& xx, double& yy, double& zz)
{
	double L = -10000, R = +10000, res, Y1, Z1, Y2, Z2, C1, C2;
	int need = 3;
	FOR(i, 0, 75)
	{
		double D = (R-L)/phi;
		if (need&1) C1 = FindYZ(L+D, Y1, Z1);
		if (need&2) C2 = FindYZ(R-D, Y2, Z2);
		if (C1 < C2)
		{
			L = R-D, res = C1, xx = L+D, yy = Y1, zz = Z1;
			C2 = C1; need = 1;
		}
		else
		{
			R = L+D, res = C2, xx = R-D, yy = Y2, zz = Z2;
			C1 = C2; need = 2;
		}
	}
	return res;
}

int main()
{
#ifdef ALMAG_LOCAL
	freopen("input.txt", "r", stdin);
#else
	//freopen("shooting.in", "r", stdin);
	//freopen("shooting.out", "w", stdout);
#endif

	scanf("%d", &n);
	FOR(i, 0, n) scanf("%d %d %d", X+i, Y+i, Z+i);

	double xx, yy, zz;
	double res = FindXYZ(xx, yy, zz);

	//printf("%.12lf\n", res);
	printf("%.12lf %.12lf %.12lf\n", xx, yy, zz);

	return 0;
}
