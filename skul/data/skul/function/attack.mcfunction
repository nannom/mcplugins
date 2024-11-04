particle minecraft:sweep_attack ~ ~1.2 ~ 0 0 0 0 1
execute store result score now damage run scoreboard players get @a[tag=player,limit=1] damage
tag @e[distance=..1.5,tag=mob] add _damagetarget
execute as @e[tag=attack] at @s run playsound minecraft:entity.blaze.shoot player @a ~ ~ ~ 0.5 2 0.5
scoreboard players operation @s attack_cooldown = @s attack_cooltime