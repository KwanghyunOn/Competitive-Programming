typedef complex<double> base;

void fft(vector<base> &a, bool invert) {
	int n = (int)a.size();
	for(int i = 1, j = 0; i < n; i++) {
		int bit = (n >> 1);
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}

	for(int len = 2; len <= n; len <<= 1) {
		double ang = (invert?-1:1) * (2*acos(-1)/len);
		base w(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			base wpow(1);
			for(int j = 0; j < len/2; j++) {
				base u = a[i+j], v = wpow * a[i+j+len/2];
				a[i+j] = u+v;
				a[i+j+len/2] = u-v;
				wpow *= w;
			}
		}
	}
	if(invert)
		for(int i = 0; i < n; i++) a[i] /= n;
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < max(a.size(), b.size())) n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);
	fft(fa, false), fft(fb, false);
	for(int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, true);
	res.resize(n);
	for(int i = 0; i < n; i++)
		res[i] = int(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
}
