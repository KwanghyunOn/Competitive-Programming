// lazy propagation
Pi tree[4*MAXK], lazy[4*MAXK];
int cnt[4*MAXK];
void pushDown(int id) {
    padd(tree[2*id], lazy[id]);
    padd(tree[2*id+1], lazy[id]);
    padd(lazy[2*id], lazy[id]);
    padd(lazy[2*id+1], lazy[id]);
    lazy[id] = {0, 0};
}

void pushUp(int id) {
    tree[id] = min(tree[2*id], tree[2*id+1]);
    cnt[id] = 0;
    if(tree[id] == tree[2*id]) cnt[id] += cnt[2*id];
    if(tree[id] == tree[2*id+1]) cnt[id] += cnt[2*id+1];
}

void buildTree(vector<Pi> &val, int l = 0, int r = k-1, int id = 1) {
    if(l == r) {
        tree[id] = val[l];
        lazy[id] = {0, 0};
        cnt[id] = 1;
        return;
    }
    int mid = (l + r) / 2;
    buildTree(val, l, mid, 2*id);
    buildTree(val, mid+1, r, 2*id+1);
    pushUp(id);
}

void rangeUpdate(int s, int e, Pi val, int l = 0, int r = k-1, int id = 1) {
    if(e < l || r < s) return;
    if(s <= l && r <= e) {
        padd(tree[id], val);
        padd(lazy[id], val);
        return;
    }
    int mid = (l + r) / 2;
    pushDown(id);
    rangeUpdate(s, e, val, l, mid, 2*id);
    rangeUpdate(s, e, val, mid+1, r, 2*id+1);
    pushUp(id);
}

int query() {
    return tree[1] == Pi(4, 0) ? cnt[1] : 0;
}
