#include "RIMS.h"
enum States {Init, OFF, Elec, GasElec, GAS, Brake} state = Init;
void Tick(){
   switch(state){
      case Init:
         state = OFF;
         break;
      case OFF:
         if(A0){
            state = Elec;
         }
         else if(A1){
            state = GasElec;
         }
         break;
      case Elec:
         if(A1 && !A2){
            state = GasElec;
         }
         else if(A2){
            state = GAS;
         }
         else if(A3 || (!A0 && !A1 && !A2)){
            state = Brake;
         }
         else{
            state = Elec;
         }
         break;
      case GasElec:
         if(A0 && !A1 && !A2){
            state = Elec;
         }
         else if(A2){
            state = GAS;
         } else{
            state = GasElec;
         }
         if(A3 || (!A0 && !A1 && !A2)){
            state = Brake;
         }
         break;
      case GAS:
         if(!A2 && !A1 && A0){
            state = Elec;
         }
         else if(!A2 && A1){
            state =GasElec;
         }
         else if(A4){
            state = Brake;
         }
         break;
      case Brake:
         if(A3|| (!A0 && !A1 && !A2)){
            state = OFF;
         }
         break;
   }
   switch(state){
      case OFF:
         B = 0;
         break;
      case Elec:
         B0 = 1;
         B1 = 0;
         B7 = 0;
         break;
      case GasElec:
         B0 = 1;
         B1 = 1;
         B7 = 0;
         break;
      case GAS:
         B0 = 0;
         B1 = 1;
         B7 = 1;
         break;
      case Brake:
         B2 = 1;
         B0 = 0;
         B1 = 0;
         B7 = 1;
         break;
      default:
         break;
   }
}
int main() {
   while(1) {
      Tick();
   }
   return 0;
}