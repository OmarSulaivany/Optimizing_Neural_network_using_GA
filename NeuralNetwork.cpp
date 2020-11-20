#include "NeuralNetwork.h"
#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;
NeuralNetwork::NeuralNetwork()
{

	this->w1 = 0;
	this->w2 = 0;
	this->b = 0;

	srand(static_cast <float> (time(0)));

	this->m_weights_bias = new float* [10];

	cout << "Weights and biases table \n W1\t\tW2\t\tb\n";

	float weight_b[10][3] = {
		{-0.349408,-0.101453,-1.20535},
		{0.231229,0.411305,-0.191918},
		{-0.406422,-1.05201,0.835551},
		{1.06898,-0.56208,-1.14504},
		{-0.167745,0.807349,-0.612013},
		{1.4544,0.851544,-1.19143},
		{-0.316567,1.23916,0.772799},
		{1.35002,0.746185,1.1885},
		{-0.0721524,1.63313,-1.62263},
		{1.67245,-0.119644,0.94616},
	};

	for (unsigned i = 0; i < 10; ++i)
	{
		this->m_weights_bias[i] = new float[3];
		for (unsigned j = 0; j < 3; ++j)
		{
			//this->m_weights_bias[i][j] = -2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - (-2))));
			this->m_weights_bias[i][j] = weight_b[i][j];
			cout << this->m_weights_bias[i][j];
			cout << ",";
		}
		cout<<endl;
	}
}

float** NeuralNetwork::inputs()
{
	unsigned rows = 10, columns = 3;

	float data[10][3] = {
		{3,1.5,         1},
		{4, 1.5,        1},
		{2, 1,          0},
		{3, 0,          0},
		{2, 2,          1},
		{3, 1,          1},
		{2, 0.5,        0},
		{0, 2,          0},
		{5.5, 1,        1},
		{1, 1,          0} };

	this->m_dataset = new float* [rows];
	cout << "\nPopulation table \n X1		X2	       Target\n";
	for (unsigned i = 0; i < rows; ++i)
	{
		this->m_dataset[i] = new float[columns];
		for (unsigned j = 0; j < columns; ++j)
		{
			this->m_dataset[i][j] = data[i][j];
			cout << this->m_dataset[i][j] << "		";
		}
		cout << endl;
	}

	return this->m_dataset;

	}

float NeuralNetwork::sigmoid(float z)
{
	return 1 / (1 + exp(-z));
}
float NeuralNetwork::sigmoid_d(float z)
{
	return sigmoid(z) * (1 - sigmoid(z));
}

void NeuralNetwork::GA()
{

	float f, fitness_function,smallest;
	float** solutions;
	
	solutions = new float* [10];
	for (unsigned generation = 0; generation < 5; ++generation)
	{
		for (unsigned i = 0; i < 10; ++i)
		{
			solutions[i] = new float[4];
			for (unsigned j = 0; j < 3; ++j)
				solutions[i][j] = this->m_weights_bias[i][j];
			f = sigmoid(this->m_dataset[i][0] * solutions[i][0] + this->m_dataset[i][1] * solutions[i][1] + solutions[i][2]);
			fitness_function = pow((f - this->m_dataset[i][2]), 2);
			solutions[i][3] = fitness_function;

		}

		cout << endl;
		fitness_function = 0;
		for (unsigned a = 0; a < 10; ++a)
		{
			for (unsigned b = 0; b < 4; ++b)
				//cout << solutions[a][b] << "  ||  ";
			this->w1 += solutions[a][0];
			this->w2 += solutions[a][1];
			this->b += solutions[a][2];
			fitness_function += solutions[a][3];
			//cout << endl;
		}
		this->w1 /= 10;
		this->w2 /= 10;
		this->b /= 10;
		fitness_function /= 10;
		

		float s0, s1, s2, s3;
		for (unsigned c = 0; c < 10; ++c)
		{
			for (unsigned d = c + 1; d < 10; ++d)
				if (solutions[c][3] > solutions[d][3])
				{
					s0 = solutions[c][0];
					s1 = solutions[c][1];
					s2 = solutions[c][2];
					s3 = solutions[c][3];

					solutions[c][0] = solutions[d][0];
					solutions[c][1] = solutions[d][1];
					solutions[c][2] = solutions[d][2];
					solutions[c][3] = solutions[d][3];

					solutions[d][0] = s0;
					solutions[d][1] = s1;
					solutions[d][2] = s2;
					solutions[d][3] = s3;
				}
		}

	/*	for (unsigned e = 0; e < 10; ++e)
		{
			for (unsigned f = 0; f < 4; ++f)
				cout << solutions[e][f] << "||";
			cout << endl;
		}*/


		unsigned a = 4, b = 0;
		for (unsigned h = 0; h < 3; ++h)
		{

			for (unsigned k = h; k < 3; ++k)
			{

				solutions[b + a][0] = solutions[h][0] * 0.1 ;

				solutions[b + a][1] = solutions[h][1] * 0.50 ;

				solutions[b + a][2] = solutions[h + 1][2] ;

				solutions[b + a][3] = solutions[h][3];


				++b;
			}
			a += b;
			b = 0;


			
		}

		cout << "\n\nGeneration "<<generation<<endl<<endl;

		for (unsigned l = 0; l < 10; ++l)
		{
			for (unsigned m = 0; m < 4; ++m)
				cout << solutions[l][m] << "||";
			cout << endl;
		}
		for (unsigned r = 0; r < 10; ++r)
			for (unsigned s = 0; s < 4; ++s)
				this->m_weights_bias[r][s] = solutions[r][s];
		cout << "AV. Fitness function = " << fitness_function << endl << endl;
	}
}

void NeuralNetwork::output()
{

	float x1, x2, out, predicted;
	x1 = 0;
	x2 = 0;

	out = sigmoid(x1 * this->w1 + x2 * this->w2 + this->b);
	cout << "Output = " << out;
}