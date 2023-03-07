
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <unordered_set>

using namespace std;

// Check if a given row in a Sudoku puzzle is valid. parameters: shared pointer, column Number and errors(passed as reference). returns: true or false.
bool rowCheck(shared_ptr<char[]> sudokuArr, int rowNum, string &errors)
{
    // Create an unordered_set named "used" to keep track of characters seen in the row.
    unordered_set<char> used;

    // Calculate the starting index of the current row in "sudokuArr".
    int startIndex = (rowNum - 1) * 9;

    // Loop through each character in the row.
    for (int i = 0; i < 9; i++, startIndex++)
    {
        char c = *(sudokuArr.get() + startIndex);

        // If the current character is not a space:
        if (c != ' ')
        {
            // Check if the character has already been seen in the row.
            if (!used.insert(c).second)
            { // insert method tries to inset c in used. Second method tell if insertion was successfull or not.
                // If the character has already been seen, set the errors string and return false.
                errors = c;
                return false;
            }
        }
    }

    // Release the ownership of the array managed by the shared pointer.
    sudokuArr.reset();
    // If no errors were found, return true.
    return true;
}

// Check if a given column in a Sudoku puzzle is valid. parameters: shared pointer, column Number and errors(passed as reference). returns: true or false.
bool columnCheck(shared_ptr<char[]> sudokuArr, int columnNum, string &errors)
{
    // Create an unordered_set named "used" to keep track of characters seen in the column.
    unordered_set<char> used;

    // Calculate the starting index of the first character in the column.
    int startIndex = columnNum - 1;

    // Loop through each character in the column.
    for (int i = 0; i < 9; i++, startIndex += 9)
    {
        // Get the character at the current index.
        char c = *(sudokuArr.get() + startIndex);

        // If the current character is not a space:
        if (c != ' ')
        {
            // Check if the character has already been seen in the column.
            if (!used.insert(c).second)
            {
                // If the character has already been seen, set the errors string and return false.
                errors = c;
                return false;
            }
        }
    }

    // Release the ownership of the array managed by the shared pointer.
    sudokuArr.reset();

    // If no errors were found, return true.
    return true;
}

// Check if a given sector in a Sudoku puzzle is valid. Parameters: shared pointer, sector Number and errors(passed as reference). Returns true or false.
bool sectorCheck(shared_ptr<char[]> sudokuArr, int sectorNum, string &errors)
{

    // Create an unordered_set named "used" to keep track of characters seen in the column.
    unordered_set<char> used;

    // Calculate the starting row and column of the specified sector
    int startRow = (sectorNum / 3) * 3;
    int startCol = (sectorNum % 3) * 3;

    // Calculate the starting index of the specified sector in the arr array
    int sectorIndex = startRow * 9 + startCol;

    // Loop over the 3x3 elements in the sector
    for (int i = 0; i < 3; i++, sectorIndex += 6)
    {
        for (int j = 0; j < 3; j++, sectorIndex++)
        {

            // Get the character at the current sector index
            char c = *(sudokuArr.get() + sectorIndex);

            // If the character is not a space, check if it has already been used in the sector
            if (c != ' ')
            {

                // If the character has already been used, set the errors pointer and return false
                if (!used.insert(c).second)
                {
                    errors = c;
                    return false;
                }
            }
        }
    }

    // Release the ownership of the array managed by the shared pointer.
    sudokuArr.reset();
    // Return true if all characters in the sector are valid
    return true;
}

// Check if a given Sudoku puzzle is solved. Parameters: shared pointer. returns: true or false.
bool solvedSudoku(shared_ptr<char[]> sudokuArr)
{

    for (int i = 0; i < 81; i++)
    {
        if (*(sudokuArr.get() + i) == ' ')
        {
            return false;
        }
    }

    // Release the ownership of the array managed by the shared pointer.
    sudokuArr.reset();
    // If all elements in the arr array are non-space characters, the puzzle is solved
    return true;
}

// Perform various Sudoku operations on a given puzzle. Parameters: shared pointer, puzzleNum variable.
void operations(shared_ptr<char[]> sudokuArr, string puzzleNum)
{

    // Initialize boolean flag and string errors
    bool isvalid = true;
    string errors = "";

    // Loop over each row, column, and sector in the puzzle
    for (int i = 1; i < 10; i++)
    {

        // Check the current row for duplicates
        if (!rowCheck(sudokuArr, i, errors))
        {
            cout << puzzleNum << "\tinvalid\trow " << i << " has multiple " << errors << "s\n";
            isvalid = false;
        }

        // Check the current column for duplicates
        if (!columnCheck(sudokuArr, i, errors))
        {
            cout << puzzleNum << "\tinvalid\tcolumn " << i << " has multiple " << errors << "s\n";
            isvalid = false;
        };

        // Check the current sector for duplicates
        if (!sectorCheck(sudokuArr, i - 1, errors))
        {
            if (i == 1)
                cout << puzzleNum << "\tinvalid\tupper left has multiple " << errors << "s\n";
            if (i == 2)
                cout << puzzleNum << "\tinvalid\tupper middle has multiple " << errors << "s\n";
            if (i == 3)
                cout << puzzleNum << "\tinvalid\tupper right has multiple " << errors << "s\n";
            if (i == 4)
                cout << puzzleNum << "\tinvalid\tleft has multiple " << errors << "s\n";
            if (i == 5)
                cout << puzzleNum << "\tinvalid\tmiddle has multiple " << errors << "s\n";
            if (i == 6)
                cout << puzzleNum << "\tinvalid\tright has multiple " << errors << "s\n";
            if (i == 7)
                cout << puzzleNum << "\tinvalid\tlower left has multiple " << errors << "s\n";
            if (i == 8)
                cout << puzzleNum << "\tinvalid\tlower middle has multiple " << errors << "s\n";
            if (i == 9)
                cout << puzzleNum << "\tinvalid\tlower right has multiple " << errors << "s\n";
            isvalid = false;
        };
    }

    // If the puzzle is valid and solved, print "solved". Otherwise, print "valid".
    if (isvalid)
    {
        if (solvedSudoku(sudokuArr))
            cout << puzzleNum << " solved" << endl;
        else
            cout << puzzleNum << " valid" << endl;
    }

    // Release the ownership of the array managed by the shared pointer.
    sudokuArr.reset();
}

int main()
{
    string fileName;

    // Get filename from user input
    cout << "Enter the filename: " << endl;
    cin >> fileName;

    // Open file with the given filename
    ifstream in(fileName);

    // Check if the file is opened successfully
    if (!in)
    {
        cout << "Error Opening the file" << endl;
        return 0;
    }

    shared_ptr<char[]> sudokuArr(new char[81]); // Create a shared pointer named sudokuArr with a dynamic array of char values of size 81.
    string puzzleNum = "";
    string line;
    int lineCounter = 1, arrInd = 0;

    // Read the file line by line
    while (getline(in, line))
    {
        // If this is the first line of a puzzle, extract the puzzle number
        if (lineCounter == 1)
        {
            puzzleNum = "";
            for (int i = 0; i < int(line.length()); i++)
            {
                if (isalnum(line.at(i)))
                    puzzleNum += line.at(i);
            }
            lineCounter++;
        }

        // If this is not the first line of a puzzle, read the sudoku grid
        else
        {
            // If the current line is part of the sudoku grid, copy it to the grid array
            if (arrInd < 9)
            {
                for (int i = 0; i < int(line.length()); i++)
                {
                    *(sudokuArr.get() + (arrInd * 9 + i)) = line.at(i);
                }
                arrInd++;
                lineCounter++;
            }
            // If we have read all 9 rows of the sudoku grid, perform operations on the grid
            else
            {
                arrInd = 0;
                operations(sudokuArr, puzzleNum);
            }
        }

        // If the line is empty, it means we have finished reading a whole puzzle
        // So we reset the lineCounter to 1 and work on other puzzle of the file if present
        if (line.empty())
        {
            lineCounter = 1;
            continue;
        }
    }

    // If we have finished reading the file but haven't finished processing the last puzzle, process it now
    if (arrInd != 0)
    {
        operations(sudokuArr, puzzleNum);
    }

    // Close the file
    in.close();

    // Release the ownership of the array managed by the shared pointer.
    sudokuArr.reset();
    return 0;
}
