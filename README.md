# Arkanoid (C++, SFML)
## Как играть: 
- Для начала нажмите Enter.
- Чтобы переместить каретку, используйте стрелку влево-вправо.
- С бонусом (прилипание шарика к каретке) нажмите кнопку Enter, чтобы мяч полетел.

## Описание:
Вверху поля множество прямоугольных блоков. Внизу горизонтально перемещается каретка. По полю летает «мяч», отражаясь от стен, блоков и каретки. Если мяч попадает вниз (мимо каретки) начисляются отрицательные очки /уменьшается каретка/увеличивается число поражений. Блоки бывают разных типов:
- Неразрушаемые. От них мяч просто отскакивает.
- Блоки могут быть со спрятанными бонусами: при попадании вертикально вниз падает бонус
- Блоки, увеличивающие скорость шарика при столкновении
- Блоки имеют уровень здоровья = число попаданий, чтобы блок исчез. За каждое попадание +1 очко игроку, -1 очко здоровья блоку.
- Бонусы: меняют размер каретки, меняют скорость шарика, меняют прилипание шарика к каретке. 
- Бонус: одноразовое дно для шарика – можно один раз пропустить, дно сработает как каретка, и исчезнет. 
- Бонус: шарик в произвольный момент меняет траекторию.
