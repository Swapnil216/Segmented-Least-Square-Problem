#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define infi numeric_limits<double>::infinity()

//Declaring the variables used throught the code
int num_pts;                                                        //Number of co-ordinate points
vector<pair<int,int> > coord;                                       //Coordinates in the form (x,y)
vector<long long> cum_sum_x, cum_sum_y, cum_sum_xy, cum_sum_xx;     //The vector stores cumulative sums
vector<vector<double> > slope;                                      //slope[i][j] stores slope of best-fit line from ith to jth points
vector<vector<double> > error;                                      //error[i][j] stores squared-error of best-fit line from ith to jth points
vector<vector<double> > interc;                                     //interc[i][j] stores y-intercept of best-fit line from ith to jth points
int cost;                                                           //Cost of making a new line segment
vector<int> opt_seg;                                                //Stores the last segment which is part of the optimal solution
vector<double> ans;                                                 //Minimum cost till ith point

/**
*This is a custom sort function to sort the pair of
*vectors in the ascending order of the first element
*/
bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first < b.first;
}

/**
*This function calculates the range of points which
*are covered in one optimal line segment.
**It then prints the co-ordinate equation of the line segments.
*/
void print_ans()
{
    cout << "Cost involved: " << ans[num_pts] << "\n";

    stack<int> s;
    for (int i = num_pts, j = opt_seg[num_pts]; i > 0; i = j - 1, j = opt_seg[i])
    {
        s.push(i);
        s.push(j);
    }

    cout << "\nOptimal solution :\n";
    while (!s.empty())
    {
        int a = s.top();
        s.pop();
        int b = s.top();
        s.pop();
        cout << "The segment is: y = " << slope[a][b] << " * x + " << interc[a][b] << "\n";
        cout << "Covers point numbers: " << a << " to " << b << ", having square of the error as: " << error[a][b] << endl << endl;
    }
}

/**
*This function calculates the optimal number of line segments in
*accordance with the cost of creating a new segment
*/
void calc_opt()
{
    //Cost of creating a new segment
    cout << "Cost of creating a new segment: ";
    cin >> cost;

    //gives opt_seg gives us the last segment in the optimal solution
    opt_seg.resize(num_pts + 1, 0);

    //Optimal solution
    ans.resize(num_pts + 1, 0);

    int i = 0, j = 0, k = 0;
    for (i = 1; i <= num_pts; i++)
    {
        double temp = infi;
        for (j = 1, k = 0; i >= j; j++)
        {
            double tp = error[j][i] + ans[j - 1];
            if (tp < temp)
            {
                temp = tp;
                k = j;
            }
        }
        ans[i] = temp + cost;
        opt_seg[i] = k;
    }
    print_ans();
}

/**
*This function makes and prepares the matrices to
*calculate the slopes of best-fit line segment,
*the intercept and the respective error associated
*/
void prepare()
{
    cum_sum_x.resize(num_pts + 1, 0);
    cum_sum_y.resize(num_pts + 1, 0);
    cum_sum_xy.resize(num_pts + 1, 0);
    cum_sum_xx.resize(num_pts + 1, 0);

    slope.resize(num_pts + 1);
    for (int i = 0; i < num_pts + 1; i++)
    {
        slope[i].resize(num_pts + 1, 0);
    }
    error.resize(num_pts + 1);
    for (int i = 0; i < num_pts + 1; i++)
    {
        error[i].resize(num_pts + 1, 0);
    }
    interc.resize(num_pts + 1);
    for (int i = 0; i < num_pts + 1; i++)
    {
        interc[i].resize(num_pts + 1, 0);
    }

    for (int j = 1; j <= num_pts; j++)
    {
        cum_sum_x[j] = cum_sum_x[j - 1] + coord[j].first;
        cum_sum_y[j] = cum_sum_y[j - 1] + coord[j].second;
        cum_sum_xy[j] = cum_sum_xy[j - 1] + coord[j].first * coord[j].second;
        cum_sum_xx[j] = cum_sum_xx[j - 1] + coord[j].first * coord[j].first;

        for (int i = 1; i <= j; i++)
        {
            int gap = j - i + 1;
            long long sum_x = cum_sum_x[j] - cum_sum_x[i - 1];
            long long sum_y = cum_sum_y[j] - cum_sum_y[i - 1];
            long long sum_xy = cum_sum_xy[j] - cum_sum_xy[i - 1];
            long long sum_xx = cum_sum_xx[j] - cum_sum_xx[i - 1];

            long long numerator = gap * sum_xy - sum_x * sum_y;
            long long denominator = gap * sum_xx - sum_x * sum_x;
            if (numerator == 0)
                slope[i][j] = 0;
            else
            {
                if (denominator == 0)
                    slope[i][j] = infi;
                else
                    slope[i][j] = numerator / (double(denominator));
            }
            interc[i][j] = (sum_y - (sum_x * slope[i][j])) / double(gap);

            for (int k = i; j >= k; k++)
            {
                double tmp = coord[k].second - slope[i][j] * coord[k].first - interc[i][j];
                error[i][j] += tmp * tmp;
            }
        }
    }
    calc_opt();
}

/**
*Getting the input in the format:
*Number of Co-ordinates
*Followed by entering the co-ordinates in the format (x,y)
*
*This function also sorts the input in the order of ascending x- co-ordinates
*/
void input()
{
    cout << "Enter number of coordinates: ";
    cin >> num_pts;
    pair<int, int> p;
    p = make_pair(0, 0);
    coord.push_back(p);

    //To take the points from 1 to total
    cout << "Enter the co-ordinates\n";
    for (int i = 1; i <= num_pts; i++)
    {
        int a, b;
        cin >> a >> b;
        pair<int, int> q;
        q = make_pair(a, b);
        coord.push_back(q);
    }
    sort(coord.begin() + 1 , coord.end(), cmp);
    prepare();
}

/**
*This is the driver function of the program
*/
int main()
{
    auto start = std::chrono::steady_clock::now(); 
    input ();
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start; cout << "Execution Time: " << std::chrono::duration <double, milli> (diff).count() << "ms" << endl;
    
    return 0;
}
