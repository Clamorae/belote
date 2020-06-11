int ** create(int lineNumber, int columnNumber);// a function which take as parameter the number of line and column you want and return the pointer to a two-dimensional array(the card deck)//
int randomize(int **array);//a function which takes a two dimensional array as parameter and return a shuffled array//
/*Our card deck is a two dimensionnal array 
  In the first line there is the card value
  when we use an enclidian division on the number the quotient will represent the color and the rest the cards value
  quotient: 0=Heart, 1=Spade, 2=Diamonds, 3=Clover
  value: 0=7, 1=8, 2=9, 3=10, 4=Jack, 5=Queen, 6=King, 7=Ace
  when the value is superior than 7 it will 
    */