#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "person.h"

typedef struct _Elevator {
    int capacity;
    int currentFloor;
    int targetFloor;
    PersonList *persons;
} Elevator;

typedef struct _Building {
    int nbFloor;
    Elevator *elevator;
    PersonList **waitingLists; // array of waiting list (one per floor)
} Building;

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons);
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists);

PersonList* exitElevator(Elevator *e);
PersonList* enterElevator(Elevator *e, PersonList *list);
void stepElevator(Building *b);

#endif
