c = 0
with open("src/minishell.c", "r") as f:
    for line in f.readlines():
        c += 1
        if c < 141:
            continue
        if \
                not line.startswith("\t") \
                and len(line) > 5 \
                and not line.startswith("/") \
                        and not(line.startswith(" ")):
            print(line[:len(line) - 1], end=";\n")