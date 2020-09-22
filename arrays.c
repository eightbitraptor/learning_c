#include <stdio.h>
#include <stdlib.h>

#define ARRLEN 10

typedef struct arr_t {
    char * data;
    int len;
} arr_t;

arr_t *
new_arr(int len)
{
    char *c = calloc(len, sizeof(char));
    arr_t *arr = malloc(sizeof(arr_t));

    arr->data = c;
    arr->len = 0;

    return arr;
}

int
simple_find(arr_t * arr, int len, char elem)
{
    int found_idx = 0;

    for( int i = 0; i < len; i++) {
        if( arr->data[i] == elem){
            found_idx = i;
            break;
        }
    }

    return found_idx;
}

int
binary_search(arr_t * arr, int start, int end, char elem)
{
    int mid = start + (end - start) / 2;

    // found it
    if(arr->data[mid] == elem) return mid;
    // if the mid point is larger than array then must be in left
    if(arr->data[mid] > elem) return binary_search(arr, 0, mid - 1, elem);
    // otherwise it must be in the right
    return binary_search(arr, mid + 1, end, elem);
}

int
partition(arr_t * arr, int low, int high)
{
    char pivot = arr->data[high];
    int i = (low - 1);
    int temp = 0;

    for(int j = low; j <= high - 1; j++)
    {
        if(arr->data[j] < pivot) {
            i++;
            temp = arr->data[i];
            arr->data[i] = arr->data[j];
            arr->data[j] = temp;
        }
    }

    temp = arr->data[i + 1];
    arr->data[i + 1] = arr->data[high];
    arr->data[high] = temp;

    return(i + 1);
}

void
quicksort(arr_t * arr, int low, int high)
{
    if (low < high) {
        int pivot = partition(arr, low, high);

        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}

void
push_char_at(arr_t * arr, int loc, char elem)
{
    // make space for the new element
    arr->data = realloc(arr->data, arr->len + 1);
    arr->len = arr->len + 1;

    // move everything after the chosen location out of the way
    for (int i = arr->len - 1; i >= loc; i--) {
        arr->data[i + 1] = arr->data[i];
    }
    // push the elem in to the arr
    arr->data[loc] = elem;
}

void
append(arr_t * arr, char elem) {
    push_char_at(arr, arr->len, elem);
}

void
prepend(arr_t * arr, char elem) {
    push_char_at(arr, 0, elem);
}

int
main()
{
    char *str = "abcdefghijklmnopqrstuvwxyz";

    arr_t * chars = new_arr(ARRLEN);

    for( int i = 0; i < ARRLEN; i++) {
        chars->data[i] = str[i];
        chars->len++;
    }

    for( int i = 0; i < ARRLEN; i++)
        printf("%c", chars->data[i]);

    printf("\n");
    printf("found the letter b at %i using scanning\n", simple_find(chars, ARRLEN, 'b'));

    for( int i = 0; i < ARRLEN; i ++){
        char c = str[i];
        printf("found the letter %c at %i\n",c , binary_search(chars, 0, ARRLEN - 1, c));
    }

    printf("%s\n", chars->data);
    push_char_at(chars, 5, 'Z');
    printf("%s\n", chars->data);
    append(chars, 'A');
    printf("%s\n", chars->data);
    prepend(chars, 'X');
    printf("%s\n", chars->data);


    printf("sorting...\n");
    quicksort(chars, 0, chars->len - 1);
    printf("%s\n", chars->data);

    free(chars);
}
