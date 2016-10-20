

## Programming Assignment #6

### 2-SUM

Download the following text file: algo1-programming_prob-2sum.txt

The goal of this problem is to implement a variant of the 2-SUM algorithm (covered in the Week 6 lecture on hash table applications).

The file contains 1 million integers, both positive and negative (there might be some repetitions!).This is your array of integers, with the $i^{th}$ row of the file specifying the $i^{th}$ entry of the array.

Your task is to compute the number of target values $t$ in the (inclusive) interval [-10000,10000] such that there are *distinct* numbers x,y in the input file that satisfy $x+y=t$. (NOTE: ensuring distinctness requires a one-line addition to the algorithm from lecture.)

Write your numeric answer (an integer between 0 and 20001) in the space provided.

OPTIONAL CHALLENGE: If this problem is too easy for you, try implementing your own hash table for it. For example, you could compare performance under the chaining and open addressing approaches to resolving collisions.


## My Note

The code run slowly. The hash table solution is probably not ideal in this particular case (as mentioned in the course forum). Because of the narrow range of t compared to the large scatter of 1 million intergers, sorting the array and limit the range of search might be more efficient than doing the 20000 $t$ for-loop all in brute force.   
 


