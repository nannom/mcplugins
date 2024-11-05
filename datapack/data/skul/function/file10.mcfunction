tag @s add _targetitem
execute if data entity @s {Item:{id:"minecraft:leather_horse_armor"}} run execute as @a run function skul:file11
execute if data entity @s {Item:{id:"minecraft:leather_horse_armor"}} run kill @s
execute if data entity @s {Item:{id:"minecraft:leather_helmet"}} run execute as @a unless data entity @s Inventory[{Slot:8b}] if data entity @s Inventory[{Slot:103b}] run item replace entity @s hotbar.8 from entity @e[tag=_targetitem,limit=1] container.0
execute if data entity @s {Item:{id:"minecraft:leather_helmet"}} run execute as @a unless data entity @s Inventory[{Slot:103b}] run item replace entity @s armor.head from entity @e[tag=_targetitem,limit=1] container.0
execute if data entity @s {Item:{id:"minecraft:leather_helmet"}} run kill @s
tag @s remove _targetitem
