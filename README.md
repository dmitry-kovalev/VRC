# Адаптер для симулятора VRC на базе Arduino Uno / Mega
## Подключение
- Подключаем пин D2 к сигнальному пину газа, пин D3 к сигнальному пину руля, подключаем питание.

## Прошивка
Прошивка состоит из двух частей:
- Прошиваем в Arduino программу VRC.ino
- Переключаем Arduino в режим джойстика
    - Ставим драйвера. Для этого скачиваем проект отсюда https://github.com/AlanChatham/UnoJoy/tree/master/ и запускаем `UnoJoyDriverInstaller.bat` из папки `Drivers`
    - Ставим Atmel's FLIP tool: https://www.microchip.com/developmenttools/ProductDetails/flip
    - Переключаем Arduino в UNO DFU mode. Для этого кратковременно закорачиваем два ближайших к USB порту пина в блоке из 6-пин.
    - Запускаем `TurnIntoAJoystick.bat` из папки `UnoJoy` для Uno или из `MegaJoy` для Mega
- Отключаем плату и подключаем снова

Чтобы вернуть Arduino в обычный режим, снова закорачиваем два пина и запускаем `TurnIntoAnArduino.bat`

Подробнее см. тут https://github.com/AlanChatham/UnoJoy