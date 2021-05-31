#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Header.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace pushingflow;
namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(correct_entry)
		{
			ifstream file("C:\\Users\\avani\\source\\repos\\AISD\\course\\Project1\\Project1\\testtext.txt");
			string line; int size;
			getline(file, line);
			size = atoi(line.c_str());
			char* tops = new char[size];
			int** Matrix = new int* [size];
			for (int i = 0; i < size; i++)
				Matrix[i] = new int[size];
			int** matrixflow = new int* [size];//flow matrix creation
			for (int i = 0; i < size; i++)
				matrixflow[i] = new int[size];
			matrixentry(file, Matrix, size, tops);
			char topstest[3] = { 'A', 'S', 'E' };
			int Matrixtest[3][3] = { {0,5,0},{0,0,8},{0,0,0} };
			for (int i = 0; i < size; i++)
			{
				Assert::IsTrue(tops[i] == topstest[i]);
				for (int j = 0; j < size; j++)
				{
					Assert::AreEqual(Matrix[i][j], Matrixtest[i][j]);
				}
			}
		}
		TEST_METHOD(correct_findatop)
		{
			char topstest[3] = { 'A', 'S', 'E' };
			char top = 'S';
			int sizetops = 3;
			Assert::AreEqual(findatop(top, topstest, sizetops), 1);
		}
		TEST_METHOD(incorrect_findatop)
		{
			char topstest[3] = { 'A', 'S', 'E' };
			char top = 'B';
			int sizetops = 3;
			Assert::AreEqual(findatop(top, topstest, sizetops), -1);
		}

		TEST_METHOD(correct_algorithm)
		{
			ifstream file("C:\\Users\\avani\\source\\repos\\AISD\\course\\Project1\\Project1\\testtext.txt");
			string line; int size;
			getline(file, line);
			size = atoi(line.c_str());
			char* tops = new char[size];
			int** Matrix = new int* [size];
			for (int i = 0; i < size; i++)
				Matrix[i] = new int[size];
			int** matrixflow = new int* [size];//flow matrix creation
			for (int i = 0; i < size; i++)
				matrixflow[i] = new int[size];
			matrixentry(file, Matrix, size, tops);
			int Matrixtest[3][3] = { {0,5,0},{0,0,8},{0,0,0} };
			int flowtest = 5;
			int matrixflowtest[3][3] = { {0,5,0},{-5,0,5},{0,-5,0} };
			int flow = algorithm(Matrix, matrixflow, size);
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					Assert::AreEqual(matrixflow[i][j], matrixflowtest[i][j]);
				}
			}
			Assert::AreEqual(flow, flowtest);
		}
	};
}
