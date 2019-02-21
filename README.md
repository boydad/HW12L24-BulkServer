# Пакетная обработка команд - Ассинхронная версия
[![Build Status](https://travis-ci.org/boydad/HW11L21-Async.svg?branch=master)](https://travis-ci.org/boydad/HW11L21-Async)


## Условие задания

Основная цель - переработать [Задание 7](https://github.com/boydad/HW7L16-Cmd) так, чтобы ввод данных контролировался внешним кодом. Интерфейс описан в файле async.h. Инициатором обмена будет  выступать внешний код, вместо привычной входной точки main() будет три - connect(), receive() и disconnect(). Порядок вызова следующий: 

* вызывается connect() с размером блока команд. Сохраняется значение возврата. Значение никак не интерпретируется и служит только для передачи контекста;
* вызывается receive() с передачей указателя на начало буфера, размера буфера и контекста. Вызов повторяемый;
* вызывается disconnect() с передачей контекста. Вызов разрушает контекст.

Необходимо реализовать эти функции так, чтобы сохранить прежнюю функциональность проекта и добавить новую возможность. Реализация должна допускать множественные вызовы connect(). Вызовы receive() с разными контекстами не должны мешать друг другу. 

В зависимости от внутренней реализации может возникнуть требование иметь одинаковый размер блока для всех команд. Нет цели вносить столь глубокие изменения. Если потенциальная возможность иметь разные размеры очереди влечет глубокую переработку, функция connect() должна вернуть nullptr.

Вызовы могут осуществляться из разных потоков, однако вызовы с одинаковым контекстом выполняются из одного и того же потока.

Опционально реализовать возможность вызывать все функции из любых потоков.

Опционально взять за основу вместо однопоточной версии из [Задание 7](https://github.com/boydad/HW7L16-Cmd) многопоточную реализацию из [Задания 10](https://github.com/boydad/HW10L20-Threads).

## Требования к реализации

Результатом работы должна стать библиотека устанавливаемая по стандартному пути. Библиотека должна называться libasync.so и
находиться в пакете async.

Результат работы должен быть опубликован на bintray.

## Установка пакета
```
wget -qO - https://bintray.com/user/downloadSubjectPublicKey?username=bintray | sudo apt-key add -

echo "deb https://dl.bintray.com/boydad/otus-cpp trusty main" | sudo tee -a /etc/apt/sources.list

sudo add-apt-repository ppa:jonathonf/gcc-7.1

sudo apt-get update && sudo apt-get install gcc-7 g++-7 bulkmt
```