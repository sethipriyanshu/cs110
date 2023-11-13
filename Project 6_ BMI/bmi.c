#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmi.h"

///////////////////////////////////////////////////////////////
// helper functions

Person *createPerson(char *first, char *last, int height, int weight, Person *nextHeight, Person *nextWeight)
{
    Person *ptr=malloc(sizeof(Person));
    ptr->first=malloc(strlen(first)+1);
    strcpy(ptr->first, first);
    ptr->last=malloc(strlen(last)+1);
    strcpy(ptr->last, last);

    ptr->height=height;
    ptr->weight=weight;

    ptr->nextHeight=nextHeight;
    ptr->nextWeight=nextWeight;

    return ptr;
}

///////////////////////////////////////////////////////////////
Person *insertByHeight(Person *head, Person *newPerson) {
    if (head == NULL || (head->height < newPerson->height) || 
        (head->height == newPerson->height && head->weight > newPerson->weight)) {
        newPerson->nextHeight = head;
        return newPerson;
    }
    Person *current = head;
    while (current->nextHeight != NULL && 
           (current->nextHeight->height < newPerson->height || 
           (current->nextHeight->height == newPerson->height && current->nextHeight->weight > newPerson->weight))) {
        current = current->nextHeight;
    }
    newPerson->nextHeight = current->nextHeight;
    current->nextHeight = newPerson;
    return head;
}

Person *insertByWeight(Person *head, Person *newPerson) {
    if (head == NULL || (head->weight > newPerson->weight) || 
        (head->weight == newPerson->weight && head->height < newPerson->height)) {
        newPerson->nextWeight = head;
        return newPerson;
    }
    Person *current = head;
    while (current->nextWeight != NULL && 
           (current->nextWeight->weight < newPerson->weight || 
           (current->nextWeight->weight == newPerson->weight && current->nextWeight->height < newPerson->height))) {
        current = current->nextWeight;
    }
    newPerson->nextWeight = current->nextWeight;
    current->nextWeight = newPerson;
    return head;
}
void freePerson(Person *person) {
    if (person != NULL) {
        free(person->first);
        free(person->last);
        free(person);
    }
}
Person *removeNode(Person *head, Person *nodeToRemove, int isHeightList) {
    Person *temp = head, *prev = NULL;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp == nodeToRemove) {
        head = isHeightList ? temp->nextHeight : temp->nextWeight;
        return head;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp != nodeToRemove) {
        prev = temp;
        temp = isHeightList ? temp->nextHeight : temp->nextWeight;
    }

    // If key was not present in linked list
    if (temp == NULL) return head;

    // Unlink the node from linked list
    if (isHeightList) {
        prev->nextHeight = temp->nextHeight;
    } else {
        prev->nextWeight = temp->nextWeight;
    }

    return head;
}
PersonList *add(PersonList *list, char *first, char *last, int height, int weight) {
    // Check if person already exists
    Person *ptr = list->headHeightList;
    while (ptr != NULL) {
        if (strcmp(ptr->first, first) == 0 && strcmp(ptr->last, last) == 0) {
            printf("Error: %s %s already exists in the list\n", first, last);
            return list;
        }
        ptr = ptr->nextHeight;
    }

    // Create new person node
    Person *pNew = (Person *)malloc(sizeof(Person));
    pNew->first = strdup(first);
    pNew->last = strdup(last);
    pNew->height = height;
    pNew->weight = weight;
    pNew->nextHeight = NULL;
    pNew->nextWeight = NULL;

    // Insert new node into headHeightList in correct order
    list->headHeightList = insertByHeight(list->headHeightList, pNew);

    // Insert new node into headWeightList in correct order
    list->headWeightList = insertByWeight(list->headWeightList, pNew);

    return list;
}

int size(PersonList *list) {
	int count=0;
	for(Person *cur=list->headHeightList; cur!=NULL; cur=cur->nextHeight){
	  count++;
	}
	return count;
}

void printByHeight(PersonList *list) {
    for(Person *cur=list->headHeightList; cur!=NULL; cur=cur->nextHeight){
      printf("%s %s: height=%d, weight=%d\n", cur->first, cur->last, cur->height, cur->weight);  
    }     
}

void printByWeight(PersonList *list) {
	for(Person *cur=list->headWeightList; cur!=NULL; cur=cur->nextWeight){
	  printf("%s %s: height=%d, weight=%d\n", cur->first, cur->last, cur->height, cur->weight);  
	}
}

Person *search(PersonList *list, char *first, char *last) {
	for(Person *cur=list->headHeightList; cur!=NULL; cur=cur->nextHeight){
	  if(strcmp(cur->first, first)==0 && strcmp(cur->last, last)==0){
	    return cur;
	  }
	}
	return NULL;
}

void updateName(PersonList *list, char *first, char *last, char *newFirst, char *newLast) { 
	Person *ptr=search(list, first, last);
	if (ptr==NULL) {
		printf("Error: %s %s does not exist in the list\n", first, last);
		return;
	}

	// update the name
	free(ptr->first);
	ptr->first=malloc(strlen(newFirst)+1);
	strcpy(ptr->first, newFirst);
	free(ptr->last);
	ptr->last=malloc(strlen(newLast)+1);
	strcpy(ptr->last, newLast);
}

PersonList *removePerson(PersonList *list, char *first, char *last) {
    // Check if person exists
    Person *ptr = list->headHeightList;
    while (ptr != NULL) {
        if (strcmp(ptr->first, first) == 0 && strcmp(ptr->last, last) == 0) {
            break;
        }
        ptr = ptr->nextHeight;
    }
    if (ptr == NULL) {
        printf("Error: %s %s does not exist in the list\n", first, last);
        return list;
    }

    // Remove person from headHeightList
    list->headHeightList = removeNode(list->headHeightList, ptr, true);

    // Remove person from headWeightList
    list->headWeightList = removeNode(list->headWeightList, ptr, false);

    // Free memory allocated to person
    freePerson(ptr);

    return list;
}

PersonList *updateHeight(PersonList *list, char *first, char *last, int height)
{ 
	Person *ptr = list->headHeightList;
    while (ptr != NULL) {
        if (strcmp(ptr->first, first) == 0 && strcmp(ptr->last, last) == 0) {
            break;
        }
        ptr = ptr->nextHeight;
    }
    if (ptr == NULL) {
        printf("Error: %s %s does not exist in the list\n", first, last);
        return list;
    }

    // Update height of person
    ptr->height = height;

    // Remove person from headHeightList
    list->headHeightList = removeNode(list->headHeightList, ptr, true);

    // Insert person into headHeightList in correct order
    list->headHeightList = insertByHeight(list->headHeightList, ptr);

    return list;
	return list;
}

PersonList *updateWeight(PersonList *list, char *first, char *last, int weight) {
    // Check if person exists
    Person *ptr = list->headWeightList;
    while (ptr != NULL) {
        if (strcmp(ptr->first, first) == 0 && strcmp(ptr->last, last) == 0) {
            break;
        }
        ptr = ptr->nextWeight;
    }
    if (ptr == NULL) {
        printf("Error: %s %s does not exist in the list\n", first, last);
        return list;
    }

    // Update weight of person
    ptr->weight = weight;

    // Remove person from headWeightList
    list->headWeightList = removeNode(list->headWeightList, ptr, false);

    // Insert person into headWeightList in correct order
    list->headWeightList = insertByWeight(list->headWeightList, ptr);

    return list;
}