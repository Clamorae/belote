void BotContract(int** cards,int player, int* passes,int* value,int* contractOwner, int* color);
/*this function will take the card array and check the IA's hand thanks to the player variable which can indicate where in the array are the current player cards.
  With this cards The IA will check his number of strong card if it has 3(of the same color) it will bet on 80,else if it has 4 or more it will vet on 120 
  if the contract is too high for The IA or if it didn't want to bet it will increment the passes variable and leave the function
  In the case which the IA bet it will change the value of the variable value/contractowner/color in the contract structure  */
void IAplayCard(int** cards, int* cardsOfRound, int atoutMode, int atout,int player,int turn,int* belote);
/**/
void IAgetplayablecards(int** cards, int* cardsOfRound,int* playableCards, int atoutMode, int atout,int player);
/*this function will take the card array and check the IA's hand thanks to the player variable which can indicate where in the array are the current player cards.
  this will analyze the current round thanks to the carsOfRound array*/

