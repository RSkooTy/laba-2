#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <typeinfo>
#include <ctime>

using namespace std;

class Student {
public:
    virtual ~Student() {};
    virtual vector<double> solution(double a, double b, double c) = 0;
};

class goodStudent : public Student {
public:
    vector<double> solution(double a, double b, double c) override {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return {0.0, 0.0};
        } else if (discriminant == 0) {
            double root = -b / (2 * a);
            return {root, root};
        } else {
            double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            return {root1, root2};
        }
    }
};

class mediumStudent : public Student {
public:
    double probability2;

    mediumStudent(double probability = 0.5) : probability2(probability) {}

    vector<double> solution(double a, double b, double c) override {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return {0.0, 0.0};
        } else if (discriminant == 0) {
            if (rand() % 2 < probability2) {
                double root = -b / (2 * a);
                return {root, root};
             }else
             {
                 return{0.0, 0.0};
             }
        } else
        {
            if(rand() % 2 < probability2)
            {
                double root1 = (-b + sqrt(discriminant)) / (2 * a);
                double root2 = (-b - sqrt(discriminant)) / (2 * a);
                return {root1, root2};
            }else
            {
                double root = -b / (2 * a);
                return {root, 0.0};
            }
        }
    }
};

class badStudent : public Student {
public:
    vector<double> solution(double a, double b, double c) override {
        return {0.0, 0.0};
    }
};

class teacher
{
public:
    vector<vector<double>> resultStudent;
    
    void examination(Student *student, double a, double b, double c, const vector<double>& roots)
    {
        vector<double> result = student->solution(a, b, c);
        
        if (typeid(*student) == typeid(badStudent)) {
            resultStudent.push_back(result);
            return;
        }
        
        double discriminant = b * b - 4 * a * c;
        vector<double> teacherRoots;
        if (discriminant > 0)
        {
            teacherRoots.push_back((-b + sqrt(discriminant)) / (2 * a));
            teacherRoots.push_back((-b - sqrt(discriminant)) / (2 * a));
        }
        else if (discriminant == 0)
        {
            teacherRoots.push_back(-b / (2 * a));
            teacherRoots.push_back(teacherRoots[0]);
        }
        else
        {
            teacherRoots.push_back(0.0);
            teacherRoots.push_back(0.0);
        }

        if (result == teacherRoots)
        {
            resultStudent.push_back(result);
        }
    }
    
    void printResults(ofstream& output)
    {
        if(output.is_open())
        {
            for(int i = 0; i < resultStudent.size(); i++)
            {
                double root1 = resultStudent[i][0];
                double root2 = resultStudent[i][1];

                output << "Student " << i+1 << ": " << endl;
                output << "Root 1: " << root1 << endl;
                output << "Root 2: " << root2 << endl << endl;
            }
            output.close();
            resultStudent.clear();
        }
    }
};

void inputCoef()
{
    teacher Teacher;
    srand(time(NULL));
    
    ifstream input("input.txt");
    ofstream output("output.txt");
    
    double a, b, c;
    while (input >> a >> b >> c)
    {
        int behavior = rand() % 3;
        Student *student;
        
        if(behavior == 0)
        {
            student = new goodStudent();
        }else if(behavior == 1)
        {
            student = new mediumStudent();
        }else
        {
            student = new badStudent();
        }

        vector<double> answer;
        if (b * b - 4 * a * c >= 0) {
            answer.push_back((-b + sqrt(b * b - 4 * a * c)) / (2 * a));
            answer.push_back((-b - sqrt(b * b - 4 * a * c)) / (2 * a));
        }
        
        Teacher.examination(student, a, b, c, answer);
        delete student;
    }
    
    input.close();
    Teacher.printResults(output);
    output.close();
}

int main()
{
    inputCoef();
    return 0;
}
