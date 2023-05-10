# Работа с trap сигналами
Демонстрация работы с trap сигналами на примере ОС Ubuntu

## Установка и настройка snmptrapd

### Устанавливаем пакеты

snmp

    sudo apt install snmp

snmpd

    sudo apt install snmpd

snmptrad

    sudo apt install snmptrapd

### Останавливаем сервисы snmp

snmpd.service

    sudo systemctl stop snmpd.service
    
snmptrapd.socket

    sudo systemctl stop snmptrapd.socket

### Настраиваем snmptrapd

В конфигурационном файле /etc/snmp/snmptrapd.conf нужно добавить строки

#### SNMPv2c

    authCommunity log,execute,net public

#### SNMPv3

    createUser -e 0x8000123acd1ab43abbfff000fa myUser SHA mySecureAuthPassword AES mySecurePrivPass    authUser log,execute myUser

### Запускаем snmptrapd вручную

    sudo snmptrapd -f -L o

запуск с выводом всей отладочной информации

    sudo snmptrapd -D -f -L o

запуск с выводом информации об авторизации пользователя

    sudo snmptrapd -Dusm -f -L o

В новом терминале проверяем статус и конфигурацию smpd

    sudo netstat -nlup | grep 162

Ожидаемый вывод

    udp        0      0 0.0.0.0:162             0.0.0.0:*                           4784/snmptrapd  

## Отправка тестовых сигналов
### Локальный тестовый сигнал
В новом терминале отправляем тестовый сигнал на себя

#### SNMPv2c

    sudo snmptrap -c public -v 2c 127.0.0.1 "" 1.3.3.3.3.3.3.3 1.2.2.2.2.2.2 s "My First TRAP"

#### SNMPv3

snmptrap -e 0x8000123acd1ab43abbfff000fa -v 3 -u myUser -a SHA -A mySecureAuthPassword -x AES -XmySecurePrivPassword -l authPriv 127.0.0.1 "" 1.3.3.3.3.3.3.3 1.2.2.2.2.2.2 s "My First TRAP"


В терминале с запущенным snmptrapd подтверждаем получение сигнала.

### Тестовый сигнал на удаленный хост
На удаленном хосте должен быть запущен snmptrapd

    sudo snmptrap -c public -v 2c <ip> "" 1.3.3.3.3.3.3.3 1.2.2.2.2.2.2 s "Remote trap test" 
