#include <iostream>
#include <fstream>

using namespace std;

const int questions_count = 16;

float yes_probability[questions_count];

float yes_probability_republican[questions_count];
float yes_probability_democrat[questions_count];

float democrat_probability = 0;
float republican_probability = 0;

float calcDemo(string &a) {
    float p1 = 1, p2d = 1,_pd = 1;// p1 = P(x0, x1, x2,..), p2 = P(x0 | democrat) * P(..).., _p = P(democrat)
    for(int i = 0; i < questions_count; ++ i) {
        int index = 2 * i;
        //cout << a[index];
        if(a[index] == 'y') {
            p1 *= yes_probability[i];
            p2d *= yes_probability_democrat[i];
        }
        else if(a[index] == '?') {
            p1 *= 0.5;
            p2d *= 0.5;
        }
        else {
            p1 *= 1 - yes_probability[i];
            p2d *= 1 - yes_probability_democrat[i];
        }

    }
    _pd = democrat_probability;
    //cout << p1 << " " << p2d << " " << _pd << " ";
    return p1 * p2d / _pd;
}

float calcRepu(string &a) {
    float p1 = 1, p2d = 1,_pd = 1;// p1 = P(x0, x1, x2,..), p2 = P(x0 | democrat) * P(..).., _p = P(democrat)
    for(int i = 0; i < questions_count; ++ i) {
        int index = 2 * i;
        //cout << a[index] << " ";
        if(a[index] == 'y') {
            //cout << "y";
            p1 *= yes_probability[i];
            p2d *= yes_probability_republican[i];
        }
        else if(a[index] == '?') {
            //cout << "?";
            p1 *= 0.5;
            p2d *= 0.5;
        }
        else {
            //cout << "n";
            p1 *= 1 - yes_probability[i];
            p2d *= 1 - yes_probability_republican[i];
        }
        //cout << endl;
    }
    //cout << endl;
    _pd = republican_probability;
    //cout << p1 << " " << p2d << " " << _pd << " ";
    return p1 * p2d / _pd;
}


int main() {
    ifstream train("train.txt");

    int sample_size = 0;

    while(!train.eof()) {
        sample_size ++;
        string a;
        train >> a;

        int offset;

        if(a.substr(0,8) == "democrat") {
            democrat_probability ++;
            offset = 8; /// democrat
        }
        else {
            republican_probability ++;
            offset = 10; ///republican
        }

        for(int i = 0;i < questions_count; ++ i) {
            int index = i * 2 + offset + 1;
            if(a[index] == 'y') {
                yes_probability[i] ++;
                yes_probability_republican[i] += offset == 10 ? 1 : 0;
                yes_probability_democrat[i] += offset == 8 ? 1 : 0;
            }
            else if(a[index] == '?') {
                yes_probability[i] += 0.5;
                yes_probability_republican[i] += (offset == 10 ? 1 : 0) * 0.5;
                yes_probability_democrat[i] += (offset == 8 ? 1 : 0) * 0.5;
            }
        }
        //cout << a << endl;
    }


    //cout << (republican_probability) << " " << (democrat_probability) << " " <<  (sample_size) << endl;
    for(int i = 0; i < questions_count; ++ i) {
        cout << (yes_probability[i] /= sample_size) << endl;
        cout << (yes_probability_republican[i] /= republican_probability) << endl;
        cout << (yes_probability_democrat[i] /= democrat_probability) << endl;
        cout << endl;
    }
    democrat_probability /= sample_size;
    republican_probability /= sample_size;
    //cout << democrat_probability << endl << republican_probability;
    cout << endl;

    ofstream out("out.txt");

    //out << sample_size << endl;

    ifstream test("test.txt");
    while(!test.eof()) {
        string b;
        test >> b;
        if(b == "")continue;
        //cout << b;
        out << (calcDemo(b) > calcRepu(b) ? "democrat" : "repubican")<< endl;
        //cout << calcDemo(b) << " " << calcRepu(b) << endl;
    }
}
