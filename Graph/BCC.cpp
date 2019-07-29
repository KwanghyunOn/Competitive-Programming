// Vertex-disjoint BCC
int num[MAXN], low[MAXN], CUR_TIME = 0;
void dfs(int v, int p) {
	num[v] = low[v] = ++CUR_TIME;
	for(auto c : adj[v]) {
		if(c == p) continue;
		if(num[c]) low[v] = min(low[v], num[c]);
		else {
			dfs(c, v);
			low[v] = min(low[v], low[c]);
		}
	}
}

vector<int> bcc[MAXN];
int CUR_COL = 0;
bool vis[MAXN];
void color(int v, int col) {
	bcc[v].push_back(col);
	for(auto c : adj[v]) if(!vis[c]) {
		vis[c] = true;
		if(num[v] <= low[c]) {
			bcc[v].push_back(++CUR_COL);
			color(c, CUR_COL);
		} else color(c, col);
	}
}


// Edge-disjoint BCC
int num[MAXN], low[MAXN], cnum;
void dfs(int v, int p) {
	num[v] = low[v] = ++cnum;
	for(auto c : adj[v]) {
		if(c == p) continue;
		if(num[c]) low[v] = min(low[v], num[c]);
		else {
			dfs(c, v);
			low[v] = min(low[v], low[c]);
		}
	}
}

int bcc[MAXN], ccol;
bool vis[MAXN];
void color(int v, int col) {
	bcc[v] = col;
	for(auto c : adj[v]) if(!vis[c]) {
		vis[c] = true;
		if(low[c] > num[v]) color(c, ++ccol);
		else color(c, col);
	}
}
