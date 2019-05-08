//sub[v]: size of subtree whose root is v
void dfsSubtree(int node, int pnode) {
	sub[node] = 1;
	for(auto cnode : adj[node]) {
		if(cnode != pnode) {
			dfsSubtree(cnode, node);
			sub[node] += sub[cnode];
		}
	}
}



int dfsCentroid(int node, int pnode, int size) {
	for(auto cnode : adj[node]) {
		if(cnode != pnode && sub[cnode] > size / 2)
			return dfsCentroid(cnode, node, size);
	}
	return node;
}



void decompose(int node, int pCtr) {
	dfsSubtree(node, -1);
	int ctr = dfsCentroid(node, node, sub[node]);
	if(pCtr == -1)  // root of centroid tree
		pCtr = ctr;	
	ctPar[ctr] = pCtr;

	for(auto cnode : adj[ctr]) {
		adj[cnode].erase(ctr);
		decompose(cnode, ctr);
	}
	adj[ctr].clear();
}
