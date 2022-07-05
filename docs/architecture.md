-- Design patterns --

- MVC
- Abstract factory
- Observer pattern
- Singleton
- Eventlistening
- ECS

- unique pointers
- exception handling
- logging
- project structure


-- Core --

- versioning
    - semver
    - cmake versioning into build system
- entity component system
- global event manager / handler
    - user input handling
    - ingame event handling
- ingame console
- physics engine
    - SAT collision detection
    - impulse based collisions
    - forces & movement & rotations
- multithreading
- networking
    - deterministic lockstep networked physics
    - server client networking
    - p2p networking
- audio
    - audiolistener component
    - spatial audio engine
- user interface system
    - screens, planes/panels, components/widgets
- performance profiling
- gameplay
    - player
        - player controller
    - platforms
        - random generation
        - movement
    - score
    - items/bonuses
    - background tiles
- game AI
    - finite state machine


-- Representation --

- texture manager/handler
    - maybe atlas texture
- entity component rendering
    - shaders
- GUI rendering
- resizable windows with ingame resolution (black bars)

-- Build --

- multiple platform targets (windows, linux, macos)
    - (maybe port to android)
    - (maybe server client)
