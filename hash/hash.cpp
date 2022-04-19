#include "hash.hpp"

namespace   hash {

__uint32_t		rightRotate(__uint32_t n, char m) {
	return (n >> m) | (n << (32 - m));
}

std::string to_sha256(const std::string &strIn) {

    std::basic_string<unsigned char> str;
    std::stringstream	ss;
    __uint32_t  h0 = 0x6A09E667, h1 = 0xBB67AE85, h2 = 0x3C6EF372, h3 = 0xA54FF53A,
                h4 = 0x510E527F, h5 = 0x9B05688C, h6 = 0x1F83D9AB, h7 = 0x5BE0CD19;
    size_t l = strIn.length();

    str.append(strIn.begin(), strIn.end());
    str.push_back(0b10000000);
    str.append(64 - ((l + 1) % 64), 0b00000000);
    l *= 8;
    for (size_t i = str.length() - 1; i > str.length() - 9; --i) {
        str[i] = l & 255;
        l >>= 8;
    }

    for (size_t z = 0; z < (str.length() / 64); ++z) {
        __uint32_t  w[64];
        __uint32_t  s0, s1, t1, t2, ch, ma;
        __uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;

        for (size_t i = 0; i < 16; ++i) {
            size_t j = i * 4 + z * 64;
            w[i] = str[j + 3] + (str[j + 2] << 8) + (str[j + 1] << 16) + (str[j] << 24);
        }
        for (size_t i = 16; i < 64; ++i) {
            s0 = rightRotate(w[i - 15], 7) ^ rightRotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
            s1 = rightRotate(w[i - 2], 17) ^ rightRotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        for (size_t i = 0; i < 64; ++i) {
            s0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
            ma = (a & b) ^ (a & c) ^ (b & c);
            t2 = s0 + ma;
            s1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
            ch = (e & f) ^ (~e & g);
            t1 = h + s1 + ch + k[i] + w[i];
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }
	ss << std::hex << h0 << h1 << h2 << h3 << h4 << h5 << h6 << h7;
	return (ss.str());
}
}
