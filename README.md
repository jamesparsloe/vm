# vm

Following along with bytecode virtual machine from [Crafting Interpreters](https://craftinginterpreters.com/) by Bob Nystrom.

~~I'm diverging from the book slightly and trying to support some small subset of Python instead of Lox.~~ I'll do this when I have some more moving parts in place - otherwise it makes following the book too confusing.

```sh
make
./build/release/vm lox/foo.lox
```

For a debug build run

```sh
make debug
./build/debug/vm lox/foo.lox
```
