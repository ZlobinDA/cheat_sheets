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
#### SNMPv2
В конфигурационном файле /etc/snmp/snmptrapd.conf нужно раскомментировать (или добавить) строку

    authCommunity log,execute,net public
#### SNMPv3
    TODO

### Запускаем snmptrapd вручную

    sudo snmptrapd -f -L o

В новом терминале проверяем статус и конфигурацию smpd

    sudo netstat -nlup | grep 162

Ожидаемый вывод

    udp        0      0 0.0.0.0:162             0.0.0.0:*                           4784/snmptrapd  

## Отправка тестовых сигналов
### Локальный тестовый сигнал
В новом терминале отправляем тестовый сигнал на себя

    sudo snmptrap -c public -v 2c 127.0.0.1 "" 1.3.3.3.3.3.3.3 1.2.2.2.2.2.2 s "My First TRAP"

В терминале с запущенным snmptrapd подтверждаем получение сигнала.

Warning: Вроде бы сигнал должен писаться в файл сислога /var/log/syslog, но у меня не пишется.

### Тестовый сигнал на удаленный хост
На удаленном хосте должен быть запущен snmptrapd

    sudo snmptrap -c public -v 2c <ip> "" 1.3.3.3.3.3.3.3 1.2.2.2.2.2.2 s "Remote trap test" 
