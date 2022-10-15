#include "Library.h"

#define MAX_SIZE 300 // capacidad de caracteres en una lienea
struct node // se crea la estructura llamada nodo
{
    char *word;  // apuntador con nombre word que apunta a caracter (char)
    struct node* next; // apuntador a siguiente nodo
} ;

FILE* OpenFile(char *fileName, char *toDo) // Devuelve el apuntador de un archivo
{
    FILE *file = NULL; // inicializa el apuntador a archivo como NULL
    file = fopen(fileName, toDo); // se abre el archivo

    if (file == NULL) // checar si sigue siendo NULL (no se abrió correctamente)
    {
        printf("No se pudo abrir su archivo\n");// si no se abre se imprime esto
    }
    return file; // regresa el file (archivo)
}


Node* ListFillIn(FILE* file) // Devolverá un apuntador de Nodo (a la cabeza de la lista (head))
{
    Node *head = NULL; // se inicializa en NUll
    char *line = malloc(sizeof(char)*MAX_SIZE); //Se reserva espacio en el heap (heap = espacio de memoria)
    line = fgets(line, MAX_SIZE, file); // obtiene la primera linea del archivo
    if ( line == NULL ) // si la primera linea no tiene nada (NULL)
    {
        return NULL; // Regresa NULL
    }
    head = WordSep(line); // Pasa a funcion la linea
    return head; // regresa el head
}


Node* WordSep(char* line) //  Devuelve el apuntador a la cabeza de la lista
{
    int index_base = 0; // se inicializan variables = 0
    int index_next = 0;
    Node *head = NULL; //se inicializa  el apuntador a la cabeza de la lista como NULL
    do
    {
        if(line[index_next] == ' ' || line[index_next] == '\n' )
        // Lo que hace es identificar espacios o saltos de liena para así separar por palabras
        {
            char *word = malloc(sizeof(char)*MAX_SIZE); // reserva un espacio en memoria en donde guardará la palabra
            int size = index_next - index_base;
            int j = index_base;
            for ( int i = 0; i < size; i++ )
            {
                word[i] = line[j++];
            }
            word[size] = '\0';
            // cuando se haya identificado una palabra esta se agrega a la lista (el apuntador será al primer carácter de la palabra)
            head = ListAddWord(word, head);
            // si se terminó la linea o un salto de linea se terminá el ciclo
            if ( line[index_next] == '\n' ) { // while
                break;
            }
            // para que pase a la siguiente palabra
            index_base = index_next + 1;
        }
        index_next++;
    } while (1);// Mientras esto sea verdadero (aka hasta que se agreguen todas las palabras)

    return head; // Regresa head ya con la lista llena
}

Node* ListAddWord(char *word_to_add, Node *head) // En esta lista se va a agregar palabra por palabra (nodo por nodo)
{
    {
        if (head == NULL) { // si la cabeza de nuestra lista esta vacia
            head = NewNode(word_to_add);// obtiene un node de la memoria con malloc para guardar ahí la palabra (la palabra es el nuevo nodo)
            return head; // regresa head
        } else { // si ya tiene una cabeza la lista entonces ...
            Node *current = head; // Se usa un apuntador a nodo para que head no se modifique
            while(current->next != NULL) // identifica el final de la lista
                current = current->next;
            current->next = NewNode(word_to_add); // agrega el nuevo nodo al final de la lista
            return head; // regresa head
        }
    }
}

Node* NewNode(char *word_to_add) // devuelve el nuevo nodo
{
    Node *new = malloc(sizeof(Node)); // reserva espacio para el nuevo nodo
    new->word = word_to_add; // se asigna la palabra
    new->next = NULL; // se asigna el siguiente nodo como NULL
    return new; //Regresa el nuevo nodo
}

void PrintCadenita(Node *head) //Función de impresión del resultado
{
    Node *current = head; // usa otra variable para que head no se modifique
    while(current != NULL) // mientras que current sea diferente a NULL
    {
        printf("WORD: %s\n", current->word); //Se imprime la palabra
        current = current->next; // se actualiza el nodo que estamos imprimiendo
    }
}
void WriteResult(FILE* resultsfile, Node * head) // Función que escribe el resultado en el archivo de result.txt
{
    char *line = malloc(sizeof(char)*MAX_SIZE); // reserva el espacio en el heap
    line[0] = '\0'; // inciializa en NULL
    Node *current = head; // Se usa otra variable para que head no se modifique

    while(current != NULL){ //mientras current ( apuntador a nodo) sea diferente de NULL
//stract =  añade un bloque de memoria a otro (va creando un string con todas las palabras (nodos) de una linea)
// LOS DOS BLOQUES DEBEN TERMINAR CON UN CARÁCTER NULL
        strcat(line, current->word);
        strcat(line, " ");
        current = current->next;
    }
    strcat(line, "\n"); // Acaba de escribir una linea , y hace saltode linea
    fputs(line, resultsfile); // escribe la linea enel archivo de result.txt
}

Node* WordReverse(FILE* file, FILE* resultfile, Node* head)
{
    if(head->next == NULL)
    {
        return head;
    }
    Node *next = NULL;
    Node *before = NULL;
    Node *newhead = NULL;
    while(head != NULL){ // mientras que head sea distinto a NULL
        next= head->next; // el next va a adquirir el siguiente del primer nodo
        head->next=before; //  Este va a ser NULL porque no va a apuntar a nada
        before=head; // before tomará el primer nodo
        head=next; // el head tomará el siguiente vodo

    }
    newhead=before; // before tomará el valor de head

    return newhead; // Regresa la nueva cabeza de la lista
}

Node* ReverseSomeWords(FILE* file, FILE* resultfile, Node* head) //
{
    Node *current = head; // usa otra variable para que head no se modifique
    char *new_word;
    while (current != NULL) // mientras current sea diferente de NULL
    {
        if (strlen(current->word) >= 5)  // Si el nodo es mayor o igual a 5 caracteres entonces...
        {
            new_word = strrev(current->word); // voltea las letras de la palabra
            current->word = new_word; // current dereferencia la palabra y la sustituye por la nueva palabra
        }
        current = current->next; // se actualiza el nodo que estamos imprimiendo
    }
    return head;// regresa head
}

void Reverse_String(int op) // función de elección de lo que queramos lograr
{
    FILE* file = OpenFile("../input.txt", "r"); // lee el archivo input
    FILE* resultfile = OpenFile("../result.txt", "w"); //escribe en el archvio result

    do {
        Node *head = ListFillIn(file);  // llena la lista
        if ( head == NULL ) {  // si el head es igual a NULL sale del ciclo
            break;
        }
        // ESCOGER CUAL DE LAS DOS FUNCIONES DE ABAJO USAR...
        if (op == 1) // si en el argumento de main(reverse string) se pone 1
        { // entonces el head realizará el volteo de palabras
            head = WordReverse(file, resultfile, head);

        } else if  (op == 2){
            // entonces el head realizará el volteo de las letras de las palabras
            head = ReverseSomeWords(file, resultfile, head);

        } else {
            // si no se aplica ninguna de las opciones anteriores se imprime opcionno valida  ...
            printf("Opcion invalida");
            break;
        }
        WriteResult(resultfile, head); // escribe el resultado en el archivo result.txt
        PrintCadenita(head); // imrpime la cadena final
    } while ( 1 );
    fclose(file); // cierre del archivo input
    fclose(resultfile); // cierre del archivo result
}



