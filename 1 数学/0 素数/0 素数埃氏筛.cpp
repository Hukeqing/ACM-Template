/*
 * 埃拉托色尼筛选法
 * 素数筛选，判断小于 MAXN 的数是不是素数。
 * notPrime 是一张表，为 false 表示是素数，true 表示不是素数
 */
const int MAXN = 1000010;
bool notPrime[MAXN]; // 值为 false 表示素数，值为 true 表示非素数
void init() {
    memset(notPrime, false, sizeof(notPrime));
    notPrime[0] = notPrime[1] = true;
    for (int i = 2; i < MAXN; i++)
        if (!notPrime[i]) {
            if (i > MAXN / i)
                continue; // 防止后面 i*i 溢出 (或者 i,j 用 long long)
            // 直接从 i*i 开始就可以，小于 i 倍的已经筛选过了, 注意是 j += i
            for (int j = i * i; j < MAXN; j += i)
                notPrime[j] = true;
        }
}
