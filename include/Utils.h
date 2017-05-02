#ifndef MODNUM_INCLUDE_UTILS_H
#define MODNUM_INCLUDE_UTILS_H

typedef long long ll;
class Utils{
public:
    //扩展欧几里得
    void static exgcd(ll a,ll b,ll& d,ll& x,ll& y);
    //gcd
    int static  gcd(ll a,ll b);
    //求逆元
    ll static modInv(ll a, ll p);
    ll static generateRandomNum(ll /*begin*/,ll /*end*/);
};

#endif
