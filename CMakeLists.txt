cmake_minimum_required(VERSION 3.26)
project(cpp_algorithm)

set(CMAKE_CXX_STANDARD 14)

#顺序表
add_executable(SeqList SeqList.cpp)
#单链表
add_executable(LinkList LinkList.cpp)
#双链表
add_executable(DblLinkList DblLinkList.cpp)
#单循环链表
add_executable(CirLinkList CirLinkList.cpp)
#双循环链表
add_executable(DblCirLinkList DblCirLinkList.cpp)
#静态链表
add_executable(StaticLinkList StaticLinkList.cpp)
#栈
add_executable(SeqStack SeqStack.cpp)
#队列
add_executable(SeqQueue SeqQueue.cpp)
#二叉树顺序存储
add_executable(BinaryTreeOrder BinaryTreeOrder.cpp)
#二叉树链式存储
add_executable(BinaryTreeChain BinaryTreeChain.cpp)
#线索二叉树
add_executable(ThreadBinaryTree ThreadBinaryTree.cpp)
#二叉查找树（BST）
add_executable(BinarySearchTree BinarySearchTree.cpp)
#平衡二叉树（AVL）
add_executable(AVLTree AVLTree.cpp)
#红黑（R-B）树
add_executable(RBTree RBTree.cpp)
#图
add_executable(HFMTree HFMTree.cpp)
#深度优先遍历（DFS）与广度优先遍历（BFS）
add_executable(GraphLink GraphLink.cpp)
#最小生成树 如何用普里姆（Prim）算法
add_executable(Prim Prim.cpp)
#最小生成树 克鲁斯卡尔（Kruskal）算法
add_executable(Kruskal Kruskal.cpp)
#最短路径 迪杰斯特拉（Dijkstra）算法
add_executable(Dijkstra Dijkstra.cpp)
#最短路径 弗洛伊德（Floyd）算法
add_executable(Floyd Floyd.cpp)
#拓扑排序
add_executable(TopologicalSort TopologicalSort.cpp)
#关键路径
add_executable(CriticalPath CriticalPath.cpp)
#直接插入排序
add_executable(InsertSort InsertSort.cpp)
#希尔排序
add_executable(ShellSort ShellSort.cpp)
#冒泡排序
add_executable(BubbleSort BubbleSort.cpp)
#快速排序
add_executable(QuickSort QuickSort.cpp)
#简单选择排序与堆排序
add_executable(HeapSelSort HeapSelSort.cpp)
#归并排序
add_executable(MergingSort MergingSort.cpp)
#串的顺序和链式存储结构
add_executable(SString SString.cpp)
#串的朴素模式匹配算法
add_executable(NaivePattern NaivePattern.cpp)
#串的KMP模式匹配算法
add_executable(KMP KMP.cpp)
#串的KMP模式匹配算法之改进
add_executable(KMPopt KMPopt.cpp)
#跳表
add_executable(SkipList SkipList.cpp
        MersenneTwister.h)
#哈希表与哈希算法
add_executable(HashTbl HashTbl.cpp)
#多路查找树 B树
add_executable(BTreeNode BTreeNode.cpp)
#折半插入、2路插入、表插入
add_executable(InsertSortCompare InsertSortCompare.cpp)
#树形选择排序
add_executable(TreeSelSort TreeSelSort.cpp)
#计数排序
add_executable(CountSort CountSort.cpp)
#基数排序与桶排序
add_executable(RadixSort RadixSort.cpp)

