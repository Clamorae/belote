void BotContract(int** card,int player, int* passes,int* value,int* contractOwner, int* color);
void IAplayCard(int** cards, int* cardsOfRound, int atoutMode, int atout,int player,int turn,int* belote);
int IAgetplayablecards(int** cards, int* cardsOfRound,int* playableCards, int atoutMode, int atout,int player);
void IAcompareAndAdd(int** cards, int* playableCards,int* NofPCards, int colorToCompare,int player);