#include "laps.h"

static race_car *race_cars;
/**
 * race_state - shows the state of the race
 * @id: array of ids of cars in the race
 * @size: size of the id array
 *
 * Return: Nothing
 */
void race_state(int *id, size_t size)
{
	race_car *temp = NULL, *new_car = NULL;
	size_t i = 0, create_car = 1;

	if (size == 0)
	{
		free_list(&race_cars);
		return;
	}
	temp = race_cars;
	for (i = 0; i < size; i++)
	{
		race_cars = temp;
		while (race_cars)
		{
			if (race_cars->id == id[i])
				race_cars->laps++;
			race_cars = race_cars->next;
		}
	}
	for (i = 0; i < size; i++)
	{
		race_cars = temp;
		create_car = detect_car(race_cars, id[i]);
		if (create_car)
		{
			new_car = malloc(sizeof(race_car));
			new_car->id = id[i];
			new_car->laps = 0;
			printf("Car %d joined the race\n", new_car->id);
			sorted_insert(&race_cars, &new_car);
			temp = race_cars;
		}
	}
	print_cars(temp);
}
/**
 * print_cars - prints the cars in the array
 * @temp: linked list of cars in the race
 *
 * Return: Nothing
 */
void print_cars(race_car *temp)
{
	race_cars = temp;
	printf("Race state:\n");
	while (race_cars)
	{
		printf("Car %d [%d laps]\n", race_cars->id, race_cars->laps);
		race_cars = race_cars->next;
	}
	race_cars = temp;
}
/**
 * sorted_insert - inserts sorted by id in the linked list
 * @cars: linked list of cars
 * @new_car: new car to be inserted
 *
 * Return: Nothing
 */
void sorted_insert(race_car **cars, race_car **new_car)
{
	race_car *temp = NULL, *initial = NULL;

	initial = *cars;
	if (!cars)
		return;
	if (*cars == NULL)
	{
		*cars = *new_car;
		(*new_car)->next = NULL;
		return;
	}
	if ((*new_car)->id < (*cars)->id)
	{
		(*new_car)->next = *cars;
		*cars = *new_car;
		return;
	}
	while ((*cars)->next)
	{
		if ((*new_car)->id < (*cars)->next->id)
		{
			temp = (*cars)->next;
			(*cars)->next = *new_car;
			(*new_car)->next = temp;
			*cars = initial;
			return;
		}
		*cars = (*cars)->next;
	}
	(*cars)->next = *new_car;
	(*new_car)->next = NULL;
	*cars = initial;
}
/**
 * free_list - frees the memory of the linked list
 * @cars: linked list of cars
 *
 * Return: Nothing
 */
void free_list(race_car **cars)
{
	race_car *temp = NULL;

	while (*cars)
	{
		temp = (*cars)->next;
		free(*cars);
		*cars = temp;
	}
	*cars = NULL;
}

/**
 * detect_car - detects if car is already on the race
 * @cars: linked list of cars
 * @car_id: id of the card to register
 * Return: 1 if car has to be created, 0 otherwise
 */
int detect_car(race_car *cars, int car_id)
{
	while (cars)
	{
		if (cars->id == car_id)
			return (0);
		cars = cars->next;
	}
	return (1);
}
