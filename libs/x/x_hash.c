#include "x_hash.h"

int debug;
int hex; /* print in hex?  (instead of default base64) */



void sum(FILE* fd, char* name) {
    byte* buf;
    byte digest[16];
    char pr64[25];
    int i, n;
    MD5state* s;

    s = nil;
    n = 0;
    buf = calloc(256, 64);
    for (;;) {
        i = fread(buf + n, 1, 128 * 64 - n, fd);
        if (i <= 0)
            break;
        n += i;
        if (n & 0x3f)
            continue;
        s = md5(buf, n, 0, s);
        n = 0;
    }
    md5(buf, n, digest, s);
    if (hex) {
        for (i = 0; i < 16; i++)
            printf("%.2X", digest[i]);
    } else {
        enc64(pr64, digest, sizeof(digest));
        pr64[22] = '\0'; /* chop trailing == */
        printf("%s", pr64);
    }
    if (name)
        printf("\t%s", name);
    printf("\n");
    free(buf);
}

/*
 *  I require len to be a multiple of 64 for all but
 *  the last call
 */
MD5state* md5(byte* p, uint len, byte* digest, MD5state* s) {
    uint a, b, c, d, tmp;
    uint i, done;
    Table* t;
    byte* end;
    uint x[16];

    if (s == nil) {
        s = calloc(sizeof(*s), 1);
        if (s == nil)
            return nil;

        /* seed the state, these constants would look nicer big-endian */
        s->state[0] = 0x67452301;
        s->state[1] = 0xefcdab89;
        s->state[2] = 0x98badcfe;
        s->state[3] = 0x10325476;
    }
    s->len += len;

    i = len & 0x3f;
    if (i || len == 0) {
        done = 1;

        /* pad the input, assume there's room */
        if (i < 56)
            i = 56 - i;
        else
            i = 120 - i;
        if (i > 0) {
            memset(p + len, 0, i);
            p[len] = 0x80;
        }
        len += i;

        /* append the count */
        x[0] = s->len << 3;
        x[1] = s->len >> 29;
        encode(p + len, x, 8);
    } else
        done = 0;

    for (end = p + len; p < end; p += 64) {
        a = s->state[0];
        b = s->state[1];
        c = s->state[2];
        d = s->state[3];

        decode(x, p, 64);

        for (i = 0; i < 64; i++) {
            t = tab + i;
            switch (i >> 4) {
                case 0:
                    a += (b & c) | (~b & d);
                    break;
                case 1:
                    a += (b & d) | (c & ~d);
                    break;
                case 2:
                    a += b ^ c ^ d;
                    break;
                case 3:
                    a += c ^ (b | ~d);
                    break;
            }
            a += x[t->x] + t->sin;
            a = (a << t->rot) | (a >> (32 - t->rot));
            a += b;

            /* rotate variables */
            tmp = d;
            d = c;
            c = b;
            b = a;
            a = tmp;
        }

        s->state[0] += a;
        s->state[1] += b;
        s->state[2] += c;
        s->state[3] += d;
    }

    /* return result */
    if (done) {
        encode(digest, s->state, 16);
        free(s);
        return nil;
    }
    return s;
}

/*
 *	encodes input (uint) into output (byte). Assumes len is
 *	a multiple of 4.
 */
void encode(byte* output, uint* input, uint len) {
    uint x;
    byte* e;

    for (e = output + len; output < e;) {
        x = *input++;
        *output++ = x;
        *output++ = x >> 8;
        *output++ = x >> 16;
        *output++ = x >> 24;
    }
}

/*
 *	decodes input (byte) into output (uint). Assumes len is
 *	a multiple of 4.
 */
void decode(uint* output, byte* input, uint len) {
    byte* e;

    for (e = input + len; input < e; input += 4)
        *output++ =
            input[0] | (input[1] << 8) | (input[2] << 16) | (input[3] << 24);
}

typedef unsigned long ulong;
typedef unsigned char uchar;

static uchar t64d[256];
static char t64e[64];

static void init64(void) {
    int c, i;

    memset(t64d, 255, 256);
    memset(t64e, '=', 64);
    i = 0;
    for (c = 'A'; c <= 'Z'; c++) {
        t64e[i] = c;
        t64d[c] = i++;
    }
    for (c = 'a'; c <= 'z'; c++) {
        t64e[i] = c;
        t64d[c] = i++;
    }
    for (c = '0'; c <= '9'; c++) {
        t64e[i] = c;
        t64d[c] = i++;
    }
    t64e[i] = '+';
    t64d['+'] = i++;
    t64e[i] = '/';
    t64d['/'] = i;
}

int dec64(uchar* out, char* in, int n) {
    ulong b24;
    uchar* start = out;
    int i, c;

    if (t64e[0] == 0)
        init64();

    b24 = 0;
    i = 0;
    while (n-- > 0) {
        c = t64d[*in++];
        if (c == 255)
            continue;
        switch (i) {
            case 0:
                b24 = c << 18;
                break;
            case 1:
                b24 |= c << 12;
                break;
            case 2:
                b24 |= c << 6;
                break;
            case 3:
                b24 |= c;
                *out++ = b24 >> 16;
                *out++ = b24 >> 8;
                *out++ = b24;
                i = -1;
                break;
        }
        i++;
    }
    switch (i) {
        case 2:
            *out++ = b24 >> 16;
            break;
        case 3:
            *out++ = b24 >> 16;
            *out++ = b24 >> 8;
            break;
    }
    *out = 0;
    return out - start;
}

int enc64(char* out, uchar* in, int n) {
    int i;
    ulong b24;
    char* start = out;

    if (t64e[0] == 0)
        init64();
    for (i = n / 3; i > 0; i--) {
        b24 = (*in++) << 16;
        b24 |= (*in++) << 8;
        b24 |= *in++;
        *out++ = t64e[(b24 >> 18)];
        *out++ = t64e[(b24 >> 12) & 0x3f];
        *out++ = t64e[(b24 >> 6) & 0x3f];
        *out++ = t64e[(b24)&0x3f];
    }

    switch (n % 3) {
        case 2:
            b24 = (*in++) << 16;
            b24 |= (*in) << 8;
            *out++ = t64e[(b24 >> 18)];
            *out++ = t64e[(b24 >> 12) & 0x3f];
            *out++ = t64e[(b24 >> 6) & 0x3f];
            break;
        case 1:
            b24 = (*in) << 16;
            *out++ = t64e[(b24 >> 18)];
            *out++ = t64e[(b24 >> 12) & 0x3f];
            *out++ = '=';
            break;
    }
    *out++ = '=';
    *out = 0;
    return out - start;
}