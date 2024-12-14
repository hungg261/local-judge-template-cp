mod = 10**9+7
def main():
    with open("SOLVE.INP", "r") as infile:
        a,b,c=map(int,infile.read().strip().split())

    def format(n):
        if(n==int(n)):
            return int(n)
        return n

    def modular_exponentiation(base, exponent, modulus):
        """Calculates (base^exponent) % modulus efficiently.

        Args:
            base: The base number.
            exponent: The exponent.
            modulus: The modulus.

        Returns:
            The result of (base^exponent) % modulus.
        """

        result = 1
        base %= modulus

        while exponent > 0:
            if exponent % 2 == 1:
                result = (result * base) % modulus
            exponent //= 2
            base = (base * base) % modulus

        return result

    result = modular_exponentiation(a, b, c)
    outfile = open("SOLVE.ans", "w")
    print(result,file=outfile)

    # print((a**b)%c,file=outfile)
    # print("Chia het cho 369" if n%369==0 else "Khong chia het cho 369",file=outfile)
    outfile.close()
    
    # with open("SOLVE.ans", "w") as outfile:
    #     outfile.write(f"{(a*n*(n+1)//2+b*dsqrt(int(n**.5)))%mod}")

if __name__ == "__main__":
    main()
