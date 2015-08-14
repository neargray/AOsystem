#pragma once

// ����Ĵ��빫ʽ����ref:WOVC@60����Ӧ��matlab����Ϊzernike.m���ѱ�����solutionĿ¼��
// C++��Matlab����Աȣ��鿴CppMatlabCompare.m���룬�ѱ�����solutionĿ¼��

#include <cmath>
#include <iostream>
#include <vector>
#include <assert.h>		// for assert()

#include "factorial.h"



extern int init_2dVector(std::vector<std::vector<double>>&vectordata, const int row, const int col);
extern int release_2dVector(std::vector<std::vector<double>>&vectordata, const int row);


#define M_PI  3.1415926 

// grid��AOSys_v8Dlg.cpp�м���һ���жϣ���Ϊȫ�ֱ���������������
#define  GRID 29  // ������Ϊ29������WFS�ӿ׾���Ŀ������  �����Ҫ������


#pragma region //## C���ĺ����𽥷������ã��𽥲���C++���ĺ���
void writeZernikeMFC(char zernikePath[], double zernikeMatrix[][GRID]);
void writePupil(char pupilPath[], double pupil[][GRID]);
#pragma endregion //## C���ĺ����𽥷������ã��𽥲���C++���ĺ���




int zernike(const int n, const int m,		// Zernike��n��m
	int grid,						// �������񣬷�ӳ����x[]�Ĵ�С��ȫ�ֱ���, gridIndex��ֵ��������
	const double diameter,					// ��ͫ��ֱ�������߽й�һ��ֱ��
	std::vector<std::vector<double>>& zernikeMatrix,			// ���أ�zernike���׾���ȫ�ֱ���
	std::vector<std::vector<double>>& pupil,					// ���أ���ͫ����ȫ�ֱ���
	const double coordMoveX,
	const double coordMoveY
	)
{
	// ��ʼ��
	int arraySize = grid;	// 0��ʾ12x12������1��ʾ29x29����
	double Nnm = 0;
	int Imax = arraySize;
	int Jmax = arraySize;
	double rho = 0;
	double radius = diameter / 2;
	double theta = 0;

	// ��ʼ��pupil��zernikeMatrix��������
	init_2dVector(pupil,arraySize,arraySize);
	init_2dVector(zernikeMatrix, arraySize, arraySize);


	// ʹ�ö�����debug������Ҫȷ��vector�Ĵ�С�Ѿ�������ʼ��
	assert(pupil.size() == arraySize);
	assert(pupil[1].size() == arraySize);
	assert(zernikeMatrix.size() == arraySize);
	assert(zernikeMatrix[1].size() == arraySize);

	// ʹ�ô����grid��diameter��ʼ������һά��������
	std::vector<double> xArray(arraySize);
	std::vector<double> yArray(arraySize);

	// ��ʼ�������������飬���������WFS��DM���������
	for (int i = 0; i < arraySize; ++i)
		xArray[i] = -diameter / 2 + coordMoveX + i * diameter / (arraySize - 1);
	for (int i = 0; i < arraySize; ++i)
		yArray[i] = -diameter / 2 + coordMoveY + i * diameter / (arraySize - 1);


	// д���ļ���У��һ�½���Ƿ���ȷ
	write_1d_File("D:\\externLib\\AOS\\Output\\xArray.txt", xArray);
	write_1d_File("D:\\externLib\\AOS\\Output\\yArray.txt", yArray);


	// �����ͫ����
	// ʹ��std::vector�������﷨
	for (int i = 0; i < Imax; ++i)
		for (int j = 0; j < Jmax; ++j)
		{
			// �����׼ӹ�ͫ
			//pupil[i][j] = (sqrt(pow(xArray[i], 2) + pow(yArray[j], 2)) <= radius) ? 1 : 0;

			// �����ײ��ӹ�ͫ
			pupil[i][j] = 1;

		}

	// д���ļ���У��һ�½���Ƿ���ȷ
	write_2d_File("D:\\externLib\\AOS\\Output\\pupilData.txt", pupil);

	// Zernike��ʽ�Ĺ�һ��ϵ��
	Nnm = sqrt(2 * (n + 1) / (1 + (m == 0)));

	// ����zernike����
	// ʹ��std::vector�������﷨
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

				// ����ط����ܻᷢ��int��double��ת�����
				for (int s = 0; s <= 0.5*(n - abs(m)); ++s)
					zernikeMatrix[i][j] = zernikeMatrix[i][j] + pow(-1, s)*factorial(n - s)*pow((rho / radius), n - 2 * s) / (factorial(s)*
					factorial(0.5*(n + abs(m)) - s)*factorial(0.5*(n - abs(m)) - s));

				zernikeMatrix[i][j] = pupil[i][j] * Nnm*zernikeMatrix[i][j] * ((m >= 0)*cos(m*theta) - (m < 0)*sin(m*theta));
			}
	}



	// ����ÿ��pupil���׶�Ҫ�������������㣬����ÿ�ζ�����push����������ǰҪpop
	for (int i = 0; i < arraySize; ++i)
		pupil.pop_back();

	return 1;
}



#pragma region //## C���ĺ����𽥷������ã��𽥲���C++���ĺ���
// д��zernike����
void writeZernikeMFC(char zernikePath[], double zernikeMatrix[][GRID])
{
	FILE* fp;

	fp = fopen(zernikePath, "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���zernikeMatrixMFC�ļ� ��"), _T("д��״̬"), MB_OK);
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

// д��pupil����
void writePupil(char pupilPath[], double pupil[][GRID])
{
	FILE* fp;

	fp = fopen(pupilPath, "w");
	if (!fp)
	{
		::MessageBox(NULL, _T("�޷���pupilMFC�ļ� ��"), _T("д��״̬"), MB_OK);
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
#pragma endregion //## C���ĺ����𽥷������ã��𽥲���C++���ĺ���


