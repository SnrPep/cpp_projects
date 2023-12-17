//Найти количество всех элементов строк матрицы целых чисел, делящихся на 3. Каждая
//строка обрабатывается своим отдельным потоком.

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void fin(vector<int> arr, int& count)
{
    int result = 0;
    for (int element : arr) {
        if (element % 3 == 0){
            result++;
        }
    }
    count = result;
}

int main()
{
    int vectorNumber = 10;
    int vectorSize = 1000;

    vector<vector<int> > matrix(vectorNumber);
    for (vector<int>& element : matrix)
    {
        element = vector<int>(vectorSize);
    }

    for(int i = 0; i < vectorNumber; i++)
    {
        for(int j = 0; j < vectorSize; j++)
        {
            if (i==j){
                matrix[i][j] = 3;
            }
            else
                matrix[i][j] = 1;
        }
    }

    vector<int> vectorOfSum(vectorNumber);
    vector<thread> vectorOfTreads(vectorNumber);
    for(int i = 0; i < vectorNumber; i++)
    {
        vectorOfTreads[i] = thread(fin, matrix[i], ref(vectorOfSum[i]));
    }

    for(int i = 0; i < vectorNumber; i++)
    {
        vectorOfTreads[i].join();
    }

    for(int i = 0; i < vectorNumber; i++)
    {
        cout << vectorOfSum[i] << "\n";
    }

    return 0;
}
