#include<iostream>
#include <Windows.h>
#include"Header.h"
#include <fstream>
using namespace std;
using namespace pushingflow;
int main()
{
    ifstream file("d:\\text.txt");
    string line; int size;
    if (!file.is_open()) // If the file cannot be opened.
        cout << "The file cannot be opened!" << endl;
    else
    {
        getline(file, line);
        size = atoi(line.c_str());
        int** Matrix = new int* [size];//Creation of a matrix of ways.
        for (int i = 0; i < size; i++)
            Matrix[i] = new int[size];
        char* tops = new char[size];//Creating an array of tops
        matrixentry(file, Matrix, size, tops);
        int** matrixflow = new int* [size];//flow matrix creation
        for (int i = 0; i < size; i++)
            matrixflow[i] = new int[size];
        algorithm(Matrix, matrixflow, size);
        matrixoutput(Matrix, size);
        matrixoutput(matrixflow, size);
    }
    return 0;
}