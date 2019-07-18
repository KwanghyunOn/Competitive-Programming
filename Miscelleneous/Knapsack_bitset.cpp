bitset<MAXK> dp;
dp[0] = 1;
for(int i = 1; i <= n; i++) {
    for(int x = 0; (1<<x) <= cnt[i]; x++) {
        dp |= (dp << (a[i]*(1<<x)));
        cnt[i] -= (1<<x);
    }
    dp |= (dp << (a[i]*cnt[i]));
}
