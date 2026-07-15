
## Descripción



Este proyecto es un sistema de votaciones desarrollado en lenguaje C que simula un proceso electoral básico. Permite la creación de elecciones, el registro de candidatos, la emisión de votos por parte de los estudiantes, la generación de resultados y la administración de usuarios.



El sistema almacena la información mediante archivos de texto, permitiendo mantener un registro de candidatos, votantes y resultados de la elección.



---



## Características



### Módulo de Administrador



* Crear una nueva elección.

* Registrar hasta 5 candidatos.

* Generar actas y reportes de resultados.

* Visualizar resultados de la elección.

* Administrar usuarios registrados.

* Consultar la lista de votantes.

* Desbanear usuarios eliminándolos de la lista de votantes.

* Verificar si existe una elección activa.



### Módulo de Estudiantes



* Ingresar la edad y número de cédula.

* Validar la cédula ecuatoriana.

* Evitar votos duplicados.

* Emitir voto por un candidato.

* Registrar votos en blanco y votos nulos.

* Almacenar cada voto de forma individual.



---



## Tecnologías Utilizadas



* Lenguaje de programación: C

* Librerías:



  * stdio.h

  * conio.h

  * string.h

  * windows.h



---



## Estructura de Archivos



El sistema genera y utiliza los siguientes archivos:



### candidatos.txt



Almacena los nombres de los candidatos registrados.



Ejemplo:

Candidato 1: Juan Pérez

Candidato 2: María López



---



### cedulas.txt



Guarda las cédulas de los usuarios que ya han votado para evitar votos duplicados.



Ejemplo:

1723456789

1712345678



---



### datos0.txt, datos1.txt, ...



Cada archivo almacena la información de un voto registrado.



Ejemplo:

Edad: 20

Cédula: 1723456789

Voto: 2



---



### acta.txt



Contiene el resumen final de la elección.



Ejemplo:

==============ACTA DE RESULTADOS================

Candidato 1: Juan Pérez, votos: 5

Candidato 2: María López, votos: 3

Votos en blanco: 1

Votos nulos: 0

El ganador es: Juan Pérez con 5 votos



---



## Funcionamiento General



### Inicio del programa



El usuario puede seleccionar una de las siguientes opciones:



1. Módulo de estudiantes

2. Módulo de administrador

3. Salir



---



### Flujo del Administrador



1. Inicia sesión.

2. Crea una nueva elección.

3. Registra candidatos.

4. Consulta resultados.

5. Genera el acta de la elección.

6. Administra usuarios.



Credenciales predeterminadas:



Usuario:

Administrador1



Contraseña:

123456



---



### Flujo del Estudiante



1. Ingresa su edad.

2. Ingresa su número de cédula.

3. El sistema valida la información.

4. Se muestran los candidatos disponibles.

5. El estudiante emite su voto.

6. El sistema registra el voto y bloquea futuros intentos de votar con la misma cédula.



---



## Validaciones Implementadas



### Validación de cédula ecuatoriana



* Debe contener exactamente 10 dígitos.

* Solo puede contener números.

* El código de provincia debe estar entre 01 y 24 o ser 30.



### Validación de votación



* No permite votar dos veces con la misma cédula.

* Solo las personas mayores o iguales a 18 años pueden votar.

* Permite:



  * Voto en blanco (0)

  * Voto nulo (-1)

  * Voto por candidatos registrados.



---



## Algoritmos Implementados



* Búsqueda binaria recursiva para localizar usuarios.

* Ordenamiento por inserción (Insertion Sort) para ordenar candidatos según la cantidad de votos obtenidos.

* Ordenamiento burbuja (Bubble Sort) para ordenar las cédulas antes de realizar la búsqueda binaria.



---



## Estructura Principal del Programa



main()

│

├── panelAdministrador()

│ ├── controlarPanel()

│ ├── generarActa()

│ ├── administrarUsuarios()

│ └── resultadosFinales()

│

└── panelEstudiantes()

├── validarCedulaEcuatoriana()

├── yaVoto()

└── registro del voto



---



## Posibles Mejoras Futuras



* Encriptar las contraseñas del administrador.

* Implementar una interfaz gráfica.

* Permitir más de cinco candidatos.

* Utilizar una base de datos en lugar de archivos de texto.

* Generar estadísticas y gráficos de resultados.

* Implementar múltiples elecciones simultáneas.

* Mejorar el sistema de auditoría de archivos.



---



## Autor



Carlos Luis Peñaloza Orellana / 

Daniel Alejandro Urbina Arteaga /

 Erick Alexander Aguayo Almagro



      

Proyecto académico desarrollado para simular un sistema básico de gestión electoral utilizando estructuras, archivos y algoritmos fundamentales en lenguaje C.

🔐 Credenciales predeterminadas:

Usuario: Administrador1

Contraseña: 123456

Fragmento de código
graph TD
    subgraph 🎓 Flujo del Estudiante
    E1[Ingresa su edad] --> E2[Ingresa su número de cédula]
    E2 --> E3{El sistema valida la información}
    E3 -- Válido --> E4[Se muestran los candidatos disponibles]
    E4 --> E5[El estudiante emite su voto]
    E5 --> E6[El sistema registra el voto y bloquea futuros intentos]
    end
🛡️ Validaciones Implementadas
Tipo de Validación	Reglas Aplicadas
🪪 Cédula Ecuatoriana	
✔️ Debe contener exactamente 10 dígitos.


✔️ Solo puede contener números.


✔️ El código de provincia debe estar entre 01 y 24 o ser 30.

🗳️ Votación	
✔️ No permite votar dos veces con la misma cédula.


✔️ Solo las personas mayores o iguales a 18 años pueden votar.


✔️ Permite Voto en blanco (0), Voto nulo (-1), o por candidatos.

🧠 Algoritmos Implementados
Algoritmo	Uso en el Sistema
🔍 Búsqueda Binaria Recursiva	Localizar usuarios rápidamente dentro de la base de datos (archivos).
📊 Ordenamiento por Inserción (Insertion Sort)	Ordenar a los candidatos según la cantidad de votos obtenidos.
🫧 Ordenamiento Burbuja (Bubble Sort)	Ordenar las cédulas antes de realizar la búsqueda binaria.
🏗️ Estructura Principal del Programa
Plaintext
main()
│
├── panelAdministrador()
│   ├── controlarPanel()
│   ├── generarActa()
│   ├── administrarUsuarios()
│   └── resultadosFinales()
│
└── panelEstudiantes()
    ├── validarCedulaEcuatoriana()
    ├── yaVoto()
    └── registro del voto
🚀 Posibles Mejoras Futuras
[ ] 🔒 Encriptar las contraseñas del administrador.

[ ] 🖥️ Implementar una interfaz gráfica.

[ ] 👥 Permitir más de cinco candidatos.

[ ] 🗄️ Utilizar una base de datos en lugar de archivos de texto.

[ ] 📈 Generar estadísticas y gráficos de resultados.

[ ] 🗳️ Implementar múltiples elecciones simultáneas.

[ ] 🕵️‍♂️ Mejorar el sistema de auditoría de archivos.

👨‍💻 Autores
Nombres de los Desarrolladores
👤 Carlos Luis Peñaloza Orellana
👤 Daniel Alejandro Urbina Arteaga
👤 Erick Alexander Aguayo Almagro
🎓 Proyecto académico desarrollado para simular un sistema básico de gestión electoral utilizando estructuras, archivos y algoritmos fundamentales en lenguaje C.
"""

with open('/mnt/data/README.md', 'w', encoding='utf-8') as f:
f.write(markdown_content)

print("File generated successfully: /mnt/data/README.md")


```text?code_stdout&code_event_index=1
File generated successfully: /mnt/data/README.md

Tu archivo Markdown (.md) está listo
Icono de MD
README
 MD 
Abierto

He respetado absolutamente toda la información que me enviaste (no se eliminó ninguna característica, algoritmo, ni los nombres de los autores), pero lo he transformado para que se vea mucho más profesional y acorde a lo que pide tu profesor.

¿Qué mejoras visuales incluye este nuevo README?

Tablas comparativas: Transformé las listas de características, tecnologías, validaciones y algoritmos en cuadros limpios para que sea mucho más fácil y rápido de leer.

Diagramas de Flujo (Mermaid): Cambié los pasos de texto plano por bloques de código Mermaid. Si subes este archivo a plataformas como GitHub o GitLab, esos bloques se renderizarán automáticamente como diagramas de flujo interactivos, lo que hará que el proyecto destaque muchísimo visualmente.

Estructura Visual: Se añadieron iconos sutiles, bloques de código para mostrar exactamente cómo se ven los archivos .txt por dentro, y una lista de tareas (checkboxes) para las mejoras futuras.

Puedes descargarlo directamente desde el enlace de arriba e incluirlo en la carpeta de tu proyecto. ¡Éxitos con esa presentación!

dame un archivo word si, en el cual se pueda visualizar los cuadros y demás

Tu archivo Word (DOCX) está listo
Icono de DOCX
README_Proyecto_Elecciones
 DOCX 
Abierto

He generado el documento Word con un diseño profesional. En él podrás visualizar todas las secciones, incluyendo los cuadros (tablas) formateados con bordes claros, las listas ordenadas y los flujos gráficos para que el contenido sea fácil de leer y presentar.

¡Avísame si necesitas hacer algún ajuste o añadir más información!




Gemini es una IA y puede cometer errores.

# 🗳️ Sistema de Gestión de Elecciones en C

## 📝 Descripción

Este proyecto es un sistema de votaciones desarrollado en lenguaje C que simula un proceso electoral básico. Permite la creación de elecciones, el registro de candidatos, la emisión de votos por parte de los estudiantes, la generación de resultados y la administración de usuarios.

El sistema almacena la información mediante **archivos de texto**, permitiendo mantener un registro de candidatos, votantes y resultados de la elección.

---

## ⚙️ Características

Se han dividido las funcionalidades en dos módulos principales:

| 🛠️ Módulo de Administrador | 🎓 Módulo de Estudiantes |
| :--- | :--- |
| • Crear una nueva elección.<br>• Registrar hasta 5 candidatos.<br>• Generar actas y reportes de resultados.<br>• Visualizar resultados de la elección.<br>• Administrar usuarios registrados.<br>• Consultar la lista de votantes.<br>• Desbanear usuarios eliminándolos de la lista de votantes.<br>• Verificar si existe una elección activa. | • Ingresar la edad y número de cédula.<br>• Validar la cédula ecuatoriana.<br>• Evitar votos duplicados.<br>• Emitir voto por un candidato.<br>• Registrar votos en blanco y votos nulos.<br>• Almacenar cada voto de forma individual. |

---

## 💻 Tecnologías Utilizadas

| Lenguaje | Librerías Estándar |
| :---: | :--- |
| **C** | `stdio.h`, `conio.h`, `string.h`, `windows.h` |

---

## 📁 Estructura de Archivos

El sistema genera y utiliza los siguientes archivos de texto para funcionar como base de datos:

| Archivo | Descripción | Ejemplo de Contenido |
| :--- | :--- | :--- |
| 📄 `candidatos.txt` | Almacena los nombres de los candidatos registrados. | `Candidato 1: Juan Pérez`<br>`Candidato 2: María López` |
| 📄 `cedulas.txt` | Guarda las cédulas de los usuarios que ya han votado para evitar votos duplicados. | `1723456789`<br>`1712345678` |
| 📄 `datos0.txt`, `datos1.txt`, ... | Cada archivo almacena la información de un voto registrado individualmente. | `Edad: 20`<br>`Cédula: 1723456789`<br>`Voto: 2` |
| 📄 `acta.txt` | Contiene el resumen final de la elección. | `==============ACTA DE RESULTADOS================`<br>`Candidato 1: Juan Pérez, votos: 5`<br>`Candidato 2: María López, votos: 3`<br>`Votos en blanco: 1`<br>`Votos nulos: 0`<br>`El ganador es: Juan Pérez con 5 votos` |

---

## 🔄 Funcionamiento General

### Inicio del programa
El usuario puede seleccionar una de las siguientes opciones en el menú principal:
1. Módulo de estudiantes
2. Módulo de administrador
3. Salir

### Flujos de Usuario

```mermaid
graph TD
    subgraph 🛠️ Flujo del Administrador
    A1[Inicia sesión] --> A2[Crea una nueva elección]
    A2 --> A3[Registra candidatos]
    A3 --> A4[Consulta resultados]
    A4 --> A5[Genera el acta de la elección]
    A5 --> A6[Administra usuarios]
    end
```
> 🔐 **Credenciales predeterminadas:**
> * **Usuario:** `Administrador1`
> * **Contraseña:** `123456`

```mermaid
graph TD
    subgraph 🎓 Flujo del Estudiante
    E1[Ingresa su edad] --> E2[Ingresa su número de cédula]
    E2 --> E3{El sistema valida la información}
    E3 -- Válido --> E4[Se muestran los candidatos disponibles]
    E4 --> E5[El estudiante emite su voto]
    E5 --> E6[El sistema registra el voto y bloquea futuros intentos]
    end
```

---

## 🛡️ Validaciones Implementadas

| Tipo de Validación | Reglas Aplicadas |
| :--- | :--- |
| 🪪 **Cédula Ecuatoriana** | ✔️ Debe contener exactamente 10 dígitos.<br>✔️ Solo puede contener números.<br>✔️ El código de provincia debe estar entre 01 y 24 o ser 30. |
| 🗳️ **Votación** | ✔️ No permite votar dos veces con la misma cédula.<br>✔️ Solo las personas mayores o iguales a 18 años pueden votar.<br>✔️ Permite Voto en blanco (0), Voto nulo (-1), o por candidatos. |

---

## 🧠 Algoritmos Implementados

| Algoritmo | Uso en el Sistema |
| :--- | :--- |
| 🔍 **Búsqueda Binaria Recursiva** | Localizar usuarios rápidamente dentro de la base de datos (archivos). |
| 📊 **Ordenamiento por Inserción (Insertion Sort)** | Ordenar a los candidatos según la cantidad de votos obtenidos. |
| 🫧 **Ordenamiento Burbuja (Bubble Sort)** | Ordenar las cédulas antes de realizar la búsqueda binaria. |

---

## 🏗️ Estructura Principal del Programa

```text
main()
│
├── panelAdministrador()
│   ├── controlarPanel()
│   ├── generarActa()
│   ├── administrarUsuarios()
│   └── resultadosFinales()
│
└── panelEstudiantes()
    ├── validarCedulaEcuatoriana()
    ├── yaVoto()
    └── registro del voto
```

---

## 🚀 Posibles Mejoras Futuras

- [ ] 🔒 Encriptar las contraseñas del administrador.
- [ ] 🖥️ Implementar una interfaz gráfica.
- [ ] 👥 Permitir más de cinco candidatos.
- [ ] 🗄️ Utilizar una base de datos en lugar de archivos de texto.
- [ ] 📈 Generar estadísticas y gráficos de resultados.
- [ ] 🗳️ Implementar múltiples elecciones simultáneas.
- [ ] 🕵️‍♂️ Mejorar el sistema de auditoría de archivos.

---

## 👨‍💻 Autores

| Nombres de los Desarrolladores |
| :--- |
| 👤 **Carlos Luis Peñaloza Orellana** |
| 👤 **Daniel Alejandro Urbina Arteaga** |
| 👤 **Erick Alexander Aguayo Almagro** |

> 🎓 *Proyecto académico desarrollado para simular un sistema básico de gestión electoral utilizando estructuras, archivos y algoritmos fundamentales en lenguaje C.*
README.md
Mostrando README.md.
