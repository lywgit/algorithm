#include<iostream>
#include<cmath>


int KaratzubaMultiply(int x, int y){
    if (x < 10  &&  y < 10) 
        return x*y;
    
    int n_digit = log10((x>y ? x : y)) + 1;
    int power_half_n = pow(10, n_digit/2);
    int a, b, c, d, ac, bd, adbc;
    a = x/power_half_n;
    b = x - a*power_half_n;
    c = y/power_half_n;
    d = y - c*power_half_n;
    ac = KaratzubaMultiply(a, c);
    bd = KaratzubaMultiply(b, d);
    adbc = KaratzubaMultiply(a+b, c+d) - ac - bd;
    return ac*power_half_n*power_half_n + adbc*power_half_n + bd;
}


int main(){

    int x = 1234;
    int y = 5678;

    int answer = KaratzubaMultiply(x, y);
    std::cout<<"Multiplying "<<x<<" and "<<y<<std::endl 
        <<"Karatzuba: "<<answer <<std::endl
        << "Direct multiply: "<<x*y<<std::endl;

    return 0;
}
