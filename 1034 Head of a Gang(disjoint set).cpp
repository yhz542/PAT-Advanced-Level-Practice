#include<iostream>//并查集方法，依然用的字符串到数字的映射。理论上来说应该可以直接利用map将这一步骤优化掉，节约内存空间
#include<vector>//算法思想，根节点是团伙中通话时间最长的人，子节点是团伙中其他人，总通话时间等于团伙中所有人通话时间之和除以2
#include<string>//这里大部分的处理放在输入时进行，一边读取输入，一边实时更新根节点。
#include<map>
#include<queue>
#include<algorithm>
#include<set>
using namespace std;
typedef unsigned int uint;
struct info
{
    int parent;
    uint callTime;
    info(uint time) :parent(-1),callTime(time)
    {}
};
class pta1034
{
    uint N, K, totalPeopleNum;
    map<string, int> relation;//名字到数字的映射
    vector<string> relationTable;//数字到名字的反映社
    map<string,uint> headOfGang;//头领及团伙信息
    vector<info> infoSet;
    uint FindRoot(uint current)//寻找根
    {
        if (infoSet[current].parent < 0)
            return current;
        else
            return infoSet[current].parent = FindRoot(infoSet[current].parent);
    }
    inline bool IsExistOrNot(string name)//该节点是否已存在
    {
        return relation.find(name) != relation.end();
    }
    void CreateNewMapping(string name,uint time)//创造一个新的映射关系
    {
        relationTable.push_back(name);
        relation.insert(make_pair(name, totalPeopleNum++));
        infoSet.push_back(time);
    }
    void ExistedProcess(string name,uint time)//如果节点已存在的处理
    {
        uint curIndex = relation[name];
        infoSet[curIndex].callTime += time;
        uint rootIndex = FindRoot(curIndex);
        if (infoSet[rootIndex].callTime < infoSet[curIndex].callTime)//有新输入，意味着呼叫时长会增加，这时要和根节点进行比较。
        {
            infoSet[curIndex].parent = infoSet[rootIndex].parent;
            infoSet[rootIndex].parent = curIndex;
        }
    }
    void Combine(uint index1, uint index2)//归并两个节点的组
    {
        uint root1 = FindRoot(index1);
        uint root2 = FindRoot(index2);
        if (root1 == root2)
            return;
        if (infoSet[root1].callTime < infoSet[root2].callTime)
        {
            infoSet[root2].parent += infoSet[root1].parent;
            infoSet[root1].parent = root2;
        }
        else
        {
            infoSet[root1].parent += infoSet[root2].parent;
            infoSet[root2].parent = root1;
        }
    }
public:
    pta1034(istream& in) :totalPeopleNum(0)
    {
        in >> N >> K;
        infoSet.reserve(2 * N);
        string name1, name2;
        uint time, index1, index2;
        relationTable.reserve(2*N);
        for (size_t i = 0; i < N; ++i)
        {
            in >> name1 >> name2 >> time;
            if (IsExistOrNot(name1))
                ExistedProcess(name1, time);
            else
                CreateNewMapping(name1, time);
            if (IsExistOrNot(name2))
                ExistedProcess(name2, time);
            else
                CreateNewMapping(name2, time);
            index1 = relation[name1];
            index2 = relation[name2];
            Combine(index1, index2);
        }
    }
    void Solve()
    {
        uint rootIndex;
        for (uint i = 0; i < totalPeopleNum; ++i)
        {
            rootIndex = FindRoot(i);
            string name = relationTable[rootIndex];
            if (headOfGang.find(name) == headOfGang.end())
                headOfGang.insert(make_pair(name,0));
            headOfGang[name] += infoSet[i].callTime;
        }
        for (auto beg = headOfGang.begin(); beg != headOfGang.end();)
        {
            beg->second /= 2;
            if (beg->second > K&& infoSet[relation[beg->first]].parent < -2)
                beg++;
            else
                beg=headOfGang.erase(beg);//干掉不满足题目条件的元素
        }
    }
    void Print()
    {
        if (headOfGang.empty())
            cout << 0 << endl;
        else
            cout << headOfGang.size() << endl;
        for (auto& elem : headOfGang)
            cout << elem.first << ' ' << -infoSet[relation[elem.first]].parent << endl;
    }
};
int main()
{
    pta1034 question(cin);
    question.Solve();
    question.Print();
    return 0;
}
