/************************************************************
* programa : exercicio6
*
* autor : Luciano H Barroqueiro  dt 31/05/2016
*
* objetivo : entrar com as informações a respeito de compra
*               e venda de açoes, incluí-los numa lista
*               e mostrar a soma das açoes , considerando
*               compra débito e venda como  crédito
*
*
*************************************************************/


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct Nodo {
    char oper;
    int qtd;
    int val;
    int valTot;
    struct Nodo * next;
} ;


struct milista
{
  struct Nodo* head;
  struct Nodo* tail;
};


struct milista* list_add_element( struct milista*, const int);

struct milista* list_new(void);
struct milista* list_free( struct milista* );
void list_print( const struct milista* );
void list_print_element(const struct Nodo* );
struct milista* list_free( struct milista* );
struct milista* list_remove_element( struct milista*);

struct milista* list_free( struct milista* s )
{
  while( s->head )
    {
      list_remove_element(s);
    }

  return s;
}

struct milista* list_remove_element( struct milista* s )
{
  struct Nodo* h = NULL;
  struct Nodo* p = NULL;

  if( NULL == s )
    {
      printf("Lista vazia\n");
      return s;
    }
  else if( NULL == s->head && NULL == s->tail )
    {
      printf("Agora a lista está vazia\n");
      return s;
    }
  else if( NULL == s->head || NULL == s->tail )
    {
      printf("Erro grave na lista \n");
      printf("O head/tail está vazio enquanto o outro não está\n");
      return s;
    }

  h = s->head;
  p = h->next;
  free(h);
  s->head = p;
  if( NULL == s->head )  s->tail = s->head;

  return s;
}


void list_print( const struct milista* ps )
{
  struct Nodo* p = NULL;

  if( ps )
    {
      for( p = ps->head; p; p = p->next )
    {
      list_print_element(p);
    }
    }

  printf("------------------\n");
}


void list_print_element(const struct Nodo* p )
{
  if( p )
    {
      printf("Operacao = %c\n", p->oper);
      printf("Qtd = %d\n", p->qtd);
      printf("Valor = %d\n", p->val);
      printf("Valor total= %d\n", p->valTot);

    }
  else
    {
      printf("Não é possivel imprimir uma estrutura nula \n");
    }
}


struct milista* list_new(void)
{
  struct milista* p = (struct milista *)malloc( 1 * sizeof(*p));

  if( NULL == p )
    {
      fprintf(stderr, "Erro linha: %d, malloc() falhou alocação\n", __LINE__);
    }

  p->head = p->tail = NULL;

  return p;
}
struct milista* list_add_element(struct milista* s, const char oper, const int qtd, const int val, const int valTot)
{
  struct Nodo* p = (struct Nodo *)malloc( 1 * sizeof(*p) );

  if( NULL == p )
    {
      fprintf(stderr, "Entrada %s, %s: malloc() fracassou \n", __FILE__, "list_add");
      return s;
    }

  p->oper = oper;
  p->qtd =  qtd;
  p->val = val;
  if(oper == 'c')
     p->valTot = -valTot;
  else
     p->valTot = valTot;

  p->next = NULL;


  if( NULL == s )
    {
      printf("Fila não iniciada\n");
      free(p);
      return s;
    }
  else if( NULL == s->head && NULL == s->tail )
    {
      /* printf("Empty list, adding p->num: %d\n\n", p->num);  */
      s->head = s->tail = p;
      return s;
    }
  else if( NULL == s->head || NULL == s->tail )
    {
      fprintf(stderr, "Erro grave ocorreu na inserção da lista\n");
      free(p);
      return NULL;
    }
  else
    {
      /* printf("List not empty, adding element to tail\n"); */
      s->tail->next = p;
      s->tail = p;
    }

  return s;
}

int somaAcao(const struct milista* ps )
{
  struct Nodo* p = NULL;
  int soma =0;
  if( ps )
    {
      for( p = ps->head; p; p = p->next )
    {
      soma = soma + p->valTot;
    }
    }
   return soma;
}

int main()
{
        int soma = 0, qtd = 0 , vlr = 0 , valTot = 0 ;
		char oper = 'c';

        struct milista*  mt = NULL;

        mt = list_new();

        while ('s' != oper)
        {
		    printf("\n Qtde de Açoes ");
            scanf("%d", &qtd );
            printf("\n Valor da Açao ");
            scanf("%d", &vlr );
            valTot = qtd * vlr;
            printf("\nOperação Compra(c) / Venda (v) ou Sair(s) ?  ");
		    scanf("  %c", &oper );
		    if ('c' == oper || 'v' == oper)
            {
                list_add_element(mt, oper, qtd, vlr, vlr * qtd);
            }
		}
        list_print(mt);
        soma =  somaAcao(mt);
        printf("Valor Total em Dinheiro %d" , soma );
        list_free(mt);
        free(mt);
        mt = NULL;

        return 0;
}
