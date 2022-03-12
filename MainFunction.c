#include "HeaderFile.h"

int main()
{
	FILE* manot, * out, * Instructions;
	PFood MANOT;//pointer to dish
	Table Amount;
	Resturant tabels;
	char productName[NAME];
	int flag = 1, SumTab, i, AmountProduct, TableNumber;//AmountProduct-amount of dishes,SumTab-the amount of tables in resturant
	MANOT = NULL;//reset the first dish
	manot = fopen("manot.txt", "r");//open manot file for reading
	if (NULL == manot)//Check if the opening was successful
	{
		printf("Error!!!");
		exit(1);
	}
	out = fopen("out.txt", "w");//open out file for writing
	if (NULL == out)//Check if the opening was successful
	{
		fclose(manot);//we dont use the reading file 
		printf("Error!!!");
		exit(1);
	}

	Instructions = fopen("Instructions.txt", "r");//open 'out' file for reading
	if (NULL == Instructions)//Check if the opening was successful
	{
		fclose(manot);
		fclose(out);
		printf("Error!!!");
		exit(1);
	}
	fscanf(Instructions, "%d", &SumTab);//scan the amount of the tables in the resturant
	tabels.SumTabels = SumTab;
	tabels.TablesArray = (PTable)malloc(SumTab * sizeof(Table));//alloacte memory to requested tables in the array
	if (tabels.TablesArray == NULL)//Checks if memory allocation was successful
	{
		fclose(manot);//if the allocation failed we dont use the other files anymore
		fclose(out);
		fclose(Instructions);
		printf("Error!!!");
		exit(1);
	}

	for (i = 0; i < tabels.SumTabels; i++) //setting the tables to null
	{
		tabels.TablesArray[i].head = NULL;
		tabels.TablesArray[i].tail = NULL;
		tabels.TablesArray[i].manotTable = 0;
	}
	while ((fscanf(Instructions, "%d", &SumTab) != EOF) && flag)//scan to sum tab- the Instruction we want to do
	{
		switch (SumTab)
		{

		case 1://if SumTab=1->scanning the dishes into the resturant
		{
			flag = CreateProducts(&MANOT, manot, out);//flag=1 if scanning was successful
			fclose(manot);
			break;
		}
		case 2://if SumTab=2->add quantity of dishes to spesific dish  in the kitchen
		{
			fscanf(Instructions, "%s %d", productName, &AmountProduct);
			AddItems(MANOT, productName, AmountProduct, out);
			break;
		}
		case 3://if SumTab=3->order dishes to spesific table
		{
			fscanf(Instructions, "%d %s %d", &TableNumber, productName, &AmountProduct);
			flag = OrderItem(&tabels, MANOT, &Amount, TableNumber, productName, AmountProduct, out);
			break;
		}
		case 4://if SumTab=4->cancel dishes in spesific table
		{

			fscanf(Instructions, "%d %s %d", &TableNumber, productName, &AmountProduct);
			RemoveItem(&tabels, &Amount, TableNumber, productName, AmountProduct, out);
			break;
		}
		case 5://if SumTab=5->closing a table, prints a bill, and clean the dishe list
		{

			fscanf(Instructions, "%d", &TableNumber);
			ClosingTable(&tabels, &Amount, TableNumber, out);
		}

		}

	}
	if (flag == 0)//if scanning the dishes list failed 
	{
		printf("Error !!!!");
	}
	CloseResturant(&tabels, &Amount);//free dishes list of evrey table
	DeleteFoodList(MANOT);//free the dishes list in the kitchen
	free(tabels.TablesArray);//free the tables array
	fclose(out);//close out file
	fclose(Instructions);//close instructions file
	return 0;
}