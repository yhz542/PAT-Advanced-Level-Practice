//解题思路：https://www.liuchuo.net/archives/2255 没什么好说的，排序之后降低查找范围。
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef unsigned int uint;
class pta1055
{
	typedef uint numOfOutput;
	typedef uint Age;
	typedef uint Amax;
	struct cmp;
	typedef struct pinfo
	{
		friend struct cmp;
		friend class pta1055;
	private:
		char name[9];
		uint age;
		int netWorth;
	public:
		pinfo(const char str[],uint a,int net):age(a),netWorth(net){
			strcpy(name, str);
		}
	} info;
	struct cmp
	{
	private:
		const vector<info> &copy_data;
	public:
		bool operator()(const int left, const int right) const
		{
			if (copy_data[left].netWorth != copy_data[right].netWorth)
			{
				return copy_data[left].netWorth > copy_data[right].netWorth;
			}
			else if (copy_data[left].age != copy_data[right].age)
			{
				return copy_data[left].age < copy_data[right].age;
			}
			else
			{
				return strcmp(copy_data[left].name ,copy_data[right].name)<0;
			}
		}
		cmp(const vector<info>&data):copy_data(data){}
	};
	vector<info> data;
	vector<uint> indexAfterFilter;
	vector<uint> indexBeforeFilter;
	vector<uint> spaceForQuery;
	vector<Age> numOfAge;
	uint N, K;
public:
	pta1055(istream &in)
	{
		numOfAge.resize(200, 0);
		scanf("%u %u", &N , &K);
		data.reserve(N);
		indexBeforeFilter.reserve(N);
		spaceForQuery.reserve(1000);
		indexAfterFilter.reserve(20000);
		char name[9];
		uint age;
		int netWorth;
		for (size_t i = 0; i < N; ++i)
		{
			scanf("%s %u %d", name ,&age, &netWorth);
			data.push_back(info(name, age, netWorth));
			indexBeforeFilter.push_back(i);
		}
	}
	void Solve()
	{
		sort(indexBeforeFilter.begin(), indexBeforeFilter.end(), cmp(data));
		for (auto elem : indexBeforeFilter)
		{
			Age val = data[elem].age - 1;
			if (numOfAge[val] != 100)
			{
				++numOfAge[val];
				indexAfterFilter.push_back(elem);
			}
		}
		numOfOutput num;
		Age Amin;
		Age Amax;
		for (size_t i = 0,cnt; i < K; ++i)
		{
			cnt = 0;
			scanf("%u %u %u", &num, &Amin, &Amax);
			printf("Case #%u:\n", i + 1);
			uint allNum = 0;
			for (Age begin = Amin; begin <= Amax; ++begin)//算得上是优化的部分
			{
				allNum += numOfAge[begin - 1];
			}
			num = (num < allNum ? num : allNum);
			if (!num)
				printf("None\n");
			for (auto elem : indexAfterFilter)
			{
				Age a = data[elem].age;
				if (a >= Amin && a <= Amax)
				{
					printf("%s %u %d\n", data[elem].name, a, data[elem].netWorth);
					if (0 == --num)
						break;
				}
			}
		}
	}
	void Print()
	{
	}
	~pta1055()
	{}
};
int main()
{
	pta1055 *question  = (pta1055 *)malloc(sizeof(pta1055));
	new (question) pta1055(cin);
	question->Solve();
	question->Print();
	question->~pta1055();
	free(question);
}
/************************ 附自己写的超时算法，常规算法，已经尽力，二分查找加桶排序，个人能想到的最快方法了，无奈输入规模太大，测试点2依然会超时
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef unsigned int uint;
class pta1055
{
	typedef uint numOfOutput;
	typedef uint Amin;
	typedef uint Amax;
	struct cmp1;
	struct cmp2;
	typedef struct pinfo
	{
		friend struct cmp1;
		friend struct cmp2;
		friend class pta1055;
	private:
		char name[9];
		uint age;
		int netWorth;
	public:
		pinfo(const char str[],uint a,int net):age(a),netWorth(net){
			strcpy(name, str);
		}
	} info;
	struct cmp1
	{
	private:
		const vector<info>& copy_data;
	public:
		bool operator()(const int left, const int right) const
		{
			return copy_data[left].age < copy_data[right].age;
		}
		cmp1(const vector<info>& data) :copy_data(data) {}
	};
	struct cmp2
	{
	private:
		const vector<info> &copy_data;
	public:
		bool operator()(const int left, const int right) const
		{
			if (copy_data[left].netWorth != copy_data[right].netWorth)
			{
				return copy_data[left].netWorth > copy_data[right].netWorth;
			}
			else if (copy_data[left].age != copy_data[right].age)
			{
				return copy_data[left].age < copy_data[right].age;
			}
			else
			{
				return strcmp(copy_data[left].name ,copy_data[right].name)<0;
			}
		}
		cmp2(const vector<info>&data):copy_data(data){}
	};
	vector<info> data;
	vector<uint> index;
	vector<uint> spaceForQuery;
	uint N, K;
	uint FindAmin(Amin target)
	{
		bool isFind = false;
		int head = 0, tail = (int)index.size() - 1;
		int cur,curIndex;
		while (head <= tail)
		{
			cur = (head + tail) / 2;
			curIndex = index[cur];
			if (data[curIndex].age < target)
				head = cur + 1;
			else if (data[curIndex].age > target)
				tail = cur - 1;
			else
			{
				isFind = true;
				break;
			}
		}
		if (isFind)
		{
			while (cur-1 >= 0)
			{
				if (data[index[cur - 1]].age == target)
					--cur;
				else
					break;
			}
			return cur;
		}
		else
		{
			while (head - 1 >= 0)
			{
				if (data[index[head - 1]].age == data[index[head ]].age)
					--head;
				else
					break;
			}
			return head;
		}
	}
public:
	pta1055(istream &in)
	{
		scanf("%u %u", &N , &K);
		data.reserve(N);
		index.reserve(N);
		spaceForQuery.reserve(100);
		char name[9];
		uint age;
		int netWorth;
		for (size_t i = 0; i < N; ++i)
		{
			scanf("%s %u %d", name ,&age, &netWorth);
			data.push_back(info(name, age, netWorth));
			index.push_back(i);
		}
	}
	void Solve()
	{
		sort(index.begin(), index.end(), cmp1(data));
		numOfOutput num;
		Amin min;
		Amax max;
		uint left = 0;
		for (size_t i = 0,cnt; i < K; ++i)
		{
			cnt = 0;
			scanf("%u %u %u", &num, &min, &max);
			left = FindAmin(min);
			for (uint begin = left; (begin<N)&&(data[index[begin]].age<=max); ++begin)
			{
				spaceForQuery.push_back(index[begin]);
			}
			sort(spaceForQuery.begin(), spaceForQuery.end(), cmp2(data));
			printf("Case #%u:\n",i + 1);
			if (spaceForQuery.empty())
				puts("None");
			for (auto elem : spaceForQuery)
			{
				if (cnt == num)
					break;
				printf("%s %u %d\n",data[elem].name ,data[elem].age , data[elem].netWorth );
				cnt++;
			}
			spaceForQuery.clear();
		}
	}
	void Print()
	{
	}
	~pta1055()
	{}
};
int main()
{
	pta1055 *question  = (pta1055 *)malloc(sizeof(pta1055));
	new (question) pta1055(cin);
	question->Solve();
	question->Print();
	question->~pta1055();
	free(question);
}
*/
