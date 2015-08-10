#pragma once

double factorial(int n)

{
	if (n > 20) // 大于20的阶乘无法正确计算
		return -1;

	double result = 1;
	 
	for (int i = 1; i <= n; i++)
	{
		result *= i;
	}
	return result;
}

