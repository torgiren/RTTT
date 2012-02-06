 /**
 * @page protokoly Protokoły
 * \section komunikacji_sieciowej Komunikacji sieciowej
 * \subsection inicjacja Inicjacja
 * <ol>
* <li> Client: Hello</li>
* <li> Server: Witam</li>
 * <li> Server: player <num> //Numer gracza jaki został mu przypisany</li>
 * <li> Server: size <num> //Rozmiar planszy na które prowadzona jest bitwa</li>
 * <li> Server: planet <num1> <num2> <num3> <num4> <num5> <num6> <num7> <num8> //Wysyła stan planet. Num1-3 pozycja planety, Num4-8 dane planety @ref Planet::ToString()</li>
 * <li> Powyższe dla wszystkich planet na planszy </li>
 * <li> Server: act <num> //Numer aktualnego gracza</li>
 * </ol>
 * \subsection rozgrywka Rozgrywka
 * <ol>
 * <li> Client: move <num1> <num2> <num3> <num4> <num5> <num6> <num7> //Żądanie przeniesienia <num7> jednostek z planety o wsp. num1-3 na planete num4-6</li>
 * <li> Server: planet <num1> <num2> <num3> <num4> <num5> <num6> <num7> <num8> //Wysyła stan planet. Num1-3 pozycja planety, Num4-8 dane planety @ref Planet::ToString()</li>
 * <li> Powyższe dla wszystkich planet na planszy </li>
 * <li> Client ponownie "move", bądź:</li>
 * <li> Client: end //Kończy turę gracza<i/li>
 * <li> Server: planet <num1> <num2> <num3> <num4> <num5> <num6> <num7> <num8> //Wysyła stan planet. Num1-3 pozycja planety, Num4-8 dane planety @ref Planet::ToString()</li>
 * <li> Powyższe dla wszystkich planet na planszy </li>
 * <li> Server: act <num> //Numer aktualnego gracza</li>
 * </ol>
 */

