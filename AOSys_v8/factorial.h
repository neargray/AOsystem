#pragma once

double factorial(int n)

{
	if (n > 20) // ����20�Ľ׳��޷���ȷ����
		return -1;

	double result = 1;
	 
	for (int i = 1; i <= n; i++)
	{
		result *= i;
	}
	return result;
}

