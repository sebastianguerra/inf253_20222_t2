set pagination off
start

set $CANTIDAD_DE_MALLOCS_SIN_LIBERAR = 0

b malloc
commands
where
set $CANTIDAD_DE_MALLOCS_SIN_LIBERAR = $CANTIDAD_DE_MALLOCS_SIN_LIBERAR + 1
printf "Cantidad de mallocs sin liberar: %d\n", $CANTIDAD_DE_MALLOCS_SIN_LIBERAR
continue
end


b free
commands
where
set $CANTIDAD_DE_MALLOCS_SIN_LIBERAR = $CANTIDAD_DE_MALLOCS_SIN_LIBERAR - 1
printf "Cantidad de mallocs sin liberar: %d\n", $CANTIDAD_DE_MALLOCS_SIN_LIBERAR
continue
end

continue