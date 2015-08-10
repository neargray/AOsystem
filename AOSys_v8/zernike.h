#pragma once

// 这里的代码公式依据ref:WOVC@60，对应的matlab代码为zernike.m，已保存在solution目录下
// C++与Matlab结果对比，查看CppMatlabCompare.m代码，已保存在solution目录下

#include <cmath>
#include <iostream>
#include <vector>
#include <assert.h>		// for assert()
#include "factorial.h"


#define M_PI  3.1415926 


int zernike(const int n, const int m,		// Zernike的n与m
	int grid,								// 根据网格，反映数组x[]的大小，全局变量, gridIndex的值传到这来
	const double diameter,					// 光瞳的直径，或者叫归一化直径
	std::vector<std::vector<double>>& zernikeMatrix,			// 返回，zernike基底矩阵，全局变量
	std::vector<std::vector<double>>& pupil,					// 返回，光瞳矩阵，全局变量
	const double coordMoveX,
	const double coordMoveY
	)
{
	// 初始化
	int arraySize = grid;	
	double Nnm = 0;
	int Imax = arraySize;
	int Jmax = arraySize;
	double rho = 0;
	double radius = diameter / 2;
	double theta = 0;

	// 为全局变量分配内存空间，调用一次zernike函数，就为全局变量重新分配一次内存空间
	zernikeMatrix.resize(arraySize);
	pupil.resize(arraySize);
	for (int index = 0; index < arraySize;++index)	
	{
		zernikeMatrix[index].resize(arraySize);
		pupil[index].resize(arraySize);
	}


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

	return 1;
}


