int fail[MAXN];
void findFailure(const string &P) {
	fail[1] = 0;
	int k = 0;
	for(int i = 1; i < (int)P.size(); i++) {
		while(k && P[i] != P[k]) k = fail[k];
		if(P[i] == P[k]) k++;
		fail[i+1] = k;
	}
}

// pattern P, string S
void kmp(const string &P, const string &S, vector<int> &matchIndex) {
	int k = 0;
	for(int i = 0; i < (int)S.size(); i++) {
		while(k && S[i] != P[k]) k = fail[k];
		if(S[i] == P[k]) k++;
		if(k == (int)P.size()) {
			matchIndex.push_back(i-(int)P.size()+1);
			k = fail[k];
		}
	}
}
