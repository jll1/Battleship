#include <iostream>
#include <vector>
#include <array>
#include <string.h>
#include <cstdlib>
using namespace std;
enum class Status {CONTINUE,FIRE,END};
Status gamestatus;
const string ship[]{"Destroyer", "Submarine", "Cruiser", "Battleship","Carrier"};
const int shipsize[]{2,3,3,4,5};
const int rowsize = 9;
const int columnsize = 9;
int turn=1;

void enterToContinue(){
	cout<<"\nPress enter to continue!";
	cin.clear(); //clears the stream
	cin.ignore(200,'\n'); //ignores next line(enter)
	cin.get(); //“cin>>” expects at least one char input, just enter doesn’t work
	//cout << string( 50, '\n' );//clear screen standard
}

class User{
	public:
	string name;
	void setnam(string n){name=n;}
	string getnam(){return name;}
	void fire(User *p);
	bool checklost(User *p){//check loss by looping through board to find ships
		if(!p->bd.shipleft(p)){
			cout << "\n";
			p->bd.displayboard();
			cout << p->getnam() << " you won!";
			delete p;
			_Exit(1);
		}
		return p->bd.shipLeft;
	}
	class Ship{
	public:
	int size;
	string type;
	bool isSunk=false;
	int hits=0;
	int getSize(){return size;}
	string getType(){return type;}
	void hit(){}
	};
class Board{
	public:
	char squares[columnsize][rowsize] = {};
	bool shipLeft;
	class BattleshipSquare{
	Ship* s;
	bool isFired;
	void reset(){
		this->s=NULL;
	}
	char getStatus(int y, int c,User p){
		char n = p.bd.squares[y][c];
		if(n==NULL){cout<<"Square is empty";}else{cout << "State: " << n;}
		return n;
	}
	};
	void displayboard(){
	cout<< " | A B C D E F G H\n"
		<<"  -----------------"<< endl;
	if(Status::FIRE == gamestatus){
		turn += 1;
		for (int i = 1; i <9; i++) {
			cout<< i<<"|";
			for (int j = 1; j < 9; j++) {
				if(squares[i][j]=='H' || squares[i][j]=='M'){
					cout << " " << squares[i][j];}
				else{cout << "  ";}
			}cout << "\n-------------------" << endl;
		}
	}else{
		for (int i = 1; i <9; i++) {
			cout<< i<<"|";
			for (int j = 1; j < 9; j++) {
				cout << " " << squares[i][j];
			}cout << "\n-------------------" << endl;
		}
	}
	}
	char getSquarestate(int y, int c,User p){
		char n = p.bd.squares[y][c];
		if(n==NULL){cout<<"Square is empty";}else{cout << "State: " << n;}
		return n;
	}
	void placeship(int size,int shipn, User* p){//place each ship on coordinates
		int y;
		char x,d;
		cout <<"\n" << p->getnam() << " add a " << ship[shipn] << " size: " << shipsize[shipn] <<"\n";
		cout<<"Enter the x coordinate (A-H): ";
		cin>>x;
		x=(toupper(x));//convert x to uppercase
		if(x < 'A' || x > 'H'){//check if user entered valid char
			do{
				cout<<"Enter valid x coordinate(A-H): ";//do until user enters valid char
				cin >> x;
				x=(toupper(x));
			}while(x < 'A' || x > 'H');
		}
		int c;
		switch(x) {
		  case 'A': c = 1;break;
		  case 'B': c = 2;break;
		  case 'C': c = 3;break;
		  case 'D': c = 4;break;
		  case 'E': c = 5;break;
		  case 'F': c = 6;break;
		  case 'G': c = 7;break;
		  case 'H': c = 8;break;
		  default:break;
		}
		cout<<"Enter the y coordinate (1-8): ";
		cin>>y;
		if(y <1 || y >8){//check whether user entered valid number
			do{
				cout<<"Enter valid y coordinate(1-8): ";//do until user enters valid number
				cin >> y;
			}while(y <1 || y >8);
		}
		cout<<"Enter the direction (N/E/S/W): ";
		cin>>d;
		d=(toupper(d));
		if(d != 'N' && d != 'E' && d != 'S' && d != 'W'){//check whether user entered valid direction
			do{
				cout<<"Enter valid direction (N/E/S/W): ";//do until user enters valid direction
				cin >> d;
				d=(toupper(d));
			}while(d != 'N' && d != 'E' && d != 'S' &&  d != 'W');
		}
		if ((y-size<0 && d=='N') || (y+size>9 && d=='S') || (c-size<0 && d=='W') || (c+size>9 && d=='E') || ( p->bd.squares[y][c] == 'S') ||
				((d=='N') && (p->bd.squares[y-1][c] == 'S' || p->bd.squares[y-2][c] == 'S' || p->bd.squares[y-size+1][c] == 'S')) ||
				((d=='S') && (p->bd.squares[y+1][c] == 'S' || p->bd.squares[y+2][c] == 'S' || p->bd.squares[y+size+1][c] == 'S')) ||
				((d=='E') && (p->bd.squares[y][c+1] == 'S' || p->bd.squares[y][c+2] == 'S' || p->bd.squares[y][c+size+1] == 'S')) ||
				((d=='W') && (p->bd.squares[y][c-1] == 'S' || p->bd.squares[y][c-2] == 'S' || p->bd.squares[y][c-size+1] == 'S'))){
			cout<<"Invalid entry! Please try again.";
			placeship(size,shipn,p);
		}else{
			int z=y;
			switch(d) {
			  case 'N':for(int z=0;z<size;z++){p->bd.squares[y][c] = 'S';y -= 1;}break;
			  case 'S':for(int z=0;z<size;z++){p->bd.squares[y][c] = 'S';y += 1;}break;
			  case 'E':for(int z=0;z<size;z++){p->bd.squares[y][c] = 'S';c += 1;}break;
			  case 'W':for(int z=0;z<size;z++){p->bd.squares[y][c] = 'S';c -= 1;}break;
			  default:break;
			}
			cout << p->getnam() << " added a " << ship[shipn]
				<< " to x:" << x << "  y:" << z << " Direction:" << d << endl;
			p->bd.displayboard();
		}
	}
	void fireatsquare(User *p){//get x y coordinates
		int a,b;
		char c;
		cout << p->getnam() << " enter coordinates to fire\n";
		cout<<"Enter the x coordinate (A-J): ";
		cin>>c;
		c=(toupper(c));//convert x to uppercase
		if(c < 'A' || c > 'H'){//check if user entered valid char
			do{
				cout<<"Enter valid x coordinate(A-H): ";//do until user enters valid char
				cin >> c;
				c=(toupper(c));
			}while(c < 'A' || c > 'H');
		}
		switch(c) {
		  case 'A': b = 1;break;
		  case 'B': b = 2;break;
		  case 'C': b = 3;break;
		  case 'D': b = 4;break;
		  case 'E': b = 5;break;
		  case 'F': b = 6;break;
		  case 'G': b = 7;break;
		  case 'H': b = 8;break;
		  default:break;
		}
		cout<<"Enter the y coordinate (1-8): ";
		cin>>a;
		if(a <1 || a >8){//check whether user entered valid number
			do{
				cout<<"Enter valid y coordinate(1-8): ";//do until user enters valid number
				cin >> a;
			}while(a <1 || a >8);
		}

		if (p->bd.squares[a][b] == 'H'){
			cout<<"Invalid entry! Please try again.\n";
			fireatsquare(p);
		}else if(p->bd.squares[a][b] == 'S'){
			cout << "Its a hit!";
			p->bd.squares[a][b] = 'H';
			enterToContinue();
		}else{
			cout << "Miss";
			p->bd.squares[a][b] = 'M';
			enterToContinue();
		}
	}
	bool shipleft(User *p){
		p->bd.shipLeft=false;
		for (int i = 1; i <9; i++) {
			for (int j = 1; j < 9; j++) {
				if(p->bd.squares[i][j]=='S'){
					p->bd.shipLeft=true;
				}
			}
		}
		return p->bd.shipLeft;
	}
	void resetboard(User *p){
		for (int i = 1; i <9; i++) {
			for (int j = 1; j < 9; j++) {
				p->bd.squares[i][j]=NULL;
			}
		}
	}
};Board bd;};
User p1,p2;

void fire(User *p){
	do{
		for(User n : {p1,p2}){
		if(n.getnam()==p1.getnam()){p = &p1;}else if(n.getnam()==p2.getnam()){p = &p2;}
		cout << "\n\nTurn: " << turn << "\n";
		p->bd.displayboard();
		p->bd.fireatsquare(p);
		p->checklost(p);}
	}while(p->bd.shipLeft);
}

void addships(){
	User *p = new User;
	for(User n : {p1,p2}){
		User::Ship s[4];
		if(n.getnam()==p1.getnam()){p = &p1;}else{p = &p2;}
		cout<<"\n---------------------------------"//display add ships menu
			<<"\n\tAdd Ships"
			<<"\n---------------------------------"
			<< "\n No Name \t Squares"
			<<"\n---------------------------------"
			<<"\n 1  Carrier \t 5"
			<<"\n 1  Battleship \t 4"
			<<"\n 2  Cruiser \t 3"
			<<"\n 1  Submarine \t 3"
			<<"\n 1  Destroyer \t 2"
			<<"\n---------------------------------";
		for(int i=1; i<6; i++){//add 5 ships
			p->bd.placeship(shipsize[i-1],i-1,p);
			s[i].size=shipsize[i-1];
			s[i].type=ship[i-1];
			User::Board::BattleshipSquare s=s;
		}cout << "All ships are added!";enterToContinue();
	}

	for (int i = 1; i<9; i++) {//swap boards
		for (int j = 1; j < 9; j++) {
			   char temp = p1.bd.squares[i][j];
			   p1.bd.squares[i][j] = p2.bd.squares[i][j];
			   p2.bd.squares[i][j] = temp;
		}
	}
	gamestatus = Status::FIRE;
	fire(p);
}

void menu(){
	int choice;//initialize choice at main menu
	cout<<"---------------------------------"//display menu
		<<"\n\tBattleships \n\t Main Menu"
		<<"\n---------------------------------"
		<<"\n \t 1. Start Game"
		<<"\n \t 2. Exit Game"
		<<"\n\nEnter selection(1 or 2): ";
	cin >> choice;
	if(choice != 1 && choice != 2){//check whether user entered valid number
		do{
			cout<<"Enter valid selection(1 or 2): ";//do until user enters valid number
			cin >> choice;
		}while(choice != 1 && choice != 2);
	}
	if(choice == 1){//start game
		gamestatus = Status::CONTINUE;
	}else if(choice == 2){//end game
		gamestatus = Status::END;
		cout<<"Goodbye";
	}
}

int mains(){//main function
	menu();
	if(Status::CONTINUE == gamestatus){
		string n1,n2;
		cout<<"User 1 Enter Name: ";
		cin >> n1;
		cout<<"User 2 Enter Name: ";
		cin >> n2;
		n1[0]=toupper(n1[0]);n2[0]=toupper(n2[0]);
		p1.setnam(n1);p2.setnam(n2);
		addships();
	}
	return 1;
}
