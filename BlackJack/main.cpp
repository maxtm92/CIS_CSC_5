/* 
 * File:   main.cpp
 * Author: Max Lothringen
 * Created on November,3 2018, 10:07 PM
 * Purpose Blackjack program
 */

//System Libraries
#include<iostream>
#include <vector>
#include<cmath>
#include<stdlib.h>
#include<ctime>
using namespace std;
//User Libraries

//Global Constants  Physics/Math/Conversions/Array Dimension

//Function Prototypes
void BubbleSort(int *a, int size);
int draw_card(string &card,                 //IN - card name
               int drawpts);          //IN - drawer's total points
void printNumber (int u);
void printNumber (float u);
//Execution begins with main
int main()
{

    srand (time(NULL));

    cout<<"BlackJack"<<endl;//title
    cout<<"*********"<<endl;//spacing
    cout<<endl;
    cout<<"Welcome to BlackJack"<<endl;
    vector<int> g1;
    int plyCash;         //players cash amount
    int plyCnt;        //player card count
    int dealCnt;        //dealer card count

    bool noHit;       //if the user chooses to not hit
    bool plyGone;       //if the player does not want to continue

    string plyCard;     //the card name in reference to the array
    string delCard;     //dealer card name in reference to the array

    plyGone = false;
    plyCash = 100;
    int sCash= plyCash;
    do
        {
        int betWrth;      //the worth of the bet that the user chose

        plyCnt = 0;
        dealCnt = 0;

        plyCard = "";
        delCard = "";

        noHit = false;

        do
        {
            //  INPUT -- get the desired amount the user wants to bet.
            cout    <<"You have $"<<plyCash<<". Enter bet:"<<endl;
            cin     >>betWrth;
        }while(betWrth < 1 || betWrth > plyCash);

        //PROCESSING -- Subtracts the user's desired bet amount from their current balance
        plyCash -= betWrth;

        //PROCESSING -- calls the function draw_card to determine the player's count.
        for(int i = 0; i < 2; i++){
            string cardNam = "";
            plyCnt += draw_card(cardNam,plyCnt);
            plyCard+=cardNam;
            int tst = plyCnt;
            float test = plyCash;
            printNumber (tst);
            printNumber (test);
        }

        //OUTPUT -- Displays the player's cards
        cout    <<"Your Cards are:\n";
        cout    <<plyCard;


        if(plyCnt < 21){
            do{
                //INPUT -- Asks the player if they want another card
                char temp;
                cout    <<"Your total is "<<plyCnt<<". Do you want another card (y/n)?\n";
                cin     >>temp;

                //PROCESSING -- checks if the user chooses to get another card and draws a card.
                if(temp == 'y'){

                    string cardNam;

                    //PROCESSING -- adds the new cards count to the current player's count
                    plyCnt+=draw_card(cardNam,plyCnt);
                    plyCard+=cardNam;

                     //OUTPUT -- Displays the player's cards
                    cout    <<"Your Cards are:\n";
                    cout    <<plyCard;

                    //PROCESSING -- Sees if the user's total count goes over 21.
                    if(plyCnt > 21){

                        //OUTPUT -- Displays the player's count
                        cout    <<"Your total is "<<plyCnt<<endl;
                        cout    <<"Your count is over 21. That's a bust!\n";
                        noHit = true;
                    }
                }else{
                    noHit = true;
                }
            }while(!noHit);
        }


         //PROCESSING -- Draws two cards for the dealer.
        for(int i = 0; i < 2; i++){
            string cardNam = "";

            //PROCESSING -- Adds the cards count to the dealer's current count.
            dealCnt += draw_card(cardNam,dealCnt);
            delCard+=cardNam;
        }

        //OUTPUT -- Displays the dealer's current cards.
        cout    <<"\nThe Dealer's cards are:\n";
        cout    <<delCard;

        //OUTPUT -- Displays the dealer's current count.
        cout    <<"The Dealer's count is: "<<dealCnt<<endl;

        //PROCESSING -- Checks if the dealers count is less then 16 and will get new cards. Also checks if the player has 21 already
        while(dealCnt <= 16 && plyCnt <= 21){

            string cardNam = "";

            //PROCESSING -- adds the new cards count to the dealers's current count
            dealCnt += draw_card(cardNam,dealCnt);

            //OUTPUT -- Displays the dealer's count.
            cout    <<"The Dealer draws a card!\n"<<cardNam;
            cout    <<"The Dealer's count is: "<<dealCnt<<endl;
        }

        //PROCESSING -- checks for win, lose, and tie conditions
        if(dealCnt == plyCnt){

            //OUTPUT -- Displays a message saying that there is a tie.
            cout    <<"Both of you have the same count. Tie!\n\n";

            //PROCESSING -- Adds the user's initial bet back
            plyCash+=betWrth;

        }else if(plyCnt > dealCnt && plyCnt <= 21 || plyCnt <=21 && dealCnt > 21){

            //OUTPUT -- Displays a message saying that the player wins
            cout    <<"You win!\n\n";

            //PROCESSING -- Returns the initial bet * 2
            plyCash+=betWrth*2;

        }else{

            //OUTPUT -- Displays a message saying the the player loses.
            cout<<"\nYou lose!\n\n";

        }


        char resp;

        //INPUT -- Asks if the user would like to play again.
        cout    <<"Play again?(y/n):\n";
        cin     >>resp;
        
        //PROCESSING -- checks if the user says no and if so ends the game.
        if(resp == 'y'){
            plyGone = true;
        }else exit(0);

    //PROCESSING -- checks the user has over 1000 or 0
    if(plyCash >= 1000){

        //OUTPUT -- displays a winning message.
        cout<<"YOU HAVE OVER $1000. YOU WIN!!!\n\n\n";
        
    }else if(plyCash == 0){
        
        //OUTPUT -- displays a losing message.
        cout<<"You have $0. GAME OVER\n\n\n";
        plyGone=false;
        cout<<"You have no more money. Sorry."<<endl;
        return false;
    }



    //PROCESSING -- checks if the users reaches below 0, above 1000, or chooses to leave the game.
    }while(plyCash > 0 || plyCash <= 1000 || plyGone);





    return 0;
}


int draw_card (string &card,            //card info
                int drawpts)      //current drawer's points
{
string CARDV[13] = {"Ace", "Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
string CARDS[4] = {"Diamonds","Clubs","Heart","Spades"};
    //Generates a random number to choose the card value and the suit.
    int cardVal = rand()%13;
    int cardSui = rand()%3;
    static int shVal;
    vector<int> g1;
    //Creates a string to display the card name
    card = "   "+CARDV[cardVal]+" of "+CARDS[cardSui]+"\n";

    //PROCESSING -- checks the card value and returns the value.
    if(cardVal >= 9){
        return 10;
    }else if (cardVal == 0){
        if(drawpts > 11){
            return 1;
        }else{
            return 11;
        }
    }
    return cardVal+1;
}
void BubbleSort(int *a, int siz) //template for the card sorting 
{                                //works but not with card need to add
	int i,j,k,temp;
	for(i = 0; i < siz-1; i++) {
		for(j=0; j < siz -1; j++) {
			if(*(a+j) > *(a+j+1)) {
				temp = *(a+j+1);
				*(a+j+1) = *(a+j);
				*(a+j) = temp;
			}
		}
		for(k = 0; k < siz; k++) 
		  cout << *(a+k) <<" ";
	    cout << endl;
	}
	int dum = 1;
}
void printNumber (int u){//playcount overloading
    cout<<endl;
};
void printNumber (float u){//playercash overloading
    cout<<"";
};

