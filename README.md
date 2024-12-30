# Galaga Inspired Game in C (SDL)

Written using SDL in C.

### TODO

- [x] Refactor bullet shooting method to not loop through entire bullet array.
- [ ] Collision detection and actually giving damage to enemies when they're shot. _Implement something that is more efficient than O(N^2)_
  - [ ] Build Quad Tree implementation. The tree needs to be able to handle values (enemies) that span multiple quadrants which adds a layer of complexity. (See `quadtree.c` for more TODOs)
    - [x] Add building functionality. (why was this so hard lol)
    - [ ] Add querying functionality.
    - [ ] Implement it into the actual game with live enemies.
- [x] Split code into multiple files.
- [x] Add enemies to shoot at (probably multiple enemies). _This is like kinda there, we'll update more later once collisions are working_
- [ ] Implement health, possibly do a health bar or hearts?
- [ ] Start menu?

### Nice to haves

- [ ] Better stars in the background that maybe move around a little when you move.
- [ ] Better or maybe even custom sprites.
- [ ] Make sure that my cpu utilization is at least okay.
- [ ] Add screenshots of gameplay (once there is gameplay).
- [ ] Make Makefile actually look decent.
- [ ] Convert quad tree to be stack allocated or at least do research into whether or not that's a good idea.
- [ ] Ensure good and helpful comments throughout the code.
- [x] Standardize code style.
- [x] Pause game when unfocused.

### Notes

- Run this to format all code

  ```
  clang-format --style="{BasedOnStyle: LLVM, UseTab: Never, IndentWidth: 4, TabWidth: 4}" -i src/*.c src/*.h
  ```

- Do **not** typedef structs or enums for this codebase.
- Assets procured from [here](https://foozlecc.itch.io/void-fleet-pack-2)
- Yes, I know a Quad Tree was definitely not required for this to run smoothly. But it's a good learning opportunity so why not.
