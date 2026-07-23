# Kółko i Krzyżyk 🎮

Klasyczna gra **Kółko i Krzyżyk** (Tic Tac Toe) z interfejsem graficznym zbudowana w C++ z wykorzystaniem framework Qt.

## Opis

Aplikacja implementuje grę Kółko i Krzyżyk z możliwością gry przeciwko komputerowi. Gra posiada kilka poziomów trudności, w tym inteligentny AI oparty na algorytmie **Minimax**.

## Funkcjonalności

- 🎯 **Gra przeciwko AI** - trzy poziomy trudności
- 🧠 **Inteligentny algorytm Minimax** - optymalny gracz komputerowy
- 🎲 **Losowe ruchy** - dla łatwego poziomu
- 🌐 **Interfejs graficzny** - stworzony z Qt (Qt5/Qt6)
## Wymagania

- **C++17** lub nowszy
- **Qt 5.x lub Qt 6.x** z modułem Widgets
- **CMake 3.16+**

# Struktura projektu

- **main.cpp** - punkt wejścia aplikacji
- **mainwindow.h / mainwindow.cpp** - główne okno aplikacji, obsługa interfejsu
- **logika.h / logika.cpp** - logika gry i algorytmy AI
- **mainwindow.ui** - plik UI (Qt Designer)
- **CMakeLists.txt** - konfiguracja CMake
- **zasoby.qrc** - zasoby aplikacji (ikony, tłumaczenia)

## Jak grać

1. Uruchom aplikację
2. Wybierz poziom trudności
3. Kliknij na puste pole, aby postawić swój znak (X)
4. Komputer będzie grał jako O
5. Pierwsza osoba, która uloży trzy symbole w linii (poziomo, pionowo lub diagonalnie) wygrywa
6. Naciśnij przycisk "Reset" lub "Nowa gra", aby rozpocząć od nowa

## Poziomy trudności

- **Łatwy** - komputer wykonuje losowe ruchy
- **Średni** - komputer używa inteligentnych strategii
- **Trudny** - komputer używa optymalnego algorytmu Minimax (nie do pokonania)

## Technologia

- **Język**: C++17
- **Framework**: Qt (GUI)
- **Budowanie**: CMake
- **Algorytm AI**: Minimax z oceną pozycji na planszy
