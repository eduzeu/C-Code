#include <stdio.h>

/*
   Eduardo Hernandez 
   CS 382 - Homework 1 
   I pledge my honor that I have abided by the Stevens Honor System.
   State the sorting algorithm you chose in task 3
   State if you want to be considered for bonus points in task 3
*/

/**
 * copies a string 
*/
void copy_str(char* src, char* dst) {
   int counter = 0; 
    start:
        if(src[counter] == '\0'){ // stop if it's at last position 
            dst[counter] = src[counter]; //copy final array
            goto end;
        }else{
         dst[counter] = src[counter]; //set each element equal to the copy 
            counter++;
            goto start;
        }
    end:
    
}
/**
 * @brief calculates doc product of two vectors
 * 
 * @param vec_a 
 * @param vec_b 
 * @param length 
 * @param size_elem 
 * @return int 
 */
int dot_prod(char* vec_a, char* vec_b, int length, int size_elem) {

    int counter = 0;
    int current_mult; 
    int current_sum = 0;
    start:
            if(counter == length){ //stop when reaches end 
                goto end; 
            }else{
                //get 4 byte integer 
                int* a_elem = (int*)(vec_a + counter * size_elem); //take the whole  integer 
                int* b_elem = (int*)(vec_b + counter * size_elem);//take whole integer
                //dereference to get actual values 
                current_mult = (*a_elem) * (*b_elem); //use dereference to get the actual value
                current_sum = current_sum + current_mult; //use dereference to get actual value 
                counter++;
                goto start; 
            }
    end: 
 
    
   return current_sum;
}

//******************************************************
// I WANT TO BE CONSIDERED FOR BONUS POINTS IN THIS TASK
// I USED BUBBLE SORT FOR THIS TASK 
//******************************************************
/**
 * @brief sorts nibs by creating an array of nibs, then using bubble sort in such array, and finally regrouping back in the original array
 * 
 * @param arr 
 * @param length 
 */
void sort_nib(int* arr, int length) {
    char nibs[8 * length]; //initialize nibs 
    char* ans = (char*) arr;
    int i = 0; 

//create array nibs 
start: 
    if (i == 8 * length) {
        goto end;
    } else {
        char num;
        if (i % 2 == 0) {
            // Take the upper 4 bits (nibble) of ans[i/2]
            num = (ans[i/2] >> 4) & 0x0F;
            nibs[i] = num;
        } else {
            // Take the lower 4 bits (nibble) of ans[i/2]
            num = ans[i / 2] & 0x0F;
            nibs[i] = num;
        }
        i++;
    }
    goto start;

end: 
    int j = 0;
loop: 
    if (j < 8 * length - 1) {
        int k = 0;

// use bubble sort in array nibs
inner: 
        if (k < 8 * length - j - 1) {
            if (nibs[k] > nibs[k + 1]) {
                // Swap nibs[k] and nibs[k + 1]
                char temp = nibs[k];
                nibs[k] = nibs[k + 1];
                nibs[k + 1] = temp;
            }
            k++;
            goto inner;
        }
        j++;
        goto loop;
    }

 // Regroup nibbles back into integers and replace them in arr
    int m = 0;
    int n = 0;
regroup:
    if (m < length) {
        int value = 0;

        regroup_loop:
            if(n < 8){
            value = (value << 4) | (nibs[m * 8 + n] & 0x0F); // Shifts `value` left by 4 bits and combines it with the lower 4 bits of `nibs[m * 8 + n]`
            n++;
            goto regroup_loop;

        }else{
            arr[m] = value;
            m++;
            n = 0; //set equal to zero to grab each value correctly when we star over
            goto regroup;
        }
    }

    // I WANT TO BE CONSIDERED FOR BONUS POINTS IN THIS TASK
}


int main(int argc, char** argv) {

    /**
     * Task 1
     */

    char str1[] = "382 is the best!";
    char str2[100] = {0};

    copy_str(str1,str2);
    puts(str1);
    puts(str2);

    /**
     * Task 2
     */

    int vec_a[3] = {12, 34, 10};
    int vec_b[3] = {10, 20, 30};
    int dot = dot_prod((char*)vec_a, (char*)vec_b, 3, sizeof(int));
    
    printf("%d\n",dot);

    /**
     * Task 3
     */

    int arr[3] = {0x12BFDA09, 0x9089CDBA, 0x56788910};
    sort_nib(arr, 3);


     for(int i = 0; i<3; i++) {
          printf("0x%08x ", arr[i]);
     }
    puts(" ");


    return 0;
}


