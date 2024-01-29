#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>  // Include this header for INT_MAX

#define MAX 10000
#define NUM_THREADS 2

// Struct to pass arguments to the thread function
struct ThreadArgs {
    int *arr;
    int start;
    int end;
};

// Function declarations
void random_shuffle(int arr[]);
void swap(int *a, int *b);
int partition(int arr[], int p, int r);
void quick_sort(int arr[], int p, int q);
void *threaded_quicksort(void *args);

int main()
{
    int i;
    int arr[MAX];
    for (i = 0; i < MAX; i++)
        arr[i] = i;

    random_shuffle(arr);

    // Create thread arguments for each part
    struct ThreadArgs args[NUM_THREADS];
    int partition_size = MAX / NUM_THREADS;

    for (i = 0; i < NUM_THREADS; i++) {
        args[i].arr = arr;
        args[i].start = i * partition_size;
        args[i].end = (i == NUM_THREADS - 1) ? MAX - 1 : (i + 1) * partition_size - 1;
    }

    // Create threads
    pthread_t threads[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, threaded_quicksort, (void *)&args[i]);
    }

    // Join threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge the sorted parts
    int merged[MAX];
    int indices[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        indices[i] = args[i].start;
    }

    for (i = 0; i < MAX; i++) {
        int min_val = INT_MAX;
        int min_index = -1;

        for (int j = 0; j < NUM_THREADS; j++) {
            if (indices[j] <= args[j].end && args[j].arr[indices[j]] < min_val) {
                min_val = args[j].arr[indices[j]];
                min_index = j;
            }
        }

        merged[i] = min_val;
        indices[min_index]++;
    }

    printf("completed...\n");

    // Uncomment the following lines to print the sorted array
    // for (i = 0; i < MAX; i++)
    //    printf("%d \n", merged[i]);

    return 0;
}

void *threaded_quicksort(void *args)
{
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
    quick_sort(threadArgs->arr, threadArgs->start, threadArgs->end);
    return NULL;
}

void random_shuffle(int arr[])
{
    srand(time(NULL));
    int i, j, temp;
    for (i = MAX - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int p, int r)
{
    int pivotIndex = p + rand() % (r - p + 1);
    int pivot;
    int i = p - 1;
    int j;

    pivot = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[r]);

    for (j = p; j < r; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[r]);
    return i + 1;
}

void quick_sort(int arr[], int p, int q)
{
    int j;
    if (p < q)
    {
        j = partition(arr, p, q);
        quick_sort(arr, p, j - 1);
        quick_sort(arr, j + 1, q);
    }
}
