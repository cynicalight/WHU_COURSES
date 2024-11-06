# from 2, delete all multiples of the primes until N 
def all_primes(n):
    allNum = list(range(1,n+1))
    print(allNum)
    primeTest = 2
    i = 2
    while primeTest <= (n**0.5):
        allNum = allNum[:i+1] + [num for num in allNum[i+1:] if num % primeTest != 0]
        primeTest = allNum[i]
        i += 1
        
    for zj in allNum:
        print(zj)
            
    
print("求n以内的所有素数")
n = input("n = ")
n = int(n)
all_primes(n)