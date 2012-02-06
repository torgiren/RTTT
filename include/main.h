/**
 * @mainpage RTTT - Risky Tic Tac Toe
 * \section description Opis gry
 * Gra strategiczna łącząca elementy gry Ryzyko z gra "Kółko i krzyżyk". Fabuła gry osadzona jest w przestrzeni kosmicznej. Twój zadaniem, jak generała floty, jest odeprzeć inwazję kosmitów, oraz wyeliminować konkurencyjne frakcje
 * \section rules Reguły panujące w kosmosie
 * \subsection zdobywanie_planet Zdobywanie planet
 * Podstawowym elementem gry są posiadane planety. Aby podbić planetę, należy umieścić na niej swoje jednostki.  Wysłane jednostki po dotarciu do celu, walczą z stacjonującymi tam statkami wroga. Po wygranej bitwie, planeta przechodzi w stan okupacji. Jeśli jest to planeta neutralna, należy ją okupować (posiadać tam co najmniej jedną jednostkę) przez 3 tury.<br/>
 * Jeśli natomiast jest to planeta przeciwnika trzeba odczekać 3 tury na obalenie tamtejszego rządu i kolejne 3 tury na utworzenie swojego.<br/>
 * Natomiast, jeśli podczas okupacji wróg najedzie na planetę która była okupowana przez 2 dni, pokona jednostki gracza i sam zacznie ją okupować, musi odczekać tylko 2 tury na obalenie tworzonego tam rządu. Dokładnie tyle ile gracz poświęcił na jego utworzenie.
 * \subsection zdobywanie_jednostek Zdobywanie jednostek
 * Na każdej pobitej przez gracza planecie produkowane są statki kosmiczne. Tempo tworzenia statków wynosi jeden na turę i zawsze jest tworzony na koniec tury danego gracza. Tak więc po wykonaniu swoich manewrów, na każdej planecie tworzona jest jedna nowa jednostka. Na planetach okupowanych przez przeciwnika nie są Tworzone jednostki.
 * \subsection wygrana Wygrana
 * Aby wygrać rozgrywkę, należy odeprzeć atak kosmitów. Można to zrobić poprzez eliminację wszystkich wrogich jednostek bądź wykorzystanie <i>Broni ostatecznej</i>. Aby móc z niej skorzystać, należy zdobyć planety znajdujące się w jednej linii na przestrzeni całego obszaru bitwy. Zostaje wtedy aktywowana <i>Bron ostateczna</i> i wszystkie wrogie jednostki zostają zniszczone.
 */
