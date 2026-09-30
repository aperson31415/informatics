import sys
 
sys.setrecursionlimit(300000)
 
def solve():
    # Fast I/O
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    N = int(input_data[0])
    T_original = [int(x) for x in input_data[1:N+1]]
    
    M = int(input_data[N+1])
    S = [int(x) for x in input_data[N+2:N+2+M]]
    
    # A valid target sequence must be non-decreasing
    for i in range(M - 1):
        if S[i] > S[i + 1]:
            print("NO")
            return
            
    # Add dummy boundary tiles to avoid bounds-checking overhead
    MAX_VAL = 200005
    T = [MAX_VAL] + T_original + [MAX_VAL]
    
    # Run-length encode the target sequence
    unique_S = []
    counts = []
    for s in S:
        if not unique_S or s != unique_S[-1]:
            unique_S.append(s)
            counts.append(1)
        else:
            counts[-1] += 1
            
    # Group indices by tile values
    indices = [[] for _ in range(MAX_VAL + 1)]
    for i in range(1, N + 1):
        val = T[i]
        if val <= MAX_VAL:
            indices[val].append(i)
            
    U_0 = unique_S[0]
    x_0 = counts[0]
    
    # State array: tracks which stage 'k' of unique_S a tile is currently active in
    active = [-1] * (N + 2)
    for i in indices[U_0]:
        if x_0 == 1:
            active[i] = 0
        else:
            # Special check for multiple starting records:
            # Requires at least one immediate neighbor to bounce steps safely.
            if T[i - 1] <= U_0 or T[i + 1] <= U_0:
                active[i] = 0
                
    # DSU Setup for instant barrier lookups
    parent_R = list(range(N + 2))
    parent_L = list(range(N + 2))
    
    # Iterative Path Compression Find (prevents deep recursion)
    def find_R(i):
        path = []
        curr = i
        while parent_R[curr] != curr:
            path.append(curr)
            curr = parent_R[curr]
        for node in path:
            parent_R[node] = curr
        return curr
 
    def find_L(i):
        path = []
        curr = i
        while parent_L[curr] != curr:
            path.append(curr)
            curr = parent_L[curr]
        for node in path:
            parent_L[node] = curr
        return curr
        
    current_max_val_processed = 0
    
    # Unions tiles that are now valid stepping stones (≤ limit_val) to their neighbors
    def process_up_to(limit_val):
        nonlocal current_max_val_processed
        for v in range(current_max_val_processed + 1, limit_val + 1):
            if v < len(indices):
                for idx in indices[v]:
                    parent_R[idx] = find_R(idx + 1)
                    parent_L[idx] = find_L(idx - 1)
        current_max_val_processed = limit_val
 
    # Traverse between unique sequence states
    for k in range(len(unique_S) - 1):
        prev_V = unique_S[k]
        V = unique_S[k + 1]
        x = counts[k]
        
        # Merge all elements up to prev_V as traversable tiles 
        process_up_to(prev_V)
        has_active = False
        
        if prev_V < len(indices):
            for j in indices[prev_V]:
                # If tile 'j' is active at the current stage
                if active[j] == k:
                    # Instantly find the nearest barrier to the left
                    L = find_L(j)
                    if T[L] == V:
                        d = j - L
                        # Verify we have enough steps and that we can exhaust even permutations
                        if d <= x and d % 2 == x % 2:
                            active[L] = k + 1
                            has_active = True
                            
                    # Instantly find the nearest barrier to the right
                    R = find_R(j)
                    if T[R] == V:
                        d = R - j
                        if d <= x and d % 2 == x % 2:
                            active[R] = k + 1
                            has_active = True
                            
        # Impossible to proceed to the required next integer in the sequence
        if not has_active:
            print("NO")
            return
            
    # Final check on whether the ultimate sequence target survives
    last_V = unique_S[-1]
    expected_k = len(unique_S) - 1
    
    if last_V < len(indices):
        for i in indices[last_V]:
            if active[i] == expected_k:
                print("YES")
                return
                
    print("NO")
 
if __name__ == '__main__':
    solve()
