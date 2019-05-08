// problem: http://codeforces.com/contest/1083/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;

#define rep(pos, len) for(int pos=0;pos<len;pos++)
#define repp(pos, len) for(int pos=1;pos<=len;pos++)

#define INF 1987654321
#define IINF 2987654321987654321
#define MOD 1000000007

// 1-index
#define L(x) ((x)<<1)
#define R(x) (((x)<<1)+1)


inline ll madd(ll a, ll b) {
	return (a+b) % MOD;
}

inline ll mmul(ll a, ll b) {
	return (a*b) % MOD;
}

const int MAXN = 1e5 + 50;
int a[MAXN], n;

void readInput() {
	scanf("%d", &n);
	repp(i, n) scanf("%d", &a[i]);

	vector<int> v;
	repp(i, n) v.push_back(a[i]);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	repp(i, n) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;	// 1-index
}

int pl[MAXN], pr[MAXN], pos[MAXN];
void findP() {
	repp(i, n) pos[i] = 0;
	for(int i = 1; i <= n; i++) {
		pl[i] = pos[a[i]];
		pos[a[i]] = i;
	}
	repp(i, n) pos[i] = n+1;
	for(int i = n; i >= 1; i--) {
		pr[i] = pos[a[i]];
		pos[a[i]] = i;
	}
}




// Lazy Propagation
struct Node {
	ll s0, sa, sb, sab;
	ll ta, tb;
} st[4 * MAXN];

void pushUp(int id) {
	st[id].s0 = madd(st[L(id)].s0, st[R(id)].s0);
	st[id].sa = madd(st[L(id)].sa, st[R(id)].sa);
	st[id].sb = madd(st[L(id)].sb, st[R(id)].sb);
	st[id].sab = madd(st[L(id)].sab, st[R(id)].sab);
}

void buildTree(int l = 1, int r = n, int id = 1) {
	if(l == r) {
		st[id].sa = l-1;
		st[id].sb = 0;
		st[id].sab = 0;
		st[id].s0 = 1;
	} else {
		int m = (l + r) >> 1;
		buildTree(l, m, L(id));
		buildTree(m+1, r, R(id));
		pushUp(id);
	}
}

void addLazy(int id, ll ta, ll tb) {
	st[id].ta = madd(st[id].ta, ta);
	st[id].tb = madd(st[id].tb, tb);
}

void pushDown(int l, int r, int id) {
	if(st[id].ta != 0 || st[id].tb != 0) {
		st[id].sab = madd(st[id].sab, mmul(st[id].ta, st[id].sb) + mmul(st[id].sa, st[id].tb) + mmul(st[id].ta, mmul(st[id].tb, st[id].s0)));
		st[id].sa = madd(st[id].sa, mmul(st[id].s0, st[id].ta));
		st[id].sb = madd(st[id].sb, mmul(st[id].s0, st[id].tb));

		if(l < r) {
			addLazy(L(id), st[id].ta, st[id].tb);
			addLazy(R(id), st[id].ta, st[id].tb);
		}
		st[id].ta = st[id].tb = 0;
	}
}

void rangeUpdate(int x, int y, ll ta, ll tb, int l = 1, int r = n, int id = 1) {
	if(x <= l && r <= y) addLazy(id, ta, tb);
	pushDown(l, r, id);

	if(r < x || y < l) return;
	if(x <= l && r <= y) return;

	int m = (l + r) >> 1;
	rangeUpdate(x, y, ta, tb, l, m, L(id));
	rangeUpdate(x, y, ta, tb, m+1, r, R(id));
	pushUp(id);
}

ll rangeSum(int x, int y, int l = 1, int r = n, int id = 1) {
	pushDown(l, r, id);

	if(r < x || y < l) return 0;
	if(x <= l && r <= y) return st[id].sab;

	int m = (l + r) >> 1;
	return madd(rangeSum(x, y, l, m, L(id)), rangeSum(x, y, m+1, r, R(id)));
}

void printTree(int l = 1, int r = n, int id = 1) {
	printf("[%d,%d]: %lld %lld %lld\n", l, r, st[id].sa, st[id].sb, st[id].sab);
	if(l == r) return;
	int m = (l + r) >> 1;
	printTree(l, m, L(id));
	printTree(m+1, r, R(id));
}




struct Segment {
	int l, r, val;
	Segment(int l_, int r_, int val_) : l(l_), r(r_), val(val_) {}

	void print() {
		printf("[%d,%d]:%d\n", l, r, val);
	}
};

int main() {
	readInput();
	findP();
	buildTree();
	rangeUpdate(1, n, 0, -1);

	ll ans = 0;
	int lb = 0;
	vector<Segment> vl, vr;	// vector of segments: (index, value)
	for(int k = 1; k <= n; k++) {
		lb = max(lb, pl[k]);
		int cl = k;		// left bound of current segment
		while(!vl.empty() && vl.back().val <= pl[k]) {
			Segment &s = vl.back();
			rangeUpdate(s.l, s.r, s.val, 0);		// erase segment
			cl = s.l;
			vl.pop_back();
		}
		vl.push_back({cl, k, pl[k]});
		rangeUpdate(cl, k, -pl[k], 0);

		cl = k;
		while(!vr.empty() && vr.back().val >= pr[k]) {
			Segment &s = vr.back();
			rangeUpdate(s.l, s.r, 0, -s.val);
			cl = s.l;
			vr.pop_back();
		}
		vr.emplace_back(cl, k, pr[k]);
		rangeUpdate(cl, k, 0, pr[k]);
		rangeUpdate(1, n, 0, -1);

		ans = madd(ans, rangeSum(lb+1, k));
	}
	printf("%lld\n", (ans+MOD)%MOD);
}
