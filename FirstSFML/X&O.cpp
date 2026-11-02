#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define Board_Size 3
#define Cell_Size 100

const int WINDOW_SIZE = Board_Size * Cell_Size;

enum Player{NONE , PLAYER_X , PLAYER_O};

Player board[Board_Size][Board_Size];
Player current_player = PLAYER_X;

void drawBoard(RenderWindow& window)
{
	window.clear(Color::White);
	for (int i = 1; i < Board_Size; i++)
	{
		RectangleShape line(Vector2f(WINDOW_SIZE, 5));
		line.setPosition(0 , i * Cell_Size);
		line.setFillColor(Color::Black);
		window.draw(line);

		line.setSize(Vector2f(5, WINDOW_SIZE));
		line.setPosition(i * Cell_Size, 0);
		window.draw(line);
	}

	for (int i = 0; i < Board_Size; i++)
	{
		for (int j = 0; j < Board_Size; j++)
		{
			if (board[i][j] != NONE)
			{
				Text text;
				Font font;
				font.loadFromFile("./Valentine.otf");
				text.setFont(font);
				text.setString(board[i][j] == PLAYER_O ? 'X' : 'O');
				text.setCharacterSize(50);
				text.setFillColor(Color::Black);
				text.setPosition(j * Cell_Size + 30 , i * Cell_Size + 17);
				window.draw(text);
			}
		}
	}
	window.display();
}

bool check_win(Player player)
{
	for (int i = 0; i < Board_Size; i++)
	{
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
			return true;
		if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
			return true;
	}
	if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
		(board[0][2] == player && board[1][1] == player && board[2][0] == player))
		return true;
	return false;
}

bool draw()
{
	for (int i = 0; i < Board_Size; i++)
		for (int j = 0; j < Board_Size; j++)
			if (board[i][j] == NONE)
				return false;
	return true;
	
}

int main()
{
	RenderWindow window(VideoMode(WINDOW_SIZE , WINDOW_SIZE) , "X & 0");
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				int x = event.mouseButton.x / Cell_Size;
				int y = event.mouseButton.y / Cell_Size;

				if (board[y][x] == NONE)
				{
					board[y][x] = current_player;
					if (check_win(current_player))
					{
						cout << (current_player == PLAYER_X ? "Player_X" : "Player_O") << " wins!\n";
						window.close();
						return 0;
					}
					current_player = (current_player == PLAYER_X) ? PLAYER_O : PLAYER_X;
				}
				if (draw())
				{
					cout << "DRAW!\n";
					window.close();
					return 0;
				}
			}
		}

		drawBoard(window);
	}

	return 0;
}