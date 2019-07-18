struct Node {
	bool isEnd;
	int count;
	Node *nxt[26], *f, *o;
	Node() : isEnd(false), count(0), f(NULL), o(NULL) { for(int i = 0; i < 26; i++) nxt[i] = NULL; }
} *root;


const int MAXN = 1050;
Node* endNode[MAXN];
void buildTrie(vector<string> &p) {
	root = new Node();
	int n = (int)p.size();
	for(int i = 0; i < n; i++) {
		Node *cur = root;
		for(char c : p[i]) {
			int x = c - 'a';
			if(!cur->nxt[x]) cur->nxt[x] = new Node();
			cur = cur->nxt[x];
		}
		cur->isEnd = true;
		endNode[i] = cur;
	}
 
	queue<Node*> que;
	for(int i = 0; i < 26; i++) if(root->nxt[i]) {
		root->nxt[i]->f = root;
		que.push(root->nxt[i]);
	}
	while(!que.empty()) {
		Node *q = que.front(); que.pop();
		if(q->isEnd) q->o = q;
		else q->o = q->f->o;
		for(int i = 0; i < 26; i++) if(q->nxt[i]) {
			Node *t = q->nxt[i];
			t->f = q->f;
			while(t->f != root && !t->f->nxt[i]) t->f = t->f->f;
			if(t->f->nxt[i]) t->f = t->f->nxt[i];
			que.push(t);
		}
	}
}
 
 
void search(string &s) {
	Node *cur = root;
	for(char c : s) {
		int x = c - 'a';
		while(cur != root && !cur->nxt[x]) cur = cur->f;
		if(cur->nxt[x]) cur = cur->nxt[x];
		if(cur->o) cur->o->count++;
	}
 
	vector<Node*> v;
	queue<Node*> que;
	que.push(root);
	while(!que.empty()) {
		Node *q = que.front(); que.pop();
		for(int i = 0; i < 26; i++) if(q->nxt[i]) {
			v.push_back(q->nxt[i]);
			que.push(q->nxt[i]);
		}
	}
	reverse(v.begin(), v.end());
	for(auto t : v)
		if(t->isEnd && t->f->o) t->f->o->count += t->count;
}
