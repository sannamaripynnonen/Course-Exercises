# TIE-02101: Ohjelmointi 1: Johdanto
# Harjoitustyö 6.2:
# Ohjelma, joka tulostaa tenttiin osallistuneiden opiskelijoiden
# kokonaisarvosanoista yksinkertaisen pylväsdiagrammin


def ind_scores(maks):
    """
    Funktio kysyy opiskelijoiden pisteet, kunnes syötettään tyhjä rivi.

    :param maks: Tuo funktiosta grade_ranges maksimipistemäärä
    :return: Palauttaa opiskelijoiden pisteet listana
    """

    print("Please input the scores for individual students. ")
    print("Finish by entering an empty line. ")
    arvosanat = []
    i = 1

    loppu = False
    while not loppu:
        rivi = (input(f"Input the exam score for student {i:.0f}: "))

        if rivi == "":
            print("Finished reading the scores. ")
            loppu = True

        else:
            luku = float(rivi)
            i += 1
            arvosanat.append(luku)

            if luku < 0:
                print(f"Entered value {luku:.0f} is not valid. Program "
                      f"terminating. ")
                return -1

            elif luku > maks:
                print(
                    f"Entered value {luku:.0f} is not valid. Program "
                    f"terminating. ")
                return -1

    if arvosanat == []:
        print()
        print("No students to process. Program terminating.")
        return -1

    return arvosanat


def count_grades(pisteet, pisterajat):
    """
    Funktio ilmoittaa opiskelijoiden arvosanajakauman.

    :param pisteet: Tuo funktiosta ind_scores opiskelijoiden pisteet
    :param pisterajat: Tuo funktiosta grade_ranges arvosanarajat
    :return: Palauttaa opiskelijoiden arvosanajakauman listana
    """

    n = 0
    m = 0
    o = 0
    p = 0
    q = 0
    r = 0

    for piste in pisteet:
        if piste <= pisterajat[0]:
            n += 1
        if pisterajat[0] < piste <= pisterajat[1]:
            m += 1
        if pisterajat[1] < piste <= pisterajat[2]:
            o += 1
        if pisterajat[2] < piste <= pisterajat[3]:
            p += 1
        if pisterajat[3] < piste <= pisterajat[4]:
            q += 1
        if pisterajat[4] < piste:
            r += 1

    lukumaarat = [n, m, o, p, q, r]

    return lukumaarat


def diagram(lkm):
    """
    Funktio piirtää tenttiarvostelun pylväsdiagrammin.

    :param lkm: Tuo funktiosta count_grades opiskelijoiden arvosanajakauman
    :return:
    """

    i = 0

    while i <= 5:
        print(f"{i:.0f}", f"{lkm[i]:3d}", "#"*lkm[i])
        i += 1


def grade_ranges():
    """
    Funktio kysyy käyttäjältä tentin arvosanarajat.

    :return: palauttaa arvosanarajat listana
    """

    print("Please input the grade ranges.")
    i = 0
    pisterajat = []
    edellinen = -1

    while i <= 5:
        row = int(input(f"Maximum score qualifying for grade {i:.0f}: "))
        pisterajat.append(row)
        i += 1

        if row <= edellinen:
            print("Entered value", row, "is not valid. Program terminating.")
            return -1

        edellinen = row

        if row < 0:
            print("Entered value", row, "is not valid. Program terminating.")
            return -1

    print("Finished reading the grade ranges.")

    return pisterajat


def main():
    pisterajat = grade_ranges()

    if pisterajat != -1:
        max_pisteet = pisterajat[5]
        print()
        osallistujien_pisteet = ind_scores(max_pisteet)

        if osallistujien_pisteet != -1:
            lasketut_arvosanat = count_grades(osallistujien_pisteet,
                                              pisterajat)
            print()
            diagram(lasketut_arvosanat)


main()
