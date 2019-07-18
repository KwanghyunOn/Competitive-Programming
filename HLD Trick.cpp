int sz[MAXN], tin[MAXN], tout[MAXN], vin[2*MAXN], CUR_TIME = 0;
void preprocess(int v, int p) {
	tin[v] = ++CUR_TIME;
	vin[tin[v]] = v;
	sz[v] = 1;
	for(auto c : adj[v]) if(c != p) {
		preprocess(c, v);
		sz[v] += sz[c];
	}
	tout[v] = ++CUR_TIME;
}
 
 
int a[MAXN], ca[MAXN], ans[MAXN];
void dfs(int v, int p, bool keep) {
	int big = -1;
	for(auto c : adj[v])
		if(c != p && (big == -1 || sz[c] > sz[big])) big = c;
	for(auto c : adj[v])
		if(c != p && c != big) dfs(c, v, false);
	if(big != -1) dfs(big, v, true);
 
	for(auto c : adj[v]) if(c != p && c != big) {
		for(int t = tin[c]; t < tout[c]; t++) {
			if(vin[t]) {
				a[col[vin[t]]]++;
				ca[a[col[vin[t]]]]++;
			}
		}
	}
	a[col[v]]++;
	ca[a[col[v]]]++;
 
	for(auto q : qlist[v])
		ans[q.id] = ca[q.k];
 
	if(!keep) {
		for(int t = tin[v]; t < tout[v]; t++) {
			if(vin[t]) {
				ca[a[col[vin[t]]]]--;
				a[col[vin[t]]]--;
			}
		}
	}
}
