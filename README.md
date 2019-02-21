# Пакетная обработка команд - Сетевой сервер (Bulk Server)
[![Build Status](https://travis-ci.org/boydad/HW12L24-BulkServer.svg?branch=master)](https://travis-ci.org/boydad/HW12L24-BulkServer)


## Условие задания

Основная цель переработать [Задание 11](https://github.com/boydad/HW11L21-Async) так, чтобы чтобы ввод данных осуществлялся по сети. 

Необходимо разработать асинхронный сервер, работающий с протоколом аналогичным консоли, принимающий построчно команды. Дальнейшая обработка остается без изменений - вывод на консоль и в файлы. 

В качестве библиотеки сетевого взаимодействия можно использовать boost.asio (можно использовать любую предоставляющую асинхронные возможности).

Поскольку не предполагается отправка данных основное взаимодействие будет вокруг методов async_read и async_accept. 

Порядок запуска:

`# bulk_server <port> <bulk_size>`

где

* port – номер tcp порта для входящих соединений. Соединения должны обслуживаться с произвольных интерфейсов.

* bulk_size – уже знакомый размер блока команд. 

Опционально взять за основу вместо однопоточной версии из [Задания 7](https://github.com/boydad/HW7L16-Cmd) многопоточную реализацию из [Задания 10](https://github.com/boydad/HW10L20-Threads).

Не должно быть искусственных ограничений на количество одновременно подключенных клиентов. Команды полученные из разных соединений должны смешиваться между собой, команды окружённые { и } обрабатываются без смешивания.


## Установка пакета

```
wget -qO - https://bintray.com/user/downloadSubjectPublicKey?username=bintray | sudo apt-key add -

echo "deb https://dl.bintray.com/boydad/otus-cpp trusty main" | sudo tee -a /etc/apt/sources.list

sudo add-apt-repository ppa:jonathonf/gcc-7.1

sudo apt-get update && sudo apt-get install gcc-7 g++-7 bulk_server
```