# Galaga Inspired Game in C (SDL)

Written using SDL in C and that's about it.

### TODO

- [ ] Refactor bullet shooting method to not loop through entire bullet array
- [x] Split code into multiple files
- [ ] Add enemies to shoot at (probably multiple enemies)
- [ ] Implement health, possibly do a health bar or hearts?
- [ ] Start menu?

### Nice to haves

- [ ] Better stars in the background that maybe move around a little when you move
- [ ] Better or maybe even custom sprites
- [ ] Make sure that my cpu utilization is at least okay
- [ ] Add screenshots of gameplay (once there is gameplay)
- [x] Standardize code style
- [x] Pause game when unfocused

### Notes

- Run this to format all code

  ```
  clang-format --style="{BasedOnStyle: LLVM, UseTab: Never, IndentWidth: 4, TabWidth: 4}" -i src/*.c src/*.h
  ```

- Do **not** typedef structs for this codebase.
