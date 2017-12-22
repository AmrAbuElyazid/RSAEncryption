#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>

using namespace std;

bool checkIfPrime(int num) {
    bool flag = true;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            flag = false;
    }
    return flag;
}

double generatePrimeNumber() {
    double prime = rand() % 900 + 10;
    while (!checkIfPrime(prime)) {
        prime = generatePrimeNumber();
    }
    return prime;
}
double gcd(double a, double b) {
    return b == 0 ? a : gcd(b, fmod(a, b));
}
double getCoPrimeNumber(double x) {
    double y = 2;
    while (y < x) {
        if (gcd(x, y) == 1) {
            return y;
        } else
            y++;
    }
}
double getMultInverse(double e, double m) {
    bool flag = true;
    int k = 0;
    double a;
    while(flag) {
       a = (double)((m*k)+1)/e;
       if(ceil(a) == a) {
           flag = false;
           break;
       }else{
           k++;
       }
    }
    return a;
}

double modulusWithPower(double a, double b, double k) {
    double result = 1;
    while (b--) {
        result *= a;
        result = fmod(result, k);
    }
    return result;
}

double encrypt(char x, double e, double n) {
    double enc = (double) x;
    enc = modulusWithPower(x, e, n);
    return enc;
}

char decrypt(double enc, double a, double n) {
    double dec;
    dec = modulusWithPower(enc, a, n);
    char out = (char) dec;
    return out;
}

void encryptIntoFile(string filename, double e, double n) {
    string st;
    int size;
    double * x = new double[size];
    ifstream infile;
    string name;
    name = filename + ".txt";
    infile.open(name.c_str());
    infile >> st;
    for (int i = 0; i <= st.size() - 1; i++) {
        x[i] = encrypt(st[i], e, n);
    }
    infile.close();

    string nameEncrypted;
    nameEncrypted = filename + "_encrypted.txt";

    ofstream myfile(nameEncrypted.c_str());
    if (myfile.is_open()) {
        for (int count = 0; count < st.size(); count++) {
            myfile << x[count] << "|";
        }
        myfile.close();
    }
}

void decryptFromFile(string filename, double a, double n) {
    ifstream infile;
    int size;
    int* array = new int[size];
    int i = 0;
    char cNum[10];
    string name;
    name = filename + ".txt";
    infile.open(name.c_str(), ifstream:: in );
    if (infile.is_open()) {
        while (infile.good()) {
            infile.getline(cNum, 256, '|');
            array[i] = atoi(cNum);
            i++;
        }
        infile.close();
    }
    int k = 0;
    string out;
    while (array[k] != 0) {
        out += decrypt(array[k], a, n);
        k++;
    }
    cout << out << endl;

    string nameEncrypted;
    nameEncrypted = filename + "_decrypted.txt";

    ofstream myfile(nameEncrypted.c_str());
    if (myfile.is_open()) {
        myfile << out;
        myfile.close();
    }
}

int main() {
    double p = generatePrimeNumber();
    double q = generatePrimeNumber();
    double n = p * q;
    double m = (p - 1) * (q - 1);
    double e = getCoPrimeNumber(m);
    double a = getMultInverse(e, m);

    int choose;
    cout << "Choose from below: \n 1- Encrypt a file. \n 2- Decrypt a file." << endl;
    cin >> choose;
    switch (choose) {
    case 1:
        {
            string filename;
            cout << "Enter the name of the file you want to encrypt" << endl;
            cin >> filename;
            encryptIntoFile(filename, e, n);
            break;
        }
    case 2:
        {
            string filename;
            cout << "Enter the name of the file you want to decrypt" << endl;
            cin >> filename;
            decryptFromFile(filename, a, n);
            break;
        }
    default:
        return 0;
    }
}
