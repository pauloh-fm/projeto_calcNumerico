#include <stdlib.h>
#include <stdio.h>
#define MAX 100

int main()

{

       int i, j, n, nmax, k, indice = 0;

       float x[MAX], coef[MAX][MAX], f[MAX];

       printf("**\tPrograma para encontrar uma solução para a matriz utlizando o metodo do Gauss-Seidel\t**\n\n");
       printf("**\tAntes de utilizar o codigo, tenha em mente que so e possivel utilizar ele com matrizes\t**\n");
	   printf("**\tque contenham a diagonal principal preenchida com coeficientes diferentes de 0\t\t**\n\n");
	   printf("**\tPor favor, antes de inserir os dados, reorganize a matriz de forma que a diagonal\t**\n");
	   printf("**\tprincipal nao contenham coeficientes com valor 0\t\t\t\t\t**\n\n");
       // Entrando com o numero de variaveis
	   
       printf("Qual e o numero de equacoes: ");
       scanf("%d", &n);
    
       // Entrando com os coeficientes das equações

       for (i = 1; i <= n; i++){
              printf("Entre com o numero dos coeficientes da linha %d: ", i);
              for (j = 1; j <= n; j++){
                    scanf("%f", &coef[i][j]);
              }

       }
		printf("-------------------------------------------------------\n");
       // Entrando com o f da questao
       for (i = 1; i <= n; i++)  {
              printf("Entre com o F[%d]: ", i);
              scanf("%f", &f[i]);
       }
       printf("-------------------------------------------------------\n");
       // Entrando com o numero maximo de iteracoes
       printf("Entre com o numero maximo de iteracoes: ");
       scanf("%d", &nmax);
       printf("\n");
       printf("Iteracoes\t");
       for (i = 1; i <= n; i++){
              printf("  x%d\t\t", i);
       }
       printf("\n");
       // Inicializa��o do metodo Gauss-Seidel
       for (i = 1; i <= n; i++){
            x[i] = 0;
       }
       for (k = 1; k <= nmax; k++){
              printf("%d\t", k);
              for (i = 1; i <= n; i++) {
                     x[i] = f[i];
                     for (j = 1; j <= n; j++) {
                            if (j != i)
                            {
                                   x[i] = x[i] - coef[i][j] * x[j];
                            } 
							}
                                   x[i] = x[i] / coef[i][i];
					if((x[i]- x[i-1])/x[i] <= 0.0001 && i > indice){
						indice = i;
						continue;
					}
                     printf("%f\t", x[i]); //nessa linha exibe todos os resultados referentes as itera�oes
			}
              printf("\n");  
		}
       // Mostrando a solu��o
       printf("-------------------------------------------------------\n");
       printf("A solucao linear para o problema com o metodo de Gauss-Seidel\n ");
       
       for (i = 1; i <= n; i++) {
              printf("-------------------------------------------------------\n");
              printf("\t X%d = %f\n", i, x[i]); 	  
			  }

		
	
       return 0;

}
