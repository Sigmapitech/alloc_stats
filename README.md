# Alloc stat

## nix

> Run
```sh
nix run github:Sigmapitech/alloc_stats -- ls
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
