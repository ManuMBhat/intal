import random


def random_number(digits):
    num = ""
    for _ in range(digits):
        temp = random.randint(0,9)
        num = num + str(temp)

    return int(num)



def main():
    digits1 = random.randint(20,100)
    digits2 = random.randint(20,100)
    intal1 = random_number(digits1)
    intal2 = random_number(digits2)
    n = random.randint(1,8)
    print(intal1)
    print(intal2)
    print(intal1 + intal2)
    with open("input.txt","w+") as outfile:
        outfile.write(str(intal1) + '\n')
        outfile.write(str(intal2) + '\n')
        outfile.write(str((intal1 + intal2)) + '\n')
        outfile.write(str(abs(intal1 - intal2)) + '\n')
        outfile.write(str(intal1 * intal2) + '\n')
        outfile.write(str(intal1 % intal2) + '\n')
        outfile.write(str(n) + '\n')
        outfile.write(str(intal1**n) + '\n')
    


if __name__ == "__main__":
    main()