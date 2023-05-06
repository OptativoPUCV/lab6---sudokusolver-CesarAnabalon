#include <stdio.h>
#include <stdlib.h>
#include "list.h"


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

int is_valid(Node* n)
{
  int fil[9] = {0} ;
  int i, j, num;

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
  
  int sub[9][10] = {0};
  //3x3
  for (int k = 0; k < 9; k++) 
  {
    int submatrix_start_row = 3 * (k / 3);
    int submatrix_start_col = 3 * (k % 3);
  
    for (int p = 0; p < 9; p++) 
    {
        int i = submatrix_start_row + (p / 3);
        int j = submatrix_start_col + (p % 3);
        int num = n->sudo[i][j];


        if (sub[k][num] == 1) {
            return 0; 
        } else {
            sub[k][num] = 1;
        }
    }
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
          nodito->sudo[i][j] = k;
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
      
    }
    if(esta == 1)
      {
        break;
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