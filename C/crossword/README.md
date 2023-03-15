## Crossword
#### this program takes as input a crossword board, its list of words
   and checks if there is a solution for the given list of words and
   the board.
   
   The input goes as follows: 
   - It first reads the size of the board, as lines and columns.
   - Then it reads the layout of the board where -1 is where you cannot place letters and 0 where letters can be places
   - Next is the number of words
   - Finally is the list of words to be tried in the board

An example of an input below:  

5 4  
-1 0 0 0  
0 0 0 0  
0 0 -1 0  
0 0 0 0  
0 -1 0 0  
10  
ad  
antas  
carn  
casa  
do  
lado  
lua  
os  
soda  
ur  

The caveat of this program is that the list of words can only start at the left edges of the board going left to right and the top edge going top to bottom. 
Also, words can start right next to spaces where words cannot be placed (-1). In these cases, it behaves as it if were and edge
where words can go left to right and top to botton from the squares to the right and below the -1 square.

