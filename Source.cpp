//#include "definitions.h"
#include "tumasulo_algorithm.h"


int main()
{


	system("cls");
	Tomasulo Tomasulo;
	Tomasulo.load("data_file.txt");
	Tomasulo.load_data("data.txt");
	Tomasulo.simulate();
	system("pause");
}
