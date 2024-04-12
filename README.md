# Sudoku Generation

generate 4x4, 9x9, 16x16 sudokus with a unique solution.

------


## Usage

`SudokuGenerator(size).sudoku(removeCellCount, maxGenerationTime);`
- where `size` can be 2, 3, or 4, indicating a 4x4, 9x9, or 16x16 Sudoku size.
- `removeCellCount` specifies the number of Sudoku cells to remove, and if you specify a large number, the program will remove as many cells as possible.
- `maxGenerationTime` specifies the maximum time the program can use to generate the Sudoku. If the program reaches `maxGenerationTime` without removing the specified `removeCellCount` cells, it will return a Sudoku with as many cells removed as possible.


## Example
```
Enter sudoku size(choose 2, 3 or 4) :(eg. 3)
3
Enter sudoku remove count:(eg. 60)
60
Enter max generation time:(eg. 3)
4

Remove 58 Cells
Remain 23 Cells
Sudoku Board:
. . 8 | . . . | 5 . . 
. . . | . 8 1 | . 3 . 
. 7 . | . . . | 2 . . 
- - - - - - - - - - - 
. 4 . | . . . | 6 . . 
. . . | 9 . . | . . 2 
. . . | 3 7 . | 8 . 5 
- - - - - - - - - - - 
. . 3 | 6 . 5 | . . . 
. . . | . . 3 | . . 6 
. 1 . | . . 2 | . 7 . 

Sudoku Answer:
1 2 8 | 4 3 7 | 5 6 9 
9 5 6 | 2 8 1 | 4 3 7 
3 7 4 | 5 6 9 | 2 8 1 
- - - - - - - - - - - 
5 4 7 | 1 2 8 | 6 9 3 
8 3 1 | 9 5 6 | 7 4 2 
2 6 9 | 3 7 4 | 8 1 5 
- - - - - - - - - - - 
7 9 3 | 6 4 5 | 1 2 8 
4 8 2 | 7 1 3 | 9 5 6 
6 1 5 | 8 9 2 | 3 7 4 
```

## License

Sudoku Generation is available under the MIT license. See the LICENSE file for more info.
# SUDOKU-generation
