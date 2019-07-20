const int MAXN = 2e5 + 50;
ll tree[4*MAXN], lazy[4*MAXN];
int n;
void pushDown(int id) {
	tree[2*id] += lazy[id];
	tree[2*id+1] += lazy[id];
	lazy[2*id] += lazy[id];
	lazy[2*id+1] += lazy[id];
	lazy[id] = 0;
}

void pushUp(int id) {
	tree[id] = min(tree[2*id], tree[2*id+1]);
}

void buildTree(int *a, int l = 0, int r = n-1, int id = 1) {
	if(l == r) {
		tree[id] = a[l];
		return;
	}
	int mid = (l + r) / 2;
	buildTree(a, l, mid, 2*id);
	buildTree(a, mid+1, r, 2*id+1);
	pushUp(id);
}

void rangeUpdate(int s, int e, int val, int l = 0, int r = n-1, int id = 1) {
	if(e < l || r < s) return;
	if(s <= l && r <= e) {
		tree[id] += val;
		lazy[id] += val;
		return;
	}
	int mid = (l + r) / 2;
	pushDown(id);
	rangeUpdate(s, e, val, l, mid, 2*id);
	rangeUpdate(s, e, val, mid+1, r, 2*id+1);
	pushUp(id);
}

ll rangeMin(int s, int e, int l = 0, int r = n-1, int id = 1) {
	if(e < l || r < s) return IINF;
	if(s <= l && r <= e) return tree[id];
	int mid = (l + r) / 2;
	pushDown(id);
	ll res = min(rangeMin(s, e, l, mid, 2*id), rangeMin(s, e, mid+1, r, 2*id+1));
	pushUp(id);
	return res;
}
