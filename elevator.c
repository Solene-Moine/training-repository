#include <ncurses.h>
#include <stdlib.h>
#include "elevator.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons) {
  Elevator *res = (Elevator*)malloc(sizeof(Elevator));
  res->capacity = capacity;
  res->currentFloor = currentFloor;
  res->targetFloor = currentFloor;
  res->persons = persons;
  return res;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists) {
  Building *res = (Building*)malloc(sizeof(Building));
  res->nbFloor = nbFloor;
  res->elevator = elevator;
  res->waitingLists = waitingLists;
  return res;
}

PersonList *exitElevator(Elevator *e) {
  // keep persons which do not exit
  // returns persons which exit the elevator
  PersonList *stay_list = NULL;
  PersonList *exit_list = NULL;
  while(e->persons != NULL) {
    Person *p = e->persons->person;
    if(p->dest == e->currentFloor) {
      exit_list = insert(p,exit_list);
    } else {
      stay_list = append(p,stay_list);
    }
    e->persons = e->persons->next;
  }
  e->persons = stay_list;
  return exit_list;
}

// take as much persons as possible
// returns list of persons which could not enter the elevator
PersonList* enterElevator(Elevator *e, PersonList *list) {
  while(list != NULL && length(e->persons) < e->capacity) {
    e->persons = insert(list->person, e->persons);
    list = list->next;
  }
  return list;
}

void stepElevator(Building *b) {
  Elevator *elevator = b->elevator;
  if(elevator->currentFloor == elevator->targetFloor) {
    exitElevator(elevator);
    b->waitingLists[elevator->currentFloor] = enterElevator(elevator, b->waitingLists[elevator->currentFloor]);
  } else if(elevator->currentFloor > elevator->targetFloor) {
    elevator->currentFloor--;
  } else {
    elevator->currentFloor++;
  }
}

