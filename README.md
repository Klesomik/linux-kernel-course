# Simple char device

phonebook

### Start

```bash
> make
> make load
> make nod
```

### Run

```bash
> cc test.c -o test
> ./test
> sudo dmesg | grep phonebook
```

### Stop

```bash
> make unload
> make clean
```