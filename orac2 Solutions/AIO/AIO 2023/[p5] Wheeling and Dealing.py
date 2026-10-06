import sys
import heapq
 
input = sys.stdin.readline; _write = sys.stdout.write
def print(*args, sep:str=' ', end:str='\n'):
    _write(sep.join(map(str, args)) + end)
 
def solve():
    N, M = map(int, input().split())
    V = list(map(int, input().split()))
    P = list(map(int, input().split()))
 
    costs = [[] for _ in range(N+1)]
    for i in range(M): costs[V[i]].append(P[i])
    for c in range(1, N+1): costs[c].sort()
 
    # Build a flattened list of all voters not voting for candidate 1,
    # and bucket[t_at] = list of uids whose "mandatory threshold" is t_at.
    cost_by_id = []
    bucket = [[] for _ in range(M+1)]  # using indices 1..M for t_at
    uid = 0
    for c in range(2, N+1):
        s = len(costs[c])
        for idx in range(s):
            cost_by_id.append(costs[c][idx])
            t_at = s - idx               # voter is mandatory for any t <= t_at
            if 1 <= t_at <= M:
                bucket[t_at].append(uid)
            uid += 1
 
    total_other = len(cost_by_id)
    # Start with t = 1: every non-1 voter is mandatory -> assume all bribed initially
    used_mandatory = [True] * total_other
    spent = sum(cost_by_id)
    votes_for_1 = len(costs[1]) + total_other
 
    # min-heap of released / available voters (costs)
    pq = []
    answer = float('inf')
 
    # Iterate t from 1..M. For t we need all voters with t_at >= t to be mandatory.
    # As t increases, some voters are "released" (no longer mandatory) and go into pq.
    for t in range(1, M+1):
        if t > 1:
            # release voters whose t_at == t-1 (they stop being mandatory now)
            for uid_rel in bucket[t-1]:
                if used_mandatory[uid_rel]:
                    used_mandatory[uid_rel] = False
                    spent -= cost_by_id[uid_rel]
                    votes_for_1 -= 1
                    heapq.heappush(pq, cost_by_id[uid_rel])
 
        # If votes_for_1 < t, bribe cheapest available voters from pq
        while votes_for_1 < t and pq:
            c = heapq.heappop(pq)
            spent += c
            votes_for_1 += 1
 
        if votes_for_1 >= t:
            answer = min(answer, spent)
 
    if answer == float('inf'): answer = 0
    
    print(answer)
 
if __name__ == "__main__":
    solve()
