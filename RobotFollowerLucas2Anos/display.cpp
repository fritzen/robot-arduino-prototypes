#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "display.h"



DisplayMatrix::DisplayMatrix()
{


   for(int i = 0; i <8; i++){  //configura os 16 pinos usados para controlar
                              // a matriz como pinos de saÃ­da
    pinMode(rowA[i], OUTPUT);
    pinMode(colA[i], OUTPUT);
  }
 

}



void DisplayMatrix::SetText(String s)
{

str_len = s.length() + 1; 

s.toCharArray(requestString, str_len);

}


void DisplayMatrix::UpdateMatrix(){
//for(int column = 0; column < 8; ){    


 if (speed >= maxSpeed) {
    LoadSprite2(); //carrega mapa de bits
    speed = 0;
 } else {

    ShowSprite2(); //mostra o mapa com a velocidade programada
    column++;

    if (column > 7) {
      column = 0;
      speed++;
     }

 }
    
}
 






//carrega o estado atual do quadro a ser mostrado na matriz data[]
void DisplayMatrix::LoadSprite2(){
  
 
     const int* letters[48]= {_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,_N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z,_COL,_DASH,_BRA2,__, _FULL, _CHECK, _B2, _TEMP, _LINE, _SMILE, _DOT, _COLDOT, __0, __1,__2,__3,__4,__5,__6,__7,__8,__9 };
     
    int currentChar = GetChar(requestString[index]); //lÃª caracter da matriz
    int nextChar = GetChar(requestString[index+1]); //lÃª o prÃ³ximo


    
 
  for(int row=0; row < 8; row++){                    //iteraÃ§Ã£o para cada linha
    data[row] = 0;                                   //reseta a linha de trabalho
    for(int column=0; column < 8; column++){         //iteraÃ§Ã£o para cada coluna
     //carrega o caractere atual, compensado por pixels de deslocamento
     data[row] = data[row] + ((powers[column] & (letters[currentChar][row] << offset)));
     //carrega o prÃ³ximo caracte compensado por pixels de deslocamento
     data[row] = data[row] + (powers[column] & (letters[nextChar][row] >> (8-offset) ));
    }
  }
  offset++; //incrementa o offset de uma linha
  //se offset Ã© de 8, carregar o par de caracteres a seguir na proxima vez
  if(offset==8){
      offset = 0;
      index++;
      //if(index==sizeof(requestString)-2){
      if(index==str_len-2){
        index=0;
       }
   }
}
 
void DisplayMatrix::ShowSprite2(){
   // for(int column = 0; column < 8; column++){            //iteraÃ§Ã£o de cada coluna
       for(int i = 0; i < 8; i++){
           digitalWrite(rowA[i], LOW);                      //desliga todos os pinos de linhas
       }
       for(int i = 0; i < 8; i++){ //configura somente um pino
         if(i == column){     digitalWrite(colA[i], LOW);}  //liga a linha corrente
         else{                digitalWrite(colA[i], HIGH); }//liga o restante das linhas
       }
       for(int row = 0; row < 8; row++){ //iteraÃ§Ã£o atravÃ©s de cada pixel da coluna corrente
          int bit = (data[column] >> row) & 1;
          if(bit == 1){
            //se o bit na matriz de dados estÃ¡ definido, acende o LED
            digitalWrite(rowA[row], HIGH);
          }
       }
       //deixar a coluna em pauseDelay microsecondos (muito alta a demora causa tremulaÃ§Ã£o)
  //     delayMicroseconds(200);
   //   }
}




void DisplayMatrix::ShowSmile(){

      index = 0; 
      offset = 0; 

      
    for(int column = 0; column < 8; column++){            //iteraÃ§Ã£o de cada coluna
       for(int i = 0; i < 8; i++){
           digitalWrite(rowA[i], LOW);                      //desliga todos os pinos de linhas
       }
       for(int i = 0; i < 8; i++){ //configura somente um pino
         if(i == column){     digitalWrite(colA[i], LOW);}  //liga a linha corrente
         else{                digitalWrite(colA[i], HIGH); }//liga o restante das linhas
       }
       for(int row = 0; row < 8; row++){ //iteraÃ§Ã£o atravÃ©s de cada pixel da coluna corrente
          int bit = (_SMILE[column] >> row) & 1;
          if(bit == 1){
            //se o bit na matriz de dados estÃ¡ definido, acende o LED
            digitalWrite(rowA[row], HIGH);
          }
       }
       //deixar a coluna em pauseDelay microsecondos (muito alta a demora causa tremulaÃ§Ã£o)
     //  delayMicroseconds(600);
      }
}

 
//retorna o indice de um dado caractere
//para a conversÃ£o de uma string e
//para a pesquisa na mtriz de mapa de bit de caracteres
int DisplayMatrix::GetChar(char charachter){
 int returnValue = Z;
 switch(charachter){
  case 'A': returnValue = A; break;
  case 'a': returnValue = A; break;
  case 'B': returnValue = B; break;
  case 'b': returnValue = B; break;
  case 'C': returnValue = C; break;
  case 'c': returnValue = C; break;
  case 'D': returnValue = D; break;
  case 'd': returnValue = D; break;
  case 'E': returnValue = E; break;
  case 'e': returnValue = E; break;
  case 'F': returnValue = F; break;
  case 'f': returnValue = F; break;
  case 'G': returnValue = G; break;
  case 'g': returnValue = G; break;
  case 'H': returnValue = H; break;
  case 'h': returnValue = H; break;
  case 'I': returnValue = I; break;
  case 'i': returnValue = I; break;
  case 'J': returnValue = J; break;
  case 'j': returnValue = J; break;
  case 'K': returnValue = K; break;
  case 'k': returnValue = K; break;
  case 'L': returnValue = L; break;
  case 'l': returnValue = L; break;
  case 'M': returnValue = M; break;
  case 'm': returnValue = M; break;
  case 'N': returnValue = N; break;
  case 'n': returnValue = N; break;
  case 'O': returnValue = O; break;
  case 'o': returnValue = O; break;
  case 'P': returnValue = P; break;
  case 'p': returnValue = P; break;
  case 'Q': returnValue = Q; break;
  case 'q': returnValue = Q; break;
  case 'R': returnValue = R; break;
  case 'r': returnValue = R; break;
  case 'S': returnValue = S; break;
  case 's': returnValue = S; break;
  case 'T': returnValue = T; break;
  case 't': returnValue = T; break;
  case 'U': returnValue = U; break;
  case 'u': returnValue = U; break;
  case 'V': returnValue = V; break;
  case 'v': returnValue = V; break;
  case 'W': returnValue = W; break;
  case 'w': returnValue = W; break;
  case 'X': returnValue = X; break;
  case 'x': returnValue = X; break;
  case 'Y': returnValue = Y; break;
  case 'y': returnValue = Y; break;
  case 'Z': returnValue = Z; break;
  case 'z': returnValue = Z; break;
  case ' ': returnValue = _; break;
 // case '3': returnValue = B2; break;
  case '<': returnValue = TEMP; break;
  case '*': returnValue = FULL; break;
  case '|': returnValue = LINE; break;
  case '_': returnValue = _; break;
  case ':': returnValue = COL; break;
  case '-': returnValue = DASH; break;
  case ')': returnValue = BRA2; break;
  case '%': returnValue = SMILE; break;
  case '.': returnValue = DOT; break;
  case '^': returnValue = COLDOT; break;


  case '0': returnValue = _0; break;
  case '1': returnValue = _1; break;
  case '2': returnValue = _2; break;
  case '3': returnValue = _3; break;
  case '4': returnValue = _4; break;
  case '5': returnValue = _5; break;
  case '6': returnValue = _6; break;
  case '7': returnValue = _7; break;
  case '8': returnValue = _8; break;
  case '9': returnValue = _9; break;


  
  }
  return returnValue;
}


