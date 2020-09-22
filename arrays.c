#include <stdio.h>
#include <stdlib.h>

#define ARRLEN 10

int
simple_find(char * arr, int len, char elem)
{
    int found_idx = 0;

    for( int i = 0; i < len; i++) {
        if( arr[i] == elem){
            found_idx = i;
            break;
        }
    }

    return found_idx;
}

int
binary_search(char * arr, int start, int end, char elem)
{
    int mid = start + (end - start) / 2;

    // found it
    if(arr[mid] == elem) return mid;
    // if the mid point is larger than array then must be in left
    if(arr[mid] > elem) return binary_search(arr, 0, mid - 1, elem);
    // otherwise it must be in the right
    return binary_search(arr, mid + 1, end, elem);
}

int
partition(char * arr, int low, int high)
{
    char pivot = arr[high];
    int i = (low - 1);
    int temp = 0;

    for(int j = low; j <= high - 1; j++)
    {
        if(arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return(i + 1);
}

void
quicksort(char * arr, int low, int high)
{
    if (low < high) {
        int pivot = partition(arr, low, high);

        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}

void
push_char_at(char * arr, int *size, int loc, char elem)
{
    // make space for the new element
    arr = realloc(arr, *size + 1);
    *size = *size + 1;
    // move everything after the chosen location out of the way
    for (int i = *size-1; i >= loc; i--) {
        arr[i + 1] = arr[i];
    }
    // push the elem in to the arr
    arr[loc] = elem;
}

void
append(char * arr, int *size, char elem) {
    push_char_at(arr, size, *size, elem);
}

void
prepend(char * arr, int *size, char elem) {
    push_char_at(arr, size, 0, elem);
}

int
main()
{
    char *str = "abcdefghijklmnopqrstuvwxyz";

    char *chars = calloc(ARRLEN, sizeof(char));
    int size = 0;

    for( int i = 0; i < ARRLEN; i++) {
        chars[i] = str[i];
        size++;
    }

    for( int i = 0; i < ARRLEN; i++)
        printf("%c", chars[i]);

    printf("\n");
    printf("found the letter b at %i using scanning\n", simple_find(chars, ARRLEN, 'b'));

    for( int i = 0; i < ARRLEN; i ++){
        char c = str[i];
        printf("found the letter %c at %i\n",c , binary_search(chars, 0, ARRLEN - 1, c));
    }

    push_char_at(chars, &size, 5, 'Z');
    append(chars, &size, 'A');
    prepend(chars, &size, 'X');
    printf("%s\n", chars);


    printf("sorting...\n");
    quicksort(chars, 0, size - 1);
    printf("%s\n", chars);

    free(chars);
}
