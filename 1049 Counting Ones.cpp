/************************************
思路：
对于个位数n=9而言：1
1的个数为1
对于两位数n=99：01,11,21,31,41,51,61,71,81,91 (0~9共10个1，其中11只算后面那个1)以及 
10，11，12，13，14，15，16，17，18，19(0~9,10个1,11只算前面那个1) 这里11分为两个1 分别分成前后两块计算

所以1的个数为 10 * 1 + 10^1 = 20

对于三位数n=999而言:可以看成10个0~99 （不考虑百位数）其中每份包含 20个1（复用n=99的结果）

以及100~199 共100个1 

1的个数为 10*20 + 10^2 = 300

对于四位数n=9999而言：同理看一看成10个0~999 以及1000~1999 

1的个数为 10*300 + 10^3 = 4000

这其中存在一个递推关系

!!! 所以得到一个递推公式 : n位数中1的个数为  10 * n-1位中1的个数 + 10^(n-1)
可以用这个递推公式生成一个表
——————————————————
...|9999|999|99|9|
——————————————————
...|4000|300|20|1|
设N = Nn * 10^(n-1) + Nn-1 * 10^(n-2)...+ N3 *10^2 + N2*10^1 + N1*10^0
例 N = 915 可以分成三部计算
000~900中1的个数 设该数为N3
900~910中1的个数 设该数为N2
910~910中1的个数 设该数为N1

从左往右依次取 N 的每一位数

因为第一个数为 9 > 1 
N3 = 9 * 20 + 100 (20)为n=99时 1的个数 000 100 200 ...800 共9份 再算上100~199 共100个百位数的1

因为第二个数为 1 = 1
N2 = 1      因为本位为1，所以看作右边的每一个数都带一个1，所以 1 的个数 = 本位右边的数+1（包括0）

因为第三个数为0
N1 = 0         
************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<vector>
using namespace std;
typedef unsigned int uint;
class pta1049
{
	uint N;
	uint numOfOne;
	uint tem;
	string Nstr;
	vector<uint> oneList;
	void GenerateOneList()
//生成一个1的个数表，表中存储的为个位数所对应的1的个数，两位数对应的1的个数，三位数对应1的个数...
	{
		uint numOfOne = 0;
		uint length = Nstr.size();
		int i = 1;
		auto beg = oneList.rbegin();
		*(beg++) = 0;
		while (--length)
		{
			numOfOne *= 10;
			numOfOne += i;
			*beg = numOfOne;
			++beg;
			i *= 10;
		}
		tem = i;
	}
public:
	pta1049(istream &in):numOfOne(0),tem(0)
	{
		in >> N;
		stringstream tem;
		tem << N;
		tem >> Nstr;
		oneList.resize(Nstr.size());
	}
	void Solve()
	{
		GenerateOneList();
		uint curNum = 0;
		for (uint index = 0; index < Nstr.size(); ++index)
		{
			curNum = Nstr[index] - '0';
			numOfOne += (curNum)*oneList[index];
			if (curNum > 1)//总共当前位数分三种情况 大于1 等于1 小于1（等于0）进行处理
			{
				numOfOne += tem;
			}
			else if(curNum == 1)
			{
				numOfOne += (N % tem)+1;//取右边的数
			}
			tem /= 10;
		}
	}
	void Print()
	{
		cout << numOfOne << endl;
	}
	~pta1049()
	{}
};
int main()
{
	pta1049 *question  = (pta1049 *)malloc(sizeof(pta1049));
	new (question) pta1049(cin);
	question->Solve();
	question->Print();
	question->~pta1049();
	free(question);
}
/***********附他人更好的做法
分析：这是一道数学问题。从第一位（个位）到最高位，设now为当前位的数字，left为now左边的所有数字构成的数字，right是now右边的所有数字构成的数字。只需要一次次累加对于当前位now来说可能出现1的个数，然后把它们累加即可。a表示当前的个位为1，十位为10，百位为100类推。
对于now，有三种情况：
1.now == 0 : 那么 ans += left * a; //因为now==0说明now位只有在left从0~left-1的时候会产生1，所以会产生left次，但是又因为右边会重复从0~999…出现a次
2.now == 1 : ans += left * a + right + 1;//now = 1的时候就要比上一步多加一个当now为1的时候右边出现0~right个数导致的now为1的次数
3.now > 1 : ans += (left + 1) * a;//now大于等于2就左边0~left的时候会在now位置产生1，所以会产生left次，但是又因为右边会重复从0~999…出现a次
***********/
/***********
#include<iostream>
#include<algorithm>
using namespace std;
int ans;
int main()
{
    int n;
    scanf("%d", &n);
    int a = 1, left, right;
    while (n / a)
    {
        int now = n / a % 10;
        left = n / (a * 10);
        right = n%a;
        if (now == 0)ans += left*a;
        else if (now == 1)ans += left*a + 1 + right;
        else if (now > 1)ans += (left + 1)*a;
        a *= 10;
        cin.get();
    }
    printf("%d", ans);
    return 0;
}
***********/
