#include<iostream>//主要思想，利用map实现快速查找，因为id号唯一，所以用set进行存储，同时由于set本身是升序排列，所以直接输出即可。省事
#include<cstdio>
#include<vector>
#include<string>
#include<sstream>
#include<map>
#include<set>
using namespace std;
typedef unsigned int uint;
class pta1022
{
	uint N,M;
	map<string,set<uint>> bookTitle;
	map<string,set<uint>> author;
	map<string,set<uint>> publisherName;
	map<string,set<uint>> year;
	map<string,set<uint>> keyword;
	vector<string> question;
	void Split(string &, uint);
	void QueryOutput(map<string,set<uint>>&,string &);
public:
	void GetInput();
	void Solve();
	void Output();
};
int main()
{
	pta1022 project;
	project.GetInput();
	project.Solve();
	project.Output();
}
void pta1022::GetInput()
{
	cin >> N;
	string words;
	uint IDnumber;
	for (uint i = 0; i < N; ++i)
	{
		cin >> IDnumber; 
		getchar();
		getline(cin, words);
		bookTitle[words].insert( IDnumber);
		getline(cin, words);
		author[words].insert(IDnumber);
		getline(cin, words);
		Split(words,IDnumber);
		getline(cin, words);
		publisherName[words].insert(IDnumber);
		getline(cin, words);
		year[words].insert(IDnumber);
	}
	cin >> M;
	getchar();//吸收\n
	string temQuestion;
	for (uint i = 0; i < M; ++i)
	{
		getline(cin, temQuestion);
		question.push_back(temQuestion);
	}
}
void pta1022::Solve()
{
	string curquestion;
	for (uint i = 0,index,length; i < M; ++i)
	{
		index = question[i][0];
		length = question[i].size()-3;
		curquestion = question[i].substr(3,length);
		cout <<question[i] << endl;
		switch (index)
		{
		case '1':
		{
			QueryOutput(bookTitle, curquestion);
			break; 
		}
		case '2':
		{
			QueryOutput(author, curquestion);
			break; 
		}
		case '3':
		{
			QueryOutput(keyword, curquestion);
			break; 
		}
		case '4':
		{
			QueryOutput(publisherName, curquestion);
			break;
		}
		case '5':
		{
			QueryOutput(year, curquestion);
			break;
		}
		default:
			cout << "error!" << endl;
			break;
		}
	}
}
void pta1022::Output()
{
}
void pta1022::Split(string &words, uint IDnumber)
{
	stringstream tem(words);
	string word;
	while (tem >> word)
		keyword[word].insert(IDnumber);
}
void pta1022::QueryOutput(map<string,set<uint>>&data,string &question)
{
	auto answer = data.find(question);
	if (answer != data.end())
	{
		set<uint> &numSet = answer->second;
		for (auto beg = numSet.begin(); beg != numSet.end(); ++beg)
		{
			printf("%07u\n", *beg);
		}
	}
	else
		cout << "Not Found" << endl;
}
