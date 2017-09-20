#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
enum { SZ = 4 };
enum { SZB = 8 };
enum { DOUBLE = 2 };
enum { MASK = 0xFF };
int
main(void)
{
    char buf[SZ];
    int newseq = 1;
    int i = 0, j = 0, sizea = SZ, sizeb = SZ, maxx = 0, n = 0;
    int *a = realloc(NULL, sizea);
    int *b = realloc(NULL, sizeb);
    while (read(0, buf, SZ) == SZ) {
        if (newseq) {
            if (SZ * j >= sizeb) {
                sizeb *= DOUBLE;
                b = realloc(b, sizeb);
            }
            b[j] = i;
            newseq = 0;
            j++;
        }
        int t = buf[0] | (buf[1] << SZB) | (buf[2] << 2 * SZB) | (buf[3] << 3 * SZB);
        if (SZ * i >= sizea) {
            sizea *= DOUBLE;
            a = realloc(a, sizea);
        }
        if ((t > maxx) || maxx == 0) {
            maxx = t;
        }
        a[i] = t;
        i++;
        if (!t) {
            newseq = 1;
        } else {
            n++;
        }
    }
    if (SZ * i >= sizea) {
        sizea *= DOUBLE;
        a = realloc(a, sizea);
    }
    a[i] = 0;
    int cnt = j;
    if (n == 0) {
        return 0;
    }
    int minn = a[0];
    int left = n;
    int cntm;
    while (left) {
        minn = maxx;
        for (i = 0; i < cnt; i++) {
            if (a[b[i]] && (a[b[i]] < minn)) {
                minn = a[b[i]];
            }
        }
        cntm = 0;
        for (i = 0; i < cnt; i++) {
            while (a[b[i]] == minn){
                cntm++;
                b[i]++;
                if (!a[b[i]]) {
                    break;
                }
            }
        }
        for (i = 0; i < cntm; i++){
            write(1, &minn, SZ);
        }
        left -= cntm;
    }
    return 0;
}
