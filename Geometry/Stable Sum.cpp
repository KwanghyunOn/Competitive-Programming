// relative error for stable sum of n elements is O(logn)
// naively adding n elements gives O(n) relative error

struct stableSum {
	int cnt = 0;
	vector<double> v, psum{0};	// psum: prefix sum of v
	void operator += (double a) {
		assert(a >= 0)
		int s = ++cnt;
		while(!(s&1)) {
			a += v.back();
			v.pop_back(), psum.pop_back();
			s /= 2;
		}
		v.push_back(a);
		psum.push_back(psum.back() + a);
	}
	double val() { return psum.back(); }
};
