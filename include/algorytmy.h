 /**
 * @page algorytmy Algorytmy
 * \section algorytmy_rysowania Algorytmy rysowania
 * \subsection rysowanie_linii Rysowanie linii
 * <ol>
 * <li>Z twierdzenia Pitagorasa oblicz długość odcinka(<i>l</i>)</li>
 * <li>Oblicz odległość w poziomie (<i>dx</i>) i w pionie (<i>dy</i>) a następnie podziel je przez długość odcinka</li>
 * <li>Zaczynając od jednego z punktów, odpal pętlę <i>l</i> razy</li>
 * <li>Dla każdej iteracji wypisz piksel w aktualnym punkcie i przesuń się o <i>dx, dy</i></li>
 * </ol>

 
 
 * \subsection rysowanie_trojkata Rysowanie trojkata:
 * <ol>
 * <li>Znajdź skrajne punkty i utwórz z nich prostokąt zawierający w sobie cały trójkąt</li>
 * <li>Przejdź po wszystkich punktach wewnątrz prostokąta</li>
 * <li>Jeśli punkt jest wewnątrz trójkąta - wstaw piksel, w przeciwnym razie kontynuuj</li>
 * </ol>
 
 * \subsection wyszukiwanie_obiektow Wyszukiwanie obiektow:
 * <ol>
 * <li>Ustaw wskaźnik na obiekt</li>
 * <li>Używając ZBuffera sprawdź, czy można wstawić piksel</li>
 * <li>Jeśli tak, wstaw piksel, zaktualizuj ZBuffer i wstaw wskaźnik na obiekt do bufora obiektów</li>
 * </ol>
 */
