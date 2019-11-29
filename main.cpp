#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-6;
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
		
        if (a.x < min(A.x, B.x) || a.x > max(A.x, B.x))
            return make_pair(false, Point(-1, -1));
        if (a.x < min(C.x, D.x) || a.x > max(C.x, D.x))
            return make_pair(false, Point(-1, -1));
        if (a.y < min(A.y, B.y) || a.y > max(A.y, B.y))
            return make_pair(false, Point(-1, -1));
        if (a.y < min(C.y, D.y) || a.y > max(C.y, D.y))
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

Point getIsect(Point B) {
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

    // cout << B.x << ' ' << B.y << '\n';
    // cout << "Points\n";
    // for (auto it : stops) {
    //     cout << it.second.x << ' ' << it.second.y << "  ";
    // }
    // cout << "\n\n";

    Point ans;
    for (auto stop : stops) {
        if (stop.first == false)
            return stop.second;
        ans = stop.second;
    }

    return ans;
}

double delta(Point a, Point b, Point c) {
    return (a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x);
}

int main() {
    ifstream cin("tst.in");
    ofstream cout("tst.out");
    
    // auto it = isect({0, 0}, {1, 1}, {1, 0}, {0, 1});
    // cout << it.first << endl;
    // cout << it.second.x << ' ' << it.second.y << endl;
    // return 0;


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
        Point far = farAway(pt);
        // cout << far.x << ' ' << far.y << '\n';

        Point stop = getIsect(far);
        stops.push_back(stop);
    }

    sort(stops.begin(), stops.end(), [](Point a, Point b) {
        return delta(P, a, b) > 0;
    });

    // for (auto it : stops) {
    //     cout << it.x << ' ' << it.y << '\n';
    // }

    vector<Point> finalPolygon;
    for (int i = 0; i < N; i++) {
        vector<Point> newPts; 
        Point A = pts[i];
        Point B = pts[i + 1];
        for (auto it : stops) {
            if (abs(getDistSqrt(A, it) + getDistSqrt(B, it) - getDistSqrt(A, B)) < EPS) {
                newPts.push_back(it);
            }
        }

        sort(newPts.begin(), newPts.end(), [&](Point a, Point b) {
            return getDistSqrt(A, a) < getDistSqrt(A, b);
        });

        finalPolygon.push_back(A);
        for (auto it : newPts)
            finalPolygon.push_back(it);
        
    }

    // for (auto it : finalPolygon) {
    //     cout << it.x << ' ' << it.y << '\n';
    // }

    vector<Point> visiblePolygon;
    for (auto it : finalPolygon) {
        auto pt = it;
        Point far = farAway(pt);
        // cout << far.x << ' ' << far.y << '\n';

        Point stop = getIsect(far);
        if (getDistSqrt(P, it) < getDistSqrt(P, stop) || abs(getDistSqrt(P, it) - getDistSqrt(P, stop)) < EPS) 
            visiblePolygon.push_back(it);
    }
    
    for (auto it : visiblePolygon) {
        cout << it.x << ' ' << it.y << '\n';
    }

    return 0;
}