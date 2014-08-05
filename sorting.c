/* By VVayne Shu */

/*------includes---------*/
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

/*-------Algorithms-------*/


void merge(int *arr, int min, int mid, int max){
  int index1,index2;
  int numIn1 = mid - min +1; 
  int numIn2 = max - mid; 
  int arr1 [numIn1+1]; //Plus 1 to include large number at end of array so we know when array is empty. 
  int arr2 [numIn2+1];
  for(index1 = 0; index1 < numIn1; index1++){
    arr1[index1] = arr[min+index1-1];
  }
  for(index2 = 0; index2 <numIn2; index2++){
    arr2[index2] = arr[mid+index2];
  }

  arr1[numIn1+1] = INFINITY;
  arr2[numIn2+1] = INFINITY;

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
  printNumArray(arr,max+1);
  if(min < max){
    int mid = (max - min)/2;
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
    return menu();   
  }
}

void printNumArray(int* arr,int count){
  for(int i = 0; i < count; i++) printf("%d ",arr[i]);
  puts("");
}

void setArrAndInputFile(char* arg, int* arr,int* count){
  *count = 0;
  FILE* d;
  d = fopen(arg,"r");
  int arrIndex = 0;
    while(fscanf(d,"%d",&(arr[arrIndex])) != EOF){                                  //while(!feof(d)) this is not good style because of of feof interacts with FILE*
    arrIndex++;
    (*count)++;
  }
  fclose(d);
}

/*--------Main ------*/
int main( int argc, char*argv[]){
  int arr[50]; 
  int count;
  setArrAndInputFile(argv[1],arr,&count);
  printNumArray(arr,count);
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
  printNumArray(arr,count);
  return 0; 
}
