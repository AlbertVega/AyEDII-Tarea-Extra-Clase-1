#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdio.h>
using namespace std;

int* ptr;
vector<int> array1D;
int row;
int col;

class Array{
    private: 
        int size;
        vector<int> array;
    public:
        Array(int, vector<int>);
        int* Paginate();
};

//constructor
Array::Array(int _size, vector<int> _array){
    size = _size;
    array = _array;
}

int* Array::Paginate(){
    ptr = (int *) malloc(6 * (256 * sizeof(int)));
    for (size_t i = 0; i<array.size(); i++){
        ptr[i] =  array[i];
        //cout<<ptr[i]<<"\n";
    }
    return 0;
}


//Copy the csv to an array
int CopyCSV(string filename){
    
    ifstream in(filename);

    string line, field;

    vector< vector<string>> array;  // the 2D array
    vector<string> v;                // array of values for one line only

    while ( getline(in,line) )    // get next line in file
    {
        v.clear();
        stringstream ss(line);

        while (getline(ss,field,','))  // break line into comma delimitted fields
        {
            v.push_back(field);  // add each field to the 1D array
        }

        array.push_back(v);  // add the 1D array to the 2D array
    }

    row = array.size();
    col = v.size();
    
    for(size_t i = 0; i < row; ++i){
        for(size_t j= 0; j < col; ++j){
            array1D.push_back(atoi(array[i][j].c_str()));
        }
    }
    Array arraytmp = Array(array1D.size(), array1D);
    arraytmp.Paginate();

    return 0;
}

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* Quick sort*/
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
}

void insertionSort(int arr[], int n) 
{ 
    int i, key, j; 
    for (i = 1; i < n; i++)
    { 
        key = arr[i]; 
        j = i - 1; 
  
        // Move elements of arr[0..i-1],  
        // that are greater than key, to one 
        // position ahead of their 
        // current position
        while (j >= 0 && arr[j] > key)
        { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n-1; i++)
    {
       
        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
        if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element
        // with the first element
        if(min_idx!=i)
            swap(&arr[min_idx], &arr[i]);
    }
}

void WriteCSV(string filename, int* Ptr){
    ofstream file;
    file.open(filename, ios::out);

    if (file.fail()){
        cout<<"no se pudo abrir el archivo";
        exit(1);
    }else{
        
        for (int i = 0; i<array1D.size(); i++){
            file<<Ptr[i]<<", ";
        }
    }
}

int main(int argc, char* argv[]){
    CopyCSV(argv[2]);
    /*for (int i = 0; i < argc; i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }*/
    string algoritmo = argv[4];
    if (algoritmo == "QS"){
        quickSort(ptr,0,array1D.size()-1);
        /*for (int i = 0; i<array1D.size(); i++){
        cout<<ptr[i]<<"\n";
        }*/
        WriteCSV(argv[6], ptr);

    }else if(algoritmo == "IS"){
        insertionSort(ptr, array1D.size());
        for (int i = 0; i<array1D.size(); i++){
        cout<<ptr[i]<<"\n";
        }
    }else if(algoritmo == "SS"){
        selectionSort(ptr, array1D.size());
        for (int i = 0; i<array1D.size(); i++){
        cout<<ptr[i]<<"\n";
        }
    }else{
        cout<<"selecione el algoritmo de ordenamiento";
    }
    
    return 0;
}