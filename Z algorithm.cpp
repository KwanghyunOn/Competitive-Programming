const int MAXN = 1e5 + 50;
int z[MAXN];

void calcZ(string &s) {
	int L = 0, R = 0;
	int n = (int)s.size();
	for(int i = 1; i < n; i++) {
		if(i > R) {
			L = R = i;
			while(R < n && s[R-L] == s[R]) R++;
			z[i] = R-L; R--;
		} else {
			int k = i-L;
			if(z[k] < R-i+1) z[i] = z[k];
			else {
				L = i;
				while(R < n && s[R-L] == s[R]) R++;
				z[i] = R-L; R--;
			}
		}
	}
}
