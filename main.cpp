#include "myDES.h"

int main() {
    ofstream encrypt_file("encrypt.txt", ios::trunc);
    encrypt_file.close();
    ofstream decrypt_file("decrypt.txt", ios::trunc);
    decrypt_file.close();
    string key = "ucalzped";
    encrypt("plain.txt", "encrypt.txt", key);
    decode("encrypt.txt", "decrypt.txt", key);
    return 0;
}
