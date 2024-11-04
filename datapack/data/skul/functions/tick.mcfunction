execute as @a at @s if data entity @s Inventory[{Slot:-106b,id:"minecraft:diamond"}] run function skul:file1
execute as @e[type=minecraft:item,nbt={}] run function skul:file2