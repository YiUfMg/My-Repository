#pragma once

#include <vector>
#include <array>
#include <memory>
#define DIMENSION 3 // 拼图的维数
#define SIZE (DIMENSION*DIMENSION) //拼图的大小

// exit(10)是路径大小和深度不一致
// exit(5)是expand时找不到0的下标
// exit(11)是创建答案时列表不为空，被注释
// exit(15)是open表中有重复项，被注释
class Node;  // 声明Node类
class Puzzle_Tree;  // 声明Puzzle_Tree类，状态空间

typedef std::shared_ptr<Node> pNode;  // pNode为指向Node的指针
typedef std::array<int, SIZE> puzzle_arr;  // puzzle_arr为储存状态的array数组
typedef std::vector<pNode> vec_pNodes;     // vec_pNodes是储存pNode的vector向量		

const puzzle_arr default_P{ 1,2,3,
							8,0,4,
							7,6,5 };  // 默认目的地
class Node  //当作有内置方法的结构体
{
public:
	// 默认构造函数，未定义
	Node();  
	// 通过一个puzzle_arr和目标puzzle_arr初始化Node，一般用作根节点
	Node(puzzle_arr arr, puzzle_arr* P);   
	// 通过一个puzzle_arr和父节点指针初始化Node，用作拓展节点
	Node(puzzle_arr arr, pNode par);
	// 复制构造函数，未定义
	Node(Node&);
	// 拓展子节点，返回子节点数量，未和openList和closeList交互，放在Puzzle_Tree中实现
	int expand();
	// 估计距离目标P的代价
	int cal_p2P(puzzle_arr& P);
	// 计算代价并更改price
	int cal_price();
	// 重载==，判断当前节点是否和目标态P相同
	bool operator==(puzzle_arr P); 
	// 强制转换未puzzle_arr类型
	operator puzzle_arr();
	// 展示状态
	void display_arr();

	vec_pNodes children;        // 所有子节点
	pNode parent = nullptr;     // 距离初始状态最近的父节点
	puzzle_arr cur_puzzle{ 0 }; // 当前拼图的局面
	puzzle_arr* target{ 0 };    // 目标状态
	int distance_to_S0 = 0;     // 距离初始状态S0最近的距离
	int price_to_P = 0;         // 预估距离目标P的距离
	int price = 0;              // 总代价
};

class Puzzle_Tree
{
public:
	friend class Bothway_Puzzle;
	// 默认构造函数，未定义
	Puzzle_Tree();
	// 析构函数
	~Puzzle_Tree();
	// 通过一个或两个puzzle_arr,作为初始状态S0,有内置默认结果
	Puzzle_Tree(puzzle_arr arrS0, puzzle_arr arrP = default_P);
	// 检查是否在openList 里，是则返回pNode，否返回nullptr
	pNode in_openList(pNode);
	// 检查是否在closeList里，是则返回pNode，否返回nullptr
	pNode in_closeList(pNode);
	// 集合前二者，是否在两个列表内,返回重复的指针
	pNode in_twoList(pNode rnode12);
	// w版本对列表进行替换
	bool in_openListw(pNode node3);
	// w版本对列表进行替换
	bool in_closeListw(pNode node4);
	// 集合前二者，是否在两个列表内
	bool in_twoListw(pNode);
	// 对openList进行排序
	void sort_openList();
	// 更改目标，未定义
	void change_target(puzzle_arr);
	// A*搜索一次，即从openList选中一个，拓展并判断
	void serch_once();
	// A*搜索过程，返回一条从初始态指向结果的vec_pNode路径
	vec_pNodes serch();
	// 展示答案
	void display_answer();
	vec_pNodes result;

private:
	pNode S0;
	puzzle_arr target;
	int node_Num = 0;
	vec_pNodes openList;  // open表， 待搜索列表
	vec_pNodes closeList; // close表，已搜索列表

};

class Bothway_Puzzle : public Puzzle_Tree // 双向A*搜索里面的r代表反向
{
public:
	Bothway_Puzzle();
	Bothway_Puzzle(puzzle_arr arrS0, puzzle_arr arrP = default_P);
	// 检查是否在openList 里，是则返回pNode，否返回nullptr
	pNode in_ropenList(pNode rnode1);
	// 检查是否在closeList里，是则返回pNode，否返回nullptr
	pNode in_rcloseList(pNode rnode2);
	// 集合前二者，是否在两个列表内,返回重复的指针
	pNode in_tworList(pNode rnode12);
	// w版本对列表进行替换
	bool in_ropenListw(pNode rnode3);
	// w版本对列表进行替换
	bool in_rcloseListw(pNode rnode4);
	// 集合前二者，是否在两个列表内
	bool in_tworListw(pNode rnode5);
	// 对openList进行排序
	void sort_ropenList();
	// A*搜索一次，即从openList选中一个，拓展并判断
	void rserch_once();
	// A*搜索过程，返回一条从初始态指向结果的vec_pNode路径
	vec_pNodes rserch();
private:
	pNode rS0;
	puzzle_arr rtarget;
	int rnode_Num = 0;
	vec_pNodes ropenList;  // ropen表， 待搜索列表
	vec_pNodes rcloseList; // rclose表，已搜索列表
};