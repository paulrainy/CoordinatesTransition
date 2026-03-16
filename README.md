# CoordinatesTransition

Библиотека на C++ для преобразования координат между различными системами отсчета: **ПЗ-90.11**, **СК-42** и **WGS-84**.

---

## 📂 Структура проекта

```text
├── CMakeLists.txt        # Сценарий сборки CMake
├── include/              # Заголовочние файлы
│   ├── CoordinateTypes.h    # Структуры GeodeticPoint, RectangularPoint, SpatialPoint
│   └── CoordinateConverter.h# Функции преобразования
├── src/                  # Реализация логики
│   └── CoordinateConverter.cpp
└── tests/                # Тесты (Google Test)
    └── CoordinateTests.cpp
```

---

## 🚀 Использование (Пример)

```cpp
#include "CoordinateConverter.h"
#include <iostream>

using namespace Coordinates;

int main() {
    try {
        // Создаем геодезическую точку (широта, долгота в радианах, высота)
        GeodeticPoint geoPoint(42.0 * M_PI / 180.0, 32.0 * M_PI / 180.0, 100.0);

        // 1. Преобразование в пространственную с использованием ПЗ-90
        SpatialPoint spatial = GeodeticToSpatial(geoPoint, Standards::PZ90_11);
        std::cout << "Spatial Point: X=" << spatial.x << ", Y=" << spatial.y << std::endl;

        // 2. Преобразование ПЗ-90 Геодезических в Прямоугольные (Гаусса-Крюгера)
        RectangularPoint rect = PZ90ToRectangular(geoPoint);
        std::cout << "Rectangular Point: X=" << rect.x << ", Y=" << rect.y << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка валидации координат: " << e.what() << std::endl;
    }
    return 0;
}
```

---

## 🛠️ Сборка и Запуск

### Требования
- Компилятор с поддержкой **C++17**
- **CMake** (версии `3.24` и выше)

### 1. Сборка
Проект использует **FetchContent** для автоматического скачивания `GoogleTest`, поэтому дополнительные зависимости для тестов устанавливать не нужно.

```bash
mkdir -p build && cd build
cmake ..
make
```

### 2. Запуск Тестов
Для ручного запуска исполняемого файла тестов:
```bash
./coord_tests
```

Или через утилиту `ctest`:
```bash
ctest --output-on-failure
```

---

## 🛡️ Валидация
Конструкторы точек защищены проверками:
- `Latitude` (Широта): `[-PI/2, PI/2]`
- `Longitude` (Долгота): `[-PI, PI]`

При попытке создать точку с ошибочными значениями будет выброшено исключение `std::invalid_argument`.
