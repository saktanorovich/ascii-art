#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

#define debug

#ifdef debug

const string infile = "ascii.in";
const string outfile = "ascii.out";

#endif

const int max_n = 100;
const int max_h = 100;
const int max_w = 100;
const double eps = 1e-11;

int x[max_n + 1], y[max_n + 1];
double f[max_w + 1][max_h + 1];
int n, w, h;

int sign(int x)
{
	if (x > 0)
		return +1;
	else if (x < 0)
		return -1;
	return 0;
}

void addSquare(int xmin, int ymin, int xmax, int ymax, int s)
{
	double dy = ymax - ymin;
	double dx = xmax - xmin;
	double k = dy / dx;
	double b = ymin - k * xmin;
	for (int x = xmin; x <= xmax - 1; ++x)
	{
		double xup = x;
		double xdown = x + 1;
		if (sign(dy) / sign(dx) > 0)
		{
			double temp = xup;
			xup = xdown;
			xdown = temp;
		}
		double yup = k * xup + b;
		double ydown = k * xdown + b;

		int down = -1;
		while (down + 1 <= k * xdown + b)
		{
			if (down >= 0)
			{
				f[x][down] = f[x][down] + s;
			}
			down++;
		}
		int up = -1;
		while (up + 1 < k * xup + b)
		{
			up++;
		}
		if (down == up)
		{
			if (down >= 0)
			{
				f[x][down] = f[x][down] + s * (ydown - down + yup - up) / 2;
			}
		}
		else if (down < up)
		{
			double xx = (down + 1 - b) / k;
			if (down >= 0)
			{
				f[x][down] = f[x][down] + s * (1 - (down + 1 - ydown) * abs(xdown - xx) / 2);
			}
			xx = (up - b) / k;
			if (up >= 0)
			{
				f[x][up] = f[x][up] + s * abs(xup - xx) * abs(yup - up) / 2;
			}
			for (int y = down + 1; y <= up - 1; ++y)
			{
				double xxd = (y - b) / k;
				double xxu = (y + 1 - b) / k;
				f[x][y] = f[x][y] + s * abs(xup - xxd + xup - xxu) / 2;
			}
		}
	}
}


void print(int x, int y)
{
	if (f[x][y] < (double)1 / 4 - eps)
		cout << (char)46;
	else if (f[x][y] < (double)1 / 2 - eps)
		cout << (char)43;
	else if (f[x][y] < (double)3 / 4 - eps)
		cout << (char)111;
	else if (f[x][y] < (double)1 - eps)
		cout << (char)36;
	else
		cout << (char)35;
}

int main()
{
#ifdef debug

	freopen(infile.c_str(), "rt", stdin);
	freopen(outfile.c_str(), "wt", stdout);

#endif

	int t = 0;
	while (cin >> n >> w >> h)
	{
		if (t > 0)
		{
			cout << endl;
		}
		t++;

		for (int i = 0; i < n; ++i)
		{
			cin >> x[i] >> y[i];
		}

		memset(f, 0, sizeof(f));
		for (int i = 0; i < n; ++i)
		{
			if (x[i] != x[(i + 1) % n])
			{
				if (x[i] < x[(i + 1) % n])
					addSquare(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], +1);
				else
					addSquare(x[(i + 1) % n], y[(i + 1) % n], x[i], y[i], -1);
			}
		}

		for (int yy = h - 1; yy >= 0; --yy)
		{
			for (int xx = 0; xx <= w - 1; ++xx)
			{
				print(xx, yy);
			}
			cout << endl;
		}
	}
	return 0;
}
