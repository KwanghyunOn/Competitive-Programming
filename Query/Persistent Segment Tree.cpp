const int MAXN = 1e6 + 50;
const int LOGN = 20;

int root[MAXN], NEXT_FREE_INDEX = 0;
struct Node {
	int sum, left, right;
} tree[2*MAXN + MAXQ*(LOGN+1)];

int buildTree(int l, int r, int *z) {
	int id = ++NEXT_FREE_INDEX;
	if(l == r) {
		tree[id] = {z[l], 0, 0};
		return id;
	}
	int mid = (l + r) >> 1;
	int L = buildTree(l, mid, z), R = buildTree(mid+1, r, z);
	tree[id] = {tree[L].sum + tree[R].sum, L, R};
	return id;
}

int updateTree(int x, int val, int prev, int l = 1, int r = n) {
	if(x < l || r < x) return prev;
	int id = ++NEXT_FREE_INDEX;
	if(l == r) {
		tree[id] = {val, 0, 0};
		return id;
	}
	int mid = (l + r) >> 1;
	int L = updateTree(x, val, tree[prev].left, l, mid);
	int R = updateTree(x, val, tree[prev].right, mid+1, r);
	tree[id] = {tree[L].sum + tree[R].sum, L, R};
	return id;
}

int rangeSum(int x, int y, int id, int l = 1, int r = n) {
	if(y < l || r < x) return 0;
	if(x <= l && r <= y) return tree[id].sum;
	int mid = (l + r) >> 1;
	return rangeSum(x, y, tree[id].left, l, mid) + rangeSum(x, y, tree[id].right, mid+1, r);
}
