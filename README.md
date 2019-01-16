# Microshell
## This is a project written in ANSI C language for classes "Operating Systems". Here is the content of the task in Polish:

Zadanie polega na wykorzystaniu języka ANSI C do napisania prostego programu powłoki – Microshell. Program ten powinien przyjmować na wejściu polecenia, a następnie wykonywać działania zgodne z ich treścia. Powłoka taka powinna:

(1 punkt) wyświetlać znak zachęty w postaci [{path}] $, gdzie {path} jest scieżką do bieżącego katalogu roboczego,
(1 punkt) obsługiwać polecenie cd, działające analogicznie do tego znanego nam z powłoki bash,
(0,5 punkta) obsługiwać polecenie exit, kończące działanie programu powłoki,
(0,5 punkta) obsługiwać polecenie help, wyświetlające na ekranie informacje o autorze programu i oferowanych przez niego funkcjonalnościach,
(2 punkty) obsługiwać dwa inne, dowolnie wybrane polecenia powłoki (chodzi tutaj np. o własną, samodzielną, prostą implementację dwóch poleceń, np. cp, których kody nie były podane podczas laboratoriów, ani nie pochodzą ze strony Bartłomieja Przybylskiego),
(2 punkty) przyjmować polecenia odwołujące się przez nazwę do skryptow i programów znajdujacych się w katalogach opisanych wartoscią zmiennej środowiskowej PATH oraz umożliwiać wywołanie tych skryptów i programów z argumentami,
(1 punkt) wypisywać komunikat błędu, gdy niemożliwe jest poprawne zinterpretowanie polecenia.
Dodatkowo przyznawane są 2 punkty za dodatkowe bajery (w zależności od stopnia skomplikowania problemu), np. wyświetlanie loginu aktualnie zalogowanego użytkownika, obsługę kolorów, obsługę argumentów w cudzysłowach, sensowną obsługę sygnałów (np. Ctrl+Z), obsługę historii poleceń, itp.

Plik Makefile musi obsługiwać polecenie make oraz make clean.
