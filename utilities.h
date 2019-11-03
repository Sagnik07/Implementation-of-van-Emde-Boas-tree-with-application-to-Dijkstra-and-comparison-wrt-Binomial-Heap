#include <bits/stdc++.h>
// int poweroftwo(int val){
//     if(val<0)return 0;
//     --val;
//     val |= val>>1;
//     val |= val>>2;
//     val |= val>>4;
//     val |= val>>8;
//     val |= val>>16;
//     return (val + 1);
// }
int poweroftwo(int val){
    int res=1;
    if(val && !(val&(val-1))){
        return val;
    }   
    while(res<val){
        res<<=1;
    }    
    return res;   
}
double lowersqrt(int value){
    return pow(2, floor(log2(value) / 2));
}
double highersqrt(int value){
    return pow(2, ceil(log2(value) / 2));
} 