#include<bits/stdc++.h>
using namespace std;

set< pair<double, double> > result_convex;
double line_dist_calc(pair<double, double> p1, pair<double, double> p2, pair<double, double> p);
int SideCheck(pair<double, double> p1, pair<double, double> p2, pair<double, double> p);


double area;


set < pair <double, double> > :: iterator it;
void quick_hull_convex(set < pair <double, double> > S, pair< double, double> p1, pair< double, double> p2)
{
    if(S.empty())
    {
        result_convex.insert(p1);
        result_convex.insert(p2);
        return;
    }

    set< pair<double, double> > S1;
    set< pair<double, double> >S2;

    double max_dist=0.0;
    pair<double, double> temp=p1;
    for(it=S.begin(); it!=S.end(); it++)
    {
        double line_dist=line_dist_calc(p1, p2, *it);
        if(max_dist<line_dist)
        {
            max_dist=line_dist;
            temp = *it;
        }
    }

    area=area+max_dist;
    int side_check=SideCheck(p1, temp, p2);

    for(it=S.begin(); it!=S.end(); it++)
    {
        int side_temp1=SideCheck(p1, temp, *it);
        if(side_temp1==-side_check)
        {
            S1.insert(*it);
        }
    }


    quick_hull_convex(S1, p1, temp);


    int side_check2=SideCheck(p2, temp, p1);

    for(it=S.begin(); it!=S.end(); it++)
    {
        int side_temp1=SideCheck(p2, temp, *it);
        if(side_temp1==-side_check2)
        {
            S2.insert(*it);
        }
    }
    quick_hull_convex(S2, p2, temp);


}
double line_dist_calc(pair<double, double> p1, pair<double, double> p2, pair<double, double> p)
{
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}

int SideCheck(pair<double, double> p1, pair<double, double> p2, pair<double, double> p)
{
    double value = (p.second - p1.second) * (p2.first - p1.first) -
              (p2.second - p1.second) * (p.first - p1.first);

    if (value > 0)
        return 1;
    if (value < 0)
        return -1;
    return 0;
}

int main()
{
    ifstream myfile;
    int n;
    double x, y;
    vector< pair<double, double> > points;
    set< pair<double, double> > S1;
    set< pair<double, double> > S2;
    myfile.open("1405117_input4.txt");
    if(!myfile)
    {
        cout<<"Unable to open the file"<<endl;
        exit(1);
    }

    myfile>>n;


   // pair<double, double> points[]={{0, 0}, {0, 4}, {4, 0}, {4, 4},
              // {2, 2}};

    for(int i=0; i<n; i++)
    {
        myfile>>x>>y;
        points.push_back(make_pair(x, y));
    }

    //cout<<n;
    int x_maximum=0, x_minimum=0;

    if(n<3)
    {
        cout<<"Convex Hull can not be formed";
        return 0;
    }

    for(int i=1; i<n; i++)
    {
        if(points[x_minimum].first>points[i].first)
        {
            x_minimum=i;
        }
        if(points[x_maximum].first<points[i].first)
        {
            x_maximum=i;
        }
    }

    result_convex.insert(points[x_minimum]);
    result_convex.insert(points[x_maximum]);



    //quick_hull_convex(points, points[x_minimum], points[x_maximum]);
    //quick_hull_convex(points, points[x_minimum], points[x_maximum]);

    for(int i=0; i<n; i++)
    {
        int side_check = SideCheck(points[x_minimum], points[x_maximum], points[i]);
        if(side_check==1)
        {
            S1.insert(points[i]);
        }
        else if(side_check==-1)
        {
            S2.insert(points[i]);
        }
    }

    quick_hull_convex(S1, points[x_minimum], points[x_maximum]);
    quick_hull_convex(S2, points[x_minimum], points[x_maximum]);


    cout << "The points in Convex Hull are:\n";
    //cout<<result_convex.size();
    while (!result_convex.empty())
    {
        cout << "(" <<( *result_convex.begin()).first << ", "
             << (*result_convex.begin()).second << ") ";
        result_convex.erase(result_convex.begin());
    }

    cout<<endl<<"Area: "<<(area/2)<<endl;


}


