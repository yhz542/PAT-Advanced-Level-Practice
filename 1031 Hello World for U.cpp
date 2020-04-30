#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
#define INFINITE 65535
typedef unsigned int uint;
class pta1031
{
    string str;
    size_t N;
    uint k1, k2, k3;
public:
    pta1031(istream& in):k1(0),k2(0),k3(0)
    {
        in >> str;
        N = str.size();
    }
    void Solve()
    {
        uint oneOfThree = (N+2) / 3;
        uint remainder = (N+2) % 3;
        k2 = oneOfThree + remainder;
        while (k2 < 3)
        {
            oneOfThree--;
            k2 += 2;
        }
        k1 = k3 = (oneOfThree-1);
    }
    void Print()
    {
        for (uint i = 0; i < k1; ++i)
        {
            cout << str[i];
            for (uint j = 0; j < k2 - 2; ++j)
                cout << ' ';
            cout << str[str.size() - i - 1]<<endl;
        }
        for (uint i = k1; i < k1 + k2; ++i)
        {
            cout << str[i];
        }
        cout << endl;
    }
};
int main()
{
    pta1031 question(cin);
    question.Solve();
    question.Print();
    return 0;
}
