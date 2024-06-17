#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <locale.h>
#include <string>
#include <windows.h> // Biblioteca para usar Sleep no Windows
#include <cstdio>   // Incluir <cstdio> para usar printf

const int ALTURA_SALA = 28;
const int LARGURA_SALA = 100;
const int ALTURA_LABIRINTO = 40;
const int LARGURA_LABIRINTO = 90;

const char PAREDE = '|';
const char ESPACO = ' ';
const char PERSONAGEM = 'P';
const char MONSTRO = 'M';
const char CHAVE = 'K';
const char POCAO = 'P';
const char OBSTACULO = 'X';
const char ITEM = 'o';
const char PORTA = '#';
const char ALAVANCA = 'V';


const int fase2=1;

struct Sala {
    char layout[ALTURA_SALA][LARGURA_SALA];
};

void limparTela() {
    system("cls");
}

void gerarSala(Sala &sala, int &chaves) {
    const int min = 0; // Define o menor número 
    const int max = 29; // Define o maior número 
    bool portaGerada = false; // Variável para controlar se a porta foi gerada

    // Preenche toda a sala com espaços vazios
    for (int i = 0; i < ALTURA_SALA; ++i) { // Percorre as linhas da sala
        for (int j = 0; j < LARGURA_SALA; ++j) { // Percorre as colunas da sala
            sala.layout[i][j] = ESPACO; // Define cada célula como um espaço vazio
        }
    }

    // Coloca paredes nas bordas esquerda e direita da sala
    for (int i = 0; i < ALTURA_SALA; ++i) { // Percorre as linhas da sala
        sala.layout[i][0] = sala.layout[i][LARGURA_SALA - 1] = PAREDE; // Define as bordas esquerda e direita como paredes
        
        
    }

    // Coloca paredes nas bordas superior e inferior da sala
    for (int j = 0; j < LARGURA_SALA; ++j) { // Percorre as colunas da sala
        sala.layout[0][j] = sala.layout[ALTURA_SALA - 1][j] = PAREDE; // Define as bordas superior e inferior como paredes
    }

    // Preenche o interior da sala com paredes, obstáculos e itens aleatoriamente
    for (int i = 1; i < ALTURA_SALA - 1; ++i) { // Percorre as linhas da sala menos as bordas
        for (int j = 1; j < LARGURA_SALA - 1; ++j) { // Percorre as colunas da sala menos as bordas
            int random_number = (rand() % (max - min + 1)) + min; // Gera um número aleatório entre min 0 e max 29

            // Se o número aleatório for 0, coloca uma parede na posição atual
            if (random_number == 0) { // 10% de chance
                sala.layout[i][j] = PAREDE;
                
            }
            // Se o número aleatório estiver entre 1 e 2, coloca um obstáculo
            else if (random_number <= 2) { // 20% de chance
                sala.layout[i][j] = OBSTACULO;
            }
            // Se o número aleatório estiver entre 3 e 4, coloca um item
            else if (random_number <= 3) { // 10% de chance => 10% + 20% = 30% de tudo
                sala.layout[i][j] = ITEM;
            }
             // Se o número aleatório estiver entre 5 e 6 e a porta ainda não foi gerada, coloca uma porta
            else if (random_number <= 6 && !portaGerada) { // 20% de chance => 10% + 20% + 20% = 50% de tudo
                sala.layout[i][j] = PORTA;
                portaGerada = true; // Marca que a porta foi gerada
            } 
            // Colisão com a porta
            else if (sala.layout[i][j] == PORTA && chaves < 10) {
                portaGerada = false; // Marca que a porta foi colidida sem chaves suficientes
                sala.layout[i][j] = ESPACO; // Remove a porta da posição atual
            }
           
        }
    }
}
 
void exibirSala(Sala &sala, char nome_personagem[60], int vida, int chaves, int pocoes, int monstros_encontrados, int vida_extra, int vida_monstros,int moeda,int sorteioVida,int codigoArma, int dano_monstros, int monstros_derrotados) {
    // Configuração do fundo no início
    system("color 3F");

    for (int i = 0; i < ALTURA_SALA; ++i) {
        // Ajuste da cor do texto apenas uma vez por linha
        printf("\x1b[38;5;45m"); 

        for (int j = 0; j < LARGURA_SALA; ++j) {
            // Configuração de cores baseada no tipo de célula
            char caracter = sala.layout[i][j];
            if (caracter == PAREDE) {
                // Paredes (texto preto)
                printf("\x1b[34m"); // Cor do texto: azul
            } else if (caracter == OBSTACULO) {
                // Obstáculos (texto vermelho)
                printf("\x1b[30m"); // Cor do texto: vermelho
            } else if (caracter == ITEM) {
                // Itens (texto verde)
                printf("\x1b[32m"); // Cor do texto: verde
            } else if (caracter == PORTA) {
                // Porta (texto amarelo)
                printf("\x1b[31m"); // Cor do texto: vermelho
            } else {
                // Espaço vazio (texto branco)
                printf("\x1b[37m"); // Cor do texto: branco
            }

            printf("%c", caracter);
        }

        // Impressão das informações adicionais ao lado da sala
        printf("\x1b[38;5;231m"); // Resetar a cor para padrão (texto branco sobre fundo azul)
        printf("  ");
        if (i == 3) {
            printf("Avent:%s", nome_personagem);
        }
        if (i == 4) {
            printf("Vida: %d", vida);
        }
        if (i == 5) {
            printf("Chaves: %d", chaves);
        }
        if (i == 6) {
            printf("Poções: %d", pocoes);
        }
        if (i == 7) {
            printf("Monstros: %d", monstros_encontrados);
        }
        if (i == 8) {
            printf("M. Derrotados:%d", monstros_derrotados);
        }
        if (i == 9) {
            printf("Moedas: %d", moeda);
        }
        if (i == 10) {
            printf("V. Extras: %d", vida_extra);
        }
        
        if (i == 12) {
            printf("\x1b[32m");
            printf("O = ITENS");
            
        }
        if (i == 13) {
            printf("\x1b[30m");
            printf("X = MONSTROS");
        }
        if (i == 14) {
            printf("\x1b[37m");
            printf("P = PRINCÍPE");
        }
        if (i == 15) {
            printf("\x1b[31m"); 
            printf("# = PORTA");
        }
        if (i == 17) {
            printf("OBJETIVO:");
        }
        if (i == 18) {
            printf("COLETE 5 CHAVES");
        }
        if (i == 19) {
            printf("DERROTE 5 MONSTROS ");
        }
        if (i == 20) {
            printf("ABRA A PORTA ");
        }
        if (i == 22) {
            printf("**************** ");
        }
        if (i == 23) {
            printf("O PRINCÍPE ESTÁ ");
        }
        if (i == 24) {
            printf("NO COMEÇO DO MAPA ");
        }
        if (i == 25) {
            printf("**************** ");
        }

        printf("\n");
        
    }
     printf("        Q- Sair.");
    printf("                O- Alterar Sala.");
    printf("                      V- Adicionar vidas extras.");

    // Resetar a cor para padrão (texto branco sobre fundo azul) antes de sair
    printf("\x1b[38;5;231m"); // Cor do texto: branco; Fundo: azul
}


//sala da proxima fase
void faseLabirinto(int x, int y) {

        // Definição do labirinto
        char labirinto[ALTURA_LABIRINTO][LARGURA_LABIRINTO] = {
        "    ##############################################\n",
        "#                                                #\n",
        "#                                                #\n",
        "#    #########################   #################\n",
        "#    #                                           #\n",
        "#    #    ###########    #########################\n",
        "#    #                                       #   #\n",
        "#    ###################    #################    #\n",
        "#                                             #  #\n",
        "#################    #####    #################  #\n",
        "#                                                #\n",
        "#                ###################   ###########\n",
        "#    ###############                             #\n",
        "#                  #                              \n",
        "############################################### V \n",
        "\n\nVá até a saída do labirinto e abra a alavanca.\n V=> Alavanca\n",
        };
        printf("\n\nVá até a saída do labirinto e abra a alavanca.\n V=> Alavanca\n");
        // Exibir o labirinto completo
        for (int i = 0; i < 26; i++) {
             printf("%s\n", labirinto[i]);
        }
    
       int posX = x, posY = y; // Posição inicial do personagem

        // Limpar tela, apaga o labirinto da fase anterior
        limparTela();
    
        // Loop principal da fase do labirinto
        char tecla;
        do {
            // Imprimir labirinto
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 50; j++) {
                    if (i == posY && j == posX) // Posição do personagem
                        printf("P");
                    else
                        printf("%c", labirinto[i][j]);
                }
                printf("\n");
            }
    
            // Capturar movimento do usuário
            tecla = _getch();
    
            int novoX = posX, novoY = posY;
            // Atualizar posição do personagem
            switch (tecla) {
                case 'w':
                case 'W':
                case 72:
                    novoY = posY - 1;
                    break;
                case 's':
                case 'S':
                case 80:
                    novoY = posY + 1;
                    break;
                case 'a':
                case 'A':
                case 75:
                    novoX = posX - 1;
                    break;
                case 'd':
                case 'D':
                case 77:
                    novoX = posX + 1;
                    break;
                case 'q': // Para sair
                    printf("Saindo...\n");
                    return;
                default:
                    break;
            }
            limparTela();
    
            // Verificar se a nova posição é válida
            if (novoX >= 0 && novoX < 50 && novoY >= 0 && novoY < 15 &&
                labirinto[novoY][novoX] != '#') {
                posX = novoX;
                posY = novoY;
            }
            //se o personagem chegar no final do labirinto
            if (labirinto[novoY][novoX] == 'V') {
                    printf("ABRIR ALAVANCA\n");
                    printf(
                            "                                                          ##               ***                                         \n"
                            "                                                        #******       +++****++==                                      \n"
                            "                                                       *********##  +++++++++====+++                                  \n"
                            "                                                      #####****#### +++===++++==++++++++                              \n"
                            "                                                     ####*****########*+=============++=====                          \n"
                            "                                                      *******#######::%#+===============+*****                       \n"
                            "                                                        ****#######%######*++=+****+=+#######%:                      \n"
                            "                                                           **#############*%#+********####**##%:                      \n"
                            "                                                             **#########::%:#######****###:%:###                      \n"
                            "                                                                *########%:****##**###**%#######                      \n"
                            "                                                                 ***#########*%#################                      \n"
                            "                   PARA ABRIR A ALAVANCA                           ***######################****                      \n"
                            "                      PRESSIONE ENTER                              +*****####%####**###*####***#                      \n"
                            "                                                                   ++++++++*#%###******###*####                      \n"
                            "                                                                   *++++*******####*********####                      \n"
                            "                                                                   ###*+****#########*******####                      \n"
                            "                                                                   *##############**#*******####                      \n"
                            "                                                                   ***############**********#***                      \n"
                            "                                                                   *****######******************                      \n"
                            "                                                                   ++***#######******##%#****###                      \n"
                            "                                                                   ++############****#**#######%                      \n"
                            "                                                                    *#######*#####***########%##                      \n"
                            "                                                                       #####***###***####%######                      \n"
                            "                                                                           ****###*+*#*%#######                       \n"
                            "                                                                               ###*++#*%####                          \n"
                            "                                                                                  +++#*%                             \n");
                        
                    getch();
                    printf("\n\n");
                    printf(
                            "                                                                                   ****+                             \n"
                            "                                                                               +++++++====++                         \n"
                            "                                                                              #*+===++===++++++                      \n"
                            "                                                                              ####*==============**                  \n"
                            "                                                                              ####*++++=+***=+*##*#%                 \n"
                            "                                                                              ######*+++******#*##:%                 \n"
                            "                                                                              ##**######***##%*#%###                 \n"
                            "                                                                              *******###############                 \n"
                            "                                                                              *****+**############**                 \n"
                            "                                                                              +++**++***##*****#####                 \n"
                            "                        MASMORRA ABERTA                                       *++++*****###*******##                 \n"
                            "                        PRESSIONE ENTER                                       ######%#######******##                 \n"
                            "                                                                              **###%######********#*                 \n'                            \n"
                            "                                                                              **:%:####%************                 \n"                             
                            "                                                                              +#*%#**#%****#%*:***#%                 \n"
                            "                                                                              ###***#*%###**#%##*::%                 \n"
                            "                                                                            #####****%####**#%*:%###                 \n"
                            "                                                                           ####*****%##*##*+**%#####                 \n"
                            "                                                                          ####*****%###  #*+**###%#                     \n"
                            "                                                                         #%*/%***%####                               \n"
                            "                                                                        ####***%/%##                                 \n"
                            "                                                                       ####***:%###                                  \n"
                            "                                                                      *#*****:%###                                   \n"
                            "                                                                     ###****#####                                    \n"
                            "                                                                    ###****#####                                     \n"
                            "                                                                       %#######                                      \n"
                            "                                                                          %###                                       \n");
                printf("\n\n\n\n\n\n\n\n");
                getch();
                printf("VOCÊ ENCONTROU A PRINCESA :)");
                 printf(
                    "                                          ##**##*+*\n"
                    "                                        =+++++++++*#\n"
                    "                                      +++++****#+*++=\n"
                    "                                     =++++**###**##+\n"
                    "                                     ++***+*#**###%\n"
                    "                                    =+*+***+++++%+\n"
                    "                                    +++****+#**#**\n"
                    "                                  ++++++**#*+*%*++\n"
                    "                                =+++++++***%@%#*++=\n"
                    "                              =++**********+*++****\n"
                    "                             =+*++++++++++++++++**\n"
                    "                             =*+#+*##%@@@@@@@@@@%%%\n"
                    "                              +**#*##%@@@%%%%%%%@%%@\n"
                    "                              =##**#%%@@@@@@@@@@@@@\n"
                    "                              +*#*##%@@@@@@@@@@@@@@\n"
                    "                               #*##%%%%%@@@@@@@@@@\n"
                    "                               #*#%#+*##%%@@@@@@@\n"
                    "                               #*###   ##%@%@@@@%\n"
                    "                                %####  *##***##%%%\n"
                    "                                 %##% %#****##%%#*#\n"
                    "                                  %##%##***###%%###\n"
                    "                                    #%####%###%%##%\n"
                    "                                   *###%%%%###%%##%\n"
                    "                                ***+###%%%####%%##%\n"
                    "                                  +*##%%%%###%%%##%\n"
                    "                                   %##%%%%###%%%##%%\n"
                    "                                   ##%##%%%#%%%%##%%\n"
                    "                                  %##%#%%%%%%%%%##%%\n"
                    "                                  %#%#%%%%%%%%%%#%%%\n"
                    "                                  ##%#%%%%%%%%%%#%%%\n"
                    "                                 ####%%%%%%%%%%%#%##\n"
                    "                                %#%#%%%%%%%%%%%%#%##\n"
                    "                               %###%%%%%%%%%%%%%%##%\n"
                    "                              %####%#%%%%%%%%%%#%##%%\n"
                    "                              %%##%#%%%%%%%%%%%%%#%%#\n"
                    "                             %###%%#%%%%%%%%%%%%%#%%#\n"
                    "                            %###%%#%%%%%%%%%%%%%%#%###\n"
                    "                           %###%%#%%%%%%%%%%%%%%##%###%\n"
                    "                         ###%%%#%%#%%%#%%%%%%%%%##%#%%##\n"
                    "                      %###%%%%#%%##%%##%%%%%%@%%##%#%%##%\n"
                    "                     ####%%%%##%##%%##%%%%%%%@%%##%#%%###\n"
                    "                  %#####%%%%##%###%###%%%%%%%%%%###%%%%##%\n"
                    "               %%#####%%%%##%%########%%%%%%%%%%%##%#%%###%\n"
                    "            %#######%%%%###%%#########%%%%%%%%%%%####%%%####%\n"
                    "        #########%%%%%###%%%###########%%%%%%#%%%%####%%%######\n"
                    "    #####%#####%%%%####%%%%############%%%%%%%#%%%####%%%%###%###%\n"
                    "     #######%%%%%###%%%#################%%%%%%#%%%%####%%%%###%%%%\n"
                    "           %%####%%######################%%%%%%#%%%%####%%%%####%\n"
                    "                     %%#####################%%%%###%\n"
                );
                getch();
                printf("\n\n\n\n\n\n");
                printf(" E CONSEGUIU RESGATA-LÁ! :) \n\n");
                
                printf(
                        "                                      +#%@@%%%@#-                                   \n"
                        "                                     #@%%%%%%%%%%%@*                                \n"
                        "                                    %%%%%%%%%%%%%%%%%#                              \n"
                        "                                   +@%%%%%%%%%%%%%%%%%@*                            \n"
                        "                                  +@%%%%%%%%%%%%%%%%@@%%%.                          \n"
                        "                                 %@%%%%%%%%%%%@%%%%%%@@@@:                          \n"
                        "                                .%%@@%%%%###*#%%%####%#-                            \n"
                        "                             ##%#********#********#%*++-                            \n"
                        "                            :@@@@@@@%***********#=+***+**%@@#**+=-                  \n"
                        "                          +@@@@@@@@@@@@*********- :*******#@@*****+                 \n"
                        "                      .*@@@@@@@@@@@@@@@@#***+.      =+*****%@#*****+                \n"
                        "                 -+@@@@@@@@@@@@@@@@@@@@@@*=        .*#++****@#******=               \n"
                        "             %@@%##%@@@@@@@@@@@@@@@@@@@@+          -+%#+=+**%#****+*+.              \n"
                        "           .@@@%#######%@@@@@@@@@@@@@@@@#        .====-+==+******+**+-              \n"
                        "          =@@@%##############%%%%%%%%%%%%#:      .+=======******+*+**+              \n"
                        "         .@@@@###########################%@@.     *+=====+*****+*+*+*+              \n"
                        "         +@@@%#######################%@@@@@@@@+  .====+++****+**+****+              \n"
                        "         @@@@%######################@@@@@@@@@@@@*     +=***+******+**=              \n"
                        "        =@@@@%####################%@@@@@@@@@@@@@@=   :=+**+***+**+***+              \n"
                        "        @@@@@%####################@@@@@@@@@@@@@@@@  .-+*********++****=             \n"
                        "       .@@@@@@###################@@@@@@@@@@@@@@@@@*+==*********++******-            \n"
                        "       *@@@@@@%#################%@@@@@@@@@@@@@@@@@#===++******+*********=           \n"
                        "       @@@@@@@@%#############%##@@@@@@@@@@@@@@@@@@#====******+*+*****+*+**.         \n"
                        "      #@@@@@@@@@%############%%#%@@@@@@@@@@@@@@@@@#====*******+******+****+         \n"
                        "     :@@@@@@@@= +#############%%%%@@@@@@@@@@@@@@@@#====**+**+*+******+**+**.        \n"
                        "     @@@@@@@@    ############%%#%%%@@@@@@@@@@@@@@@%====+*+**++******+***+*+         \n"
                        "     @@@@@@@%     #############%%%%%%@@@@@@@@@@@@@@=@@@@#+*+*+**********+=          \n"
                        "     -@@@@@@*     :###############%%%%%%@@@@@@@@@@@%@@@@@%*+*+*******+****+.        \n"
                        "      @@@@@@=      +####################+ #@@@@@@@@@@@@@@@#*+*+**+*++**++**:        \n"
                        "                    ###################*   =@@@@@@@@@@@@@@@@**+**++***+*+*+         \n"
                        "                                 -+++*=     =@@@@@@@@@@@@@@@@%*+***+++*+.           \n"
                        "                                              @@@@@@@@@@@@@%-  :++****+             \n"
                        "                                               %@@@@@%#:                             \n");
                _getch();
                printf("\n\n\n\n\n");    
                printf("           COMO FORMA DE AGRADECIMENTO O REI TE PRESENTEOU COM UM DIAMANTE \n");                         
                printf(
                        "                   .     '     ,                                   \n"
                        "                     _________                                     \n"
                        "                    /_|_____|_\       MISSÃO CONCLUIDA COM SUCESSO \n"
                        "                    '. \    / .'               PARABÉNS            \n"
                        "                      '.\  /.'          VOCÊ SE MOSTROU CORAJOSO   \n"
                        "                        '.'                                        \n");
                _getch();
                printf("\n");
                printf("=================================\n");
                printf("Pressione Q 2x para sair do jogo.\n"); 
                printf("=================================\n\n");
                printf("\n\n\n\n\n");
                       
                       
                       
                       
                                                                                                     
                                                                                     
  
       
       
            }
        } while (tecla != 'q'); // Sair
        
        
    
}



int main() {

   
    
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("color 30"); // Define as cores padrão do console
    printf("\n============================================================================================================\n");
    printf("                                        Bem-vindo ao Reino do Mistério!");
    printf("\n============================================================================================================\n");

    printf("\n               Um aventureiro corajoso entra em uma masmorra lendária em busca de fama e fortuna.\n");
    printf("\n");
    printf("                   No entanto, ele descobre que a masmorra também é o local onde uma princesa \n");
    printf("                                   foi aprisionada por um malvado feiticeiro.\n");
    printf("\n");
    printf("\n");
    printf("            O aventureiro decide ajudar a princesa, mas para fazer isso, ele precisa coletar recursos \n");
    printf("                          suficientes para desbloquear a cela onde ela está presa.\n");
    printf("\n");
    printf("\n");
    printf("             Você é o aventureiro corajoso e determinado a resgatar a princesa do castelo sombrio.\n");
    printf("\n============================================================================================================\n");
    printf("\n============================================================================================================\n");
    printf("                                Pressione ENTER para começar sua jornada!");
    printf("\n============================================================================================================\n");
    printf("\n============================================================================================================\n");
    getchar(); // Aguarda o pressionar da tecla ENTER
    printf("\n\n\n\n\n\n\n\n");

    printf("\n                         Você está diante do castelo, um lugar cheio de magia e mistério.\n");
    printf("\n");
    printf(
            "                           /\\                                                        /\\\n"
            "                          |  |                                                      |  |\n"
            "                         /----\\                A PRINCESA CORRE PERIGO!            /----\\\n"
            "                        [______]                  QUAL A SUA DECISÃO?             [______]\n"
            "                         |    |         _____                        _____         |    |\n"
            "                         |[]  |        [     ]                      [     ]        |  []|\n"
            "                         |    |       [_______][ ][ ][ ][][ ][ ][ ][_______]       |    |\n"
            "                         |    [ ][ ][ ]|     |  ,----------------,  |     |[ ][ ][ ]    |\n"
            "                         |             |     |/'    ____..____    '\\|     |             |\n"
            "                          \\  []        |     |    /'    ||    '\\    |     |        []  /\n"
            "                           |      []   |     |   |o     ||     o|   |     |  []       |\n"
            "                           |           |  _  |   |     _||_     |   |  _  |           |\n"
            "                           |   []      | (_) |   |    (_||_)    |   | (_) |       []  |\n"
            "                           |           |     |   |     (||)     |   |     |           |\n"
            "                           |           |     |   |      ||      |   |     |           |\n"
            "                         /''           |     |   |o     ||     o|   |     |           ''\\\n"
            "                        [_____________[_______]--'------''------'--[_______]_____________]\n"
            "                        __________________________________________________________________\n"
            "                        |                                                                |\n"
            "                        |         | 1- RESGATAR A PRINCESA |     | 2 - DESISTO |         |\n"
            "                        \\______________________________________________________________//\n"
    );

    char escolha;
    char nome_personagem[60]; 
    int vida = 100;
    int chaves = 0;
    int pocoes = 0;
    int monstros_encontrados = 0;
    int vida_extra=0;
    int vida_monstros=  (rand() % (50 - 15 + 1)) + 15;
    int moeda=0;
    int codigoArma=0;
    int dano_monstros=0;
    int sorteioVida=0;
    int monstros_derrotados=0;
    
    int vida_monstro=0;
   
    
    
    do {
        escolha = _getch();
    } while (escolha != '1' && escolha != '2');

    if (escolha == '1') {
        printf("\nVocê avança corajosamente em direção à entrada do castelo...\n");
        printf("Digite o seu nome corajoso(a) aventureiro(a): ");
        scanf("%s", nome_personagem);
        printf("Sua aventura está apenas começando!\n");
        getchar(); // Aguarda o pressionar da tecla ENTER
        printf("\n\n\n\n\n");

        printf("\n                                                   SUA MISSÃO: \n");
        printf("\n                  Encontre as 5 chaves e derrote 5 monstros para abrir a masmorra e resgate a princesa! :) \n");
        printf("\n                         Tome cuidado com seu caminho, monstros e obstáculos te esperam....\n");
        printf("\n\n\n\n");
        printf("                                               Pressione ENTER para começar!");
        getch();
        
    } else {
        printf("\nVocê decide voltar atrás e desistir da missão. Medrosoo....\n");
        printf("Infelizmente, a princesa permanecerá prisioneira para sempre...\n");
        printf("                    Fim de jogo.\n");
        Sleep(4400);
        return 0;
    }

    srand(time(0));
    
    Sala salaAtual;
    gerarSala(salaAtual, chaves);
    int posX = 1, posY = 1;

    salaAtual.layout[posY][posX] = PERSONAGEM;

    while (true) {
        limparTela();
        exibirSala(salaAtual, nome_personagem, vida, chaves, pocoes, monstros_encontrados, vida_extra, vida_monstros,moeda, sorteioVida,codigoArma, dano_monstros, monstros_derrotados);

        char tecla = _getch();

        int novoX = posX, novoY = posY;
        switch (tecla) {
            case 'w':
            case 'W':
            case 72:
                novoY = posY - 1;
                break;
            case 's':
            case 'S':
            case 80:
                novoY = posY + 1;
                break;
            case 'a':
            case 'A':
            case 75:
                novoX = posX - 1;
                break;
            case 'd':
            case 'D':
            case 77:
                novoX = posX + 1;
                break;
            case 'O':
            case 'o':
                gerarSala(salaAtual, chaves);
                posX = 1;
                posY = 1;
                salaAtual.layout[posY][posX] = PERSONAGEM;
                break;
            case 'V':
            case 'v':
                if(vida_extra > 0){
                   vida+=vida_extra;
                   printf("Vida extra adicionada!");
                   vida_extra=0;
                }else{
                   printf("Você não tem vida extra. :(");
                }
                break;
            case 'q':
            case 'Q':
                return 0;
        }

        if (salaAtual.layout[novoY][novoX] != PAREDE) {
            salaAtual.layout[posY][posX] = ESPACO;
            if (salaAtual.layout[novoY][novoX] == OBSTACULO) {
                // Lógica para combate com o monstro
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 64 /*Cor 0 a 225*/); // Muda a cor do texto para verde
                printf("\n                        VOCÊ ENCONTROU UM MONSTRO!\n");
                printf("\nCOMPRE SUA ARMA PARA DERROTAR O MONSTRO \nDigite o código correspondente!\n");
                
                printf("\n       ESPADA       ARCO E FLECHA      MACHADO\n"
                       " DANO:     40             35                50   \n"
                       " CUSTO:    10m             5m                15m  \n"
                       " CÓDIGO:    1               2                 3    \n");
                printf("CÓDIGO: 4 => Não tenho moedas, vou deixar a sorte decidir...\n");
                scanf("%d", &codigoArma);
                if(codigoArma==1){
                   if(moeda>=10){
                      printf("COMPROU UMA ESPADA\n");
                        printf("\n");
                        printf("          / \\                              \n");
                        printf("         {   }                                \n");
                        printf("         !   !                                \n");
                        printf("         ; : ;                                \n");
                        printf("         | : |                                \n");
                        printf("         | : |                                \n");
                        printf("         l ; l                                \n");
                        printf("         l ; l                                \n");
                        printf("         I ; I                                \n");
                        printf("         I ; I                                \n");
                        printf("         I ; I                                \n");
                        printf("         I ; I                                \n");
                        printf("         d | b                                \n");
                        printf("         H | H                                \n");
                        printf("         H | H                                \n");
                        printf("         H I H                                \n");
                        printf(" ,;,     H I H     ,;,                        \n");
                        printf(";H@H;    ;_H_;,   ;H@H;                       \n");
                        printf("`\\Y/d_,;|4H@HK|;,_b\\Y/'                    \n");
                        printf(" '\\;MMMMM$@@@$MMMMM;/'                     \n");
                        printf("   \"~~~*;!8@8!;*~~~\"                       \n");
                        printf("         ;888;                              \n");
                        printf("         ;888;                              \n");
                        printf("         ;888;                              \n");
                        printf("         ;888;                              \n");
                        printf("         d8@8b                              \n");
                        printf("         O8@8O                              \n");
                        printf("         T808T                              \n");
                        printf("          `~`                                \n");
                        moeda=moeda -10;
                   }else{
                        printf("VOCÊ NÃO TEM MOEDAS SUFICIENTES\n");
                   }
                }else if(codigoArma==2){
                    if(moeda>=5){
                        printf("VOCÊ COMPROU UM ARCO E FLECHA\n");
                        printf("          4$$-.                                 \n");
                        printf("           4   '.                              \n");
                        printf("           4    ^.                             \n");
                        printf("           4     $                             \n");
                        printf("           4     'b                            \n");
                        printf("           4      'b.                          \n");
                        printf("           4        $                          \n");
                        printf("           4        $r                         \n");
                        printf("           4        $F                         \n");
                        printf("-$b========4========$b====*P=-                 \n");
                        printf("           4       *$$F                        \n");
                        printf("           4        $$\"                        \n");
                        printf("           4       .$F                         \n");
                        printf("           4       dP                          \n");
                        printf("           4      F                            \n");
                        printf("           4     @                             \n");
                        printf("           4    .                              \n");
                        printf("           J.  H                               \n");
                        printf("          '$$ '                                \n");
                        moeda=moeda - 5;
                    }else{
                        printf("VOCÊ NÃO TEM MOEDAS SUFICIENTES\n");
                    }
                }else if(codigoArma==3){
                    if(moeda>=15){
                        printf("                     _,,--.._                    \n");
                        printf("                    /. ` ` .  `.                \n");
                        printf("                    )|       `  `.              \n");
                        printf("       .           / |         `  `             \n");
                        printf("        `.        / /            ` `            \n");
                        printf("         `.`.    / /              ` `           \n");
                        printf("           `.`.'' /                ' :          \n");
                        printf("            <','/'`                . ;          \n");
                        printf("           ,-'.-    `             , /           \n");
                        printf("       _.-',-^`       `      _.-----            \n");
                        printf(" /`==::.,-'     `       ` ,-                    \n");
                        printf("/ /               `     .;                      \n");
                        printf("| |..               ` .,' `.                    \n");
                        printf("| ':`....---.       ,'`'.   `                   \n");
                        printf(" .`:.:.:.:.:-..    /     `.   `.                 \n");
                        printf("  .`ccoccoccoc'``./        `.   `.               \n");
                        printf("   `.`CQCCQCCCQCC/           `.   `.             \n");
                        printf("     `.`8O8O8O8O8(             `.   `.           \n");
                        printf("       `.`_-_@-@_-;              `. .'''.        \n");
                        printf("            '""'                   :,' ,--'      \n");
                        printf("                                    `.` _,--            \n");
                        printf("                                      `.  _,',.        \n");
                        printf("                                        `. .-' `_          \n");
                        printf("                                          `. ,-^.`   \n");
                        printf("                                            `. - _.´      \n");
                        printf("                                              `.', '-´    \n");
                        printf("                                                `. _,-´__   \n");
                        printf("                                                  `. _=, | \n");
                        printf("                                                    |, = |      \n");
                        printf("                                                    '----'   \n");
                        moeda=moeda - 15;
                    }else{
                        printf("VOCÊ NÃO TEM MOEDAS SUFICIENTES\n");
                    }
                }else if(codigoArma==4) {
                    printf("CONSIGA MAIS MOEDAS PARA PRÓXIMA!!\n");
                }else{
                  printf("Código Inválido\n");
                }
               Sleep(800);
                
                /*Sortear o monstro */
                vida_monstros=  (rand() % (50 - 15 + 1)) + 15;
                int sorteioMonstro = rand() % 3;
                switch (sorteioMonstro) {
                    case 0:
                        printf( " _____________________________________________________________________ \n"
                                "|                                   ___                                   |\n"
                                "|                                .-'   `'.                                |\n"
                                "|                               /         \\                               |\n"
                                "|                               |         ;                               |\n"
                                "|                               |         |           ___.--,             |\n"
                                "|                      _.._     |0) ~ (0) |    _.---'`__.-( (_.           |\n"
                                "|               __.--'`_.. '.__.\\    '--. \\_.-' ,.--'`     `--`           |\n"
                                "|              ( ,.--'`   ',__ /./;   ;, '.__.'`                          |\n"
                                "|              _`) )  .---.__.' / |   |\\   \\__..--_--_--_--.,_            |\n"
                                "|             `---' .'.''-._.-'`_./  /\\ '.  \\ _.-~~~````~~~-._`-.__.-     |\n"
                                "|                   | |  .' _.-' |  |  \\  \\  '.               `~---`      |\n"
                                "|                    \\ \\/ .'     \\  \\   '. '-._)                          |\n"
                                "|                     \\/ /        \\  \\    `=.__`~-.                       |\n"
                                "|                     / /\\         `) )    / / `--.`\\                     |\n"
                                "|               , _.-'.'\\ \\        / /    ( (     / /                     |\n"
                                "|                `--~`   ) )    .-'.'      '.'.  | (                      |\n"
                                "|                       (/`    ( (`          ) )  '-;                     |\n"
                                "|                        `      '-;         (-'                           |\n"
                                "|                                                                         |\n");
                        Sleep(2000);
                        break;
                    case 1:
                        printf(   "                   ,                   \\       '-,-`,'-.' | ._         \n"
                                  "                  /|           \\    ,   |\\         }  )/  / `-,',       \n"
                                  "                 [ ,          |\\  /|   | |        /  ||  |/`  ,`        \n" 
                                  "                | |       ,.`  `,` `, | |  _,...(   (      .',          \n"
                                  "               \\  \\  __ ,-` `  ,  , `/ |,'      Y     (   /_L\\        \n"
                                  "                 \\  \\,``,   ` , ,  /  |         )         _,/         \n"
                                  "                  \\ '  `  ,_ _`_,-,<._.<        /         /            \n" 
                                  "                   ', `>.,`  `  `   ,., |_      |         /             \n"
                                  "                     /`  `,   `   ,`  | /__,.-`    _,   `|             \n"
                                  "                 -,-..|  _  |  `  /  ,  / `._) _,-|`       |            \n"
                                  "                  |_,,.) /|    ` /  / ) (-,, ``    ,        |           \n"
                                  "                 ,` )  |   |       '-`  |  `(               |           \n"
                                  "                /  /```(   , --, ,' |   |`<`    ,            |          \n"
                                  "               /  /_,--`|   <|  V /> ,` )<_/)  | |      _____)          \n"
                                  "         ,-, ,`   `   (_,|    |   /) / __/  /   `----`                \n"
                                  "        (-, |           ) \\('_.-._)/ /,`    /                          \n"
                                  "        | /  `          `/ \\ V   V, /`     /                           \n" 
                                  "    ,--|(        ,     <_/` |     ||      /                             \n"
                                  "    (   ,``-      /|         |-A.A-`|     /                             \n"
                                  "   ,>,_ )_,..(    )|          -,,_-`  _--`                              \n"
                                  "  (_ / `   _,/_  /  |_            ,--`                                  \n"
                                  "   |( `   <.,../`     `-.._   _,-`                                      \n");
                         Sleep(2000);
                         break;
                     case 2:
                         printf("                    ,     .                                           \n"
                                "                    /(     )\\               A                         \n"
                                "               .--.( `.___.' ).--.         /_\\                         \n"
                                "               `._ `%_&%#%$_ ' _.'     /| <___> |\\                     \n"
                                "                  `|(@|*%%/@)|'       / (  |L|  ) \\                     \n"
                                "                   |  |%%#|  |       J d8bo|=|od8b L                    \n"                
                                "                    \\ $#%/ /        | 8888|=|8888 |                    \n"
                                "                    | |%%#|/|        J Y8P*|=|*Y8P F                      \n"
                                "                    | (.*.)%|        \\ (  |L|  ) /                      \n"
                                "                ___.'  `-'  `.___      \\|  |L|  |/                         \n"
                                "              .'#*#`-       -'$#*`.       / )|                               \n"
                                "             /#%^#%*_ *%^%_  #  %$%\\   .J (__)                             \n"
                                "             #&  . %%%#% ###%*.   *%\\-'&# (__)                              \n"
                                "             %*  J %.%#_|_#$.|J \\ %'#%*^  (__)                                \n"
                                "             *#% J %$%%#|#$#$ J|%   *   .--|(_)                                \n"
                                "             |%  J| `%%#|#%%' / `.   _.'   |L|                                \n"
                                "             |#$%||` %%%$### '|   `-'      |L|                                \n"
                                "             (#%%||` #$#$%%% '|\\          |L|                                \n"
                                "             | ##||  $%%.%$%  | |          |L|                                \n"
                                "             |||||(__ $F J$ __) |          |L|                                 \n"
                                "             `||| J#%$ | |%%#%L            |L|                                  \n"
                                "                  |$$%#& & %%#|            |L|                                \n"
                                "                  J##$ J % %%$F            |L|                                 \n"
                                "                   %$# * * %#&             |L|                                \n"
                                "                   %#$ | |%#$%             |L|                                \n"
                                "                   *#$%| | #$*             |L|                                \n"
                                "                  /$#' ) ( `%%\\                                            \n"
                                "                 /#$# /   \\ %$%\\                                             \n"
                                "                ooooO'     `Ooooo                                             \n");
                         Sleep(2000);
                         break;
                }
                printf("VIDA DO MONSTRO: %d\n", vida_monstros);
                Sleep(900);
                int dano_monstros;
                if(codigoArma==4){
                        dano_monstros= rand() % 40;
                        vida_monstros= vida_monstros - dano_monstros;
                }else if(codigoArma==1){
                        dano_monstros=40;
                        vida_monstros-=40;
                }else if(codigoArma==2){
                        dano_monstros=35;
                        vida_monstros -= 35;
                }else if(codigoArma==3){
                        dano_monstros=50;
                        vida_monstros -= 50;
                }
                printf("VIDA DO MONSTRO APÓS O DANO: %d\n", vida_monstros);
                Sleep(800);
                
                if(vida_monstros<=0){
                        printf("\nVOCÊ DERROTOU O MONSTRO! \n");
                        salaAtual.layout[novoY][novoX] = ESPACO; // Remove o monstro do mapa
                        monstros_encontrados++;
                        monstros_derrotados++;
                       system("color 30"); // Restaura as cores padrão do console
                }else if(vida_monstros>0){
                        printf("\nVOCÊ PERDEU A BATALHA COM O MONSTRO! \n");
                        Sleep(500);
                        salaAtual.layout[novoY][novoX] = ESPACO;
                        monstros_encontrados++;
                        int sorteioVida = rand() % 4; //gera um número aleatorio no intervalo de 0 a 3
                        int vidaPerdida=10;
                        switch(sorteioVida){
                            case 0:
                                 vida -= 15;
                                 vidaPerdida=15;
                                 break;
                            case 1:
                                 vida -= 25;
                                 vidaPerdida=25;
                                 break;
                            case 2:
                                 vida -= 30;
                                 vidaPerdida=30;
                                 break;
                            case 3:
                                 vida -= 35;
                                 vidaPerdida=35;
                              break;
                            default:
                              break;
                        }
                        printf("\n-%d VIDAS \n", vidaPerdida);
                        _getch();
                        system("color 30"); // Restaura as cores padrão do console   
                        if (vida <= 0) {    
                        // Imprime mensagem de fim de jogo caso o jogador perca toda a vida
                        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 64 /*Cor 0 a 225*/); // Muda a cor do texto para verde
                        printf(".                                                          .\n"
                               ".                      FIM DO JOGO                         .\n"
                               ".                                                          .\n"
                               ".                        ________                           .\n"
                               ".                     .-/        \\-.                        .\n"
                               ".                     //          \\                        .\n"
                               ".       _            |              |          _             .\n"
                               ".      ( \\          |,  .-.  .-.  ,|         / )           .\n"
                               ".       > \"=._      | )(__/  \\__)( |     _.=\" <          .\n"
                               ".      (_/\"=._\"=._ |/     /\\     \\| _.=\"_.""-)         .\n"
                               ".             \"=._ (_     ^^     _)\"_.=\"                 .\n"
                               ".                 \"=\\__|IIIIII|__/=\"                    .\n"
                               ".                _.=\"| \\IIIIII/ |\"=._                   .\n"
                               ".      _     _.=\"_.=\"\\         /\"=._\"=._     _       .\n"
                               ".     ( \\_.=\"_.=\"     `-------`     \"=._\"=._/ )      .\n"
                               ".      > _.=\"                            \"=._ <          .\n"
                               ".     (_/                                    \\_)          .\n");
                        Sleep(6500);
                        printf("                     Você morreu. Fim de jogo.\n");
                        printf("                      NÃO CONCLUIU A MISSÃO :( \n");
                        return 0;
                        }
                    
                }                    
                    
            }
             else if (salaAtual.layout[novoY][novoX] == ITEM) {
                salaAtual.layout[novoY][novoX] = ESPACO; // Remove o item do mapa
                // Lógica para encontrar um item
                printf("\n\n");
                printf("         VOCÊ ENCONTROU UM BAÚ\n");
                // Desenha o baú na tela
                printf(" _________________________________________\n"
                       "/                                         \\\n"
                       "|              BAÚ ABERTO!!               |\n"
                       "|                                         |\n"
                       "|                  ___________            |\n"
                       "|                /\\____;;___\\           |\n"
                       "|               | /         /             |\n"
                       "|               `. ())oo() .              |\n"
                       "|                |\\(%()*^^()^\\          |\n"
                       "|               %| |-%-------|            |\n"
                       "|               % \\ | %  ))   |          |\n"
                       "|               %  \\|%________|          |\n"
                       "|                                         |\n"
                       " __________________________________________\n");

                Sleep(1050);
                
                int vida_recuperada = (rand() % 4) + 1; // //int vida_recuperada = (rand() % (4 - 1 + 1)) + 1;  => int vida_recuperada = (rand() % (4) + 1; 1 ao 4               
                int sorteio = rand() % 3;
                switch (sorteio) {
                    case 0:
                        // Encontrou uma chave
                        chaves++;
                        salaAtual.layout[novoY][novoX] = ESPACO; // Remove o item do mapa
                        printf("\nVOCÊ ENCONTROU UMA CHAVE!\n");
                        printf("====================================\n");
                        printf("                                :..                   \n"
                               "                            .=#%:#%#*.:*###*-:#    \n"
                               "                            .*#-.  .:#:%+. .=#+.   \n"
                               "                            -#+      :*+.   .+#.   \n"
                               "                            :##.     :+:. ..+#-    \n"
                               "                             .#%+:.=+*%:+.#%#:.    \n"
                               "                              ..=*#%*:+.   .=#*.   \n"
                               "                              ..+:%:#%+     .=%=   \n"
                               "                             .*:%:*=##     .=%-   \n"
                               "                           ..*:%##. .+%#:..:+%+.   \n"
                               "                          .+#%*:.     .=**#*=      \n"
                               "                        .+#%#-.                    \n"
                               "                      .=#%#-.                      \n"
                               "                    .-#%#=.                        \n"
                               "                  .:*%#+..                         \n"
                               "                 .#:%+..                           \n"
                               "              ..*:%*:...                           \n"
                               "             .+%:#=.=**-..                         \n"
                               "           .=%##********+.                        \n"
                               "         .-#%-:*******=***                        \n"
                               "        =%*-.:*******:.                           \n"
                               "        .=+:.:*****-:**=                           \n"
                               "              .:+**=.                              \n"
                               "                .+*:                               \n");
                               
                        printf("====================================");
                        printf("\n+1 CHAVE");
                        Sleep(1500);
                        break;
                    case 1:
                            pocoes++;
                            salaAtual.layout[novoY][novoX] = ESPACO; // Remove o item do mapa
                            printf("\nVOCÊ ENCONTROU UMA POÇÃO!\n");
                            printf("====================================\n");
                            printf("                                             .-.         \n"
                                   "                                         ..=:.           \n"
                                   "                                      .==-..             \n"
                                   "                                   .--=+.                \n"
                                   "                                     :=:                 \n"
                                   "                                    :+===-.              \n"
                                   "                                     .=+===:             \n"
                                   "                                      .+==+.             \n"
                                   "                        =++++++=                        \n"
                                   "                      ::=+++++++::                      \n"
                                   "                     :::-******+:::                     \n"
                                   "                     :::::--=-:::::                    \n"
                                   "                      ::::::::::::                       \n"
                                   "                      ::::::::::::                       \n"
                                   "                      ::-+*****-::                       \n"
                                   "                      ::=******=::                       \n"
                                   "                      ::+######+::                       \n"
                                   "                      ::+######+::                       \n"
                                   "                    ::::+######+::::                     \n"
                                   "                 ::::+*##########*+-:::                  \n"
                                   "               :::+##################+:::                \n"
                                   "              ::=######################=::               \n"
                                   "             ::+########################+::              \n"
                                   "             :-*################*#######*-:              \n"
                                   "             :-*###*############***#####*-:               \n"
                                   "             ::=########################+::              \n"
                                   "              ::-##########****########-::               \n"
                                   "               :::=*################*=:::                \n"
                                   "                 .:::-*##########*=::::                  \n"
                                   "                    ::::::::::::::                       \n");
                            printf("====================================\n");
                            Sleep(1500);
                            if (vida_recuperada == 1) {
                                vida_extra += 10;
                                printf("  +10 VIDAS\n");
                            } else if (vida_recuperada == 2) {
                                vida_extra += 15;
                                printf("  +15 VIDAS\n");
                            } else if (vida_recuperada == 3) {
                                vida_extra += 20;
                                printf("  +20 VIDAS\n");
                            } else {
                                printf("  POÇÃO MALDITA\n");
                            }
                            Sleep(1200);
                        break;
                    case 2:
                        int sorteiomoedas= (rand() % (10 - 3 + 1)) + 3;
                        moeda=moeda+sorteiomoedas;
                        salaAtual.layout[novoY][novoX] = ESPACO; // Remove o item do mapa
                        // Encontrou outro tipo de item
                        printf("\nVOCÊ ENCONTROU MOEDAS\n");
                        printf("                 -===++++++===-.                \n");
                        printf("             -++*++++++++++++++*++-             \n");
                        printf("          -+++++++++===--===+++++++++-          \n");
                        printf("        -++++++=----------------=++++++-        \n");
                        printf("      :=++++=----------------------=++++=:      \n");
                        printf("     -++++=-----------=@@=-----------=++++-     \n");
                        printf("    =++++-------------=@@*-------------++++=    \n");
                        printf("   -++++=---------*@@@@@@@@@@@@---------++++-   \n");
                        printf("  :=+++=---------@@@@@%@@@%@@@+---------=+++=:  \n");
                        printf("  =+++=---------+@@@@-=@@=---------------=+++=  \n");
                        printf(" .=+++=---------=@@@@%+@@=---------------=+++=. \n");
                        printf(" .=+++-----------*@@@@@@@@@@+-------------+++=: \n");
                        printf(" .=+++--------------@@@@@@@@@@@-----------+++=: \n");
                        printf(" .=+++=---------------=@@+%@@@@@---------=+++=. \n");
                        printf("  -+++=----------==---=@@=-=@@@@---------=+++=  \n");
                        printf("  :=+++=--------=@@@@#%@@%@@@@@+--------=+++=:  \n");
                        printf("   -++++--------=@@@@@@@@@@@@%----------++++-   \n");
                        printf("    =++++-------------+@@+-------------++++=    \n");
                        printf("     -++++=-----------=@@=-----------=++++-     \n");
                        printf("      :=++++=----------------------=++++=-      \n");
                        printf("       .-++++++=----------------=++++++-.       \n");
                        printf("          -++++++++====--====++++++++-          \n");
                        printf("             -++++++++++++++++++++-.            \n");
                        printf("                .-==++++++++==-.                \n");
                        printf("====================================\n");
                        printf("+%d MOEDAS\n", sorteiomoedas);
                
                
                
                
                        Sleep(1250);
                        break;
                }
           }else if (salaAtual.layout[novoY][novoX] == PORTA) {
                printf("\n\n");
                printf("\n\n\Chaves: %d\n", chaves);
                printf("Monstros derrotados: %d\n", monstros_derrotados);
                Sleep(500);
           
                // Lógica para abrir a porta
                if (chaves >= 5 && monstros_derrotados>=5) {
                    printf("\n\n");
                    printf("A porta da masmorra está destrancada! Você conseguiu resgatar a princesa!\n");
                    printf(" PARABÉNS, %s!\n", nome_personagem);
                    printf( " ___________________________________\n"
                            "/                                   |\n"
                            "|      PASSAGEM PARA MASMORRA       |\n"
                            "|                                   |\n"
                            "|              ______               |\n"
                            "|           ,-' ;  ! `-.            |\n"
                            "|          / :  !  :  . \\           |\n"
                            "|         |_ ;   __:  ;  |          |\n"
                            "|         )| .  :)(.  !  |          |\n"
                            "|         |    (##)  _   |          |\n"
                            "|         |  :  ;`'  (_) (          |\n"
                            "|         |  :  :  .     |          |\n"
                            "|         )_ !  ,  ;  ;  |          |\n"
                            "|         |  .  .  :  :  |          |\n"
                            "|         |; .  |  :  .  |          |\n"
                            "|         |___._;____.___|          |\n"
                            "|                                   |\n"
                            "|          |   ENTRAR   |           |\n"
                            "|                                   |\n"
                            "\\__________________________________//\n");
                    printf("\n\n   Vá até a saída do labirinto e abra a alavanca.\n V=> Alavanca\n");
                    getch();
                    Sleep(1000);
                    
                    faseLabirinto(1, 1); // Posição inicial do personagem
                    
                } else {
                    printf("\nVocê encontrou a porta da masmorra, mas não possui chaves suficientes para abri-la.\n");
                    printf("Volte e encontre mais chaves!\n");
                    Sleep(1550);
                }
            }
            posX = novoX;
            posY = novoY;

            salaAtual.layout[posY][posX] = PERSONAGEM;
            
            salaAtual.layout[posY][posX] = ESPACO;
            posX = novoX;
            posY = novoY;
            salaAtual.layout[posY][posX] = PERSONAGEM;
        }
    }

    return 0;
}
