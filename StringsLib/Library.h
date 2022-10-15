#ifndef STRINGSLIB_LIBRARY_H
#define STRINGSLIB_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node; // se le agrega el alias a node
//Función para abrir el archivo
FILE* OpenFile(char *fileName, char *toDo);
//Declaración de funciones
Node* ListFillIn(FILE* file);
Node* WordSep(char* line);
Node* ListAddWord(char *word_to_add, Node *head);
Node* NewNode(char * word_to_add);
void PrintCadenita(Node *head);
void WriteResult(FILE* resultsfile, Node * head);
void Reverse_String(int op);
Node* WordReverse(FILE* file, FILE* resultfile, Node* head);
Node* ReverseSomeWords(FILE* file, FILE* resultfile, Node* head);

#endif //STRINGSLIB_LIBRARY_H
