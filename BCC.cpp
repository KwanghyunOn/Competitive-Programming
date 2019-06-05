// https://gist.github.com/koosaga/6f6fd50dd7067901f1b1

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
