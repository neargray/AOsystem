#pragma once

// 这里的代码公式依据ref:WOVC@60，对应的matlab代码为zernike.m，已保存在solution目录下
// C++与Matlab结果对比，查看CppMatlabCompare.m代码，已保存在solution目录下

#include <cmath>
#include <iostream>
#include <vector>
#include <assert.h>		// for assert()

#include "factorial.h"



extern int init_2dVector(std::vector<std::vector<double>>&vectordata, const int row, const int col);
extern int release_2dVector(std::vector<std::vector<double>>&vectordata, const int row);


#define M_PI  3.1415926 

// grid在AOSys_v8Dlg.cpp中加入一个判断，作为全局变量，传到这里来
#define  GRID 29  // 网格数为29，这是WFS子孔径数目决定的  这个宏要被废弃


#pragma region //## C风格的函数逐渐废弃不用，逐渐采用C++风格的函数
void writeZernikeMFC(char zernikePath[], double zernikeMatrix[][GRID]);
void writePupil(char pupilPath[], double pupil[][GRID]);
#pragma endregion //## C风格的函数逐渐废弃不用，逐渐采用C++风格的函数




int zernike(const int n, const int m,		// Zernike的n与m
	int grid,						// 根据网格，反映数组x[]的大小，全局变量, gridIndex的值传到这来
	const double diameter,					// 光瞳的直径，或者叫归一化直径
	std::vector<std::vector<double>>& zernikeMatrix,			// 返回，zernike基底矩阵，全局变量
	std::vector<std::vector<double>>& pupil,					// 返回，光瞳矩阵，全局变量
	const double coordMoveX,
	const double coordMoveY
	)
{
	// 初始化
	int arraySize = grid;	// 0表示12x12的网格，1表示29x29网格
	double Nnm = 0;
	int Imax = arraySize;
	int Jmax = arraySize;
	double rho = 0;
	double radius = diameter / 2;
	double theta = 0;

	// 初始化pupil与zernikeMatrix两个矩阵
	init_2dVector(pupil,arraySize,arraySize);
	init_2dVector(zernikeMatrix, arraySize, arraySize);


	// 使用断言来debug，这里要确保vector的大小已经经过初始化
	assert(pupil.size() == arraySize);
	assert(pupil[1].size() == arraySize);
	assert(zernikeMatrix.size() == arraySize);
	assert(zernikeMatrix[1].size() == arraySize);

	// 使用传入的grid与diameter初始化两个一维坐标容器
	std::vector<double> xArray(arraySize);
	std::vector<double> yArray(arraySize);

	// 初始化两个坐标数组，在这里调整WFS与DM的相对坐标
	for (int i = 0; i < arraySize; ++i)
		xArray[i] = -diameter / 2 + coordMoveX + i * diameter / (arraySize - 1);
	for (int i = 0; i < arraySize; ++i)
		yArray[i] = -diameter / 2 + coordMoveY + i * diameter / (arraySize - 1);


	// 写入文件，校验一下结果是否正确
	write_1d_File("D:\\externLib\\AOS\\Output\\xArray.txt", xArray);
	write_1d_File("D:\\externLib\\AOS\\Output\\yArray.txt", yArray);


	// 计算光瞳矩阵
	// 使用std::vector的数组语法
	for (int i = 0; i < Imax; ++i)
		for (int j = 0; j < Jmax; ++j)
		{
			// 给基底加光瞳
			//pupil[i][j] = (sqrt(pow(xArray[i], 2) + pow(yArray[j], 2)) <= radius) ? 1 : 0;

			// 给基底不加光瞳
			pupil[i][j] = 1;

		}

	// 写入文件，校验一下结果是否正确
	write_2d_File("D:\\externLib\\AOS\\Output\\pupilData.txt", pupil);

	// Zernike公式的归一下系数
	Nnm = sqrt(2 * (n + 1) / (1 + (m == 0)));

	// 计算zernike矩阵
	// 使用std::vector的数组语法
	if (0 == n)
	{
		for (int i = 0; i < Imax; ++i)
			for (int j = 0; j < Jmax; ++j)
			{
				zernikeMatrix[i][j] = 0;
			}

	}
	else
	{
		for (int i = 0; i < Imax; ++i)
			for (int j = 0; j < Jmax; ++j)
			{
				rho = sqrt(pow(xArray[i], 2) + pow(yArray[j], 2));

				if (xArray[i] >= 0 && yArray[j] >= 0 || xArray[i] >= 0 && yArray[j] < 0)
					theta = atan(yArray[j] / (xArray[i] + 1e-20));
				else
					theta = M_PI + atan(yArray[j] / (xArray[i] + 1e-20));

				// 这个地方可能会发生int到double的转换误差
				for (int s = 0; s <= 0.5*(n - abs(m)); ++s)
					zernikeMatrix[i][j] = zernikeMatrix[i][j] + pow(-1, s)*factorial(n - s)*pow((rho / radius), n - 2 * s) / (factorial(s)*
					factorial(0.5*(n + abs(m)) - s)*factorial(0.5*(n - abs(m)) - s));

				zernikeMatrix[i][j] = pupil[i][j] * Nnm*zernikeMatrix[i][j] * ((m >= 0)*cos(m*theta) - (m < 0)*sin(m*theta));
			}
	}



	// 由于每个pupil基底都要在这个函数里计算，不能每次都运行push，函数结束前要pop
	for (int i = 0; i < arraySize; ++i)
		pupil.pop_back();

	return 1;
}



#pragma region //## C风格的函数逐渐废弃不用，逐渐采用C++风格的函数
// 写入zernike矩阵
void writeZernikeMFC(char zernikePath[], double zernikeMatrix[][GRID])
{
	FILE* fp;

	fp = fopen(zernikePath, "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开zernikeMatrixMFC文件 ！"), _T("写入状态"), MB_OK);
	}

	for (int i = 0; i < GRID; ++i)
	{
		for (int j = 0; j < GRID; ++j)
		{
			fprintf(fp, "%f", zernikeMatrix[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);

}

// 写入pupil矩阵
void writePupil(char pupilPath[], double pupil[][GRID])
{
	FILE* fp;

	fp = fopen(pupilPath, "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("无法打开pupilMFC文件 ！"), _T("写入状态"), MB_OK);
	}

	for (int i = 0; i < GRID; ++i)
	{
		for (int j = 0; j < GRID; ++j)
		{
			fprintf(fp, "%f", pupil[i][j]);
			fprintf(fp, "\t\t");
		}
		fputc('\n', fp);
	}

	fclose(fp);
}
#pragma endregion //## C风格的函数逐渐废弃不用，逐渐采用C++风格的函数


