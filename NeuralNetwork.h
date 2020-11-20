#pragma once
#ifndef NN_H
#define NN_H
class NeuralNetwork
{
public:
	NeuralNetwork();
	float** inputs();
	void GA();
	void output();
	float sigmoid(float z);
	float sigmoid_d(float z);
	

private:
	float w1, w2, b;
	float** m_dataset;
	float** m_weights_bias;
};

#endif // !NN_H

