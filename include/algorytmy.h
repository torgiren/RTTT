// void drawLine(const Vertex& a, const Vertex& b);
/** Rysowanie linii:
 * <ol>
 * <li>Z twierdzenia Pitagorasa oblicz d�ugo�� odcinka(<i>l</i>)</li>
 * <li>Oblicz odleg�o�� w poziomie (<i>dx</i>) i w pionie (<i>dy</i>) a nast�pnie podziel je przez d�ugo�� odcinka</li>
 * <li>Zapaczynaj�c od jednego z punkt�w, odpal p�tl� <i>l</i> razy</li>
 * <li>Dla ka�dej iteracji wypisz piksel w aktualnym punkcie i przesu� si� o <i>dx, dy</i></li>
 * </ol>
 */
 
 
// void drawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);
/** Rysowanie tr�jk�ta:
 * <ol>
 * <li>Znajd� skrajne punkty i utw�rz z nich prostok�t zawieraj�cy w sobie ca�y tr�jk�t</li>
 * <li>Przejd� po wszystkich punktach wewn�trz prostok�ta</li>
 * <li>Je�li punkt jest wewn�trz tr�jk�ta - wstaw piksel, w przeciwnym razie kontynuuj</li>
 * </ol>
 */
 
/** Wyszukiwanie obiekt�w:
 * <ol>
 * <li>Ustaw wska�nik na obiekt</li>
 * <li>U�ywaj�c ZBuffera sprawd�, czy mo�na wstawi� piksel</li>
 * <li>Je�li tak, wstaw piksel, zaktualizuj ZBuffer i wstaw wska�nik na obiekt do bufora obiekt�w</li>
 * </ol>
 */
