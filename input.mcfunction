execute as @a at @s if data entity @s Inventory[{Slot:-106b,id:"minecraft:diamond"}] run (
    scoreboard players add @s a 1
    tp ~ ~1 ~
)
execute as @e[type=minecraft:item,nbt={}] run (
    kill @s
)