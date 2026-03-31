# Sling N Salsa Show

Our entry to the game jam. A physics-based arcade game built with Unreal Engine 5.3 — launch yourself as a projectile to smash through waves of destructible targets before time runs out.

## Gameplay

- **Click to aim**, release to launch the player with a slingshot mechanic
- Destroy all target objects to clear each wave
- Waves increase in difficulty as the game progresses
- Use launch pads scattered across the level for extra boosts
- Dodge and navigate moving platforms

## Controls

| Input | Action |
|---|---|
| Left Click (hold) | Aim toward cursor |
| Left Click (release) | Launch |

## Project Structure

```
Source/SlingNSalsaShow/
  MyPawn.cpp              # Player character and slingshot launch logic
  JumperActor.cpp         # Launch pad mechanics
  SlingNSalsaShowGameMode # Wave progression and win condition
  Actors/
    MovingObjects.cpp     # Destructible targets with health system
    TriggerActors.cpp     # Wave objective triggers
  Components/
    PlatformMovement.cpp  # Moving platform component
  Widgets/                # UI widgets
```

## Built With

- Unreal Engine 5.3
- C++
