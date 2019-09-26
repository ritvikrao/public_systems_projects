# Readme

This is a list of tutorials that you can follow along to help aide you in assembly.

1. Don't commit any code here, as I may push updates (more tutorials or any minor corrections) as students request them.
2. [toc.md](./toc.md) contains a table of contents for easier navigation.

# Handy GDB Commands to Try to speed up debugging


```
x 0x4000cd  # Prints value at address 0x4000cd 
            # (Useful to see if you put the thing you thought in memory at that location)
```

```
print $rip # See contents of register (You can do this for all registers)
```

```
print /x $rip # See value in hex
```

```
print /t $rip # See value in binary
```

```
print *($r8)            # See the value of the thing that this register points to 
                        # (i.e. dereferencing the register)
```

### More useful gdb commands

- `br 10` puts a breakpoint at line 10
- `br _myfunction` puts a breakpoint at the label '_myfunction'
- `info registers` prints out registers
- `info frame` prints out current frame
- More here: https://cs61.seas.harvard.edu/wiki/Useful_GDB_commands
