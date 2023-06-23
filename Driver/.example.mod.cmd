cmd_/home/ninebro/workspace/Driver/example.mod := printf '%s\n'   example.o | awk '!x[$$0]++ { print("/home/ninebro/workspace/Driver/"$$0) }' > /home/ninebro/workspace/Driver/example.mod
