# Vanilla

"Vanilla" means the level of change of the NHL94PC and NHL95PC SDL2 ports: the game's own code does exactly
what the original did, and only the host around it is new. Those ports run the retail code unchanged
("Nothing of the game is changed or patched"); this C port replaces the CPU, so the same promise is checked by
the frame hashes instead.

| Allowed (host) | Not in the vanilla game |
|---|---|
| Window, scaling, aspect, filters, fullscreen | Changes to game rules, rosters, teams, art or text |
| Settings file, key and pad bindings, controller setup | New items inside the game's own menus |
| Screenshots, audio capture, an FPS display | Fixing the original's bugs (the weight bug stays) |
| Fast-forward or pause as host keys | A speed other than the original's as the default |
| A headless runner, scripted input | Anything that changes `test` hashes without Abdul's approval |

Speed (decided 2026-11-03): the cartridge's slowdown is an **option, off by default**. Without it every pass of
the game loop takes one vblank (Smooth); with it a CPU cost model decides how many vblanks a pass takes, as the
cartridge does.

## Where this repository stands

* Game code: 1nput's v0.3.6 with the rule, roster-set and wide-view hooks taken back to the original path.
* Host: a settings menu (F9), controller setup, an FPS display, 4:3 or native pixels. Within vanilla.
* Slowdown: none (Smooth only). The option, off by default, belongs in the base first.
