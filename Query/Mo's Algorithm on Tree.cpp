int pa[MAXN][LOGN], depth[MAXN];
int tin[MAXN], tout[MAXN], f[2*MAXN], CUR_TIME = 0;
void dfs(int v, int p) {
	tin[v] = ++CUR_TIME;
	f[CUR_TIME] = v;
	for(auto c : adj[v]) if(c != p) {
		pa[c][0] = v;
		depth[c] = depth[v] + 1;
		dfs(c, v);
	}
	tout[v] = ++CUR_TIME;
	f[CUR_TIME] = v;
}

void preprocess() {
	dfs(1, -1);
	pa[1][0] = 1;
	for(int x = 1; x < LOGN; x++)
		for(int v = 1; v <= n; v++)
			pa[v][x] = pa[pa[v][x-1]][x-1];
}

int lca(int u, int v) {
	if(depth[u] > depth[v]) swap(u, v);
	int d = depth[v] - depth[u];
	for(int x = 0; x < LOGN; x++)
		if(d & (1<<x)) v = pa[v][x];
	if(u == v) return u;
	for(int x = LOGN-1; x >= 0; x--)
		if(pa[u][x] != pa[v][x]) u = pa[u][x], v = pa[v][x];
	return pa[u][0];
}


int cnt[MAXN], sz;
bool flag[MAXN];
void update(int i) {
	if(i == 0) return;
	if(!flag[f[i]]) {
		cnt[a[f[i]]]++;
		if(cnt[a[f[i]]] == 1) sz++;
	} else {
		cnt[a[f[i]]]--;
		if(cnt[a[f[i]]] == 0) sz--;
	}
	flag[f[i]] = !flag[f[i]];
}


struct Query {
	int l, r, p, id;
};

vector<Query> qlist;
int ans[MAXM];
void solve() {
	repp(i, m) {
		int u = q[i].first, v = q[i].second;
		if(u == v) {
			ans[i] = 1;
			continue;
		}
		int p = lca(u, v);
		if(tin[u] > tin[v]) swap(u, v);
		qlist.push_back({tout[u], tin[v], p, i});
	}
	int rt = 0;
	while(rt*rt < n) rt++;
	sort(qlist.begin(), qlist.end(), [rt](const Query &a, const Query &b) {
		return make_tuple(a.l/rt, a.r) < make_tuple(b.l/rt, b.r);
	});
	
	int cl = 0, cr = 0;
	for(auto t : qlist) {
		int l = t.l, r = t.r, p = t.p, id = t.id;
		if(l < cl) for(int i = cl-1; i >= l; i--) update(i);
		if(cr < r) for(int i = cr+1; i <= r; i++) update(i);
		if(cl < l) for(int i = cl; i < l; i++) update(i);
		if(r < cr) for(int i = cr; i > r; i--) update(i);
		ans[id] = (cnt[a[p]] > 0) ? sz : sz+1;
		// printf("[%d,%d] = %d (size: %d)\n", l, r, ans[id], sz);
		cl = l, cr = r;
	}
	
	repp(i, m) printf("%d\n", ans[i]);
}
