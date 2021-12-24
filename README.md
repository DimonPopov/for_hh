# for_hh


- [qtMT](https://github.com/DimonPopov/for_hh/tree/master/qtMT) - Многопоточное графическое приложение, отображающее процесс выполнение ресурсоемкой задачи. Каждая процедура представлена в таблице в виде отдельной строки, которая имеет свой порядковый номер и шкалу выполнения. Пользователь может запустить одновременно только 10-ть потоков, а при попытке создания 11-го - диалоговое окно, информирующее о невозможности данной операции. Ресурсоемкая задача представлена в виде цикла, на каждой итераций которого поток засыпает на 100 мс.

![](https://github.com/DimonPopov/for_hh/blob/master/qtMT/interface.jpg)

- [drivers](https://github.com/DimonPopov/for_hh/tree/master/drivers) - Два модуля ядра линукс. dummy_driver1.c производит регистрацию, инициализацию, а так же добавление виртуального символьного устройства в систему. dummy_driver2.c является драйвером, который сигнализирует о появлений в системе usb устройства. В качестве id_Vendor'a и id_Produt'a были выбраны значения принадлежавшие подручной флешке.


- [AhoCorasick](https://github.com/DimonPopov/for_hh/tree/master/ahoCorasick) - Небольшое консольное приложение, реализующее алгоритм Ахо-Корасика.

- [serverInfo](https://github.com/DimonPopov/for_hh/tree/master/serverInfo) - Консольное приложение выводящее базовую информацию о системе (Ubuntu).

![](https://github.com/DimonPopov/for_hh/blob/master/serverInfo/result.jpg)

- [mlFit](https://github.com/DimonPopov/for_hh/tree/master/mlFit) - Программа реализующая метод МНК для конечного набора значений используя полином 5-ой степени. Коэффициенты многочлена, который представляет из себя аппроксимирующую функцию, высчитываются автоматически и без использования стандартных функций среды MathLab.

![](https://github.com/DimonPopov/for_hh/blob/master/mlFit/g1.jpg)
![](https://github.com/DimonPopov/for_hh/blob/master/mlFit/g2.jpg)
