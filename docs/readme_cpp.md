<h2> Доки на С++ часть проекта </h2>

Исполняемый файл выполняет функцию расчёта траекторий лучей в среде с изменяющемся показателем преломления.
В качестве входных данных в программу поступает набор коэффициентов либо ряда Тейлора, либо ряда Фурье (также возможно поточечное задание) для функции коэффициента преломления, т.е. n(y).
_**Важно**: нулём считается положение у земли, положительное направление соответствует высоте_.

Также нужно задать количество лучей и их _угол развёрстки_ - угол между первым и последним лучём. 
Лучи пускаются симметрично относительно оси y, распределены равномерно по начальному углу.

Есть два режима вывода - через поток ввода-вывода //и через файл todo//.

В качестве вывода программы выдаётся число хорошести (todo). Также можно дополнительно получить данные самих лучей в полном размере или только в момент их приземления.

****

<h3> Аргументы исполняемого файла  </h3>

Вводятся в поток вывода

- type : "fourier" / "poly"
- N : int - степень ряда
- дальше идёт N чисел через пробел

Технические аргументы

- H - высота с которой пускаются лучи (R=1 - радиус земли)
- alpha - угол развёрстки
- N - количество лучей
- dt - дт

- T - int - вывод дополнительной информации.

Если T = 0 - никакой доп.информации не выводится. Если
T = 1, выводится оптическая информация о последних лучах. T = 2 - полная информация по лучам