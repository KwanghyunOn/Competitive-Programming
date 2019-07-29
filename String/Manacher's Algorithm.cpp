void manacher(const string &s, int *A, int *B) {
	int n = (int)s.size();
	int R = -1, P = -1;
	for(int i = 0; i < n; i++) {
		if(i <= R) A[i] = min(A[2*P-i], R-i);
		else A[i] = 0;
		while(0 <= i-A[i]-1 && i+A[i]+1 < n && s[i-A[i]-1] == s[i+A[i]+1]) A[i]++;
		if(R < i+A[i]) R = i+A[i], P = i;
	}
	
	R = -1, P = -1;
	for(int i = 0; i < n; i++) {
		if(i <= R) B[i] = min(B[2*P-i], R-i+1);
		else B[i] = 0;
		while(0 <= i-B[i]-1 && i+B[i] < n && s[i-B[i]-1] == s[i+B[i]]) B[i]++;
		if(R < i+B[i]-1) R = i+B[i]-1, P = i;
	}
}
