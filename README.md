# Alloc stat

## nix

> Build
```sh
nix build github:Sigmapitech/alloc_stats
```

> Run
```sh
LD_PRELOAD=result/lib/liballoc_stats.so ls
```

## Non-nix

> Clone
```sh
git clone Sigmapitech/alloc_stats
cd alloc_stats
```

> Build
```sh
make
```

> Run
```sh
LD_PRELOAD=liballoc_stats.so ls
```
