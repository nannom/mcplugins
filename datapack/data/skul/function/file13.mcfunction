execute as @a unless data entity @s Inventory[{Slot:8b}] if data entity @s Inventory[{Slot:103b}] run item replace entity @s hotbar.8 from entity @e[tag=_targetitem,limit=1] container.0
execute as @a unless data entity @s Inventory[{Slot:103b}] run item replace entity @s armor.head from entity @e[tag=_targetitem,limit=1] container.0
kill @s
