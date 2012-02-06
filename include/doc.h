1. Tytuł projektu i autorzy
Risky Tic Tac Toe jest połączeniem gry "Kółko i Krzyżyk" oraz elementów z gry "Ryzyko".
Projekt został wykonany przez trzech studentów Informatyki Stosowanej na Wydziale Fizyki i Informatyki Stosowanej Akademii Górniczo-Hutniczej im. Stanisława Staszica w Krakowie. Skład zespołu przedstawia się następująco:
- Dawid Barnaś – specjalista od biblioteki SDL, główna osoba odpowiedzialna za poprawne wyświetlanie i obsługę zdarzeń
- Marcin Fabrykowski – główny programista, implementacja zasad gry, a także abstrakcyjnego poziomu przesyłanych komunikatów. Integracja modułu wyświetlania i modułu sieciowego z silnikiem gry.
- Paweł Ściegienny – odpowiedzialny za komunikację przez TCP/IP, buforowanie wiadomości pomiędzy serwerem a instancjami klienckimi.
2. Opis projektu:
Prymitywna gra w kółko i krzyżyk nawet w 3 wymiarowej przestrzeni, stąd zasady RTTT zostały zmodyfikowane.

--ZASADY--
        --POCZATEK--
        Na początku, gracz dostaje 3 jednostki, które może dowolnie rozplanować na planszy
        --ROZGRYWKA--
        Gracz wybiera swoją prowincję na której ma >1 jednosktę z której chce wysłaś jednoski, oraz docelową, którą chce przejąć.
        Atakujący i obroniący się "rzucają kostką" K6 w liczbie odpowiadająch jednostek walczących w danej potyczce. Porównywane są odpowiednio największe wyniki, np:
                --NIEUDANY--
                Atakujący wyrzuci: 3 4 6 6, natomiast:
                Broniący wyrzuci: 5 5 5. porównujemy odpowiednio:
                6>5 wygrywa atakujący
                6>5 wygrywa atakujący
                4<5 przegrywa atakujący
                wynik takiej potyczki jest taki, że prowincja broniąca obroniła się, i pozostał jej jeden wojownik, natomiast atakujący stracił 1 wojownika. Wojska które przeżyły atak, wracają na prowincję z której wyruszyły.
                --UDANY--
                Atakujący wyrzuci 3 4 6 6, natomiast:
                Broniący wyrzuci: 5 5 3, porównujemy odpowiednio:
                6>5 wygrywa atakujący
                6>5 wygrywa atakujący
                4>3 wygrywa atakujący
                broniący sie nie ma już jednostek, dlatego atakujący podbija tą prowincję i przenosi tam swoje jednostki. Liczba przeniesionych jednostek nie może być mniejsza niż pozostałych przy życiu po walce ani większa niż suma jednostek pozostałych na prowincji oraz pozostałych przy życiu minus 1. Jedna jednostka musi zostać na prowincji.
                --PRZEJOWANIE PROWINCJI--
                Po udanym ataku na prowincje, dana prowincja staje się prowincją okupowaną przez danego gracz. Aby ją przejąc, gracz musi zawiesić na niej swoją flagę. Proces trwa 5 tur.
                Jeśli gracz podbije prowincje która już należy do innego gracza (już ma jego flagę) gracz ten musi poczekać 5 tur na zdjęcie flagi przeciwnika oraz kolejne 5 tur na zawieszenie swojej.
                W przypadku jeżeli jeden gracz wiesza swoją flage i w tym czasie prowincja zostanie przejęta przez innego gracza, podbijający musi poczekać tyle tur na zdjęcie flagi przeciwnika, ile ten poświęcił na jej wzniesienie. np:
                        Gracz X okupuje prowincje i ma ją przez 2 tury, jego flaga jest na "drugim poziomie". Następnie gracz Y podbija tą prowincje i musi poczekać 2 tury aż zdejmie flage przeciwnika a następnie 5 tur aby zawiesić swoją.
                        Analogicznie, jeśli w powyższym przypadku gracz Y podbija prowincje i ma ją przez jedną turę, to flaga przeciwnika spada z drugiego poziomu na pierwszy. Jeśli w tym czasie gracz X ponownie podbije prowincję musi czekać tylko 4 tury na oznaczenie tej prowincji jako jego, gdyż prowincja miałą już jego flagę na poziomie pierwszym.
                Jeżeli gracz X podbije prowincje należącą do gracza Y, prowincja należy nadal do gracza Y do czasu gdy gracz X nie zdejmie jego flagi. Gracz Y jednak nie ma prawa wstawiać tam nowych jednostek.
        Co turę każdy gracz otrzymuje nowe jednostki w liczbie (LiczbaPosiadanychProwincji+LiczbaOkupowanychProwincji/3) które może dowolnie dołożyć do posiadaych lub okupowanych przez siebie prowincji.
        --KONIEC--
        Koniec gry następuje gdy jeden z graczy przejmie (postawi w pełni flagę) na 5 prowincjach ułożonych w lini prostej, bądź gdy jeden z graczy się podda.

--WYMAGANIA SPRZĘTOWE--
        Procesor przynajmniej 1.2GHz
        Przynajmniej 16MB pamięci RAM
        System Windows/Linux
       bibliteki Boost (Boost System, FileSystem, Thread) >=1.42, SDL1.2, SDL-Image1.2
        Mysz/Touchpad
        Monitor
        Karta sieciowa
        Gracz
        Wygodne siedzisko
        Przeciwnik (co najmniej 1)
3. Założenia wstępne przyjęte w realizacji projektu.

Nasza unikatowa gra ma być unikatowa dzięki kilku elementom:
- gra ma pozwalać na grę zarówno na zdalnej maszynie, jak i na maszynie lokalnej
- to gracz decyduje o rozmiarze planszy
- sześciany będą oddalone od siebie w celu umożliwienia wysłania jednostek na niebrzegowe pola
- intuicyjna obsługa za pomocą myszy (naciśnij, przeciągnij, kliknij)
- nielimitowany obrót wokół każdej osi
- pola każdego z użytkowników wyróżniają się unikatowym kolorem

4. Analiza projektu
4.1 Zdefiniowanie struktur danych.

/// TUTAJ O TYCH VERTEXACH I INNYCH SREXACH ///

4.2 Specyfikacja interfejsu użytkownika
        Wybór planety źródłowej         - Lewy przycisk myszy
        Wybór planety docelowej         - Prawy przycisk myszy
        Wybór ilości jednostek          - Rolka (góra - zwiększenie, dół - zmniejszenie)
        Wysłanie jednostek                      - Rolka (wciśnięcie)
        Obrót pola gry                          - Wciśnięty lewy przycisk myszy + ruch, klawisze strzałek
        Skalowanie pola gry                     - Wciśnięty prawy przycisk myszy + ruch
        Przesunięcie pola gry           - Wciśnięta rolka + ruch

4.3 Wyodrębnienie i zdefiniowanie zadań
- komunikacja z użytkownikiem – mysz, klawiatura
- wyświetlenie okna, generowanie planszy – SDL
- komunikacja okna z silnikiem gry – Boost Asio, TCP/IP
- logika gry kółko i krzyżyk z elementami gry w ryzyko

4.4 Decyzja o wyborze narzędzi

Projekt został wykonany przy użyciu następujących bibliotek:
- Boost 1.46.1 – ze względu na znakomite możliwości Boost Asio do połączeń TCP/IP
- SDL 1.2 – generowanie okna
- Vim, Gedit, Eclipse
- repozytorium GIT
- Gentoo Linux, Debian, Ubuntu, MS Windows




5 Podział pracy i analiza czasowa
Ze względu na to, iż nasz projekt dzieli się w naturalny sposób na trzy moduły, barbarzyństwem byłoby nie wykorzystać tego przy podziale obowiązków.
Po ustaleniu wspólnych interfejsów i po wielu owocnych dyskusjach (ok 10% czasu projektu), przystąpiliśmy do pracy.

W ten sposób szacujemy że poniższe zadania w sumie zajęły 90%

1. Komunikacja sieciowa – 15% [Paweł Ściegienny]
2. Stworzenie okna gry, implementacja algorytmu rysowania, obsługa zdarzeń – 20% [Dawid Barnaś]
3. Implementacja logiki gry – 15%[Marcin Fabrykowski]
4. Weryfikacja, ustalenie nowego SRS – 5% [razem]
5. Refactoring komunikacji – 5% [Paweł Ściegienny]
6. Optymalizacja wyświetlania – 10% [Dawid Barnaś]
7. Integracja -15% [Marcin Fabrykowski]
8. Uzupłenienie dokumentacji – 5% [Paweł Ściegienny]


6. Tutaj opis algorytmów graficznych...
7. Dokumentacja techniczna
