execute if data entity @s {SelectedItemSlot:0} run scoreboard players set @s dash 1
execute if data entity @s {SelectedItem:{id:"minecraft:diamond_pickaxe"}} run function skul:skills
execute if data entity @s {SelectedItemSlot:3} run function skul:obb
execute if data entity @s {SelectedItemSlot:8} run function skul:swap
