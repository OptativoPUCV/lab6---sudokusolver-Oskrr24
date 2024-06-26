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

int is_valid(Node* n){
   //verificar filas, columnas y matrices de 3x3
   for(int i = 0; i < 9; i++){
      int visto[10] = {0};
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] != 0){
         if(visto[n->sudo[i][j]] == 1) 
            return 0;
         else visto[n->sudo[i][j]] = 1;
         }
      }
   }

   for(int j = 0; j < 9; j++){
      int visto[10] = {0};
      for(int i = 0; i < 9; i++){
         if(n->sudo[i][j] != 0){
         if(visto[n->sudo[i][j]] == 1) 
            return 0;
         else visto[n->sudo[i][j]] = 1;
         }
      }
   }

   for(int fila = 0; fila < 9; fila+=3){
      for(int col = 0; col < 9; col +=3){
         int visto[10] = {0};
         for(int i = fila; i < fila+3; i++){
            for(int j = col; j < col+3; j++){
                  if(n->sudo[i][j] != 0){
                     if(visto[n->sudo[i][j]] == 1)
                        return 0;
                     else 
                        visto[n->sudo[i][j]] = 1;
                  }
            }
         }
      }
   }
   
    return 1;
}

List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(n->sudo[i][j]==0){
             for(int k = 1; k <= 9; k++){
             Node*aux = copy(n);
             aux->sudo[i][j]=k;
             if(is_valid(aux))
                pushBack(list, aux);
                else
                free(aux);
             }
             return list;
          }
       }
    }
    return list;
}


int is_final(Node* n){
   for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0)
            return 0;
      }
   }
    return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S = createStack();
   push(S, initial);
   (*cont) = 0;

   while(get_size(S) != 0){
      Node* n = top(S);
      pop(S);
      (*cont)++;
      if(is_final(n)) return n;
      
      List * adj = get_adj_nodes(n);
      Node * adjNode = first(adj);
      while(adjNode != NULL){
         push(S, adjNode);
         adjNode = next(adj);
         
      }
      free(n);
   }
   
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