//Feito por: Gabriela Stieler, Gabrielle Assunção e Geovana Silva


/*      Este é um jogo da memória com as maiores fofuras do mundo presentes.
        O objetivo é você virar as cartas e encontrar os pares dos mini queridos.
        Assim que finalizar o jogo você receberá um prêmio e o seu reconhecimento!
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>


//VARIAVEIS
int posicaox=0, posicaoy=0, primeiraCarta=0, valorMatriz=0, valorMatriz2=0;
int opcao = 0, win = 0;
int descoberto = 1;
int i, j, x=140, y=80;

//MATRIZ DAS POSIÇÕES DAS CARTAS SENDO DUPLICADAS
int jogo1[4][5] =
{
    0, 5, 3, 9, 6,
    1, 8, 7, 8, 2,
    9, 4, 2, 3, 4,
    5, 6, 7, 1, 0
};


//MATRIZ PARA VERIFICAR SE AS CARTAS FORAM DESCOBERTAS
int jogo2[4][5] =
{
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};


//ENDEREÇO DAS IMAGENS DAS CARTAS
const char imagens[10][50] = {
    "../assets/imagem0.jpg",
    "../assets/imagem1.jpg",
    "../assets/imagem2.jpg",
    "../assets/imagem3.jpg",
    "../assets/imagem4.jpg",
    "../assets/imagem5.jpg",
    "../assets/imagem6.jpg",
    "../assets/imagem7.jpg",
    "../assets/imagem8.jpg",
    "../assets/imagem9.jpg"
};

//PROTOTIPO DAS FUNÇÕES
const char* obterNomeDaImagem(int valor);
void montaJogo();
void viraPrimeiraCarta();
void viraSegundaCarta();
void encontrouPar();
void verificaVitoria();
void telaVitoria();

int main(){

    //JANELA EXECUTAVEL
    initwindow(1000, 700, "Jogo da Memoria", 0, 0);

    //PADRONIZAÇÃO E ESTILIZAÇÃO DO MENU
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5 /*tamanho da fonte*/);
    outtextxy(205, 150, "JOGO DA MEMORIA");
    outtextxy(285, 350, "[1] Iniciar");
    outtextxy(345, 450, "[2] Sair");
    rectangle(50, 50, 950, 650);


    //ESTRUTURA DE REPETIÇÃO PARA VERIFICAR A ESCOLHA DO JOGADOR DE INICIAR OU SAIR
    while (1) {

        //RECONHECER SE O TECLADO FOI PRESSIONADO
        if (kbhit()) {
            opcao = getch(); //GUARDAR TECLA PRESSIONADA

            //EVENTOS DE ACORDO COM A ESCOLHA DO JOGADOR
            switch (opcao) {
                case '1':

                    //INICIAREMOS O JOGO AO PRESSIONAR A TECLA 1
                    cleardevice(); //LIMPAR TELA

                    //MONTAR O INICIO DO JOGO
                    montaJogo();

                    //VERIFICAÇÃO DE CLIQUE DO MOUSE
                    clearmouseclick(WM_LBUTTONDOWN);

                    //ESTRUTURA DE REPETIÇÃO PARA VERIFICAR SE O JOGADOR VENCEU O JOGO, SE NÃO ELE CONTINUA
                    while(win<20){

                        //VARIAVEL PARA ARMAZENAR QUANTIDADE DE CARTAS DESCOBERTAS
                        win = 0;

                        //ARMAZENAR A POSIÇÃO DO MOUSE APÓS O CLIQUE
                        posicaox = mousex();
                        posicaoy = mousey();


                        //SE HOUVE CLIQUE DO MOUSE ENTÃO ELE INICIA A VERIFICAÇÃO DE QUAL CARTA FOI SELECIONADA
                        if(ismouseclick(WM_LBUTTONDOWN)){


                            //TEREMOS DE ESCOLHER A PRIMEIRA CARTA, ENTÃO FAREMOS ESTA VERIFICAÇÃO
                            if(primeiraCarta==0){

                                //CASO SEJA A PRIMEIRA CARTA A VIRAR, EXECUTA A FUNÇÃO PARA VERIFICAR A CARTA ESCOLHIDA
                                viraPrimeiraCarta();

                            }
                            else{

                                //CASO SEJA A SEGUNDA CARTA, VERIFICAMOS NOVAMENTE QUAL FOI A SEGUNDA CARTA ESCOLHIDA
                                viraSegundaCarta();

                                //IREMOS ZERAR A CONTAGEM DE CARTAS SELECIONADAS PARA VIRARMOS APENAS 2 POR VEZ
                                primeiraCarta=0;

                                //VERIFICA SE OS VALORES DAS CARTAS REPRESENTADAS NA MATRIZ SÃO IGUAIS
                                if(valorMatriz==valorMatriz2){

                                    //SE FOR IGUAL, EXECUTA A FUNÇÃO PARA DEFINIR QUE O PAR FOI ENCONTRADO
                                    encontrouPar();
                                }
                                else{

                                    //CASO AS CARTAS NÃO SEJAM IGUAIS, ELA IRÁ DAR UM TEMPO PARA VOCE IDENTIFICAR QUE SÃO DIFERENTES
                                    Sleep(500);

                                    //VIRA AS CARTAS NOVAMENTE E CONTINUA COM O JOGO
                                    montaJogo();

                                }

                            }

                        }

                        //VERIFICA SE O JOGADOR ENCONTROU TODOS OS PARES
                        verificaVitoria();

                    }

                    //LIMPAR A TELA
                    cleardevice();

                    //EXECUTA A TELA DA VITORIA ASSIM QUE FINALIZA O JOGO
                    telaVitoria();

                    break;

                case '2':
                    //SERÁ A ESCOLHA DE SAIR DO JOGO
                    closegraph(); //FECHAR A JANELA
                    return 0; // RETORNAR O ENCERRAMENTO DO JOGO SEM ERRO

                default:
                    //CASO ESCOLHA OUTRA TECLA ALEM DAS OPÇÕES MOSTRADAS ELE MOSTRA A MENSAGEM
                    outtextxy(225, 600, "TECLA INVÁLIDA!");
            }
        }
    }

    //ASSIM QUE FINALIZAR O JOGO E O JOGADOR FECHAR A JANELA, ELE ENCERRA E NÃO RETORNA ERRO
    closegraph();
    return 0;
}

//FUNÇÃO PRA PEGAR AS IMAGENS CORRESPONDENTES AO VALOR QUE SE ENCONTRA NA MATRIZ
const char* obterNomeDaImagem(int valor) {
    // Verifica se o valor está no intervalo válido do vetor
    if (valor >= 0 && valor < 10) {
        return imagens[valor];
    } else {
        // Se o valor não existir no vetor, retorna NULL
        return NULL;
    }
}


//FUNÇÃO PARA MONTAR
void montaJogo(){

    //COLOCAMOS O TITULO DO JOGO COM FONTE E TAMANHO ESTILIZADO
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3 );
    outtextxy(320, 20, "JOGO DA MEMORIA");


    //PERCORREMOS A MATRIZ PARA SABER SE A CARTA FOI DESCOBERTA OU NÃO
    for(i=0;i<4;i++){
        for(j=0;j<5;j++){
            if(jogo2[i][j]!=descoberto){//CASO NÃO ESTEJA DESCOBERTA ELA A COLOCA DESVIRADA PARA JOGO
                readimagefile("../assets/descoberta.jpg",x,y,x + 100, y + 130);
            }
            //CASO ELA JÁ TENHA SIDO DESCOBERTA, ESTA CARTA FICA A MOSTRA NA JANELA PARA VISUALIZAÇÃO

            x+=150; //espaço entre colunas
            }

        x=140;
        y+=150; //espaço entre linhas
    }

    x=140;
    y=80;
}

//VERIFICAÇÃO DE QUAL CARTA FOI SELECIONADA E ARMAZENA ESTA NA VARIAVEL DE valorMatriz E APRESENTA A CARTA VIRADA
void viraPrimeiraCarta(){

    //SE MOUSE ESTIVER ENTRE A POSIÇÃO DE UMA CARTA ELA PROSSEGUE
    if (posicaox >= 140 && posicaoy >= 80 && posicaox <= 240 && posicaoy <= 210){

        //ATRIBUI O VALOR DA MATRIZ A VARIAVEL PARA COMPARAÇÕES FUTURAS
        valorMatriz = jogo1[0][0];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz); //FUNÇÃO QUE BUSCA IMAGEM CORRESPONDENTE AO VALOR DA MATRIZ
        readimagefile(nomeImagem, 140, 80, 240, 210); //CARTA "VIRADA"
        clearmouseclick(WM_LBUTTONDOWN); //LIMPEZA DA POSIÇÃO DO CLIQUE DO MOUSE
        primeiraCarta++; //ACRESCENTA UMA UNIDADE PARA CONTROLE DE QUANTIDADE DE CARTAS VIRADAS

    }
    if (posicaox >= 290 && posicaoy >= 80 && posicaox <= 390 && posicaoy <= 210){

        valorMatriz = jogo1[0][1];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 290, 80, 390, 210);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 440 && posicaoy >= 80 && posicaox <= 540 && posicaoy <= 210){

        valorMatriz = jogo1[0][2];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 440, 80, 540, 210);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 590 && posicaoy >= 80 && posicaox <= 690 && posicaoy <= 210){

        valorMatriz = jogo1[0][3];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 590, 80, 690, 210);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 740 && posicaoy >= 80 && posicaox <= 840 && posicaoy <= 210){

        valorMatriz = jogo1[0][4];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 740, 80, 840, 210);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 140 && posicaoy >= 230 && posicaox <= 240 && posicaoy <= 360){

        valorMatriz = jogo1[1][0];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 140, 230, 240, 360);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 290 && posicaoy >= 230 && posicaox <= 390 && posicaoy <= 360){

        valorMatriz = jogo1[1][1];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 290, 230, 390, 360);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 440 && posicaoy >= 230 && posicaox <= 540 && posicaoy <= 360){

        valorMatriz = jogo1[1][2];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 440, 230, 540, 360);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 590 && posicaoy >= 230 && posicaox <= 690 && posicaoy <= 360){

        valorMatriz = jogo1[1][3];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 590, 230, 690, 360);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 740 && posicaoy >= 230 && posicaox <= 840 && posicaoy <= 360){

        valorMatriz = jogo1[1][4];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 740, 230, 840, 360);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 140 && posicaoy >= 380 && posicaox <= 240 && posicaoy <= 510){

        valorMatriz = jogo1[2][0];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 140, 380, 240, 510);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 290 && posicaoy >= 380 && posicaox <= 390 && posicaoy <= 510){

        valorMatriz = jogo1[2][1];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 290, 380, 390, 510);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 440 && posicaoy >= 380 && posicaox <= 540 && posicaoy <= 510){

        valorMatriz = jogo1[2][2];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 440, 380, 540, 510);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 590 && posicaoy >= 380 && posicaox <= 690 && posicaoy <= 510){

        valorMatriz = jogo1[2][3];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 590, 380, 690, 510);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 740 && posicaoy >= 380 && posicaox <= 840 && posicaoy <= 510){

        valorMatriz = jogo1[2][4];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 740, 380, 840, 510);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 140 && posicaoy >= 530 && posicaox <= 240 && posicaoy <= 660){

        valorMatriz = jogo1[3][0];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 140, 530, 240, 660);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 290 && posicaoy >= 530 && posicaox <= 390 && posicaoy <= 660){

        valorMatriz = jogo1[3][1];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 290, 530, 390, 660);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 440 && posicaoy >= 530 && posicaox <= 540 && posicaoy <= 660){

        valorMatriz = jogo1[3][2];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 440, 530, 540, 660);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 590 && posicaoy >= 530 && posicaox <= 690 && posicaoy <= 660){

        valorMatriz = jogo1[3][3];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 590, 530, 690, 660);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }
    if (posicaox >= 740 && posicaoy >= 530 && posicaox <= 840 && posicaoy <= 660){

        valorMatriz = jogo1[3][4];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz);
        readimagefile(nomeImagem, 740, 530, 840, 660);
        clearmouseclick(WM_LBUTTONDOWN);
        primeiraCarta++;

    }

}

//VERIFICAÇÃO DE QUAL CARTA FOI SELECIONADA E ARMAZENA ESTA NA VARIAVEL DE valorMatriz2 E APRESENTA A CARTA VIRADA
void viraSegundaCarta(){

    if (posicaox >= 140 && posicaoy >= 80 && posicaox <= 240 && posicaoy <= 210){

        valorMatriz2 = jogo1[0][0];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 140, 80, 240, 210);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 290 && posicaoy >= 80 && posicaox <= 390 && posicaoy <= 210){

        valorMatriz2 = jogo1[0][1];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 290, 80, 390, 210);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 440 && posicaoy >= 80 && posicaox <= 540 && posicaoy <= 210){

        valorMatriz2 = jogo1[0][2];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 440, 80, 540, 210);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 590 && posicaoy >= 80 && posicaox <= 690 && posicaoy <= 210){

        valorMatriz2 = jogo1[0][3];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 590, 80, 690, 210);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 740 && posicaoy >= 80 && posicaox <= 840 && posicaoy <= 210){

        valorMatriz2 = jogo1[0][4];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 740, 80, 840, 210);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 140 && posicaoy >= 230 && posicaox <= 240 && posicaoy <= 360){

        valorMatriz2 = jogo1[1][0];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 140, 230, 240, 360);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 290 && posicaoy >= 230 && posicaox <= 390 && posicaoy <= 360){

        valorMatriz2 = jogo1[1][1];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 290, 230, 390, 360);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 440 && posicaoy >= 230 && posicaox <= 540 && posicaoy <= 360){

        valorMatriz2 = jogo1[1][2];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 440, 230, 540, 360);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 590 && posicaoy >= 230 && posicaox <= 690 && posicaoy <= 360){

        valorMatriz2 = jogo1[1][3];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 590, 230, 690, 360);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 740 && posicaoy >= 230 && posicaox <= 840 && posicaoy <= 360){

        valorMatriz2 = jogo1[1][4];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 740, 230, 840, 360);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 140 && posicaoy >= 380 && posicaox <= 240 && posicaoy <= 510){

        valorMatriz2 = jogo1[2][0];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 140, 380, 240, 510);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 290 && posicaoy >= 380 && posicaox <= 390 && posicaoy <= 510){

        valorMatriz2 = jogo1[2][1];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 290, 380, 390, 510);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 440 && posicaoy >= 380 && posicaox <= 540 && posicaoy <= 510){

        valorMatriz2 = jogo1[2][2];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 440, 380, 540, 510);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 590 && posicaoy >= 380 && posicaox <= 690 && posicaoy <= 510){

        valorMatriz2 = jogo1[2][3];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 590, 380, 690, 510);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 740 && posicaoy >= 380 && posicaox <= 840 && posicaoy <= 510){

        valorMatriz2 = jogo1[2][4];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 740, 380, 840, 510);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 140 && posicaoy >= 530 && posicaox <= 240 && posicaoy <= 660){

        valorMatriz2 = jogo1[3][0];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 140, 530, 240, 660);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 290 && posicaoy >= 530 && posicaox <= 390 && posicaoy <= 660){

        valorMatriz2 = jogo1[3][1];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 290, 530, 390, 660);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 440 && posicaoy >= 530 && posicaox <= 540 && posicaoy <= 660){

        valorMatriz2 = jogo1[3][2];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 440, 530, 540, 660);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 590 && posicaoy >= 530 && posicaox <= 690 && posicaoy <= 660){

        valorMatriz2 = jogo1[3][3];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 590, 530, 690, 660);
        clearmouseclick(WM_LBUTTONDOWN);

    }
    if (posicaox >= 740 && posicaoy >= 530 && posicaox <= 840 && posicaoy <= 660){

        valorMatriz2 = jogo1[3][4];
        const char* nomeImagem = obterNomeDaImagem(valorMatriz2);
        readimagefile(nomeImagem, 740, 530, 840, 660);
        clearmouseclick(WM_LBUTTONDOWN);

    }

}

//CASO O PAR SEJA ENCONTRADO ELE SERÁ COLOCADO COMO VARIAVEL DESCOBERTA NA MATRIZ DO JOGO2
void encontrouPar(){

    for(i=0;i<4;i++){
        for(j=0;j<5;j++){
            if(valorMatriz==jogo1[i][j]){
                jogo2[i][j]=descoberto;
            }
        }
    }

}


//VERIFICA SE TODAS AS CARTAS FORAM DESCOBERTAS, DE ACORDO COM A MATRIZ DO JOGO2
void verificaVitoria(){

    for(i=0;i<4;i++){
        for(j=0;j<5;j++){
            if(jogo2[i][j]==descoberto){
                win++;
            }
        }
    }

}

//APRESENTA NA TELA A VISUALIZAÇÃO DA VITORIA DO JOGO
void telaVitoria(){

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5 /*tamanho da fonte*/);
    outtextxy(340, 80, "VITÓRIA!");
    readimagefile("../assets/premio.jpg", 270, 165, 700, 525);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3 /*tamanho da fonte*/);
    outtextxy(160, 590, "Parabéns, você venceu o jogo.");

}
