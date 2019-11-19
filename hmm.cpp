#include <iostream>

using namespace std;

// 1 SYMBOL RIGHT ARROW
// 2 SYMBOL UP ARROW
// 3 SYMBOL UP_DOWN ARROW
// 4 SYMBOL DOWN ARROW

// modify here
int matSF [] = {1, 2, 3, 4};
const int N_matSF = 4;

int matV [] = {1, 2, 3, 4, 5, 6, 7, 8};
const int K_matV = 8;

int matSI[] = {1, 3, 4};
const int N_matSI = 3;

int matObserve [] = {1, 2, 4, 6};
const int T_matObserve = 4;

float forward(float A[][N_matSF], float B[][K_matV])
{
	// Step 1: calculate alpha zero
	float alpha [T_matObserve][N_matSF] = {};
	float keadAwal = 0;

	int t = 0;
	for(int i = 0; i < N_matSF; i++)
	{
		keadAwal = 0;

		//calculate initial conditions
		for(int check = 0; check < N_matSI; check++)
		{
			int k = i + 1;
			if( k == matSI[check])
			{
				keadAwal = 1./N_matSI;
				break;
			}
		}

		alpha[t][i] = keadAwal * B[i][matObserve[t]];
		printf("alpha[%d][%d] = %f\n", t, i, alpha[t][i]);
	}
	cout << endl;

	// Step 2: calculate all the alpha
	for(t = 1; t < T_matObserve; t++)
	{
		for(int j = 0; j < N_matSF; j++)
		{
			for(int i = 0; i < N_matSF; i++)
			{
				alpha[t][j] = alpha[t][j] + alpha[t-1][i]*A[i][j];
			}
			alpha[t][j]*=B[j][matObserve[t]];
			printf("alpha[%d][%d] = %f\n", t, j, alpha[t][j]);
		}
		printf("\n");
	}
	printf("\n");

	// Step 3: calculate the result
	float result = 0;

	for(int i = 0; i < N_matSF; i++)
	{
		result+=alpha[t-1][i];
	}
	printf("Result = %f\n", result);
	return result;
}



int main(int argc, char **argv)
{
	// modify here the matA and matB
	// Matrix of probability in every state Q
	float matA [N_matSF][N_matSF] = 
	{
		{0, .5, 0, .5},
		{.33333, .33333, .33333, 0},
		{.25, .5, 0, .25},
		{.25, .25, .5, 0}
	};

	float matB [N_matSF][K_matV] = 
	{
		{.1428571, 0, .4285714, 0, .1428571, .1428571, 0, .1428571},
		{0, .1428571, .1428571, 0, .4285714, 0, .1428571, .1428571},
		{.2, .1, .1, .1, .2, .1, .1, .1},
		{.4285714, 0, .1428571, .1428571, 0, .1428571, .1428571}
	};

	float result = forward(matA, matB);

	return 0;
}
