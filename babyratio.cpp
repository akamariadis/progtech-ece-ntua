#include <iostream>
#include <cmath>
#ifndef CONTEST
#include "babyratio.hpp"
#endif // CONTEST

using namespace std;

bool Negative (int &n, int &d) {
    if ((n < 0 && d > 0) || (n > 0 && d < 0)) {
        if (n < 0) n =-n;
        if(d < 0) d =-d;
        return true;
    }
    return false;
}

rational::rational (int n, int d){
    int CurrentGCD = gcd(n,d);
    nom = n / CurrentGCD;
    den = d / CurrentGCD;
}

int rational::gcd (int a,int b){
    if (a == 0) return b;
    return gcd (b%a,a);
}

rational rational::add (rational r) {
    int NewNom = nom*r.den + den*r.nom;
    int NewDen = den*r.den;
    int CurrentGCD = gcd(NewNom,NewDen);
    rational NewRational(NewNom/CurrentGCD,NewDen/CurrentGCD);
    return NewRational;
}

rational rational::sub (rational r) {
    int NewNom = nom*r.den - den*r.nom;
    int NewDen = den*r.den;
    int CurrentGCD = gcd(NewNom,NewDen);
    rational NewRational(NewNom/CurrentGCD,NewDen/CurrentGCD);
    return NewRational;
}

rational rational::mul(rational r){
    int NewNom = nom*r.nom;
    int NewDen = den*r.den;
    int CurrentGCD = gcd(NewNom,NewDen);
    rational NewRational(NewNom/CurrentGCD,NewDen/CurrentGCD);
    return NewRational;
}

rational rational::div (rational r) {
    int NewNom = nom*r.den;
    int NewDen = den*r.nom;
    int CurrentGCD = gcd(NewNom,NewDen);
    rational NewRational(NewNom/CurrentGCD,NewDen/CurrentGCD);
    return NewRational;
}
void rational::print () {
    if (Negative (nom, den)) cout << '-';
    cout << abs(nom) << "/" << abs(den);
}