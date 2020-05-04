#include<iostream>//首次AC代码，用的连通分量的方法以及字符串到数字的映射表关系
#include<vector>//可优化空间极大，主要是在计算一组通话人的总时间时不需要把所有人的所有童话关系都记录下来。
#include<string>
#include<map>
#include<queue>
#include<algorithm>
#include<set>
using namespace std;
typedef unsigned int uint;
struct GangInfo
{
    string head;
    uint num;
    GangInfo(string name, uint cnt) :head(name), num(cnt) {}
    bool operator<(const GangInfo other) const
    {
        return this->head < other.head;
    }
};
class pta1034
{
    uint N, K, totalPeopleNum;
    map<string, int> relation;//名字到数字的映射
    vector<string> relationTable;//数字到名字的反映社
    vector<vector<uint>> callTime;//呼叫时长构建的图
    vector<uint> callTimeForEach;//计算单人的总呼叫时长
    vector<GangInfo> headOfGang;//记录头领
    set<int> remaindedPeopleIndex;//剩余未处理的人的数值映射
public:
    //读取输入做的处理
    //因为输入是字符串，所以为了建立图，需要建立从字符串到整形的映射转换。
    //这里用relation建立从字符串到整数的映射
    //用relationTable建立从整数到字符串的反映社
    //然后可以利用映射关系建立图
    //图中边代表两个人的通话时长。
    pta1034(istream& in) :totalPeopleNum(0)
    {
        in >> N >> K;
        callTime.resize(2*N, vector<uint>(2*N, 0));
        string name1, name2;
        uint time, index1, index2;
        for (size_t i = 0; i < N; ++i)
        {
            in >> name1 >> name2 >> time;
            if (relation.find(name1) == relation.end())
                relation.insert(make_pair(name1, totalPeopleNum++));
            if (relation.find(name2) == relation.end())
                relation.insert(make_pair(name2, totalPeopleNum++));
            index1 = relation[name1];
            index2 = relation[name2];
            callTime[index1][index2] += time;
            callTime[index2][index1] += time;
        }
        relationTable.resize(totalPeopleNum);
        for (auto beg = relation.cbegin(); beg != relation.cend(); ++beg)
        {
            string name = beg->first;
            size_t index = beg->second;
            remaindedPeopleIndex.insert(index);
            relationTable[index] = name;
        }
        callTimeForEach.resize(totalPeopleNum, 0);
        headOfGang.reserve(totalPeopleNum / 3);
    }
    //解题思路：
    //1.用连通图的思想来处理所有数据来确定有多少组
    //2.对每个连通图进行广度优先搜索，确定该组中的人数和总通话时间
    //3.通过人数和通话时间来确定该组是否是Gang
    //4.广度优先搜索时，判断当前人是否是该组人中通话时长最长的那个，并记录
    //5.如果该组是Gang，那么将该组通话时长最长的人设为头领，
    void Solve()
    {
        queue<int> search;//广度优先队列
        uint numInGroup = 0;//组中的人数
        uint groupCallTime = 0;//该组的总通话时长
        uint maxTimeInGroup = 0;//该组中的人通话最长的时长
        uint maxTimePeopleIndex;//该组中通话最长的人的整形映射
        vector<bool> visited(totalPeopleNum, false);//这个人是否已经访问过
        while (!remaindedPeopleIndex.empty())
        {
            //外循环计算连通图
            int callerIndex = *(remaindedPeopleIndex.begin());
            search.push(callerIndex);
            visited[callerIndex] = true;
            while (!search.empty())
            {
                //内循环是广度优先搜索
                int curIndex = search.front();
                search.pop();
                remaindedPeopleIndex.erase(curIndex);
                numInGroup++;
                for (size_t i = 0; i < totalPeopleNum; ++i)
                {
                    callTimeForEach[curIndex] += callTime[curIndex][i];//计算每个人的呼叫总时长
                    if (callTime[i][curIndex])//计算每组呼叫总时长，由于一条边只能遍历一次。但是图是双向的，所以遍历一次后，将该calltime置为0，避免下次重复访问
                    {
                        groupCallTime += callTime[i][curIndex];//计算组通话时间，可以用每个人的通话时间累加和除以2.
                        if (!visited[i])//如果改点未访问过，将改点加入广度优先搜索队列中。
                        {
                            search.push(i);
                            visited[i] = true;
                        }
                        callTime[curIndex][i] = 0;//访问过后，将该值置为0，
                    }
                }
                if (callTimeForEach[curIndex] > maxTimeInGroup)
                {
                    maxTimeInGroup = callTimeForEach[curIndex];
                    maxTimePeopleIndex = curIndex;
                }
            }
            if (numInGroup > 2 && groupCallTime > K)
                headOfGang.push_back(GangInfo(relationTable[maxTimePeopleIndex], numInGroup));
            numInGroup = 0;
            groupCallTime = 0;
            maxTimeInGroup = 0;
        }
    }
    void Print()
    {
        if (headOfGang.empty())
        {
            cout << 0 << endl;
        }
        else
        {
            sort(headOfGang.begin(), headOfGang.end());
            cout << headOfGang.size() << endl;
            for (auto elem : headOfGang)
                cout << elem.head << ' ' << elem.num << endl;
        }
    }
};
int main()
{
    pta1034 question(cin);
    question.Solve();
    question.Print();
    return 0;
}
