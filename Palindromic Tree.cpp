struct Node {
	int len;
	bool flag[26];
	Node *nxt[26], *suf;
	Node() : len(0), suf(NULL) {
		for(int i = 0; i < 26; i++)
			flag[i] = false, nxt[i] = NULL;
	}

	int countChar() {
		int cnt = 0;
		for(int i = 0; i < 26; i++)
			if(flag[i]) cnt++;
		return cnt;
	}
} *iroot, *root, *maxSuf;


void addChar(char *s, int p) {
	int x = s[p] - 'a';
	Node *t = maxSuf;
	while(true) {
		if(p-(t->len)-1 >= 0 && s[p-(t->len)-1] == s[p]) break;
		t = t->suf;
	}
	if(t->nxt[x]) {
		maxSuf = t->nxt[x];
		return;
	}

	Node *v = t->nxt[x] = new Node();
	maxSuf = v;
	if(t == iroot) {
		v->len = 1;
		v->flag[x] = true;
		v->suf = root;
		return;
	}

	v->len = t->len + 2;
	for(int i = 0; i < 26; i++)
		v->flag[i] = t->flag[i];
	v->flag[x] = true;
	t = t->suf;
	while(true) {
		if(p-(t->len)-1 >= 0 && s[p-(t->len)-1] == s[p]) break;
		t = t->suf;
	}
	v->suf = t->nxt[x];
}


void buildPalTree(int n, char *s) {
	iroot = new Node(), root = new Node();
	iroot->len = -1;
	root->len = 0;
	iroot->suf = root->suf = iroot;
	maxSuf = root;
	for(int i = 0; i < n; i++)
		addChar(s, i);
}
