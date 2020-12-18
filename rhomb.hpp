//
// Created by Nikita on 25.11.2020.
//

#pragma once
#include "figure.hpp"
template <typename T>
class Rhomb : public Figure<T>{
public:
    Rhomb(){
        this->points.resize(4);
        this->points[0] = {0, 0};
        this->points[1] = {0, 0};
        this->points[2] = {0, 0};
        this->points[3] = {0, 0};
    }
    Rhomb(T const& p11, T const& p12, T const& p21, T const& p22, T const& p31, T const& p32, T const& p41,
             T const& p42){
        this->points.resize(4);
        this->points[0] = {p11, p12};
        this->points[1] = {p21, p22};
        this->points[2] = {p31, p32};
        this->points[3] = {p41, p42};
    }
    void Write(ostream &os){
        os << "Rhomb\n";
        os << this->points[0];
        os << this->points[1];
        os << this->points[2];
        os << this->points[3] << "\n";
    }
    void Write(ofstream &of){
        of << "2\n";
        of << this->points[0];
        of << this->points[1];
        of << this->points[2];
        of << this->points[3] << "\n";
    }
};

//Оператор ввода
template<typename T>
std::istream& operator>>(std::istream& is, Rhomb<T>& rb)
{
    while(true)
    {
        try
        {
            std::string str[8];
            double d[8];
            std::cout << "Enter 8 values: p1(x,y), p2(x,y), p3(x,y), p4(x,y)\n";
            for(auto & i : str) {
                is >> i;
            }
            for(size_t i = 0; i < 8; ++i) {
                d[i] = std::stod(str[i]);
            }
            rb.points[0] = { static_cast<T>(d[0]), static_cast<T>(d[1]) };
            rb.points[1] = { static_cast<T>(d[2]), static_cast<T>(d[3]) };
            rb.points[2] = { static_cast<T>(d[4]), static_cast<T>(d[5]) };
            rb.points[3] = { static_cast<T>(d[6]), static_cast<T>(d[7]) };
            vector<double> sides(5);
            sides[0] = distance(rb.points[0], rb.points[1]);
            sides[1] = distance(rb.points[1], rb.points[2]);
            sides[2] = distance(rb.points[2], rb.points[3]);
            sides[3] = distance(rb.points[3], rb.points[4]);
            double arg = sides[0];
            int ans = count_if(sides.begin(), sides.end(), [arg](double &side) {
                return arg == side;
            });
            if(ans != sides.size()){
                throw std::exception();
            }
            return is;
        }
        catch(const std::exception& e) { std::cerr << e.what() << "\n"; }
    }
}

//Оператор вывода
template<typename T>
std::ostream& operator<<(std::ostream& os, Rhomb<T>& rb)
{
    os << "2\n";
    os << rb.points[0];
    os << rb.points[1];
    os << rb.points[2];
    os << rb.points[3] << "\n";
    return os;
}
