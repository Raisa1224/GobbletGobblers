#include "graphics.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int strategie = 0, caz, subcaz, numarPieseMari1, numarPieseMedii1, numarPieseMici1, numarPieseMari2, numarPieseMedii2, numarPieseMici2;
int stadiul = 0, jucatorul = 2, tur = 0;

int player1 = 1, player2 = 1, currentPlayer;

int difLeftLev = 1, difRightLev = 1;

struct globalMove {
    int fl, fc, ol, oc, type, decision;
    bool change;
} g;

struct mutarea
{
    int tip; ///1=pus piesa, 2=mutat piesa
    int l; ///linie
    int c; ///coloana
    int ci, cf, li, lf;
    int dimensiuneaPiesei;
}mutareaAnterioara;

struct stiva
{
    int player;
    int dimensiune;

};

struct matrice
{
    int jucator;
    int marimePiesa;
    stiva piese[3]; ///trebuie retinuta piesa de sub piesa curenta. poti sa ai mai multe piese una peste alta;

} a[3][3], b[3][3], c[3][3];
///b este matricea auxiliara pentru rotiri

void homeScreen();
void muta_o_piesa(matrice a[3][3], int liniaInitiala, int coloanaInitiala, int liniaFinala, int coloanaFinala);
int verifica_daca_mai_are_un_tip_de_piese(int marime, int jucatorul);
int verifica_daca_se_poate_pune_o_piesa(matrice a[3][3], int linie, int coloana, int jucatorul, int marime);
void pune_o_piesa(matrice a[3][3], int linie, int coloana, int jucatorul, int marime);

///////////////////////////////
// HARD STRATEGY STARTS HERE
///////////////////////////////

void muta_piesa_auxiliar_strat(matrice a[][3], matrice b[][3], int liniaInitiala, int coloanaIitiala, int liniaFinala, int coloanaFinala);
void rotire_stanga_strat(matrice a[3][3], matrice b[3][3]);
void rotire_dreapta_strat(matrice a[3][3], matrice b[3][3]);
void afisare_strat(matrice a[3][3]);
void adaugare_strat(stiva piese[3], int jucatorul, int marime);
void stergere_strat(stiva piese[3]);
int verifica_daca_a_castigat_strat(matrice a[3][3]);
void pune_o_piesa_strat(matrice a[3][3], int linie, int coloana, int jucatorul, int marime);
int verifica_daca_mai_are_piese_mici_strat(int jucator);
int verifica_daca_mai_are_piese_medii_strat(int jucator);
int verifica_daca_mai_are_piese_mari_strat(int jucator);
int verifica_daca_mai_are_un_tip_de_piese_strat(int marime, int jucatorul);
int verifica_daca_se_poate_pune_o_piesa_strat_strat(matrice a[3][3], int linie, int coloana, int jucatorul, int marime);
int verifica_daca_piesa_are_marimea_corecta_strat(int marime);
void muta_o_piesa_strat(matrice a[3][3], int liniaInitiala, int coloanaInitiala, int liniaFinala, int coloanaFinala);
int verifica_daca_vrea_sa_mute_piesa_lui_strat(matrice a[3][3], int jucatorul, int linie, int coloana);
int verifica_daca_mai_are_piese_strat(int jucator);
void strategia1_strat(matrice a[3][3], int& tur);
void strategia13_strat(matrice a[3][3], int& tur, int& caz);
void strategia17_strat(matrice a[3][3], int& tur, int& caz, int& subcaz);
void strategia5_strat(matrice a[3][3], int& tur, int& caz, int& subcaz);
void strategia21_strat(matrice a[3][3], int& tur);
void strategia9_strat(matrice a[3][3], int& tur);
void strategia4_strat(int& tur);
void strategia3_strat(int& tur);
void strategia2_strat(int& tur);
void strategia6_strat(int& tur);
void strategia8_strat(int& tur);
void strategia7_strat(int& tur);
void strategia11_strat(int& tur);
void strategia12_strat(int& tur);
void strategia10_strat(int& tur);
void strategia14_strat(int& tur);
void strategia16_strat(int& tur);
void strategia15_strat(int& tur);
void strategia18_strat(int& tur);
void strategia20_strat(int& tur);
void strategia19_strat(int& tur);
void strategia22_strat(int& tur);
void strategia23_strat(int& tur);
void strategia24_strat(int& tur);
int Alegestrategia1_strat();
int Alegestrategia2_strat();
int Alegestrategia3_strat();
void mutarea_calculatorului_strat(matrice a[3][3], int& tur);
void tabla_goala_strat(matrice a[3][3]);
void randul_jucatorului_strat(matrice a[3][3]);


void muta_piesa_auxiliar_strat(matrice a[][3], matrice b[][3], int liniaInitiala, int coloanaIitiala, int liniaFinala, int coloanaFinala)
{

    ///copiem in matricea auxiliara stiva de pe pozitia data
    b[liniaFinala][coloanaFinala].piese[0].player = a[liniaInitiala][coloanaIitiala].piese[0].player;
    b[liniaFinala][coloanaFinala].piese[1].player = a[liniaInitiala][coloanaIitiala].piese[1].player;
    b[liniaFinala][coloanaFinala].piese[2].player = a[liniaInitiala][coloanaIitiala].piese[2].player;
    b[liniaFinala][coloanaFinala].piese[0].dimensiune = a[liniaInitiala][coloanaIitiala].piese[0].dimensiune;
    b[liniaFinala][coloanaFinala].piese[1].dimensiune = a[liniaInitiala][coloanaIitiala].piese[1].dimensiune;
    b[liniaFinala][coloanaFinala].piese[2].dimensiune = a[liniaInitiala][coloanaIitiala].piese[2].dimensiune;
    b[liniaFinala][coloanaFinala].jucator = b[liniaFinala][coloanaFinala].piese[0].player;
    b[liniaFinala][coloanaFinala].marimePiesa = b[liniaFinala][coloanaFinala].piese[0].dimensiune;

}

void rotire_stanga_strat(matrice a[3][3], matrice b[3][3])
{
    int i, j, liniaInitiala, liniaFinala, coloanaInitiala, coloanaFinala;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; j++)
        {   ///b[i][j]=a[j][2-i]
            liniaInitiala = j;
            liniaFinala = i;
            coloanaInitiala = 3 - 1 - i;
            coloanaFinala = j;
            muta_piesa_auxiliar_strat(a, b, liniaInitiala, coloanaInitiala, liniaFinala, coloanaFinala);
        }
}

void rotire_dreapta_strat(matrice a[3][3], matrice b[3][3])
{
    int i, j, liniaInitiala, liniaFinala, coloanaInitiala, coloanaFinala;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {///b[i][j]=a[2-j][i]
            liniaInitiala = 3 - j - 1;
            liniaFinala = i;
            coloanaInitiala = i;
            coloanaFinala = j;
            muta_piesa_auxiliar_strat(a, b, liniaInitiala, coloanaInitiala, liniaFinala, coloanaFinala);
        }
}


void afisare_strat(matrice a[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            cout << a[i][j].jucator << " ";
        cout << "\n";
    }
}

void adaugare_strat(stiva piese[3], int jucatorul, int marime)
{
    piese[2].player = piese[1].player;
    piese[2].dimensiune = piese[1].dimensiune;
    piese[1].player = piese[0].player;
    piese[1].dimensiune = piese[0].dimensiune;

    piese[0].player = jucatorul;
    piese[0].dimensiune = marime;
}

void stergere_strat(stiva piese[3])
{

    piese[0].player = piese[1].player;
    piese[0].dimensiune = piese[1].dimensiune;
    piese[1].player = piese[2].player;
    piese[1].dimensiune = piese[2].dimensiune;
    piese[2].player = 0;
    piese[2].dimensiune = 0;
}

int verifica_daca_a_castigat_strat(matrice a[3][3])
{
    int i, j;

    for (i = 0; i < 3; ++i)
    {
        if ((a[i][0].jucator == a[i][1].jucator) && (a[i][1].jucator == a[i][2].jucator) && (a[i][0].jucator != 0)) return 1;
    }
    for (j = 0; j < 3; j++)
    {
        if ((a[0][j].jucator == a[1][j].jucator) && (a[1][j].jucator == a[2][j].jucator) && (a[0][j].jucator != 0)) return 1;
    }
    if ((a[0][0].jucator == a[1][1].jucator) && (a[1][1].jucator == a[2][2].jucator) && (a[0][0].jucator != 0)) return 1;
    if ((a[2][0].jucator == a[1][1].jucator) && (a[1][1].jucator == a[0][2].jucator) && (a[2][0].jucator != 0)) return 1;
    return 0;
}


void pune_o_piesa_strat(matrice a[3][3], int linie, int coloana, int jucatorul, int marime)
{

    cout << endl << "SE PUNE O PIESA DE LA RAISA cu MARIMEA: " << marime;
    cout << endl << "LA POZITIA: " << linie << " " << coloana;

    g.fl = linie;
    g.fc = coloana;
    g.decision = 0;
    g.type = marime;
    g.change = true;

    a[linie][coloana].jucator = jucatorul;
    a[linie][coloana].marimePiesa = marime;
    adaugare_strat(a[linie][coloana].piese, jucatorul, marime);
    cout << endl << "FRESH DUPA ADAUGARE: ";
    cout << endl;
    afisare_strat(a);
    if (jucatorul == 1)
    {
        if (marime == 1) numarPieseMici1++;
        else
        {
            if (marime == 3) numarPieseMari1++;
            else numarPieseMedii1++;
        }
    }
    else
    {
        if (marime == 1) numarPieseMici2++;
        else
        {
            if (marime == 3) numarPieseMari2++;
            else numarPieseMedii2++;
        }
    }
}

int verifica_daca_mai_are_piese_mici_strat(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMici1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMici2 == 2) return 0;
        return 1;
    }
}

int verifica_daca_mai_are_piese_medii_strat(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMedii1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMedii2 == 2) return 0;
        return 1;
    }
}

int verifica_daca_mai_are_piese_mari_strat(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMari1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMari2 == 2) return 0;
        return 1;
    }
}

int verifica_daca_mai_are_un_tip_de_piese_strat(int marime, int jucatorul)
{
    if (marime == 1)
    {
        if (verifica_daca_mai_are_piese_mici_strat(jucatorul) == 0) return 0;
        return 1;
    }
    else
    {
        if (marime == 2)
        {
            if (verifica_daca_mai_are_piese_medii_strat(jucatorul) == 0) return 0;
            return 1;
        }

        else
        {
            if (verifica_daca_mai_are_piese_mari_strat(jucatorul) == 0) return 0;
            else return 1;
        }
    }
}
int verifica_daca_se_poate_pune_o_piesa_strat_strat(matrice a[3][3], int linie, int coloana, int jucatorul, int marime)
{

    if (a[linie][coloana].jucator == 0) return 1;
    if (a[linie][coloana].marimePiesa >= marime) return 0;
    return 1;
}

int verifica_daca_piesa_are_marimea_corecta_strat(int marime)
{
    if (marime < 1 || marime>3) return 0;
    return 1;
}

void muta_o_piesa_strat(matrice a[3][3], int liniaInitiala, int coloanaInitiala, int liniaFinala, int coloanaFinala)
{

    g.fl = liniaFinala;
    g.fc = coloanaFinala;
    g.ol = liniaInitiala;
    g.oc = coloanaInitiala;
    g.decision = 1;
    g.change = true;

    a[liniaFinala][coloanaFinala].jucator = a[liniaInitiala][coloanaInitiala].jucator;
    a[liniaFinala][coloanaFinala].marimePiesa = a[liniaInitiala][coloanaInitiala].marimePiesa;
    adaugare_strat(a[liniaFinala][coloanaFinala].piese, a[liniaFinala][coloanaFinala].jucator, a[liniaFinala][coloanaFinala].marimePiesa);
    stergere_strat(a[liniaInitiala][coloanaInitiala].piese);
    a[liniaInitiala][coloanaInitiala].jucator = a[liniaInitiala][coloanaInitiala].piese[0].player;
    a[liniaInitiala][coloanaInitiala].marimePiesa = a[liniaInitiala][coloanaInitiala].piese[0].dimensiune;

}

int verifica_daca_vrea_sa_mute_piesa_lui_strat(matrice a[3][3], int jucatorul, int linie, int coloana)
{
    if (a[linie][coloana].jucator != jucatorul) return 0;
    return 1;
}

int verifica_daca_mai_are_piese_strat(int jucator)
{
    if (verifica_daca_mai_are_piese_mari_strat(jucator) == 1 || verifica_daca_mai_are_piese_medii_strat(jucator) == 1 || verifica_daca_mai_are_piese_mici_strat(jucator) == 1) return 1;
    return 0;
}

void strategia1_strat(matrice a[3][3], int& tur)
{
    int dimensiune = 0, linia = 0, coloana = 0, calculator = 2;
    if (tur == 1)
    {
        dimensiune = 3; linia = 2; coloana = 0;
        pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
    }

    if (tur == 2)
    {
        if (mutareaAnterioara.tip == 1)
        {
            if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2)
            {
                if (mutareaAnterioara.dimensiuneaPiesei == 3)
                {
                    caz = 2;
                    linia = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    cout << "\n" << "punem piesa la " << linia << " " << coloana << "\n";
                }
                else
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 2)
                    {
                        caz = 1;
                        int li, lf, ci, cf;
                        li = 2; ci = 0; lf = 0; cf = 2;
                        muta_o_piesa_strat(a, li, ci, lf, cf);
                    }
                    else
                    {
                        linia = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                linia = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }

        }
        else
        {
            if (mutareaAnterioara.lf == 0 && mutareaAnterioara.cf == 2)
            {
                caz = 3; dimensiune = 2; linia = 1; coloana = 0; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            }
            else
            {
                linia = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
        }

    }

    if (tur == 3)
    {
        if (caz == 3)
        {
            if (mutareaAnterioara.tip == 1)
            {
                if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 0)
                {
                    linia = 2; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                }
                else
                {
                    if (a[0][0].jucator == 0)
                    {
                        linia = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                linia = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
        else
        {
            if (caz == 2)
            {
                if (mutareaAnterioara.tip == 2)
                {
                    if ((mutareaAnterioara.li == 2) && (mutareaAnterioara.ci == 1) && (mutareaAnterioara.lf == 1) && (mutareaAnterioara.cf == 0))
                    {
                        linia = 2; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        if (a[1][0].jucator == 2)
                        {
                            if (a[0][0].jucator == 0)
                            {
                                linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am castigat
                            }
                            else
                            {
                                if (a[1][2].jucator == 0)
                                {
                                    linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                    ///am castigat
                                }
                                else
                                {
                                    if (a[0][2].jucator == 0)
                                    {
                                        linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                        ///am cstigat
                                    }
                                }

                            }
                        }
                    }
                }
                else
                {
                    if (a[0][0].jucator == 0)
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                }
            }
            else
            {
                if (mutareaAnterioara.tip == 2)
                {
                    if ((mutareaAnterioara.li == 2) && (mutareaAnterioara.ci == 1) && (mutareaAnterioara.lf == 2) && (mutareaAnterioara.cf == 0))
                    {
                        subcaz = 3; linia = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linia = 2; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
                else
                {
                    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 0)
                    {
                        if (mutareaAnterioara.dimensiuneaPiesei == 3)
                        {
                            subcaz = 2;
                            dimensiune = 2; linia = 2; coloana = 2;
                            pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            if (mutareaAnterioara.dimensiuneaPiesei == 2)
                            {
                                subcaz = 1;
                                int li, lf, ci, cf;
                                li = 1; ci = 1; lf = 2; cf = 0;
                                muta_o_piesa_strat(a, li, ci, lf, cf);
                            }
                            else
                            {
                                linia = 2; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am castigat
                            }
                        }
                    }
                    else
                    {
                        linia = 2; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }

        }
    }

    if (tur == 4)
    {
        if (caz == 3)
        {
            if (mutareaAnterioara.tip == 1)
            {
                if (a[0][1].jucator == 0)
                {
                    linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am caqstigat
                }
            }
            else
            {
                if (a[2][0].jucator == 0)
                {
                    linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[0][0].jucator == 0)
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        else
        {
            if (caz == 2)
            {
                if (mutareaAnterioara.tip == 1)
                {
                    if (a[2][2].jucator == 0)
                    {
                        linia = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
                else
                {
                    if (a[0][2].jucator == 0)
                    {
                        linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        if (a[0][0].jucator == 0)
                        {
                            linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///am castigat
                        }
                        else
                        {
                            linia = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///am castigat
                        }
                    }
                }
            }
            else
            {
                if (subcaz == 3)
                {
                    if (mutareaAnterioara.tip == 2)
                    {
                        linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 2)
                        {
                            dimensiune = 2; linia = 0; coloana = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            if (a[2][2].jucator == 0)
                            {
                                linia = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am castigat
                            }
                            else
                            {
                                linia = 1; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am castigat
                            }
                        }
                    }
                }
                else
                {
                    if (subcaz == 2)
                    {
                        if (mutareaAnterioara.tip == 2)
                        {
                            if ((mutareaAnterioara.li == 2) && (mutareaAnterioara.ci == 1) && (mutareaAnterioara.lf == 2) && (mutareaAnterioara.cf == 2))
                            {
                                linia = 2;
                                coloana = 1;
                                dimensiune = 2;
                                pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            }
                            else
                            {
                                if (a[2][0].jucator == 0)
                                {
                                    linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                    ///am castigat
                                }
                                else
                                {
                                    if (a[0][0].jucator == 0)
                                    {
                                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                        ///am castigat
                                    }
                                    else
                                    {
                                        linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                        ///am castigat
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (a[0][0].jucator == 0)
                            {
                                linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am castigat
                            }
                            else
                            {
                                linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am castigat
                            }
                        }
                    }
                    else
                    {
                        if (subcaz == 1)
                        {
                            if (mutareaAnterioara.tip == 2)
                            {
                                if (mutareaAnterioara.lf == 1 && mutareaAnterioara.cf == 1)
                                {
                                    subcaz = 6;
                                    dimensiune = 2; linia = 2; coloana = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                }
                                else
                                {
                                    dimensiune = 1; linia = 1; coloana = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                    ///am castigat
                                }
                            }
                            else
                            {
                                if ((mutareaAnterioara.l == 1) && (mutareaAnterioara.c == 1))
                                {
                                    if (mutareaAnterioara.dimensiuneaPiesei == 3)
                                    {
                                        linia = 0; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                    }
                                    else
                                    {
                                        linia = 1; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                        ///am castigat
                                    }
                                }
                                else
                                {
                                    linia = 1; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                    ///am castigat
                                }
                            }
                        }
                    }
                }

            }




        }

    }

    if (tur == 5)
    {
        if (subcaz == 3)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (a[0][0].jucator == 0)
                {
                    linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    linia = 2; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
            }
        }
        else
        {
            if (subcaz == 2)
            {
                if (mutareaAnterioara.tip == 2)
                {
                    if (a[2][0].jucator == 0)
                    {
                        linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        if (a[1][2].jucator == 0)
                        {
                            linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///am castigat
                        }
                        else
                        {
                            linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///am cstigat
                        }
                    }
                }
                else
                {
                    int li, ci, lf, cf;
                    li = 0; ci = 2; lf = 0; cf = 1;
                    muta_o_piesa_strat(a, li, ci, lf, cf);
                    ///am castigat
                }
            }
            else
            {
                if (subcaz == 6)
                {
                    if (mutareaAnterioara.tip == 2)
                    {
                        linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 2)
                        {
                            linia = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            if (a[1][2].jucator == 0)
                            {
                                linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am cstigat
                            }
                            else
                            {
                                linia = 2; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am castigat
                            }
                        }
                    }
                }
                else
                {
                    if (mutareaAnterioara.tip == 1)
                    {
                        int li, ci, lf, cf;
                        li = 2; ci = 0; lf = 0; cf = 0;
                        muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat
                    }
                    else
                    {
                        if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 1)
                        {
                            linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///am castigat
                        }
                        else
                        {
                            if (mutareaAnterioara.lf == 0 && mutareaAnterioara.cf == 1)
                            {
                                subcaz = 7;
                                dimensiune = 2; linia = 2; coloana = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            }
                            else
                            {
                                if (mutareaAnterioara.lf == 0 && mutareaAnterioara.cf == 0)
                                {
                                    subcaz = 8; dimensiune = 2; linia = 2; coloana = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                }
                                else
                                {
                                    linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                    ///am castigat
                                }
                            }
                        }
                    }
                }
            }

        }

    }

    if (tur == 6)
    {
        if (subcaz == 6)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (a[0][1].jucator == 0)
                {
                    linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am caqstigat
                }
                else
                {
                    linia = 1; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
            }
        }
        else
        {
            if (subcaz == 7)
            {
                int li, ci, lf, cf;
                li = 0; ci = 2; lf = 2; cf = 2;
                muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (a[0][0].jucator == 0)
                {
                    linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[1][2].jucator == 0)
                    {
                        linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 2;  coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
    }
}


void strategia13_strat(matrice a[3][3], int& tur, int& caz)
{
    int dimensiune = 0, linia = 0, coloana = 0, calculator = 2;
    if (tur == 1)
    {
        linia = 2; coloana = 2; dimensiune = 3;
        pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
    }
    else
    {
        if (tur == 2)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linia = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0)
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 2)
                    {
                        caz = 1;
                        int li, ci, cf, lf;
                        li = 1; ci = 1; lf = 0; cf = 0;
                        muta_o_piesa_strat(a, li, ci, lf, cf);
                    }
                    else
                    {
                        if (mutareaAnterioara.dimensiuneaPiesei == 3)
                        {
                            caz = 2;
                            dimensiune = 2; linia = 2; coloana = 1;
                            pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }

                    }
                }
                else
                {
                    linia = 0; coloana = 0; dimensiune = 2;
                    pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///castiga
                }
            }
        }
        else
        {
            if (tur == 3)
            {
                if (caz == 1)
                {
                    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 1)
                    {
                        if (mutareaAnterioara.dimensiuneaPiesei == 3)
                        {
                            linia = 2; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            linia = 1; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///am castigat
                        }
                    }
                    else
                    {
                        linia = 1; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///castiga
                    }
                }
                else
                {
                    if (mutareaAnterioara.tip == 2)
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///castiga
                    }
                    else
                    {
                        if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 1)
                        {
                            linia = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            if (a[0][1].jucator == 0)
                            {
                                linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///castig
                            }
                            else
                            {
                                linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///castig
                            }
                        }
                    }
                }
            }
            else
            {
                if (tur == 4)
                {
                    if (caz == 2)
                    {
                        int li, ci, lf, cf;
                        li = 2; ci = 2; lf = 1; cf = 2;
                        muta_o_piesa_strat(a, li, ci, lf, cf);
                    }
                    else
                    {
                        if (mutareaAnterioara.tip == 2)
                        {
                            linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///castiga
                        }
                        else
                        {
                            if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 0)
                            {
                                linia = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            }
                            else
                            {
                                if (a[1][0].jucator == 0) pune_o_piesa_strat(a, 1, 0, 2, 1);
                                else pune_o_piesa_strat(a, 2, 1, 2, 1);
                            }
                        }
                    }
                }
                else
                {
                    if (a[1][1].jucator == 0)
                    {
                        linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        if (a[0][1].jucator == 0)
                        {
                            linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }
                    }
                }
            }
        }

    }

}

void strategia17_strat(matrice a[3][3], int& tur, int& caz, int& subcaz)
{
    int linia = 0, coloana = 0, calculator = 2, dimensiune = 0;
    if (tur == 1)
    {
        linia = 2; coloana = 0; dimensiune = 3;
        pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
    }

    if (tur == 2)
    {
        if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2)
        {
            if (mutareaAnterioara.dimensiuneaPiesei == 2)
            {
                caz = 1; linia = 2; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            }
            else
            {
                caz = 2; linia = 2; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            }
        }
        else
        {
            linia = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            ///am castigat
        }
    }

    if (tur == 3)
    {
        if (caz == 1)
        {
            if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 1)
            {
                linia = 1; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            }
            else
            {
                if (a[0][1].jucator == 0)
                {
                    linia = 0; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    linia = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                }
            }
        }
        else
        {
            if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 1)
            {
                linia = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            }
            else
            {
                if (mutareaAnterioara.tip == 2)
                {
                    linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[0][1].jucator == 0)
                    {
                        linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///castiga
                    }
                    else
                    {
                        linia = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///braa
                    }
                }
            }
        }
    }

    if (tur == 4)
    {
        if (caz == 2)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///castigaaaaam
            }
            else
            {
                if (a[0][0].jucator == 0)
                {
                    linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///yasss
                }
                else
                {
                    linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                }
            }
        }
        else
        {
            if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 0)
            {
                if (mutareaAnterioara.dimensiuneaPiesei == 2)
                {
                    subcaz = 1;
                    linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                }
                else
                {
                    subcaz = 2;
                    linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                }
            }
            else
            {
                if (mutareaAnterioara.tip == 2)
                {
                    if (a[2][2].jucator == 0)
                    {
                        linia = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        //.wiin
                    }
                    else
                    {
                        linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///do wii have a problem
                    }
                }
                else
                {
                    if (a[0][0].jucator == 0)
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///yh
                    }
                    else
                    {
                        linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                }
            }
        }

    }

    if (tur == 5)
    {
        if (subcaz == 1)
        {
            if ((mutareaAnterioara.l == 0) && (mutareaAnterioara.c == 0) && (mutareaAnterioara.dimensiuneaPiesei == 3))
            {
                int li, lf, ci, cf;
                li = 1; ci = 1; lf = 0; cf = 2;
                muta_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            }
            else
            {
                if (mutareaAnterioara.tip == 2)
                {
                    if (a[2][0].jucator == 0)
                    {
                        linia = 2; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        //ayy
                    }
                    else
                    {
                        linia = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        /// ayy ayy
                    }
                }
                else
                {
                    linia = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    /// ayy ayy ayy
                }
            }
        }
        else
        {
            if (mutareaAnterioara.tip == 2)
            {
                if (a[0][2].jucator == 0)
                {
                    linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///oya
                }
                else
                {
                    if (a[1][0].jucator == 2)
                    {
                        linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linia = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                }
            }
            else
            {
                if ((mutareaAnterioara.l == 0) && (mutareaAnterioara.c == 1) && (mutareaAnterioara.dimensiuneaPiesei == 2))
                {
                    int li, lf, ci, cf;
                    li = 1; ci = 1; lf = 0; cf = 2;
                    muta_o_piesa_strat(a, li, ci, lf, cf);
                }
                else
                {
                    int li, ci, lf, cf;
                    li = 2; ci = 0; lf = 2; cf = 2;
                    pune_o_piesa_strat(a, li, ci, lf, cf);
                }
            }
        }
    }

    if (tur == 6)
    {
        if (subcaz == 2)
        {
            if (mutareaAnterioara.tip == 1)
            {
                linia = 1; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ////oyy aoyya
            }
            else
            {
                if (mutareaAnterioara.li == 0 && mutareaAnterioara.ci == 0)
                {
                    if (a[0][1].jucator == 0)
                    {
                        linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                }
                else
                {
                    int li, ci, lf, cf;
                    li = 0; ci = 2;
                    if (a[1][0].jucator == 2) { lf = 0; cf = 0; }
                    else { lf = 2; cf = 2; }
                    muta_o_piesa_strat(a, li, ci, lf, cf);
                }
            }
        }
        else
        {
            if (mutareaAnterioara.tip == 1)
            {
                dimensiune = 2; linia = 1; coloana = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            }
            else
            {
                if ((mutareaAnterioara.li == 1) && (mutareaAnterioara.ci == 0) && (mutareaAnterioara.lf == 1) && (mutareaAnterioara.cf == 1))
                {
                    int li, lf, ci, cf;
                    li = 2; ci = 0; lf = 1; cf = 1;
                    muta_o_piesa_strat(a, li, ci, lf, cf);
                }
                else
                {
                    if (a[1][1].jucator == 0)
                    {
                        linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linia = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                }
            }
        }
    }
    if (tur == 7)
    {
        if (a[0][1].jucator == 0)
        {
            linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
        }
        else
        {
            linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
        }
    }
}

void strategia5_strat(matrice a[3][3], int& tur, int& caz, int& subcaz)
{
    int dimensiune = 0, calculator = 2, linie, coloana, li, lf, ci, cf;
    if (tur == 1)
    {
        dimensiune = 3; linie = 1; coloana = 2;
        pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
    }
    if (tur == 2)
    {
        if (mutareaAnterioara.tip == 1)
        {
            if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 0)
            {
                if (mutareaAnterioara.dimensiuneaPiesei == 2)
                {
                    caz = 1; li = 1; ci = 2; lf = 1; cf = 0;
                    muta_o_piesa_strat(a, li, ci, lf, cf);
                }
                else
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 3)
                    {
                        caz = 2; linie = 0; coloana = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linie = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                linie = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
        else
        {
            if (mutareaAnterioara.lf == 1 && mutareaAnterioara.cf == 0)
            {
                caz = 3; dimensiune = 2; linie = 0; coloana = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
            }
            else
            {
                linie = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
    }

    if (tur == 3)
    {
        if (caz == 3)
        {
            if (mutareaAnterioara.tip == 1)
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2)
                {
                    linie = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    if (a[2][0].jucator == 0)
                    {
                        linie = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                linie = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
        if (caz == 2)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 2; lf = 2; cf = 0;
                muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 0)
                {
                    linie = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.lf == 0 && mutareaAnterioara.cf == 2)
                    {
                        dimensiune = 2; linie = 2; coloana = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (caz == 1)
        {
            if (mutareaAnterioara.tip == 2)
            {
                if (mutareaAnterioara.lf == 1 && mutareaAnterioara.cf == 2)
                {
                    subcaz = 3; dimensiune = 2; linie = 0; coloana = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    linie = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
            }
            else
            {
                if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 2)
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 2)
                    {
                        subcaz = 1; li = 1; ci = 1; lf = 1; cf = 2;
                        muta_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        if (mutareaAnterioara.dimensiuneaPiesei == 3)
                        {
                            subcaz = 2; dimensiune = 2; linie = 0; coloana = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            linie = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                            ///am castigat
                        }
                    }
                }
                else
                {
                    linie = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
            }

        }
    }
    if (tur == 4)
    {
        if (caz == 3)
        {
            if (mutareaAnterioara.tip == 2)
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 0)
                {
                    linie = 1; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.lf == 2 && mutareaAnterioara.cf == 2)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                li = 1; ci = 2; lf = 0; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
        }
        if (caz == 2)
        {
            if (mutareaAnterioara.tip == 2)
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 0)
                {
                    linie = 1; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.lf == 2 && mutareaAnterioara.cf == 2)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                li = 1; ci = 2; lf = 0; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
        }
        if (caz == 1)
        {
            if (subcaz == 1)
            {
                if (mutareaAnterioara.tip == 2)
                {
                    if (mutareaAnterioara.lf == 1 && mutareaAnterioara.cf == 1)
                    {
                        subcaz = 5;
                        linie = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
                else
                {
                    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 1)
                    {
                        subcaz = 4; linie = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            if (subcaz == 2)
            {
                if (mutareaAnterioara.tip == 1)
                {
                    li = 1; ci = 0; lf = 2; cf = 0;
                    muta_o_piesa_strat(a, li, ci, lf, cf);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 2)
                    {
                        linie = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                }
            }
            if (subcaz == 3)
            {
                if (mutareaAnterioara.tip == 2)
                {
                    linie = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[2][0].jucator == 0)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);

                    }
                }
            }
        }
    }
    if (tur == 5)
    {
        if (subcaz == 3)
        {
            if (mutareaAnterioara.tip == 1)
            {
                lf = 0; cf = 0; li = 1; ci = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.lf == 0 && mutareaAnterioara.cf == 0)
                {
                    li = 1; ci = 0; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.lf == 2 && mutareaAnterioara.cf == 2)
                    {
                        li = 1; ci = 0; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat
                    }
                    else
                    {
                        li = 1; ci = 0; lf = 0; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat

                    }
                }
            }
        }
        if (subcaz == 2)
        {
            if (mutareaAnterioara.tip == 1)
            {
                lf = 0; cf = 0; li = 1; ci = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.lf == 0 && mutareaAnterioara.cf == 0)
                {
                    li = 1; ci = 0; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.lf == 2 && mutareaAnterioara.cf == 2)
                    {
                        li = 1; ci = 0; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat
                    }
                    else
                    {
                        li = 1; ci = 0; lf = 0; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat

                    }
                }
            }
        }
        if (subcaz == 4)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 2; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 1)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.lf == 0 && mutareaAnterioara.cf == 0)
                    {
                        subcaz = 6;
                        dimensiune = 2; linie = 2; coloana = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        if (mutareaAnterioara.lf == 2 && mutareaAnterioara.cf == 0)
                        {
                            subcaz = 7;
                            dimensiune = 2; linie = 0; coloana = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                            ///am castigat
                        }
                    }
                }
            }
        }
        if (subcaz == 5)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2)
                {
                    subcaz = 8;  linie = 2; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 2)
                    {
                        if (mutareaAnterioara.dimensiuneaPiesei == 3)
                        {
                            subcaz = 9;
                            linie = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            li = 1; ci = 0; lf = 2; cf = 2;
                            muta_o_piesa_strat(a, li, ci, lf, cf);
                            ///am castigat
                        }
                    }
                    else
                    {
                        li = 1; ci = 0; lf = 2; cf = 2;
                        muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat
                    }
                }
            }
        }
    }
    if (tur == 6)
    {
        if (subcaz == 6)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 0; lf = 0; cf = 2; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 1)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[2][0].jucator == 0)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (subcaz == 7)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 0; lf = 0; cf = 1;
                muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 1)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am cstigat
                }
                else
                {
                    if (a[0][0].jucator == 2)
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (subcaz == 8)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 2; lf = 0; cf = 0;
                muta_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.ci == 1 && mutareaAnterioara.li == 1)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[2][2].jucator == 0)
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (subcaz == 9)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 2; lf = 0; cf = 1;
                muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am acstigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.lf == 1)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[2][0].jucator == 2)
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
    }

}

void strategia21_strat(matrice a[3][3], int& tur)
{
    int linia, coloana, dimensiune, calculator = 2, ci, cf, li, lf;
    if (tur == 1)
    {
        linia = 1; coloana = 2; dimensiune = 3; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
    }
    if (tur == 2)
    {
        if (mutareaAnterioara.tip == 2)
        {
            linia = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
            ///am cstigat
        }
        else
        {
            if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 0)
            {
                if (mutareaAnterioara.dimensiuneaPiesei == 2)
                {
                    caz = 1;
                    li = 1; ci = 2; lf = 1; cf = 0;
                    muta_o_piesa_strat(a, li, ci, lf, cf);

                }
                else
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 3)
                    {
                        caz = 2;
                        dimensiune = 2; linia = 2; coloana = 2;
                        pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linia = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                linia = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
    }
    if (tur == 3)
    {
        if (caz == 2)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linia = 1; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 2)
                {
                    dimensiune = 2; linia = 0; coloana = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                }
                else
                {
                    if (a[0][0].jucator == 0)
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (caz == 1)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linia = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 2)
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 2)
                    {
                        subcaz = 1; li = 1; ci = 1; lf = 1; cf = 2;
                        muta_o_piesa_strat(a, li, ci, lf, cf);
                    }
                    else
                    {
                        if (mutareaAnterioara.dimensiuneaPiesei == 3)
                        {
                            subcaz = 2; linia = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        }
                        else
                        {
                            linia = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///am cstigat
                        }
                    }
                }
                else
                {
                    linia = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am cstigat
                }
            }
        }
    }
    if (tur == 4)
    {
        if (caz == 2)
        {
            if (mutareaAnterioara.tip == 2)
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 0)
                {
                    linia = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.lf == 0 && mutareaAnterioara.cf == 2)
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                li = 1; ci = 2; lf = 2; cf = 0;
                muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
        }
        if (caz == 1)
        {
            if (subcaz == 1)
            {
                if (mutareaAnterioara.tip == 2)
                {
                    linia = 1; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 1 && mutareaAnterioara.dimensiuneaPiesei == 3)
                    {
                        linia = 2; dimensiune = 2; coloana = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linia = 1; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            if (subcaz == 2)
            {
                if (mutareaAnterioara.tip == 2)
                {
                    linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am cstigat
                }
                else
                {
                    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 2)
                    {
                        subcaz = 6;
                        dimensiune = 2; linia = 0; coloana = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0)
                        {
                            if (mutareaAnterioara.dimensiuneaPiesei == 3)
                            {
                                subcaz = 5;
                                linia = 2; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            }
                            else
                            {
                                linia = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                                ///am cstigat
                            }
                        }
                        else
                        {
                            linia = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                            ///am cstigat
                        }
                    }
                }
            }
        }
    }
    if (tur == 5)
    {
        if (subcaz == 6)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 0; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 2)
                {
                    linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[0][0].jucator == 0)
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (subcaz == 5)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 1; lf = 2; cf = 0;
                muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castgat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 2)
                {
                    linia = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[2][1].jucator == 2)
                    {
                        linia = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                }
            }
        }
        if (subcaz == 1)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2)
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 3)
                    {
                        subcaz = 3;
                        linia = 2; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        li = 1; ci = 0; lf = 0; cf = 2; muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat
                    }
                }
                else
                {
                    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 2)
                    {
                        subcaz = 4;
                        linia = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am acstigat
                    }
                    else
                    {
                        li = 1; ci = 0; lf = 0; cf = 2; muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat
                    }
                }
            }
        }
    }
    if (tur == 6)
    {
        if (subcaz == 4)
        {
            if (mutareaAnterioara.tip == 2)
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 1)
                {
                    linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[0][2].jucator == 0)
                    {
                        linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am cstigat
                    }
                    else
                    {
                        linia = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am cstigat
                    }
                }
            }
            else
            {
                li = 1; ci = 2; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am cstigat
            }
        }
        if (subcaz == 3)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 2; lf = 0; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.c == 1)
                {
                    linia = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                    ///am cqastigat
                }
                else
                {
                    if (a[2][2].jucator == 2)
                    {
                        linia = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linia = 0; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
    }
}

void strategia9_strat(matrice a[3][3], int& tur)
{
    int linie, coloana, calculator = 2, dimensiune, li, lf, ci, cf;
    if (tur == 1)
    {
        linie = 1; coloana = 2; dimensiune = 3;
        pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
    }
    if (tur == 2)
    {
        if (mutareaAnterioara.tip == 2)
        {
            if (mutareaAnterioara.lf == 1 && mutareaAnterioara.cf == 0)
            {
                caz = 3;
                li = 1; ci = 2; lf = 1; cf = 0;
                muta_o_piesa_strat(a, li, ci, lf, cf);
            }
            else
            {
                linie = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
        else
        {
            if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 0)
            {
                if (mutareaAnterioara.dimensiuneaPiesei == 2)
                {
                    caz = 1;
                    li = 1; ci = 2; lf = 1; cf = 0;
                }
                else
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 3)
                    {
                        caz = 2;
                        linie = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linie = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                linie = 1; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
    }
    if (tur == 3)
    {
        if (caz == 2)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linie = 1; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2)
                {
                    linie = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    if (a[2][0].jucator == 0)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        /// a castigat
                    }
                }
            }
        }
        if (caz == 3)
        {
            if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 2)
            {
                if (mutareaAnterioara.dimensiuneaPiesei == 2)
                {
                    subcaz = 5;
                    li = 1; ci = 1; lf = 1; cf = 2;
                    muta_o_piesa_strat(a, li, ci, lf, cf);
                }
                else
                {
                    if (mutareaAnterioara.dimensiuneaPiesei == 3)
                    {
                        subcaz = 6;
                        linie = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        linie = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
            else
            {
                linie = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
        if (caz == 1)
        {
            if (mutareaAnterioara.tip == 1)
            {
                if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 2 && mutareaAnterioara.dimensiuneaPiesei == 3)
                {
                    subcaz = 1; dimensiune = 2; linie = 0; coloana = 0; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    linie = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
            }
            else
            {
                if (mutareaAnterioara.lf == 1 && mutareaAnterioara.cf == 2)
                {
                    subcaz = 2;
                    li = 1; ci = 1; lf = 1; cf = 2; muta_o_piesa_strat(a, li, ci, lf, cf);
                }
                else
                {
                    linie = 1; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am cstigat
                }
            }
        }
    }
    if (tur == 4)
    {
        if (caz == 2)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linie = 1; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am cstigat
            }
            else
            {
                li = 1; ci = 2; lf = 0; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
        }
        if (subcaz = 5)
        {
            if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 1 && mutareaAnterioara.dimensiuneaPiesei == 3)
            {
                linie = 0; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                linie = 1; coloana = 1; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
            }
        }
        if (subcaz == 6)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linie = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0)
                {
                    dimensiune = 2; linie = 2; coloana = 0;
                    pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    if (a[2][0].jucator == 0)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///castiga
                    }
                }

            }
        }
        if (subcaz == 1)
        {
            if (mutareaAnterioara.tip == 1)
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0)
                {
                    linie = 2; coloana = 0; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    li = 1; ci = 1; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                    ///am castigat
                }
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 2)
                {
                    dimensiune = 1; linie = 1; coloana = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[2][0].jucator == 1)
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        if (a[0][0].jucator == 1)
                        {
                            li = 1; ci = 0; lf = 0; cf = 2; muta_o_piesa_strat(a, li, ci, lf, cf);
                        }
                    }
                }
            }
        }
        if (subcaz == 2)
        {
            if (mutareaAnterioara.tip == 1 && mutareaAnterioara.l == 1 && mutareaAnterioara.c == 1 && mutareaAnterioara.dimensiuneaPiesei == 3)
            {
                linie = 0; coloana = 0; dimensiune = 2;
                pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
            }
            else
            {
                linie = 1; dimensiune = 2; coloana = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am castigat
            }
        }
    }
    if (tur == 5)
    {
        if (subcaz == 5)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///am cstigat
            }
            else
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0)
                {
                    subcaz = 7;
                    linie = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 0 && mutareaAnterioara.dimensiuneaPiesei == 3)
                    {
                        linie = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        li = 1; ci = 2; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                    }
                }
            }
        }
        if (subcaz == 6)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 0; lf = 0; cf = 2; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 2)
                {
                    linie = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    //am castigat
                }
                else
                {
                    if (a[2][0].jucator == 1)
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (subcaz == 1)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 0; lf = 0; cf = 2; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (mutareaAnterioara.li == 1 && mutareaAnterioara.ci == 2)
                {
                    linie = 1; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am cstigat
                }
                else
                {
                    if (a[2][0].jucator == 1)
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        if (a[0][2].marimePiesa != 3)
                        {
                            li = 1; ci = 0; lf = 0; cf = 2; muta_o_piesa_strat(a, li, lf, ci, cf);
                            ///am castigat
                        }
                    }
                }
            }
        }
        if (subcaz == 2)
        {
            if (mutareaAnterioara.tip == 2)
            {
                linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                ///a m castigay
            }
            else
            {
                if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0)
                {
                    subcaz = 3;
                    linie = 2; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                }
                else
                {
                    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 0 && mutareaAnterioara.dimensiuneaPiesei == 3)
                    {
                        subcaz = 4;
                        linie = 0; coloana = 2; dimensiune = 2; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    }
                    else
                    {
                        li = 1; ci = 2; lf = 2; cf = 0;
                        muta_o_piesa_strat(a, li, ci, lf, cf);
                        ///am castigat
                    }
                }
            }
        }
    }
    if (tur == 6)
    {
        if (subcaz == 4)
        {
            if (mutareaAnterioara.tip == 1)
            {
                if (a[0][1].jucator == 0)
                {
                    linie = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
            }
            else
            {
                if (a[1][1].jucator == 0)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[0][0].jucator == 2)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (subcaz == 3)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 0; lf = 2; cf = 0; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (a[1][1].jucator == 0)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[0][0].jucator == 2)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (subcaz == 7)
        {
            if (mutareaAnterioara.tip == 1)
            {
                li = 1; ci = 0; lf = 0; cf = 2; muta_o_piesa_strat(a, li, ci, lf, cf);
                ///am castigat
            }
            else
            {
                if (a[1][1].jucator == 0)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[2][0].jucator == 0)
                    {
                        linie = 2; coloana = 0; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
        if (subcaz == 8)
        {
            if (mutareaAnterioara.tip == 1)
            {
                if (a[0][1].jucator == 0)
                {
                    linie = 0; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
            }
            else
            {
                if (a[1][1].jucator == 0)
                {
                    linie = 1; coloana = 1; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                    ///am castigat
                }
                else
                {
                    if (a[0][0].jucator == 2)
                    {
                        linie = 0; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                    else
                    {
                        linie = 2; coloana = 2; dimensiune = 1; pune_o_piesa_strat(a, linie, coloana, calculator, dimensiune);
                        ///am castigat
                    }
                }
            }
        }
    }
}

void strategia4_strat(int& tur)
{
    rotire_dreapta_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.l;
        mutareaAnterioara.l = mutareaAnterioara.c;
        mutareaAnterioara.c = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.li;
        mutareaAnterioara.li = mutareaAnterioara.ci;
        mutareaAnterioara.ci = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.lf;
        mutareaAnterioara.lf = mutareaAnterioara.cf;
        mutareaAnterioara.cf = 2 - aux2;
    }
    strategia1_strat(b, tur);
    rotire_stanga_strat(b, a);
}

void strategia3_strat(int& tur)
{
    rotire_stanga_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.c;
        mutareaAnterioara.c = mutareaAnterioara.l;
        mutareaAnterioara.l = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.ci;
        mutareaAnterioara.ci = mutareaAnterioara.li;
        mutareaAnterioara.li = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.cf;
        mutareaAnterioara.cf = mutareaAnterioara.lf;
        mutareaAnterioara.lf = 2 - aux2;
    }
    strategia1_strat(b, tur);
    rotire_dreapta_strat(b, a);
}

void strategia2_strat(int& tur)
{

    int aux;
    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";

    int aux2;

    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";


    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    rotire_dreapta_strat(a, b);
    rotire_dreapta_strat(b, c);
    strategia1_strat(c, tur);
    rotire_stanga_strat(c, b);
    rotire_stanga_strat(b, a);
}

void strategia6_strat(int& tur)
{
    rotire_dreapta_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.l;
        mutareaAnterioara.l = mutareaAnterioara.c;
        mutareaAnterioara.c = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.li;
        mutareaAnterioara.li = mutareaAnterioara.ci;
        mutareaAnterioara.ci = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.lf;
        mutareaAnterioara.lf = mutareaAnterioara.cf;
        mutareaAnterioara.cf = 2 - aux2;
    }
    strategia5_strat(b, tur, caz, subcaz);
    rotire_stanga_strat(b, a);
}

void strategia8_strat(int& tur)
{
    rotire_stanga_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.c;
        mutareaAnterioara.c = mutareaAnterioara.l;
        mutareaAnterioara.l = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.ci;
        mutareaAnterioara.ci = mutareaAnterioara.li;
        mutareaAnterioara.li = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.cf;
        mutareaAnterioara.cf = mutareaAnterioara.lf;
        mutareaAnterioara.lf = 2 - aux2;
    }
    strategia5_strat(b, tur, caz, subcaz);
    rotire_dreapta_strat(b, a);

}

void strategia7_strat(int& tur)
{
    int aux;
    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";

    int aux2;

    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";


    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    rotire_dreapta_strat(a, b);
    rotire_dreapta_strat(b, c);
    strategia5_strat(c, tur, caz, subcaz);
    rotire_stanga_strat(c, b);
    rotire_stanga_strat(b, a);
}

void strategia11_strat(int& tur)
{
    rotire_dreapta_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.l;
        mutareaAnterioara.l = mutareaAnterioara.c;
        mutareaAnterioara.c = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.li;
        mutareaAnterioara.li = mutareaAnterioara.ci;
        mutareaAnterioara.ci = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.lf;
        mutareaAnterioara.lf = mutareaAnterioara.cf;
        mutareaAnterioara.cf = 2 - aux2;
    }
    strategia9_strat(b, tur);
    rotire_stanga_strat(b, a);
}

void strategia12_strat(int& tur)
{
    rotire_stanga_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.c;
        mutareaAnterioara.c = mutareaAnterioara.l;
        mutareaAnterioara.l = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.ci;
        mutareaAnterioara.ci = mutareaAnterioara.li;
        mutareaAnterioara.li = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.cf;
        mutareaAnterioara.cf = mutareaAnterioara.lf;
        mutareaAnterioara.lf = 2 - aux2;
    }
    strategia9_strat(b, tur);
    rotire_dreapta_strat(b, a);
}

void strategia10_strat(int& tur)
{
    int aux;
    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";

    int aux2;

    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";


    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    rotire_dreapta_strat(a, b);
    rotire_dreapta_strat(b, c);
    strategia9_strat(c, tur);
    rotire_stanga_strat(c, b);
    rotire_stanga_strat(b, a);
}

void strategia14_strat(int& tur)
{
    rotire_dreapta_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.l;
        mutareaAnterioara.l = mutareaAnterioara.c;
        mutareaAnterioara.c = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.li;
        mutareaAnterioara.li = mutareaAnterioara.ci;
        mutareaAnterioara.ci = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.lf;
        mutareaAnterioara.lf = mutareaAnterioara.cf;
        mutareaAnterioara.cf = 2 - aux2;
    }
    strategia13_strat(b, tur, caz);
    rotire_stanga_strat(b, a);
}

void strategia16_strat(int& tur)
{
    rotire_stanga_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.c;
        mutareaAnterioara.c = mutareaAnterioara.l;
        mutareaAnterioara.l = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.ci;
        mutareaAnterioara.ci = mutareaAnterioara.li;
        mutareaAnterioara.li = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.cf;
        mutareaAnterioara.cf = mutareaAnterioara.lf;
        mutareaAnterioara.lf = 2 - aux2;
    }
    strategia13_strat(b, tur, caz);
    rotire_dreapta_strat(b, a);

}

void strategia15_strat(int& tur)
{
    int aux;
    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";

    int aux2;

    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";


    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    rotire_dreapta_strat(a, b);
    rotire_dreapta_strat(b, c);
    strategia13_strat(c, tur, caz);
    rotire_stanga_strat(c, b);
    rotire_stanga_strat(b, a);
}

void strategia18_strat(int& tur)
{
    rotire_dreapta_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.l;
        mutareaAnterioara.l = mutareaAnterioara.c;
        mutareaAnterioara.c = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.li;
        mutareaAnterioara.li = mutareaAnterioara.ci;
        mutareaAnterioara.ci = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.lf;
        mutareaAnterioara.lf = mutareaAnterioara.cf;
        mutareaAnterioara.cf = 2 - aux2;
    }
    strategia17_strat(b, tur, caz, subcaz);
    rotire_stanga_strat(b, a);
}

void strategia20_strat(int& tur)
{
    rotire_stanga_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.c;
        mutareaAnterioara.c = mutareaAnterioara.l;
        mutareaAnterioara.l = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.ci;
        mutareaAnterioara.ci = mutareaAnterioara.li;
        mutareaAnterioara.li = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.cf;
        mutareaAnterioara.cf = mutareaAnterioara.lf;
        mutareaAnterioara.lf = 2 - aux2;
    }
    strategia17_strat(b, tur, caz, subcaz);
    rotire_dreapta_strat(b, a);
}

void strategia19_strat(int& tur)
{
    int aux;
    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";

    int aux2;

    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";


    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    rotire_dreapta_strat(a, b);
    rotire_dreapta_strat(b, c);
    strategia17_strat(c, tur, caz, subcaz);
    rotire_stanga_strat(c, b);
    rotire_stanga_strat(b, a);
}

void strategia22_strat(int& tur)
{
    rotire_dreapta_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.l;
        mutareaAnterioara.l = mutareaAnterioara.c;
        mutareaAnterioara.c = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.li;
        mutareaAnterioara.li = mutareaAnterioara.ci;
        mutareaAnterioara.ci = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.lf;
        mutareaAnterioara.lf = mutareaAnterioara.cf;
        mutareaAnterioara.cf = 2 - aux2;
    }
    strategia21_strat(b, tur);
    rotire_stanga_strat(b, a);
}

void strategia23_strat(int& tur)
{
    int aux;
    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";

    int aux2;

    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    aux = mutareaAnterioara.l;
    mutareaAnterioara.l = mutareaAnterioara.c;
    mutareaAnterioara.c = 2 - aux;
    cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";


    aux = mutareaAnterioara.li;
    mutareaAnterioara.li = mutareaAnterioara.ci;
    mutareaAnterioara.ci = 2 - aux;

    aux2 = mutareaAnterioara.lf;
    mutareaAnterioara.lf = mutareaAnterioara.cf;
    mutareaAnterioara.cf = 2 - aux2;

    rotire_dreapta_strat(a, b);
    rotire_dreapta_strat(b, c);
    strategia21_strat(c, tur);
    rotire_stanga_strat(c, b);
    rotire_stanga_strat(b, a);
}

void strategia24_strat(int& tur)
{
    rotire_stanga_strat(a, b);
    if (mutareaAnterioara.tip == 1)
    {
        int aux;
        aux = mutareaAnterioara.c;
        mutareaAnterioara.c = mutareaAnterioara.l;
        mutareaAnterioara.l = 2 - aux;
        cout << "mutarea anterioara " << mutareaAnterioara.l << " " << mutareaAnterioara.c << "\n";
    }
    else
    {
        int aux;
        aux = mutareaAnterioara.ci;
        mutareaAnterioara.ci = mutareaAnterioara.li;
        mutareaAnterioara.li = 2 - aux;
        int aux2;
        aux2 = mutareaAnterioara.cf;
        mutareaAnterioara.cf = mutareaAnterioara.lf;
        mutareaAnterioara.lf = 2 - aux2;
    }
    strategia21_strat(b, tur);
    rotire_dreapta_strat(b, a);

}

int Alegestrategia1_strat()
{
    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 1) return 1;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 1) return 2;
    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 0) return 3;
    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 2) return 4;

    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 2) return 5;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2) return 6;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0) return 7;
    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 0) return 8;
}

int Alegestrategia2_strat()
{
    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 1) return 9;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 1) return 10;
    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 0) return 12;
    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 2) return 11;

    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 2) return 13;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2) return 14;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0) return 15;
    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 0) return 16;
}


int Alegestrategia3_strat()
{
    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 1) return 17;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 1) return 19;
    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 0) return 20;
    if (mutareaAnterioara.l == 1 && mutareaAnterioara.c == 2) return 18;

    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 2) return 21;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 2) return 22;
    if (mutareaAnterioara.l == 0 && mutareaAnterioara.c == 0) return 23;
    if (mutareaAnterioara.l == 2 && mutareaAnterioara.c == 0) return 24;
}



void mutarea_calculatorului_strat(matrice a[3][3], int& tur)
{
    int linia, coloana, dimensiune, calculator = 2;
    if (tur == 0)
    {
        linia = 1;
        coloana = 1;
        dimensiune = 3;
        pune_o_piesa_strat(a, linia, coloana, calculator, dimensiune);

    }
    else if (tur == 1)
    {
        if (mutareaAnterioara.tip == 1)
        {
            if (mutareaAnterioara.dimensiuneaPiesei == 3)
            {
                strategie = Alegestrategia1_strat();
            }
            else
            {
                if (mutareaAnterioara.dimensiuneaPiesei == 2) strategie = Alegestrategia2_strat();
                else strategie = Alegestrategia3_strat();
            }

        }
    }

    switch (strategie)
    {
    case 1:
        strategia1_strat(a, tur);
        break;
    case 2:
        strategia2_strat(tur);
        break;
    case 3:
        strategia3_strat(tur);
        break;
    case 4:
        strategia4_strat(tur);
        break;
    case 5:
        strategia5_strat(a, tur, caz, subcaz);
        break;
    case 6:
        strategia6_strat(tur);
        break;
    case 7:
        strategia7_strat(tur);
        break;
    case 8:
        strategia8_strat(tur);
        break;
    case 9:
        strategia9_strat(a, tur);
        break;
    case 10:
        strategia10_strat(tur);
        break;
    case 11:
        strategia11_strat(tur);
        break;
    case 12:
        strategia12_strat(tur);
        break;
    case 13:
        strategia13_strat(a, tur, caz);
        break;
    case 14:
        strategia14_strat(tur);
        break;
    case 15:
        strategia15_strat(tur);
        break;
    case 16:
        strategia16_strat(tur);
        break;
    case 17:
        strategia17_strat(a, tur, caz, subcaz);
        break;
    case 18:
        strategia18_strat(tur);
        break;
    case 19:
        strategia19_strat(tur);
        break;
    case 20:
        strategia20_strat(tur);
        break;
    case 21:
        strategia21_strat(a, tur);
        break;
    case 22:
        strategia22_strat(tur);
        break;
    case 23:
        strategia23_strat(tur);
        break;
    case 24:
        strategia24_strat(tur);
        break;
    }
    tur++;
}

void tabla_goala_strat(matrice a[3][3])
{
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
        {
            a[i][j].jucator = 0;
            a[i][j].piese[0].player = 0;
            a[i][j].piese[1].player = 0;
            a[i][j].piese[2].player = 0;
            a[i][j].piese[0].dimensiune = 0;
            a[i][j].piese[1].dimensiune = 0;
            a[i][j].piese[2].dimensiune = 0;
        }
}
void randul_jucatorului_strat(matrice a[3][3])
{
    int decizie = 0, i, j, jucatorul = 1, marime, linie, coloana, ok = 0, liniaInitiala, liniaFinala, coloanaInitiala, coloanaFinala;
    char raspuns[3];
    int verificare = 0;
    mutareaAnterioara.tip = 0; mutareaAnterioara.l = 0; mutareaAnterioara.c = 0; mutareaAnterioara.li = 0; mutareaAnterioara.ci = 0;
    mutareaAnterioara.lf = 0; mutareaAnterioara.cf = 0;
    cout << "Randul jucatrorului \n";
    cout << "Doriti sa puneti o piesa noua?  da/nu ";
    cin >> raspuns;
    if (strcmp(raspuns, "da") == 0)
    {
        mutareaAnterioara.tip = 1;
    mama:
        cout << "Introduceti marimea piesei:";
        cin >> marime;
        if (verifica_daca_mai_are_un_tip_de_piese_strat(marime, jucatorul) == 0)
        {
            cout << "Nu mai aveti piese de aceasta marime. Alta:" << "\n";
            goto mama;
        }

        if (verifica_daca_piesa_are_marimea_corecta_strat(marime) == 0)
        {
            cout << "Nu exista piese de aceasta marime. Alta marime" << "\n";
            goto mama;
        }
        mutareaAnterioara.dimensiuneaPiesei = marime;
        do
        {
            cout << "Introduceti pozitia piesei:";
            cout << "\n";
            cout << "Introduceti linia:";
            cin >> linie;
            cout << "Introduceti coloana:";
            cin >> coloana;
            ok = 1;
            if (linie > 2 || coloana > 2) ok = 0;
            if (verifica_daca_se_poate_pune_o_piesa_strat_strat(a, linie, coloana, jucatorul, marime) == 0) ok = 0;
            if (ok == 0) cout << "Pozitie invalida. Introduceti alta pozitie" << "\n";
        } while (ok != 1);
        mutareaAnterioara.l = linie;
        mutareaAnterioara.c = coloana;
        pune_o_piesa_strat(a, linie, coloana, jucatorul, marime);
    }
    else
    {
        cout << "Doriti sa mutati o piesa? da/nu ";
        cin >> raspuns;
        if (strcmp(raspuns, "da") == 0)
        {
            mutareaAnterioara.tip = 2;
            cout << "Introduceti pozitia initiala a piesei:" << "\n";
            cout << "Introduceti linia:";
            cin >> liniaInitiala;
            cout << "Introduceti coloana:";
            cin >> coloanaInitiala;
            mutareaAnterioara.li = liniaInitiala;
            mutareaAnterioara.ci = coloanaInitiala;
            do
            {
                cout << "Introduceti pozitia finala piesei:";
                cout << "\n";
                cout << "Introduceti linia:";
                cin >> liniaFinala;
                cout << "Introduceti coloana:";
                cin >> coloanaFinala;
                ok = 1;
                if (liniaFinala > 2 || coloanaFinala > 2) ok = 0;

                ok = verifica_daca_se_poate_pune_o_piesa_strat_strat(a, liniaFinala, coloanaFinala, jucatorul, marime);
                if (ok == 0) cout << "Pozitie invalida. Introduceti alta pozitie" << "\n";

            } while (ok != 1);

            mutareaAnterioara.lf = liniaFinala;
            mutareaAnterioara.cf = coloanaFinala;

            muta_o_piesa_strat(a, liniaInitiala, coloanaInitiala, liniaFinala, coloanaFinala);
        }
    }
}

///////////////////////////////
// HARD STRATEGY ENDS HERE
///////////////////////////////


///////////////////////////////
// MEDIUM STRATEGY STARTS HERE
///////////////////////////////

void afisare(matrice a[3][3]);
void adaugare_min_strat(stiva piese[3], int jucatorul, int marime);
void stergere_min_strat(stiva piese[3]);
int verifica_daca_a_castigat_min_strat(matrice a[3][3]);
void pune_o_piesa_min_strat(matrice a[3][3], int linie, int coloana, int jucatorul, int marime);
int verifica_daca_mai_are_piese_mici_min_strat(int jucator);
int verifica_daca_mai_are_piese_medii_min_strat(int jucator);
int verifica_daca_mai_are_piese_mari_min_strat(int jucator);
int verifica_daca_mai_are_un_tip_de_piese_min_strat(int marime, int jucatorul);
int verifica_daca_se_poate_pune_o_piesa_min_strat(matrice a[3][3], int linie, int coloana, int jucatorul, int marime);
int verifica_daca_piesa_are_marimea_corecta_min_strat(int marime);
void muta_o_piesa_min_strat(matrice a[3][3], int liniaInitiala, int coloanaInitiala, int liniaFinala, int coloanaFinala);
int verifica_daca_vrea_sa_mute_piesa_lui_min_strat(matrice a[3][3], int jucatorul, int linie, int coloana);
void randul_jucatorului_min_strat(matrice a[3][3]);
int verifica_linia_min_strat(matrice a[3][3], int i, int jucatorul, int& liniaCastigatoare, int& coloanaCastigatoare);
int verifica_coloana_min_strat(matrice a[3][3], int j, int jucatorul, int& liniaCastigatoare, int& coloanaCastigatoare);
int verifica_diagonalele_min_strat(matrice a[3][3], int jucatorul, int& liniaCastigatoare, int& coloanaCastigatoare);
void verifica_daca_poate_castiga_min_strat(matrice a[3][3], int jucatorul, int& liniaCastigatoare, int& coloanaCastigatoare, int& r);
int verifica_daca_poate_acoperi_piesa_min_strat(int dimensiune, int jucatorul);
int decide_dimensiunea_min_strat();
void mutare1_min_strat(matrice a[3][3], int linia, int coloana);
void mutare2_min_strat(matrice a[3][3], int linia, int coloana);
void mutare3_min_strat(matrice a[3][3], int linia, int coloana, int& rez);
int inMarice_min_strat(int i, int j);
int cauta_pozitia_min_strat(matrice a[3][3], int i, int j, int& linia, int& coloana, int dimensiune);
void randul_calculatorului_min_strat(matrice a[3][3]);


///asta imi trebuie doar ca sa afisez matricea in main sa vad ce mutari face calculatorul

void afisare(matrice a[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            cout << a[i][j].jucator << " ";
        cout << "\n";
    }
}

void adaugare_min_strat(stiva piese[3], int jucatorul, int marime)
{
    piese[2].player = piese[1].player;
    piese[2].dimensiune = piese[1].dimensiune;
    piese[1].player = piese[0].player;
    piese[1].dimensiune = piese[0].dimensiune;

    piese[0].player = jucatorul;
    piese[0].dimensiune = marime;
}

void stergere_min_strat(stiva piese[3])
{

    piese[0].player = piese[1].player;
    piese[0].dimensiune = piese[1].dimensiune;
    piese[1].player = piese[2].player;
    piese[1].dimensiune = piese[2].dimensiune;
    piese[2].player = 0;
    piese[2].dimensiune = 0;
}

int verifica_daca_a_castigat_min_strat(matrice a[3][3])
{
    int i, j;

    for (i = 0; i < 3; ++i)
    {
        if ((a[i][0].jucator == a[i][1].jucator) && (a[i][1].jucator == a[i][2].jucator) && (a[i][0].jucator != 0)) return 1;
    }
    for (j = 0; j < 3; j++)
    {
        if ((a[0][j].jucator == a[1][j].jucator) && (a[1][j].jucator == a[2][j].jucator) && (a[0][j].jucator != 0)) return 1;
    }
    if ((a[0][0].jucator == a[1][1].jucator) && (a[1][1].jucator == a[2][2].jucator) && (a[0][0].jucator != 0)) return 1;
    if ((a[2][0].jucator == a[1][1].jucator) && (a[1][1].jucator == a[0][2].jucator) && (a[2][0].jucator != 0)) return 1;
    return 0;
}


void pune_o_piesa_min_strat(matrice a[3][3], int linie, int coloana, int jucatorul, int marime)
{

    g.fl = linie;
    g.fc = coloana;
    g.decision = 0;
    g.type = marime;
    g.change = true;

    a[linie][coloana].jucator = jucatorul;
    a[linie][coloana].marimePiesa = marime;
    adaugare_min_strat(a[linie][coloana].piese, jucatorul, marime);
    if (jucatorul == 1)
    {
        if (marime == 1) numarPieseMici1++;
        else
        {
            if (marime == 3) numarPieseMari1++;
            else numarPieseMedii1++;
        }
    }
    else
    {
        if (marime == 1) numarPieseMici2++;
        else
        {
            if (marime == 3) numarPieseMari2++;
            else numarPieseMedii2++;
        }
    }
    cout << "\n linia" << " " << linie << " " << coloana << "\n";
}

int verifica_daca_mai_are_piese_mici_min_strat(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMici1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMici2 == 2) return 0;
        return 1;
    }
}

int verifica_daca_mai_are_piese_medii_min_strat(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMedii1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMedii2 == 2) return 0;
        return 1;
    }
}

int verifica_daca_mai_are_piese_mari_min_strat(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMari1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMari2 == 2) return 0;
        return 1;
    }
}

int verifica_daca_mai_are_un_tip_de_piese_min_strat(int marime, int jucatorul)
{
    if (marime == 1)
    {
        if (verifica_daca_mai_are_piese_mici_min_strat(jucatorul) == 0) return 0;
        return 1;
    }
    else
    {
        if (marime == 2)
        {
            if (verifica_daca_mai_are_piese_medii_min_strat(jucatorul) == 0) return 0;
            return 1;
        }

        else
        {
            if (verifica_daca_mai_are_piese_mari_min_strat(jucatorul) == 0) return 0;
            else return 1;
        }
    }
}
int verifica_daca_se_poate_pune_o_piesa_min_strat(matrice a[3][3], int linie, int coloana, int jucatorul, int marime)
{
    if (linie < 0 || coloana < 0 || linie>2 || coloana>2) return 0;
    if (a[linie][coloana].jucator == 0) return 1;
    if (a[linie][coloana].marimePiesa >= marime) return 0;
    return 1;
}

int verifica_daca_piesa_are_marimea_corecta_min_strat(int marime)
{
    if (marime < 1 || marime>3) return 0;
    return 1;
}

void muta_o_piesa_min_strat(matrice a[3][3], int liniaInitiala, int coloanaInitiala, int liniaFinala, int coloanaFinala)
{
    g.fl = liniaFinala;
    g.fc = coloanaFinala;
    g.ol = liniaInitiala;
    g.oc = coloanaInitiala;
    g.decision = 1;
    g.change = true;
    g.type = a[liniaInitiala][coloanaInitiala].marimePiesa;
    a[liniaFinala][coloanaFinala].jucator = a[liniaInitiala][coloanaInitiala].jucator;
    a[liniaFinala][coloanaFinala].marimePiesa = a[liniaInitiala][coloanaInitiala].marimePiesa;
    adaugare_min_strat(a[liniaFinala][coloanaFinala].piese, a[liniaFinala][coloanaFinala].jucator, a[liniaFinala][coloanaFinala].marimePiesa);
    stergere_min_strat(a[liniaInitiala][coloanaInitiala].piese);
    a[liniaInitiala][coloanaInitiala].jucator = a[liniaInitiala][coloanaInitiala].piese[0].player;
    a[liniaInitiala][coloanaInitiala].marimePiesa = a[liniaInitiala][coloanaInitiala].piese[0].dimensiune;
    cout << "\n" << "linia initiala " << liniaInitiala << " " << coloanaInitiala << "\n";
    cout << "\n" << "linia fimala " << liniaFinala << " " << coloanaFinala << "\n";
}

int verifica_daca_vrea_sa_mute_piesa_lui_min_strat(matrice a[3][3], int jucatorul, int linie, int coloana)
{
    if (a[linie][coloana].jucator != jucatorul) return 0;
    return 1;
}

int verifica_daca_mai_are_piese_min_strat(int jucator)
{
    if (verifica_daca_mai_are_piese_mari_min_strat(jucator) == 1 || verifica_daca_mai_are_piese_medii_min_strat(jucator) == 1 || verifica_daca_mai_are_piese_mici_min_strat(jucator) == 1) return 1;
    return 0;
}


void randul_jucatorului_min_strat(matrice a[3][3])
{
    int decizie = 0, i, j, jucatorul = 1, marime, linie, coloana, stadiul = 0, ok = 0, liniaInitiala, liniaFinala, coloanaInitiala, coloanaFinala;
    char raspuns[3];
    int verificare = 0;
    cout << "Randul jucatrorului " << jucatorul << "\n";


    cout << "Doriti sa puneti o piesa noua?  da/nu ";
    cin >> raspuns;
    if (strcmp(raspuns, "da") == 0)
    {

    mama:
        cout << "Introduceti marimea piesei:";
        cin >> marime;
        if (verifica_daca_mai_are_un_tip_de_piese_min_strat(marime, jucatorul) == 0)
        {
            cout << "Nu mai aveti piese de aceasta marime. Alta:" << "\n";
            goto mama;
        }

        if (verifica_daca_piesa_are_marimea_corecta_min_strat(marime) == 0)
        {
            cout << "Nu exista piese de aceasta marime. Alta marime" << "\n";
            goto mama;
        }
        do
        {
            cout << "Introduceti pozitia piesei:";
            cout << "\n";
            cout << "Introduceti linia:";
            cin >> linie;
            cout << "Introduceti coloana:";
            cin >> coloana;
            ok = 1;
            if (linie > 2 || coloana > 2) ok = 0;
            if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, linie, coloana, jucatorul, marime) == 0) ok = 0;
            if (ok == 0) cout << "Pozitie invalida. Introduceti alta pozitie" << "\n";
        } while (ok != 1);
        pune_o_piesa_min_strat(a, linie, coloana, jucatorul, marime);
    }
    else
    {
        cout << "Doriti sa mutati o piesa? da/nu ";
        cin >> raspuns;
        if (strcmp(raspuns, "da") == 0)
        {

            cout << "Introduceti pozitia initiala a piesei:" << "\n";
            cout << "Introduceti linia:";
            cin >> liniaInitiala;
            cout << "Introduceti coloana:";
            cin >> coloanaInitiala;
            do
            {
                cout << "Introduceti pozitia finala piesei:";
                cout << "\n";
                cout << "Introduceti linia:";
                cin >> liniaFinala;
                cout << "Introduceti coloana:";
                cin >> coloanaFinala;
                ok = 1;
                if (liniaFinala > 2 || coloanaFinala > 2) ok = 0;

                ok = verifica_daca_se_poate_pune_o_piesa_min_strat(a, liniaFinala, coloanaFinala, jucatorul, marime);
                if (ok == 0) cout << "Pozitie invalida. Introduceti alta pozitie" << "\n";

            } while (ok != 1);
            muta_o_piesa_min_strat(a, liniaInitiala, coloanaInitiala, liniaFinala, coloanaFinala);
        }
    }


}

int verifica_linia_min_strat(matrice a[3][3], int i, int jucatorul, int& liniaCastigatoare, int& coloanaCastigatoare)
{
    if (a[i][0].jucator == jucatorul)
    {
        if (a[i][1].jucator == jucatorul) { liniaCastigatoare = i; coloanaCastigatoare = 2; return 1; }
        if (a[i][2].jucator == jucatorul) { liniaCastigatoare = i; coloanaCastigatoare = 1; return 1; }
    }
    else
    {
        if (a[i][1].jucator == jucatorul)
        {
            if (a[i][2].jucator == jucatorul) { liniaCastigatoare = i; coloanaCastigatoare = 0; return 1; }
        }
    }
    return 0;
}

int verifica_coloana_min_strat(matrice a[3][3], int j, int jucatorul, int& liniaCastigatoare, int& coloanaCastigatoare)
{
    if (a[0][j].jucator == jucatorul)
    {
        if (a[1][j].jucator == jucatorul) { liniaCastigatoare = 2; coloanaCastigatoare = j; return 1; }
        if (a[2][j].jucator == jucatorul) { liniaCastigatoare = 1; coloanaCastigatoare = j; return 1; }
    }
    else
    {
        if (a[1][j].jucator == jucatorul)
        {
            if (a[2][j].jucator == jucatorul) { liniaCastigatoare = 0; coloanaCastigatoare = j; return 1; }
        }
    }
    return 0;

}

int verifica_diagonalele_min_strat(matrice a[3][3], int jucatorul, int& liniaCastigatoare, int& coloanaCastigatoare)
{
    if (a[0][0].jucator == jucatorul)
    {
        if (a[1][1].jucator == jucatorul) { liniaCastigatoare = 2; coloanaCastigatoare = 2; return 1; }
        if (a[2][2].jucator == jucatorul) { liniaCastigatoare = 1; coloanaCastigatoare = 1; return 1; }
    }
    else
    {
        if (a[0][2].jucator == jucatorul)
        {
            if (a[1][1].jucator == jucatorul) { liniaCastigatoare = 2; coloanaCastigatoare = 0; return 1; }
            if (a[2][0].jucator == jucatorul) { liniaCastigatoare = 1; coloanaCastigatoare = 1; return 1; }
        }
        else
        {
            if (a[1][1].jucator == jucatorul)
            {
                if (a[2][0].jucator == jucatorul) { liniaCastigatoare = 0; coloanaCastigatoare = 2; return 1; }
                if (a[2][2].jucator == jucatorul) { liniaCastigatoare = 0; coloanaCastigatoare = 0; return 1; }
            }
        }
    }
    return 0;
}

void verifica_daca_poate_castiga_min_strat(matrice a[3][3], int jucatorul, int& liniaCastigatoare, int& coloanaCastigatoare, int& r)
{
    ///verificam liniile
    r = 0;
    int i, j;
    for (i = 0; i < 3 && r != 1; ++i) r = verifica_linia_min_strat(a, i, jucatorul, liniaCastigatoare, coloanaCastigatoare);
    if (r != 1)
    {
        ///verificam coloanele
        for (j = 0; j < 3 && r != 1; j++) r = verifica_coloana_min_strat(a, j, jucatorul, liniaCastigatoare, coloanaCastigatoare);
        if (r != 1)
        {
            ///verificam diagonalele
            r = verifica_diagonalele_min_strat(a, jucatorul, liniaCastigatoare, coloanaCastigatoare);
        }
    }
}

int verifica_daca_poate_acoperi_piesa_min_strat(int dimensiune, int jucatorul)
{
    int marime = dimensiune + 1;
    if (verifica_daca_mai_are_un_tip_de_piese_min_strat(marime, jucatorul) == 1) return 1;
    if (marime != 3)
    {
        if (verifica_daca_mai_are_piese_mari_min_strat(jucatorul) == 1) return 1;
    }
    return 0;
}
int decide_dimensiunea_min_strat()
{
    int ok = 0, calculator = 2;
    ok = verifica_daca_mai_are_piese_mari_min_strat(calculator);
    if (ok == 1) return 3;
    ok = verifica_daca_mai_are_piese_medii_min_strat(calculator);
    if (ok == 1) return 2;
    ok = verifica_daca_mai_are_piese_mici_min_strat(calculator);
    if (ok == 1) return 1;
    return -1;
}
void mutare1_min_strat(matrice a[3][3], int linia, int coloana)
{
    int liniaInitiala, coloanaInitiala;

    int l1, l2, c1, c2, ok1 = 0;

    ///verificam daca castigam pe coloana
    if (linia == 1) { if (a[linia - 1][coloana].jucator == 2 && a[linia + 1][coloana].jucator == 2) c1 = c2 = coloana; l1 = linia - 1; l2 = linia + 1; ok1 = 1; }
    if (linia == 0) { if (a[linia + 1][coloana].jucator == 2 && a[linia + 2][coloana].jucator == 2) c1 = c2 = coloana; l1 = linia + 1; l2 = linia + 2; ok1 = 1; }
    if (linia == 2) { if (a[linia - 1][coloana].jucator == 2 && a[linia - 2][coloana].jucator == 2) c1 = c2 = coloana; l1 = linia - 2; l2 = linia - 1; ok1 = 1; }

    if (ok1 == 0)
    {
        ///verificam daca castigam pe linie
        if (coloana == 0) { if (a[linia][coloana + 1].jucator == 2 && a[linia][coloana + 2].jucator == 2) l1 = l2 = linia; c1 = coloana + 1; c2 = coloana + 2; ok1 = 1; }
        if (coloana == 1) { if (a[linia][coloana - 1].jucator == 2 && a[linia][coloana + 1].jucator == 2) l1 = l2 = linia; c1 = coloana - 1; c2 = coloana + 1; ok1 = 1; }
        if (coloana == 2) { if (a[linia][coloana - 1].jucator == 2 && a[linia][coloana - 2].jucator == 2) l1 = l2 = linia; c1 = coloana - 1; c2 = coloana - 2; ok1 = 1; }
    }
    if (ok1 == 0)
    {
        ///verificam daca castiga pe coloana
        if (linia == 0 && coloana == 0) { if (a[1][1].jucator == 2 && a[2][2].jucator == 2) { l1 = 1; c1 = 1; l2 = 2; c2 = 2; } }
        if (linia == 0 && coloana == 2) { if (a[1][1].jucator == 2 && a[2][0].jucator == 2) { l1 = 1; c1 = 1; l2 = 2; c2 = 0; } }
        if (linia == 2 && coloana == 0) { if (a[1][1].jucator == 2 && a[0][2].jucator == 2) { l1 = 1; c1 = 1; l2 = 0; c2 = 2; } }
        if (linia == 2 && coloana == 2) { if (a[1][1].jucator == 2 && a[0][0].jucator == 2) { l1 = 1; c1 = 1; l2 = 0; c2 = 0; } }
        if (linia == 1 && coloana == 1)
        {
            if (a[0][0].jucator == 2 && a[2][2].jucator == 2) { l1 = 0; c1 = 0; l2 = 2; c2 = 2; }
            else { if (a[2][0].jucator == 2 && a[0][2].jucator == 2) { l1 = 0; c1 = 2; l2 = 2; c2 = 0; } }
        }
    }

    int i, j, ok = 0;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
        {
            if ((a[i][j].jucator == 2) && (i != l1) && (i != l2) && (j != c1) && (j != c2))
            {
                ok = 1;
                liniaInitiala = i; coloanaInitiala = j;
            }
        }
    if (ok == 1) muta_o_piesa_min_strat(a, liniaInitiala, coloanaInitiala, linia, coloana);
}

void mutare2_min_strat(matrice a[3][3], int linia, int coloana)
{
    int c1, l1, c2, l2, ok1 = 0, liniaInitiala, coloanaInitiala;
    ///verificam daca castigam pe coloana
    if (linia == 1) { if (a[linia - 1][coloana].jucator == 2 && a[linia + 1][coloana].jucator == 2) c1 = c2 = coloana; l1 = linia - 1; l2 = linia + 1; ok1 = 1; }
    if (linia == 0) { if (a[linia + 1][coloana].jucator == 2 && a[linia + 2][coloana].jucator == 2) c1 = c2 = coloana; l1 = linia + 1; l2 = linia + 2; ok1 = 1; }
    if (linia == 2) { if (a[linia - 1][coloana].jucator == 2 && a[linia - 2][coloana].jucator == 2) c1 = c2 = coloana; l1 = linia - 2; l2 = linia - 1; ok1 = 1; }

    if (ok1 == 0)
    {
        ///verificam daca castigam pe linie
        if (coloana == 0) { if (a[linia][coloana + 1].jucator == 2 && a[linia][coloana + 2].jucator == 2) l1 = l2 = linia; c1 = coloana + 1; c2 = coloana + 2; ok1 = 1; }
        if (coloana == 1) { if (a[linia][coloana - 1].jucator == 2 && a[linia][coloana + 1].jucator == 2) l1 = l2 = linia; c1 = coloana - 1; c2 = coloana + 1; ok1 = 1; }
        if (coloana == 2) { if (a[linia][coloana - 1].jucator == 2 && a[linia][coloana - 2].jucator == 2) l1 = l2 = linia; c1 = coloana - 1; c2 = coloana - 2; ok1 = 1; }
    }
    if (ok1 == 0)
    {
        ///verificam daca castiga pe diagonala
        if (linia == 0 && coloana == 0) { if (a[1][1].jucator == 2 && a[2][2].jucator == 2) { l1 = 1; c1 = 1; l2 = 2; c2 = 2; } }
        if (linia == 0 && coloana == 2) { if (a[1][1].jucator == 2 && a[2][0].jucator == 2) { l1 = 1; c1 = 1; l2 = 2; c2 = 0; } }
        if (linia == 2 && coloana == 0) { if (a[1][1].jucator == 2 && a[0][2].jucator == 2) { l1 = 1; c1 = 1; l2 = 0; c2 = 2; } }
        if (linia == 2 && coloana == 2) { if (a[1][1].jucator == 2 && a[0][0].jucator == 2) { l1 = 1; c1 = 1; l2 = 0; c2 = 0; } }
        if (linia == 1 && coloana == 1)
        {
            if (a[0][0].jucator == 2 && a[2][2].jucator == 2) { l1 = 0; c1 = 0; l2 = 2; c2 = 2; }
            else { if (a[2][0].jucator == 2 && a[0][2].jucator == 2) { l1 = 0; c1 = 2; l2 = 2; c2 = 0; } }
        }
    }

    int i, j, ok = 0;
    int marime = a[linia][coloana].marimePiesa;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
        {
            if ((a[i][j].jucator == 2) && (i != l1) && (i != l2) && (j != c1) && (j != c2) && (a[i][j].marimePiesa > marime))
            {
                ok = 1;
                liniaInitiala = i; coloanaInitiala = j;
            }
        }

    if (ok == 1) muta_o_piesa_min_strat(a, liniaInitiala, coloanaInitiala, linia, coloana);
}

void mutare3_min_strat(matrice a[3][3], int linia, int coloana, int& rez)
{
    int c1, l1, c2, l2, calculator = 2, ok1 = 0;
    ///verificam daca castiga pe coloana
    if (linia == 1) { if (a[linia - 1][coloana].jucator == 1 && a[linia + 1][coloana].jucator == 1) c1 = c2 = coloana; l1 = linia - 1; l2 = linia + 1; ok1 = 1; }
    if (linia == 0) { if (a[linia + 1][coloana].jucator == 1 && a[linia + 2][coloana].jucator == 1) c1 = c2 = coloana; l1 = linia + 1; l2 = linia + 2; ok1 = 1; }
    if (linia == 2) { if (a[linia - 1][coloana].jucator == 1 && a[linia - 2][coloana].jucator == 1) c1 = c2 = coloana; l1 = linia - 2; l2 = linia - 1; ok1 = 1; }

    if (ok1 == 0)
    {
        ///verificam daca castigam pe linie
        if (coloana == 0) { if (a[linia][coloana + 1].jucator == 1 && a[linia][coloana + 2].jucator == 1) l1 = l2 = linia; c1 = coloana + 1; c2 = coloana + 2; ok1 = 1; }
        if (coloana == 1) { if (a[linia][coloana - 1].jucator == 1 && a[linia][coloana + 1].jucator == 1) l1 = l2 = linia; c1 = coloana - 1; c2 = coloana + 1; ok1 = 1; }
        if (coloana == 2) { if (a[linia][coloana - 1].jucator == 1 && a[linia][coloana - 2].jucator == 1) l1 = l2 = linia; c1 = coloana - 1; c2 = coloana - 2; ok1 = 1; }
    }
    if (ok1 == 0)
    {
        ///verificam daca castiga pe diagonala
        if (linia == 0 && coloana == 0) { if (a[1][1].jucator == 1 && a[2][2].jucator == 1) { l1 = 1; c1 = 1; l2 = 2; c2 = 2; } }
        if (linia == 0 && coloana == 2) { if (a[1][1].jucator == 1 && a[2][0].jucator == 1) { l1 = 1; c1 = 1; l2 = 2; c2 = 0; } }
        if (linia == 2 && coloana == 0) { if (a[1][1].jucator == 1 && a[0][2].jucator == 1) { l1 = 1; c1 = 1; l2 = 0; c2 = 2; } }
        if (linia == 2 && coloana == 2) { if (a[1][1].jucator == 1 && a[0][0].jucator == 1) { l1 = 1; c1 = 1; l2 = 0; c2 = 0; } }
        if (linia == 1 && coloana == 1)
        {
            if (a[0][0].jucator == 1 && a[2][2].jucator == 1) { l1 = 0; c1 = 0; l2 = 2; c2 = 2; }
            else { if (a[2][0].jucator == 1 && a[0][2].jucator == 1) { l1 = 0; c1 = 2; l2 = 2; c2 = 0; } }
        }
    }
    int sePuede = 1;
    if (a[l1][c1].marimePiesa == 3 && a[l2][c2].marimePiesa == 3) sePuede = 0;

    if (!sePuede)
    {
        if (verifica_daca_mai_are_piese_mari_min_strat(calculator) == 1)
        {
            pune_o_piesa_min_strat(a, linia, coloana, calculator, 3); rez = 1;
        }
        else
        {
            int i, j, ok = 0;
            for (i = 0; i < 3 && !ok; ++i)
                for (j = 0; j < 3 && !ok; ++j)
                {
                    if (a[i][j].jucator == 2 && a[i][j].marimePiesa == 3)
                    {
                        muta_o_piesa_min_strat(a, i, j, linia, coloana);
                        ok = 1;
                        rez = 1;
                    }
                }
        }
    }

    if (sePuede || rez == 0)
    {
        if (verifica_daca_mai_are_piese_min_strat(calculator) == 1)
        {
            int dimensiune = decide_dimensiunea_min_strat();
            if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, l1, c1, calculator, dimensiune) == 1) { pune_o_piesa_min_strat(a, l1, c1, calculator, dimensiune); rez = 1; }
            else if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, l2, c2, calculator, dimensiune) == 1) { pune_o_piesa_min_strat(a, l2, c2, calculator, dimensiune); rez = 1; }
        }
        if (verifica_daca_mai_are_piese_min_strat(calculator) == 0 || rez == 0)
        {
            int ok = 0, i, j;
            for (i = 0; i < 3 && !ok; ++i)
                for (j = 0; j < 3 && !ok; ++j)
                {
                    if (a[i][j].jucator == 2)
                    {
                        int dimensiune = a[i][j].marimePiesa;
                        if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, l1, c1, calculator, dimensiune) == 1)
                        {
                            ok = 1;
                            muta_o_piesa_min_strat(a, i, j, l1, c1);
                            rez = 1;
                        }
                        else
                        {
                            if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, l2, c2, calculator, dimensiune) == 1)
                            {
                                ok = 1;
                                muta_o_piesa_min_strat(a, i, j, l2, c2);
                                rez = 1;
                            }
                        }
                    }
                }
        }

    }

}
int inMarice_min_strat(int i, int j)
{
    if (i < 0) return 0;
    if (j < 0) return 0;
    if (i > 2) return 0;
    if (j > 2) return 0;
}
int cauta_pozitia_min_strat(matrice a[3][3], int i, int j, int& linia, int& coloana, int dimensiune)
{
    int calculator = 2;
    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i, j + 1, calculator, dimensiune) == 1 && inMarice_min_strat(i, j + 1) == 1) { linia = i; coloana = j + 1; return 1; }
    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i, j - 1, calculator, dimensiune) == 1 && inMarice_min_strat(i, j - 1) == 1) { linia = i; coloana = j - 1; return 1; }
    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i + 1, j, calculator, dimensiune) == 1 && inMarice_min_strat(i + 1, j) == 1) { linia = i + 1; coloana = j; return 1; }
    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i - 1, j, calculator, dimensiune) == 1 && inMarice_min_strat(i - 1, j) == 1) { linia = i - 1; coloana = j; return 1; }
    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i + 1, j + 1, calculator, dimensiune) == 1 && inMarice_min_strat(i + 1, j + 1) == 1) { linia = i + 1; coloana = j + 1; return 1; }
    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i + 1, j - 1, calculator, dimensiune) == 1 && inMarice_min_strat(i + 1, j - 1) == 1) { linia = i + 1; coloana = j - 1; return 1; }
    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i - 1, j + 1, calculator, dimensiune) == 1 && inMarice_min_strat(i - 1, j + 1) == 1) { linia = i - 1; coloana = j + 1; return 1; }
    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i - 1, j - 1, calculator, dimensiune) == 1 && inMarice_min_strat(i - 1, j - 1) == 1) { linia = i - 1; coloana = j - 1; return 1; }
    return 0;
}

void randul_calculatorului_min_strat(matrice a[3][3])
{
    int r = 0, linia = -1, coloana = -1, calculator = 2, dimensiune, jucatorul = 1, amMutat = 0;
    verifica_daca_poate_castiga_min_strat(a, calculator, linia, coloana, r);
    if (r == 1) ///putem noi castiga
    {
        if (a[linia][coloana].jucator == 0)
        {
            if (verifica_daca_mai_are_piese_min_strat(calculator) == 1)
            {
                int dimensiune = decide_dimensiunea_min_strat();
                pune_o_piesa_min_strat(a, linia, coloana, calculator, dimensiune);
                if (a[linia][coloana].jucator == 2) amMutat = 1;
            }
            else
            {
                mutare1_min_strat(a, linia, coloana);
                if (a[linia][coloana].jucator == 2) amMutat = 1;
            }
        }
        else
        {
            if (a[linia][coloana].marimePiesa != 3)
            {
                if (verifica_daca_mai_are_piese_min_strat(calculator) == 1)
                {
                    dimensiune = decide_dimensiunea_min_strat();
                    if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, linia, coloana, calculator, dimensiune) == 1)
                    {
                        pune_o_piesa_min_strat(a, linia, coloana, calculator, dimensiune);
                        amMutat = 1;
                    }
                }
                if (verifica_daca_mai_are_piese_min_strat(calculator) == 0 || amMutat == 0)
                {
                    mutare2_min_strat(a, linia, coloana);
                    if (a[linia][coloana].jucator == 2) amMutat = 1;
                }
            }
        }
    }

    if (amMutat == 0)
    {
        verifica_daca_poate_castiga_min_strat(a, jucatorul, linia, coloana, r);
        if (r == 1) ///poate el castiga
        {
            if (a[linia][coloana].jucator == 0)
            {
                dimensiune = decide_dimensiunea_min_strat();
                if (dimensiune != -1) { pune_o_piesa_min_strat(a, linia, coloana, calculator, dimensiune); amMutat = 1; }
                else
                {
                    int liniaInitiala, coloanaInitiala;

                    int i, j, ok = 0, dimensiune = 0;
                    for (i = 0; i < 3 && !ok; ++i)
                        for (j = 0; j < 3 && !ok; ++j)
                        {
                            if (a[i][j].jucator == 2 && a[i][j].marimePiesa > dimensiune)
                            {
                                ok = 1;
                                liniaInitiala = i; coloanaInitiala = j;
                            }
                        }
                    if (ok == 1) { muta_o_piesa_min_strat(a, liniaInitiala, coloanaInitiala, linia, coloana); amMutat = 1; }
                }
            }
            else ///unde poate el castiga este o piesa de-a noastra

            {
                if (a[linia][coloana].marimePiesa != 3) ///daca piesa noastra nu e de 3 poate sa o acopere
                {
                    int areRost = verifica_daca_poate_acoperi_piesa_min_strat(a[linia][coloana].marimePiesa, jucatorul);
                    if (areRost) ///poate sa puna o piesa peste a noastra
                    {
                        mutare3_min_strat(a, linia, coloana, amMutat);
                    }
                }
            }
        }

    }

    if (amMutat == 0)
    {
        ///nu castiga nimeni :( off
        if (numarPieseMari2 == 0 && numarPieseMici2 == 0 && numarPieseMedii2 == 0)
        {
            int l, c, d;
            l = 1; c = 1;
            d = decide_dimensiunea_min_strat();
            if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, l, c, calculator, d) == 1) { pune_o_piesa_min_strat(a, l, c, calculator, d); amMutat = 1; }
            else
            {
                int i, j, ok = 0;
                for (i = 0; i < 3 && !ok; ++i)
                    for (j = 0; j < 3 && !ok; ++j)
                    {
                        if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i, j, calculator, d) == 1)
                        {
                            pune_o_piesa_min_strat(a, i, j, calculator, d);
                            ok = 1;
                            amMutat = 1;
                        }
                    }
            }
        }

        else
        {
            if (verifica_daca_mai_are_piese_min_strat(calculator) == 1)
            {
                dimensiune = decide_dimensiunea_min_strat();
                int i, j, ok = 0, lf, cf;
                for (i = 0; i <= 2 && !ok; ++i)
                    for (j = 0; j <= 2 && !ok; ++j)
                    {
                        if (a[i][j].jucator == 2)
                        {
                            if (cauta_pozitia_min_strat(a, i, j, lf, cf, dimensiune) == 1)
                            {
                                ok = 1;
                                pune_o_piesa_min_strat(a, lf, cf, calculator, dimensiune);
                                amMutat = 1;
                            }
                        }
                    }
            }
            else
            {
                int i, j, li, lf, ci, cf, d = 0, ok = 0;
                for (i = 0; i <= 2; ++i)
                    for (j = 0; j <= 2; ++j)
                    {
                        if (a[i][j].jucator == 2 && a[i][j].marimePiesa > d)
                        {
                            d = a[i][j].marimePiesa;
                            li = i; ci = j;
                        }
                    }
                for (i = 0; i <= 2 && !ok; ++i)
                    for (j = 0; j <= 2 && !ok; ++j)
                    {
                        if (verifica_daca_se_poate_pune_o_piesa_min_strat(a, i, j, calculator, d) == 1)
                        {
                            lf = i; cf = j; ok = 1;
                        }
                    }
                muta_o_piesa_min_strat(a, li, ci, lf, cf);
                amMutat = 1;
            }
        }

    }

}

/////////////////////////////
// MEDIUM STRATEGY STOPS HERE
/////////////////////////////

///asta imi trebuie doar ca sa afisez matricea in main sa vad ce mutari face calculatorul

void adaugare(stiva piese[3], int jucatorul, int marime)
{
    piese[2].player = piese[1].player;
    piese[2].dimensiune = piese[1].dimensiune;
    piese[1].player = piese[0].player;
    piese[1].dimensiune = piese[0].dimensiune;

    piese[0].player = jucatorul;
    piese[0].dimensiune = marime;
}

int verifica_daca_mai_are_piese_mici(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMici1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMici2 == 2) return 0;
        return 1;
    }
}

int verifica_daca_mai_are_piese_medii(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMedii1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMedii2 == 2) return 0;
        return 1;
    }
}

int verifica_daca_mai_are_piese_mari(int jucator)
{
    if (jucator == 1)
    {
        if (numarPieseMari1 == 2) return 0;
        return 1;
    }
    else
    {
        if (numarPieseMari2 == 2) return 0;
        return 1;
    }
}


int verifica_daca_mai_are_piese(int jucator)
{
    if (verifica_daca_mai_are_piese_mari(jucator) == 1 || verifica_daca_mai_are_piese_medii(jucator) == 1 || verifica_daca_mai_are_piese_mici(jucator) == 1) return 1;
    return 0;
}


int mutarea_calculatorului(matrice a[3][3])
{
    int calculator = 2, decizie = 0;
    if (numarPieseMari2 == 0 && numarPieseMedii2 == 0 && numarPieseMici2 == 0) decizie = 0;
    else
    {
        if (verifica_daca_mai_are_piese(calculator) == 1) decizie = rand() % 2;
        else decizie = 1; ///sa mute o piesa
    }
    return decizie;
}

void muta_o_piesa_pentru_calculator(matrice a[3][3], int& type, int& line, int& col, int& origy, int& origx)
{
    int i, j, ok = 0, liniaFinala, coloanaFinala, calculator = 2, liniaInitiala, coloanaInitiala, dimensiune = 0;
    for (i = 0; i <= 2; ++i)
        for (j = 0; j <= 2; ++j)
        {
            if (a[i][j].jucator == 2 && a[i][j].marimePiesa > dimensiune)
            {
                dimensiune = a[i][j].marimePiesa;
                liniaInitiala = i;
                coloanaInitiala = j;
            }
        }
    ok = 0;
    do
    {
        liniaFinala = rand() % 3;
        coloanaFinala = rand() % 3;
        ok = verifica_daca_se_poate_pune_o_piesa(a, liniaFinala, coloanaFinala, calculator, dimensiune);
    } while (ok == 0);

    type = a[liniaInitiala][coloanaInitiala].marimePiesa;
    line = liniaFinala;
    col = coloanaFinala;
    origy = liniaInitiala;
    origx = coloanaInitiala;
    muta_o_piesa(a, liniaInitiala, coloanaInitiala, liniaFinala, coloanaFinala);
}


void adauga_o_piesa_pentru_calculator(matrice a[3][3], int& type, int& line, int& col)
{
    int dimensiune = 0, calculator = 2, ok = 0;
    int linie = 0, coloana = 0, ok2 = 0;
    do
    {
        dimensiune = rand() % 3 + 1;
        type = dimensiune;
        ok2 = verifica_daca_mai_are_un_tip_de_piese(dimensiune, calculator);
    } while (ok2 == 0);

    do
    {
        linie = rand() % 3;
        line = linie;
        coloana = rand() % 3;
        col = coloana;
        ok = verifica_daca_se_poate_pune_o_piesa(a, linie, coloana, calculator, dimensiune);
    } while (ok == 0);
    pune_o_piesa(a, linie, coloana, calculator, dimensiune);
}

void stergere(stiva piese[3])
{

    piese[0].player = piese[1].player;
    piese[0].dimensiune = piese[1].dimensiune;
    piese[1].player = piese[2].player;
    piese[1].dimensiune = piese[2].dimensiune;
    piese[2].player = 0;
    piese[2].dimensiune = 0;
}

int verifica_daca_a_castigat(matrice a[3][3])
{
    int i, j;

    for (i = 0; i <= 2; ++i)
    {
        if ((a[i][0].jucator == a[i][1].jucator) && (a[i][1].jucator == a[i][2].jucator) && (a[i][0].jucator != 0)) return a[i][1].jucator;
    }
    for (j = 0; j <= 2; j++)
    {
        if ((a[0][j].jucator == a[1][j].jucator) && (a[1][j].jucator == a[2][j].jucator) && (a[0][j].jucator != 0)) return a[2][j].jucator;
    }
    if ((a[0][0].jucator == a[1][1].jucator) && (a[1][1].jucator == a[2][2].jucator) && (a[0][0].jucator != 0)) a[0][0].jucator;
    if ((a[2][0].jucator == a[1][1].jucator) && (a[1][1].jucator == a[0][2].jucator) && (a[2][0].jucator != 0)) a[0][2].jucator;
    return 0;
}

void pune_o_piesa(matrice a[3][3], int linie, int coloana, int jucatorul, int marime)
{
    a[linie][coloana].jucator = jucatorul;
    a[linie][coloana].marimePiesa = marime;
    adaugare(a[linie][coloana].piese, jucatorul, marime);
    if (jucatorul == 1)
    {
        if (marime == 1) numarPieseMici1++;
        else
        {
            if (marime == 3) numarPieseMari1++;
            else numarPieseMedii1++;
        }
    }
    else
    {
        if (marime == 1) numarPieseMici2++;
        else
        {
            if (marime == 3) numarPieseMari2++;
            else numarPieseMedii2++;
        }
    }
}

int verifica_daca_se_poate_pune_o_piesa(matrice a[3][3], int linie, int coloana, int jucatorul, int marime)
{

    if (a[linie][coloana].jucator == 0) return 1;
    if (a[linie][coloana].marimePiesa >= marime) return 0;
    return 1;
}

int verifica_daca_piesa_are_marimea_corecta(int marime)
{
    if (marime < 1 || marime>3) return 0;
    return 1;
}

int verifica_daca_mai_are_un_tip_de_piese(int marime, int jucatorul)
{
    if (marime == 1)
    {
        if (verifica_daca_mai_are_piese_mici(jucatorul) == 0) return 0;
        return 1;
    }
    else
    {
        if (marime == 2)
        {
            if (verifica_daca_mai_are_piese_medii(jucatorul) == 0) return 0;
            return 1;
        }

        else
        {
            if (verifica_daca_mai_are_piese_mari(jucatorul) == 0) return 0;
            else return 1;
        }
    }
}



void muta_o_piesa(matrice a[3][3], int liniaInitiala, int coloanaInitiala, int liniaFinala, int coloanaFinala)
{
    a[liniaFinala][coloanaFinala].jucator = a[liniaInitiala][coloanaInitiala].jucator;
    a[liniaFinala][coloanaFinala].marimePiesa = a[liniaInitiala][coloanaInitiala].marimePiesa;
    adaugare(a[liniaFinala][coloanaFinala].piese, a[liniaFinala][coloanaFinala].jucator, a[liniaFinala][coloanaFinala].marimePiesa);
    stergere(a[liniaInitiala][coloanaInitiala].piese);
    a[liniaInitiala][coloanaInitiala].jucator = a[liniaInitiala][coloanaInitiala].piese[0].player;
    a[liniaInitiala][coloanaInitiala].marimePiesa = a[liniaInitiala][coloanaInitiala].piese[0].dimensiune;

}

void randul_calculatorului(matrice a[3][3], int& decision, int& type, int& line, int& col, int& origy, int& origx)
{
    int decizie;
    decizie = mutarea_calculatorului(a);
    decision = decizie;
    if (decizie == 0) {
        adauga_o_piesa_pentru_calculator(a, type, line, col);
    }
    else muta_o_piesa_pentru_calculator(a, type, line, col, origy, origx);
}


void randul_jucatorului(matrice a[3][3], int originy, int originx, int posy, int posx, int jucatorul, int dimensiune)
{

    if (originy == -1)
    {
        mutareaAnterioara.tip = 1;
        mutareaAnterioara.dimensiuneaPiesei = dimensiune;
        mutareaAnterioara.l = posy;
        mutareaAnterioara.c = posx;
        pune_o_piesa(a, posy, posx, jucatorul, dimensiune);
    }
    else
    {

        mutareaAnterioara.tip = 2;
        mutareaAnterioara.li = originy;
        mutareaAnterioara.ci = originx;
        mutareaAnterioara.lf = posy;
        mutareaAnterioara.cf = posx;
        muta_o_piesa(a, originy, originx, posy, posx);
    }

}


int w = GetSystemMetrics(SM_CXSCREEN);
int h = GetSystemMetrics(SM_CYSCREEN);
int smol = 25, medium = 45, large = 65;

void winScreen(int player);

void infoScreen() {
    cleardevice();
    readimagefile("info.jpg", 0, 0, w, h);
    readimagefile("close.gif", 25, 25, 75, 75);

    bool infoScreen = true;

    setmousequeuestatus(WM_LBUTTONUP, true);

    int mousex = 0, mousey = 0, newx = 0, newy = 0;

    while (infoScreen) {
        getmouseclick(WM_LBUTTONUP, newx, newy);
        if (newx != mousex || newy != mousey) {
            mousex = newx;
            mousey = newy;
            if (mousex >= 25 && mousex <= 75 && mousey >= 25 && mousey <= 75) {
                infoScreen = false;
                homeScreen();
            }
        }
    }
}

struct piece {
    int type, team;
    bool onboard;
};

struct boardState {
    int leftx, lefty, stackL = 0;
    piece stack[3];
} board[3][3];

struct pieces {
    int leftx, lefty, boardx, boardy;
    piece piece;
} p1[3][2], p2[3][2];

bool addPiece(int i, int j, piece piece) {

    cout << endl << "Adding piece to: " << i << " " << j;

    bool valid = true;

    for (int x = 0; x < board[i][j].stackL; x++) {
        if (board[i][j].stack[x].type >= piece.type) valid = false;
    }
    if (board[i][j].stackL == 3) valid = false;

    char path[7];

    if (piece.team == 1) strcpy(path, "g1.gif");
    else strcpy(path, "g2.gif");
    setlinestyle(SOLID_LINE, 1, 3);

    if (valid) {
        board[i][j].stack[board[i][j].stackL] = piece;
        board[i][j].stack[board[i][j].stackL].onboard = true;
        board[i][j].stackL++;
        if (piece.type == 1) {
            readimagefile(path, board[i][j].leftx + 86, board[i][j].lefty + 75, board[i][j].leftx + 114, board[i][j].lefty + 125);
        }
        else if (piece.type == 2) {
            readimagefile(path, board[i][j].leftx + 71, board[i][j].lefty + 50, board[i][j].leftx + 128, board[i][j].lefty + 150);
        }
        else {
            readimagefile(path, board[i][j].leftx + 57, board[i][j].lefty + 25, board[i][j].leftx + 143, board[i][j].lefty + 175);
        }
    }
    return valid;

}

void removePieceFromSide(int x, int y, int team) {
    setcolor(COLOR(235, 235, 235));
    setbkcolor(COLOR(235, 235, 235));
    setfillstyle(SOLID_FILL, COLOR(235, 235, 235));

    if (team == 1) {
        bar(p1[x][y].leftx, p1[x][y].lefty, p1[x][y].leftx + 150, p1[x][y].lefty + 150);
    }
    else {
        bar(p2[x][y].leftx, p2[x][y].lefty, p2[x][y].leftx + 150, p2[x][y].lefty + 150);
    }
}

void removePieceFromBoard(int x, int y) {
    setcolor(COLOR(235, 235, 235));
    setbkcolor(COLOR(235, 235, 235));
    setfillstyle(SOLID_FILL, COLOR(235, 235, 235));
    board[x][y].stackL = board[x][y].stackL - 1;
    if (board[x][y].stackL > 0) {
        int type = board[x][y].stack[board[x][y].stackL - 1].type;
        int team = board[x][y].stack[board[x][y].stackL - 1].team;
        char path[7];
        if (team == 1) strcpy(path, "g1.gif");
        else strcpy(path, "g2.gif");
        setfillstyle(SOLID_FILL, COLOR(235, 235, 235));
        bar(board[x][y].leftx + 10, board[x][y].lefty + 10, board[x][y].leftx + 180, board[x][y].lefty + 180);
        if (type == 1) {
            readimagefile(path, board[x][y].leftx + 86, board[x][y].lefty + 75, board[x][y].leftx + 114, board[x][y].lefty + 125);
        }
        else if (type == 2) {
            readimagefile(path, board[x][y].leftx + 71, board[x][y].lefty + 50, board[x][y].leftx + 128, board[x][y].lefty + 150);
        }
        else {
            readimagefile(path, board[x][y].leftx + 57, board[x][y].lefty + 25, board[x][y].leftx + 143, board[x][y].lefty + 175);
        }
    }
    else {
        setfillstyle(SOLID_FILL, COLOR(235, 235, 235));
        bar(board[x][y].leftx + 10, board[x][y].lefty + 10, board[x][y].leftx + 180, board[x][y].lefty + 180);
    }
}

void putPieceBack(int x, int y, piece piece, int originx, int originy) {

    if (piece.team == 1) setcolor(RED);
    else setcolor(BLUE);

    if (piece.onboard) {
        addPiece(originx, originy, piece);
    }
    else {
        if (piece.team == 1) {
            if (p1[x][y].piece.type == 1) readimagefile("g1.gif", p1[x][y].leftx + 61, p1[x][y].lefty + 50, p1[x][y].leftx + 89, p1[x][y].lefty + 100);
            else if (p1[x][y].piece.type == 2) readimagefile("g1.gif", p1[x][y].leftx + 49, p1[x][y].lefty + 30, p1[x][y].leftx + 100, p1[x][y].lefty + 120);
            else readimagefile("g1.gif", p1[x][y].leftx + 38, p1[x][y].lefty + 10, p1[x][y].leftx + 111, p1[x][y].lefty + 140);
        }
        else {
            if (p2[x][y].piece.type == 1) readimagefile("g2.gif", p2[x][y].leftx + 61, p2[x][y].lefty + 50, p2[x][y].leftx + 89, p2[x][y].lefty + 100);
            else if (p2[x][y].piece.type == 2) readimagefile("g2.gif", p2[x][y].leftx + 49, p2[x][y].lefty + 30, p2[x][y].leftx + 100, p2[x][y].lefty + 120);
            else readimagefile("g2.gif", p2[x][y].leftx + 38, p2[x][y].lefty + 10, p2[x][y].leftx + 111, p2[x][y].lefty + 140);
        }
    }
}

void whichPiece(int& x, int& y, pieces a[3][2], int mousex, int mousey) {
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 2; j++)
            if (mousex >= a[i][j].leftx && mousex <= a[i][j].leftx + 1503
                && mousey >= a[i][j].lefty && mousey <= a[i][j].lefty + 150) {
                x = i;
                y = j;
            }
}

void printSides();

piece findOfSize(int type, int p) {
    int i, j;
    piece x;
    if (p == 1) {
        int found = 0;
        for (i = 0; i < 3; i++)
            for (j = 0; j < 2; j++)
                if (p1[i][j].piece.type == type && p1[i][j].piece.onboard == false && found == 0) {
                    x = p1[i][j].piece;
                    p1[i][j].piece.onboard = true;
                    removePieceFromSide(i, j, 1);
                    found = 1;
                }
    }
    else {
        int found = 0;
        for (i = 0; i < 3; i++)
            for (j = 0; j < 2; j++)
                if (p2[i][j].piece.type == type && p2[i][j].piece.onboard == false && found == 0) {
                    x = p2[i][j].piece;
                    p2[i][j].piece.onboard = true;
                    removePieceFromSide(i, j, 2);
                    found = 1;
                }
    }

    printSides();

    return x;
}

void printSides() {
    int i, j;

    cout << endl << "SIDE 1: ";
    cout << endl;
    for (int i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) cout << p1[i][j].piece.onboard;
        cout << endl;
    }
    cout << endl << "SIDE 2: ";
    cout << endl;
    for (int i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) cout << p2[i][j].piece.onboard;
        cout << endl;
    }

}


void gameScreen() {

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) board[i][j].stackL = 0;

    if (player1 == 2) currentPlayer = 1;
    else if (player2 == 2) currentPlayer = 2;
    else currentPlayer = (rand() % 2) + 1;

    readimagefile("bg.jpg", 0, 0, w, h);
    setlinestyle(SOLID_LINE, 1, 7);
    setfillstyle(SOLID_FILL, COLOR(235, 235, 235));
    setcolor(BLACK);

    int squarex = (w - 600) / 2, squarey = (h - 600) / 2;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j].leftx = squarex + 200 * i;
            board[i][j].lefty = squarey + 200 * j;
            bar(board[i][j].leftx, board[i][j].lefty, board[i][j].leftx + 200, board[i][j].lefty + 200);
        }
    }

    line(squarex, squarey, squarex, squarey + 600);
    line(squarex, squarey, squarex + 600, squarey);
    line(squarex + 600, squarey, squarex + 600, squarey + 600);
    line(squarex, squarey + 600, squarex + 600, squarey + 600);

    for (int i = 1; i <= 2; i++) {
        line(squarex + 200 * i, squarey, squarex + 200 * i, squarey + 600);
        line(squarex, squarey + 200 * i, squarex + 600, squarey + 200 * i);
    }

    setmousequeuestatus(WM_LBUTTONUP, true);

    int mousex = 0, mousey = 0, newx = 0, newy = 0;

    int fPieceX = (squarex - 300) / 2, fPieceY = (h - 450) / 2,
        sPieceX = (squarex + 600) + (w - (squarex + 600) - 300) / 2, sPieceY = (h - 450) / 2;

    setlinestyle(DOTTED_LINE, 1, 4);

    putpixel(sPieceX, sPieceY, 0);

    p1[0][0].leftx = fPieceX;
    p1[0][0].lefty = fPieceY;
    p2[0][0].leftx = sPieceX;
    p2[0][0].lefty = sPieceY;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++) {
            if (i == 0) {
                p1[i][j].piece.type = 1;
                p2[i][j].piece.type = 1;
            }
            else if (i == 1) {
                p1[i][j].piece.type = 2;
                p2[i][j].piece.type = 2;
            }
            else {
                p1[i][j].piece.type = 3;
                p2[i][j].piece.type = 3;
            }
            p1[i][j].piece.team = 1;
            p2[i][j].piece.team = 2;
            p1[i][j].piece.onboard = false;
            p2[i][j].piece.onboard = false;
        }

    p1[0][1].leftx = p1[0][0].leftx + 150;
    p1[0][1].lefty = p1[0][0].lefty;
    p2[0][1].leftx = p2[0][0].leftx + 150;
    p2[0][1].lefty = p2[0][0].lefty;

    for (int i = 1; i < 3; i++)
        for (int j = 0; j < 2; j++) {
            if (j == 0) {
                p1[i][j].leftx = p1[i - 1][j].leftx;
                p1[i][j].lefty = p1[i - 1][j].lefty + 150;
                p2[i][j].leftx = p2[i - 1][j].leftx;
                p2[i][j].lefty = p2[i - 1][j].lefty + 150;
            }
            else {
                p1[i][j].leftx = p1[i][j - 1].leftx + 150;
                p1[i][j].lefty = p1[i][j - 1].lefty;
                p2[i][j].leftx = p2[i][j - 1].leftx + 150;
                p2[i][j].lefty = p2[i][j - 1].lefty;
            }
        }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            bar(p1[i][j].leftx, p1[i][j].lefty, p1[i][j].leftx + 150, p1[i][j].lefty + 150);
            bar(p2[i][j].leftx, p2[i][j].lefty, p2[i][j].leftx + 150, p2[i][j].lefty + 150);
            if (p1[i][j].piece.type == 1) {
                setcolor(RED);
                readimagefile("g1.gif", p1[i][j].leftx + 61, p1[i][j].lefty + 50, p1[i][j].leftx + 89, p1[i][j].lefty + 100);
                setcolor(BLUE);
                readimagefile("g2.gif", p2[i][j].leftx + 61, p2[i][j].lefty + 50, p2[i][j].leftx + 89, p2[i][j].lefty + 100);
            }
            else if (p1[i][j].piece.type == 2) {
                setcolor(RED);
                readimagefile("g1.gif", p1[i][j].leftx + 49, p1[i][j].lefty + 30, p1[i][j].leftx + 100, p1[i][j].lefty + 120);
                setcolor(BLUE);
                readimagefile("g2.gif", p2[i][j].leftx + 49, p2[i][j].lefty + 30, p2[i][j].leftx + 100, p2[i][j].lefty + 120);
            }
            else {
                setcolor(RED);
                readimagefile("g1.gif", p1[i][j].leftx + 38, p1[i][j].lefty + 10, p1[i][j].leftx + 111, p1[i][j].lefty + 140);
                setcolor(BLUE);
                readimagefile("g2.gif", p2[i][j].leftx + 38, p2[i][j].lefty + 10, p2[i][j].leftx + 111, p2[i][j].lefty + 140);
            }
        }
    }

    setlinestyle(SOLID_LINE, 1, 5);

    line(fPieceX, fPieceY, fPieceX + 300, fPieceY);
    line(fPieceX, fPieceY, fPieceX, fPieceY + 450);
    line(fPieceX, fPieceY + 450, fPieceX + 300, fPieceY + 450);
    line(fPieceX + 300, fPieceY, fPieceX + 300, fPieceY + 450);
    line(sPieceX, sPieceY, sPieceX + 300, sPieceY);
    line(sPieceX, sPieceY, sPieceX, sPieceY + 450);
    line(sPieceX, sPieceY + 450, sPieceX + 300, sPieceY + 450);
    line(sPieceX + 300, sPieceY, sPieceX + 300, sPieceY + 450);

    int next1 = textwidth("Player 1 now has to move"),
        next2 = textwidth("Player 2 now has to move");

    bool picked = false;
    int pickx, picky, originx = 1, originy = 1;
    piece pickedPiece;

    setbkcolor(COLOR(0, 0, 0));
    setcolor(WHITE);

    if (currentPlayer == 1) {
        outtextxy((w - next1) / 2, h - 100, "Player 1 now has to move");
    }
    else {
        outtextxy((w - next1) / 2, h - 100, "Player 2 now has to move");
    }

    int tur = 0;

    int win;

    while (!stadiul) {
        if (currentPlayer == 1 && player1 == 2 && difLeftLev == 1 || currentPlayer == 2 && player2 == 2 && difRightLev == 1) {
            int wp;
            if (currentPlayer == 1) wp = 1;
            else wp = 2;
            int decision, type, line, col, origy, origx;
            randul_calculatorului(a, decision, type, line, col, origy, origx);
            if (decision == 0) {
                piece x = findOfSize(type, wp);
                addPiece(col, line, x);
                afisare(a);
            }
            else {
                removePieceFromBoard(origx, origy);
                addPiece(col, line, board[origx][origy].stack[board[origx][origy].stackL]);
                afisare(a);
            }
            setbkcolor(COLOR(0, 0, 0));
            setcolor(WHITE);
            if (currentPlayer == 1) {
                currentPlayer = 2;
                outtextxy((w - next1) / 2, h - 100, "Player 2 now has to move");
            }
            else {
                currentPlayer = 1;
                outtextxy((w - next1) / 2, h - 100, "Player 1 now has to move");
            }
            win = verifica_daca_a_castigat(a);
            if (win) {
                stadiul = 1;
                winScreen(win);
            }
        }
        else if (currentPlayer == 1 && player1 == 2 && difLeftLev == 2 || currentPlayer == 2 && player2 == 2 && difRightLev == 2) {
            randul_calculatorului_min_strat(a);
            if (g.change) {
                if (g.decision == 0) {
                    piece x;
                    if (currentPlayer == 1) x = findOfSize(g.type, 2);
                    else x = findOfSize(g.type, 2);
                    addPiece(g.fc, g.fl, x);
                }
                else {
                    removePieceFromBoard(g.ol, g.oc);
                    addPiece(g.fl, g.fc, board[g.ol][g.oc].stack[board[g.ol][g.oc].stackL]);
                }
                g.change = false;
            }
            afisare(a);
            setbkcolor(COLOR(0, 0, 0));
            setcolor(WHITE);
            if (currentPlayer == 1) {
                currentPlayer = 2;
                outtextxy((w - next1) / 2, h - 100, "Player 2 now has to move");
            }
            else {
                currentPlayer = 1;
                outtextxy((w - next1) / 2, h - 100, "Player 1 now has to move");
            }
            win = verifica_daca_a_castigat(a);
            if (win) {
                stadiul = 1;
                winScreen(win);
            }
        }
        else if (currentPlayer == 1 && player1 == 2 && difLeftLev == 3 || currentPlayer == 2 && player2 == 2 && difRightLev == 3) {
            mutarea_calculatorului_strat(a, tur);
            cout << endl << "DISPLAY AFTER RETURN: " << endl;
            afisare(a);
            if (g.change) {
                if (g.decision == 0) {
                    piece x;
                    if (currentPlayer == 1) x = findOfSize(g.type, 2);
                    else x = findOfSize(g.type, 2);
                    addPiece(g.fl, g.fc, x);
                }
                else {
                    removePieceFromBoard(g.ol, g.oc);
                    addPiece(g.fl, g.fc, board[g.ol][g.oc].stack[board[g.ol][g.oc].stackL]);
                }
                g.change = false;
            }
            cout << endl << "FINAL DISPLAY" << endl;
            afisare(a);
            setbkcolor(COLOR(0, 0, 0));
            setcolor(WHITE);
            if (currentPlayer == 1) {
                currentPlayer = 2;
                outtextxy((w - next1) / 2, h - 100, "Player 2 now has to move");
            }
            else {
                currentPlayer = 1;
                outtextxy((w - next1) / 2, h - 100, "Player 1 now has to move");
            }
            win = verifica_daca_a_castigat(a);
            if (win) {
                stadiul = 1;
                winScreen(win);
            }
        }
        else {
            getmouseclick(WM_LBUTTONUP, newx, newy);
            if (newx != mousex || newy != mousey) {
                mousex = newx;
                mousey = newy;
                if (mousex >= squarex && mousex <= squarex + 600 && mousey >= squarey && mousey <= squarey + 600) {
                    int posx, posy;
                    if (mousex > squarex&& mousex < squarex + 200) posx = 0;
                    if (mousex > squarex + 200 && mousex < squarex + 200 * 2) posx = 1;
                    if (mousex > squarex + 200 * 2 && mousex < squarex + 200 * 3) posx = 2;
                    if (mousey > squarey&& mousey < squarey + 200) posy = 0;
                    if (mousey > squarey + 200 && mousey < squarey + 200 * 2) posy = 1;
                    if (mousey > squarey + 200 * 2 && mousey < squarey + 200 * 3) posy = 2;
                    if (picked) {
                        mutareaAnterioara.tip = 0; mutareaAnterioara.l = 0; mutareaAnterioara.c = 0; mutareaAnterioara.li = 0; mutareaAnterioara.ci = 0;
                        mutareaAnterioara.lf = 0; mutareaAnterioara.cf = 0;
                        bool valid;
                        int win = 0;
                        if (pickedPiece.team == 1) {
                            valid = addPiece(posx, posy, pickedPiece);
                            if (!valid) {
                                putPieceBack(pickx, picky, pickedPiece, originx, originy);
                            }
                            else {
                                if (pickedPiece.onboard) {
                                    randul_jucatorului(a, originy, originx, posy, posx, pickedPiece.team, pickedPiece.type);
                                }
                                else {
                                    mutareaAnterioara.tip = 1;
                                    randul_jucatorului(a, -1, -1, posy, posx, pickedPiece.team, pickedPiece.type);
                                    p1[pickx][picky].piece.onboard = true;
                                }
                                win = verifica_daca_a_castigat(a);
                                if (win) {
                                    stadiul = 1;
                                    winScreen(win);
                                }
                            }
                            picked = false;
                            jucatorul = 2;
                        }
                        else {
                            valid = addPiece(posx, posy, pickedPiece);
                            if (!valid) {
                                putPieceBack(pickx, picky, pickedPiece, originx, originy);
                            }
                            else {
                                if (pickedPiece.onboard) {
                                    randul_jucatorului(a, originy, originx, posy, posx, pickedPiece.team, pickedPiece.type);
                                }
                                else {
                                    mutareaAnterioara.tip = 1;
                                    randul_jucatorului(a, -1, -1, posy, posx, pickedPiece.team, pickedPiece.type);
                                    p2[pickx][picky].piece.onboard = true;
                                }
                                win = verifica_daca_a_castigat(a);
                                if (win) {
                                    stadiul = 1;
                                    winScreen(win);
                                }
                            }
                            picked = false;
                        }
                        if (!win) {
                            setbkcolor(COLOR(0, 0, 0));
                            setcolor(WHITE);
                            if (valid) {
                                if (currentPlayer == 1) {
                                    currentPlayer = 2;
                                    outtextxy((w - next1) / 2, h - 100, "Player 2 now has to move");
                                }
                                else {
                                    currentPlayer = 1;
                                    outtextxy((w - next1) / 2, h - 100, "Player 1 now has to move");
                                }
                            }
                        }
                        afisare(a);
                    }
                    else {
                        if (board[posx][posy].stackL > 0) {
                            if (board[posx][posy].stack[board[posx][posy].stackL - 1].team == currentPlayer) {
                                removePieceFromBoard(posx, posy);
                                picked = true;
                                originx = posx;
                                originy = posy;
                                pickedPiece = board[posx][posy].stack[board[posx][posy].stackL];
                            }
                        }
                    }
                }
                else if (mousex >= fPieceX && mousex <= fPieceX + 300
                    && mousey >= fPieceY && mousey <= fPieceY + 450 && !picked && currentPlayer == 1) {
                    int x, y;
                    whichPiece(x, y, p1, mousex, mousey);
                    if (!p1[x][y].piece.onboard) {
                        picked = true;
                        pickx = x;
                        picky = y;
                        pickedPiece = p1[pickx][picky].piece;
                        removePieceFromSide(x, y, 1);
                    }
                }
                else if (mousex >= sPieceX && mousex <= sPieceX + 300
                    && mousey >= sPieceY && mousey <= sPieceY + 450 && !picked && currentPlayer == 2) {
                    int x, y;
                    whichPiece(x, y, p2, mousex, mousey);
                    if (!p2[x][y].piece.onboard) {
                        picked = true;
                        pickx = x;
                        picky = y;
                        pickedPiece = p2[pickx][picky].piece;
                        removePieceFromSide(x, y, 2);
                    }
                }
            }
        }
    }
}

void resetMatrix();

void winScreen(int player) {
    readimagefile("bg.jpg", 0, 0, w, h);
    settextstyle(TRIPLEX_SCR_FONT, HORIZ_DIR, 5);
    setcolor(BLACK);
    setbkcolor(WHITE);
    int p1w = textwidth("Player 1 has won!"),
        p1h = textheight("Player 1 has won!"),
        p2h = textheight("Player 2 has won!"),
        p2w = textwidth("Player 2 has won!");

    if (player == 1) {
        outtextxy((w - p1w) / 2, (h - p1h) / 2, "Player 1 has won!");
    }
    else {
        outtextxy((w - p2w) / 2, (h - p2h) / 2, "Player 2 has won!");
    }

    Sleep(5000);
    resetMatrix();
    homeScreen();
}

void paintDifficulty(bool remove, int level, int side, int rsqx, int lsqx, int lsqy, int& difrxpos, int& difrypos, int& diflxpos, int& diflypos) {

    int difw = textwidth("Difficulty"),
        difh = textheight("Difficulty"),
        l1w = textwidth("< Level 1 >"),
        l1h = textheight("< Level 1 >"),
        l2w = textwidth("< Level 2 >"),
        l2h = textheight("< Level 2 >"),
        l3w = textwidth("< Level 3 >"),
        l3h = textheight("< Level 3 >");

    setcolor(WHITE);

    if (remove) {
        setbkcolor(COLOR(136, 136, 136));
    }
    else {
        setbkcolor(COLOR(0, 0, 0));
        setcolor(WHITE);
    }

    if (level == 1) {
        if (side == 0 || side == 2) {
            outtextxy(lsqx + (300 - difw) / 2, lsqy + 200, "Difficulty");
            outtextxy(lsqx + (300 - l1w) / 2, lsqy + 250, "< Level 1 >");
            diflxpos = lsqx + (300 - l1w) / 2;
            diflypos = lsqy + 250;
        }
        if (side == 1 || side == 2) {
            outtextxy(rsqx - 300 + (300 - difw) / 2, lsqy + 200, "Difficulty");
            outtextxy(rsqx - 300 + (300 - l1w) / 2, lsqy + 250, "< Level 1 >");
            difrxpos = rsqx - 300 + (300 - l1w) / 2;
            difrypos = lsqy + 250;
        }
    }
    else if (level == 2) {
        if (side == 0 || side == 2) {
            outtextxy(lsqx + (300 - difw) / 2, lsqy + 200, "Difficulty");
            outtextxy(lsqx + (300 - l2w) / 2, lsqy + 250, "< Level 2 >");
            diflxpos = lsqx + (300 - l2w) / 2;
            diflypos = lsqy + 250;
        }
        if (side == 1 || side == 2) {
            outtextxy(rsqx - 300 + (300 - difw) / 2, lsqy + 200, "Difficulty");
            outtextxy(rsqx - 300 + (300 - l2w) / 2, lsqy + 250, "< Level 2 >");
            difrxpos = rsqx - 300 + (300 - l2w) / 2;
            difrypos = lsqy + 250;
        }
    }
    else {
        if (side == 0 || side == 2) {
            outtextxy(lsqx + (300 - difw) / 2, lsqy + 200, "Difficulty");
            outtextxy(lsqx + (300 - l3w) / 2, lsqy + 250, "< Level 3 >");
            diflxpos = lsqx + (300 - l3w) / 2;
            diflypos = lsqy + 250;
        }
        if (side == 1 || side == 2) {
            outtextxy(rsqx - 300 + (300 - difw) / 2, lsqy + 200, "Difficulty");
            outtextxy(rsqx - 300 + (300 - l3w) / 2, lsqy + 250, "< Level 3 >");
            difrxpos = rsqx - 300 + (300 - l3w) / 2;
            difrypos = lsqy + 250;
        }
    }

    setbkcolor(COLOR(0, 0, 0));

}

void resetMatrix() {
    int i, j;

    stadiul = 0;

    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
        {
            a[i][j].jucator = 0;
            a[i][j].piese[0].player = 0;
            a[i][j].piese[1].player = 0;
            a[i][j].piese[2].player = 0;
            a[i][j].piese[0].dimensiune = 0;
            a[i][j].piese[1].dimensiune = 0;
            a[i][j].piese[2].dimensiune = 0;
            a[i][j].marimePiesa = 100;
        }

}

void pickUsers() {
    clearviewport();

    setlinestyle(SOLID_LINE, 1, 5);
    settextstyle(8, HORIZ_DIR, 3);

    bool users = true;

    readimagefile("bg.jpg", 0, 0, w, h);
    /*setbkcolor(COLOR(235, 150, 5));*/

    int entertw = textwidth("Click here to Start Game"),
        enterh = textheight("Click here to Start Game");

    outtextxy((w - entertw) / 2, h - 150, "Click here to Start Game");

    // set up left user square
    int lsqx = 300, lsqy = (h - 400) / 2;

    line(lsqx, lsqy, lsqx + 300, lsqy);
    line(lsqx, lsqy, lsqx, lsqy + 400);
    line(lsqx + 300, lsqy, lsqx + 300, lsqy + 400);
    line(lsqx, lsqy + 400, lsqx + 300, lsqy + 400);

    // set up right user square
    int rsqx = w - 300, rsqy = (h - 400) / 2;

    line(rsqx, rsqy, rsqx - 300, rsqy);
    line(rsqx, rsqy, rsqx, rsqy + 400);
    line(rsqx - 300, rsqy, rsqx - 300, rsqy + 400);
    line(rsqx, rsqy + 400, rsqx - 300, rsqy + 400);

    // text setup
    int pone = textwidth("Player #1"), ptwo = textwidth("Player #2");

    outtextxy(lsqx + (300 - pone) / 2, lsqy + 50, "Player #1");
    outtextxy(rsqx - 300 + (300 - ptwo) / 2, lsqy + 50, "Player #2");

    int ptype = textwidth("<  Human  >"),
        btype = textwidth("<  Machine  >"),
        ptypeh = textheight("<  Human  >"),
        btypeh = textheight("<  Machine  >"),
        difw = textwidth("Difficulty"),
        difh = textheight("Difficulty"),
        l1w = textwidth("< Level 1 >"),
        l1h = textheight("< Level 1 >"),
        l2w = textwidth("< Level 2 >"),
        l2h = textheight("< Level 2 >"),
        l3w = textwidth("< Level 3 >"),
        l3h = textheight("< Level 3 >");

    outtextxy(lsqx + (300 - ptype) / 2, lsqy + 100, "<   Human   >");
    outtextxy(rsqx - 300 + (300 - ptype) / 2, lsqy + 100, "<   Human   >");

    int difrxpos, difrypos, diflxpos, diflypos, difLeftWidth = l1w, difRightWidth = l1w;

    paintDifficulty(true, 1, 2, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);

    setmousequeuestatus(WM_LBUTTONUP, true);
    int mousex = 0, mousey = 0, newx = 0, newy = 0;
    bool lbot = false, rbot = false;

    while (users) {
        getmouseclick(WM_LBUTTONUP, newx, newy);
        if (newx != mousex || newy != mousey) {
            mousex = newx;
            mousey = newy;
            if (mousex >= (w - entertw) / 2
                && mousex <= (w - entertw) / 2 + entertw
                && mousey >= (h - 150)
                && mousey <= (h - 150 + enterh)) {
                if (lbot) player1 = 2;
                if (rbot) player2 = 2;
                gameScreen();
            }
            if (lbot) {
                if (mousex >= lsqx + (300 - btype) / 2
                    && mousex <= (lsqx + (300 - btype) / 2) + btype
                    && mousey >= lsqy + 100
                    && mousey <= (lsqy + 100) + btypeh) {
                    outtextxy(lsqx + (300 - ptype) / 2, lsqy + 100, "<   Human   >");
                    paintDifficulty(true, 1, 0, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                    difLeftLev = 0;
                    lbot = false;
                }
                else if (mousex >= diflxpos
                    && mousey >= diflypos
                    && mousex <= diflxpos + difLeftWidth
                    && mousey <= diflypos + l1h) {
                    if (difLeftLev == 1) {
                        paintDifficulty(false, 2, 0, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                        difLeftLev = 2;
                        difLeftWidth = l2w;
                    }
                    else if (difLeftLev == 2) {
                        paintDifficulty(false, 3, 0, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                        difLeftLev = 3;
                        difLeftWidth = l3w;
                    }
                    else {
                        paintDifficulty(false, 1, 0, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                        difLeftLev = 1;
                        difLeftWidth = l1w;
                    }
                }
            }
            else {
                if (mousex >= lsqx + (300 - ptype) / 2
                    && mousex <= (lsqx + (300 - ptype) / 2) + ptype
                    && mousey >= lsqy + 100
                    && mousey <= (lsqy + 100) + ptypeh) {
                    outtextxy(lsqx + (300 - ptype) / 2, lsqy + 100, "<  Machine  >");
                    paintDifficulty(false, 1, 0, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                    lbot = true;
                }
            }
            if (rbot) {
                if (mousex >= (rsqx - 300 + (300 - ptype) / 2)
                    && mousex <= (rsqx - 300 + (300 - ptype) / 2) + ptype
                    && mousey >= lsqy + 100
                    && mousey <= (lsqy + 100) + ptypeh) {
                    outtextxy(rsqx - 300 + (300 - ptype) / 2, lsqy + 100, "<   Human   >");
                    paintDifficulty(true, 1, 1, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                    rbot = false;
                }
                else if (mousex >= difrxpos
                    && mousey >= difrypos
                    && mousex <= difrxpos + difRightWidth
                    && mousey <= difrypos + l1h) {
                    if (difRightLev == 1) {
                        paintDifficulty(false, 2, 1, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                        difRightLev = 2;
                        difRightWidth = l2w;
                    }
                    else if (difRightLev == 2) {
                        paintDifficulty(false, 3, 1, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                        difRightLev = 3;
                        difRightWidth = l3w;
                    }
                    else {
                        paintDifficulty(false, 1, 1, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                        difRightLev = 1;
                        difRightWidth = l1w;
                    }
                }
            }
            else {
                if (mousex >= (rsqx - 300 + (300 - ptype) / 2)
                    && mousex <= (rsqx - 300 + (300 - ptype) / 2) + ptype
                    && mousey >= lsqy + 100
                    && mousey <= (lsqy + 100) + ptypeh) {
                    outtextxy(rsqx - 300 + (300 - ptype) / 2, lsqy + 100, "<  Machine  >");
                    paintDifficulty(false, 1, 1, rsqx, lsqx, lsqy, difrxpos, difrypos, diflxpos, diflypos);
                    rbot = true;
                }
            }
        }
    }
}

void homeListenForClick() {
    bool game = true;
    int textw = textwidth("Start Game"), texth = textheight("Start Game"),
        infow = textwidth("Tutorial"), infoh = textheight("Tutorial");

    setmousequeuestatus(WM_LBUTTONUP, true);

    int mousex = 0, mousey = 0, newx = 0, newy = 0;
    while (game) {
        getmouseclick(WM_LBUTTONUP, newx, newy);
        if (newx != mousex || newy != mousey) {
            mousex = newx;
            mousey = newy;
            if (mousex >= (w - textw) / 2 && mousex <= (w - textw) / 2 + textw && mousey >= 400 && mousey <= 400 + texth) {
                game = false;
                pickUsers();
            }
            else if (mousex >= (w - infow) / 2 && mousex <= (w - infow) / 2 + infow && mousey >= 470 && mousey <= 470 + infoh) {
                game = false;
                infoScreen();
            }
        }
    }
}

void homeScreen() {
    settextstyle(8, HORIZ_DIR, 5);
    int startw = textwidth("Start Game"), infow = textwidth("Tutorial");
    readimagefile("bg.jpg", 0, 0, 1920, 1080);
    readimagefile("gobblets.gif", (w - 600) / 2, 50, (w - 600) / 2 + 600, 350);
    /*setbkcolor(COLOR(235, 150, 5));*/
    outtextxy((w - startw) / 2, 400, "Start Game");
    outtextxy((w - infow) / 2, 470, "Tutorial");
    homeListenForClick();
}

int main() {
    bool game = true;

    initwindow(w, h, "", -3, -3);
    settextstyle(8, HORIZ_DIR, 5);

    homeScreen();

    homeListenForClick();

    getch();

    return 0;
}
