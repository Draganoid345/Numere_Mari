#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#define maxSize 100
#include <bits/stdc++.h>
using namespace std;

class BigNumber
{
    public:
        BigNumber(char* = nullptr);
        BigNumber(long long);
        virtual ~BigNumber();
        friend ostream& operator <<(ostream&, const BigNumber&);
        friend istream& operator >>(istream&, BigNumber&);
        friend BigNumber operator +(const BigNumber&, const BigNumber&);
        friend BigNumber operator -(const BigNumber&, const BigNumber&);
        friend BigNumber operator *(const BigNumber&, long long);
        friend BigNumber operator *(long long, const BigNumber&);
        friend BigNumber operator *(const BigNumber&, const BigNumber&);
        friend bool operator <(const BigNumber&, const BigNumber&);
        friend bool operator ==(const BigNumber&, const BigNumber&);
    protected:

    private:
        short int digits[maxSize];
        bool isNegative;
        int nrDigits;

};

#endif // BIGNUMBER_H
