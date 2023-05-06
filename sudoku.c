#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define FIL 9
#define COL 9

typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int subMatricesValidas(int sudoku[][COL], int k)
{
  int *busq = (int*) calloc(10,sizeof(int));

  for(int p = 0; p < 9; p++)
  {
    int i=3*(k/3) + (p/3) ;
    int j=3*(k%3) + (p%3) ;
    
    if(sudoku[i][j] !=0)
    {
      busq[sudoku[i][j]] +=1;

      if(busq[sudoku[i][j]] ==2)
      {
        free(busq);
        return 0;
      }
    }
  }
  
  free(busq);
  return 1;
  
}

int is_valid(Node* n)
{
  int fil[9] = {0} ;
  int i, j,num;

    // filas
  for(i=0; i<9; i++)
  {
    for(j=0; j<9; j++)
    {
      num = n->sudo[i][j];
      if(num == 0) continue;
      if(fil[num-1] == 1) return 0; 
      fil[num-1] = 1;
    }
    for (int k = 0; k < 9; k++) 
    {
        fil[k] = 0;
    }
  }
  
  int col[9] = {0};
    //columnas
  for(i=0; i<9; i++)
  {
    for(j=0; j<9; j++)
    {
      num = n->sudo[j][i];
      if(num == 0) continue;
      if(col[num-1] == 1) return 0; 
      col[num-1] = 1;
    }
    for (int k = 0; k < 9; k++) 
    {
    col[k] = 0;
    }    
  }
  

  //3x3
  for (int k = 0; k < 9; k++) 
  {
    if(subMatricesValidas(n->sudo,k)==0 )return 0;
  }
  
  return 1;
}


List* get_adj_nodes(Node* n){
  
  List* list=createList();
  int esta = 0;
  int i, j, k;
  
  for ( i = 0; i<9; i++)
    {
      for( j = 0; j<9; j++)
      {
        
        if(n->sudo[i][j] == 0)
        {
          esta =1;
          for( k=1;k<=9;k++)
          {
            Node* nodito=copy(n);
            nodito->sudo[i][j]=k;
            if (is_valid(nodito) == 1)
            {
              pushBack(list, nodito);
              print_node(nodito);
            }
            else 
            {
              free(nodito);
            }
            
          }
          break;
          //return list;
        }
        if(esta == 1)
        {
          break;
        }
      }
      
    }
  return list;
}


int is_final(Node* n){
  int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(n->sudo[i][j] == 0) return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack(); // Crear una pila vacía
    push(S, n); // Insertar el nodo inicial en la pila

    while (!isEmpty(S)) {
        Node* current = pop(S); // Sacar y eliminar el primer nodo de la pila
        (*cont)++; // Incrementar contador de iteraciones

        if (is_final(current)) {
            // Liberar memoria del stack y del nodo actual
            freeStack(S);
            freeNode(current);
            return current; // Retornar nodo final
        }

        List* adj = get_adj_nodes(current); // Obtener lista de nodos adyacentes
        Node* adj_node;
        for (int i = 0; i < adj->size; i++) {
            adj_node = getElement(adj, i); // Obtener nodo adyacente
            push(S, adj_node); // Insertar nodo adyacente en pila
        }
        freeList(adj); // Liberar memoria de la lista de nodos adyacentes

        freeNode(current); // Liberar memoria del nodo actual
    }

    freeStack(S); // Liberar memoria del stack
    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/