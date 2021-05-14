#ifndef display_h
#define display_h


#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


class DisplayMatrix
{


  public:
    DisplayMatrix();
    
    void UpdateMatrix();
    int GetChar(char charachter);
    void LoadSprite();
    void ShowSmile();
    void LoadSprite2();
    void ShowSprite2();
    void SetText(String s);
       
  private:

    int str_len = 0;
    char requestString[50] = {};
     
   /* LETREIRO */
      int column = 0; 
      int maxSpeed = 20;  

      int speed = 0;

      int index = 0;  //este Ã© o caracter corrente na string sendo mostrada
      int offset = 0; //esta sÃ£o quantas colunas de offset
       
      //definiÃ§Ã£o de pinos
      // documentar como sao mapeados os pinos
      int colA[8] = {18, 2, 3, 15, 5, 16, 20, 21}; 
      
      int rowA[8] = {14, 19, 7, 17, 27, 6, 25, 4};
       
       
      //constantes definindo cada posiÃ§Ã£o de caracter numa matriz de inteiros
      //Letras
      const int A = 0;  const int B = 1;  const int C = 2;  const int D = 3;  const int E = 4;
      const int F = 5;  const int G = 6;  const int H = 7;  const int I = 8;  const int J = 9;
      const int K = 10; const int L =11;  const int M = 12; const int N = 13; const int O = 14;
      const int P = 15; const int Q =16;  const int R = 17; const int S = 18; const int T = 19;
      const int U = 20; const int V =21;  const int W = 22; const int X = 23; const int Y = 24;
      const int Z = 25;
       
      //PontuaÃ§Ã£o
      const int COL =26; const int DASH = 27; const int BRA2 = 28; const int  _ = 29; const int LINE = 34;
      const int DOT =36;
       
      //Caracteres extras
      const int  FULL =30; const int CHECK = 31; const int B2 = 32; const int TEMP = 33;
      const int SMILE =35; const int COLDOT = 36;

      const int _0 = 38;
      const int _1 = 39;
      const int _2 = 40;
      const int _3 = 41;
      const int _4 = 42;
      const int _5 = 43;
      const int _6 = 44;
      const int _7 = 45;
      const int _8 = 46;
      const int _9 = 47;

  
       
      //Matriz usada para armazenar um mapa de bits a ser mostrado
      //(se vocÃª desejar fazer algum outro modifique os dados desta
      //variÃ¡vel)
      byte data[8] = {0,0,0,0,0,0,0,0};
       
      const int __0[8] = {B0011100,
                          B0100010,
                          B1000001,
                          B1000001,
                          B1000001,
                          B0100010,
                          B0011100,
                          B0000000};
       

      const int __1[8] = {B0001100,
                          B0010100,
                          B0100100,
                          B0000100,
                          B0000100,
                          B0000100,
                          B1111111,
                          B0000000};
      const int __2[8] = {B1111111,
                          B0000001,
                          B0000001,
                          B1111111,
                          B1000000,
                          B1000000,
                          B1111111,
                          B0000000};

      const int __3[8] = {B1111111,
                          B0000001,
                          B0000001,
                          B0011111,
                          B0000001,
                          B0000001,
                          B1111111,
                          B0000000};

      const int __4[8] = {B0000001,
                          B1000001,
                          B1000001,
                          B1111111,
                          B0000001,
                          B0000001,
                          B0000001,
                          B0000000};

      const int __5[8] = {B1111111,
                          B1000000,
                          B1000000,
                          B1111111,
                          B0000001,
                          B0000001,
                          B1111111,
                          B0000000};

      const int __6[8] = {B1111111,
                          B1000000,
                          B1000000,
                          B1111111,
                          B1000001,
                          B1000001,
                          B1111111,
                          B0000000};

      const int __7[8] = {B1111111,
                          B0000001,
                          B0000010,
                          B0000100,
                          B0111110,
                          B0010000,
                          B0100000,
                          B0000000};

      const int __8[8] = {B1111111,
                          B1000001,
                          B1000001,
                          B1111111,
                          B1000001,
                          B1000001,
                          B1111111,
                          B0000000};

      const int __9[8] = {B1111111,
                          B1000001,
                          B1000001,
                          B1111111,
                          B0000001,
                          B0000001,
                          B1111111,
                          B0000000};


                        
      const int _A[8] = {B0001000,
                        B0010100,
                        B0100010,
                        B1000001,
                        B1111111,
                        B1000001,
                        B1000001,
                        B0000000};
       
      const int _B[8] = {B1111110,
                        B0100001,
                        B0100001,
                        B0111110,
                        B0100001,
                        B0100001,
                        B1111110,
                        B0000000};
       
      const int _C[8] = {B0011111,
                        B0100000,
                        B1000000,
                        B1000000,
                        B1000000,
                        B0100000,
                        B0011111,
                        B0000000};
       
      const int _D[8] = {B1111100,
                        B0100010,
                        B0100001,
                        B0100001,
                        B0100001,
                        B0100010,
                        B1111100,
                        B0000000};
       
      const int _E[8] = {B1111111,
                        B1000000,
                        B1000000,
                        B1111100,
                        B1000000,
                        B1000000,
                        B1111111,
                        B0000000};
       
      const int _F[8] = {B1111111,
                        B1000000,
                        B1000000,
                        B1111100,
                        B1000000,
                        B1000000,
                        B1000000,
                        B0000000};
       
      const int _G[8] = {B0011111,
                        B0100000,
                        B1000000,
                        B1001111,
                        B1000001,
                        B0100001,
                        B0011111,
                        B0000000};
       
      const int _H[8] = {B1000001,
                        B1000001,
                        B1000001,
                        B1111111,
                        B1000001,
                        B1000001,
                        B1000001,
                        B0000000};
       
      const int _I[8] = {B1111111,
                        B0001000,
                        B0001000,
                        B0001000,
                        B0001000,
                        B0001000,
                        B1111111,
                        B0000000};
       
      const int _J[8] = {B0001111,
                        B0000001,
                        B0000001,
                        B0000001,
                        B0000001,
                        B1000001,
                        B0111110,
                        B0000000};
       
      const int _K[8] = {B1000011,
                        B1000100,
                        B1001000,
                        B1110000,
                        B1001000,
                        B1000100,
                        B1000011,
                        B0000000};
       
      const int _L[8] = {B1000000,
                        B1000000,
                        B1000000,
                        B1000000,
                        B1000000,
                        B1000000,
                        B1111111,
                        B0000000};
       
      const int _M[8] = {B1110110,
                        B1001001,
                        B1001001,
                        B1001001,
                        B1001001,
                        B1001001,
                        B1001001,
                        B0000000};
       
      const int _N[8] = {B1000001,
                        B1100001,
                        B1010001,
                        B1000001,
                        B1000101,
                        B1000011,
                        B1000001,
                        B0000000};
       
      const int _O[8] = {B0011100,
                        B0100010,
                        B1000001,
                        B1000001,
                        B1000001,
                        B0100010,
                        B0011100,
                        B0000000};
       
      const int _P[8] = {B1111110,
                        B0100001,
                        B0100001,
                        B0111110,
                        B0100000,
                        B0100000,
                        B0100000,
                        B0000000};
       
      const int _Q[8] = {B0011100,
                        B0100010,
                        B1000001,
                        B1000001,
                        B1000101,
                        B0100010,
                        B0011101,
                        B0000000};
       
      const int _R[8] = {B1111110,
                        B0100001,
                        B0100001,
                        B0101110,
                        B0100100,
                        B0100010,
                        B0100001,
                        B0000000};
       
      const int _S[8] = {B0111111,
                        B1000000,
                        B1000000,
                        B0111110,
                        B0000001,
                        B0000001,
                        B1111110,
                        B0000000};
       
      const int _T[8] = {B1111111,
                        B0001000,
                        B0001000,
                        B0001000,
                        B0001000,
                        B0001000,
                        B0001000,
                        B0000000};
       
      const int _U[8] = {B1000001,
                        B1000001,
                        B1000001,
                        B1000001,
                        B1000001,
                        B1000001,
                        B0111110,
                        B0000000};
       
      const int _V[8] = {B1000001,
                        B1000001,
                        B1000001,
                        B1000001,
                        B0100010,
                        B0010100,
                        B0001000,
                        B0000000};
       
      const int _W[8] = {B1000001,
                        B1001001,
                        B1001001,
                        B1001001,
                        B1001001,
                        B1001001,
                        B0110110,
                        B0000000};
       
      const int _X[8] = {B1000001,
                        B0100010,
                        B0010100,
                        B0001000,
                        B0010100,
                        B0100010,
                        B1000001,
                        B0000000};
       
      const int _Y[8] = {B1000001,
                        B0100010,
                        B0010100,
                        B0001000,
                        B0001000,
                        B0001000,
                        B0001000,
                        B0000000};
       
      const int _Z[8] = {B1111111,
                        B0000010,
                        B0000100,
                        B0111110,
                        B0010000,
                        B0100000,
                        B1111111,
                        B0000000};
       
      const int _COL[8] = {B0000000,
                          B0011000,
                          B0011000,
                          B0000000,
                          B0011000,
                          B0011000,
                          B0000000,
                          B0000000};
       
      const int _DASH[8] = {B0000000,
                           B0000000,
                           B0000000,
                           B0111110,
                           B0000000,
                           B0000000,
                           B0000000,
                           B0000000};
       
      const int _BRA2[8] = {B0010000,
                           B0001000,
                           B0000100,
                           B0000100,
                           B0001000,
                           B0010000,
                           B0000000,
                           B0000000};
       
      const int __[8] = {B0000000,
                        B0000000,
                        B0000000,
                        B0000000,
                        B0000000,
                        B0000000,
                        B0000000,
                        B0000000};
       
      const int _FULL[8] = {B1111111,
                           B1111111,
                           B1111111,
                           B1111111,
                           B1111111,
                           B1111111,
                           B1111111,
                           B0000000};
       
      const int _CHECK[8] = {B1010101,
                            B0101010,
                            B1010101,
                            B0101010,
                            B1010101,
                            B0101010,
                            B1010101,
                            B0000000};
       
      const int _B2[8] = {B0111110,
                         B0000001,
                         B0000001,
                         B0001111,
                         B0000001,
                         B1000001,
                         B0111110,
                         B0000000};
       
      const int _TEMP[8] = {B0000011,
                           B0011111,
                           B0111111,
                           B1111110,
                           B1111111,
                           B0011111,
                           B0000011,
                           B0000000};
       
      const int _LINE[8] = {B0000001,
                           B0000001,
                           B0000001,
                           B0000001,
                           B0000001,
                           B0000001,
                           B0000001,
                           B0000000};
       
      const int _SMILE[8] = {
                            B01100110,
                            B01100110,
                            B00000000,
                            B00000000,
                            B11000011,
                            B11000011,
                            B01111110,
                            B00111100};
       
      const int _DOT[8] = {B0000000,
                          B0000000,
                          B0000000,
                          B0000000,
                          B0011000,
                          B0011000,
                          B0000000,
                          B0000000};
       
      const int _COLDOT[8] = {B0000000,
                             B0110000,
                             B0110000,
                             B0000000,
                             B0110011,
                             B0110011,
                             B0000000,
                             B0000000};
       

        const int powers[8] = {1,2,4,8,16,32,64,128};

  
};


#endif


