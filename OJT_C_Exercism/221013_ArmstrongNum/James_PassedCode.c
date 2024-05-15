#include "armstrong_numbers.h"
#include "math.h"
bool is_armstrong_number(int candidate){
int ND = 0;
int sum = 0;
for(int i = 0; i < 10; i++){
if((int)(pow(10,i)) <= candidate && (int)(pow(10,i+1)) > candidate)
ND = i+1;
}
for(int k =0; k < ND; k++){
int n;
n = (candidate / (int)(pow(10, k))) % 10;
sum += (int)(pow(n,ND));
}
if(sum == candidate)
return true;
else
return false;
}