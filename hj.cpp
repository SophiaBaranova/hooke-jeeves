#include <stdio.h>
#include <math.h>
#define N 2 //number of point coordinates

typedef struct point
{
	double coord[N]; //point coordinates
} point;

typedef struct restr
{
	int is_restr[N]; //1 if coordinate value is restricted, 0 otherwise
	int cond[N]; //symbol of condition
	float val[N]; //border value
} restr;

double f(point b); //given function
point exploratory_search(point bas, double h, restr r); //exploratory search
point pattern_search(point b1, point b2, restr r); //pattern search
int is_valid(point b, restr r); //check if the point is valid according to given restrictions
void print(point b); //print point coordinates and function value at it

int main()
{
	point curr, bas, fix;
	double e, h, a = 2;
	int i, number_iter = 0, go = 0;
	restr r;
	//enter input data
	printf("basic point:\n");
	for (i = 0; i < N; i++)
	{
		printf("x%d -> ", i + 1);
		scanf_s("%lf", &bas.coord[i]);
	}
	printf("desired accuracy: ");
	scanf_s("%lf", &e);
	printf("initial step: ");
	scanf_s("%lf", &h);
	printf("'1' to add restrictions for point coordinates, '0' to continue -> ");
	scanf_s("%d", &go);
	if (go)
	{
		printf("1 - '<', 2 - '>', 3 - '<=', 4 - '>=', 5 - '!='\n");
		for (i = 0; i < N; i++)
		{
			printf("x%d -> ", i + 1);
			scanf_s("%d%f", &r.cond[i], &r.val[i]);
		}
	}
	//perform iterations
	do
	{
		number_iter++;
		printf("%dth iteration\n", number_iter);
		printf("basic point ( ");
		for (i = 0; i < N; i++)
		{
			printf("%.3lf ", bas.coord[i]);
		}
		printf(")\n");
		curr = exploratory_search(bas, h, r); //exploratory search from basic point
		//if the search was successful
		if (f(curr) < f(bas))
		{
			fix = curr; //remember the point
			//pattern search
			printf("pattern search\n");
			curr = pattern_search(bas, fix, r);
			while (f(curr) < f(fix))
			{
				bas = fix;
				fix = curr;
				curr = pattern_search(bas, fix, r);
			}
			//remember the new basic point
			bas = fix;
		}
		//if the search wasn't successful
		else
		{
			//reduce the step
			if (h > e)
			{
				h /= a;
			}
			//if the step is smaller than desired accuracy
			else
			{
				break;
			}
		}
	} while (h > e);
	//print results
	printf("f_min = ");
	print(bas);
	printf("number of iterations: %d\n", number_iter);
	return 0;
}

double f(point b)
{
	double f = pow(b.coord[0], 3) + 8 * pow(b.coord[1], 3) - 6 * b.coord[0] * b.coord[1] + 5;
	return f;
}

point exploratory_search(point bas, double h, restr r)
{
	point curr = bas, fix = bas;
	int i;
	printf("exploratory search\n");
	//iterate through point coordinates
	for (i = 0; i < N; i++)
	{
		//increase coordinate by h
		curr.coord[i] = bas.coord[i] + h;
		print(curr);
		//if the function decreased
		if (f(curr) < f(fix) && is_valid(curr, r))
		{
			fix = curr; //remember the point
		}
		//if the function didn't decrease
		else
		{
			//decrease coordinate by h
			curr.coord[i] = bas.coord[i] - h;
			print(curr);
			//if the function decreased
			if (f(curr) < f(fix) && is_valid(curr, r))
			{
				fix = curr; //remember the point
			}
			//if the function didn't decrease
			else
			{
				curr.coord[i] = bas.coord[i];
			}
		}
	}
	return fix; //improved point
}

point pattern_search(point b1, point b2, restr r)
{
	point p;
	int i;
	//pattern move
	for (i = 0; i < N; i++)
	{
		p.coord[i] = b1.coord[i] + 2 * (b2.coord[i] - b1.coord[i]);
	}
	print(p);
	if (is_valid(p, r))
	{
		return p;
	}
	return b2;
}

int is_valid(point b, restr r)
{
	int i;
	for (i = 0; i < N; i++)
	{
		switch (r.cond[i])
		{
		case 1:
			if (b.coord[i] < r.val[i])
			{
				break;
			}
			return 0;
		case 2:
			if (b.coord[i] > r.val[i])
			{
				break;
			}
			return 0;
		case 3:
			if (b.coord[i] <= r.val[i])
			{
				break;
			}
			return 0;
		case 4:
			if (b.coord[i] >= r.val[i])
			{
				break;
			}
			return 0;
		case 5:
			if (b.coord[i] != r.val[i])
			{
				break;
			}
			return 0;
		}
	}
	return 1;
}

void print(point b)
{
	int i;
	printf("f( ");
	for (i = 0; i < N; i++)
	{
		printf("%.3lf ", b.coord[i]);
	}
	printf(") = %lf\n", f(b));
}
