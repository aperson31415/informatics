import sys
import heapq
 
def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    n = next(it)
    d = next(it)
    s = next(it)
    A = [next(it) for i in range(n)]
 
    cnt = {}
    for x in A:
        cnt[x] = cnt.get(x, 0) + 1
 
    present = set(cnt.keys())
 
    adj = {u: set() for u in present}
    for u in list(present):
        if (u - d) in present:
            adj[u].add(u - d)
        if (u + d) in present:
            adj[u].add(u + d)
        if (s - u) in present:
            adj[u].add(s - u)
 
    adj_heap = []   
    nd_heap = []   
    for u in present:
        heapq.heappush(adj_heap, (len(adj[u]), u))
        heapq.heappush(nd_heap, u)
 
    def abrt():
        print("NO")
        sys.exit(0)
 
    def dlt(u):
        if u not in present:
            return
        present.remove(u)
        for v in list(adj[u]):   
            if v == u:
                continue
            if u in adj[v]:
                adj[v].remove(u)
                heapq.heappush(adj_heap, (len(adj[v]), v))
        adj[u].clear()
 
    def pr(u, v):
        if u == v:
            if cnt.get(u, 0) % 2 == 1:
                abrt()
            cnt[u] = 0
            dlt(u)
        else:
            xu = cnt.get(u, 0)
            xv = cnt.get(v, 0)
            if xu == 0 or xv == 0:
                abrt()
            x = min(xu, xv)
            cnt[u] = xu - x
            cnt[v] = xv - x
            if cnt[u] == 0:
                dlt(u)
            if cnt[v] == 0:
                dlt(v)
 
    while present:
        while True:
            if not adj_heap:
                abrt()
            deg, u = heapq.heappop(adj_heap)
 
            # Unlike C++, modification is implemented lazily rather than in dlt()
            if u not in present:
                continue
            cur_deg = len(adj[u])
            if cur_deg != deg:
                heapq.heappush(adj_heap, (cur_deg, u))
                continue
            break
 
        if deg == 0:
            abrt()
 
        if deg == 1:
            v = next(iter(adj[u]))
            pr(u, v)
            continue
 
        while True:
            if not nd_heap:
                abrt()
            umin = heapq.heappop(nd_heap)
            if umin in present:
                break
 
        vmin = s - umin
        if vmin not in adj.get(umin, set()):
            abrt()
        pr(umin, vmin)
    print("YES")
 
main()
