/*
	Assigned by:
	Niv Schendel #322698184
	NULL #0
*/

#define _CRT_SECURE_NO_WARNINGS

/* Libraries */

#include <stdio.h>
#include <malloc.h>

/* Constant definitions */

#define N 3
#define ROWS 4
#define COLS 5

/* Type definitions */

typedef struct number
{
	unsigned long long num;
	int sum;
} Number;

typedef struct triad
{
	int i, j, value;
} Triad;

typedef struct item
{
	Triad data;
	struct item* next;
} Item;

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

Number* primeSums(unsigned long long n1, unsigned long long n2, int* p_size);
int** matrixMaxNeighbor(int A[][COLS], int rows, int cols);
void createThreeLists(int** A, int rows, int cols, Item** pL1, Item** pL2);

/* Declarations of auxiliary functions */

int isPrime(int num);
int digitSum(unsigned long long num);

int neighborMax(int A[][COLS], int rows, int cols, int i, int j);
int** allocMatrix(int rows, int cols);

Triad createThree(int i, int j, int value);
void insertItem(Item** head, Triad t);

void printArray(Number* arr, int size);
void inputMatrix(int A[][COLS], int rows, int cols);
void printMatrix(int A[][COLS], int rows, int cols);
void printDynamicMatrix(int** A, int rows, int cols);
void freeMatrix(void** A, int rows);
void inputDynamicMatrix(int** A, int rows, int cols);
void printList(Item* lst);
void freeList(Item* lst);

/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= N; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-%d : ", N);
				scanf("%d", &select);
			} while ((select < 0) || (select > N));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			}
		} while (all_Ex_in_loop && select);
	return 0;
}


/* Function definitions */

// Ex1: Read two numbers and print all primes in [n1,n2] with their digit?sums
void Ex1()
{
	/* Called functions:
		primeSums, printArray */
	unsigned long long n1, n2;
	int size;
	Number* res;

	printf("Enter n1 and n2: ");
	if (scanf("%llu %llu", &n1, &n2) != 2 || n1 > n2)
	{
		printf("Invalid input.\n");
		return;
	}

	// compute primes and sums
	res = primeSums(n1, n2, &size);

	if (!size)
	{
		printf("No primes found.\n");
	}
	else
	{
		printf("Primes and digit sums:\n");
		printArray(res, size);
		free(res);
		res = NULL;
	}
}

// Ex2: Read a 4×5 matrix, build & print its max-neighbor matrix
void Ex2()
{
	/* Called functions:
		inputMatrix, printMatrix, matrixMaxNeighbor, printDynamicMatrix, freeMatrix */

	int A[ROWS][COLS];
	int** B;

	// read input
	inputMatrix(A, ROWS, COLS);

	// show original
	printf("Original matrix:\n");
	printMatrix(A, ROWS, COLS);

	// neighbors
	B = matrixMaxNeighbor(A, ROWS, COLS);

	// show result
	printf("Max-neighbor matrix:\n");
	printDynamicMatrix(B, ROWS, COLS);

	// FREE
	freeMatrix((void**)B, ROWS);
	B = NULL;
}

// Ex3: Read dynamic matrix, build two triad-lists and print them
void Ex3()
{
	/* Called functions:
		allocMatrix, inputDynamicMatrix, printDynamicMatrix, createThreeLists, printList, freeMatrix, freeList */
	int** A;
	Item* L1, * L2;

	// alloc dynamic matrix
	A = allocMatrix(ROWS, COLS);

	// read values
	inputDynamicMatrix(A, ROWS, COLS);

	// show matrix
	printf("Dynamic matrix:\n");
	printDynamicMatrix(A, ROWS, COLS);

	// build lists
	createThreeLists(A, ROWS, COLS, &L1, &L2);

	// show listS
	printf("List1 (v == i+j):\n");
	printList(L1);

	printf("List2 (arithmetic seq):\n");
	printList(L2);

	// free resources
	freeMatrix((void**)A, ROWS);
	A = NULL;

	freeList(L1);
	L1 = NULL;
	
	freeList(L2);
	L2 = NULL;

}

// primeSums: return array of primes in [n1,n2] and fill *p_size

Number* primeSums(unsigned long long n1, unsigned long long n2, int* p_size)
{
	/* Called functions:
		isPrime, digitSum */

	Number* tmp;
	Number* arr;
	int capacity, count;
	unsigned long long num;

	arr = NULL;
	tmp = NULL;
	capacity = 0;
	count = 0;

	for (num = n1; num <= n2; num++)
	{
		if (isPrime((int)num))
		{
			if (count == capacity)
			{
				capacity = (!capacity) ? 1 : capacity*2;
				tmp = (Number*)realloc(arr, capacity * sizeof(Number));

				if (!tmp)// alloc failed
				{
					free(arr);
					*p_size = count;
					return NULL;
				}
				arr = tmp;
			}
			arr[count].num = num;
			arr[count].sum = digitSum(num);
			count++;
		}
	}

	if (!count)
	{
		free(arr);
		arr = NULL;
	}

	*p_size = count;
	return arr;
}

// matrixMaxNeighbor: allocate and return B[i][j]=max neighbor of A[i][j]
int** matrixMaxNeighbor(int A[][COLS], int rows, int cols)
{
	/* Called functions:
		neighborMax, allocMatrix */

	int i, j;
	int** B;

	B = allocMatrix(rows, cols);
	
	if (!B)
		return NULL;

	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			B[i][j] = neighborMax(A, rows, cols, i, j);
	return B;

}

// createThreeLists: scan A and prepend (i,j,v) into two lists by two rules
void createThreeLists(int** A, int rows, int cols, Item** pL1, Item** pL2)
{
	/* Called functions:
		createThree, insert */

	int i, j, v;

	*pL1 = NULL;
	*pL2 = NULL;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			v = A[i][j];

			if (v == i + j)             // A: value == i+j 
				insertItem(pL1, createThree(i, j, v));

			if ((j - i) == (v - j))     // B: (i,j,v) 
				insertItem(pL2, createThree(i, j, v));
		}
	}
}

/* Definitions of auxiliary functions */

/*Q1*/

// isPrime: return 1 if num>1 and has no divisors up to sqrt(num)
int isPrime(int num) 

{
	int i;

	if (num < 2) 
		return 0;

	for (i = 2; i * i <= num; i++) 
	{
		if (!(num % i)) 
			return 0;
	}
	return 1;
}

// digitSum: return sum of all digits of num
int digitSum(unsigned long long num)

{
	int sum = 0;

	while (num > 0)
	{
		sum += num%10;
		num /= 10;
	}

	return sum;
}

void printArray(Number* arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%llu: %d\n", arr[i].num, arr[i].sum);
}

/*Q2 & Q3*/

// allocMatrix: allocate rows×cols dynamic int matrix (or return NULL)
int** allocMatrix(int rows, int cols)
{
	int i;
	int** M;

	M = malloc(rows * sizeof(int*));
	if (!M)
		return NULL;

	for (i = 0; i < rows; i++)
	{
		M[i] = malloc(cols * sizeof(int));
		if (!M[i])
		{
			// free any prior rows on fail
			while (--i >= 0)
				free(M[i]);
			free(M);
			return NULL;
		}
	}

	return M;
}

/*Q2*/

// inputMatrix: prompt and read rows×cols ints into static A
void inputMatrix(int A[][COLS], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
		{
			printf("A[%d][%d] = ", i, j);
			scanf("%d", &A[i][j]);
		}
}

// printArray: print each prime and its digit?sum from arr[0..size-1]
void printMatrix(int A[][COLS], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			printf("%4d", A[i][j]);
		printf("\n");
	}
}

/*Q2*/

// neighborMax: return max of A[i][j] and its up/down/left/right
int neighborMax(int A[][COLS], int rows, int cols, int i, int j)
{
	int max, up, down, left, right;

	max = A[i][j];
	up = (i > 0) ? A[i - 1][j] : max;
	down = (i < rows - 1) ? A[i + 1][j] : max;
	left = (j > 0) ? A[i][j - 1] : max;
	right = (j < cols - 1) ? A[i][j + 1] : max;

	if (up > max) max = up;
	if (down > max) max = down;
	if (left > max) max = left;
	if (right > max) max = right;

	return max;
}

/*Q2 & Q3*/

// printDynamicMatrix: pretty?print dynamic matrix A rows×cols
void printDynamicMatrix(int** A, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++) 
			printf("%4d", A[i][j]);
		printf("\n");
	}
}

// freeMatrix: free dynamic matrix rows×cols
void freeMatrix(void** A, int rows)
{
	int i;
	for (i = 0; i < rows; i++)
		free(A[i]);
	free(A);
}

/*Q3*/

// createThree: build a Triad struct from (i,j,value)
Triad createThree(int i, int j, int value)
{
	Triad t;
	t.i = i;
	t.j = j;
	t.value = value;
	return t;
}

// insertItem: prepend a new node with triad t onto *head
void insertItem(Item** head, Triad t)
{
	Item* node = malloc(sizeof(Item)); // alloc new node
	if (!node)
		return;

	node->data = t;     // set triad
	node->next = *head; // link to old head
	*head = node;       // update head
}

// inputDynamicMatrix: prompt and read rows×cols ints into dynamic A
void inputDynamicMatrix(int** A, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
		{
			printf("A[%d][%d] = ", i, j);
			scanf("%d", &A[i][j]);
		}
}

// printList: print each node’s (i,j)=value in linked list -> NULL
void printList(Item* head)
{
	Item* cur = head;
	while (cur)
	{
		printf("(%d,%d)=%d -> ",
			cur->data.i,
			cur->data.j,
			cur->data.value);
		cur = cur->next;
	}
	printf("NULL\n");
}

// freeList: free all nodes in linked list
void freeList(Item* head)
{
	Item* cur = head;
	Item* tmp;
	while (cur)
	{
		tmp = cur->next;   // save next
		free(cur);
		cur = tmp;
	}
}

/* ------------------- */
