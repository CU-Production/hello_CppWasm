# hello_CppWasm
Embed WASM3 into Cpp

# Build rust wasm proj

```shell
$ cd test_proj
$ rustup target add wasm32-wasi
$ cargo build --release --target wasm32-wasi
```

# Optimize wasm bundle size

Add following to the `Cargo.toml`

```toml
# https://rustwasm.github.io/docs/book/reference/code-size.html
[profile.release]
lto = true
opt-level = 's'
# opt-level = 'z' # 'z' to even more aggressively optimize for size 
```
