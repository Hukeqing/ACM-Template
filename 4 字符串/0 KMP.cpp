/*
 * next[] 的含义:x[i-next[i]...i-1]=x[0...next[i]-1]
 * next[i] 为满足 x[i-z...i-1]=x[0...z-1] 的最大 z 值(就是 x 的自身匹配)
 */
void kmpPre(char *x, int m, int *next) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < m) {
        while (-1 != j && x[i] != x[j])
            j = next[j];
        next[++i] = ++j;
    }
}

/*
 * kmpNext[i] 的意思:next'[i]=next[next[...[next[i]]]](直到 next'[i]<0 或者 x[next'[i]]!=x[i])
 * 这样预处理可以快一点
 */
void preKMP(char *x, int m, int *kmpNext) {
    int i = 0, j = kmpNext[0] = -1;
    while (i < m) {
        while (-1 != j && x[i] != x[j])
            j = kmpNext[j];
        if (x[++i] == x[++j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}

/*
 * 以上两个预处理的函数均可用，且效果相同
 */
int KMPCountUnoverlap(char *x, int m, char *y, int n) { //x 是模式串，y 是主串，m 为 x 的长度，n 为 y 的长度，返回 x 在 y 中出现的次数，不可以重叠
    int cnt = 0, k = -1;
    int *next = new int[m + 5];
    kmpPre(x, m, next);
    // preKMP(x, m, next);
    for (int i = 0; i < n; i++) {
        while (k > -1 && x[k + 1] != y[i])
            k = next[k];
        if (x[k + 1] == y[i])
            k++;
        if (k == m - 1) {
            k = -1;
            cnt++;
        }
    }
    delete[] next;
    return cnt;
}

int KMPCountOverlap(char *x, int m, char *y, int n) { //x 是模式串，y 是主串，m 为 x 的长度，n 为 y 的长度，返回 x 在 y 中出现的次数，可以重叠
    int i = 0, j = 0, ans = 0;
    int *next = new int[m + 5];
    kmpPre(x, m, next);
    // preKMP(x, m, next);
    while (i < n) {
        while (-1 != j && y[i] != x[j])
            j = next[j];
        i++;
        j++;
        if (j >= m) {
            ans++;
            j = next[j];
        }
    }
    delete[] next;
    return ans;
}

/*
 * 扩展KMP算法
 * next[i]:x[i...m-1] 与 x[0...m-1] 的最长公共前缀长度
 * extend[i]:y[i...n-1] 与 x[0...m-1] 的最长公共前缀长度
 */
void preEKMP(char *x, int m, int *next) {
    next[0] = m;
    int j = 0;
    while (j + 1 < m && x[j] == x[j + 1])
        j++;
    next[1] = j;
    int k = 1;
    for (int i = 2; i < m; i++) {
        int p = next[k] + k - 1;
        int L = next[i - k];
        if (i + L < p + 1)
            next[i] = L;
        else {
            j = 0 > p - i + 1 ? 0 : p - i + 1;
            while (i + j < m && x[i + j] == x[j])
                j++;
            next[i] = j;
            k = i;
        }
    }
}

void EKMP(char *x, int m, char *y, int n, int *extend) { //x、y 为字符串，一般把 x 作为较短的，m、n 分别为x、y的字符串长度，extend 为答案。
    int *next = new int[m + 5];
    pre_EKMP(x, m, next);
    int j = 0, k = 0;
    while (j < n && j < m && x[j] == y[j])
        j++;
    extend[0] = j;
    for (int i = 1; i < n; i++) {
        int p = extend[k] + k - 1;
        int L = next[i - k];
        if (i + L < p + 1)
            extend[i] = L;
        else {
            j = 0 > p - i + 1 ? 0 : p - i + 1;
            while (i + j < n && j < m && y[i + j] == x[j])
                j++;
            extend[i] = j;
            k = i;
        }
    }
}
