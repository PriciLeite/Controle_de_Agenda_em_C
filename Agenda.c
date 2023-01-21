#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/* função getch */ 
#ifdef DOS 
#include <conio.h>
#else
//#include <curses.h> 
#endif


typedef struct Agenda
{
    char nome[40];
    char email[40];
    int telefone;

}AGENDA;

void alocar(AGENDA **pAgenda, int *pEntradas);
void consultar(AGENDA *pAgenda, int iEntradas);

void qs_ordena(AGENDA pAgenda[], int left, int right);
void ordena(AGENDA pAgenda[], int iEntradas);

void excluir(AGENDA **pAgenda, int *pEntradas);
void pesquisar(AGENDA *pAgenda, int iEntradas);
void alterar(AGENDA *pAgenda, int iEntradas);

int main(void)
{
    AGENDA *pAgenda;

    int iEntradas, op;
    iEntradas = 0;

    pAgenda = (AGENDA *)malloc(sizeof(AGENDA)); //alocando espaço para posição 
                                                // 0 do vetor.

    if (pAgenda == NULL)
    {
        printf("\nErro de alocação de memoria!!!");
        exit(1);
    }
    
   do
   {
        flush(stdin); 
        printf("\n1 - Inclusao"); 
        printf("\n2 - Alteracao"); 
        printf("\n3 - Consultar"); 
        printf("\n4 - Excluir"); 
        printf("\n5 - Pesquisar"); 
        printf("\n9 - Sair"); 
        printf("\nEntre com uma opcao -> "); 
        scanf("%d", &op);

        if( op == 1 ) 
        { 
            fflush(stdin);

            alocar(&pAgenda, &iEntradas);   /* Alocar ponteiros em funções será 
                                                Ponteiro -> Ponteiro*/
            printf("\n=== Inclusão ===\n");
            // Forma1:
            printf("Digite o Nome: ");
            gets((pAgenda+iEntradas)->nome);  /* Endereço do ponteiro inicial + x posições */
            fflush(stdin);

            // Forma2:
            printf("Digite o Email: ");
            gets((*(pAgenda+iEntradas)).email);  /* Endereço do ponteiro inicial + x posições */
            fflush(stdin);
            
            // Forma3: 
            printf("Digite o Telefone: ");
            scanf("%d", &pAgenda[iEntradas].telefone);  /* Trabalhando com vetores nesta forma */
            fflush(stdin);

            iEntradas++;
        } 
        else if (op == 2)
        {
            alterar(pAgenda, iEntradas);
        }
        
        else if (op == 3)
        {
            ordena(pAgenda, iEntradas);
            consultar(pAgenda, iEntradas); /* Será apenas lido não precisa passar *P -> *P */
        }
        
        else if (op == 4)
        {
            ordena(pAgenda, iEntradas);
            excluir(&pAgenda, &iEntradas);
        }
        
        else if (op == 5)
        {
            ordena(pAgenda, iEntradas);
            pesquisar(pAgenda, iEntradas);
        }


    } while(op!=9); 
}


void consultar(AGENDA *pAgenda, int iEntradas) 
{ 
    int i; 
    for(i=0; i < iEntradas; i++) 
    { 
        printf("\n\nRegistro %d", i); 
        printf("\n\tNome: %s", pAgenda[i].nome ); 
        printf("\n\tEmails: %s", pAgenda[i].email ); 
        printf("\n\tTelefone: %d", pAgenda[i].telefone ); 
        getch();
    }
} 

void alterar(AGENDA *pAgenda, int iEntradas)
{   
    char op;
    int i = 0;
    char nome[40];
    printf("Digite o nome: ");
    fflush(stdin);
    gets(nome);
    
    for(i=0; i < iEntradas && strncmp(pAgenda[i].nome, nome, strlen(nome))!=0;i++);
    
    if (i >= iEntradas)
    {
        printf("\nRegistro nao encontrado!!!");
    }


    else
    { 
        printf("\n\tRegistro %d", i); 
        printf("\n\tNome : %s", pAgenda[i].nome ); 
        printf("\n\tEmail : %s", pAgenda[i].email ); 
        printf("\n\tTelefone : %d", pAgenda[i].telefone ); 
        printf("\n\tConfirmar a alteracao(S/N) ?"); 
        op = getch(); 

        if( op == 'S' || op == 's' ) 
        { 
            flush(stdin); 

            /* forma 1 */
            printf("\nEntre com o Nome:"); /* endereço ponteiro inicial + x posições na memória */
            gets((pAgenda+i)->nome);       /*quando se trabalhar com o endereço, deve-se usar -> */ 
            flush(stdin);                                       
            
             /* forma 2 */
            printf("\nEntre com o E-mail:");  /* endereço ponteiro inicial + x posições na memória */ 
            gets((*(pAgenda+i)).email);       /*quando se trabalhar com o endereço, deve-se usar -> */ 
            flush(stdin);

            /* forma 3*/
            printf("\nEntre com o Telefone:"); /* trabalhando como vetor */ 
            scanf("%d", &pAgenda[i].telefone);   
            flush(stdin);

        }
    
    }   

}

void excluir(AGENDA **pAgenda, int *pEntradas)
{   
    char op;
    int i = 0;
    char nome[40];
    printf("Digite o nome: ");
    fflush(stdin);
    gets(nome);
    
    for(i=0; i < *pEntradas && strncmp((*pAgenda)[i].nome, nome, strlen(nome))!=0;i++);
    
    if (i >= *pEntradas)
    {
        printf("\nRegistro nao encontrado!!!");
    }


    else
    { 
        printf("\n\tRegistro %d", i); 
        printf("\n\tNome : %s", (*pAgenda)[i].nome ); 
        printf("\n\tTelefone : %d", (*pAgenda)[i].telefone ); 
        printf("\n\tEmail : %s", (*pAgenda)[i].email ); 
        printf("\n\tConirmar a alteracao ?"); 
        op = getch(); 

        if( op == 'S' || op == 's' ) 
        { 
            flush(stdin); 

            (*pAgenda)[i] = (*pAgenda)[(*pEntradas)-1];

            (*pEntradas)--;
            alocar(pAgenda, pEntradas);

        }

    }   

}

void alocar(AGENDA **pAgenda, int *pEntradas)
{
    (*pAgenda) = (AGENDA *)(realloc(*pAgenda, (*pEntradas +1)*sizeof(AGENDA)));

    if (*pAgenda == NULL)
    {
        printf("\nErro de re-alocacao de memoria!!!");
        exit(1);
    }
    
}

void pesquisar(AGENDA *pAgenda, int iEntradas)
{
    char op; 
    int i=0; 
    char nome[40]; 
    printf("\n\tDigite o Nome:"); 
    flush(stdin); 
    gets(nome); 
    for(i=0; i < iEntradas && strncmp( pAgenda[i].nome, nome, strlen(nome))!=0;i++); 
    
    if( i>= iEntradas ) 
    { 
        printf("\nRegistro nao encontrado"); 
    }

    else 
    { 
        do
        { 
            flush(stdin); 
            printf("\n\n\tRegistro %d", i); 
            printf("\n\tNome : %s", pAgenda[i].nome ); 
            printf("\n\tEmail : %s", pAgenda[i].email ); 
            printf("\n\tFone : %d", pAgenda[i].telefone ); 
            printf("\n\tProximo ?" );
            op = getch(); 
            i++; 

            if(i>=iEntradas) 
            {
                i = 0; 
            } 

        } while(op == 'S' || op == 's');

    }

}

void ordena(AGENDA pAgenda[], int iEntradas)
{
    qs_ordena(pAgenda, 0 , iEntradas-1);
}

void qs_ordena(AGENDA pAgenda[], int left, int right)
{
    register int i, j;
    char *x;
    AGENDA t;

    i = left;
    j = right;
    x = pAgenda[(left + right)/2].nome;

    do
    {
        while(strcmp(pAgenda[i].nome,x)<0 && i<right) i++; 
        while(strcmp(pAgenda[j].nome,x)>0 && j>left) j --; 
        if(i <= j) 
        { 
            t = pAgenda[i]; 
            pAgenda[i]=pAgenda[j]; 
            pAgenda[j]=t; 
            i++; 
            j--; 
        } 
    } while( i <= j); 
    if( left < j ) qs_ordena(pAgenda, left, i); 
    if( i < right) qs_ordena(pAgenda, i, right ); 
}






