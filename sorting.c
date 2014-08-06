/* By VVayne Shu

Sorting algorithms in C.   
Sorts up to the first 100 numbers of an input. Currently supports insert and merge sort so far

To-Do: 
Heap Sort, Selection Sort, Bubble Sort
Add time measures to each sorting algorithm to compare quickness. 
Explore different methods of implementing each sort. */

/*------includes---------*/
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

/*-------Algorithms-------*/

void printNumArray(int*, int, int);

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
  puts("Choose your sorting algorithm:");
  scanf("%d",&choice);
  if((choice | 1) == 1) return choice;
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
  setArrAndInputFile(argv[1],arr,&count);
  puts("Initial Array: ");
  printNumArray(arr,0,count-1);
  int choice = menu(); 
  switch(choice){
  case 0:
    insertSort(arr,count);
    break;
  case 1:
    mergeSort(arr,0,count-1);
    break;
  default:
    break;
  }
  printNumArray(arr,0,count-1);
  return 0; 
}
