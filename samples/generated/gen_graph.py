from random import randint, choice

MAX_VERTICES = 10

for i in range(100):
    case = open('input' + str(i + 1) + '.txt', 'w')
    n = randint(2, MAX_VERTICES)
    m = randint(1, n - 1)
    case.write(str(n) + '\n')
    case.write(str(m * n) + '\n')
    for v1 in range(1, n + 1):
        possible_neighbours = list(range(1, n + 1))
        possible_neighbours.remove(v1)
        for k in range(m):
            v2 = choice(possible_neighbours)
            possible_neighbours.remove(v2)
            case.write(str(v1) + ' ' + str(v2) + '\n')
    case.close()    