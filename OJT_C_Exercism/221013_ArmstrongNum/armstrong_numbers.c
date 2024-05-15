#include "armstrong_numbers.h"

bool is_armstrong_number(int candidate)
{
    int temp = candidate;
    int size = candidate;
    int count1 = 0;        //size of numsize
   
    int resultSize = 0;
    int idx = 0;
    int arr[count1];       //Space of splited Num

//*************** Find Size of SquareSize *******************//
    while(size != 0) {

        size = size/10;
        ++count1;

        if(size < 10)
            break;
    } 
//***********************************************************//   
    
//*************** Split the Candidate ***********************//   
    while(1) {
        
        arr[idx] = temp%10;
        temp/=10;
        idx++;
        if (temp < 10)
            break;        
    }
//************************************************************//   
    
    for(int jdx = 0; jdx < (count1 +1) ; jdx++)
    {
        resultSize += pow(arr[jdx], count1);
    } // Result of Armstrong Finding

    if(resultSize != candidate)
        return false;
    else
        return true;
        
} //End of is_armstrong_number FUNCTION ....

