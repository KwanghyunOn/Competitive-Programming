void calcZ(const string &s, int *z) {
	int n = (int)s.size();
	int L = 0, R = 0;
	for(int i = 1; i < n; i++) {
		if(i > R) {
			L = R = i;
			while(R+1 < n && s[R-L+1] == s[R+1]) R++;
			z[i] = R-L+1;
		} else {
			int k = i-L;
			if(z[k] < R-i+1) z[i] = z[k];
			else {
				L = i;
				while(R+1 < n && s[R-L+1] == s[R+1]) R++;
				z[i] = R-L+1;
			}
		}
	}
}
