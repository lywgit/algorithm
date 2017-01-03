### Programming Assignment #4: knapsack'sproblem 
 
*Algorithms: Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming*

**Q1**

In this programming problem and the next you'll code up the knapsack algorithm from lecture.

Let's start with a warm-up. Download the text file below.

[knapsack1.txt](knapsack1.txt)

This file describes a knapsack instance, and it has the following format:

[knapsack\_size][number\_of\_items]

[value\_1] [weight\_1]

[value\_2] [weight\_2]

...

For example, the third line of the file is "50074 659", indicating that the second item has value 50074 and size 659, respectively.

You can assume that all numbers are positive. You should assume that item weights and the knapsack capacity are integers.

In the box below, type in the value of the optimal solution.

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases. And then post them to the discussion forum!


<!--
Ans: 2493893
-->


**Q2**

This problem also asks you to solve a knapsack instance, but a much bigger one.

Download the text file below.

[knapsack_big.txt](knapsack_big.txt)

This file describes a knapsack instance, and it has the following format:

[knapsack\_size][number\_of\_items]

[value\_1] [weight\_1]

[value\_2] [weight\_2]

...

For example, the third line of the file is "50074 834558", indicating that the second item has value 50074 and size 834558, respectively. As before, you should assume that item weights and the knapsack capacity are integers.

This instance is so big that the straightforward iterative implemetation uses an infeasible amount of time and space. So you will have to be creative to compute an optimal solution. One idea is to go back to a recursive implementation, solving subproblems --- and, of course, caching the results to avoid redundant work --- only on an "as needed" basis. Also, be sure to think about appropriate data structures for storing and looking up solutions to subproblems.

In the box below, type in the value of the optimal solution.

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases. And then post them to the discussion forum!

<!--
Ans 4243395
-->

## LY Note

- The second problem can actually be solved with the direct program implementation (*knapsack_array.cpp*) described in the lecture within resonable time (~1.5 minutes). The number of items (2000) is not large, but the large weight limit (knapsack\_size) 2,000,000 ndeed cost substaintial memory space.
- The recurseve implementation (*knapsack_recursive.cpp*) takes ~11 seconds.  
