# AIO Invitational Sample Paper I - Editorial
For some reason the timing on orac for these problems is kinda cooked as everything takes like 10x the time to run
## Q1: Conga Line (Redux)
**Subtask 1**
You can just realise that if $K=N$, the order of everyone is fixed, so just calculate the sum of all consecutive distances in $O(N)$

**Subtask 2**
First, make an observation that any people of Umit's family can be put between people from Kathryn's family if their height is between $H_1$ and $H_k$ without adding any additional sum to the sum of consecutive height differences.

Then, consider the height of the tallest person in Umit's family $x$, and the height of the shortest person in Umit's family $y$. If $x > H_k$, then notice that we can just put $x$ in line directly after $H_k$, and then put all people with heights between $x$ and $H_k$ between these, and not add any additional sum (due to above). We can do this similarly for $H_1$, and after so, the remaining heights of people in Umit's family can be placed within $H_1$ to $H_k$. 

(ig this is optimal because either you place $x$ at end, or between two people of Kathryn's family, but thats worse (try prove, quite easy))

**Subtask 3** 
Similar to the observation in subtask 2, realise that every height between $\max(H_1\dots H_k)$ and $\min(H_1 \dots H_k)$ can be placed without adding any extra cost.

But we are given that the max is $2200$, and the min is $1000$, which is the min and max for heights of people in Umit's family, and since they optimally do not add any more to the sum of height differences, our answer is just the result if we just consider $H_1 \dots H_k$ as in subtask 1

**Subtask 4**
Assume that the height of the shortest person in Umit's family, $x$, is less than the height of the shortest person in Kathryn's family (otherwise we just use the obs in sub3).

Then, realise that once we place $x$ somewhere on the line, every other person in Umit's family can be placed without gaining extra sum.

Then, we can just precompute the cost if only $H_1 \dots H_k$ were placed, then try placing $x$ between each gap of $(H_1, H_2), \dots ,(H_{k-1}, H_k)$ (including before $H_1$ and after $H_k$), and calculating how much this changes the sum, and the minimum result over all positions of $x$ is our result).

**Subtask 5 (Full Solution)**
Realise that we can actually just use the same approach as subtask 4, but for the minimum height in Umit's family, and the maximum height in Umit's family.

## Q2: AIOLI
**Subtask 1**
For each query of $S$, we can just check all possible pairs of people from $A$ and $B$, giving us a worst time complexity of $O(S) \times O(N^2) = O(SN^2)$, which will pass.

**Subtask 2 and 3**
We can first go through all possible values of $i$ and $j$ for each  query ($N^2$ of these), and calculate the answer, but amortising our results, by 
- First, calculate the result for $i=1$ and all $j$ by binary searching for $i$ on $B_1, \dots, B_j$ to see how many are larger/smaller
- For $i > 1$, realise that `result(i, j) = result(i-1, j) + [how many in B_1...B_j are bigger than A_i]`, so we can just binary search for the second part of the right hand side, and keep the first part of the right hand side as we precomputed

Then, for each query $S$, we just pull out our answer from our precomputed answers as above, giving us a complexity of $O(N^2 + S)$

**Subtask 4 (Full Solution)**
I don't really know that much of an intuitive way to solve this subtask except for bashing with some math. First, we know that in each query, when we output the number of games won by a, it is actually just $ij -\text{number of games won by b}$. Then, we actually just need to only calculate the number of games won by team B.

For a query with $i$ and $j$, the games won by B is
$$\sum_{k=1}^{j}\min(i, X[k])$$
where $X[k]$ is the number of people from team A with less skill than person $B_k$ (since all values of skill are $\le 2\cdot10^5$, we can precompute this). Then, rearranging, we get
$$\sum_{\substack{k=1 \\ X[k] \le i}}^{j}X[k] + \sum_{\substack{k=1 \\ X[k] > i}}^{j}i$$

Since $X$ is monotonic (quite easy to prove), we can binary search for the first value $k$ where $X[k] > i$ for every single $i$ (precomputed) (let this value be $z$. Then, we get
$$\sum_{k=1}^{\min(0, z-1)}X[k] + \sum_{k=z}^{j}i$$

Then, we can precompute the prefix sums of $X[k]$ as $Y[k]$, further rearranging to
$$Y[\min(0, z-1)] + i(j-z+1)$$

Which we can now calculate in $O(\log N)$ (cuz of the binary search for $z$).

Therefore, our final time complexity is $O(N  + S\log N)$ or smth like that I'm not too bothered cuz it passes.

## Get Rich Quick
**Subtask 1**
Obviously we can just stimulate the process ig, in $O(N)$

**Subtask 2**
Again, we can stimulate the process for every query, giving us $O(QN)$, even though it might be a bit tight

**Subtask 3**
Notice that we can first stimulate our process from $1$ to $N-1$, storing how much starting money we needed $a$, and how much money we have at the end $b$

If $X_i > b$, then we need more starting money, specifically $a \rightarrow a+(X_i - b)$. Else, we have enough money and don't need to add anything else.

This gives us a complexity of $O(N + Q)$

**Subtask 4**
First, define $C_i$ as the amount of extra money needed to get upgrade $A_i$, assuming you have gone through $A_1$ to $A_{i-1}$.  Then, get maximum of $C_2, C_3, \dots, C_n$, as $y$. 

Then, realise that if you change $A_1$ to $B_i$, realise that the result is $\max\big(0, y - (B_i - A_1)\big)$, so you can calculate each query in $O(1)$.

**Subtask 5**
Define $C$ as in sub4. Then, make prefix and suffix maximums of $C$.

Then, for each query, the amount of starting money needed is 
$$\max\big(0, \text{pmax}[X_i - 1], B - \text{pmax}[X_i - 1], \text{smax}[X_i + 1]-(B - A_x)\big)$$

(if you consider the first $X_i - 1$ elements, then the $X_i$th element, then the elements after $X_i$)

## Pairing Cards 2
_This is a very difficult problem designed to challenge the very top students in Australia ig_ so i do not have a concrete proof of why my way works and stuff.

Basically by intuition or some sort of proof, realise that one of the following must happen:
- $S = A_1 + B_n$
- $S = A_n + B_1$
- $D = A_1 - B_1$
- $D = A_n - B_n$

Then, as another cool trick (i got this off catterpillow's solution cuz its cool), you can realise that the sum condition $A_i + B_j = S$ can be rearranged into $B_j - (-A_i) = S$ which is kinda trivial but it allows us to take the negative inverse (or perpendicular ig) of $A$ and make the sum condition a difference condition.

Then, for each of the 4 cases above, just get the two conditions, and then do the sum condition first, and pushing all _bad_ elements which can't be done into a list.

Then, just try do the difference condition and SOMEHOW this works (I did something similar in my solution but I can't actually prove that this greedy-ish approach actually works)
