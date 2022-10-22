from math import log

n = int(input())

# if (n <= 1): print(1)
# else:        print(int(log(n) / log(6)) + 1)


if (n <= 1): print(1)
else:
    l, r = int(0), int(750000);
    while r - l > 1:
        m = (l + r) // 2
        if 6**m > n:
            r = m
        else:
            l = m
    print(int(r))
        
