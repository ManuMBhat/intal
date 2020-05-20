#include"intal.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define ASCII_ZERO 48
#define DOUBLE_ZERO 96
#define MAX_SIZE    1000

//mod gcd

static char* init_intal(int n){
    char* result = (char*)malloc(sizeof(char)*(n+1));
    for(int i = 0;i < n;i++){
        result[i] = '0';
    }
    result[n] = '\0';
    return result;
}

static char* lstrip0(const char* input){
    
    int i = 0;
    int len = strlen(input);
    
    while(input[i] == '0'){
        i++;
    }
    if(input[i] == '\0'){
        return init_intal(1);
    }
    int j = 0;
    char* result = init_intal(len - i);
    while(input[i] != '\0'){
        result[j] = input[i];
        i++;
        j++;
    }
    result[j] = '\0';
    return result;
}

int intal_compare(const char* intal1,const char* intal2){
    char* intal1_1 = lstrip0(intal1);
    int intal1_length = strlen(intal1_1);
    char* intal2_1 = lstrip0(intal2);
    int intal2_length = strlen(intal2_1);
    int result = 0;
    if(intal1_length > intal2_length){
        return 1;
    }
    else if(intal1_length < intal2_length){
        return -1;
    }
    else{
        int i = 0;
        while(i < intal1_length){
            if(intal1_1[i] - intal2_1[i] > 0){
                return 1;
            }
            else if(intal1_1[i] - intal2_1[i] < 0){
                return -1;
            }
            else{
                i++;
            }
        }
    }
    free(intal1_1);
    free(intal2_1);
    return result;
}

static char* intal_add_char(const char* intal1, int size_intal1, const char* intal2, int size_intal2){
    int max_size = size_intal1>size_intal2?size_intal1:size_intal2;
    
    char* result = init_intal(max_size + 1);
    
    int carry = 0;

    int i = size_intal1 - 1;
    int j = size_intal2 - 1;
    int k = max_size;
    while(i >= 0 && j>= 0){
        int sum = (int)(intal1[i]+ intal2[j] + carry - DOUBLE_ZERO);
        if(sum > 9){
            sum = sum % 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        result[k] = (char)(sum + ASCII_ZERO);
        i--;
        j--;
        k--;
    }
    while(i>=0){
        int sum = (int)(intal1[i] - ASCII_ZERO) + carry;
        if(sum > 9){
            sum = sum % 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        result[k] = (char)(sum + ASCII_ZERO);
        i--;
        k--;
    }
    while( j>= 0){
        int sum = (intal2[j] - ASCII_ZERO) + carry;
        if(sum > 9){
            sum = sum % 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        result[k] = (char)(sum + ASCII_ZERO);
        j--;
        k--;
    }
    result[k] = (char)(carry + ASCII_ZERO);

    char* final_result = lstrip0(result);
    free(result);
    return final_result;
}

char* intal_add(const char* intal1, const char* intal2){ 
    int size_intal1 = strlen(intal1);
    int size_intal2 = strlen(intal2);
    return intal_add_char(intal1,size_intal1,intal2,size_intal2);

}
char* intal_diff(const char* intal1,const char* intal2){
    int coeff_intal1 = 1;
    int coeff_intal2 = -1;
    if(intal_compare(intal1,intal2) == -1){
        coeff_intal1 = -1;
        coeff_intal2 = 1;
    }
    int size_intal1 = strlen(intal1);
    int size_intal2 = strlen(intal2);
    int max_size = size_intal1>size_intal2?size_intal1:size_intal2;
    
    char* result = init_intal(max_size);
    
    int carry = 0;

    int i = size_intal1 - 1;
    int j = size_intal2 - 1;
    int k = max_size - 1;
    while(i >= 0 && j >= 0){
        int diff = (int)(coeff_intal1*(intal1[i] -ASCII_ZERO) +  coeff_intal2*(intal2[j] - ASCII_ZERO) - carry);
        if(diff < 0){
            carry = 1;
            diff = diff + 10;
        }
        else{
            carry = 0;
        }
        result[k] = (char)(diff + ASCII_ZERO);
        i--;
        j--;
        k--;
    }
    while(i >= 0 && coeff_intal1 == 1){
        int diff = (int)((intal1[i] - ASCII_ZERO) - carry);
        if(diff < 0){
            carry = 1;
            diff = diff + 10;
        }
        else{
            carry = 0;
        }
        result[k] = (char)(diff + ASCII_ZERO);
        i--;
        k--;
    }
    while(j >= 0 && coeff_intal2 == 1){
        int diff = (int)((intal2[j] - ASCII_ZERO) - carry);
        if(diff < 0){
            carry = 1;
            diff = diff + 10;
        }
        else{
            carry = 0;
        }
        result[k] = (char)(diff + ASCII_ZERO);
        j--;
        k--;
    }
    char* final_result = lstrip0(result);
    free(result);
    return final_result;

}

static char* pad_0(const char* input,int total_digits, int length){
    char* result = init_intal(total_digits);
    
    int i = length - 1;
    int j = total_digits - 1;
    while(i >= 0){
        result[j] = input[i];
        i--;
        j--;
    }
    return result;
}

static char* power_10(const char* input, int n){
    int len = strlen(input);
    char* result = init_intal(len + n);
    int i = 0;
    while(input[i] != '\0'){
        result[i] = input[i];
        i++;
    }
    
    return result;
}

static char* karatsuba(const char* intal1, int size_intal1, const char* intal2, int size_intal2){
    int n = size_intal1 > size_intal2 ? size_intal1 : size_intal2;
    char* intal1_mod = pad_0(intal1,n,size_intal1);
    char* intal2_mod = pad_0(intal2,n,size_intal2);

    if(size_intal1 == 0 || size_intal2 == 0){
        char* result = init_intal(MAX_SIZE);
        strcpy(result,"0");
        result[1] = '\0';
        return result;
    }
    if(n == 1){
        int product = (int)(intal1_mod[0] - ASCII_ZERO) * (intal2_mod[0] - ASCII_ZERO);
        char* result = init_intal(2);
        result[1] = (char)((product % 10) + ASCII_ZERO);
        result[0] = (char)((int)(product/10) + ASCII_ZERO);
        return result;
    }
    int first_half = (int)n/2;
    int second_half = n - first_half;

    //A1*B1
    char* r1 = karatsuba(intal1_mod,first_half,intal2_mod,first_half);
    //A2*B2
    char* r2 = karatsuba(intal1_mod + first_half,second_half, intal2_mod + first_half, second_half);
    //(A1 + A2)*(B1 + B2)
    char* r3 = intal_add_char(intal1_mod,first_half,intal1_mod + first_half, second_half); // A1 + A2
    char* r4 = intal_add_char(intal2_mod,first_half,intal2_mod + first_half,second_half);               // B1 + B2
    char* r5 = karatsuba(r3,strlen(r3),r4,strlen(r4));

    char* r6 = intal_diff(r5,r1);
    char* r7 = intal_diff(r6,r2);
    char* r8 = power_10(r1,2 * second_half);
    char* r9 = power_10(r7,second_half);
    char* r10 = intal_add(r8,r9);
    char* result1 = intal_add(r10,r2);

    char* final_result = lstrip0(result1);
    free(result1);
    free(r10);
    free(r9);
    free(r8);
    free(r7);
    free(r6);
    free(r5);
    free(r4);
    free(r3);
    free(r2);
    free(r1);
    free(intal1_mod);
    free(intal2_mod);
    return final_result;
}


char* intal_multiply(const char* intal1,const char* intal2){
    int size_intal1 = strlen(intal1);
    int size_intal2 = strlen(intal2);
    char* result = karatsuba(intal1,size_intal1,intal2,size_intal2);
    char* final_result = lstrip0(result);
    free(result);
    return final_result;

}


char* intal_fibonacci(unsigned int n){
    char* fibonacci1 = init_intal(MAX_SIZE);
    char* fibonacci2 = init_intal(MAX_SIZE);
    char* fibonacci3;
    strcpy(fibonacci1,"0");
    strcpy(fibonacci2,"1");
    unsigned int i;
    for(i = 2; i<= n; i++){
        fibonacci3 = intal_add(fibonacci1, fibonacci2);
        char* temp = fibonacci1;
        fibonacci1 = fibonacci2;
        fibonacci2 = fibonacci3;
        free(temp);
    }
    char* final_result = lstrip0(fibonacci3);
    if(i > 4){
        free(fibonacci2);
        free(fibonacci3);
    }
    return final_result;
    
}

int intal_max(char **arr,int n){
    char* max = arr[0];
    int pos = 0;
    int i = 0;
    while(i < n){
        if(intal_compare(arr[i],max) == 1){
            max = arr[i];
            pos = i;
        }
        i++;
    }
    return pos;
}


int intal_min(char **arr,int n){
    char* min = arr[0];
    int pos = 0;
    int i = 0;
    while(i < n){
        if(intal_compare(arr[i],min) == -1){
            min = arr[i];
            pos = i;
        }
        i++;
    }
    return pos;
}


int intal_search(char **arr, int n,const char* key){
    int pos = 0;
    while(pos < n){
        if(!intal_compare(arr[pos],key)){
            return pos;
        }
        pos++;
    }
    return -1;
}
//char** bincoeff = (char**)malloc(sizeof(char*)*(n + 1)*(k + 1));
    // unsigned int  i = 0;
    // if(k > n -k){
    //     k = n - k;
    // }
    // while(i <= n){
    //     unsigned int j = 0;
    //     while(j <= i && j<= k){
    //         if(j == 0 || j == i){
    //             bincoeff[i*(k + 1) + j] = "1";
    //         }
    //         else{
    //             bincoeff[i*(k + 1) + j] = intal_add(bincoeff[(i - 1)*(k + 1) + j],bincoeff[(i - 1)*(k + 1) + j - 1]);
    //         }
    //         j++;
    //     }
    //     i++;
    // }
    // char* res = init_intal(strlen(bincoeff[n * (k + 1) + k]));
    // strcpy(res,bincoeff[n * (k + 1) + k]);
    // free(bincoeff);
    // char* final_result = lstrip0(res);
    // free(res);
    // return final_result;
char* intal_bincoeff(unsigned int n, unsigned int k){
    char** bincoeff =  (char**)malloc(sizeof(char*)*(k + 1));
    bincoeff[0] = init_intal(1);
    strcpy(bincoeff[0],"1");
    if(k > (n - k)){
        k = n - k;
    }
    unsigned int i = 1;
    while(i <= k){
        bincoeff[i] = "0";
        i++;
    }
    i = 1;
    while(i <= n){
        unsigned int j = (i >= k)? k: i;
        while(j > 0){
            bincoeff[j] = intal_add(bincoeff[j],bincoeff[j - 1]);
            j--;
        }
        i++;
    }
    char* result = init_intal(strlen(bincoeff[k]));
    strcpy(result,bincoeff[k]);
    for(unsigned int i = 0; i <= k; i++){
        free(bincoeff[i]);
    }
    free(bincoeff);
    return result;
}



char* intal_pow(const char* intal1, unsigned int n){
    if(n == 0){
        char* result = init_intal(MAX_SIZE);
        strcpy(result,"1");
        return result;
    }
    char* k = intal_pow(intal1,(int)n/2);
    char* result;
    if(n % 2 == 1){
        char* inter = intal_multiply(k,k);
        result = intal_multiply(inter,intal1);
        free(inter);
    }
    else{
        result = intal_multiply(k,k);
    }
    free(k);
    return result;
}





char* intal_factorial(unsigned int n){
    char* result = (char*)malloc(sizeof(char)*MAX_SIZE);
    strcpy(result,"1");
    char* tempVal;
    for(unsigned int i = 2;i <= n; i++){
        char* temp;
        sprintf(temp,"%d",i);
        tempVal = result;
        result = intal_multiply(temp,tempVal);
        free(tempVal);
    }
    return result;
}

int intal_binsearch(char **arr, int n, const char* key){
    int beg = 0;
    int end = n - 1;
    int mid;
    while(beg <= end){
        mid = (beg + end)/2;
        int res = intal_compare(arr[mid],key);
        if(res == 0){
            return mid;
        }
        else if(res == -1){
            beg = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }
    return -1;
}


static void merge(char** arr,int l,int m,int r){
    int i,j,k;
    int n1 = m - l + 1;
    int n2 = r - m;

    char* L[n1];
    char* R[n2];
    for(i = 0;i < n1; i++){
        L[i] = arr[l + i];
    }
    for(j = 0;j < n2; j++){
        R[j] = arr[m + 1 +j];
    }
    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2){
        int res = intal_compare(L[i],R[j]);
        if(res == -1){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

static void mergeSort(char** arr,int l,int r){
    if(l < r){
        int m = (l + r)/2;
        mergeSort(arr,l,m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
void intal_sort(char **arr, int n){
    mergeSort(arr, 0, n - 1);
}

static char* max(char* intal1, char* intal2){
    int res = intal_compare(intal1,intal2);
    char* result = init_intal(MAX_SIZE);
    if(res > 0){
        int i = 0;
        while(intal1[i] != '\0'){
            result[i] = intal1[i];
            i++;
        }
        result[i] = '\0';
    }
    else{
         int i = 0;
        while(intal2[i] != '\0'){
            result[i] = intal2[i];
            i++;
        }
        result[i] = '\0';
    }
    return result;
}

char* coin_row_problem(char **arr, int n){
    if(n == 0){
        return "0";
    }
    char* prev = init_intal(MAX_SIZE);
    strcpy(prev,"0");
    char* curr = init_intal(strlen(arr[0]));
    int i = 0;
    while(arr[0][i] != '\0'){
        curr[i] = arr[0][i];
        i++;
    }
    curr[i] = '\0';
    for(int j = 2; j<=n; j++){
        char* temp  = intal_add(prev,arr[j - 1]);
        char* next = max(temp,curr);
        char* t1 = prev;
        prev = curr;
        curr = next;
        free(temp);
        free(t1);
    }
    return curr;
}


char* intal_mod(const char* intal1, const char* intal2)
{
    int res = intal_compare(intal1,intal2);
	if(res == -1){
		char* result = init_intal(strlen(intal1));
		strcpy(result,intal1);
		return result;
	}
	int diff = strlen(intal1) - strlen(intal2) - 1;
	if(diff > 0)
	{
        char* r1 = power_10(intal2,diff);
        char* temp = r1;
		r1 = intal_diff(intal1,temp);
        free(temp);
		return intal_mod(r1,intal2);
	}
    char* temp = init_intal(strlen(intal1));
    strcpy(temp,intal1);
    while(intal_compare(temp,intal2) > -1){
        char* temp3 = temp;
        temp = intal_diff(temp,intal2);
        free(temp3);
    }
    char* final_result = lstrip0(temp);
    free(temp);
	return final_result;
}

char* intal_gcd(const char* intal1, const char* intal2){
    if(intal_compare(intal2,"0") == 0){
        char* result = init_intal(strlen(intal1));
        strcpy(result,intal1);
        return result;
    }
    char* mod = intal_mod(intal1,intal2);
    char* result = intal_gcd(intal2,mod);
    free(mod);
    return result;
}