# Image-Editor
### PCLP 1 Homework 3 -> Image Editor

##### Copyright 2022
##### Nastase Cristian-Gabriel Grupa 315CA
##### Tema 3
##### PCLP

                    - Editor de imagini -

        (structura se afla in 'function.h')
        Am considerat ca folosirea unei structuri va duce la o rezolvare
    a temei mult mai organizata. Astfel, declaram structura 'v', in care
    avem posibilitatea de a stoca:
        -- **a -> matricea imaginii;
        -- **r, **g, **b -> 3 matrici ale imaginii color, fiecare
            reprezentand cate o culoare: red, green, blue;
        -- latimea matricii
        -- inaltimea matricii
        -- magic-word-ul
        -- x1, y1, x2, y2 -> coordonatele din selectie
        -- *v_frecventa -> frecventa pixelilor -> ne va ajuta la
            histograma si egalizare
        -- variabila 'selectat' ne arata daca este selectata o parte
            a pozei. daca da este 1, daca nu este 0;
        -- analog si pentru variabila 'imagine_incarcata'
        -- 'valoare_maxima' reprezinta valoarea maxima din matrice;

        In functia main declaram variabilele:

        -- 'v' -> structura in care stocam toate aspectele pozei cum
                am spus mai spus
        -- '*p' -> aceasta va stoca intreaga comanda pe care o primim,
                inpreuna cu parametrii (exp: *p = 'SELECT 10 20 30 40')
        -- '*comanda' -> in care o sa stocam cu ajutorul
                         lui strtok primul cuvant

        Vom incepe cu un while(1), care nu se va opri pana nu primim
    comanda EXIT, in care exista un 'break;'.
        Inlantuirea de if-uri ne permite sa tratam fiecare comanda
    in parte. Verificam cu strcmp variabila 'comanda' si pentru
    fiecare comanda este alocat cate un if, in care se afla cate o
    functie.
        Un caz mai special le reprezinta comenzile SELECT si SELECT ALL,
    in care verific daca al doilea cuvant din stringul "p" este egal
    cu "ALL"... daca da, inseamna ca avem comanda SELECT ALL...
    daca nu, inseamna ca avem comanda SELECT.

        Am creat cate o functie si un fisier (.c) pentru fiecare comanda.
    Conform pdf-ului cu Tema3, comenzile (LOAD, CROP, APPLY etc...) sunt
    intr-o anumita ordine, asa ca am numerotat fiecare fisier.c.

    Fisierul 0.function.c contine functii care sunt comune aproape
    tuturor celorlaltor comenzi. Am decis ca inloc sa le scriu de mai
    multe ori, sa le pun intr-un fisier separat.

        - 'alocare_rgb_ALL' aloca red, green, blue pe
          dimensiunile totale ale matricii;

        - 'alocare_rgb_portiune' aloca red, green, blue pe
          o dimensiune partiala a matricii;

        - 'eliberare_matrice' elibereaza poza

        - 'verificare_existenta_imagine' verifica daca este incarcata
                                         vreo poza;

        - 'swap' schimba doua valori intre ele, a doua variabile;

        - 'limitare_rezultate' este clamp;

    Fisierul 1.load.c contine functii pentru comanda 'LOAD':

        - 'verificare_comentariu' verifica daca avem comentarii in
                                  fisierul pozei

        - 'citire_info_poza' citeste informatiile pozei, adica magic-word,
                            latimea, inaltimea si valoarea maxima

        - 'LOAD' este functia principala:
            a) deschide fisierul
            b) aloca matricea in care urmeaza sa stocam informatia
                din fisier
            c) in functie de magic-word stim cum sa citim informatia
                din fisier: text/binar, PGM/PPM
            d) inchidem fisierul

    Fisierul 2.select.c contine functii pentru comenzile 'SELECT' si 'SELECT ALL':

        - 'verif_comanda_select' verifica daca comanda este invalida

        - 'verif_coordonate' verifica daca coordonatele sunt valide

        - 'SELECT' este prima functie principala:
            a) cele 3 if-uri verifica comanda introdusa
            b) stocam coordonatele noi

        - 'SELECT_ALL' este a doua functie principala:
            a) atribuim coordonatelor x1, y1, x2, y2 dimensiunile
                care cuprind intreaga imagine

    Fisierul 3.histogram.c contine functii pentru comanda 'HISTOGRAM':

        - 'verif_comanda_histograma' verifica parametrii din comanda

        - 'HISTOGRAM' este functia principana:
            a) cele 3 if-uri verifica comanda introdusa
            b) reinitializam vectorul de frecventa cu 0
            c) calculam vectorul de frecventa
            d) calculam numarul maxim de stelute
            e) cu ajutorul formulei calculam histograma si o afisam

    Fisierul 4.equalize.c contine functii pentru comanda 'EQUALIZE':

        - 'EQUALIZE':
            a) verificam existenta imaginii
            b) verificam daca e imagine PGM
            c) reinitializam vectorul de frecventa cu 0
            d) calculam vectorul de frecventa
            e) conform formulei date, calculam valoarea noua a pixelului

    Fisierul 5.rotate.c contine functii pentru comanda 'ROTATE':

        - 'verif_comanda_rotate' verifica unghiul de rotire

        - 'rotire_90_grade_ALL' roteste intreaga poza la 90 de grade

        - 'rotire_180_grade_ALL' roteste intreaga poza la 180 de grade.
            Aceasta functie nu este tocmai necesara, dar am facut o pentru
            a optimiza programul. O rotire la 270 de grade ar consta in
            3 rotiri succesive la 90 de grade, ceea ce inseamna 3 realocari.
            O rotire la 270 de grade mai poate insemna si o rotire la 180
            si una la 90. Pentru rotirea la 180 nu mai este nevoie de realocare,
            asa ca pentru a face o rotire la 270 acum este nevoie numai de o
            realocare. Cred ca se salveaza timp cu acest aspect.

        - 'rotire_90_grade_portiune' roteste la 90 de grade o portiune a pozei

        - 'ROTATE' este functia principala:
            a) cele doua if-uri verifica toate conditiile care trebuie sa le
                le respecte comanda
            b) verificam daca este selectata toata imaginea sau nu. pentru
                rotirea la 90 de grade a intregii imagini am facut 'swap' la
                latime si inaltime, se schimba dimensiunile intre ele

    Fisierul 6.crop.c contine functii pentru comanda 'CROP':

        - 'alocare_rgb_crop' aloca 3 matrici (red, green, blue) conform
                            dimensiunilor portiunii care trebuie cropata;

        - 'CROP' este functia principala:
            a) alocam matrici auxiliare. pentru imagine PGM alocam doar una
                pentru imagine PPM mai alocam inca 3. cate una pt fiecare culoare
            b) copiem in matricile auxiliare valorile de care avem nevoie
            c) eliberam imaginea principala deoarece avem stocata informatia
                de care avem nevoie
            d) alocam cu noile dimensiuni
            e) resetam coordonatele pentru ca acum cuprind toata imaginea
            f) copiem in 'v' noua poza
            g) nu mai avem nevoie de matricile auxiliare si le dealocam

    Fisierul 7.apply.c contine functii pentru comanda 'APPLY':

        - 'apply_edge' calculeaza noua valoare a pixelului cu ajutorul formulei date

        - 'apply_sharpen' analog

        - 'apply_blur' analog

        - 'apply_gaussian_blur' analog

        - 'APPLY' este functia principala:
            a) cele 4 if uri verifica daca comanda este buna
            b) alocam matrici auxiliare si vom copia poza noastra in ele,
                deoarece atunci cand calculam noua valoare a pixelului,
                valoarea vecinilor va fi influentata
            c) cu cele doua for uri parcurgem pixelii selectati

    Fisierul 8.save.c contine functii pentru comanda 'SAVE':

        - 'SAVE':
            a) descidem fisierul
            b) verificam cum trebuie sa scriem fisierul
            c) in functie de tipul de imagine text/binar PGM/PPM vom
                stoca poza corespunzator
            d) inchidem fisierul

        De a lungul intregului cod am facut programare defensiva;



