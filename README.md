# 🗳 Sistema de Gestión de Elecciones en C

```text
┌─────────────────────────────────────────────────────────────────────────────┐
│                  SISTEMA DE GESTIÓN DE ELECCIONES EN C                      │
├─────────────────────────────────────────────────────────────────────────────┤
│ Proyecto académico desarrollado en lenguaje C que simula un proceso         │
│ electoral completo mediante el uso de estructuras, archivos de texto        │
│ y algoritmos clásicos de programación.                                      │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 📖 Descripción

Este proyecto consiste en un sistema de votaciones desarrollado en lenguaje **C**, cuyo objetivo es simular el funcionamiento de un proceso electoral. El sistema permite crear una elección, registrar candidatos, validar a los votantes, almacenar los votos emitidos y generar un acta final con los resultados.

Toda la información se administra mediante **archivos de texto**, permitiendo almacenar de forma persistente los candidatos, los votantes registrados, los votos emitidos y el acta oficial de resultados.

---

# ✨ Características del Sistema

|          Módulo         | Funcionalidades                                                                                                           |
| :---------------------: | ------------------------------------------------------------------------------------------------------------------------- |
| 👨‍💼 **Administrador** | Crear elecciones, registrar candidatos, generar actas, visualizar resultados, administrar usuarios y auditar información. |
|    🗳 **Estudiantes**   | Validar cédula, registrar voto, evitar votos duplicados, emitir votos válidos, blancos o nulos.                           |

---

# 🏗 Arquitectura General del Programa

```text
                             ┌──────────────┐
                             │   main()     │
                             └──────┬───────┘
                                    │
                 ┌──────────────────┴──────────────────┐
                 │                                     │
                 ▼                                     ▼
      ┌────────────────────┐              ┌────────────────────┐
      │ Panel Administrador│              │ Panel Estudiantes  │
      └─────────┬──────────┘              └─────────┬──────────┘
                │                                   │
                ▼                                   ▼
      Crear elección                     Validar cédula
      Registrar candidatos               Verificar edad
      Generar resultados                 Evitar doble voto
      Administrar usuarios               Registrar voto
      Generar acta                       Guardar información
```

---

# 🔄 Flujo General del Sistema

```text
                               INICIO
                                  │
                                  ▼
                       ┌────────────────────┐
                       │ Menú Principal     │
                       └─────────┬──────────┘
                                 │
               ┌─────────────────┴──────────────────┐
               │                                    │
               ▼                                    ▼
      Módulo Administrador                 Módulo Estudiante
               │                                    │
               ▼                                    ▼
      Crear Elección                     Validar Cédula
               │                                    │
               ▼                                    ▼
      Registrar Candidatos             Mostrar Candidatos
               │                                    │
               ▼                                    ▼
      Administrar Sistema               Registrar Voto
               │                                    │
               └──────────────────┬─────────────────┘
                                  ▼
                         Generar Resultados
                                  │
                                  ▼
                              Fin del Proceso
```

---

# 📂 Estructura de Archivos

```text
📁 votaciones
│
├── candidatos.txt
├── cedulas.txt
├── datos0.txt
├── datos1.txt
├── datos2.txt
├── datos3.txt
├── ...
└── acta.txt
```

---

# 📄 Archivos Utilizados

| Archivo            | Descripción                                                          |
| ------------------ | -------------------------------------------------------------------- |
| **candidatos.txt** | Almacena los nombres de los candidatos registrados.                  |
| **cedulas.txt**    | Guarda las cédulas de los usuarios que ya emitieron su voto.         |
| **datosX.txt**     | Contiene la información correspondiente a cada voto registrado.      |
| **acta.txt**       | Genera el reporte oficial con los resultados finales de la elección. |

---

# ⚙ Tecnologías Utilizadas

| Tecnología        | Uso                                   |
| ----------------- | ------------------------------------- |
| Lenguaje C        | Desarrollo del sistema                |
| stdio.h           | Entrada y salida de datos             |
| string.h          | Manipulación de cadenas               |
| conio.h           | Entrada por teclado                   |
| windows.h         | Compatibilidad con consola de Windows |
| Archivos de texto | Persistencia de la información        |

---

# 👨‍💼 Funcionamiento del Administrador

```text
┌──────────────────────────────────────────────────────────────┐
│                  PANEL DE ADMINISTRACIÓN                     │
├──────────────────────────────────────────────────────────────┤
│ • Crear una nueva elección                                  │
│ • Registrar hasta cinco candidatos                          │
│ • Generar el acta oficial                                   │
│ • Consultar resultados                                      │
│ • Administrar usuarios registrados                          │
│ • Desbanear usuarios                                        │
│ • Verificar si existe una elección activa                   │
└──────────────────────────────────────────────────────────────┘
```

---

# 🗳 Funcionamiento del Estudiante

```text
┌──────────────────────────────────────────────────────────────┐
│                    PANEL DE VOTACIÓN                         │
├──────────────────────────────────────────────────────────────┤
│ 1. Ingresa su edad                                           │
│ 2. Ingresa su número de cédula                               │
│ 3. El sistema valida la información                          │
│ 4. Se muestran los candidatos registrados                    │
│ 5. Selecciona su voto                                        │
│ 6. El voto queda almacenado                                  │
└──────────────────────────────────────────────────────────────┘
```

---

# ✅ Validaciones Implementadas

```text
┌──────────────────────────────────────────────────────┐
│ ✔ Cédula de exactamente 10 dígitos                  │
│ ✔ Solo admite caracteres numéricos                  │
│ ✔ Código de provincia válido                        │
│ ✔ Edad mínima de 18 años                            │
│ ✔ Impide votar dos veces con la misma cédula        │
│ ✔ Permite voto en blanco y voto nulo                │
└──────────────────────────────────────────────────────┘
```

---

# 🧠 Algoritmos Implementados

```text
                    ALGORITMOS UTILIZADOS

               ┌───────────────────────────────┐
               │ Bubble Sort                   │
               │ Ordena las cédulas            │
               └──────────────┬────────────────┘
                              │
                              ▼
               ┌───────────────────────────────┐
               │ Búsqueda Binaria Recursiva    │
               │ Localiza una cédula           │
               └──────────────┬────────────────┘
                              │
                              ▼
               ┌───────────────────────────────┐
               │ Insertion Sort                │
               │ Ordena candidatos por votos   │
               └───────────────────────────────┘
```

---

# 🔐 Credenciales del Administrador

```text
┌──────────────────────────────────────┐
│ Usuario     : Administrador1         │
│ Contraseña  : 123456                 │
└──────────────────────────────────────┘
```

---

# 🚀 Posibles Mejoras Futuras

```text
☐ Implementar una base de datos.
☐ Incorporar una interfaz gráfica.
☐ Permitir más de cinco candidatos.
☐ Encriptar las contraseñas.
☐ Generar estadísticas automáticas.
☐ Soportar múltiples elecciones.
☐ Mejorar el sistema de auditoría.
☐ Exportar resultados en formato PDF.
```

---

# 👥 Autores

| Integrantes del Proyecto               |
| -------------------------------------- |
| 👤 **Carlos Luis Peñaloza Orellana**   |
| 👤 **Daniel Alejandro Urbina Arteaga** |
| 👤 **Erick Alexander Aguayo Almagro**  |

---

# 📌 Observaciones

Este proyecto fue desarrollado con fines académicos para aplicar los conocimientos de programación en lenguaje **C**, haciendo uso de estructuras, funciones, archivos de texto, algoritmos de ordenamiento, búsqueda binaria, validación de datos y modularización del código en un sistema funcional de gestión electoral.
