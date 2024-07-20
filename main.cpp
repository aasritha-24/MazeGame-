#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

std::mt19937 rng (std::time (nullptr));

bool
isValid (int nrow, int ncol, vector < vector < int >>&visited, int noOfRows,
		 int noOfCols)
{
  return (nrow >= 0 && nrow < noOfRows && ncol >= 0 && ncol < noOfCols
		  && !visited[nrow][ncol]);
}

// Depth-First Search (DFS) function to generate the maze
void
dfs (int row, int col, vector < vector < int >>&visited, stack < pair < int,
	 int >>&st, int noOfRows, int noOfCols)
{
  visited[row][col] = 1;
  st.push (
			{
			row, col});
  int drow[] = { 1, 0, -1, 0 };
  int dcol[] = { 0, 1, 0, -1 };
  vector < int >directions = { 0, 1, 2, 3 };
  shuffle (directions.begin (), directions.end (), rng);
  for (int i = 0; i < 4; i++)
	{
	  int nrow = row + drow[directions[i]];
	  int ncol = col + dcol[directions[i]];
	  if (nrow == noOfRows - 1 && ncol == noOfCols - 1)
		{
		  visited[noOfRows - 1][noOfCols - 1] = 1;
		  break;
		}
	  if (isValid (nrow, ncol, visited, noOfRows, noOfCols))
		{
		  dfs (nrow, ncol, visited, st, noOfRows, noOfCols);
		  break;
		}
	}
  if (!visited[noOfRows - 1][noOfCols - 1])
	{
	  st.pop ();
	  int prevRow = st.top ().first;
	  int prevCol = st.top ().second;
	  st.pop ();
	  dfs (prevRow, prevCol, visited, st, noOfRows, noOfCols);
	}
}

void printMaze(vector<vector<char>>&grid,int noOfRows,int noOfCols){
    for (int i = 0; i < noOfRows; ++i)
	{
	  for (int j = 0; j < noOfCols; ++j)
		{
		 cout<<grid[i][j]<<" ";
		  }
	  cout << endl;
	}
}

void
generateMaze (int noOfRows, int noOfCols, vector < vector < char >>&grid)
{
  vector < vector < int >>visited (noOfRows, vector < int >(noOfCols, 0));
  stack < pair < int, int >>st;
  grid[noOfRows - 1][noOfCols - 1] = 'E';
  while (!visited[noOfRows - 1][noOfCols - 1])
	{
	  dfs (0, 0, visited, st, noOfRows, noOfCols);
	}
  while (!st.empty ())
	{
	  int i = st.top ().first;
	  int j = st.top ().second;
	  grid[i][j] = '1';
	  st.pop ();
	}
  grid[0][0] = '@';

  cout << "Find your path to E moving through 1's :" << endl;
  printMaze(grid,noOfRows,noOfCols);
}

// Function to handle user movement in the maze
void
movefn (vector < vector < char >>&grid, int row, int col, int noOfRows,
		int noOfCols)
{
  if (grid[noOfRows - 1][noOfCols - 1] != '@')
	{
	  char move;
	  cout << "Move : Enter D/L/R/U" << endl;
	  cin >> move;
	  switch (move)
		{
		case ('D'):
		  if (grid[row + 1][col] != '0' && row + 1 < noOfRows)
			{
			  grid[row][col] = '1';
			  grid[row + 1][col] = '@';
			  printMaze(grid,noOfRows,noOfCols);
			  movefn (grid, row + 1, col, noOfRows, noOfCols);
			}
		  else
			{
			  cout << "Invalid Move" << endl;
			  cout << "Try Again" << endl;
			  movefn (grid, row, col, noOfRows, noOfCols);
			}
		  break;
		case ('L'):
		  if (grid[col - 1][row] != '0' && col - 1 >= 0)
			{
			  grid[row][col] = '1';
			  grid[row][col - 1] = '@';
			  printMaze(grid,noOfRows,noOfCols);
			  movefn (grid, row, col - 1, noOfRows, noOfCols);
			}
		  else
			{
			  cout << "Invalid Move" << endl;
			  cout << "Try Again" << endl;
			  movefn (grid, row, col, noOfRows, noOfCols);
			}
		  break;
		case ('R'):
		  if (grid[row][col + 1] != '0' && col + 1 < noOfCols)
			{
			  grid[row][col] = '1';
			  grid[row][col + 1] = '@';
			  printMaze(grid,noOfRows,noOfCols);
			  movefn (grid, row, col + 1, noOfRows, noOfCols);
			}
		  else
			{
			  cout << "Invalid Move" << endl;
			  cout << "Try Again" << endl;
			  movefn (grid, row, col, noOfRows, noOfCols);
			}
		  break;
		case ('U'):
		  if (grid[row - 1][col] != '0' && row - 1 >= 0)
			{
			  grid[row][col] = '1';
			  grid[row - 1][col] = '@';
			  printMaze(grid,noOfRows,noOfCols);
			  movefn (grid, row - 1, col, noOfRows, noOfCols);
			}
		  else
			{
			  cout << "Invalid Move" << endl;
			  cout << "Try Again" << endl;
			  movefn (grid, row, col, noOfRows, noOfCols);
			}
		  break;
		default:
		  cout << "InValid Input" << endl;
		  cout << "Try Again" << endl;
		  movefn (grid, row, col, noOfRows, noOfCols);
		}
	}
  else
	cout << "Congratulations! You solved the maze" << endl;
}

int
main ()
{
  int noOfRows, noOfCols;
  cout << "Welcome to MazeSolver" << endl;
  cout << "Enter the number of rows and columns: ";
  cin >> noOfRows >> noOfCols;
  vector < vector < char >>grid (noOfRows, vector < char >(noOfCols, '0'));
  generateMaze (noOfRows, noOfCols, grid);
  movefn (grid, 0, 0, noOfRows, noOfCols);
  return 0;
}
