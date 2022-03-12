#include "HeaderFile.h"

//CreateProducts-this function gets a pointer to the head of dishes list, a pointer to file to write in, pointer to file we want to read
//this function scanning from "manot file"  the details of each dish,checks if the price/Quantity of each dish is positive
//then,allocate memmory for a new dish in the list,insert to the dish the info we got,and connect it to the list 
//the function return 1 if the recived dish in the kitchen complited, else return 0

int CreateProducts(PFood* headFd, FILE* manot, FILE* out)
{
	char name[NAME];
	int tempPrice, tempQuantity;
	PFood TempHead, AddFood;
	TempHead = (*headFd);
	while (fscanf(manot, "%s %d %d", name, &tempQuantity, &tempPrice) != EOF)
	{

		if (tempPrice < 0 || tempQuantity < 0)
		{
			fprintf(out, "Error my friend,The system gets only positive prices/Quantity\n");
		}
		else
		{
			AddFood = (PFood)malloc(sizeof(Food));
			if (AddFood == NULL)
			{
				return 0;
			}
			AddFood->Price = tempPrice;
			AddFood->Quantity = tempQuantity;
			AddFood->ProductName = (char*)malloc((strlen(name) + 1) * sizeof(char));//allocate memmory to the name of the dish
			if (AddFood->ProductName == NULL)
			{
				return 0;
			}
			strcpy(AddFood->ProductName, name);
			if (TempHead == NULL)//if the list of dish in kitchen is emptey
			{
				AddFood->next = NULL;
				TempHead = AddFood;//the dish is in the head
			}
			else
			{
				AddFood->next = TempHead;
				TempHead = AddFood;
			}
		}

	}
	(*headFd) = TempHead;
	fprintf(out, "The Kitchen was created!\n");
	return 1;
}


//AddItems-this function gets a pointer to dish,a string ,a number-amount of dishs,dishes amount,and a pointer to file we write in
//this function Adds a dish to existing stock in the kitchen. the function checks if the amount we want to add is positive
//the function check the list of dishes and search the spesific dish we want to add to
//if its find the meal in the list its add the amount, else its print a massege
void AddItems(PFood Food, char* name, int amount, FILE* out)
{
	int flag = 0;
	PFood check = Food;
	if (amount < 0)
	{
		fprintf(out, "Error my friend, The system gets only positive Quantity\n");
	}
	else
	{
		while (check != NULL)
		{
			if (!strcmp(check->ProductName, name))
			{
				check->Quantity += amount;
				fprintf(out, "%d %s were added to kitchen\n", amount, name);
				return;
			}
			check = check->next;
		}
		fprintf(out, "Error my friend,unfortunately we dont have %s\n", name);
	}
}

//OrderItem-this function gets a pointer to resturant-the tables,pointer to the head of the dishes list
//poiunter to table,table number,dish name,Quantity of dished and pointer to file we write in.
//the function goes through the array of tables,checks if the number of table we got exists,if i'snt it returns 1.
//else,goes trough the dish list,look for the name of the dish,if there is no dish like this in the list prints a message
//if the dish is in the list-checks if there is enough of dishes in stock, if not print a message
//else,allocate memmory to the new dish, connect it to the list. increse the number of dishes,and the quantity of the dish.
int OrderItem(PResturant HeadServ, PFood HeadFd, PTable Manang, int TableNumber, char* ProductName, int Quantity, FILE* out)
{
	int flag = 0;
	PResturant resturant;
	PTable TempTable;
	PFood food = HeadFd, NewMana;
	resturant = HeadServ;
	TempTable = &HeadServ->TablesArray[TableNumber - 1];
	if (TableNumber > resturant->SumTabels || 0 >= resturant->SumTabels)
	{
		fprintf(out, "Sorry we dont have table number %d\n", TableNumber);
		return 1;
	}

	while (food != NULL)
	{
		if (!strcmp(ProductName, food->ProductName))
		{
			flag = 1;
			break;
		}
		food = food->next;
	}

	if (flag == 0)
	{
		fprintf(out, "We dont have %s, sorry!\n", ProductName);
	}
	else
		if (food->Quantity < Quantity)
		{
			fprintf(out, "Sorry,you are ordering %d dishes of %s. We have %d dishes in the kitchen.\n", Quantity, ProductName, food->Quantity);
		}
		else
		{
			if (CheckDish(TempTable, ProductName) == -1)
			{
				NewMana = (PFood)malloc(sizeof(Food));
				if (NewMana == NULL)
				{
					return 0;
				}

				NewMana->ProductName = (char*)malloc((strlen(ProductName) + 1) * sizeof(char));
				if (NewMana->ProductName == NULL)
				{
					return 0;
				}
				strcpy(NewMana->ProductName, ProductName);
				NewMana->Price = food->Price;
				NewMana->Quantity = Quantity;
				TempTable->manotTable++;
				if (TempTable->head == NULL)//if its the only dish in list
				{
					TempTable->head = NewMana;
					TempTable->tail = NewMana;
					TempTable->tail->next = NULL;
				}
				else
				{
					TempTable->tail->next = NewMana;
					TempTable->tail = NewMana;
				}
			}
			else
			{
				TempTable->head->Quantity += Quantity;
			}
			fprintf(out, "%d %s were added to the table number %d\n", Quantity, ProductName, TableNumber);
		}
	return 1;
}

//RemoveItem-this function gets a pointer to the tables array,number of table,pointer to the dishes list,name of dish,quantity and a pointer to file we want to write in. 
//the function goes trough the list of meals of the spesific table,looking for the dish we want to cancel,if the dish is not in the list print a message.
//then the function check that we dont cancel more dished then the dishes that was ordered.
//the function checks if the user want to cancel all the dishes he ordered and this is the only dish in list- update the list head and tail to NULL, and delete the list.
void RemoveItem(PResturant HeadTable, PTable headMang, int TableNumber, char* ProductName, int Quantity, FILE* out)
{
	int flag = 1, Informatin, Informatin2;
	Table* Manang, * DeleteTable, * TempTable, * PrevTempTable;
	TempTable = &HeadTable->TablesArray[TableNumber - 1];
	PrevTempTable = headMang;
	DeleteTable = headMang;
	Manang = headMang;
	while (TempTable->head != NULL)
	{
		if (!(strcmp(TempTable->head->ProductName, ProductName)))
		{
			flag = 0;
			break;
		}
		PrevTempTable->head = TempTable->head;
		TempTable->head = TempTable->head->next;
	}
	if (flag)
	{
		fprintf(out, "Erorr There is no table %d with an active %s dishes\n", TableNumber, ProductName);
		return;
	}
	if (TempTable->head->Quantity < Quantity)
	{
		fprintf(out, "Sorry, you orderd only %d dishes from %s And you want to cancel %d dishes\n", TempTable->head->Quantity, ProductName, Quantity);
		return;
	}
	if ((TempTable->head->Quantity -= Quantity) == 0)
	{

		if (TempTable->manotTable == 1)
		{
			Delete_Table(TempTable);
			TempTable->head = NULL;
			TempTable->tail = NULL;
		}
		else
		{
			DeleteTable = TempTable->head;//TempTable->head is a temp pointer to the table we want to delete
			PrevTempTable->head->next = TempTable->head->next;
			Delete_Table(TempTable);//delte the dishes list of the spesific table
		}
		TempTable->manotTable--;
	}
	fprintf(out, "%d %s was returnd to the kitchen from table number %d\n", Quantity, ProductName, TableNumber);
}


//CheckDish-this function gets a pointer to table dishes list, and a name of a dish
//the function checks if the dish is in the list of dishes,if it is- return 1, else return -1.
int CheckDish(PTable Manang, char* dish)
{
	Food SerchInMenu;
	PTable SerchDish;
	SerchDish = Manang;

	while (SerchDish->head != NULL)
	{
		if (!strcmp(SerchDish->head->ProductName, dish))
		{
			return 1;
		}
		SerchDish->head->next;
	}
	return -1;
}

//ClosingTable-this function gets a pointer to resturant=tables array, pointer to dishes list,table number and pointer to file we want to write in.
//the function goes trough the prices the table dishes list-checks the melas price and the quantity,then calculate the price of the meal.
//the function deltes and free the info of the spsific table, using Delete_Table function.
//the function prints the tips the table need to pay.
void ClosingTable(PResturant  head, PTable Manang, int TableNumber, FILE* out)
{
	int bils = 0, tip;
	PTable TempTable, DeleteTabele;
	TempTable = &head->TablesArray[TableNumber - 1];
	DeleteTabele = Manang;
	if (TempTable->head == NULL)
	{
		fprintf(out, "The table number %d is not orderd yet\n", TableNumber);//if there is no tables in resturant
	}
	else
	{
		while (TempTable->head != NULL)
		{
			bils += TempTable->head->Quantity * TempTable->head->Price;
			fprintf(out, "%d %s. ", TempTable->head->Quantity, TempTable->head->ProductName);
			DeleteTabele->head = TempTable->head;
			TempTable->head = TempTable->head->next;
			Delete_Table(DeleteTabele);
		}
		tip = (bils * 0.10);
		fprintf(out, "%d nis + %d nis for tips, please!\n", bils, tip);
	}
}

//Delete_Table-this function gets a pointer to table,free the memory of each dish name, and free the memmory that was allocated to the whole dishes list. 
void Delete_Table(PTable Delete)
{
	if (Delete->head != NULL)
	{
		free(Delete->head->ProductName);
		free(Delete->head);
	}
}

//CloseResturant-this functin gets a pointer to resturant and a pointer to table
//the function goes trough evrey table, free the memmory that was allocated to evrey dish, and free the list of dishes of evrey table.
void CloseResturant(PResturant TableT, PTable Manan)
{
	int i;
	PResturant TempTable;
	PTable Manang, Temp;
	Temp = Manan;
	for (i = 0; i < TableT->SumTabels; i++)
	{
		Manang = &TableT->TablesArray[i];
		while (Manang->head != NULL)
		{
			Temp->head = Manang->head;
			Manang->head = Manang->head->next;
			free(Temp->head->ProductName);
			free(Temp->head);
		}

	}
}


//DeleteFoodList-this function gets a pointer to the dishes list in the kitchen
//free the memory of the name of each dish and the dish itself.
void DeleteFoodList(PFood FoodDelead)
{
	PFood FoodDel;
	FoodDel = FoodDelead;
	while (FoodDelead != NULL)
	{
		FoodDel = FoodDelead;
		FoodDelead = FoodDelead->next;
		free(FoodDel->ProductName);
		free(FoodDel);
	}
}
