#include <iostream>
#include <deque>
#include "Tree.h"
int main()
{
	puzzle_arr puzzlearr1{ 1, 2, 3,
					      0, 8, 4,
						  7, 6, 5 };
	puzzle_arr puzzlearr2{ 1, 3, 4,
						  7, 8, 5,
						  0, 2, 6 };
	puzzle_arr puzzlearr3{ 0, 2, 3,
						   1, 6, 4,
						   8, 7, 5 };
	puzzle_arr puzzlearr4{ 1, 2, 3,
					       6, 4, 0,
					       8, 7, 5 };
	puzzle_arr puzzlearr5{ 1, 3, 6,
					       5, 7, 2,
					       0, 8, 4 };
	puzzle_arr puzzlearr6{ 5,7,4,1,8,0,2,3,6 };
	puzzle_arr puzzlearr7{ 6,0,3,7,1,2,4,5,8 };
	puzzle_arr puzzlearr8{ 0,1,2,3,4,7,5,8,6 };
	puzzle_arr puzzlearr9{ 8,3,6,7,5,2,1,0,4 };
	Bothway_Puzzle puzzle(puzzlearr8);
	puzzle.rserch();
	puzzle.display_answer();
	return 0;
}