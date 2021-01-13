# TIE-02101: Ohjelmointi 1: Johdanto
# Harjoitustyö 3.4:
# Ohjelma, joka kertoo, onko viini mennyt pilalle

def main():
    row = input("Enter the number of measurements: ")
    measurements = int(row)
    if measurements < 1:
        print("The number of measurements must be a positive number.")
        return
    i = 0
    T = str(i)
    m = 0
    M = measurements * 0.1
    n = 0

    while i < measurements:
        i += 1
        T = str(i)
        row = input("Enter the temperature " + T + ": ")
        temperature = int(row)

        if temperature >= 20 and temperature <= 25:
            n = 0
            continue

        else:
            m += 1
            n += 1

            if m > M:
                print("Your wine is ruined.")
                return

            elif n >= 2:
                print("Your wine is ruined.")
                return
    print("Your wine is ready.")

main()
