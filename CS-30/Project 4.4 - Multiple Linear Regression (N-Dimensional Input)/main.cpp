#include <iostream>
#include <fstream>
#include "LinearRegression.h"


int main()
{
	ifstream training("training_data_7.txt");

	Model model(training);

	model.linear_regression(true);
	model.print_features();
}