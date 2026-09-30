total_people, beam_width = map(int, input().split())
people_positions = [int(input()) for _ in range(total_people)]
 
starting_index = 0
ending_index = 0
current_people_captured = 1
current_beam_distance_needed = 0
max_people_captured = -1
done = 0
 
while starting_index < len(people_positions) and ending_index < len(people_positions):
    while current_beam_distance_needed < beam_width:
        if ending_index >= len(people_positions) - 1:
            #print('done')
            done = 1
            break;
        ending_index += 1
        current_people_captured += 1
        #print(starting_index, ending_index, current_people_captured)
        current_beam_distance_needed = 1 + people_positions[ending_index] - people_positions[starting_index]
 
    if current_beam_distance_needed > beam_width:
        ending_index -= 1
        current_people_captured -= 1
        current_beam_distance_needed = 1 + people_positions[ending_index] - people_positions[starting_index]
    
    if current_people_captured > max_people_captured:
        max_people_captured = current_people_captured
 
    if done:
        break
 
    if starting_index == len(people_positions) - 1:
        break
 
    starting_index += 1
    current_people_captured -= 1
    current_beam_distance_needed = 1 + people_positions[ending_index] - people_positions[starting_index]
 
print(max_people_captured)
