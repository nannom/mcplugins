tag @s add _targetitem
execute if data entity @s {Item:{id:"minecraft:leather_horse_armor"}} run execute as @a run function skul:file12
execute if data entity @s {Item:{id:"minecraft:leather_horse_armor"}} run kill @s
execute if data entity @s {Item:{id:"minecraft:leather_helmet"}} run function skul:file13
tag @s remove _targetitem
