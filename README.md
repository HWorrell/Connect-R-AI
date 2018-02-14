# Connect-R-AI
Connect R (Generic size connect 4
This is a project I created in my AI class to play NxM Connect R (generic sizeable connect 4)

It uses a MiniMax algorithim and heuristic to find the best possible move.

I delete the objects as I finish with them, so the program runs in a very small memory profile compared to many other recursive algoritims.

There is a small issue with it, during the "Tournament" we had for the class, I discovered a logic error exists somewhere in the MiniMax that causes it to make illegal moves.

Future development ideas: 
1) Fix the logic error.
2) Parallelize the MiniMax search (OpenMP seems a good candidate for it.)
