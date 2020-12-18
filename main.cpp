#include "factory.hpp"
#include "pub_sub.hpp"
#include <thread>
#include <functional>
using namespace std;
/*
 * Ежов Н П М80-204Б-19
* Создать приложение, которое будет считывать из стандартного
 * ввода данные фигур, согласно варианту задания, выводить их
 * характеристики на экран и записывать в файл. Фигуры могут
 * задаваться как своими вершинами, так и другими характеристиками
 * (например, координата центра, количество точек и радиус).
 * Программа должна:
 * 1. Осуществлять ввод из стандартного ввода данных фигур,
 *    согласно варианту задания;
 * 2. Программа должна создавать классы, соответствующие введенным
 *    данных фигур;
 * 3. Программа должна содержать внутренний буфер, в который
 *    помещаются фигуры. Для создания буфера допускается
 *    использовать стандартные контейнеры STL. Размер буфера
 *    задается параметром командной строки. Например, для буфера
 *    размером 10 фигур: oop_exercise_08 10
 * 4. При накоплении буфера они должны запускаться на
 *    асинхронную обработку, после чего буфер должен очищаться;
 * 5. Обработка должна производиться в отдельном потоке;
 * 6. Реализовать два обработчика, которые должны обрабатывать
 *    данные буфера:
 *    1. Вывод информации о фигурах в буфере на экран;
 *    2. Вывод информации о фигурах в буфере в файл. Для каждого
 *       буфера должен создаваться файл с уникальным именем.
 * 7. Оба обработчика должны обрабатывать каждый введенный буфер.
 *    Т.е. после каждого заполнения буфера его содержимое должно
 *    выводиться как на экран, так и в файл.
 * 8. Обработчики должны быть реализованы в виде лямбда-функций и
 *    должны хранится в специальном массиве обработчиков. Откуда и
 *    должны последовательно вызываться в потоке – обработчике.
 * 9. В программе должно быть ровно два потока (thread). Один
 *    основной (main) и второй для обработчиков;
 * 10. В программе должен явно прослеживаться шаблон
 *    Publish-Subscribe. Каждый обработчик должен быть реализован
 *    как отдельный подписчик.
 * 11. Реализовать в основном потоке (main) ожидание обработки
 *    буфера в потоке-обработчике. Т.е. после отправки буфера на
 *    обработку основной поток должен ждать, пока поток обработчик
 *    выведет данные на экран и запишет в файл.
 */
enum type {
    trapeze = 1,
    rhomb = 2,
    pentagon = 3
};
using SCALAR_TYPE = int;
const string FOLDER = "files/";
ofstream file;
PubSub <vector<shared_ptr<Figure<SCALAR_TYPE>>>> pubsub;
int part = 1;
string genFileName(size_t n) {
    string res = to_string(n)+".txt";
    return res;
}

void ThreadFunc() {
    using functionType = function<void(shared_ptr<Figure<SCALAR_TYPE>> fig)>;
    functionType PrintToStdout = [](const shared_ptr<Figure<SCALAR_TYPE>> fig) {
        (*fig).Write(cout);
    };
    functionType WriteToFile = [](const shared_ptr<Figure<SCALAR_TYPE>> fig) {
        (*fig).Write(file);
    };
    vector<functionType> funcs({PrintToStdout, WriteToFile});
    bool awake = true;
    while (awake) {
        if (!pubsub.Empty()) {
            vector<shared_ptr<Figure<SCALAR_TYPE>>> message = pubsub.Front();
            if (message.empty()) {
                awake = false;
            }
            string filename = (FOLDER + genFileName(part));
            file = ofstream(filename);
            while (!message.empty()) {
                shared_ptr<Figure<SCALAR_TYPE>> figPtr = message.back();
                message.pop_back();
                for (auto func : funcs) {
                    func(figPtr);
                }
            }
            file.close();
            ++part;
            pubsub.Pop();
        }
    }
}

int main(int argc, char** argv) {
    size_t bufferSize;
    if(argc != 2){
        cout << "Wrong count of arguments!" << "\n";
        return -1;
    }
    try {
        bufferSize = stoi(string(argv[1]));
    }
    catch (exception & ex) {
        cout << ex.what() << "\n";
        return -1;
    }
    if(bufferSize <= 0){
        cout << "Wrong size!" << "\n";
        return -1;
    }
    thread myThread(ThreadFunc);
    vector<shared_ptr<Figure<SCALAR_TYPE>>> figures;
    unsigned int type;
    while (cin >> type) {
        if (type == trapeze) {
            figures.push_back(Factory<SCALAR_TYPE, Trapeze<SCALAR_TYPE>>::CreateFigure(cin));
        }
        else if (type == rhomb) {
            figures.push_back(Factory<SCALAR_TYPE, Rhomb<SCALAR_TYPE>>::CreateFigure(cin));
        }
        else if (type == pentagon) {
            figures.push_back(Factory<SCALAR_TYPE, Pentagon<SCALAR_TYPE>>::CreateFigure(cin));
        }
        if (figures.size() == bufferSize) {
            pubsub.Push(figures);
            bool threadWorkDone = false;
            while (!threadWorkDone) {
                if (pubsub.Empty()){
                    threadWorkDone = true;
                }
            }
            figures.clear();
        }
    }
    pubsub.Push(figures);
    figures.clear();
    pubsub.Push(figures);
    myThread.join();
}