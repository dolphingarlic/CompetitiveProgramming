#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBITS 12
#define MAXSEQ (1 << (MAXBITS + 1))

typedef struct Seq Seq;
struct Seq {
    unsigned bits;
    int count;
};

Seq seq[MAXSEQ];

/* increment the count for the n-bit sequence "bits" */
void addseq(unsigned bits, int n) {
    bits &= (1 << n) - 1;
    bits |= 1 << n;
    assert(seq[bits].bits == bits);
    seq[bits].count++;
}

/* print the bit sequence, decoding the 1<<n stuff */
/* recurse to print the bits most significant bit first */
void printbits(unsigned bits) {
    assert(bits >= 1);
    if (bits == 1) /* zero-bit sequence */
        return;

    printbits(bits >> 1);
    printf("%d", bits & 1);
}

int seqcmp(const void *va, const void *vb) {
    Seq *a, *b;

    a = (Seq *)va;
    b = (Seq *)vb;

    /* big counts first */
    if (a->count < b->count) return 1;
    if (a->count > b->count) return -1;

    /* same count: small numbers first */
    if (a->bits < b->bits) return -1;
    if (a->bits > b->bits) return 1;

    return 0;
}

int main() {
    int i, a, b, n, nbit, c, j, k;
    unsigned bit;
    char *sep;

    nbit = 0;
    bit = 0;

    for (i = 0; i <= MAXBITS; i++)
        for (j = 0; j < (1 << i); j++) seq[(1 << i) | j].bits = (1 << i) | j;

    scanf("%d %d %d", &a, &b, &n);

    while ((c = getc(stdin)) != EOF) {
        if (c != '0' && c != '1') continue;

        bit <<= 1;
        if (c == '1') bit |= 1;

        if (nbit < b) nbit++;

        for (i = a; i <= nbit; i++) addseq(bit, i);
    }

    qsort(seq, MAXSEQ, sizeof(Seq), seqcmp);

    /* print top n frequencies for number of bits between a and b */
    j = 0;
    for (i = 0; i < n && j < MAXSEQ; i++) {
        if (seq[j].count == 0) break;

        c = seq[j].count;
        printf("%d ", c);

        /* print all entries with frequency c */
        for (k = 0; seq[j].count == c; j++, k++) {
            printbits(seq[j].bits);
            printf(" ");
        }
        printf("\n");
    }

    return 0;
}