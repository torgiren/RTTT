#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

/**
* @details Klasa odpowiedzialna za poprawne informacje o wiadomości
* @author Paweł Ściegienny
* @brief Przesyłana wiadomość.
*/

class Message {
	public:
		///@brief maksymalna długość nagłówka
		enum { header_length = 4 };
		///@brief maksymalna długość wiadomości
		enum { max_body_length = 512 };
		///@brief Konstruktor
		///@details Konstruktor domyślny - inicjalizuje długość wiadomości 
		Message();
		///@brief Konstruktor
		///@details Konstruktor kopiujący - w pewnym momencie bardzo istotny element programu
		Message(const Message& src);
		///@brief operator przypisania
  		///@brief operator przypisania [depracated]
		void operator=(const Message& src);
		///@brief metoda zwracająca treść wiadomości razem z nagłówkiem
		const char* data() const { return _data; }
		///@brief metoda zwracająca treść wiadomości razem z nagłówkiem
		char* data() { return _data; }
		///@brief metoda zwracająca długość wiadomości
		///@details   metoda zwracająca długość wiadomości WRAZ z długością nagłówka
		size_t length() const { return header_length + _body_length; }
		///@brief metoda zwracająca treść wiadomości
		const char* body() const { return _data + header_length; }
		///@brief metoda zwracająca treść wiadomości
		char* body() { return _data + header_length; }
		///@brief metoda zwracająca długość treści
		size_t body_length() const { return _body_length; }
		///@brief metoda zwracająca dłu;gość treści
		void body_length(size_t length);
		///@brief metoda odczytująca nagłówek
		bool decode_header();
		///@brief metoda zapisująca nagłówek
		void encode_header();
                ///@brief metoda dopisująca do wiadomości id klienta
                ///@param[in] src id klienta
		void source(unsigned src) { _src=src; }
                ///@brief metoda zwracająca id klienta z wiadmości
		unsigned source() const { return _src; }
                ///@brief metoda konwertująca wiadomość do stringa [depracated]
		std::string getString() {
			std::string s(body(), body_length());
			return s;
		}

	private:
		///@brief istotne dla serwera pole - nadawca wiadomości
		unsigned _src;
                ///@brief miejsce do przechowywania bajtów które nadeszły
		char _data[header_length + max_body_length];
 		///@brief przechowuje długość właściwej wiadomości
		size_t _body_length;

};

#endif //MESSAGE_HPP
