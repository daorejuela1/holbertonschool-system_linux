#ifndef LAPS_H
#define LAPS_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * struct Cars - structure to define the circuit cars
 *
 * @id: id of the car
 * @laps:number of laps given by the car
 * @next: pointer to the next racing car
 */
typedef struct Cars
{
int id;
int laps;
struct Cars *next;
} race_car;

void print_cars(race_car *cars);
void race_state(int *id, size_t size);
void sorted_insert(race_car **cars, race_car **new_car);
void free_list(race_car **cars);
int detect_car(race_car *cars, int car_id);
#endif
