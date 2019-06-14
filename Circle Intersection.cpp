// finding intersection point of two circles
bool circleCircle(Point c1, double r1, Point c2, double r2, pair<Point, Point> &interPoint) {
	double d = distance(c1, c2), cosA = (d*d + r1*r1 - r2*r2) / (2.0*d*r1);
	if(abs(cosA) > 1) return false;
	double alpha = acos(cosA);
	Point rad = ((c2-c1) / d) * r1;
	interPoint = {c1 + rotate(rad, -alpha), c1 + rotate(rad, alpha)};
	return true;
}
