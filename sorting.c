/* By VVayne Shu

Sorting algorithms in C.   
Sorts up to the first 100 numbers of an input. Currently supports insert and merge sort so far

To-Do: 
Heap Sort, Selection Sort, Bubble Sort
Add time measures to each sorting algorithm to compare quickness. 
Explore different methods of implementing each sort. 

quicksort(A, i, k):
  if i < k:
    p := partition(A, i, k)
    quicksort(A, i, p - 1)
    quicksort(A, p + 1, k)


In-place partition in action on a small list. The boxed element is the pivot element, blue elements are less or equal, and red elements are larger.
Sorting the entire array is accomplished by calling quicksort(A, 1, length(A)). The partition operation is step 2 from the description in English, above. It can be defined as:

  // left is the index of the leftmost element of the subarray
  // right is the index of the rightmost element of the subarray (inclusive)
  // number of elements in subarray = right-left+1
  partition(array, left, right)
     pivotIndex := choose-pivot(array, left, right)
     pivotValue := array[pivotIndex]
     swap array[pivotIndex] and array[right]
     storeIndex := left
     for i from left to right - 1
         if array[i] ≤ pivotValue
             swap array[i] and array[storeIndex]
             storeIndex := storeIndex + 1
     swap array[storeIndex] and array[right]  // Move pivot to its final place
     return storeIndex

*/


/*------includes---------*/
#include <stdlib.h> 
#include <stdio.h> 
#include <math.h>
#include <time.h>

/*-------Algorithms-------*/

void printNumArray(int*, int, int);
void swap(int*, int ,int);
int partition(int *arr, int min, int max);

int choosePivot(int *arr, int min, int max){
  return (min+max)/2;
}


void quickSort(int *arr, int min, int max){
  if(min < max){
    int p;
    p = partition(arr,min,max);
    quickSort(arr,min,p-1);
    quickSort(arr,p+1,max);
  }

}

int partition(int *arr, int min, int max){
  int p = choosePivot(arr, min, max);
  int pivotValue = arr[p];
  swap(arr,p,max);
  int finalIndex = min;
  for(int c = min; c < max ; c++){
    if(arr[c] <= pivotValue){
      swap(arr,c,finalIndex);
      finalIndex++;
        }
      }
        swap(arr,finalIndex,max); 
        return finalIndex;
    } 

void swap(int *arr, int a, int b){
  int tempValue = arr[a];
  arr[a] = arr[b];
  arr[b] = tempValue;
}

void merge(int *arr, int min, int mid, int max){
  int index1,index2;
  int numIn1 = mid - min +1; 
  int numIn2 = max - mid; 
  int arr1 [numIn1+1]; //Plus 1 to include large number at end of array so we know when array is empty. 
  int arr2 [numIn2+1];
  for(index1 = 0; index1 < numIn1; index1++){
    arr1[index1] = arr[min+index1];
  }
  for(index2 = 0; index2 <numIn2; index2++){
    arr2[index2] = arr[mid+index2+1];
  }

  arr1[numIn1] = (int)INFINITY;
  arr2[numIn2] = (int)INFINITY;

  index1 = 0;
  index2 = 0;
  for(int z = min; z <= max; z++){
    if(arr1[index1] <= arr2[index2]){
      arr[z] = arr1[index1];
      index1++;
    }
    else{
      arr[z] = arr2[index2];
      index2++;
    }
  }
}

void mergeSort(int *arr, int min, int max){
  if(min < max){
    int mid = (max + min)/2;
    mergeSort(arr,min,mid);
    mergeSort(arr,mid+1,max);
    merge(arr,min,mid,max);
  }
}

 void insertSort(int *arr, int count){
   for(int j = 1; j < count; j++){
     int key = arr[j];
     int i = j-1; 
     while(i >=0 && arr[i] > key){
       arr[i+1] = arr[i];
       i = i-1; 
     }
     arr[i+1] = key; 
   }
 }

 /*--------Auxiliary --------*/

int menu(){
  int choice;
  puts("Insert: 0");
  puts("Merge: 1");
  puts("Quicksort 2");
  puts("Choose your sorting algorithm:");
  scanf("%d",&choice);
  if(choice < 3 && choice >= 0) return choice;
  else{ 
    puts("Not an option try again");
    while(fgetc(stdin) != '\n'); //manual flush of stdin because scanf does not read from stream if
    //format does not match. Without this, recursion goes forever. 
    return menu();   
  }
}

void printNumArray(int* arr,int start, int finish){
  for(int i = start; i <= finish; i++) printf("%d ",arr[i]);
  puts("");
}

void setArrAndInputFile(char* arg, int* arr,int* count){
  *count = 0;
  FILE* d;
  d = fopen(arg,"r");
  int arrIndex = 0;
    while(fscanf(d,"%d",&(arr[arrIndex])) != EOF){    //while(!feof(d)) this is not good style because of of feof interacts with FILE*
    arrIndex++;
    (*count)++;
    if(*count > 99) break; 
  }
  fclose(d);
}

/*--------Main ------*/
int main( int argc, char*argv[]){
  int arr[100]; 
  int count;
  // clock_t start, end;
  // double speed;
  setArrAndInputFile(argv[1],arr,&count);
  puts("Initial Array: ");
  printNumArray(arr,0,count-1);
  int choice = menu(); 
  //start = clock();
  switch(choice){
  case 0:
    insertSort(arr,count);
    break;
  case 1:
    mergeSort(arr,0,count-1);
    break;
  case 2:
    quickSort(arr,0,count-1);
  default:
    break;
  }
  // end = clock();
  // speed = (double)((end-start));
  // printf("Time:%f\n",speed);
  printNumArray(arr,0,count-1);
  return 0; 
}
