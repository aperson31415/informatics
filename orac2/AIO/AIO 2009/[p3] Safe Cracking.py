# Get the input
a, b = map(int, input().split())
code_sheet = [int(input()) for i in range(a)]
looked_at = [int(input()) for i in range(b)]
 
# Set the looked pos to the smallest ones, to calculate difference
min_looked = min(looked_at)
modified_looked = [i-min_looked for i in looked_at]
 
for i in range(len(code_sheet) - len(looked_at) + 1):
    curr_seq = code_sheet[i:i+len(looked_at)] # The ith possible seqence
    # Now modify set as same way as looked at
    min_curr = min(curr_seq)
    modified_curr = [i-min_curr for i in curr_seq]
    # Test if these 2 are equal
    if modified_curr == modified_looked:
        increment = curr_seq[0] - looked_at[0]
        if increment >= 0:
            # This sequence is correct!
            break
 
# Now that we have the sequence, just generate values using increment and sheet
vals = []
for i in code_sheet:
    vals.append(i-increment)
 
print('\n'.join(map(str, vals)))
