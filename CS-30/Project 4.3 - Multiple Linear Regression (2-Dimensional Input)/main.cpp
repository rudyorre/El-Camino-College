#include <iostream>
#include <fstream>
using namespace std;

struct Data
{
	double* x1;
	double* x2;
	double* y;
	int size;

	Data(double* set_x1, double* set_x2, double* set_y, int set_size) : x1(set_x1), x2(set_x2), y(set_y), size(set_size) { }
};

void load_data(ifstream& file, Data data)
{
	for (int i = 0; i < data.size; i++)
	{
		file >> data.x1[i];
		file >> data.x2[i];
		file >> data.y[i];
	}
}

void print(Data data)
{
	for (int i = 0; i < data.size; i++)
	{
		cout << data.x1[i] << " " << data.x2[i] << " " << data.y[i] << endl;
	}
}

bool above_threshold(double* cost_gradient, double threshold)
{
	return abs(cost_gradient[0]) > threshold
		|| abs(cost_gradient[1]) > threshold
		|| abs(cost_gradient[2]) > threshold;
}

void fit(const Data& data, const double* parameters, double* y_predicted)
{
	for (int i = 0; i < data.size; i++)
	{
		y_predicted[i] = parameters[0] + parameters[1] * data.x1[i] + parameters[2] * data.x2[i];
	}
}

double calculate_cost(const Data& data, const double* y_predicted, double* cost_gradient)
{
	double cost = 0;
	cost_gradient[0] = 0;
	cost_gradient[1] = 0;
	cost_gradient[2] = 0;

	for (int i = 0; i < data.size; i++)
	{
		double difference =	y_predicted[i] - data.y[i];

		cost_gradient[0] += (difference * 1);
		cost_gradient[1] += (difference * data.x1[i]);
		cost_gradient[2] += (difference * data.x2[i]);
		cost += (difference * difference);
	}

	cost_gradient[0] /= data.size;
	cost_gradient[1] /= data.size;
	cost_gradient[2] /= data.size;

	return cost / (2.0 * data.size);
}

void update_parameters(const double* cost_gradient, double learning_rate, double* parameters)
{
	for (int i = 0; i < 3; i++)
	{
		parameters[i] -= learning_rate * cost_gradient[i];
	}
}

double* linear_regression(Data data)
{
	double learning_rate = 0.0001;
	double threshold = 0.0001;
	int iteration = 0;

	double* y_predicted = new double[data.size];
	double* cost_gradient = new double[3];
	double* parameters = new double[3]{ 0, 0, 0 };

	do
	{
		// predict output with current parameters
		fit(data, parameters, y_predicted);

		double cost = calculate_cost(data, y_predicted, cost_gradient);

		update_parameters(cost_gradient, learning_rate, parameters);

		//if (iteration > 1000) break;
		if (iteration % 1000 == 0)
		{
			cout << "Iterations: " << iteration << " Cost: " << cost << " Gradient: <"
				<< cost_gradient[0] << ", " << cost_gradient[1] << ", " << cost_gradient[2] << ">" << endl;
		}

		iteration++;
	}
	while (above_threshold(cost_gradient, threshold));
	
	return parameters;
}

int main()
{
	ifstream file("training_data_2.txt");
	int size;
	file >> size;

	double* x1 = new double[size];
	double* x2 = new double[size];
	double* y = new double[size];

	Data data(x1, x2, y, size);

	load_data(file, data);

	double* parameters = new double[3]; // coefficients and bias {b, c1, c2} 

	parameters = linear_regression(data);

	cout << "y = " << parameters[0] << " + (" << parameters[1] << ")x1 + (" << parameters[2] << ")x2" << endl;

}