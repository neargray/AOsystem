#pragma once

#include "stdafx.h"
#include "afxdialogex.h"
#include <string>

#include "AOSystem_DataStructures.h"
#include "macroExtern.h"
#include "AOSys_v8.h"
#include "AOSys_v8Dlg.h"


// 由于AOSystem.dll没有给出头文件，只能显式调用
// WFS_32.dll隐式调用

typedef void(*SYNCCALLBACK)();

// 导入动态链接库句柄
HINSTANCE hDll = LoadLibrary(TEXT("D:\\externLib\\AOS\\AOSystem.dll"));

// 函数指针
typedef int(*DLL_AOS_Initialize)(int);
typedef char*(*DLL_AOS_GetInfoOnDevices)(void);
typedef int(*DLL_AOS_GetVarAddress)(unsigned long, void**);
typedef int(*DLL_AOS_SetVarAddress)(unsigned long, void*);
typedef int(*DLL_AOS_Callibration)(SYNCCALLBACK);
typedef void(*DLL_DM_SetVoltageFrame)(void);
typedef int(*DLL_DM_SetSpatialFrame)(void);
typedef void(*DLL_DM_SetQuadraticCoeffAndMaxV)(double coeff[], double maxVoltage);
typedef int(*DLL_AOS_Close)(void);


// 调用AOSystem.dll中的函数

// 初始化DM设备
DLL_AOS_Initialize P_AOS_Initialize = (DLL_AOS_Initialize)GetProcAddress(hDll, "AOS_Initialize");

// 返回一个char指针，包含DM与WFS设备信息
DLL_AOS_GetInfoOnDevices P_AOS_GetInfoOnDevices = (DLL_AOS_GetInfoOnDevices)GetProcAddress(hDll, "AOS_GetInfoOnDevices");

// 返回AOSystem数据结构体地址
DLL_AOS_GetVarAddress P_AOS_GetVarAddress = (DLL_AOS_GetVarAddress)GetProcAddress(hDll, "AOS_GetVarAddress");

// 为数据结构体设置一个本地地址（locally defined memory address）
DLL_AOS_SetVarAddress P_AOS_SetVarAddress = (DLL_AOS_SetVarAddress)GetProcAddress(hDll, "AOS_SetVarAddress");

// 为DM准备缺省值
DLL_AOS_Callibration P_AOS_Callibration = (DLL_AOS_Callibration)GetProcAddress(hDll, "AOS_Callibration");

// 使能displacement，驱动DM
DLL_DM_SetVoltageFrame P_DM_SetVoltageFrame = (DLL_DM_SetVoltageFrame)GetProcAddress(hDll, "DM_SetVoltageFrame");

// 使能nm-V映射，驱动DM
DLL_DM_SetSpatialFrame P_DM_SetSpatialFrame = (DLL_DM_SetSpatialFrame)GetProcAddress(hDll, "DM_SetSpatialFrame");

// 设置nm-V映射系数，最大电压
DLL_DM_SetQuadraticCoeffAndMaxV P_DM_SetQuadraticCoeffAndMaxV =
(DLL_DM_SetQuadraticCoeffAndMaxV)GetProcAddress(hDll, "DM_SetQuadraticCoeffAndMaxV");

// 关闭设备
DLL_AOS_Close P_AOS_Close = (DLL_AOS_Close)GetProcAddress(hDll, "AOS_Close");


