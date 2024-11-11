# 345-warzone

Implementation of the Warzone game for COMP345, Fall 2024 semester @Concordia.

Team: endgame.exe

Team members:

| Full Name           | Student ID | Github Handle  |
| ------------------- | ---------- | -------------- |
| Ralph Elhage        | 40131981   | CloudedByLight |
| Dalia Betinjaneh    | 40200966   | daliabtnj      |
| Ayman Bohsali       | 40231988   | AymBohs        |
| Aymane Arfaoui      | 40248780   | Aymane-Arfaoui |
| Mathew Sakellarakos | 40248474   | ms8074         |
| Alexander El Ghaoui | 40200062   | Ghawi25        |

## Running the code

### Main Driver

1. Make sure to comment out the main functions of all other Driver files.
2. From terminal, go to the project root directory and type cmd:

`g++ -std=c++11 -o warzone MainDriver.cpp Map.cpp MapLoader.cpp MapDriver.cpp Player.cpp PlayerDriver.cpp Order.cpp OrdersDriver.cpp Cards.cpp CardsDriver.cpp GameEngine.cpp GameEngineDriver.cpp`

This will generate a warzone executable file.

3. Then, depending on your OS:

- Windows run:

```
./warzone
```

- macOS run:

```
./warzone.exe
```

### Part 1: Map

1. From terminal, go to the project root directory and type cmd:

```
g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp MapDriver.cpp
```

This will generate a warzone executable file.

2. Then, depending on your OS:git

- Windows run:

```
./warzone
```

- macOS run:

```
./warzone
```

### Part 2: Player

1. From terminal, go to the project root directory and type cmd:

`g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp Player.cpp Cards.cpp Order.cpp PlayerDriver.cpp`

This will generate a warzone executable file.

2. Then, depending on your OS:

- Windows run:

```
./warzone
```

- macOS run:

```
./warzone.exe
```

### Part 3: Orders

1. From terminal, go to the project root directory and type cmd:

`g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp Player.cpp Order.cpp Cards.cpp OrdersDriver.cpp`

This will generate a warzone executable file.

2. Then, depending on your OS:

- Windows run:

```
./warzone
```

- macOS run:

```
./warzone.exe
```

### Part 4: Cards

1. From terminal, go to the project root directory and type cmd:

`g++ -std=c++11 -o warzone Map.cpp MapLoader.cpp Cards.cpp CardsDriver.cpp Order.cpp Player.cpp`

This will generate a warzone executable file.

2. Then, depending on your OS:

- Windows run:

```
./warzone
```

- macOS run:

```
./warzone.exe
```

### Part 5: Game Engine

1. From terminal, go to the project root directory and type cmd:

`g++ -std=c++11 -o warzone GameEngine.cpp GameEngineDriver.cpp Map.cpp Maploader.cpp CommandProcessing.cpp Player.cpp Order.cpp Cards.cpp`

This will generate a warzone executable file.

2. Then, depending on your OS:

- Windows run:

```
./warzone
```

- macOS run:

```
./warzone.exe
```
