//#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <math.h>


using namespace std;

const double EPS = 1e-6;
const double ANG_EPS = 1e-5;
const double MUL = 1e2;

struct Point {
  double x;
  double y;
  Point(double xx = 0, double yy = 0) {
    x = xx;
    y = yy;
  }
  bool operator == (const Point& other) const {
    return abs(x - other.x) < EPS && abs(y - other.y) < EPS;
  }
};

int N;
vector<Point> pts;
Point aux, P;

bool isDifferent(double x, double y) {
  return abs(x - y) > EPS;
}

pair<bool, Point> isect(Point A, Point B, Point C, Point D) {
	double a1 = B.y - A.y; 
	double b1 = A.x - B.x; 
	double c1 = a1 * A.x + b1 * A.y; 

	double a2 = D.y - C.y; 
	double b2 = C.x - D.x; 
	double c2 = a2 * C.x + b2 * C.y; 

	double determinant = a1 * b2 - a2 * b1; 

	if (determinant == 0) { 
		return make_pair(false, Point(-1, -1)); 
	} else { 
		double x = (b2 * c1 - b1 * c2) / determinant; 
		double y = (a1 * c2 - a2 * c1) / determinant; 
    Point a(x, y);
		
    if ((a.x < min(A.x, B.x) && isDifferent(a.x, min(A.x, B.x)))
    || (a.x > max(A.x, B.x) && isDifferent(a.x, max(A.x, B.x))))
      return make_pair(false, Point(-1, -1));
    if ((a.x < min(C.x, D.x) && isDifferent(a.x, min(C.x, D.x)))
    || (a.x > max(C.x, D.x) && isDifferent(a.x, max(C.x, D.x))))
      return make_pair(false, Point(-1, -1));
    if ((a.y < min(A.y, B.y) && isDifferent(a.y, min(A.y, B.y)))
    || (a.y > max(A.y, B.y) && isDifferent(a.y, max(A.y, B.y))))
      return make_pair(false, Point(-1, -1));
    if ((a.y < min(C.y, D.y) && isDifferent(a.y, min(C.y, D.y)))
    || (a.y > max(C.y, D.y) && isDifferent(a.y, max(C.y, D.y))))
      return make_pair(false, Point(-1, -1));

    return make_pair(true, a);
	} 
}

Point farAway(Point A) {
  double difx = A.x - P.x;
  double dify = A.y - P.y;
  return Point(A.x + difx * MUL, A.y + dify * MUL);
}

double getDistSq(Point A, Point B) {
  return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

double getDistSqrt(Point A, Point B) {
  return sqrt(getDistSq(A, B));
}

pair<Point, bool> getIsect(Point B) {
  Point A = P;
  vector<pair<bool, Point> > stops;
  for (int i = 0; i < N; i++) {
    Point C = pts[i];
    Point D = pts[i + 1];

    auto [result, pt] = isect(A, B, C, D);

    if (result == false)
      continue;

    if (pt == pts[i] || pt == pts[i + 1])
      stops.push_back(make_pair(true, pt));
    else stops.push_back(make_pair(false, pt));
  }

  sort(stops.begin(), stops.end(), [](pair<bool, Point> a, pair<bool, Point> b) {
    return getDistSq(P, a.second) < getDistSq(P, b.second);
  });

  if (stops.empty())
    return {Point(0, 0), false};
  return {stops[0].second, true};
}

double delta(Point a, Point b, Point c) {
  return (a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x);
}

int main() {
  ifstream cin("snake.in");
  ofstream cout("tst.out");

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> aux.x >> aux.y;
    pts.push_back(aux);
  }
  pts.push_back(pts[0]);

  cin >> P.x >> P.y;

  vector<Point> stops;
  for (int i = 0; i < N; i++) {
    auto pt = pts[i];

    double rdx = pt.x - P.x;
    double rdy = pt.y - P.y;

    for (int j = 0; j < 3; j++) {
      double newRdx = rdx;
      double newRdy = rdy;

      if (j == 0) {
        if (abs(rdy) < EPS)
          newRdy += ANG_EPS;
        else newRdx += ANG_EPS;
      }
      if (j == 1) {
        if (abs(rdy) < EPS)
          newRdy -= ANG_EPS;
        else newRdx -= ANG_EPS;
      }

      Point far = farAway(Point(P.x + newRdx, P.y + newRdy));
      auto [stop, status] = getIsect(far);
      if (status == false)
        continue;
      stops.push_back(stop);
    }
  }

  sort(stops.begin(), stops.end(), [](Point a, Point b) {
    return delta(P, a, b) > 0;
  });

  // stops.resize(distance(stops.begin(), unique(stops.begin(), stops.end())));

  for (auto it : stops)
    cout << it.x << ' ' << it.y << '\n';

  return 0;
}