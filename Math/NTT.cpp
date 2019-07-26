// p = a*(2^b) + 1, x = primitive root of p
// g = x^a, gpow = b
const ll g = 15311432;
const ll ginv = inverse(g, MOD);
const int gpow = 23;

void fft(vector<ll> &a, bool invert) {
	int n = (int)a.size();
	for(int i = 1, j = 0; i < n; i++) {
		int bit = (n >> 1);
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}
	int k = 1;
	for(int len = 2; len <= n; len <<= 1, k++) {
		ll w = (invert) ? ginv : g;
		for(int i = 0; i < gpow-k; i++) w = mmul(w, w);
		for(int i = 0; i < n; i += len) {
			ll wpow = 1;
			for(int j = 0; j < len/2; j++) {
				ll u = a[i+j], v = mmul(wpow, a[i+j+len/2]);
				a[i+j] = madd(u, v);
				a[i+j+len/2] = msub(u, v);
				wpow = mmul(wpow, w);
			}
		}
	}
	ll n_inv = inverse(n, MOD);
	if(invert)
		for(int i = 0; i < n; i++) a[i] = mmul(a[i], n_inv);
}


void multiply(vector<ll> &a, vector<ll> &b, vector<ll> &res) {
	vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while(n < max(a.size(), b.size())) n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);
	fft(fa, false), fft(fb, false);
	for(int i = 0; i < n; i++) fa[i] = mmul(fa[i], fb[i]);
	fft(fa, true);
	res.assign(fa.begin(), fa.end());
}
