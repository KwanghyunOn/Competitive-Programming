// https://gist.github.com/koosaga/6f6fd50dd7067901f1b1
// Vertex-disjoint BCC
void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	par[x] = p;
	for(int i=0; i<graph[x].size(); i++){
		int w = graph[x][i];
		if(w == p) continue;
		if(!dfn[w]){
			dfs(w, x);
			low[x] = min(low[x], low[w]);
		}
		else{
			low[x] = min(low[x], dfn[w]);
		}
	}
}

void color(int x, int c){
	if(c > 0) bcc[x].push_back(c);
	vis[x] = 1;
	for(int i=0; i<graph[x].size(); i++){
		int w = graph[x][i];
		if(vis[w]) continue;
		if(dfn[x] <= low[w]){
			bcc[x].push_back(++cpiv);
			color(w, cpiv);
		}
		else{
			color(w, c);
		}
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
