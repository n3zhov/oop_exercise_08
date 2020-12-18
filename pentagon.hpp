//
// Created by Nikita on 25.11.2020.
//

#pragma once
#include "figure.hpp"
template <typename T>
class Pentagon : public Figure<T>{
public:
    Pentagon(){
        this->points.resize(5);
        this->points[0] = {0, 0};
        this->points[1] = {0, 0};
        this->points[2] = {0, 0};
        this->points[3] = {0, 0};
        this->points[4] = {0, 0};
    }
    Pentagon(T const& p11, T const& p12, T const& p21, T const& p22, T const& p31, T const& p32, T const& p41,
             T const& p42, T const& p51, T const& p52){
        this->points.resize(5);
        this->points[0] = {p11, p12};
        this->points[1] = {p21, p22};
        this->points[2] = {p31, p32};
        this->points[3] = {p41, p42};
        this->points[4] = {p51, p52};
    }
    void Write(ostream &os){
        os << "Pentagon\n";
        os << this->points[0];
        os << this->points[1];
        os << this->points[2];
        os << this->points[3];
        os << this->points[4] << "\n";
    }
    void Write(ofstream &of){
        of << "3\n";
        of << this->points[0];
        of << this->points[1];
        of << this->points[2];
        of << this->points[3];
        of << this->points[4] << "\n";
    }
};

//Оператор ввода
template<typename T>
std::istream& operator>>(std::istream& is, Pentagon<T>& pg)
{
    while(true)
    {
        try
        {
            std::string str[10];
            double d[10];
            std::cout << "Enter 10 values: p1(x,y), p2(x,y), p3(x,y), p4(x,y), p5(x,y)\n";
            for(size_t i = 0; i < 10; ++i) {
                is >> str[i];
            }
            for(size_t i = 0; i < 10; ++i) {
                d[i] = std::stod(str[i]);
            }
            pg.points[0] = { static_cast<T>(d[0]), static_cast<T>(d[1]) };
            pg.points[1] = { static_cast<T>(d[2]), static_cast<T>(d[3]) };
            pg.points[2] = { static_cast<T>(d[4]), static_cast<T>(d[5]) };
            pg.points[3] = { static_cast<T>(d[6]), static_cast<T>(d[7]) };
            pg.points[4] = { static_cast<T>(d[8]), static_cast<T>(d[9]) };
            vector<double> sides(5);
            sides[0] = distance(pg.points[0], pg.points[1]);
            sides[1] = distance(pg.points[1], pg.points[2]);
            sides[2] = distance(pg.points[2], pg.points[3]);
            sides[3] = distance(pg.points[3], pg.points[4]);
            sides[4] = distance(pg.points[0], pg.points[4]);
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
std::ostream& operator<<(std::ostream& os, Pentagon<T>& pg)
{
    os << "3\n";
    os << pg.points[0];
    os << pg.points[1];
    os << pg.points[2];
    os << pg.points[3];
    os << pg.points[4] << "\n";
    return os;
}
