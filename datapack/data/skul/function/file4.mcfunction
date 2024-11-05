execute as @e[tag=mob] at @s if score @s hp matches ..0 run kill @s
execute as @e[tag=mob] at @s if block ~ ~-0.01 ~ air run tp ~ ~-0.1 ~
execute as @e[tag=mob] at @s unless block ~ ~ ~ air run tp @s ~ ~0.1 ~
