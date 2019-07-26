int pa[MAXN], aux[MAXN], ui[MAXN];
int cntPa, cntAux;

void initDSU(int n) {
	for(int i = 1; i <= n; i++) {
		pa[i] = aux[i] = i;
		ui[i] = 0;
	}
	cntPa = cntAux = n;
}

int findPa(int x) {
	return (pa[x] == x) ? x : pa[x] = findPa(pa[x]);
}

void mergePa(int x, int y) {
	if(findPa(x) != findPa(y)) {
		pa[pa[x]] = pa[y];
		cntPa--;
	}
}

int findAux(int x, int cur) {
	if(ui[x] != cur) {
		ui[x] = cur;
		if(pa[x] == x) aux[x] = x;
		else aux[x] = findAux(pa[x], cur);
		return aux[x];
	}
	return (aux[x] == x) ? x : aux[x] = findAux(aux[x], cur);
}

void mergeAux(int x, int y, int cur) {
	if(findAux(x, cur) != findAux(y, cur)) {
		aux[aux[x]] = aux[y];
		cntAux--;
	}
}
