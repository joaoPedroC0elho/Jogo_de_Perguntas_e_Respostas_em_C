/*
 * Jogo de Perguntas e Respostas - Algoritmos e Linguagem C
 * Versão para Windows com seleção aleatória corrigida
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 #include <windows.h>  // Para GetTickCount()
 
 #define NIVEIS 5
 #define PERGUNTAS_POR_NIVEL 3
 
 // Estrutura da pergunta
 typedef struct {
     char pergunta[256];
     char opcoes[4][100];
     int correta; // índice da opção correta (0 a 3)
 } Pergunta;
 
 // Estrutura para armazenar respostas do usuário
 typedef struct {
     Pergunta pergunta;
     int resposta_usuario;
 } RespostaJogador;
 
 // Banco de perguntas [nível][índice]
 Pergunta bancoPerguntas[NIVEIS][PERGUNTAS_POR_NIVEL] = {
     { // Nível 1
         {"Qual o tamanho de um tipo 'int' em C (em bytes)?", {"2", "4", "6", "8"}, 1},
         {"Qual comando exibe algo na tela em C?", {"scanf()", "input()", "printf()", "write()"}, 2},
         {"Qual a função da palavra-chave 'sizeof'?", {"Comparar variáveis", "Ler uma string", "Retornar o tamanho de um tipo de dado", "Converter um valor"}, 2}
     },
     { // Nível 2
         {"Qual operador é usado para módulo (resto da divisão)?", {"%", "/", "*", "&"}, 0},
         {"Qual estrutura condicional é usada para decisões simples?", {"switch", "while", "if / else", "for"}, 2},
         {"Qual o resultado de 10 % 3?", {"0", "1", "2", "3"}, 1}
     },
     { // Nível 3
         {"Qual comando permite repetir instruções enquanto uma condição for verdadeira?", {"switch", "while", "case", "break"}, 1},
         {"Qual comando escolhe uma entre várias opções com base em um valor?", {"if", "switch", "while", "for"}, 1},
         {"Qual comando é usado para laços com número definido de repetições?", {"while", "for", "do-while", "repeat"}, 1}
     },
     { // Nível 4
         {"Qual algoritmo de ordenação compara pares adjacentes e os troca se estiverem fora de ordem?", {"Selection Sort", "Bubble Sort", "Insertion Sort", "Quick Sort"}, 1},
         {"No Selection Sort, qual é a principal operação feita a cada passo?", {"Trocar os dois primeiros elementos", "Escolher o menor valor e colocá-lo na posição correta", "Dividir o vetor ao meio", "Comparar o primeiro e último elemento"}, 1},
         {"Qual estrutura pode ser usada para gerar uma senha aleatória?", {"for e rand()", "if e scanf()", "while e switch", "struct e goto"}, 0}
     },
     { // Nível 5
         {"Qual palavra-chave define uma estrutura de dados personalizada em C?", {"union", "array", "struct", "object"}, 2},
         {"Como acessar um campo de uma struct chamada 'pessoa' com campo 'idade'?", {"pessoa->idade", "pessoa.idade", "pessoa[idade]", "idade.pessoa"}, 1},
         {"Qual estrutura pode representar um labirinto em C?", {"Um único int", "Um vetor de caracteres", "Uma matriz (array bidimensional)", "Uma struct com strings"}, 2}
     }
 };
 
 int main() {
     // Inicializa o gerador de números aleatórios com uma semente mais robusta para Windows
     srand(GetTickCount());
     
     int nivel = 1;
     int acertos = 0;
     RespostaJogador respostas[NIVEIS];
     
     // Matriz para controlar quais perguntas já foram usadas
     int perguntasUsadas[NIVEIS][PERGUNTAS_POR_NIVEL] = {0};
 
     printf("=== JOGO DE PERGUNTAS E RESPOSTAS ===\n");
     printf("Responda corretamente para avançar de nível!\n");
 
     while (nivel <= NIVEIS) {
         // Seleciona uma pergunta aleatória não usada ainda
         int indice;
         do {
             indice = rand() % PERGUNTAS_POR_NIVEL;
         } while (perguntasUsadas[nivel - 1][indice] == 1);
         
         perguntasUsadas[nivel - 1][indice] = 1;  // Marca como usada
         Pergunta p = bancoPerguntas[nivel - 1][indice];
 
         printf("\n[Nível %d] %s\n", nivel, p.pergunta);
         for (int i = 0; i < 4; i++) {
             printf("%d) %s\n", i + 1, p.opcoes[i]);
         }
 
         int resposta;
         printf("Sua resposta: ");
         scanf("%d", &resposta);
 
         // Armazena a resposta do jogador
         respostas[nivel - 1].pergunta = p;
         respostas[nivel - 1].resposta_usuario = resposta - 1;
 
         if (resposta - 1 == p.correta) {
             printf("Correto! Avançando de nível...\n");
             acertos++;
             nivel++;
         } else {
             printf("Errado! Fim de jogo. Você acertou %d níveis.\n", acertos);
             break;
         }
     }
 
     printf("\n=== RESUMO DAS RESPOSTAS ===\n");
     for (int i = 0; i < acertos; i++) {
         Pergunta p = respostas[i].pergunta;
         int marcada = respostas[i].resposta_usuario;
 
         printf("\n[Nível %d] %s\n", i + 1, p.pergunta);
         for (int j = 0; j < 4; j++) {
             printf("%d) %s%s\n", j + 1, p.opcoes[j], (j == p.correta) ? " (correta)" : "");
         }
         printf("-> Sua resposta: %d) %s\n", marcada + 1, p.opcoes[marcada]);
     }
 
     if (acertos == NIVEIS) {
         printf("\nParabéns! Você venceu o jogo respondendo todas as perguntas corretamente!\n");
     }
 
     return 0;
 }