// avoids catastrophic cancellation
int quadRoots(double a, double b, double c, pair<double, double> &root) {
	assert(a != 0);
	double disc = b*b - 4*a*c;
	if(disc < 0) return 0;
	double sum = (b >= 0) ? -b-sqrt(disc) : -b+sqrt(disc);
	root = {sum / (2.0*a), (sum == 0) ? 0 : (2*c) / sum};
	return 1 + (disc > 0.0);
}
