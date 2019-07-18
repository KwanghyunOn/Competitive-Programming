int par[MAXN];
int rank[MAXN];

void init(int n) {
  for(int i = 0; i < n; i++) {
    par[i] = i;
    rank[i] = 0;
  }
}

int find(int x) {
  if(par[x] == x)
    return x;
  else
    return par[x] = find(par[x]);
}

void merge(int x, int y) {
  x = find(x);
  y = find(y);
  if(x == y) return;
  par[x] = y;
}
