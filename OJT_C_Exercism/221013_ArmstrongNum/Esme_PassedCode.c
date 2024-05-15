#include "armstrong_numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



bool is_armstrong_number(int input_number){
    char buffer[10] = {0, };
    int digit, number, result = 0;



   // 자릿수 구하기
    itoa(input_number, buffer, 10);
    digit = strlen(buffer);
    
    printf("%d is %s!\n", input_number, buffer);
    printf("strlen is %d!\n", digit);



   // 자릿수에 따른 계산하기
    for(int i = 1; i <= digit; i++){
        number = input_number % (int)pow(10, i);  
        number /= (int)pow(10, i-1);
        printf("\n%d\t", number);            // 각 자릿수의 값
        result += pow(number, digit);        // (각 자릿수의 값)^자릿수
    }



   // 계산 결과값이 입력값과 동일한지 비교
    if(result == input_number){
        printf("%d is an Armstrong number!\n", input_number);
        return true;
    }else{
        printf("%d is not an Armstrong number...\n", input_number);
        return false;
    }
}




// 두 숫자를 바꾸는 함수
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}

// `buffer[i…j]`를 반전시키는 함수
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}



char* itoa(int value, char* buffer, int base)
{
    // 잘못된 입력
    if (base < 2 || base > 32) {
        return buffer;
    }

    // 숫자의 절대값을 고려
    int n = abs(value);

    int i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }

        n = n / base;
    }

    // 숫자가 0인 경우
    if (i == 0) {
        buffer[i++] = '0';
    }

    // 밑이 10이고 값이 음수이면 결과 문자열
    // 마이너스 기호(-)가 앞에 옵니다.
    // 다른 기준을 사용하면 값은 항상 부호 없는 것으로 간주됩니다.
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null 종료 문자열

    // 문자열을 반대로 하여 반환
    return reverse(buffer, 0, i - 1);
}