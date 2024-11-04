execute as @e[tag=_damagetarget] run scoreboard players operation @s hp -= @a[tag=player,limit=1] damage
execute as @e[tag=_damagetarget] at @s run playsound minecraft:entity.zombie.destroy_egg player @a ~ ~ ~ 0.5 0 0.5
execute as @e[tag=_damagetarget] run tp @s ~ ~ ~ facing entity @a[tag=player,limit=1]
execute as @e[tag=_damagetarget] at @s run tp @s ^ ^1 ^1
execute as @e[tag=_damagetarget] run tag @s remove _damagetarget