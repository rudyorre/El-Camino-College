#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

void fit(const vector<double>& training_x, const vector<double>& model_parameters, vector<double>& predicted_y)
{
	for (int i = 0; i < training_x.size(); i++)
	{
		predicted_y[i] = model_parameters[1] * training_x[i] + model_parameters[0];
	}
}

void update_weights(vector<double>& model_parameters, const vector<double>& cost_gradient, double learning_rate)
{
	model_parameters[0] -= learning_rate * cost_gradient[0];
	model_parameters[1] -= learning_rate * cost_gradient[1];
}

void calculate_cost(const vector<double>& predicted_y, const vector<double>& training_x,
	const vector<double>& training_y, vector<double>& cost_gradient)
{
	double gradient_intercept = 0;
	double gradient_slope = 0;

	for (int i = 0; i < training_x.size(); i++)
	{
		// partial derivative of cost function with respect to y-intercept (dC/dB)
		gradient_intercept += (predicted_y[i] - training_y[i]);
		// partial derivative of cost function with respect to slope (dC/dM)
		gradient_slope += ((predicted_y[i] - training_y[i]) * training_x[i]);
	}

	gradient_intercept *= (2.0 / training_x.size());
	gradient_slope *= (2.0 / training_x.size());

	cost_gradient[0] = gradient_intercept;
	cost_gradient[1] = gradient_slope;
}

vector<double> linear_regression(const vector<double>& training_x, const vector<double>& training_y)
{
	double learning_rate = 0.0001;
	double threshold = 0.0001;
	int iteration = 0;

	vector<double> predicted_y(training_y.size());
	vector<double> cost_gradient(2);
	vector<double> model_parameters(2);

	model_parameters[0] = 0; // will be the predicted y-intercept, however its not considered a weight, but rather a "bias"
	model_parameters[1] = 1; // will be the predicted slope

	do
	{
		// predict y-values based off of the weights and given x-values
		fit(training_x, model_parameters, predicted_y);

		// calculate the cost gradient based off of the predicted and actual y-values
		calculate_cost(predicted_y, training_x, training_y, cost_gradient);

		// update the weights with the cost gradient
		update_weights(model_parameters, cost_gradient, learning_rate);

		iteration++;
		if (iteration % 100000 == 0)
		{
			cout << "Iteration: " << iteration << " dC/dB: " << cost_gradient[0] << " dC/dM: " << cost_gradient[1] << endl;
		}
	} while (abs(cost_gradient[0]) > threshold || abs(cost_gradient[1]) > threshold);

	cout << "Iteration: " << iteration << " dC/dB: " << cost_gradient[0] << " dC/dM: " << cost_gradient[1] << endl;

	return model_parameters;
}


int main()
{
	ifstream file("training_data.txt");

	vector<double> training_x;
	vector<double> training_y;

	while (!file.eof())
	{
		double x;
		double y;
		file >> x;
		file >> y;
		training_x.push_back(x);
		training_y.push_back(y);
	}

	vector<double> model_parameters(2);

	model_parameters = linear_regression(training_x, training_y);

	cout << "y = (" << model_parameters[1] << ")x + (" << model_parameters[0] << ")" << endl;
}