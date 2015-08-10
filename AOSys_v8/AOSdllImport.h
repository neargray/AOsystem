#pragma once

#include "stdafx.h"
#include "afxdialogex.h"
#include <string>

#include "AOSystem_DataStructures.h"
#include "macroExtern.h"
#include "AOSys_v8.h"
#include "AOSys_v8Dlg.h"


// ����AOSystem.dllû�и���ͷ�ļ���ֻ����ʽ����
// WFS_32.dll��ʽ����

typedef void(*SYNCCALLBACK)();

// ���붯̬���ӿ���
HINSTANCE hDll = LoadLibrary(TEXT("D:\\externLib\\AOS\\AOSystem.dll"));

// ����ָ��
typedef int(*DLL_AOS_Initialize)(int);
typedef char*(*DLL_AOS_GetInfoOnDevices)(void);
typedef int(*DLL_AOS_GetVarAddress)(unsigned long, void**);
typedef int(*DLL_AOS_SetVarAddress)(unsigned long, void*);
typedef int(*DLL_AOS_Callibration)(SYNCCALLBACK);
typedef void(*DLL_DM_SetVoltageFrame)(void);
typedef int(*DLL_DM_SetSpatialFrame)(void);
typedef void(*DLL_DM_SetQuadraticCoeffAndMaxV)(double coeff[], double maxVoltage);
typedef int(*DLL_AOS_Close)(void);


// ����AOSystem.dll�еĺ���

// ��ʼ��DM�豸
DLL_AOS_Initialize P_AOS_Initialize = (DLL_AOS_Initialize)GetProcAddress(hDll, "AOS_Initialize");

// ����һ��charָ�룬����DM��WFS�豸��Ϣ
DLL_AOS_GetInfoOnDevices P_AOS_GetInfoOnDevices = (DLL_AOS_GetInfoOnDevices)GetProcAddress(hDll, "AOS_GetInfoOnDevices");

// ����AOSystem���ݽṹ���ַ
DLL_AOS_GetVarAddress P_AOS_GetVarAddress = (DLL_AOS_GetVarAddress)GetProcAddress(hDll, "AOS_GetVarAddress");

// Ϊ���ݽṹ������һ�����ص�ַ��locally defined memory address��
DLL_AOS_SetVarAddress P_AOS_SetVarAddress = (DLL_AOS_SetVarAddress)GetProcAddress(hDll, "AOS_SetVarAddress");

// ΪDM׼��ȱʡֵ
DLL_AOS_Callibration P_AOS_Callibration = (DLL_AOS_Callibration)GetProcAddress(hDll, "AOS_Callibration");

// ʹ��displacement������DM
DLL_DM_SetVoltageFrame P_DM_SetVoltageFrame = (DLL_DM_SetVoltageFrame)GetProcAddress(hDll, "DM_SetVoltageFrame");

// ʹ��nm-Vӳ�䣬����DM
DLL_DM_SetSpatialFrame P_DM_SetSpatialFrame = (DLL_DM_SetSpatialFrame)GetProcAddress(hDll, "DM_SetSpatialFrame");

// ����nm-Vӳ��ϵ��������ѹ
DLL_DM_SetQuadraticCoeffAndMaxV P_DM_SetQuadraticCoeffAndMaxV =
(DLL_DM_SetQuadraticCoeffAndMaxV)GetProcAddress(hDll, "DM_SetQuadraticCoeffAndMaxV");

// �ر��豸
DLL_AOS_Close P_AOS_Close = (DLL_AOS_Close)GetProcAddress(hDll, "AOS_Close");


