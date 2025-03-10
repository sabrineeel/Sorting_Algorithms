#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// BubbleSort
void BubbleSort(int A[], int n) {
    bool Change = true;
    while (Change == true) {
        Change = false;
        for (int i = 0; i < n - 1; i++) {
            if (A[i] > A[i + 1]) {
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                Change = true;
            }
        }
    }
}

// BubbleSortOpt
void BubbleSortOpt(int A[], int n) {
    int m = n - 1;
    bool Change = true;
    while (Change == true) {
        Change = false;
        for (int i = 0; i < m; i++) {
            if (A[i] > A[i + 1]) {
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
                Change = true;
            }
        }
        m--;
    }
}

// Function to measure execution time
double measureTime(void (*sortFunc)(int[], int), int A[], int n) {
    clock_t start, end;
    start = clock();
    sortFunc(A, n);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Function to generate a sorted array best case
void generateSortedArray(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

// Function to generate a reversed array  worst case
void generateReverseSortedArray(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i - 1;
    }
}

/***Gnome SORT***/
void gnomeSort(int arr[], int n) {
    int index = 0;

    while (index < n) {
        if (index == 0 || arr[index] >= arr[index - 1]) {
            index++;
        } else {
            int temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

/***Heap SORT***/
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}


/***QUICK SORT***/
// Function to partition (random pivot choice)
int partition(int tab[], int d, int f) {
    int eltPivot = tab[d];
    int i = d + 1;
    int j = f;
    int x;

    while (1) {
        while (i <= f && tab[i] <= eltPivot) {
            i++;
        }

        while (tab[j] > eltPivot && j >= d) {
            j--;
        }

        if (i >= j) {
            break;
        }

        x = tab[i];
        tab[i] = tab[j];
        tab[j] = x;
    }

    tab[d] = tab[j];
    tab[j] = eltPivot;

    return j;
}

// Best case function (pivot to center on each recursive call)
int partitionBestCase(int tab[], int d, int f) {
    int mid = (d + f) / 2;
    int eltPivot = tab[mid];
    int i = d;
    int j = f;
    int x;

    tab[mid] = tab[d];
    tab[d] = eltPivot;

    while (1) {
        while (i <= f && tab[i] <= eltPivot) {
            i++;
        }

        while (tab[j] > eltPivot && j >= d) {
            j--;
        }

        if (i >= j) {
            break;
        }

        x = tab[i];
        tab[i] = tab[j];
        tab[j] = x;
    }

    tab[d] = tab[j];
    tab[j] = eltPivot;

    return j;
}
// worst case function
int partitionWorstCase(int tab[], int d, int f) {
    int eltPivot = tab[f];
    int i = d - 1;
    int j;

    for (j = d; j < f; j++) {
        if (tab[j] <= eltPivot) {
            i++;
            int temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
    }

    int temp = tab[i + 1];
    tab[i + 1] = tab[f];
    tab[f] = temp;

    return i + 1;
}

// Fonction quicksort
void quickSort(int tab[], int p, int r, int (*partitionFunc)(int[], int, int)) {
    if (p < r) {
        int q = partitionFunc(tab, p, r);
        quickSort(tab, p, q - 1, partitionFunc);
        quickSort(tab, q + 1, r, partitionFunc);
    }
}

// Fonction pour générer un tableau trié (meilleur cas)
void generateBestCaseArray(int tab[], int size) {
    for (int i = 0; i < size; i++) {
        tab[i] = i;
    }
}

// Fonction pour générer un tableau trié à l'envers (pire cas)
void generateWorstCaseArray(int tab[], int size) {
    for (int i = 0; i < size; i++) {
        tab[i] = size - i - 1;
    }
}

// Fonction pour mesurer le temps d'exécution
double measureTimeQuick(void (*sortFunc)(int[], int, int, int (*)(int[], int, int)), int tab[], int p, int r, int (*partitionFunc)(int[], int, int)) {
    clock_t start, end;
    start = clock();
    sortFunc(tab, p, r, partitionFunc);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}


/***Radix SORT***/
int key(int x, int i) {
    int b = 1;
    for (int k = 0; k < i; k++) {
        b *= 10;
    }
    int a = b * 10;
    return (x % a) / b;
}

void SortAux(int* T, int n, int i) {
    int* Ttmp = (int*)calloc(10, sizeof(int));
    for (int j = 0; j < n; j++) {
        int digit = key(T[j], i);
        Ttmp[digit]++;
    }
    for (int j = 1; j < 10; j++) {
        Ttmp[j] += Ttmp[j - 1];
    }

    int* Ttrie = (int*)malloc(n * sizeof(int));
    for (int j = n - 1; j >= 0; j--) {
        int digit = key(T[j], i);
        Ttrie[--Ttmp[digit]] = T[j];
    }

    for (int j = 0; j < n; j++) {
        T[j] = Ttrie[j];
    }

    free(Ttmp);
    free(Ttrie);
}

int findMaxDigits(int* T, int n) {
    int maxVal = 0;
    for (int i = 0; i < n; i++) {
        if (T[i] > maxVal) {
            maxVal = T[i];
        }
    }
    int digits = 0;
    while (maxVal > 0) {
        maxVal /= 10;
        digits++;
    }
    return digits;
}

void RadixSort(int* T, int n, int k) {
    for (int i = 0; i < k; i++) {
        SortAux(T, n, i);
    }
}

double measureTimeRadix(void (*sortFunc)(int[], int, int), int A[], int n, int k) {
    clock_t start, end;
    start = clock();
    sortFunc(A, n, k);
    end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void generateBestCaseArrayRadix(int tab[], int size) {
    for (int i = 0; i < size; i++) {
        tab[i] = i;
    }
    printf("\nBest case array: ");
    for (int j = 0; j < size; j++) {
        printf("%d ", tab[j]);
    }
    printf("\n");
}

void generateWorstCaseArrayRadix(int tab[], int size) {
    int k=100;
    for (int i = 0; i < size; i++) {
        tab[i] = size-i-1+k;
        k+=100;
    }

    printf("\nWorst case array: ");
    for (int j = 0; j < size; j++) {
        printf("%d ", tab[j]);
    }
    printf("\n");
}





/******/
int main() {
    system("cls");
    system("Color E0");

    printf("\n\n\t\t\t\t\t\tSorting algorithms");
    getchar();

    char choice;
    int n;

    do {
        printf("Choose the sorting algorithm:\n");
        printf("[1] Bubble Sort\n");
        printf("[2] Optimized Bubble Sort\n");
        printf("[3] Gnome Sort\n");
        printf("[4] Radix Sort\n");
        printf("[5] Quick Sort\n");
        printf("[6] Heap Sort\n");
        printf("[q] Quit\n");

        while (1) {
            scanf(" %c", &choice);
            if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6' || choice == 'q') {
                break;
            } else {
                printf("Invalid choice. Please enter 1, 2, or q to quit: ");
            }
        }

        if (choice == 'q') {
            break;
        }

        printf("Enter the size of the array: ");
        while (1) {
            if (scanf("%d", &n) == 1 && n > 0) {
                break;
            } else {
                printf("Invalid size. Please enter a positive integer: ");
                while (getchar() != '\n');
            }
        }

        // Dynamic allocation of arrays
        int *A = (int *)malloc(n * sizeof(int));
        int *B = (int *)malloc(n * sizeof(int));
        if (A == NULL || B == NULL) {
            printf("Memory allocation failed!\n");
            return -1;
        }

        // Best case: sorted array
        generateSortedArray(A, n);
        for (int i = 0; i < n; i++) {
            B[i] = A[i];
        }

        int* tab = NULL;
        tab = (int*)malloc(n * sizeof(int));


        double time = 0.0;

        if (choice == '1') {
            time = measureTime(BubbleSort, A, n);
            printf("Time for BubbleSort (Best case): %.6f seconds\n", time);
        } else if (choice == '2') {
            time = measureTime(BubbleSortOpt, B, n);
            printf("Time for BubbleSortOpt (Best case): %.6f seconds\n", time);
        } else if (choice == '3') {
            time = measureTime(gnomeSort, B, n);
            printf("Time for gnomeSort (Best case): %.6f seconds\n", time);
        } else if (choice == '4') {
            generateBestCaseArrayRadix(tab, n);
            int k = findMaxDigits(tab, n);
            printf("Number of digits (k): %d\n", k);
            double timeTaken = measureTimeRadix(RadixSort, tab, n, k);
            printf("Time for Radix sort (Best Case): %.6f seconds\n", timeTaken);
        } else if (choice == '5') {
            generateBestCaseArray(tab, n);
            double timeBestCase = measureTimeQuick(quickSort, tab, 0, n - 1, partitionBestCase);
            printf("Time taken to sort (Best Case): %.6f seconds\n", timeBestCase);
        } else if (choice == '6') {
            time = measureTime(heapSort, B, n);
            printf("Time for gnomeSort (Best case): %.6f seconds\n", time);
        }

        // Worst case: reversed array
        generateReverseSortedArray(A, n);
        for (int i = 0; i < n; i++) {
            B[i] = A[i];
        }


        time = 0.0;
        if (choice == '1') {
            time = measureTime(BubbleSort, A, n);
            printf("Time for BubbleSort (Worst case): %.6f seconds\n", time);
        } else if (choice == '2') {
            time = measureTime(BubbleSortOpt, B, n);
            printf("Time for BubbleSortOpt (Worst case): %.6f seconds\n", time);
        } else if (choice == '3') {
            time = measureTime(BubbleSortOpt, B, n);
            printf("Time for BubbleSortOpt (Worst case): %.6f seconds\n", time);
        } else if (choice == '3') {
            time = measureTime(gnomeSort, B, n);
            printf("Time for gnomeSort (Worst case): %.6f seconds\n", time);
        } else if (choice == '4') {
            generateWorstCaseArrayRadix(tab, n);
            int k = findMaxDigits(tab, n);
            printf("Number of digits (k): %d\n", k);
            double timeTaken = measureTimeRadix(RadixSort, tab, n, k);
            printf("Time for Radix sort (Worst Case): %.6f seconds\n", timeTaken);
        } else if (choice == '5') {
            generateWorstCaseArray(tab, n);
            double timeWorstCase = measureTimeQuick(quickSort, tab, 0, n - 1, partitionWorstCase);
            printf("Time taken to sort (Worst Case): %.6f seconds\n", timeWorstCase);
        } else if (choice == '6') {
            time = measureTime(heapSort, B, n);
            printf("Time for gnomeSort (Worst case): %.6f seconds\n", time);
        }

        free(A);
        free(B);
        free(tab);

        printf("****************************************************************************************************\n");

    } while (choice != 'q');

    printf("Exiting the program.\n");

    return 0;
}
