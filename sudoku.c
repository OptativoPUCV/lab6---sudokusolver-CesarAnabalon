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
    int row[9] = {0}, col[9] = {0}, sub[9] = {0};
    int i, j, r, c, s, num;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            num = n->sudo[i][j];
            if(num == 0) continue;
            if(row[num-1] == 1) return 0; 
            row[num-1] = 1;
        }
        memset(row, 0, sizeof(row));
    }

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            num = n->sudo[j][i];
            if(num == 0) continue;
            if(col[num-1] == 1) return 0; 
            col[num-1] = 1;
        }
        memset(col, 0, sizeof(col));
    }

    // Validar submatrices de 3x3
    for(r=0; r<9; r+=3){
        for(c=0; c<9; c+=3){
            for(i=r; i<r+3; i++){
                for(j=c; j<c+3; j++){
                    num = n->sudo[i][j];
                    if(num == 0) continue;
                    s = (i-r)*3 + (j-c);
                    if(sub[s] == 1) return 0; // ya se repite el número en la submatriz
                    sub[s] = 1;
                }
            }
            memset(sub, 0, sizeof(sub));
        }
    }
    return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  Node* nodito = createNode();
  int i, j, k;
  
  for ( i = 0; i<9; i++)
    {
      for( j = 0; j<9; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          for( k=1;k<=9;k++)
          {
            nodito=copy(n);
            nodito->sudo[i][j]=k;
            pushBack(list, nodito);
          }
          break;
        }
      }
    }
    return list;
}


int is_final(Node* n){
    return 0;
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