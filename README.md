# TANCKIKI-2D

  Необходимо реализовать игрушку "Танчики 2D", суть которого в следующем. Пользователь (игрок) управлет своим танчиком, который может двигаться по четырём направлениям и стрелять снарядами (будем считать, что она способна летать по всей карте). Снаряды, попадая по другому танку, наносят урон, снижая запас здоровья. При неположительном запасе здоровья танк уничтожается и игрок теряет над ним контроль.
  Игра мультиплеерная. Взаимодействие игроков будет через удаленный сервер.
  Игрок имеет следующие действия:
  - Появиться на карте с координатами (x0, y0)
  - Двигаться вверх
  - Двигаться вниз
  - Двигаться влево
  - Двигаться вправо
  - Остановиться
  - Выстрелить
  - Уничтожиться
  - Изменить запас здоровья на ∆HP
  - Отправить в чат игры сообщение

  На каждое действие клиент отправляет сообщение на сервер, который, в свою очередь, транслирует это же сообщение всем остальным подключившимся игрокам. А игроки, получив сообщение от сервера, начинают обновлять картину происходящего. 
  На мой взгляд, это – минимум, что должно быть сделано в проекте.
  
  Можно сделать дополнительные приколюхи, которые сделают нашу игрушку более интересной:
  1. Туман войны
  2. Вода как ландшафт (через воду проезжать нельзя, только морская техника)
  3. Самолеты-бомбардировщики, разведчики, оглушатели (как они будут действовать – придумаем сами)
  4. Виды орудий на танк (пушки, пулеметы, лазеры, артиллерия, и так далее)
  5. Морская техника (скажем, она будет обеспечивать нас продовольствием, которая играет ключевую роль в игре)
  6. Мультиязычность, игровое меню с игровыми командами
  7. Конвертирование растрового изображения в карту игры
  8. Генерация игровых карт
  9. Голосовые сообщения реального времени
  10. Отлаженная синхронизация клиента и сервера при медленных соединениях
  
  
