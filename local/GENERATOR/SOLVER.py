with open("SOLVE.INP","r") as f:
    n, k = [int(i) for i in f.read().strip().split('\n')]
    start = 2 * k * (k - 1) + 1
    ans = start

    low1 = n * (n - 1) // 2 + 1 - (n - k + n - 2) * (n - 2 - n + k + 1) // 2
    high1 = low1 + (n - k + 1) - 2 * (k - 1) - 1

    if low1 != high1:
        ans += (low1 + high1) * (high1 - low1 + 1) // 2

    low2 = 2 * k - 1
    high2 = n - k - 1

    if low2 <= high2:
        m = high2 - low2 + 1
        ans += start * m + low2 * m * (m + 1) // 2 + m * (m * m - 1) // 6
        ans += start * m + (low2 + 1) * m * (m + 1) // 2 + m * (m * m - 1) // 6


with open("SOLVE.OUT","w") as f:
    print(ans,file=f)
