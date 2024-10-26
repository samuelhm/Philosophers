
# Philosophers

**Philosophers** es un proyecto de la escuela 42 basado en el problema clásico de los **filósofos comensales**. El objetivo del proyecto es aplicar conceptos de concurrencia, manejo de threads, sincronización y uso de mutexes en C para resolver un problema común en sistemas paralelos.

## Tabla de contenidos

- [Descripción](#descripción)
- [Estructura del Proyecto](#estructura-del-proyecto)
- [Compilación e Instalación](#compilación-e-instalación)
- [Uso](#uso)
- [Detalles Técnicos](#detalles-técnicos)
- [Autores](#autores)

## Descripción

El problema de los **filósofos comensales** plantea la situación de varios filósofos (threads) que están sentados alrededor de una mesa y deben alternar entre comer, pensar y dormir. Cada filósofo necesita dos tenedores (MUTEX) para comer, pero solo hay un tenedor entre cada par de filósofos. El reto es evitar "data races" y evitar que los filósofos caigan en un estado de inanición.

## Estructura del Proyecto

El proyecto está organizado en los siguientes componentes:

- **Estructuras de datos** para representar a los filósofos y los recursos.
- **Funciones de manejo de threads** para crear y gestionar los filósofos como hilos independientes.
- **Mecanismos de sincronización** utilizando mutexes para controlar el acceso a los recursos compartidos (tenedores).

## Compilación e Instalación

1. **Clona el repositorio**:
   ```bash
   git clone https://github.com/samuelhm/Philosophers.git
   cd Philosophers
   ```

2. **Compila el proyecto** usando el comando `make`:
   ```bash
   make
   ```

3. **Ejecuta el programa** pasando los argumentos necesarios:

   ```bash
   ./philo <número_de_filósofos> <tiempo_para_morir> <tiempo_para_comer> <tiempo_para_dormir> [<número_de_comidas>]
   ```

   Por ejemplo:

   ```bash
   ./philo 5 800 200 200
   ```

   Esto ejecutará el programa con 5 filósofos, donde cada filósofo morirá si no come en 800ms, y cada comida y tiempo de sueño durarán 200ms.

## Detalles Técnicos

- **Manejo de Threads**: Cada filósofo se representa como un hilo independiente que alterna entre los estados de pensar, comer y dormir.
- **Sincronización con Mutexes**: Los tenedores se representan como mutexes para evitar condiciones de carrera y garantizar el acceso seguro a los recursos compartidos.
- **Condiciones de Parada**: El programa se detendrá si un filósofo no puede comer en el tiempo límite o si se ha alcanzado el número de comidas especificado (si se proporciona).

## Autores

- **Samuel H. M.** - [GitHub](https://github.com/samuelhm)

