/*****
2   *
3   * Name:       Diego Gonzalez Reyes
4   * email:      dgonz348@mtroyal.ca
5   * Course:     COMP 1633 - 002
6   * Instructor: Paul Pospisil
7   * Assignment: 4
8   * Due Date:   March 24, 2023
9   *
10  * Source File:  a4p2.cpp
11  *
12  *****
13  *
14  *  PROGRAM: groc - Grocery List Management Program
15  *
16  *  PURPOSE: the program builds a grocery list, sorted by item name,
17  *           given a meal plan and an inventory of existing items.
18  *
19  *  DETAILS: The program processes a meal plan file which specifies the
20  *           ingredients for a number of meals. These items are added to
21  *           a grocery list that consist of item and quantity. Duplicate
22  *           items result in the quantity being updated. An inventory file
23  *           is then processed which consists of ingredients that are present.
24  *           For each ingredient item if it is present on the grocery list
25  *           results in either the quantity being reduced or the item being
26  *           completely removed from the list.
27  *           Once both files are processed the grocery list is written to a
28  *           file.
29  *
30  *           The program allows the user to specify the name of each file.
31  *
32  *           All three files have the same format which is:
33  *
34  *                <item quantity><space><item name>
35  *
36  *           Blank lines are allowed in the input files and are ignored.
37  *
38  *****/
39
40
41 #include <iostream>
42 #include <fstream>
43 #include <cstring>
44 // 1
45 // #include "groclist.h"
46 #include "GroceryList.h"
47
48 using namespace std;
49
50
51 const int MAX_FILENAME_LEN = 30;

void open_input_file(ifstream &in, const char prompt[]);
54 // 2
55 //void process_meal_plan(ifstream &meal_plan, Grocery_Item_Ptr &head);
56 //void process_inventory(ifstream &inventory, Grocery_Item_Ptr &head);
57 void process_meal_plan(ifstream &meal_plan, GroceryList &list);
58 void process_inventory(ifstream &inventory, GroceryList &list);
59 void read_input_line(ifstream &in, int &quantity, char item[], bool &success);
60 void read_filename(const char prompt[], char str[]);
61
62 int main()
63 {
64 // 3
65 //  Grocery_Item_Ptr head = NULL;
66   GroceryList list;
67   char grocery_list_filename[MAX_FILENAME_LEN + 1];
68   ifstream meal_plan;
69   ifstream inventory;
70   ofstream grocery_list;
71
72   open_input_file(meal_plan, "enter ingredients file name  : ");
73 // 4
74 //  process_meal_plan(meal_plan, head);
75   process_meal_plan(meal_plan, list);
76   meal_plan.close();
77
  open_input_file(inventory, "enter inventory file name    : ");
79  // 5
80  //  process_inventory(inventory, head);
81    process_inventory(inventory, list);
82    inventory.close();
83
84    read_filename("enter name of grocery list file to create   : ",
85                  grocery_list_filename);
86
87    grocery_list.open(grocery_list_filename);
88    if (grocery_list.fail())
89    {
90      cout << "unable to open " << grocery_list_filename
91           << " grocery list not saved" << endl;
92    }
93    else
94    {
95  // 6
96  //    write_list(head, grocery_list);
97      list.write(grocery_list);
98      grocery_list.close();
99
100     cout << endl << "grocery list produced in file '"
101          << grocery_list_filename
102          << "'" << endl << endl;
103   }
 // 7
105 //  remove_all_items(head);
106
107   return 0;
108 }
109
110
111 /*****
112  *
113  *  FUNCTION: open_input_file
114  *
115  *  PURPOSE:  reliably opens an input file of the user's choice.
116  *
117  *  INPUT:    prompt - the message which askes for the file name
118  *
119  *  OUTPUT:   in - the successfully opened input file
120  *
121  *  DETAILS:  the function forces the successful opening of
122  *            the user specified file.
123  *
124  *****/
125
126 void open_input_file(ifstream &in, const char prompt[])
127 {
128   char filename[MAX_FILENAME_LEN + 1];

  do
131   {
132
133     read_filename(prompt, filename);
134
135     in.open(filename);
136
137     if (in.fail())
138       cout << "couldn't open file "
139            << filename << endl;
140   }
141   while (in.fail());
142 }
143
144
145 /*****
146  *
147  *  FUNCTION: process_meal_plan
148  *
149  *  PURPOSE: to read each line in the meal plan file and build the
150  *           corresponding sorted grocery list.
151  *
152  *  INPUT: meal_plan - the previously opened meal plan file
153  *         head      - the grocery list (initially empty) to fill
154  *
155  *  OUTPUT: meal_plan - at EOF
 *          head      - the filled grocery list, sorted by item name with
157  *                      no duplicates
158  *
159  *  DETAILS: each pair of items read is added to the list, which is maintained
160  *           in alphabetical order. New items are inserted into the list,
161  *           whereas duplicate items result in the quantity being updated.
162  *
163  *****/
164 // 8
165 //void process_meal_plan(ifstream &meal_plan, Grocery_Item_Ptr &head)
166 void process_meal_plan(ifstream &meal_plan, GroceryList &list)
167 {
168   int quantity;
169   bool success;
170   char name[MAX_ITEM_NAME_LEN + 1];
171
172   read_input_line(meal_plan, quantity, name, success);
173
174   while (success)
175   {
176 // 9
177 //    insert_item(head, quantity, name);
178     if (list.contains(name))
179       list.updateQuantity(name, quantity);
180     else
181       list.insertItem(name, quantity);

183     read_input_line(meal_plan, quantity, name, success);
184   }
185 }
186
187
188 /*****
189  *
190  *  FUNCTION: process_inventory
191  *
192  *  PURPOSE: to read each line in the inventory file and remove
193  *           the corresponding items from the sorted grocery list.
194  *
195  *  INPUT: inventory - the previously opened inventory file
196  *         head      - the grocery list with items to cross out
197  *
198  *  OUTPUT: inventory - at EOF
199  *          head      - the updated grocery list, without the
200  *                      inventory items
201  *
202  *  DETAILS: each pair of items read is removed from the list, with the
203  *           alphabetical order beign maintained. The count of the item on
204  *           the list is reduced by the inventory quantity. If the list quantity
205  *           becomes less than or equal to 0 the item is removed from the list.
206  *
207  *****/

209 // 10
210 //void process_inventory(ifstream &inventory, Grocery_Item_Ptr &head)
211 void process_inventory(ifstream &inventory, GroceryList &list)
212 {
213 // 11
214   int want;
215   int quantity;
216   char name[MAX_ITEM_NAME_LEN + 1];
217   bool success;
218
219   read_input_line(inventory, quantity, name, success);
220
221   while (success)
222   {
223 // 12
224 //    remove_item(head, quantity, name);
225     if (list.contains(name))
226     {
227       want = list.getQuantity(name);
228       if (want - quantity <= 0)
229         list.removeItem(name);
230       else
231         list.updateQuantity(name, -1*quantity);
232     }
233     read_input_line(inventory, quantity, name, success);
   }
235 }
236
237
238 /*****
239  *
240  *  FUNCTION: read_input_line
241  *
242  *  PURPOSE: to read one item line (quantity + name) from the meal plan file.
243  *
244  *  INPUT: in - the previously opened meal plan file
245  *
246  *  OUTPUT: in       - the file position has been advanced
247  *          quantity - the quantity of the item, if valid line was read
248  *          name     - the name of the item, if valid line was read
249  *          success  - indicates if the line was valid or not
250  *
251  *  DETAILS: Two item pairs, quantity and description are attempted to be
252  *           read from the file. If a pair of items is read the success flag
253  *           will be returned with a value of true; otherwise encountering the
254  *           EOF will result in success being returned with a value of false.
255  *           The two items are separated by a single space, which needs to be
256  *           read and discarded.
257  *
258  *           The data is assumed to be valid as no error checking is done.
259  *
 *****/
261
262 void read_input_line(ifstream &in, int &quantity, char name[], bool &success)
263 {
264   char space;
265
266   success = true;
267   in >> quantity;
268   if (in.eof())
269     success = false;
270   else
271   {
272     in.get(space);
273     in.getline(name, MAX_ITEM_NAME_LEN + 1);
274   }
275 }
276
277
278 /*****
279  *
280  *  FUNCTION: read_filename
281  *
282  *  PURPOSE:  reliably reads from the user a c-string representing a filename
283  *
284  *  INPUT:    prompt - the message which askes for the file name
285  *
*  OUTPUT:   str - a non-empty c-string
287  *
288  *  DETAILS:  the function forces the user to enter a non-empty c-string,
289  *            representing a filename. The filename must also be less than
290  *            or equal to the specified maximum for a filename.
291  *
292  *****/
293 void read_filename(const char prompt[], char str[])
294 {
295   bool good_read = false;
296
297   do {
298     cout << prompt;
299     cin.getline(str, MAX_FILENAME_LEN + 1);
300
301     if (strlen(str) > 0)
302       good_read = true;
303     else
304       cout << "The empty string is an invalid filename" << endl;
305   } while (!good_read);
306
307   return;
308 }
309
