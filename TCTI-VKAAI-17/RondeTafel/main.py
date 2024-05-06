import matplotlib.pyplot as plt
import random
from typing import List
import time

random.seed(0)

def generate_affinities(table : List[List[float]], sequence : List[int]) -> List[float]:
    """
        Generate pairs based on the given sequence.    
            looks up affinity in the given table for each
            in both direction and calculates the product of both directions.
    """
    pairs = zip(sequence, sequence[1:] + [sequence[0]])
    return [float(table[i][j]) * float(table[j][i]) for i,j in pairs]


def affinity(table : List[List[float]], sequence : List[int]) -> float:
    """
        Calculate fitness of sample using sum of affinities.
    """
    return sum(generate_affinities(table, sequence))


def print_affinity_stats(data : List[List], sequence : List[int]):
    """
        Output stats of the calculated affinities
    """
    pairs = zip(sequence, sequence[1:] + [sequence[0]])
    table = data[1:]
    stats = []

    for knight, nextTo in pairs:
        name = data[0][knight]
        affinityTo = table[knight][nextTo]
        affinityFrom = table[nextTo][knight]
        stats.append( (name, affinityTo, affinityFrom) )

    arthur = [*filter(lambda x: x[0] == "Arthur", stats)][0]
    arthurIndex = stats.index(arthur)
    stats = stats[arthurIndex:] + stats[:arthurIndex]
    
    for x,y,z in stats:
        print("%s (%sx%s)" % (x, y, z))
    


def find_best(table : List[List[float]], sequence : List[int]) -> List[int]:
    """
        Selects the best seat in sequence.
            returns all seats influenced by said seat.
    """
    affinities = generate_affinities(table, sequence)

    maxInd = affinities.index(max(affinities))
    # Loop around if the maxInd is equal to the "last" seat
    if maxInd == len(affinities) - 1 :
        tmp = [maxInd-1, maxInd, 0]
    else:
        tmp = [*range(maxInd-1, maxInd + 2)]

    return [sequence[x] for x in tmp]


def recombine(table : List[List[float]], a : List[int], b : List[int]) -> List[int]:
    """
        Keeps the best part of subject, takes the rest from a randomized sample.
    """
    bestA = find_best(table, a)
    bestB = find_best(table, b)

    if len( [*filter( lambda x: x in bestA, bestB )] ) == 0 :
        best = bestA + bestB
    else:
        best = bestA

    tmp = b.copy()
    for x in best:
        tmp.remove( x ) # Otherwise we might find the same combo twice

    return best + tmp


def new_sequence(data : List[List]) -> List[int]:
    """
        Generates a list containing the index of the knight assigned to seat.
    """
    tmp = list(range(0, len(data[0])))
    random.shuffle(tmp)
    return tmp

def mutate(sequence : List[float]) -> List[float]:
    """
        Mutate by randomly selecting two indexes and switching them around.  
    """
    a = random.randrange(0, len(sequence) - 1)
    b = random.randrange(0, len(sequence) - 1)
    sequence[a], sequence[b] = sequence[b], sequence[a]
    return sequence

# First we'll remove the comment contained within the file from our data
# then we'll remove the names in the affinity table.
data = [x.strip().split(";")[1:] for x in open("RondeTafel.csv", "r").readlines()[1:]]


# We'll create a starting point and loop until the required fitness is found.
# In the loop we will replace the weakest samples.
POPULATION_SIZE = 500
REPLACE_SIZE=100
population = [new_sequence(data) for x in range(POPULATION_SIZE)]

affinityTable = data[1:]
affinityHistory = [0]
currAffinity = affinityHistory[0]

start_time = time.time()
while currAffinity <= 6.8:
    
    # Calculate affinities based on affinityTable
    calculatedAffinities = [affinity(affinityTable, x) for x in population]
    
    # Combine calculated affinities and population
    zippedPopulation = zip(calculatedAffinities, population)
    
    # Sort the population based on the affinity
    sortedPopulation = sorted(zippedPopulation, key=lambda x:x[0], reverse=True)
    currAffinity, p  = sortedPopulation[0]
    
    affinityHistory.append(currAffinity)
    print("Current affinity: %f" % currAffinity, end='\r')

    # re-populate, split affinities and sequences.
    # Replace weakest by combining best and second-best with slight mutation.
    population = [p[1] for p in sortedPopulation]
    population_part = zip(population[0:REPLACE_SIZE], population[1:REPLACE_SIZE+1])
    population[-REPLACE_SIZE:0] = [recombine( affinityTable, x, mutate(y) ) for x,y in population_part]

    # Local optimum hit, regenerate whole population.
    if len( [*filter(lambda x: x == currAffinity, affinityHistory)] ) >= 25:
        population = [new_sequence(data) for x in range(POPULATION_SIZE)]
    
print("\nTook: %fs\n" % (time.time() - start_time))
plt.plot(range(len(affinityHistory)), affinityHistory)
plt.xlabel("Iterations")
plt.ylabel("Affinity")
plt.show()

print_affinity_stats(data, p)