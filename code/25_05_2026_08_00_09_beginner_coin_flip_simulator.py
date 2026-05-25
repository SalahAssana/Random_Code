import random
import statistics

# Set the number of coin flips to simulate
num_flips = 10000

# Initialize lists to store the results
heads = []
tails = []

for _ in range(num_flips):
    flip = random.randint(0, 1)
    if flip == 0:
        heads.append('H')
        tails.append('T')
    else:
        heads.append('T')
        tails.append('H')

# Calculate and print the probability of heads
heads_count = len(heads)
print(f'Heads: {heads_count} out of {num_flips}')
print(f'Probability of Heads: {(heads_count / num_flips):.4f}')

# Calculate and print the mean of the results
mean_heads = statistics.mean([1 if h == 'H' else 0 for h in heads])
print(f'Mean of Heads: {mean_heads:.4f}')