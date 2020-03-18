#include "stdafx.h"
//
#include "KSTreeNode.h"  

void KSTreeNode::AddSub(KSCommand * Data)
{
	KSTreeNode * NewNode = new KSTreeNode();
	NewNode->DataNode = Data;
	Sub = NewNode;
}


//
//class KSCommand
//{
//public:
//	string Cmd;
//	bool IsSub = false;
//	KSCommandTree * SubCmds;
//	KSCommandTree * Parent;
//};
//// ÓÐË³Ðò
//class KSCommandTree
//{
//public:
//	vector<KSCommand> CmdList;
//	int Count = 0;
//public:
//	void AddCmd(string);
//	KSCommandTree * AddSub();
//};
//
//KSCommandTree * KSCommandTree::AddSub()
//{
//	KSCommand k;
//	k.IsSub = true;
//	k.Parent = this;
//	k.SubCmds = new KSCommandTree();
//	return k.SubCmds;
//}
//
//void KSCommandTree::AddCmd(string cmd)
//{
//	KSCommand k;
//	k.Cmd = cmd;
//	CmdList.push_back(k);
//}
//
//int ParseCMDs1(string str)
//{
//	str = str.append(" ");
//	const char * chrs = str.c_str();
//	INT Length = str.length();
//	INT i = 0;
//	INT j = 0;
//	auto root = new KSCommandTree();
//	while (i < Length)
//	{
//		// trim 
//		while (chrs[i] == ' ') i++;
//		j = i;
//		if (j >= Length)
//			break;
//		while (chrs[j++] == '{')
//		{
//			root = root->AddSub();
//		}
//		while (chrs[j] != ' ' && chrs[j] != '}'&& chrs[j] != '{') j++;
//		string p = str.substr(i, j - i);
//		root->AddCmd(p);
//
//		while (chrs[j++] == '}')
//		{
//			int count = 0;
//			while (chrs[j] >= '0' && chrs[j] <= '9')
//			{
//				count = count * 10 + chrs[j] - '0';
//				j++;
//			}
//			root->Count = count == 0 ? 1 : count;
//			root = root->AddSub();
//		}
//		// p = p.append('\0');
//		// CMDList.push_back(p);
//		i = j;
//		i++;
//	}
//
//	return 0;
//}
