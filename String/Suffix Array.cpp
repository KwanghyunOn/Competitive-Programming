const int MAXN = 1e5 + 50;
int cnt[MAXN], x[MAXN], y[MAXN];
void suffixArray(int n, char *s, int *sa, int *rk) {
    memset(cnt, 0, sizeof cnt);
    int m = 255;
    for(int i = 0; i < n; i++) cnt[x[i] = s[i]]++;
    for(int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
    for(int i = 0; i < n; i++) sa[--cnt[x[i]]] = i;
    for(int len = 1, sz = 1; sz < n; len <<= 1, m = sz) {
        int p = 0;
        for(int i = n-len; i < n; i++) y[p++] = i;
        for(int i = 0; i < n; i++) if(sa[i] >= len) y[p++] = sa[i]-len;
        for(int i = 1; i <= m; i++) cnt[i] = 0;
        for(int i = 0; i < n; i++) cnt[x[i]]++;
        for(int i = 1; i <= m; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
        swap(x, y), sz = 1, x[sa[0]] = 1;
        for(int i = 0; i < n-1; i++) {
            if(y[sa[i]] != y[sa[i+1]] || y[sa[i]+len] != y[sa[i+1]+len]) sz++;
            x[sa[i+1]] = sz;
        }
    }

    for(int i = 0; i < n; i++) rk[sa[i]] = i;
}

void findLcp(int n, char *s, int *sa, int *rk, int *lcp) {
    int h = 0;
    for(int i = 0; i < n; i++) {
        if(rk[i]) {
            int prv = sa[rk[i]-1];
            while(s[prv+h] == s[i+h]) h++;
            lcp[rk[i]] = h;
        }
        h = max(h-1, 0);
    }
}
