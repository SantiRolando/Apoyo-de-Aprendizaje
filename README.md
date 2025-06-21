# Laboratorio 4 – Programación Avanzada 🧑‍💻

**Universidad Tecnológica del Uruguay – Maldonado**  
**Programación Avanzada – 2024**

Laboratorio final: implementación en C++ de los casos de uso definidos en Laboratorio 2 y 3, usando un menú interactivo y datos de prueba cargables. El código se compila vía Makefile estándar en Linux (compatible con las máquinas de la facultad). Se permite el uso de valgrind para detectar memoria.

---

## 🛠️ Tecnologías y herramientas

- **Lenguaje**: C++ (usando `std::string`, STL: `vector`, `map`, `set`, etc.) :contentReference[oaicite:1]{index=1}  
- **Modularidad**: forward declarations para resolver dependencias circulares entre clases :contentReference[oaicite:2]{index=2}  
- **Makefile**: independiente de IDE, incluye objetivos `all`, `clean`, `run`, `memcheck` (opcional con valgrind) :contentReference[oaicite:3]{index=3}  
- **Linux**: código compilable sin errores en las máquinas del laboratorio  
- **Valgrind** (opcional): usar con `-g` para detectar memory leaks (`valgrind --leak-check=full ./programa`) :contentReference[oaicite:4]{index=4}

---

## 🎯 Qué se entrega

- Todo el código, incluyendo `main()` con menú interactivo y carga de datos de prueba.
- `Makefile` completamente funcional para compilar y ejecutar.
- Ejecución y pruebas en Linux sin IDE.

---


