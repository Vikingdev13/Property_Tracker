#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Parameter names in functions can be changed to 
	your desired names
*/

struct prop_def
{
	char prop_type[25];
	double rent_income;
	double maint_cost;
	int numBeds;
	int numBaths;
};
typedef struct prop_def prop;

int readProps(FILE *ifp, prop O[]);
void printProps(prop O[], int num);
double totalIncome(prop O[], int num);
double totalCost(prop O[], int num);
double pricePerBed(prop O[], int num);
int numHouses(prop O[], int num);

int main(int argc, char *argv[])
{
	// array of structs for the owners
	prop owner1[60];
	prop owner2[60];

	FILE *ifp1, *ifp2 = NULL;

	// open files
	ifp1 = fopen(argv[1], "r");
	ifp2 = fopen(argv[2], "r");

	int numOfProps1 = readProps(ifp1, owner1);
	int numOfProps2 = readProps(ifp2, owner2);

	// making sure all the property types are read in properly
	//printProps(owner1, numOfProps1);
	//printProps(owner2, numOfProps2);

	// Function calls
	printf("\nTotal income Owner1: $%0.2lf\n", totalIncome(owner1, numOfProps1));
	printf("Total cost Owner2: $%0.2lf\n", totalCost(owner2, numOfProps2));
	printf("Average price per bedroom Owner1: $%0.2lf\n", pricePerBed(owner1, numOfProps1));
	printf("Average price per bedroom Owner2: $%0.2lf\n", pricePerBed(owner2, numOfProps2));
	printf("# of Houses Owner1: %d\n", numHouses(owner1, numOfProps1));
	printf("# of Houses Owner2: %d\n", numHouses(owner2, numOfProps2));

	double total = totalIncome(owner1, numOfProps1) + totalIncome(owner2, numOfProps2);
	double avg = total / (numOfProps1 + numOfProps2);
	printf("Average price of all properties: $%0.2lf\n\n", avg);

	// close files
	fclose(ifp1);
	fclose(ifp2);
	return 0;
}

int readProps(FILE *ifp, prop O[])
{
	int count;
	fscanf(ifp, "%d", &count);

	for (int i = 0; i < count; ++i)
	{
		fscanf(ifp, "%s", O[i].prop_type);
		fscanf(ifp, "%lf", &O[i].rent_income);
		fscanf(ifp, "%lf", &O[i].maint_cost);
		fscanf(ifp, "%d", &O[i].numBeds);
		fscanf(ifp, "%d", &O[i].numBaths);
	}
	return count;
}

void printProps(prop O[], int num)
{
	for (int i = 0; i < num; ++i)
		printf("%s\n", O[i].prop_type);
}

double totalIncome(prop O[], int num)
{
	double total = 0.0;
	for (int i = 0; i < num; ++i)
		total += O[i].rent_income;
	return total;
}

double totalCost(prop O[], int num)
{
	double total = 0.0;
	for (int i = 0; i < num; ++i)
		total += O[i].maint_cost;
	return total;
}

double pricePerBed(prop O[], int num)
{
	double avg = 0.0;
	for (int i = 0; i < num; ++i)
		avg += O[i].numBeds;
	return totalIncome(O, num) / avg;
}

int numHouses(prop O[], int num)
{
	int total = 0;
	for (int i = 0; i < num; ++i)
		if (strcmp(O[i].prop_type, "house") == 0)
			total++;
	return total;
}
