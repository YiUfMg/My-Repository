#include <algorithm>
#include <iostream>
#include "Tree.h"
Node::Node(puzzle_arr arr, puzzle_arr* P)
{
	cur_puzzle = arr;
	target = P;
	cal_p2P(*P);
	cal_price();
}
Node::Node(puzzle_arr arr, pNode par)
{
	cur_puzzle = arr;
	target = par->target;
	parent = par;
	distance_to_S0 = par->distance_to_S0 + 1;
	cal_p2P(*target);
	cal_price();
}
int Node::expand()  
{
	puzzle_arr next_puzzle = cur_puzzle;
	int pos_0 = //0的位置
		([](puzzle_arr& arr)->int 
		{
			int count = 0;
			for (auto x : arr) 
			{ 
				if (x == 0)
				{
					return count;
				}
				count++;
			}
			exit(5);
		})(cur_puzzle); 
	if (pos_0 - DIMENSION >= 0)  // 向上
	{
		std::swap(next_puzzle.at(pos_0), next_puzzle.at(pos_0 - DIMENSION));
		children.push_back(pNode(new Node(next_puzzle, pNode(this))));
		std::swap(next_puzzle.at(pos_0), next_puzzle.at(pos_0 - DIMENSION));
	}
	if (pos_0 + DIMENSION < SIZE)  // 向下
	{
		std::swap(next_puzzle.at(pos_0), next_puzzle.at(pos_0 + DIMENSION));
		children.push_back(pNode(new Node(next_puzzle, pNode(this))));
		std::swap(next_puzzle.at(pos_0), next_puzzle.at(pos_0 + DIMENSION));
	}
	if (pos_0 % DIMENSION != 0)  // 向左
	{
		std::swap(next_puzzle.at(pos_0),next_puzzle.at(pos_0-1));
		children.push_back(pNode(new Node(next_puzzle, pNode(this))));
		std::swap(next_puzzle.at(pos_0), next_puzzle.at(pos_0 - 1));
	}
	if ((pos_0 + 1) % DIMENSION != 0)  // 向右
	{
		std::swap(next_puzzle.at(pos_0), next_puzzle.at(pos_0 + 1));
		children.push_back(pNode(new Node(next_puzzle, pNode(this))));
		std::swap(next_puzzle.at(pos_0), next_puzzle.at(pos_0 + 1));
	}
	return int(children.size());
}
int Node::cal_p2P(puzzle_arr& P)
{
	
	auto compare = [](puzzle_arr &arr1, puzzle_arr &arr2)->int
	{
		int count = 0;  // 相同位置数字相同的个数
		auto p2 = arr2.begin();
		for (auto a1 : arr1)
		{
			if (a1 == *p2 && a1!=0)
				count++;
			p2++;
		}
		return count;
	};// 相同位置数字相同的个数
	price_to_P = SIZE - compare(cur_puzzle, P);// 相同位置数字不同的个数
	return price_to_P;
}
int Node::cal_price()
{
	price = distance_to_S0 + price_to_P * 2;
	return price;
}
bool Node::operator==(puzzle_arr P)
{
	return cur_puzzle == P;
}
Node::operator puzzle_arr()
{
	return cur_puzzle;
}
void Node::display_arr()
{
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int j = 0; j < DIMENSION; j++)
		{
			std::cout << cur_puzzle[DIMENSION * i + j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

Puzzle_Tree::Puzzle_Tree(puzzle_arr arrS0, puzzle_arr arrP) 
{

	target = arrP;
	node_Num++;
	S0 = pNode(new Node(arrS0, &target));

	closeList.push_back(S0);
	S0->expand();
	for (pNode x : S0->children)
	{
		openList.push_back(x);
		node_Num++;
	}
	sort_openList();
	if (arrS0 == arrP)
	{
		result.push_back(S0);
	}
	else
	{
		for (pNode& x : openList) // 先进行是否成功判断，避免一步就成功了
		{
			if (*x == target)
			{
				if (!result.empty())
				{
					exit(11);
				}
				result.push_back(S0);
				result.push_back(x);
			}
		}
	}
}
Puzzle_Tree::~Puzzle_Tree()
{
	openList.clear();
	closeList.clear();
	result.clear();
}
pNode Puzzle_Tree::in_openList(pNode node1)
{
	for (pNode node : openList)
	{
		if (node->cur_puzzle == node1->cur_puzzle)
			return node;
	}
	return nullptr;
}
pNode Puzzle_Tree::in_closeList(pNode node2)
{
	for (pNode node : closeList)
	{
		if (node->cur_puzzle == node2->cur_puzzle)
			return node;
	}
	return nullptr;
}
pNode Puzzle_Tree::in_twoList(pNode rnode12)
{
	pNode rnod = in_openList(rnode12);
	return  (rnod == nullptr ? in_closeList(rnode12) : rnod);
}
bool Puzzle_Tree::in_openListw(pNode node3)
{
	for (pNode &node : openList)
	{
		if (node->cur_puzzle == node3->cur_puzzle)
		{
			if (node3->distance_to_S0 < node->distance_to_S0)
			{
				node = node3;//替换掉路径最短的
			}
			return true;
		}
	}
	return false;
}
bool Puzzle_Tree::in_closeListw(pNode node4)
{
	for (pNode &node : closeList)
	{
		if (node->cur_puzzle == node4->cur_puzzle)
		{
			/*if (node4->distance_to_S0 < node->distance_to_S0)
			{
				for (pNode& nod : node->children)
				{
					nod->parent = node4;
					nod->distance_to_S0 = node4->distance_to_S0 + 1;
					nod->cal_price();
				}
				node = node4;
			}*/
			return true;
		}
	}
	return false;
}
bool Puzzle_Tree::in_twoListw(pNode node5)
{
	return (in_openListw(node5) || in_closeListw(node5));
}
void Puzzle_Tree::sort_openList()
{
	std::sort(openList.begin(), openList.end(), [](pNode  pN1, pNode pN2)->bool 
		{
			/*if (pN1->cur_puzzle == pN2->cur_puzzle)
			{
				pN1->display_arr();
				pN2->display_arr();
				exit(15);
			}*/
			return pN1->price < pN2->price; 
		});
}
void Puzzle_Tree::display_answer()
{
	for (pNode &x : result)
	{
		x->display_arr();
	}
	std::cout << "共" << result.size()-1 << "步";
}
void Puzzle_Tree::serch_once()
{
	pNode curNode = openList.front();  // 储存open表的第一个节点
	openList.erase(openList.begin());  // 在open表中删去
	curNode->expand();
	if (closeList.size() % 100 == 0)
	{
		std::cout << "node_Num:" << node_Num << " closeList:" << closeList.size() << ' ' << curNode->distance_to_S0 << '\n';
	}
	for (pNode child : curNode->children)  //对新节点进行操作
	{
		if (in_twoListw(child))  // 检查是否有重复
		{
		}
		else if (*child == target)  // 是否到达目标
		{
			/*if (!result.empty())
			{
				exit(11);
			}*/
			int size = child->distance_to_S0;
			do {
				result.insert(result.begin(), child);
				child = child->parent;
			} while (child != nullptr);
			if (result.size() -1 != size)
			{
				exit(10);
			}
			return;
		}
		else
		{
			// 既无重复，也未达目标
			openList.push_back(child);
			node_Num++;
		}
	}
	closeList.push_back(curNode);
	sort_openList();
}
vec_pNodes Puzzle_Tree::serch()
{
	while (result.empty())
	{
		serch_once();
	}
	return result;
}

Bothway_Puzzle::Bothway_Puzzle(puzzle_arr arrS0, puzzle_arr arrP) : Puzzle_Tree(arrS0, arrP)
{

	rtarget = arrS0;
	rnode_Num++;
	rS0 = pNode(new Node(arrP, &rtarget));
	rcloseList.push_back(rS0);
	rS0->expand();
	for (pNode x : rS0->children)
	{
		ropenList.push_back(x);
		rnode_Num++;
	}
	sort_ropenList();
}
pNode Bothway_Puzzle::in_ropenList(pNode rnode1)
{
	for (pNode node : ropenList)
	{
		if (node->cur_puzzle == rnode1->cur_puzzle)
			return node;
	}
	return nullptr;
}
pNode Bothway_Puzzle::in_rcloseList(pNode rnode2)
{
	for (pNode node : rcloseList)
	{
		if (node->cur_puzzle == rnode2->cur_puzzle)
			return node;
	}
	return nullptr;
}
pNode Bothway_Puzzle::in_tworList(pNode rnode12)
{
	pNode rnod = in_ropenList(rnode12);
	return  (rnod == nullptr ? in_rcloseList(rnode12) : rnod);
}
bool Bothway_Puzzle::in_ropenListw(pNode rnode3)
{
	for (pNode& node : ropenList)
	{
		if (node->cur_puzzle == rnode3->cur_puzzle)
		{
			if (rnode3->distance_to_S0 < node->distance_to_S0)
			{
				node = rnode3;//替换掉路径最短的
			}
			return true;
		}
	}
	return false;
}
bool Bothway_Puzzle::in_rcloseListw(pNode rnode4)
{
	for (pNode& node : rcloseList)
	{
		if (node->cur_puzzle == rnode4->cur_puzzle)
		{
			/*if (rnode4->distance_to_S0 < node->distance_to_S0)
			{
				for (pNode& nod : node->children)
				{
					nod->parent = rnode4;
					nod->distance_to_S0 = rnode4->distance_to_S0 + 1;
					nod->cal_price();
				}
				node = rnode4;
			}*/
			return true;
		}
	}
	return false;
}
bool Bothway_Puzzle::in_tworListw(pNode rnode5)
{
	return (in_ropenListw(rnode5) || in_rcloseListw(rnode5));
}
void Bothway_Puzzle::sort_ropenList()
{
	std::sort(ropenList.begin(), ropenList.end(), [](pNode  pN1, pNode pN2)->bool
		{
			/*if (pN1->cur_puzzle == pN2->cur_puzzle)
			{
				pN1->display_arr();
				pN2->display_arr();
				exit(15);
			}*/
			return pN1->price < pN2->price;
		});
}
void Bothway_Puzzle::rserch_once()
{
	pNode repetition;

	pNode curNode = openList.front();  // 储存open表的第一个节点
	openList.erase(openList.begin());  // 在open表中删去
	curNode->expand();

	for (pNode child : curNode->children)  //对新节点进行操作
	{
		if (in_twoListw(child))  // 检查是否有重复
		{
		}
		else if ((repetition = in_tworList(child)) != nullptr)
		{
			do {
				result.insert(result.begin(), child);
				child = child->parent;
			} while (child != nullptr);
			while (repetition->parent != nullptr)
			{
				repetition = repetition->parent;
				result.push_back(repetition);
			}
			return;
		}
		else if (*child == target)  // 是否到达目标
		{
			/*if (!result.empty())
			{
				exit(11);
			}*/
			//std::cout << "1111111111111\n";
			int size = child->distance_to_S0;
			do {
				result.insert(result.begin(), child);
				child = child->parent;
			} while (child != nullptr);
			if (result.size() - 1 != size)
			{
				exit(10);
			}
			return;
		}
		else
		{
			// 既无重复，也未达目标
			openList.push_back(child);
			node_Num++;
		}
	}
	closeList.push_back(curNode);
	sort_openList();
	//反向搜索一次
	pNode rcurNode = ropenList.front();  // 储存open表的第一个节点
	ropenList.erase(ropenList.begin());  // 在open表中删去
	rcurNode->expand();
	for (pNode child : rcurNode->children)  //对新节点进行操作
	{
		if (in_tworListw(child))  // 检查是否有重复
		{
		}
		else if ((repetition = in_twoList(child)) != nullptr)
		{
			do {
				result.insert(result.begin(), repetition);
				repetition = repetition->parent;
			} while (repetition != nullptr);
			while (child->parent != nullptr)
			{
				child = child->parent;
				result.push_back(child);
			}
			return;
		}
		else if (*child == rtarget)  // 是否到达目标
		{
			//std::cout << "1111111111111\n";
			do {
				result.push_back(child);
				child = child->parent;
			} while (child != nullptr);
			return;
		}
		else
		{
			// 既无重复，也未达目标
			ropenList.push_back(child);
			rnode_Num++;
		}
	}
	rcloseList.push_back(curNode);
	sort_ropenList();

	if ((closeList.size() + rcloseList.size()) % 100 == 0)
	{
		std::cout << "r+node_Num:" << node_Num << " r+closeList:" << closeList.size() + rcloseList.size() << ' '
			<< curNode->distance_to_S0 << ' ' << rcurNode->distance_to_S0 << '\n';
	}
}
vec_pNodes Bothway_Puzzle::rserch()
{
	while (result.empty())
	{
		rserch_once();
	}
	return result;
}
