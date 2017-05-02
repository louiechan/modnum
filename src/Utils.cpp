#include "../include/Utils.h"
#include <iostream>

void Utils::exgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(!b) { d = a; x = 1; y = 0; }
    else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

ll Utils::modInv(ll a, ll p){
    ll d,x,y;
    exgcd(a,p,d,x,y);
    return d == 1 ? (x+p)%p : -1;
}

int Utils::gcd(ll a,ll b)
{
    return (int) (b == 0 ? a : gcd(b, a % b));
}

ll Utils::generateRandomNum(ll begin,ll end){
    srand((unsigned int)clock());
    return (rand()+begin)%end;
}
