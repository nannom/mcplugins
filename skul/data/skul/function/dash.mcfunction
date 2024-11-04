tp @s ~ ~ ~ ~ 0
execute if block ^ ^ ^1 air run tp @s ^ ^ ^0.8
execute if block ^ ^ ^1 light run tp @s ^ ^ ^0.8
playsound block.sand.place player @a ~ ~ ~ 1 1 1
scoreboard players add @s dash 1
attribute @s minecraft:generic.gravity base set 0