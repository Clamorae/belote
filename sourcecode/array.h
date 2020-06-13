int ** create(int lineNumber, int columnNumber);// a function which take as parameter the number of line and column you want and return the pointer to a two-dimensional array(the card deck)//
int randomize(int **array);//a function which takes a two dimensional array as parameter and return a shuffled array//
/*Our card deck is a two dimensionnal array 
  In the first line there is the card value
  when we use an enclidian division on the number the quotient will represent the color and the rest the cards value
  quotient: 0=Heart, 1=Spade, 2=Diamonds, 3=Clover
  value: 0=7, 1=8, 2=9, 3=10, 4=Jack, 5=Queen, 6=King, 7=Ace 
  when the value is superior than 7 it will pass to the next ten
  So we have 32 value between 0 and 37

  The card distribution is a bit special because we distribute the player
  each card will get a random value between 1 and 4
  if 8 card as already the same player it will attribute another value
  Then the array will be bubble sorted the height first card will be the players 1 card,the next 8 for the second players, etc
  at every moment we can access the players hand by starting at cards[0][player*8]

  When a cards has been used the player number will become 0
  at this moment the cards stay at the same place in the array
  but in our check it will not be added in the playablecard array 
  and no one will be able to replay a card which has been already played
    */
void freeCards(int **cards);// this function will free the two dimensionnal array