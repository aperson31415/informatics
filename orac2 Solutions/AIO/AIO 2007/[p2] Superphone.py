N = int(input())
moving_costs = [list(map(int, input().split())) for _ in range(N - 1)]
moving_costs.append([int(input())])
 
optimal: list[list] = [[-1, -1] for _ in range(N)]
optimal[0] = [0, moving_costs[0][1]]
 
# Do the optimal loop thingy
for i in range(1, N - 1):
    optimal[i][0] = min(optimal[i-1][1] + moving_costs[i-1][2], optimal[i-1][0] + moving_costs[i-1][0] + moving_costs[i][1])
    optimal[i][1] = min(optimal[i-1][0] + moving_costs[i-1][0], optimal[i-1][1] + moving_costs[i-1][2] + moving_costs[i][1])
 
# Edge case instead of [1], its [0] at the end
optimal[N - 1][0] = min(optimal[N - 2][1] + moving_costs[N - 2][2], optimal[N - 2][0] + moving_costs[N - 2][0] + moving_costs[N - 1][0])
optimal[N - 1][1] = min(optimal[N - 2][0] + moving_costs[N - 2][0], optimal[N - 2][1] + moving_costs[N - 2][2] + moving_costs[N - 1][0])
 
print(optimal[-1][1])
