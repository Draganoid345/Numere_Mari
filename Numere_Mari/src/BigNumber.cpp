#include "BigNumber.h"
#include <bits/stdc++.h>
#define maxSize 100
using namespace std;

BigNumber::BigNumber(char* x)
{
    this->isNegative = false;
    this->nrDigits = 0;
    if(x != nullptr)
    {
        if(strlen(x) > maxSize)
            throw "Depasita limita de cifre";

        if(x[0] == '-')
        {
            this->isNegative = true;
            int k = 0;
            for(int i = strlen(x) -  1; i >= 1; i--)
            {
                this->digits[k] = x[i] - '0';
                k++;
            }
            this->nrDigits = k;
        }
        else
        {

            int k = 0;
            for(int i = strlen(x) -  1; i >= 0; i--)
            {
                this->digits[k] = x[i] - '0';
                k++;
            }
            this->nrDigits = k;
        }
        for(int i = this->nrDigits; i < maxSize; i++)
            this->digits[i] = 0;
        /*
        for(int i = 0; i < this->nrDigits; i++)
            cout << this->digits[i] << " ";
        cout << "\n";
        */

    }
}

BigNumber toBigNumber(long long x)
{
    string s = to_string(x);
    char c[maxSize];
    strcpy(c, s.c_str());
    return BigNumber(c);
}


//afisarea
ostream& operator << (ostream& out, const BigNumber& x)
{
    if(x.isNegative)
        cout << '-';
    for(int i = x.nrDigits - 1; i >= 0; i--)
        cout << x.digits[i];
//    cout << "\n";
    return out;
}

istream& operator >>(istream& in, BigNumber& x)
{
    char c[maxSize];
    in >> c;
    x = BigNumber(c);
    return in;
}

//adunare a 2 numere mari
BigNumber operator +(const BigNumber& x, const BigNumber& y)
{
    BigNumber z = x;
    if((!x.isNegative && !y.isNegative) || (x.isNegative && y.isNegative))
    {
        //cout << "+ ambele negative sau pozitive\n";
        int carry = 0;
        for(int i = 0; i < max(x.nrDigits, y.nrDigits); i++)
        {
            z.digits[i] = z.digits[i] + y.digits[i] + carry;
            carry = z.digits[i] / 10;
            z.digits[i] %= 10;
        }
        z.nrDigits = max(x.nrDigits, y.nrDigits);
        if(carry > 0)
        {
            z.digits[z.nrDigits] = carry;
            z.nrDigits++;

        }
        if(x.isNegative && x.isNegative)
            z.isNegative = true;
    }
    else
    {
        if(x.isNegative)
        {
            //cout << "+ x e negativ\n";
            BigNumber temp = x;
            temp.isNegative = false;
            z = y - temp;
        }
        else
        {
            //cout << "+ y e negativ\n";
            BigNumber temp = y;
            temp.isNegative = false;
            z = x - temp;
        }
    }

    return z;
}

//scaderea

BigNumber operator -(const BigNumber& x, const BigNumber& y)
{
    BigNumber z = x;

    if(x.isNegative && !y.isNegative)           // (-x - y) = - (x + y)
    {
        //cout << "- x e negativ, y pozitiv\n";
        BigNumber temp = x;
        temp.isNegative = false;
        z = (temp + y);
        z.isNegative = true;
        return z;
    }
    else if(!x.isNegative && y.isNegative)      //(x - (-y)) = (x + y)
    {
        //cout << "- x e pozitiv, y negativ\n";
        BigNumber temp = y;
        temp.isNegative = false;
        z = (temp + x);
        z.isNegative = false;
        return z;
    }
    else if(x.isNegative && y.isNegative)     //(-x - (-y)) = (-x + y) = (y - x)
    {
        //cout << "- ambele negative\n";
        BigNumber temp1 = x;
        BigNumber temp2 = y;
        temp1.isNegative = false;
        temp2.isNegative = false;
        return (temp2 - temp1);
    }
    else                                      //(x - y)
    {
        if((y < x) || (y == x))
        {
            //cout << "- ambele pozitive, y <= x\n";
            int carry = 0;
            for(int i = 0; i < x.nrDigits; i++)
            {
                z.digits[i] = z.digits[i] - (y.digits[i] + carry);
                if(z.digits[i] < 0)
                    carry = 1;
                else
                    carry = 0;
                if(carry)
                    z.digits[i] += 10;
            }
            while(!z.digits[z.nrDigits-1] && z.nrDigits > 1) z.nrDigits--;
            return z;
        }
        else
        {
            //cout << "- ambele pozitive, y > x\n";
            BigNumber temp = (y - x);
            temp.isNegative = true;
            return temp;
        }

    }
}

//inmultire

BigNumber operator *(const BigNumber& x, const BigNumber& y)
{
    BigNumber z("0");
    if((x.nrDigits == 1 && x.digits[0] == 0) || (y.nrDigits == 1 && y.digits[0] == 0))
    {
        return z;
    }
    int i, j, carry;
    for(i = 0; i < x.nrDigits; i++)
    {
        for(carry = 0, j = 0; j < y.nrDigits || carry; j++, carry /= 10)
        {
            z.digits[i + j] = (carry += z.digits[i + j] + x.digits[i] * y.digits[j]) % 10;
        }
        //cout << z.nrDigits << "\n";
        //cout << i << " " << j << "\n";
        if(i + j > z.nrDigits)
        {
            z.nrDigits = i + j;
        }

    }
    return z;
}

BigNumber operator *(const BigNumber& x, long long y)
{
    return (x * toBigNumber(y));
}

BigNumber operator *(long long x, const BigNumber& y)
{
    return (y * toBigNumber(x));
}

//comparare <
bool operator <(const BigNumber& x, const BigNumber& y)
{
    if(x.isNegative && !y.isNegative)
        return true;
    if(!x.isNegative && y.isNegative)
        return false;

    if((!x.isNegative && !y.isNegative))
    {
        if(x.nrDigits < y.nrDigits)
            return true;
        if(x.nrDigits > y.nrDigits)
            return false;

        for(int i = x.nrDigits - 1; i >= 0; i--)
        {
            if(x.digits[i] > y.digits[i])
                return false;
            if(x.digits[i] < y.digits[i])
                return true;
        }
        return false;

    }
    if((x.isNegative && y.isNegative))
    {
        if(x.nrDigits < y.nrDigits)
            return false;
        if(x.nrDigits > y.nrDigits)
            return true;
        for(int i = x.nrDigits - 1; i >= 0; i--)
        {
            if(x.digits[i] < y.digits[i])
                return false;
            if(x.digits[i] > y.digits[i])
                return true;
        }
        return false;
    }

}

//comparare ==
bool operator ==(const BigNumber& x, const BigNumber& y)
{
    if((x.isNegative && !y.isNegative) || (!x.isNegative && y.isNegative))
        return false;
    if(x.nrDigits != y.nrDigits)
        return false;
    for(int i = 0; i < x.nrDigits; i++)
        if(x.digits[i] != y.digits[i])
            return false;
    return true;
}


BigNumber::~BigNumber()
{
    //dtor
}
