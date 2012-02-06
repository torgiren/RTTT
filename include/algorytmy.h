// void drawLine(const Vertex& a, const Vertex& b);
/** Rysowanie linii:
 * <ol>
 * <li>Z twierdzenia Pitagorasa oblicz d¿ugo¿¿ odcinka(<i>l</i>)</li>
 * <li>Oblicz odleg³oœæ w poziomie (<i>dx</i>) i w pionie (<i>dy</i>) a nastêpnie podziel je przez d³ugoœæ odcinka</li>
 * <li>Zapaczynaj¹c od jednego z punktów, odpal pêtlê <i>l</i> razy</li>
 * <li>Dla ka¿dej iteracji wypisz piksel w aktualnym punkcie i przesuñ siê o <i>dx, dy</i></li>
 * </ol>
 */
 
 
// void drawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);
/** Rysowanie trójk¹ta:
 * <ol>
 * <li>ZnajdŸ skrajne punkty i utwórz z nich prostok¹t zawieraj¹cy w sobie ca³y trójk¹t</li>
 * <li>PrzejdŸ po wszystkich punktach wewn¹trz prostok¹ta</li>
 * <li>Jeœli punkt jest wewn¹trz trójk¹ta - wstaw piksel, w przeciwnym razie kontynuuj</li>
 * </ol>
 */
 
/** Wyszukiwanie obiektów:
 * <ol>
 * <li>Ustaw wskaŸnik na obiekt</li>
 * <li>U¿ywaj¹c ZBuffera sprawdŸ, czy mo¿na wstawiæ piksel</li>
 * <li>Jeœli tak, wstaw piksel, zaktualizuj ZBuffer i wstaw wskaŸnik na obiekt do bufora obiektów</li>
 * </ol>
 */
