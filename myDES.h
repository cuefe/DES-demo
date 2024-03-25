#pragma once

#include <bitset>
#include <fstream>
#include <iostream>
using namespace std;

int fill_cnt = 0;
bitset<48> sub_key[16];
const int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44, 36, 28,
                    20, 12, 4,  62, 54, 46, 38, 30, 22, 14, 6,  64, 56,
                    48, 40, 32, 24, 16, 8,  57, 49, 41, 33, 25, 17, 9,
                    1,  59, 51, 43, 35, 27, 19, 11, 3,  61, 53, 45, 37,
                    29, 21, 13, 5,  63, 55, 47, 39, 31, 23, 15, 7};
const int RIP[64] = {40, 8,  48, 16, 56, 24, 64, 32, 39, 7,  47, 15, 55,
                     23, 63, 31, 38, 6,  46, 14, 54, 22, 62, 30, 37, 5,
                     45, 13, 53, 21, 61, 29, 36, 4,  44, 12, 52, 20, 60,
                     28, 35, 3,  43, 11, 51, 19, 59, 27, 34, 2,  42, 10,
                     50, 18, 58, 26, 33, 1,  41, 9,  49, 17, 57, 25};
const int PC_1[56] = {57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34, 26, 18,
                      10, 2,  59, 51, 43, 35, 27, 19, 11, 3,  60, 52, 44, 36,
                      63, 55, 47, 39, 31, 23, 15, 7,  62, 54, 46, 38, 30, 22,
                      14, 6,  61, 53, 45, 37, 29, 21, 13, 5,  28, 20, 12, 4};
const int PC_2[48] = {14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10,
                      23, 19, 12, 4,  26, 8,  16, 7,  27, 20, 13, 2,
                      41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
                      44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
const int ROL[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
const int E[] = {32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,  8,  9,  10, 11,
                 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
                 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
const int S[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};
const int P[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23,
                   26, 5, 18, 31, 10, 2,  8,  24, 14, 32, 27,
                   3,  9, 19, 13, 30, 6,  22, 11, 4,  25};
                   
bitset<64> str2bit(string str) {
    bitset<64> bit;
    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            bit[k++] = (str[i] >> (7 - j)) & 1;
        }
    }
    return bit;
}

string bit2str(bitset<64> bit) {
    string str = "";
    for (int i = 0; i < 8; i++) {
        char ch = 0;
        ch += bit[i * 8] * 128 + bit[i * 8 + 1] * 64 + bit[i * 8 + 2] * 32 +
              bit[i * 8 + 3] * 16 + bit[i * 8 + 4] * 8 + bit[i * 8 + 5] * 4 +
              bit[i * 8 + 6] * 2 + bit[i * 8 + 7];
        str += ch;
    }
    return str;
}

bitset<28> rotate_left(bitset<28> bit, int step) {
    bitset<28> rotated_bit;
    for (int i = 0; i < 28; i++) {
        rotated_bit[i] = bit[(i + step) % 28];
    }
    return rotated_bit;
}

void gen_sub_key(string key) {
    bitset<64> key_bit = str2bit(key);
    bitset<56> PC_1_key_bit;
    for (int i = 0; i < 56; i++) {
        PC_1_key_bit[i] = key_bit[PC_1[i] - 1];
    }
    bitset<28> C;
    bitset<28> D;
    for (int i = 0; i < 28; i++) {
        C[i] = PC_1_key_bit[i];
        D[i] = PC_1_key_bit[i + 28];
    }

    for (int i = 0; i < 16; i++) {
        C = rotate_left(C, ROL[i]);
        D = rotate_left(D, ROL[i]);
        for (int j = 0; j < 28; j++) {
            PC_1_key_bit[j] = C[j];
            PC_1_key_bit[j + 28] = D[j];
        }
        for (int j = 0; j < 48; j++) {
            sub_key[i][j] = PC_1_key_bit[PC_2[j] - 1];
        }
    }
}

bitset<32> F(bitset<32> R, bitset<48> sub_key) {
    bitset<48> E_R;
    for (int i = 0; i < 48; i++) {
        E_R[i] = R[E[i] - 1];
    }
    E_R = E_R ^ sub_key;
    bitset<32> S_R;
    for (int i = 0, j = 0; i < 48; i += 6, j += 4) {
        int row = E_R[i] * 2 + E_R[i + 5];
        int col = E_R[i + 1] * 8 + E_R[i + 2] * 4 + E_R[i + 3] * 2 + E_R[i + 4];
        int S_out = S[i / 6][row][col];
        bitset<4> S_out_bit(S_out);
        S_R[j] = S_out_bit[3];
        S_R[j + 1] = S_out_bit[2];
        S_R[j + 2] = S_out_bit[1];
        S_R[j + 3] = S_out_bit[0];
    }
    bitset<32> P_R;
    for (int i = 0; i < 32; i++) {
        P_R[i] = S_R[P[i] - 1];
    }
    return P_R;
}

bitset<64> bit_encrypt(bitset<64> plain_bit) {
    bitset<64> IP_bit;
    for (int i = 0; i < 64; i++) {
        IP_bit[i] = plain_bit[IP[i] - 1];
    }
    bitset<32> L;
    bitset<32> R;
    for (int i = 0; i < 32; i++) {
        L[i] = IP_bit[i];
        R[i] = IP_bit[i + 32];
    }
    bitset<32> L_tmp;
    for (int i = 0; i < 16; i++) {
        L_tmp = L;
        L = R;
        R = L_tmp ^ F(R, sub_key[i]);
    }
    bitset<64> merge_bit;
    for (int i = 0; i < 32; i++) {
        merge_bit[i] = R[i];
        merge_bit[i + 32] = L[i];
    }
    bitset<64> encrypt_bit;
    for (int i = 0; i < 64; i++) {
        encrypt_bit[i] = merge_bit[RIP[i] - 1];
    }
    return encrypt_bit;
}

bitset<64> bit_decrypt(bitset<64> encrypt_bit) {
    bitset<64> IP_bit;
    for (int i = 0; i < 64; i++) {
        IP_bit[i] = encrypt_bit[IP[i] - 1];
    }
    bitset<32> L;
    bitset<32> R;
    for (int i = 0; i < 32; i++) {
        L[i] = IP_bit[i];
        R[i] = IP_bit[i + 32];
    }
    bitset<32> L_tmp;
    for (int i = 15; i >= 0; i--) {
        L_tmp = L;
        L = R;
        R = L_tmp ^ F(R, sub_key[i]);
    }
    bitset<64> merge_bit;
    for (int i = 0; i < 32; i++) {
        merge_bit[i] = R[i];
        merge_bit[i + 32] = L[i];
    }
    bitset<64> decrypt_bit;
    for (int i = 0; i < 64; i++) {
        decrypt_bit[i] = merge_bit[RIP[i] - 1];
    }
    return decrypt_bit;
}

void encrypt(string file, string destFile, string key) {
    gen_sub_key(key);
    ifstream fin("plain.txt");
    ofstream fout("encrypt.txt", ios::app);
    string line, plain_txt;
    while (std::getline(fin, line)) {
        plain_txt += line + "\n";
    }
    while (plain_txt.size() % 8 != 0) {
        plain_txt += '0';
        fill_cnt += 8;
    }
    int block_cnt = plain_txt.size() / 8;
    for (int i = 0; i < block_cnt; i++) {
        bitset<64> plain_bit = str2bit(plain_txt);
        bitset<64> encrypt_bit = bit_encrypt(plain_bit);
        string encrypt_txt = bit2str(encrypt_bit);
        fout << encrypt_txt;
        plain_txt.erase(0, 8);
    }
    fin.close();
    fout.close();
}

void decode(string file, string destFile, string key) {
    gen_sub_key(key);
    ifstream fin("encrypt.txt");
    ofstream fout("decrypt.txt", ios::app);
    string line, encrypt_txt;
    while (std::getline(fin, line)) {
        encrypt_txt += line + "\n";
    }
    int block_cnt = encrypt_txt.size() / 8;
    for (int i = 0; i < block_cnt; i++) {
        bitset<64> encrypt_bit = str2bit(encrypt_txt);
        bitset<64> decrypt_bit = bit_decrypt(encrypt_bit);
        string decrypt_txt = bit2str(decrypt_bit);
        if (i == block_cnt - 1) {
            while (fill_cnt) {
                decrypt_txt.erase(decrypt_txt.size() - 1);
                fill_cnt -= 8;
            }
        }
        fout << decrypt_txt;
        encrypt_txt.erase(0, 8);
    }
    fin.close();
    fout.close();
}