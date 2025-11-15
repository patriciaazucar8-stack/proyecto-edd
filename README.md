# # POKEWAR: Pokemon Elemental Duel

Juego de batallas Pokémon por turnos en C.

## Estructura del Proyecto

```
proyecto edd/
├── main.c          # Archivo principal del programa
├── pokemon.h       # Definiciones de estructuras y funciones de Pokémon
├── pokemon.c       # Implementación de lógica de Pokémon
├── ui.h            # Definiciones de funciones de interfaz de usuario
├── ui.c            # Implementación de la interfaz visual
├── combate.h       # Definiciones de funciones de combate
├── combate.c       # Implementación del sistema de combate
├── Makefile        # Archivo para compilación automatizada
└── README.md       # Este archivo
```

## Características Implementadas

### ✅ Mejoras Recientes

1. **Movimientos sin duplicados**: Los Pokémon ahora reciben 4 movimientos únicos (sin repetición)
2. **Código modular**: Separado en módulos independientes para mejor organización
3. **Selección aleatoria corregida**: El enemigo se selecciona con distribución uniforme

### 🎮 Funcionalidades

- 9 Pokémon disponibles (3 por tipo: Agua, Fuego, Planta)
- Sistema de tipos con ventajas y desventajas
- 10 movimientos únicos por tipo
- Animaciones visuales con colores
- Barras de HP animadas
- Combate por turnos

## Compilación

### Opción 1: Usando Makefile (recomendado)

```bash
make
```

Para compilar y ejecutar directamente:
```bash
make run
```

Para limpiar archivos compilados:
```bash
make clean
```

### Opción 2: Compilación manual

```bash
gcc -Wall -Wextra -std=c99 -c main.c
gcc -Wall -Wextra -std=c99 -c pokemon.c
gcc -Wall -Wextra -std=c99 -c ui.c
gcc -Wall -Wextra -std=c99 -c combate.c
gcc -Wall -Wextra -std=c99 -o pokewar main.o pokemon.o ui.o combate.o
```

### Opción 3: Compilación simple (todo en uno)

```bash
gcc -Wall -Wextra -std=c99 -o pokewar main.c pokemon.c ui.c combate.c
```

## Ejecución

```bash
.\pokewar.exe
```

## Cómo Jugar

1. Selecciona tu Pokémon (1-9)
2. El juego asignará un rival aleatorio
3. En cada turno, elige uno de tus 4 movimientos
4. El combate continúa hasta que un Pokémon se debilite (HP = 0)

## Sistema de Tipos

- **Agua** es fuerte contra **Fuego** (×1.5 daño)
- **Fuego** es fuerte contra **Planta** (×1.5 daño)
- **Planta** es fuerte contra **Agua** (×1.5 daño)

Las relaciones inversas causan × 0.75 daño.

## Mejoras Futuras Sugeridas

- [ ] Sistema de estadísticas variables por Pokémon
- [ ] Precisión de movimientos
- [ ] Efectos de estado (veneno, parálisis, etc.)
- [ ] Sistema de niveles y experiencia
- [ ] Múltiples combates/torneos
- [ ] Guardar y cargar partida
- [ ] Arte ASCII de los Pokémon

## Notas de integración

- En la versión inicial del código se utilizó el tipo “hielo”.
- Posteriormente se ajustó a “planta” para mantener coherencia con el informe académico,
  donde los tipos oficiales definidos son agua, fuego y planta.
- Estos cambios reflejan el proceso de integración y corrección realizado en la etapa final,
  asegurando consistencia entre código y documentación.

## Aprendizajes
  
- Gran parte del desarrollo inicial se realizó en local y luego se subió la carpeta completa a GitHub para centralizar el trabajo. 
- A partir de ese momento, los commits reflejan la etapa de integración, ajustes y documentación.  
- El uso de GitHub nos permitió aprender sobre control de versiones y trazabilidad, convirtiéndose en un aporte adicional al proceso académico del semestre.  
- Además, nos permitió mejorar la coordinación del equipo y reforzar la importancia de mantener la coherencia entre código e informe.
