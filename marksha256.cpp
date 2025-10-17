#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstring>

typedef unsigned int uint32;
typedef unsigned long long uint64;

class SHA256 {
public:
    SHA256() { reset(); }
    void update(const unsigned char* data, size_t len);
    std::string digest();
private:
    void reset();
    void process(const unsigned char* chunk);
    static uint32 rotr(uint32 x, uint32 n);
    static uint32 ch(uint32 x, uint32 y, uint32 z);
    static uint32 maj(uint32 x, uint32 y, uint32 z);
    static uint32 e0(uint32 x);
    static uint32 e1(uint32 x);
    static uint32 s0(uint32 x);
    static uint32 s1(uint32 x);
    uint32 h[8];
    unsigned char data[64];
    uint64 bitlen;
    size_t datalen;
};


uint32 SHA256::rotr(uint32 x, uint32 n){ return (x >> n) | (x << (32 - n)); }
uint32 SHA256::ch(uint32 x, uint32 y, uint32 z){ return (x & y) ^ (~x & z); }
uint32 SHA256::maj(uint32 x, uint32 y, uint32 z){ return (x & y) ^ (x & z) ^ (y & z); }
uint32 SHA256::e0(uint32 x){ return rotr(x,2)^rotr(x,13)^rotr(x,22); }
uint32 SHA256::e1(uint32 x){ return rotr(x,6)^rotr(x,11)^rotr(x,25); }
uint32 SHA256::s0(uint32 x){ return rotr(x,7)^rotr(x,18)^(x>>3); }
uint32 SHA256::s1(uint32 x){ return rotr(x,17)^rotr(x,19)^(x>>10); }

void SHA256::reset() {
    h[0]=0x6a09e667; h[1]=0xbb67ae85; h[2]=0x3c6ef372; h[3]=0xa54ff53a;
    h[4]=0x510e527f; h[5]=0x9b05688c; h[6]=0x1f83d9ab; h[7]=0x5be0cd19;
    datalen = 0;
    bitlen = 0;
}

void SHA256::update(const unsigned char* dataIn, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        data[datalen] = dataIn[i];
        datalen++;
        if (datalen == 64) {
            process(data);
            bitlen += 512;
            datalen = 0;
        }
    }
}

void SHA256::process(const unsigned char* chunk) {
    static const uint32 k[64] = {
        0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
        0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
        0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
        0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
        0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
        0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
        0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
        0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
    };
    uint32 w[64];
    for (int i = 0; i < 16; ++i)
        w[i] = (chunk[i*4]<<24) | (chunk[i*4+1]<<16) | (chunk[i*4+2]<<8) | chunk[i*4+3];
    for (int i = 16; i < 64; ++i)
        w[i] = s1(w[i-2]) + w[i-7] + s0(w[i-15]) + w[i-16];

    uint32 a=h[0],b=h[1],c=h[2],d=h[3],e=h[4],f=h[5],g=h[6],hh=h[7];

    for (int i=0;i<64;i++){
        uint32 t1 = hh + e1(e) + ch(e,f,g) + k[i] + w[i];
        uint32 t2 = e0(a) + maj(a,b,c);
        hh=g; g=f; f=e; e=d+t1; d=c; c=b; b=a; a=t1+t2;
    }

    h[0]+=a; h[1]+=b; h[2]+=c; h[3]+=d;
    h[4]+=e; h[5]+=f; h[6]+=g; h[7]+=hh;
}

std::string SHA256::digest() {
    unsigned char pad[64] = {0x80};
    uint64 totalBits = bitlen + datalen * 8;
    size_t padLen = (datalen < 56) ? (56 - datalen) : (120 - datalen);
    update(pad, padLen);

    unsigned char lenBytes[8];
    for (int i = 0; i < 8; ++i)
        lenBytes[7 - i] = (totalBits >> (i * 8)) & 0xff;
    update(lenBytes, 8);

    std::ostringstream out;
    for (int i = 0; i < 8; ++i)
        out << std::hex << std::setw(8) << std::setfill('0') << h[i];
    return out.str();
}

int main() {
    std::string filename;
    std::cout << "Enter text file path: ";
    std::getline(std::cin, filename);

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Cannot open file!\n";
        return 1;
    }

    SHA256 sha;
    const size_t bufferSize = 8192;
    std::vector<unsigned char> buffer(bufferSize);

    while (file) {
        file.read(reinterpret_cast<char*>(buffer.data()), bufferSize);
        std::streamsize bytesRead = file.gcount();
        if (bytesRead > 0)
            sha.update(buffer.data(), bytesRead);
    }

    std::cout << "SHA-256: " << sha.digest() << std::endl;
    return 0;
}
