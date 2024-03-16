#include<stdio.h>
#include"Header.h"
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define N 2
#define DEBUG

int is_correct_str(char* s_field, char* n_field) //ïðîâåðêà ââåä¸ííîãî ïîëÿ íà êîððåêòíîñòü
{
	for (int i = 0; i < strlen(s_field); i++)
	{
		if ((s_field[i] == '\n') && (i != 0)) s_field[i] = '\0';
		else if (!isalpha(s_field[i]) && s_field[i] != ' ')
		{
			printf("Error! Incorrect %s\n", n_field);
			return 1;
		}
	}
	return 0;
}

int choose_direction()//ôóíêöèÿ âûáîðà íàïðàâëåíèÿ ñîðòèðîâêè
{
	int d;
	printf("Enter '1' to sort ascending\nEnter '-1' to sort descending\n");
	scanf_s("%d", &d);
	if (d != 1 && d != -1)
	{
		printf("Error! Incorrect direction\n");
		return 0;
	}
	return d;
}

int compare_structs(players* a, players* b) //ôóíêöèÿ ïîñëåäîâàòåëüíî ñðàâíèâàåò ïîëÿ äâóõ ñòðóêòóð
{
	int f = strcmp(a->fio, b->fio);
	if (f!= 0) return f;
	int c = strcmp(a->club, b->club);
	if (c != 0) return c;
	int r = strcmp(a->role, b->role);
	if (r != 0) return r;
	int ag = a->age - b->age;
	if (ag != 0) return ag;
	int m = a->matches - b->matches;;
	if (m!= 0) return m;
	return a->goals - b->goals;
}

void print_arr(players* ptr, int n)//ïå÷àòü ìàññèâà
{
	for (int i = 0; i < n; i++)
		printf("%s %s %s %d %d %d\n", ptr[i].fio, ptr[i].club, ptr[i].role, ptr[i].age, ptr[i].matches, ptr[i].goals);
	return;
}

players* gen_array( int n)
{	
	players* fball_arr = (players*)malloc(n * sizeof(players));
	if (!fball_arr) return NULL;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		
		int p = rand() % N +1;
		for (int u = 0; u < p; u++) 
			fball_arr[i].fio[u] = rand() % 26 + 97;
		fball_arr[i].fio[p] = '\0';
		int t = rand() % N +1;
		for (int u = 0; u < t; u++)
			fball_arr[i].club[u] = rand() % 26 + 97;
		fball_arr[i].club[t] = '\0';
		char* s[] = { "midfielder", "goalkeeper", "defender", "striker" };
		strcpy_s(fball_arr[i].role, sizeof(fball_arr[i].role), s[rand() % 4 + 0]);
		fball_arr[i].role[strlen(fball_arr[i].role)] = '\0';
		fball_arr[i].age = rand() % 100;
		fball_arr[i].matches = rand() % 100;
		fball_arr[i].goals = rand() % 100;
	}
	return fball_arr;
}

players* fill_array(int n)
{
	players* fball_arr = (players*)malloc(n * sizeof(players));
	if (!fball_arr) return NULL;
	for (int i = 0; i < n; i++)
	{
		char* s[] = { "midfielder", "goalkeeper", "defender", "striker" };
		int ex = 0;
		rewind(stdin);
		printf("Enter the name:");
		fgets(fball_arr[i].fio, sizeof(fball_arr[i].fio), stdin);
		if (is_correct_str(fball_arr[i].fio, "name")) return NULL;
		printf("Enter the club:");
		fgets(fball_arr[i].club, sizeof(fball_arr[i].club), stdin);
		if (is_correct_str(fball_arr[i].club, "club")) return NULL;
		printf("Enter the role:");
		fgets(fball_arr[i].role, sizeof(fball_arr[i].role), stdin);
		fball_arr[i].role[strlen(fball_arr[i].role) - 1] = '\0';
		for (int l = 0; l < sizeof(s) / sizeof(s[0]); l++)
		{
			if (strncmp(s[l], fball_arr[i].role, strlen(s[l])) == 0) ex = 1;
		}
		if (ex == 0)
		{
			printf("Error! Incorrect role\n");
			
		}
		printf("Enter the age:");
		if (!scanf_s("%d", &fball_arr[i].age) || (fball_arr[i].age <= 0) || (fball_arr[i].age > 100))
		{
			printf("Error! Incorrect age\n");
			
		}
		printf("Enter the matches:");
		if (!scanf_s("%d", &fball_arr[i].matches) || (fball_arr[i].matches < 0) || (fball_arr[i].matches > 1000))
		{
			printf("Error! Incorrect amount of matches\n");
			
		}
		printf("Enter the goals:");
		if (!scanf_s("%d", &fball_arr[i].goals) || (fball_arr[i].goals < 0) || (fball_arr[i].goals > 1000))
		{
			printf("Error! Incorrect amount of goals\n");
			
		}
	
	}
	return fball_arr;
}
players* copyArray(players* a, int n)
{
	players* x = (players*)malloc(n * sizeof(players));
	if (!x) return NULL;
	memcpy(x, a, n * sizeof(players));
	return x;
}

void insert_sort(players* a, int size, int d)
{
	int i, j;
	players value;

		for (i = 1; i < size; i++)
		{
			value = a[i];
			for (j = i - 1; j >= 0 && compare_structs(&a[j], &value)*d>0; j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = value;
		}
}

void shaker_sort(players* a, int size, int d)//ïåðåäà¸òñÿ íàïðàâëåíèå ñîðòèðîâêè åù¸
{
  int j, k = size-1;
  int lb = 1, ub = size-1; 
  players x;

  do
  {
    for( j=ub; j>0; j-- )
    {
      if (compare_structs(&a[j-1], &a[j])*d > 0)
      {
        x=a[j-1]; 
		a[j-1]=a[j]; 
		a[j]=x;
        k=j;
      }
    }

    lb = k+1;
 
    for (j=1; j<=ub; j++)
    {
      if (compare_structs(&a[j-1], &a[j]) * d > 0)
      {
        x=a[j-1]; 
		a[j-1]=a[j]; 
		a[j]=x;
        k=j;
      }
    }

    ub = k-1;
  }
  while (lb < ub);
}

void merge(players* a, int low, int mid, int high, int d)
{
	players* b = (players*)malloc((high + 1 - low) * sizeof(players));
	if (b == NULL)return;
	int h, i, j, k;
	h = low;
	i = 0;
	j = mid + 1;
	while ((h <= mid) && (j <= high))
	{
		if (compare_structs(&a[h], &a[j])*d <=0)
		{
			b[i] = a[h];
			h++;
		}
		else
		{

			b[i] = a[j];
			j++;
		}
		i++;
	}
	if (h > mid)
	{
		for (k = j;k <= high;k++)
		{
			b[i] = a[k];
			i++;
		}
	}
	else
	{
		for (k = h;k <= mid;k++)
		{
			b[i] = a[k];
			i++;
		}
	}
	for (k = 0;k <= high - low;k++)
	{
		a[k + low] = b[k];
	}
	free(b);
}

void merge_sort(players* a, int low, int high, int d)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		merge_sort(a, low, mid, d);
		merge_sort(a, mid + 1, high, d);
		merge(a, low, mid, high, d);
	}
}

void checkSort(players* a, int size, int d, int s)
{
	char sort_str[10] = { 0 };
	clock_t t1, t2;
	switch (s)
	{
	case 1:
	{
		t1 = clock();
		insert_sort(a, size, d);
		t2 = clock();
		strcpy_s(sort_str, sizeof(sort_str), "Insert");
		break;
	}
	case 2: 
	{
		t1 = clock();
		shaker_sort(a, size, d);
		t2 = clock();
		strcpy_s(sort_str, sizeof(sort_str), "Shaker");
		break;
	}
	case 3: 
	{
		t1 = clock();
		merge_sort(a, 0, size-1, d);
		t2 = clock();
		strcpy_s(sort_str, sizeof(sort_str), "Merge");
		break;
	}
	}
	
	double sortTime = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printf("%s sort time for array of %li elements in seconds %.10lf\n", sort_str, size, sortTime);
}


int main()
{
	int size, sort_type, direction;
	printf("Enter the size: ");
	scanf_s("%d", &size);
	players* x = gen_array(size);
	if (!x || size==0)
	{
		printf("Error! An array coundn't be created");
		return 1;
	}
	if (!(direction = choose_direction())) return;

#ifdef DEBUG
	printf("Choose the sort algorithm:\n'1' - insertion sort\n'2' - shaker\n'3' - Merge sort\n");
	scanf_s("%d", &sort_type);
	if (sort_type != 1 && sort_type != 2 && sort_type != 3)
	{
		printf("Error! Incorrect type of sort");
		return;
	}
	//ìîæíî âûáîð íàïðàâëåíèÿ ñþäà ïåðåíåñòè
	checkSort(x, size, direction, sort_type);
	print_arr(x, size);
		
#else
	players* y = copyArray(x, size);
	players* z = copyArray(x, size);
	players* arrays[] = { x, y, z };

	for (int i = 0; i < sizeof(arrays)/sizeof(arrays[0]); i++)
	{
			checkSort(arrays[i], size, direction, i+1);
	}
	free(y);
	free(z);
#endif
	free(x);
	
	return 0;
}
