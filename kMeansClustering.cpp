#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
#include <utility>
#include <climits>
#include <map>

using namespace std;

int min(vector<float> vec)
{
    float minimum = vec[0];
    int index = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (minimum > vec[i])
        {
            minimum = vec[i];
            index = i;
        }
    }
    return index;
}

float distance(pair<float, float> p1, pair<float, float> p2)
{
    float x1 = p1.first;
    float y1 = p1.second;
    float x2 = p2.first;
    float y2 = p2.second;
    float dis = pow((pow((x1 - x2), 2) + pow((y1 - y2), 2)), 0.5);
    return dis;
}

pair<float, float> coOrdinates(vector<pair<float, float>> subKCluster)
{
    float iq = 0;
    float eq = 0;
    for (int i = 0; i < subKCluster.size(); i++)
    {
        iq = iq + subKCluster[i].first;
        eq = eq + subKCluster[i].second;
    }
    iq = iq / subKCluster.size();
    eq = eq / subKCluster.size();

    pair<float, float> p;
    p = make_pair(iq, eq);
    return p;
}

vector<pair<pair<float, float>, vector<pair<float, float>>>> kMeansClustering(int k, vector<pair<float, float>> vec)
{
    vector<pair<pair<float, float>, vector<pair<float, float>>>> kCluster(k);

    for (int i = 0; i < k; i++)
    {
        ((kCluster[i]).second).push_back(vec[i]);
        pair<float, float> p = coOrdinates((kCluster[i]).second);
        (kCluster[i]).first = p;
        ((kCluster[i]).second).pop_back();
    }
label:
    for (int i = 0; i < vec.size(); i++)
    {

        vector<float> vec1(k);
        for (int j = 0; j < k; j++)
        {
            float dis = distance((kCluster[j]).first, vec[i]);
            vec1[j] = dis;
        }
        int index = min(vec1);
        ((kCluster[index]).second).push_back(vec[i]);
    }
    int h = 0;
    for (int i = 0; i < k; i++)
    {
        pair<float, float> p = coOrdinates((kCluster[i]).second);
        pair<float, float> p1 = (kCluster[i]).first;
        if (p.first == p1.first && p.second == p1.second)
        {
            h++;
        }
    }
    if (h != k)
    {
        for (int g = 0; g < k; g++)
        {
            pair<float, float> p = coOrdinates((kCluster[g]).second);
            (kCluster[g]).first = p;
            kCluster[g].second.clear();
        }
        goto label;
    }
    // else
    // {
    //     for (int g = 0; g < k; g++)
    //     {
    //         pair<float, float> p = coOrdinates((kCluster[g]).second);
    //         (kCluster[g]).first = p;
    //     }
    // }
    return kCluster;
}

float overallSumOfDistace(vector<pair<pair<float, float>, vector<pair<float, float>>>> finalKMeansCluster)
{
    float result = 0;
    int k = finalKMeansCluster.size();
    for (int i = 0; i < k; i++)
    {
        float x1 = finalKMeansCluster[i].first.first;
        float y1 = finalKMeansCluster[i].first.second;
        int a = finalKMeansCluster[i].second.size();
        for (int j = 0; j < a; j++)
        {
            float x2 = finalKMeansCluster[i].second[j].first;
            float y2 = finalKMeansCluster[i].second[j].second;
            result = result + distance(make_pair(x1, y1), make_pair(x2, y2));
        }
    }
    return result;
}

int main()
{
    vector<pair<float, float>> vec(20);
    vec[0] = make_pair(20, 22);
    vec[1] = make_pair(23, 12);
    vec[2] = make_pair(8, 5);
    vec[3] = make_pair(3, 3);
    vec[4] = make_pair(6, 25);
    vec[5] = make_pair(24, 4);
    vec[6] = make_pair(23, 14);
    vec[7] = make_pair(45, 5);
    vec[8] = make_pair(6, 7);
    vec[9] = make_pair(2, 2);
    vec[10] = make_pair(9, 10);
    vec[11] = make_pair(11, 10);
    vec[12] = make_pair(16, 16);
    vec[13] = make_pair(5, 23);
    vec[14] = make_pair(23, 2);
    vec[15] = make_pair(22, 2);
    vec[16] = make_pair(56, 7);
    vec[17] = make_pair(9, 2);
    vec[18] = make_pair(8, 2);
    vec[19] = make_pair(5, 48);

    int k;
    ofstream myfile;
    myfile.open("example1.txt");
    for (k = 1; k < 10; k++)
    {
        vector<pair<pair<float, float>, vector<pair<float, float>>>> finalKMeansCluster = kMeansClustering(k, vec);
        for (int i = 0; i < k; i++)
        {
            cout << ((finalKMeansCluster[i]).first).first << " " << ((finalKMeansCluster[i]).first).second;
            cout << endl;
            printf("This is the %dth cluster and below are its vector-pair-->\n", i + 1);
            for (int j = 0; j < (finalKMeansCluster[i]).second.size(); j++)
            {
                cout << ((finalKMeansCluster[i]).second)[j].first << " " << ((finalKMeansCluster[i]).second)[j].second << endl;
            }
            cout << endl;
        }
        float dis = overallSumOfDistace(finalKMeansCluster);
        cout << "The total distance that is the sum of each cluster with their corresponding data is: " << dis << endl;
        myfile << dis << endl;
    }

    myfile.close();

    return 0;
}