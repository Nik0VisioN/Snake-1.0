#include <iostream>
#include <Windows.h>


using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() 
{
   gameOver = false;
   dir = STOP;
   x = width / 2;
   y = height / 2;
   fruitX = rand() % width;
   fruitY = rand() % height;
   score = 0;
   nTail = 0;
}

void Draw() 
{
   system("cls");

   
   for (int i = 0; i < width + 2; i++) cout << "#";
   cout << endl;

   for (int i = 0; i < height; i++) 
   {
      for (int j = 0; j < width; j++) 
      {
         if (j == 0) cout << "#";

         if (i == y && j == x)
            cout << "O"; 
         else if (i == fruitY && j == fruitX)
            cout << "F";
         else 
         {
            bool print = false;
            for (int k = 0; k < nTail; k++) 
            {
               if (tailX[k] == j && tailY[k] == i) 
               {
                  cout << "o"; 
                  print = true;
               }
            }
            if (!print) cout << " ";
         }
         if (j == width - 1) cout << "#";
      }
      cout << endl;
   }

   for (int i = 0; i < width + 2; i++) cout << "#";
   cout << endl;

   cout << "Score: " << score << endl;
}

void Input() 
{
   if (GetAsyncKeyState(VK_LEFT)  || GetAsyncKeyState('A') ) dir = LEFT;
   if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') ) dir = RIGHT;
   if (GetAsyncKeyState(VK_UP)    || GetAsyncKeyState('W') ) dir = UP;
   if (GetAsyncKeyState(VK_DOWN)  || GetAsyncKeyState('S') ) dir = DOWN;
   if (GetAsyncKeyState('X') ) gameOver = true;

}

void Logic() 
{
   int prevX = tailX[0], prevY = tailY[0];
   int prev2X, prev2Y;
   tailX[0] = x; tailY[0] = y;
   for (int i = 1; i < nTail; i++) 
   {
      prev2X = tailX[i];
      prev2Y = tailY[i];
      tailX[i] = prevX;
      tailY[i] = prevY;
      prevX = prev2X;
      prevY = prev2Y;
   }

   switch (dir) 
   {
      case LEFT:  x--; break;
      case RIGHT: x++; break;
      case UP:    y--; break;
      case DOWN:  y++; break;
      default: break;
   }

	//lose conditions
   if (x >= width || x < 0 || y >= height || y < 0) gameOver = true;
   for (int i = 0; i < nTail; i++)
      if (tailX[i] == x && tailY[i] == y) gameOver = true;

   if (x == fruitX && y == fruitY) 
   {
      score += 10;
      fruitX = rand() % width;
      fruitY = rand() % height;
      nTail++;
   }
}

void RunGame()
{
   Setup();
   while (!gameOver) 
   {
      Draw();
      Input();
      Logic();
      Sleep(120);
   }
}
int main() 
{
   bool exitGame = false;
   while (!exitGame) 
   {
      RunGame(); 

      system("cls");
      cout << "\n=== GAME OVER ===\n";
      cout << "Your score: " << score << "\n";
      cout << "Press R to restart or Q to quit\n";

      bool waitInput = true;
      while (waitInput) 
      {
         if (GetAsyncKeyState('R') ) 
         {
            waitInput = false;
         }
         if (GetAsyncKeyState('Q') ) 
         {
            waitInput = false;
            exitGame = true;
         }
      }
   }
   return 0;
}
