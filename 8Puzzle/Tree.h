#pragma once

#include <vector>
#include <array>
#include <memory>
#define DIMENSION 3 // ƴͼ��ά��
#define SIZE (DIMENSION*DIMENSION) //ƴͼ�Ĵ�С

// exit(10)��·����С����Ȳ�һ��
// exit(5)��expandʱ�Ҳ���0���±�
// exit(11)�Ǵ�����ʱ�б�Ϊ�գ���ע��
// exit(15)��open�������ظ����ע��
class Node;  // ����Node��
class Puzzle_Tree;  // ����Puzzle_Tree�࣬״̬�ռ�

typedef std::shared_ptr<Node> pNode;  // pNodeΪָ��Node��ָ��
typedef std::array<int, SIZE> puzzle_arr;  // puzzle_arrΪ����״̬��array����
typedef std::vector<pNode> vec_pNodes;     // vec_pNodes�Ǵ���pNode��vector����		

const puzzle_arr default_P{ 1,2,3,
							8,0,4,
							7,6,5 };  // Ĭ��Ŀ�ĵ�
class Node  //���������÷����Ľṹ��
{
public:
	// Ĭ�Ϲ��캯����δ����
	Node();  
	// ͨ��һ��puzzle_arr��Ŀ��puzzle_arr��ʼ��Node��һ���������ڵ�
	Node(puzzle_arr arr, puzzle_arr* P);   
	// ͨ��һ��puzzle_arr�͸��ڵ�ָ���ʼ��Node��������չ�ڵ�
	Node(puzzle_arr arr, pNode par);
	// ���ƹ��캯����δ����
	Node(Node&);
	// ��չ�ӽڵ㣬�����ӽڵ�������δ��openList��closeList����������Puzzle_Tree��ʵ��
	int expand();
	// ���ƾ���Ŀ��P�Ĵ���
	int cal_p2P(puzzle_arr& P);
	// ������۲�����price
	int cal_price();
	// ����==���жϵ�ǰ�ڵ��Ƿ��Ŀ��̬P��ͬ
	bool operator==(puzzle_arr P); 
	// ǿ��ת��δpuzzle_arr����
	operator puzzle_arr();
	// չʾ״̬
	void display_arr();

	vec_pNodes children;        // �����ӽڵ�
	pNode parent = nullptr;     // �����ʼ״̬����ĸ��ڵ�
	puzzle_arr cur_puzzle{ 0 }; // ��ǰƴͼ�ľ���
	puzzle_arr* target{ 0 };    // Ŀ��״̬
	int distance_to_S0 = 0;     // �����ʼ״̬S0����ľ���
	int price_to_P = 0;         // Ԥ������Ŀ��P�ľ���
	int price = 0;              // �ܴ���
};

class Puzzle_Tree
{
public:
	friend class Bothway_Puzzle;
	// Ĭ�Ϲ��캯����δ����
	Puzzle_Tree();
	// ��������
	~Puzzle_Tree();
	// ͨ��һ��������puzzle_arr,��Ϊ��ʼ״̬S0,������Ĭ�Ͻ��
	Puzzle_Tree(puzzle_arr arrS0, puzzle_arr arrP = default_P);
	// ����Ƿ���openList ����򷵻�pNode���񷵻�nullptr
	pNode in_openList(pNode);
	// ����Ƿ���closeList����򷵻�pNode���񷵻�nullptr
	pNode in_closeList(pNode);
	// ����ǰ���ߣ��Ƿ��������б���,�����ظ���ָ��
	pNode in_twoList(pNode rnode12);
	// w�汾���б�����滻
	bool in_openListw(pNode node3);
	// w�汾���б�����滻
	bool in_closeListw(pNode node4);
	// ����ǰ���ߣ��Ƿ��������б���
	bool in_twoListw(pNode);
	// ��openList��������
	void sort_openList();
	// ����Ŀ�꣬δ����
	void change_target(puzzle_arr);
	// A*����һ�Σ�����openListѡ��һ������չ���ж�
	void serch_once();
	// A*�������̣�����һ���ӳ�ʼָ̬������vec_pNode·��
	vec_pNodes serch();
	// չʾ��
	void display_answer();
	vec_pNodes result;

private:
	pNode S0;
	puzzle_arr target;
	int node_Num = 0;
	vec_pNodes openList;  // open�� �������б�
	vec_pNodes closeList; // close���������б�

};

class Bothway_Puzzle : public Puzzle_Tree // ˫��A*���������r������
{
public:
	Bothway_Puzzle();
	Bothway_Puzzle(puzzle_arr arrS0, puzzle_arr arrP = default_P);
	// ����Ƿ���openList ����򷵻�pNode���񷵻�nullptr
	pNode in_ropenList(pNode rnode1);
	// ����Ƿ���closeList����򷵻�pNode���񷵻�nullptr
	pNode in_rcloseList(pNode rnode2);
	// ����ǰ���ߣ��Ƿ��������б���,�����ظ���ָ��
	pNode in_tworList(pNode rnode12);
	// w�汾���б�����滻
	bool in_ropenListw(pNode rnode3);
	// w�汾���б�����滻
	bool in_rcloseListw(pNode rnode4);
	// ����ǰ���ߣ��Ƿ��������б���
	bool in_tworListw(pNode rnode5);
	// ��openList��������
	void sort_ropenList();
	// A*����һ�Σ�����openListѡ��һ������չ���ж�
	void rserch_once();
	// A*�������̣�����һ���ӳ�ʼָ̬������vec_pNode·��
	vec_pNodes rserch();
private:
	pNode rS0;
	puzzle_arr rtarget;
	int rnode_Num = 0;
	vec_pNodes ropenList;  // ropen�� �������б�
	vec_pNodes rcloseList; // rclose���������б�
};