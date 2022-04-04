#include "hash.hpp"
#include <algorithm>
#include <sstream>

__uint32_t		rightRotate(__uint32_t n, char m) {
	return (n >> m) | (n << (32 - m));
}

// std::string to_sha256(std::string str) {
//     std::basic_string<unsigned char> str2;
//     //str2.reserve(str.length());
//     str2.push_back(0); str2.push_back(0); str2.push_back(0);
//     std::copy(str.begin(), str.end(), str2.begin());
//     for (int i = 0; i < str2.length(); ++i)
//     std::cout << str2[i] << ' ';
//     return algo(str2);
// }

std::string to_sha256(std::string &strIn) {

    std::basic_string<unsigned char> str;
    str.append(strIn.begin(), strIn.end());

    size_t l = str.length();

    // std::cout << str.length() << " - dlina first stroki" << std::endl;
    str.push_back(0b10000000);
    for (size_t i = 0; i < str.length(); ++i) {
        std::cout << (int)str[i] << ' ';
    }
    str.append(64 - ((l + 1) % 64), 0b00000000);

    //std::cout << str.length() << " - dlina dolzhna 64+64+64+...+64 byt" << std::endl;

    l *= 8;

    for (size_t i = str.length() - 1; i > str.length() - 9; --i) {
        str[i] = l & 255;
        l >>= 8;
        // std::cout << (int)str[i] << ' ';
    }

    __uint32_t  h0 = 0x6A09E667, h1 = 0xBB67AE85, h2 = 0x3C6EF372, h3 = 0xA54FF53A, h4 = 0x510E527F, h5 = 0x9B05688C, h6 = 0x1F83D9AB, h7 = 0x5BE0CD19;

    __uint32_t  k[64] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5, 
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 0xE49B69C1, 0xEFBE4786, 
    0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA, 0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 
    0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 
    0x81C2C92E, 0x92722C85, 0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070, 
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F, 
    0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
    };

    for (size_t z = 0; z < (str.length() / 64); ++z) {

    __uint32_t  w[64];

    for (size_t i = 0; i < 16; ++i) {
        size_t j = i * 4 + z * 64;
        w[i] = str[j + 3] + (str[j + 2] << 8) + (str[j + 1] << 16) + (str[j] << 24);
        std::cout << w[i] << ' ';
    }
    __uint32_t  s0, s1, t1, t2, ch, ma;

    for (size_t i = 16; i < 64; ++i) {
        s0 = rightRotate(w[i - 15], 7) xor rightRotate(w[i - 15], 18) xor (w[i - 15] >> 3);
        s1 = rightRotate(w[i - 2], 17) xor rightRotate(w[i - 2], 19) xor (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    __uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;

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

    h0 = h0 + a;
    h1 = h1 + b;
    h2 = h2 + c;
    h3 = h3 + d;
    h4 = h4 + e;
    h5 = h5 + f;
    h6 = h6 + g;
    h7 = h7 + h;

    }


    std::cout << std::hex << h0 << std::endl;
    		std::stringstream	ss;
			ss << std::hex << h0 << h1 << h2 << h3 << h4 << h5 << h6 << h7;
		return (ss.str());	

    // return "nothing";
}

int main() {

    std::string str2("dlina etogo soobsheniya dolzhna byt bolshe 65 simvolov dlya proverki govna plz sdelai 65 nu zhe comon");
    std::string str("123");

    std::cout << to_sha256(str) << std::endl;

    //std::cout << str << std::endl;
    return 0;
}