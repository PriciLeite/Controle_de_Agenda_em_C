#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/* função getch*/
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

        void aloca(AGENDA **pAgenda, int *pEntradas);
        void consulta(AGENDA **pAgenda, int iEntradas);

        void qs_ordena(AGENDA **pAgenda[], int left, int right);
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
        fflush(stdin);
        printf("\n1 - Inclusão");            
        printf("\n2 - Alteração");            
        printf("\n3 - Consultar");            
        printf("\n4 - Excluir");            
        printf("\n5 - Pesquisar");            
        printf("\n5 - Sair");              
        printf("\nDigite uma opcao: ");
        scanf("%d", &op);

        if (op == 1)        /* Manipulando ponteiros */
        {
            fflush(stdin);

            aloca(&pAgenda, &iEntradas);   /* Alocar ponteiros em funções será 
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
        





    }while(op != 9);
    
   



    return 0;
}





