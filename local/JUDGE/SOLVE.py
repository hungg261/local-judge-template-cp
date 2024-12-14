def main():
    with open("SOLVE.INP", "r") as infile:
        n,k=[int(i.strip()) for i in infile.read().strip().split('\n')]

    def format(n):
        if(n==int(n)):
            return int(n)
        return n

    outfile = open("SOLVE.OUT", "w")
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

    print(ans,file=outfile)
    outfile.close()
    
    # with open("SOLVE.ans", "w") as outfile:
    #     outfile.write(f"{(a*n*(n+1)//2+b*dsqrt(int(n**.5)))%mod}")

if __name__ == "__main__":
    main()
