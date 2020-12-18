//
// Created by nikita on 16.12.2020.
//
#pragma once
#include <iostream>
#include <fstream>
#include<vector>
#include <cmath>
#include <utility>
using namespace std;
template <typename T>
class Figure {
protected:
    using vertex_t = pair<T,T>;
    vector<vertex_t> points;
public:
    virtual void Write(ostream &os) = 0;
    virtual void Write(ofstream &of) = 0;
    virtual ~Figure() {}
};

template<class T1, class T2>
std::ostream & operator << (std::ostream & out, const pair<T1, T2> & p) {
    out << p.first << " " << p.second << " ";
    return out;
}

//Подсчёт расстояния между точками
template <typename T>
double distance (std::pair<T, T> first, std::pair<T, T> second){
    double res = sqrt(pow((second.first - first.first),2) + pow((second.second - first.second),2));
    res = round(res*100)/100;
    return res;
}
