#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef HeaderFile
#define HeaderFile
#define NAME 50

typedef struct Food ///Food struct-contains the Meal name,prict,Quantity in the kitchen and pointer to the next meal
{
	int Price;
	char* ProductName;
	int Quantity;
	struct Food* next;
}Food, * PFood;

typedef struct Resturant //restrant struct-contains numbers of structs and a pointer to the tables array
{
	int SumTabels;
	struct	Table* TablesArray;
}Resturant, * PResturant;

typedef struct Table//Table struct-contains the Quantity of the meals in each table, and a pointer to the head of meals list and tail of the meals list
{
	int manotTable;
	struct Food* head, * tail;
}Table, * PTable;

//Announcement of functions
void AddItems(PFood Food, char* name, int amount, FILE* out);
int OrderItem(PResturant HeadServ, PFood HeadFd, PTable Manang, int TableNumber, char* ProductName, int Quantity, FILE* out);
int CheckDish(PTable Manang, char* dish);
void Delete_Table(PTable Delete);
void RemoveItem(PResturant TableT, PTable head, int TableNumber, char* ProductName, int Quantity, FILE* out);
void ClosingTable(PResturant  head, PTable Manang, int TableNumber, FILE* out);
int CreateProducts(PFood* headFd, FILE* manot, FILE* out);
void CloseResturant(PResturant TableT, PTable Manan);
void DeleteFoodList(PFood FoodDelead);
#endif