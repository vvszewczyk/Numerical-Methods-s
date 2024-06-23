<h3>Lab 06</h3>
Zad 1. Napisz program, który będzie rozwiązywał układ 𝑛 równań liniowych
o 𝑛 niewiadomych metodą Jacobiego (7 pkt). 
Wymagania:

• Dane pobierane są z pliku.

• Program wypisze układ równań (macierz rozszerzoną), sprawdzi czy macierz jest
diagonalnie słabo dominująca i wyświetli stosowny komunikat.

• Napisać kod do przemnażania macierzy.

• Warunkiem zatrzymania algorytmu jest podana przez użytkownika ilość iteracji.

• Program wypisze macierze: 𝐿 + 𝑈 oraz 𝐷^−1.

• Program wypisze zadaną ilość iteracji i rozwiązanie układu równań.

W sprawozdaniu należy zamieścić rozwiązanie układu równań przedstawionego
w przykładzie dla 5 iteracji. Za początkowe wartości wektora x przyjąć 0. Porównaj wyniki
uzyskane metodą Jacobiego i Gaussa.

Zad 2. Zaimplementować warunek stopu w postaci (3 pkt):

|𝑥^(𝑖+1) − 𝑥^(𝑖)| < 𝜀

Wymagania:

• Warunek musi być spełniony dla każdego 𝑥.

• Ustalić maksymalną ilość iteracji, aby w przypadku braku rozwiązania z zadaną
dokładnością program nie liczył w nieskończoność.

• Program wypisze przyjętą wartość błędu 𝜀, ilość wykonanych iteracji, rozwiązanie
układu równań i obliczoną wartość błędu dla każdego x. Obliczenia wykonać dla
𝜀 = 0.001 oraz 𝜀 = 0.000001.
