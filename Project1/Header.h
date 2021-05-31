#pragma once
#include<iostream>
#include< iomanip >
#include <fstream>
#include<string>
using namespace std;
namespace pushingflow
{
    void matrixoutput(int** Matrix, int size)
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                cout << setw(4) << Matrix[i][j];
                if (j == size - 1)
                    cout << endl;
            }
        cout << endl;
    }
    void push(int u, int v, int** f, int* e, int** c, int n)//Push the flow trough the top
    {
        int d = min(e[u], c[u][v] - f[u][v]);
        f[u][v] += d;
        f[v][u] = -f[u][v];
        e[u] -= d;
        e[v] += d;
    }

    void lift(int u, int* h,int** f, int** c, int n)//Raising the top
    {
        int d = 1000000;
        for (int i = 0; i < n; i++)
            if (c[u][i] - f[u][i] > 0)
                d = min(d, h[i]);
        if (d == 1000000)
            return;
        h[u] = d + 1;
    }
    int overflow(int* e,int n) //determining the number of the overflow top
    {
        int i=1;
        while ((e[i] <= 0) && (i < n-1))
            i++;
        if (i == n - 1)
            return -1;
        else
            return i;
    }
    int algorithm(int** c, int** f, int n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                f[i][j] = 0;
        for (int i = 1; i < n; i++)
        {
            f[0][i] = c[0][i];
            f[i][0] = -c[0][i];
        }
        int* h = new int[n];
        h[0] = n;
        for (int i = 1; i < n; i++) h[i] = 0;
        int* e = new int[n];
        e[0] = 0;
        for (int i = 1; i < n; i++) e[i] = f[0][i];
        int i;
        while((i=overflow(e,n))!=-1)
        {
            int j=0;
            while (((c[i][j] - f[i][j] <= 0) || (h[i] != h[j] + 1)) && (j < n))
                j++;
            if (j < n)
                push(i, j, f, e, c,n);
            else
                lift(i, h, f, c,n);
        }
        int flow = e[n - 1];
        cout << "Maximum flow: "<< flow <<endl;
        return flow;
    }
    int findatop( char top, char*tops, int sizetops)
    {
        for (int i = 0; i < sizetops; i++)
        {
            if (top == tops[i])
                return i;
        }
        return -1;
    }
    void matrixentry(ifstream& file, int** Matrix, int size, char* tops)
    {
        string line; string selection;
        int sizetops = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                Matrix[i][j] = 0;
        while (!file.eof())
        {
            getline(file, line);
            int firstspace = line.find(" ");//define the names of the tops
            int secondspace = line.find(" ", firstspace + 1);
            selection=line.substr(0, firstspace);//We separate cities and paths.
            char firstop = selection[0];
            selection=line.substr(firstspace + 1, secondspace - firstspace - 1);
            char secondtop = selection[0];
            selection = line.substr(secondspace + 1);
            int cost=atoi(selection.c_str());
            if (findatop(firstop, tops, sizetops) == -1)//If you have not found a top in the list, then add a new one.
            {
                tops[sizetops] = firstop; sizetops++;
            }
            if (findatop(secondtop, tops, sizetops) == -1)
            {
                tops[sizetops] = secondtop; sizetops++;
            }
            Matrix[findatop(firstop, tops, sizetops)][findatop(secondtop, tops, sizetops)] = cost;
        }
    }
}
