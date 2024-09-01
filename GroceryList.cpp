/*
2   *  File name: GroceryList.cpp
3   *  The "GroceryList" class represents a list of item and quantity for
4   *  ingredients that need to be purchased.
5   *
6   *  PRIVATE METHOD SPECIFICATION:
7   *
8   *     search:
9   *     Input:     takes a name
10  *                A GroceryPtr 'here'
11  *                a boolean 'found'
12  *
13  *                the grocery list is search for this name and if it is found,
14  *                the boolean, found, parameter is set to true and the pointer,
15  *                here, is set to point to the node containing the name;
16  *                otherwise if the name is not found, the found parameter is
17  *                set to false and here is set to point to the node with the
18  *                name that would follow the name being searched for,
19  *                i.e. the name’s alphabetic successor.
20  *
21  *                Details:
22  *                Since the list can be traversed in either direction, this
23  *                function will start searching from the head node for names
24  *                that start with the letters 'a' through 'm'; the search will
25  *                start from the tail node for names starting with the letters
26  *                'n' through 'z'.
27  *
28  *
29  *  PRIVATE DATA MEMBERS:
30  *
31  *      struct GroceryNode:
32  *
33  *                The GroceryNode field consists of:
34  *                *next: a pointer to a GroceryNode
35  *                *prev: a pointer to a GroceryNode
36  *                quantity: an integer that represents the amount of the item
37  *                name: a NAME type that represents the name of the item
38  *
39  *      typedef *GroceryPtr:
40  *               definitions for pointers to point to a GroceryNode
41  *
42  *      head and tail:
43  *                two Grocery Nodes that represents the beginning and end of the
44  *                list.
45  *                Some notes about head and tail:
46  *                they are not pointers to index nodes but actual index nodes.
47  *                they are not allocated dynamically, and therefore they must
48  *                never be deallocated back to the heap.
49  *
50 */
51 #include "GroceryList.h"
#include "globals.h"
53
54 GroceryList::GroceryList()
55 {
56     head.next = &tail;
57     tail.prev = &head;
58
59     head.prev = NULL;
60     tail.next = NULL;
61 }
62
63 GroceryList::~GroceryList()
64 {
65     GroceryPtr here;
66
67     while (head.next != &tail)
68     {
69         here = head.next;
70         head.next = head.next->next;
71         delete here;
72     }
73 }
74
75
76 bool GroceryList::contains(const NAME aName)
77 {
    bool found = false;
79      GroceryPtr here;
80
81      search(aName, here, found);
82
83      return found;
84  }
85
86  int GroceryList::getQuantity(const NAME aName) const
87  {
88      int qty = 0; // quantity
89      bool found = false;
90      GroceryPtr here;
91
92      search(aName, here, found);
93
94      if (found)
95          qty = here->quantity;
96
97      return qty;
98  }
99
100 void GroceryList::updateQuantity(const NAME aName, int quantity) const
101 {
102     bool found = false;
103     GroceryPtr here;

105     search(aName, here, found);
106
107     if (found)
108         here->quantity += quantity;
109
110     return;
111 }
112
113 void GroceryList::insertItem(const NAME aName, int quantity)
114 {
115     bool found = false;
116     GroceryPtr here, temp;
117
118     search(aName, here, found);
119
120     temp = new GroceryNode;
121     strncpy(temp->name, aName, MAX_ITEM_NAME_LEN);
122     temp->quantity = quantity;
123
124     here->prev->next = temp;
125     temp->prev = here->prev;
126     temp->next = here;
127     here->prev = temp;
128
129     return;
}
131
132 bool GroceryList::removeItem(const NAME aName) const
133 {
134     bool found = false;
135     GroceryPtr here;
136
137
138     search(aName, here, found);
139
140     if (found)
141     {
142         here->prev->next = here->next;
143         here->next->prev = here->prev;
144         delete here;
145     }
146
147     return found;
148 }
149
150 void GroceryList::write(ostream &out) const
151 {
152     bool found = false;
153     GroceryPtr here;
154
155     search(head.next->name, here, found);
    if (head.next == &tail)
157         out << "Empty grocery list\n";
158     else
159     {
160         while (here != &tail)
161         {
162             out << here->quantity << ' ' << here->name << endl;
163             here = here->next;
164         }
165     }
166 }
167
168 void GroceryList::search(const NAME aWord, GroceryPtr &here, bool &found) const
169 {
170     int diff; //difference
171
172     found = false;
173
174     if (aWord[0] < 'n')
175     {
176         here = head.next;
177         while (!found && here != &tail && here->name[0] < 'n' &&
178                strncmp(aWord, here->name, MAX_ITEM_NAME_LEN) >= 0 )
179         {
180             diff = strncmp(aWord, here->name, MAX_ITEM_NAME_LEN);
181             if (diff == 0)
                found = true;
183             else
184                 here = here->next;
185         }
186     }
187     else
188     {
189         here = tail.prev;
190         while (!found && here != &head && here->name[0] >= 'n' &&
191                strncmp(aWord, here->name, MAX_ITEM_NAME_LEN) <= 0 )
192         {
193             diff = strncmp(aWord, here->name, MAX_ITEM_NAME_LEN);
194             if (diff == 0)
195                 found = true;
196             else
197                 here = here->prev;
198         }
199
200         if (!found)
201             here = here->next;
202     }
203
204     return;
205 }
