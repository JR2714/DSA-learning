def printOut(n):
    if (n >= 10):
        printOut(n / 10)
    print(int(n % 10),end="")

printOut(782112123123)
