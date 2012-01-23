/**
 * @mainpage RTTT - Risky Tic Tac Toe
 * \section desctiption Opis gry
 * Gra strategiczna laczaca elementy gry Ryzyko z gra "Kółko i krzyżyk". Fabuła gry osadzona jest w przestrzeni kosmicznej. Twoj zadaniem, jak generała floty, jest odeprzeć inwazję kosmitów, oraz wyeliminować konkurencyjne frakcje
 * \section rules Reguly panujace w kosmosie
 * \subsection zdobywanie_planet Zdobywanie planet
 * Podstawowym elementem gry są posiadane planety. Aby podbić planete, należy umieścić na niej swoje jednoski.  Wyslane jednostki po dotarciu do celu, walczą z stacjonujacymi tam statkami wroga. Po wygranej bitwie, planeta przechodzi w stan okupacji. Jeśli jest to planeta neutralna, należy ją okupować (posiadac tam conajmniej jedną jednostkę) przez 3 tury.<br/>
 * Jeśli natomiast jest to planeta przeciwnika trzeba odczekać 3 tury na obalenie tamtejszego rządu i kolejne 3 tury na utworzenie swojego.<br/>
 * Natomiast, jeśli podczas okupacji wróg najedzie na planetę która była okupowana przez 2 dni, pokona jednostki gracza i sam zacznie ją okupować, musi odczekać tylko 2 tury na obalenie tworzonego tam rządu. Dokładnie tyle ile gracz poświęcił na jego utworzenie.
 * \subsection zdobywanie_jednostek Zdobywanie jednostek
 * Na każdej pobitej przez gracza planecie produkowane są statki kosmiczne. Tempo tworzenia statków wynisi jeden na turę i zawsze jest tworzony na koniec tury danego gracza. Tak więc po wykonaniu swoich manewrów, na każdej planecie tworzona jest jedna nowa jednostka. Na planetach okupowanych przez przeciwnika nie sa Tworzone jednostki.
 * \subsection wygrana Wygrana
 * Aby wygrać rozgrywkę, należy odeprzeć atak kosmitów. Można to zrobić poprzez eliminację wszystkich wrogich jednostek bądź wykorzystanie <i>Broni ostatecznej</i>. Aby móc z niej skorzystać, nalezy zdobyć planety znajdujące się w jednej lini na przestrzeni całego obszaru bitwy. Zostaje wtedy aktywowana <i>Bron ostateczna</i> i wszystkie wrogie jednostki zostają zniszczone.
 * @page algorytmy Algorytmy
 * \section algorytm_walki Algorytm walki
 * W walce uczestniczy dwóch różnych graczy - atakujący i broniący się. Na każdą rundę walki wystawiana jest maksymalnie flota składająca się z 3 jednostek.
 */
