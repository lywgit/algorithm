### Programming Assignment #2: Clustering
 
*Algorithms: Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming*

**Q1**

In this programming problem and the next you'll code up the clustering algorithm from lecture for computing a max-spacing k-clustering.

Download the text file below

[clustering1.txt](clustering1.txt)

This file describes a distance function (equivalently, a complete graph with edge costs). It has the following format:

[number_of_nodes]

[edge 1 node 1] [edge 1 node 2] [edge 1 cost]

[edge 2 node 1] [edge 2 node 2] [edge 2 cost]

...

There is one edge (i,j) for each choice of 1≤i<j≤n, where n is the number of nodes.

For example, the third line of the file is "1 3 5250", indicating that the distance between nodes 1 and 3 (equivalently, the cost of the edge (1,3)) is 5250. You can assume that distances are positive, but you should NOT assume that they are distinct.

Your task in this problem is to run the clustering algorithm from lecture on this data set, where the target number k of clusters is set to 4. What is the maximum spacing of a 4-clustering?

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases. And then post them to the discussion forum!


<!--
	Ans: 106
-->


**Q2**

In this question your task is again to run the clustering algorithm from lecture, but on a MUCH bigger graph. So big, in fact, that the distances (i.e., edge costs) are only defined implicitly, rather than being provided as an explicit list.

The data set is below.

[clustering_big.txt](clustering_big.txt)

The format is:

[# of nodes] [# of bits for each node's label]

[first bit of node 1] ... [last bit of node 1]

[first bit of node 2] ... [last bit of node 2]

...

For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" denotes the 24 bits associated with node #2.

The distance between two nodes u and v in this problem is defined as the Hamming distance--- the number of differing bits --- between the two nodes' labels. For example, the Hamming distance between the 24-bit label of node #2 above and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd, 7th, and 21st bits).

The question is: what is the largest value of k such that there is a k-clustering with spacing at least 3? That is, how many clusters are needed to ensure that no pair of nodes with all but 2 bits in common get split into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you probably can't write it out explicitly, let alone sort the edges by cost. So you will have to be a little creative to complete this part of the question. For example, is there some way you can identify the smallest distances without explicitly looking at every pair of nodes?

<!--
Ans: Number of clusters (after mergeing all edges with distance <= 2) : 6118
-->

### LY Note

**For Q1**

- *k\_clustering\_basic.cpp* 
	- the basic implementation that simply union the latter cluster to the former (without considering ranks). 
- *k\_clustering\_by\_rank.cpp*
	- union by rank, but still update all parent
- *k\_clustering\_lazy\_by\_rank.cpp*
	- union by rank, only update the leader
- *k\_clustering\_lazy\_by\_rank\_path\_compression.cpp*
	- union by rank, with path compression

It seems that these doesn't make a big difference (on the clustering1.txt data set)?


**For Q2**

Thoughts:

- There exist an edge between every two nodes
- Not every possible node (combination of 24 bit label) exist.
	- there are 2$^{24}$ = 16,777,216 possible combinations, where there are only 200,000 nodes in the cluster_big.txt file
- to have cluster spacing of larger than 3, no edge of distance 0,1,2 should exist across clusters. 
	- => you should check (and merge) all edges with distance smaller than 2.
	- => once all distance <=2 edges are checked (and merged if they were in differemnt clusters), you don't care about the rest of the edges, since now the spacing is at least 3 
	- => and you should actually stop mergeing after all distance 2 edges are done, since we want the maximun k, and continue merging will decrease k.
- In cnclusion, should find out all edges with distance <=2 

Concern:

- There may still be too many combinations
- number of connected candidates for a given node  
	- distance 0: 1 (duplicates)
	- distance 1: 24 (fliping one of the 24 bit)
	- distance 2: C(24,2) = (24 * 23)/(2 * 1) = 276   
	- in total: 301 
- For each node in the list, look up if the 301 possible other nodes exist as well, if yes, then the edge need to be considered. Storing the data in unordered\_multiset should give O(1) look up time(?). 
- The node data should contain an id so that when we know that the other node is also in the list, we are able to record the edge for later merging.   

Code:

- *clustering\_largest\_k\_brute\_force.cpp*
	- Using brute force to find edges of distance 0,1,2 takes: ~ 20 min
- *clustering\_largest\_k.cpp*
	- Using the check-small-edges method takes ~2.5 min. 


Info:

- I store the bit label as `bitset<24>` inside the costumed Node structure.
- Putting this in container `unordered_set<Node>` for fast look up requires some tricks. See the following link for information: 
	- [customed hash function and operator== ](http://stackoverflow.com/a/17017281) 
	- [c++ already has hash function for bitset](http://en.cppreference.com/w/cpp/utility/bitset/hash)
