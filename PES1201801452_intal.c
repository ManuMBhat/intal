#include"intal.h"
#include<malloc.h>
#include<stdio.h>

static int number_of_digits(char* num){
    int i = 0;
    while(num[i] != '\0'){
        i++;
    }
    return i;
}

static char* init_intal(int n){
    char* result = (char*)malloc(sizeof(char)*(n+1));
    for(int i = 0;i < n;i++){
        result[i] = '0';
    }
    result[n] = '\0';
    return result;
}
char* rstrip0(char* input){
    int i = 0;
    char* result = (char*)malloc(sizeof(char)*100);
    while(input[i] == '0'){
        i++;
    }
    int index = 0;
    while(input[i] != '\0'){
        result[index] = input[i];
        index++;
        i++;
    }
    result[index] = '\0';
    return result;
}

char* intal_add(char* intal1, char* intal2){
    int carry = 0;
    int size1 = number_of_digits(intal1);
    int size2 = number_of_digits(intal2);
    int larger_size = size1>size2?size1:size2;
    
    char* result = init_intal(larger_size);

    int index_first = size1 - 1;
    int index_second = size2 - 1;
    int index_result = larger_size;
    while(index_first >= 0 && index_second >= 0){
        int r1 = (int)intal1[index_first] + (int)intal2[index_second] + carry - 96;
        carry = r1>9?(int)r1 % 9:0;
        result[index_result] = (char)((r1%10) + 48);
        index_second--;
        index_first--;
        index_result--;
    }
    if(index_second > 0){
        while (index_second >= 0){
            int r1 = intal2[index_second] + carry - 48;
            carry = (int)r1 / 10;
            result[index_result] = (char)((r1%10) + 48);
            index_second--;
            index_result--;
        } 
    }
    if(index_first >= 0){
        while (index_first >= 0){
            int r1 = intal1[index_first] + carry - 48;
            carry = (int)r1 / 10;
            result[index_result] = (char)((r1%10) + 48);
            index_first--;
            index_result--;
        } 
    }
    char* final_result = rstrip0(result);
    free(result);
    return final_result;
}


int intal_compare(char* intal1, char* intal2){
    int size_intal1 = number_of_digits(intal1);
    int size_intal2 = number_of_digits(intal2);
    if(size_intal1 > size_intal2){
        return 1;
    }
    if(size_intal2 > size_intal1){
        return -1;
    }
    int i = 0;
    while(intal1[i] != '\0' && intal2[i] != '\0'){
        if(intal1[i] > intal2[i]){
            return 1;
        }
        if(intal2[i] > intal1[i]){
            return -1;
        }
        i++;
    }
    return 0;
}

char* intal_diff(char* intal1, char* intal2){
    if(intal_compare(intal1,intal2) == -1){
        char* temp = intal2;
        intal2 = intal1;
        intal1 = temp;
    }
    int size_intal1 = number_of_digits(intal1);
    int size_intal2 = number_of_digits(intal2);
    int carry = 0;
    char* result = init_intal(size_intal1);
    for(int i = 0; i < size_intal2; i++){
        int s1 = intal1[size_intal1 - i - 1] - intal2[size_intal2 - i - 1] - carry;

        if(s1 < 0){
            s1 += 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        result[size_intal1 - i - 1] = (char)(s1 + 48);
    }
    for(int i = size_intal2; i<size_intal1; i++){
        int s1 = intal1[size_intal1 - i - 1] - carry - 48;
        if(s1 < 0){
            s1 += 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        result[size_intal1 - i - 1] = (char)(s1 + 48);

    }
    char* final_result = rstrip0(result);
    free(result);
    return final_result;
}

// static char* stringIt(int n){
//     char* result = (char*)malloc(sizeof(char)*2);
//     result[0] = (char)((n % 10) + 48);
//     int res = n/10;
//     if(res >= 0 && res <= 9){
//         result[1] = (char)((int)(n/10) + 48);
//     }
//     else{
//         result[1] = '0';
//     }
//     return result; 
// }
static char* multiply_10_power_n(char* input, int n){
    int num = number_of_digits(input);
    char* res = (char*)malloc(sizeof(char)*(num + n + 1));
    for(int i = 0; i < num; i++){
        res[i] = input[i];
    }
    for(int i = 0; i < n; i++){
        res[num + i] = '0';
    }
    res[num + n] = '\0';
    return rstrip0(res);
}
static int max_2(int n, int m){
    return n>m?1:0;
}

static char* equal_digits(char* intal1,int num_digits){
    int size = number_of_digits(intal1);
    char* result = (char*)malloc(sizeof(char)*(num_digits + 1));

    for(int i=0;i<(num_digits - size);i++){
        result[i] = '0';
    }        
    
    for(int i = (num_digits - size), j = 0;j < size; i++,j++){
        result[i] = intal1[j];
    }
    result[num_digits] = '\0';
    return result;
}


char* karatsuba(char* intal1,char* intal2,int num_digits1, int num_digits2){
    int max = max_2(num_digits1,num_digits2)?num_digits1:num_digits2;
    
    if(num_digits1 == 1 && num_digits2 == 1){
        int product = (intal1[0] - '0')*(intal2[0] - '0');
        char* result = init_intal(2);
        sprintf(result,"%d",product);
        return rstrip0(result);
    }
    if(num_digits1 == 0 || num_digits2 == 0){
        return "0";
    }
    char* intal1_1 = equal_digits(intal1,max);
    char* intal2_1 = equal_digits(intal2,max);
    int first_half = max/2;
    int second_half = max - first_half;
    //A1*B1
    char* r1 = karatsuba(intal1_1,intal2_1,first_half,first_half);
    //A2*B2
    char* r2 = karatsuba(intal1_1 + first_half, intal2_1 + first_half, second_half, second_half);
    //A2*B1
    char* r3 = karatsuba(intal1_1 + first_half, intal2_1, second_half, first_half);
    //A1*B2
    char* r4 = karatsuba(intal1_1, intal2_1 + first_half, first_half, second_half);
    // A1*B1*10^n
    char* r1_mod = multiply_10_power_n(r1,max);
    char* r3_mod = intal_add(r3,r4);
    char* r4_mod = multiply_10_power_n(r3_mod,first_half);

    char* r5 = intal_add(r2,r4_mod);
    char* r6 = intal_add(r1_mod,r5);
    // free(r1);
    // free(r2);
    // free(r3);
    // free(r4);
    // free(r5);
    // free(r1_mod);
    // free(r3_mod);
    //free(r4_mod);
    // free(intal1_1);
    // free(intal2_1);
    return rstrip0(r6);
}
char* intal_multiply(char* intal1, char* intal2){
    int size_intal1 = number_of_digits(intal1);
    int size_intal2 = number_of_digits(intal2);
    int max = size_intal2>size_intal1?size_intal2:size_intal1;
    return karatsuba(intal1,intal2,size_intal1,size_intal2);
}
//Write test for multiplication
