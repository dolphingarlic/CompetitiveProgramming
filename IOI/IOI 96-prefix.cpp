#include <stdio.h>
#include <string.h>

/* maximum number of primitives */
#define MAXP 200
/* maximum length of a primitive */
#define MAXL 10

char prim[MAXP + 1][MAXL + 1]; /* primitives */
int nump;                      /* number of primitives */

int start[200001]; /* is this prefix of the sequence expressible? */
char data[200000]; /* the sequence */
int ndata;         /* length of the sequence */

int main() {
    int best;
    int lv, lv2, lv3;

    /* read in primitives */
    while (1) {
        scanf("%s", prim[nump]);
        if (prim[nump][0] != '.')
            nump++;
        else
            break;
    }

    /* read in string, one line at a time */
    ndata = 0;
    while (scanf("%s", data + ndata) == 1) ndata += strlen(data + ndata);

    start[0] = 1;
    best = 0;
    for (lv = 0; lv < ndata; lv++)
        if (start[lv]) { /* for each expressible prefix */
            best = lv;   /* we found a longer expressible prefix! */
            /* for each primitive, determine the sequence starting at
               this location matches it */
            for (lv2 = 0; lv2 < nump; lv2++) {
                for (lv3 = 0; lv + lv3 < ndata && prim[lv2][lv3] &&
                              prim[lv2][lv3] == data[lv + lv3];
                     lv3++)
                    ;
                if (!prim[lv2][lv3]) /* it matched! */
                    start[lv + lv3] =
                        1; /* so the expanded prefix is also expressive */
            }
        }

    /* see if the entire sequence is expressible */
    if (start[ndata]) best = ndata;

    printf("%i\n", best);
    return 0;
}