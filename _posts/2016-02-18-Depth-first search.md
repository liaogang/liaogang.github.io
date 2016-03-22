---
layout: post  
title: Depth-first search
date: 2016-02-18  
categories: tech     
---  

[Wiki: Depth-First Search](https://zh.wikipedia.org/wiki/%E6%B7%B1%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2)  

深度优先搜索算法（英语：Depth-First-Search，简称DFS）是一种用于遍历或搜索树或图的算法。沿着树的深度遍历树的节点，尽可能深的搜索树的分支。当节点v的所在边都己被探寻过，搜索将回溯到发现节点v的那条边的起始节点。这一过程一直进行到已发现从源节点可达的所有节点为止。如果还存在未被发现的节点，则选择其中一个作为源节点并重复以上过程，整个进程反复进行直到所有节点都被访问为止。属于盲目搜索。  

深度优先搜索是图论中的经典算法，利用深度优先搜索算法可以产生目标图的相应拓扑排序表，利用拓扑排序表可以方便的解决很多相关的图论问题，如最大路径问题等等。  



		struct Node 
		{
		   int self; //数据 
		   Node *left; //左节点 
		   Node *right; //右节点 
		};
		
		const int TREE_SIZE = 9;
		std::stack<Node*> unvisited; 
		Node nodes[TREE_SIZE]; 
		Node* current;
			
		//初始化树
		for(int i=0; i<TREE_SIZE; i++)
		{
		  nodes[i].self = i;
		  int child = i*2+1;
		  if(child<TREE_SIZE) // Left child
		    nodes[i].left = &nodes[child];
		  else
		    nodes[i].left = NULL;
		  child++;
		  if(child<TREE_SIZE) // Right child    
		    nodes[i].right = &nodes[child];
		  else
		    nodes[i].right = NULL;
		}           
			
		unvisited.push(&nodes[0]); //先把0放入UNVISITED stack
			
		// 只有UNVISITED不空
		while(!unvisited.empty())
		{
		  current=(unvisited.top()); //当前应该访问的
		  unvisited.pop(); 
		  if(current->right!=NULL) 
		    unvisited.push(current->right); // 把右边压入 因为右边的访问次序是在左边之后
		  if(current->left!=NULL) 
		    unvisited.push(current->left);
		  cout<<current->self<<endl;
		}


