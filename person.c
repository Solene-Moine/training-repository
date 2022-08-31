#include <stdlib.h>
#include "person.h"

Person* createPerson(int src, int dest) {
    Person *res = (Person*)malloc(sizeof(Person));
    res->src = src;
    res->dest = dest;
    return res;
}

PersonList* insert(Person *p, PersonList *list) {
    PersonList *res = (PersonList*) malloc(sizeof(PersonList));
    res->person = p;
    res->next = list;
    return res;
}

PersonList* append(Person *p, PersonList *list) {
  if(list==NULL) {
    return insert(p,NULL);
  }
  return insert(list->person,append(p,list->next));
}

int length(PersonList *list) {
  if(list==NULL) {
    return 0;
  }
  return 1 + length(list->next);
}
