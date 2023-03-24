import sys
print(sys.argv)
limit = int(sys.argv[1])
count, n = 0, 0
while True:
    for ch in sys.stdin.read(100000):
        match ch:
            case '(': count += 1
            case ')': count -= 1
        assert 0 <= count <= limit
    n = n + 100000
    print(f'{n} Ok.')
