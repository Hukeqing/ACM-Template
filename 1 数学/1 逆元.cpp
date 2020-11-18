ll exgcd(ll a, ll b, ll &x, ll &y) { //扩展欧几里得算法
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll ret = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}

ll getInv(int a, int mod) { //求a在mod下的逆元，不存在逆元返回-1
    ll x, y;
    ll d = exgcd(a, mod, x, y);
    return d == 1 ? (x % mod + mod) % mod : -1;
}
