# Grocery List Management Program

## Overview

This project is a Grocery List Management Program designed to create a grocery list based on a meal plan and an inventory of existing items. The list is sorted by item name and updates quantities appropriately. The user can specify the name of the input and output files.

### Program Details

The program processes two files:
1. **Meal Plan File**: Specifies the ingredients and quantities for meals. These items are added to the grocery list, updating the quantities for duplicates.
2. **Inventory File**: Lists items that are already available. For each item present in the inventory, the program reduces the corresponding quantity in the grocery list or removes the item entirely if the quantity reaches zero.

Both input files and the resulting grocery list have the following format:

<quantity> <item name>

Blank lines in the input files are ignored.

### Files

- `a4p2.cpp`: Main program file containing the implementation of the grocery list management logic.
- `GroceryList.cpp`: Implements the `GroceryList` class, which manages the list of items and quantities.
- `GroceryList.h`: Header file for the `GroceryList` class, defining its public and private methods.
- `globals.h`: Defines global constants and types used across the program.

## Compilation and Execution

### Compilation

To compile the program, you can use the following command in your terminal:

g++ a4p2.cpp GroceryList.cpp -o grocery_list_manager


This will compile the main program and the `GroceryList` class into an executable named `grocery_list_manager`.

### Running the Program

To run the program, use the command:

./grocery_list_manager

The program will prompt you for:
1. The name of the meal plan file.
2. The name of the inventory file.
3. The name of the output file where the final grocery list will be saved.

## Program Usage

1. **Meal Plan Input**: Enter the filename of the meal plan when prompted.
2. **Inventory Input**: Enter the filename of the inventory list when prompted.
3. **Output File**: Specify the name of the output file where the resulting grocery list will be saved.

### Example

If the input files are named `meal_plan.txt` and `inventory.txt`, and you want the output in `grocery_list.txt`, you would run:

./grocery_list_manager
enter ingredients file name  : meal_plan.txt
enter inventory file name    : inventory.txt
enter name of grocery list file to create   : grocery_list.txt

Upon completion, the program will inform you that the grocery list has been created in the specified output file.

## Error Handling

- If a file cannot be opened (e.g., due to an incorrect filename), the program will prompt you to re-enter the filename until a valid file is provided.
- The program assumes all input data is valid and does not perform error checking on the contents of the files beyond basic format checks.

## Author

- Name: Diego Gonzalez Reyes
- Email: dgonz348@mtroyal.ca
- Course: COMP 1633 - 002
- Instructor: Paul Pospisil

## License

This project is for educational purposes under the supervision of the instructor Paul Pospisil as part of COMP 1633 at Mount Royal University.

