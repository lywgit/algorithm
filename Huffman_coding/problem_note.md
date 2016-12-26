### Programming Assignment #3-1,2: Huffman Coding 
 
*Algorithms: Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming*


**Q1**

In this programming problem and the next you'll code up the greedy algorithm from the lectures on Huffman coding.

Download the text file below.

[huffman.txt](huffman.txt)

This file describes an instance of the problem. It has the following format:

[number\_of\_symbols]

[weight of symbol #1]

[weight of symbol #2]

...

For example, the third line of the file is "6852892," indicating that the weight of the second symbol of the alphabet is 6852892. (We're using weights instead of frequencies, like in the "A More Complex Example" video.)

Your task in this problem is to run the Huffman coding algorithm from lecture on this data set. What is the maximum length of a codeword in the resulting Huffman code?

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases. And then post them to the discussion forum!

<!-- 
Ans: 19
-->

**Q2**

Continuing the previous problem, what is the minimum length of a codeword in your Huffman code?

<!-- 
Ans: 9
-->

### LY Note

Problem: 

- In my current implementation, I search the tree to locate the node position so that I can insert two children for it. This is done by a brute force search over the tree (since the tree maintains no key properties for search for). This is probably not a good way.   

[constructing Tree in C++](http://www.cprogramming.com/tutorial/lesson18.html)
