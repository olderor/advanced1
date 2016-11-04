Задача 1.3 «Автобусы»

Решение Евченко Богдана ПИ-15-1

[*https://github.com/olderor/advanced1*](https://github.com/olderor/advanced1)

![](media/image1.png){width="6.491666666666666in" height="6.025in"}

![](media/image2.png){width="6.491666666666666in"
height="5.016666666666667in"}

Решение.

1\. Создадим и считаем переменные $\text{busCount}$ – количество
автобусов ($M$ по условию), $\text{busCapacity}$ – вместимость автобусов
($D$ по условию) и $\text{peopleCount}$ – количество людей
($N$ – по условию).

1\. Создадим массив $\text{peopleWeights}$ размером $\text{peopleCount}$
элементов. Тут будут храниться веса каждого пассажира ($L(i)$ по
условию). Заполним массив значениями из условия.

2\. Создадим массив $\text{weightsPerOneBus}$ размером
$\text{peopleCount}*\text{peopleCount}$ элементов. Тут будут храниться
максимальное количество пассажиров из диапазона от $i$ до $j$,
$i \leq j$, которые могут поместиться в один автобус.

2.1. Для каждой строки $i$ посчитаем это максимальное количество. Для
этого создадим набор $\text{currentWeights}$, в котором будем хранить
набор весов пассажиров, а также две переменные
$\text{currentWeightsSum}$ – сумма элементов набора, то есть сумма весов
всех пассажиров, которых мы можем посадить в автобус, и
$\text{currentWeights}\text{Size}$ – количество элементов в наборе, то
есть количество пассажиров, которые мы можем посадить в автобус.

2.2 Переберем всех пассажиров с индексами $j$ от $i$ до
$\text{peopleCount}$. Далее рассмотрим следующие случаи:

2.2.1 В автобусе есть достаточно свободного места, и мы можем спокойно
посадить пассажира $j$ в автобус, то есть
$\text{peopleWeights}\left( j \right) \leq busCapacity - currentWeightsSum$.
Добавляем вес пассажира $j$ в набор $\text{currentWeights}$, увеличиваем
сумму $\text{currentWeightsSum}$ на вес пассажира $j$ и инкрементируем
переменную $\text{currentWeightsSize}$.

2.2.2 Если пассажир не влезает в автобус, необходимо взять максимальный
вес пассажира$\text{\ top}$, который находится в наборе
$\text{currentWeights}$. Если вес $\text{top}$ больше, чем вес
$\text{peopleWeights}\left( j \right)\ $пассажира $j$, заменим этот вес
на вес пассажира $j$, а также изменим вместимость
$currentWeightsSum + = peopleWeights\left( j \right) - top$. Таким
образом мы не меняем максимальное количество пассажиров, однако
увеличиваем доступную вместимость автобуса, что дает нам больше свободы
в будущем при добавлении новых пассажиров. Иначе следует пропустить
пассажира, поскольку его добавление не делает вместимость оптимальным.

2.3 Запишем полученное максимальное количество в массив
$\text{weightsPerOneBus}\left( i \right)\left( j \right)\  = \ currentWeightsSize$.

Исходя из этого, можно сделать вывод, что для хранения набора
$\text{currentWeights}$ следует использовать структуру данных
$priority\_ queue$ для того, чтобы мы могли быстро находить максимальное
значение в этом наборе. А значит, что значение $\text{top}$
(максимальный вес пассажира в набое) мы можем получить используя
$currentWeights.top()$ за $O(1)$. Для того, чтобы заменить максимальный
вес пассажира $\text{top}$ на вес $peopleWeights(j)$ пассажира $j$
следует достать максимальный вес $\text{top}$ с помощью
$currentWeights.pop()$, который работает за $O(logn)$,
где $n$ – количество элементов в наборе ($currentWeightsSize)$, и
добавить новый вес $currentWeights.push(peopleWeights(j))$, который
работает за $O(logn)$, где $n$ – количество элементов в наборе
($currentWeightsSize - 1)$. Поскольку $\text{currentWeightsSize}$ может
принимать максимальное значение $N$ – количество людей
$\text{peopleCount}$, то время работы изменения очереди в целом будет
работать за $O\left( \log N \right)$.

3\. Создадим массив $\text{optimal}\text{Weights}$ размером
$peopleCount*\text{busCount}$. Заполним его с помощью динамического
программирования, разбив задачу на подзадачи «максимальное количество
пассажиров $\text{optimal}Weights(i)(j)$, которое можно поместить в
количество автобусов $j$, взяв пассажиров от $0$ до $i$. Поскольку у нас
уже имеются такие данные для одного автобуса, то база динамики –
$\text{optimal}\text{Weights}\left( i \right)\left( j \right) = \ weightsPerOneBus(0)(i)$.
Для заполнения будем брать максимальное $\text{optimal}Weights(i)(j)$,
то есть
$\text{optimal}\text{Weights}\left( i \right)\left( j \right)\  = max(\text{optimal}\text{Weights}\left( i \right)(j),\ \ \text{optimal}\text{Weights}\left( k \right)\left( j - 1 \right) + weightsPerOneBus(k + 1)(i)$),
где $k\ ot\ 0\ do\ i$. То есть либо $\text{optimal}\text{Weights}$ для
пассажиров от $0$ до $i$ для количества автобусов $j$ уже есть
оптимальным, либо мы можем взять больше пассажиров, если возьмем
оптимальное количество пассажиров
$\text{optimal}\text{Weights}\left( k \right)\left( j - 1 \right)$ для
пассажиров от $0$ до $k$ для количества автобусов $(j - 1)$, а также
добавим новый автобус для остальных пассажиров
$weightsPerOneBus(k + 1)(i)$ – максимальное количество пассажиров на
отрезке от $k + 1$ до $i$.

4\. Ответ будет храниться в
$\text{optimal}\text{Weights}\left( peopleCount - 1 \right)(busCount - 1)$
– максимальное количество пассажиров, которые можно посадить в
$\text{busCount}$ автобусов, используя $\text{peopleCount}$ пассажиров.

Доказательство

В пункте 2 заполняем массив $\text{weightsPerOneBus}$. Перебирая
пассажиров, заполняем очередь $\text{currentWeights}$, с помощью которой
определяется максимальное количество пассажиров на заданном промежутке.
При рассмотрении нового пассажира следует рассмотреть такие случаи: 1)
пассажир вмещается в автобус – помещаем пассажира в автобус и
увеличиваем максимальное количество, 2) пассажир не помещается в
автобус: 2.1) если объем этого пассажира меньше, чем максимальный объем
пассажира, который уже находится в автобусе, следует их заменить, таким
образом количество не меняется, но увеличивается свободное место, что
даст нам больше возможностей для помещения следующих пассажиров, 2.2)
объем пассажира больше, чем максимальный объем пассажира, который уже
находится в автобусе, то этого пассажира следует пропустить, поскольку
на количество это не влияет, а заменив их только потеряется свободное
место, которое мог бы занять какой-либо из следующих пассажиров.
Следовательно, после рассмотрения каждого из пассажиров мы будем иметь
максимальное возможное количество пассажиров на заданном промежутке.

В пункте 3 заполняем массив $\text{optimal}\text{Weights}$. Перебирая
все возможное количестов автобусов, а также в каждый раз перебирая
пассажиров на отрезках от 0 до $k$ и от $k + 1$ до $i$ будут перебраны
все возможные варианты размещения в автобусе. Для этого необходимо
каждый раз сравнивать текущее оптимально размещение и выбирать
наибольшее: либо в $j$ автобусах уже хранится максимальное количество
пассажиров, либо можно взять $j - 1$ автобусов с уже оптимальным
размещением пассажиров от 0 до $k$, которое мы нашли раннее, и добавить
новый автобус с пассажирами от $k + 1$ до $i$. Таким образом, на каждой
итерации будет выбираться наибольшее количество пассажиров, а поскольку
изначальные данные $\text{weightsPerOneBus}$, которые были занесены в
$\text{optimal}\text{Weights}$ с количеством автобусов 1, были уже
оптимальными, то и каждое вычисление для следующего количества автобусов
будет тоже оптимальным. Это значит, что выбрав $M$ автобусов с
пассажирами на промежутке от 0 до $N$, получим максимальное количество
пассажиров, используя $M$ автобусов и $N$ людей, что и есть ответом на
задачу. Следовательно, алгоритм работает правильно.

Итоги

Оценка памяти. Для решения задачи потребовалось: массив
$\text{peopleWeights}$ размером $N$; массив $\text{weightsPerOneBus}$
размером $N*N$; очередь $\text{currentWeights}$, максимальный размер
которой мог достичь $N$; а также массив $\text{optimal}\text{Weights}$
размером $N*M$. Следовательно, полная сложность алгоритма по памяти
равна $O(N + \ N*N + N + \ N*M) \approx O(N*N + N*M)$.

Оценка времени работы. Для решения задачи потребовалось: считать данные
в массив $\text{peopleWeights}$ за $O(N)$; заполнить массив
$\text{weightsPerOneBus}$ с помощью двух вложенных циклов по $i$ и $j$,
за $O(N)$ каждый, а также изменять очередь за $O(\log N)$, что в целом
составляет $O(N*\ N*\log N)$; а также заполнить массив
$\text{optimal}\text{Weights}$ с помощью трех вложенных циклов
по$\text{\ j}$, который работал за $O\left( M \right)$ и $i,k$, которые
работали за $O\left( N \right)$ каждый, что в целом составляет
$O(M*\ N*N)$. Следовательно, полная сложность алгоритма по времени
работы
равна$\text{\ O}\left( N + N*N*\log N + \ M*\ N*N \right) \approx O(M*\ N*N + N*N*\log N)$.

Итог:

-   затраты по памяти$\ O(N*N + N*M)$.

-   затраты по времени$\ O(M*\ N*N + N*N*\log N)$.

