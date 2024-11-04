execute as @a if data entity @s {OnGround:1b} run scoreboard players set @s double 0
execute as @a if score @s sneak matches 1.. if data entity @s {OnGround:0b} if score @s double matches 0 run effect give @s minecraft:levitation 1 10 true
execute as @a if score @s sneak matches 1.. if data entity @s {OnGround:0b} if score @s double matches 0 at @s run particle minecraft:cloud ~ ~ ~ 0.5 0.0 0.5 0 20
execute as @a if score @s sneak matches 1.. if data entity @s {OnGround:0b} if score @s double matches 0 at @s run playsound minecraft:item.firecharge.use player @a ~ ~ ~ 1 1 1
execute as @a if score @s sneak matches 1.. if data entity @s {OnGround:0b} run scoreboard players set @s double 1
execute as @a if score @s sneak matches 1.. run scoreboard players set @s sneak 0