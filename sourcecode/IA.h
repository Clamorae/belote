void BotContract(int** cards,int player, int* passes,int* value,int* contractOwner, int* color,int* coinche);
/*this function will take the card array and check the IA's hand thanks to the player variable which can indicate where in the array are the current player cards.
  With this cards The IA will check his number of strong card if it has 3(of the same color) it will bet on 80,else if it has 4 or more it will vet on 120 
  if the contract is too high for The IA or if it didn't want to bet it will increment the passes variable and leave the function
  In the case which the IA bet it will change the value of the variable value/contractowner/color in the contract structure  */
void IAplayCard(int** cards, int* cardsOfRound, int atoutMode, int atout,int player,int turn,int* belote);
/*This function will create the playabvlecard array and send it to the IAgetplayblecards() function and the analyse in which situation is the game
  using the cardsOfRound:AtoutMode/atout states. then it will browse the IA's hand and check if the IA has a cards which can win the round.
  If the round is the winnable the Ia will play is lowest wining card else his lowest playable card*/
void IAgetplayablecards(int** cards, int* cardsOfRound,int* playableCards, int atoutMode, int atout,int player);
/*this function will take the card array and check the IA's hand thanks to the player variable which can indicate where in the array are the current player cards.
  this will analyze the current round thanks to the carsOfRound array and depend of wich type of game it is(Fulltrump/noTRump/normal/normal with trump in play...)
  it will check if the card respect the rule and if it's true add the card in the array playablecard */
void removeCard(int** cards,int player,int* cardsOfround, int turn,int* i, int* j);
/* this function will take the array cardsOfround and the variable turn for determine wich cards have been played
   then a for loop will search the cards in the IA's hand using players variable and cards array
   then it will change the player which has the card and passed it to 0
   the card is  now out of the game
   finally it will increment i and j at 8 for break the loop(for prenvent to play more than one card/turn)*/