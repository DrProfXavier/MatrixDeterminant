#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
	int value, row, col;
	Node* next = NULL;
};


/*
 *    Utilities    *
 */

int length(Node* head)
{
	int i = 0;
	while (head != NULL) {
		head = head->next;
		i++;
	}

	return i;
}

void printElements(Node* head)
{
	while (head != NULL) {
		cout << head->value << " ";
		head = head->next;
	}
	cout << "\n";
}


Node* getSubMatrix(Node* head)
{
	bool childFound = false;

	//exRow & exCol == row and column to be excluded
	int exRow = head->row;
	int exCol = head->col;

	Node* child = new Node(); //Start from the next node, even if it's in the same row, it wont be allowed by logic
	Node* current = head;
	Node* temp = new Node();


	//MUST FIND FIRST MINOR HEAD
	while (current)//->next
	{
		int currRow = current->row;
		int currCol = current->col;

		if ((currRow != exRow) && (currCol != exCol))
		{
			current->row = currRow - 1;
			if (current->col > 0)
			{
				current->col -= 1;
			}

			if (!childFound) //First "safe" node in list
			{
				child = current;
				childFound = true;
			}
			
						
			//vvv For some reason, outputs desired list vvv
			//cout << "Current data: " << current->value << ": (" << current->row << "," << current->col << ")" << endl;
			//Outputs desired list, with unchanged index (Expected)

			//temp = new Node();
			//temp = current;	//Reduce row and col since they will be reduced as part of making minor
			//temp->row = temp->row - 1;
			//if (temp->col != 0)
			//{
			//	temp->col = temp->col - 1;
			//}	Rewrite to use change current data directly
			
			cout << "Current data: " << current->value << ": (" << current->row << "," << current->col << ")" << endl;

		}

		temp = current;
		current = current->next;
		temp->next = current;

		if (temp->next == NULL) //Avoid null pointer after tail
		{
			return child;
		}
		//current = current->next;	//Iterate
		//cout << "exRow: " <<exRow << "," << "exCol: " << exCol << endl;

	}
}

Node* getInputMatrix()
{
	Node* head = new Node();
	Node* current = head;
	Node* temp;

	string line;
	getline(cin, line);

	string token;

	int matrixLength;
	int rowNum = 0;
	int colNum = 0;
	int size = 0;
	int currSize = 0;

	int term;

	//get size
	stringstream lineStream(line);
	while (lineStream >> token)
	{
		if (size == 0)
		{
			head->value = stoi(token);
			head->row = 0;
			head->col = 0;
		}
		size++;
	}

	int lim;
	int rowCount = 0;
	//Gets ugly here
	do {
		stringstream lineStream2(line);
		lim = 0;

		while (lineStream2 >> token) {
			term = stoi(token);

			if ((rowCount != 0 || lim != 0) && term != 0) {			//To skip head
				temp = new Node();
				temp->value = term;			//b(term)
				temp->row = rowCount;
				temp->col = lim;

				/*Tester
				cout << "head info: " << head->value << "(" << head->row << "," << head->col << ") " << endl;
				cout << "temp value:" << temp->value << "\ntemp row:" << temp->row << "\ntemp col:" << temp->col << endl;
				*/
				current->next = temp;				//head/curr   ->  temp
				current = current->next;		    //head  -> temp/curr
			}

			matrixLength++;
			lim++;	//row length limit

		}

		rowCount++;
	} while (getline(cin, line));

	/* Print elements debug
	cout << "\n\t" << "Elements: ";
	printElements(head);
	cout << "Num rows: " << rowCount << endl;
	cout << "\n----\n";
	*/

	//Check dimensions
	if ((size * size) != matrixLength)
	{
		cout << "Error! Non-square matrix!";
		return NULL;
	}

	return head;
}

int main() {
	Node* head = getInputMatrix();
	Node* test = getSubMatrix(head);
	printElements(head);
	cout << "-----" << endl;
	printElements(test);
	if (head == NULL) {
		return 1;
	}

	//cout << determinant(head);

	return 0;
}