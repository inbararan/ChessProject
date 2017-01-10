#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Game.h"

using namespace std;
void main()
{
	srand(time_t(NULL));

	system("start chessGraphics.exe");
	Sleep(1000);

	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	
	cout << "Connected to pipe." << endl;

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	Game game;

	strcpy_s(msgToGraphics, game.getBoardRepr().c_str());
	
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)

		cout << "Recieved from graphics: " << msgFromGraphics << endl;
		MoveReport report = { 0 };
		strcpy_s(msgToGraphics, game.nextMove(msgFromGraphics, report).c_str()); // msgToGraphics should contain the result of the operation

		if (report.promotionAvaliable) // Promotion is avaliable for user
		{
			char choice = ' ';
			cout << "STOP!" << endl << "You can promote last moved unit!" << endl;
			do
			{
				cout << "Insert desired unit (q/r/b/n) : ";
				cin >> choice;
			}
			while (game.promote(report.moved, choice));
		}
		if (report.needsReopen)
		{
			p.close();
			system("taskkill /im chessGraphics.exe");
			Sleep(500);
			system("start chessGraphics.exe");
			Sleep(500);
			p.connect();
			strcpy_s(msgToGraphics, game.getBoardRepr().c_str());
		}

		cout << "Sending to graphics: " << msgToGraphics << endl;

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}