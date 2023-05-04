#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <typeinfo>
#include <ctime>

using namespace std;

class quadraticEquation {
public:
    double a, b, c;

    quadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    vector<double> roots() const {
        vector<double> root;

        double discriminant = b * b - 4 * a * c;
        if (discriminant >= 0)
        {
            root.push_back((-b + sqrt(discriminant)) / (2 * a));
            root.push_back((-b - sqrt(discriminant)) / (2 * a));
        }
        return root;
    }
};

class Student {
public:
    virtual ~Student() {};
    virtual vector<double> getAnswer(const quadraticEquation& coef) const = 0;
};


class goodStudent : public Student {
public:
    vector<double> getAnswer(const quadraticEquation& coef) const override
    {
        return coef.roots();
    }
};

class mediumStudent : public Student {
public:
    vector<double> getAnswer(const quadraticEquation& coef) const override
    {
        if (rand() % 2 == 1)
        {
            vector<double> root;
            root.push_back((-coef.b + sqrt(coef.b * coef.b - 4 * coef.a * coef.c)) / (2 * coef.a));
            return root;
        }
        else
        {
            return vector<double>();
        }
    }
};

class badStudent : public Student {
public:
    vector<double> getAnswer(const quadraticEquation& coef) const override
    {
        return vector<double>();
    }

};

class teacher
{
public:
    vector<int> resultStudent;

    void examination(Student* student, double a, double b, double c, const vector<double>& answer)
    {
        vector<double> result = student->getAnswer(quadraticEquation(a, b, c));

        int numRoots = result.size();
        if ((numRoots == 2 && result == answer))
        {
            resultStudent.push_back(2);
        }
        else if (numRoots == 1 || (numRoots == 2 && result != answer))
        {
            resultStudent.push_back(1);
        }
        else
        {
            resultStudent.push_back(0);
        }
    }

    void printResults(ofstream& outputs)
    {
        if (outputs.is_open())
        {
            for (int i = 0; i < resultStudent.size(); i++)
            {
                outputs << "Student" << i + 1 << ": " << "Grade " << resultStudent[i] << endl;
            }
            outputs.close();
            resultStudent.clear();
        }
    }
};

void inputCoef()
{
    teacher Teacher;
    srand(time(NULL));

    ifstream input("input.txt");
    ofstream outputs("outputs.txt");

    double a, b, c;
    while (input >> a >> b >> c)
    {
        int behavior = rand() % 3;
        Student* student = nullptr;

        switch (behavior) {
        case 0:
            student = new goodStudent();
            break;
        case 1:
            student = new mediumStudent();
            break;
        case 2:
            student = new badStudent();
            break;
        }
        vector<double> answer;
        int numRoots = 0;
        double discriminant = b * b - 4 * a * c;
        if (discriminant >= 0)
        {
            answer.push_back((-b + sqrt(discriminant)) / (2 * a));
            numRoots++;
            if (discriminant > 0)
            {
                answer.push_back((-b - sqrt(discriminant)) / (2 * a));
                numRoots++;
            }
        }
        Teacher.examination(student, a, b, c, answer);
        delete student;
    }

    input.close();
    Teacher.printResults(outputs);
    outputs.close();
}

int main()
{
    inputCoef();
    return 0;
}
