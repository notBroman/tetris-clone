# tetris-clone
A clone of the Tetris game made without an engine

# TODO

- [ ] Physics
    - [ ] Make block fall
    - [ ] Move block
    - [ ] Rotate block
    - [ ] Collisions

- [ ] Rendering
    - [x] Setup Vulkan
        - [x] Z buffering
    - [ ] Render submitted data
    - [ ] Batch rendering
    - [ ] Texture Atlas
    - [ ] ~~UI Rendering~~
      - [ ] ~~Text Rendering~~
        - [ ] ~~Rectangle Packing?~~
        - [ ] ~~Layout System (not resizable, 4:3 aspect ratio only)~~
    - [ ] Post Effects?
    - [ ] Blit to screen
    - [ ] Render game state to screen


- [ ] Systems
    - [ ] Manage block assets
    - [ ] Pick a random block
    - [ ] Keep track of score
    - [ ] Leaderboard
    - [ ] ~~Events~~
    - [ ] ~~Input handling~~

- [ ] Game logic
    - [ ] Keep track of placed blocks
    - [ ] Delete full rows

# Renderer

Renderer uses Vulkan 
