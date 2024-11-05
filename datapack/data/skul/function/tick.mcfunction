execute as @a run function skul:file1

#공격 관련 엔티티 위치 세팅
execute as @e[tag=attack] at @a[tag=player] run tp ^ ^ ^1
execute as @e[tag=click] at @a[tag=player] run tp ~ ~-1 ~

#공격시
execute as @e[tag=click] on attacker at @e[tag=attack] if score @s attack_cooldown matches ..0 run function skul:file3
execute as @e[tag=click] on attacker run execute as @e[tag=click] run data remove entity @s attack
execute as @a if score @s attack_cooldown matches 1.. run scoreboard players remove @s attack_cooldown 1

#몬스터 AI[임시]
function skul:file4

#대쉬 조건설정
#execute as @a at @s unless data entity @s {Inventory:[{Slot:-106b,id:"minecraft:leather_horse_armor"}]} if data entity @s {SelectedItem:{id:"minecraft:leather_horse_armor"}} run scoreboard players set @s dash 1
#execute as @a at @s unless data entity @s {Inventory:[{Slot:-106b,id:"minecraft:leather_horse_armor"}]} if data entity @s {SelectedItem:{id:"minecraft:leather_horse_armor"}} run item replace entity @s weapon.mainhand from entity @s weapon.offhand
#execute as @a at @s unless data entity @s {Inventory:[{Slot:-106b,id:"minecraft:leather_horse_armor"}]} run item replace entity @s weapon.offhand with minecraft:leather_horse_armor[minecraft:custom_model_data=1,minecraft:hide_tooltip={},!minecraft:item_name]
execute as @e[tag=click] on target run function skul:file5
execute as @e[tag=click] if data entity @s interaction run data remove entity @s interaction

#대쉬
execute as @a at @s if score @s dash matches 1.. run function skul:file6

#대쉬 종료
execute as @a at @s if score @s dash matches 8.. run function skul:file7

#점프 이팩트
execute as @a at @s if score @s jump matches 1.. run function skul:file8
scoreboard players set @a jump 0

#버튼 이벤트
execute as @a[tag=player] at @s run execute as @e[tag=selectobj,limit=1,sort=nearest,distance=..5] at @s run particle minecraft:flame ~ ~0.5 ~ 0 0 0 0 0
execute as @a if data entity @s {OnGround:1b} run scoreboard players set @s double 0

#아이템 클릭 이벤트
item replace entity @e[tag=test] armor.head from entity @a[tag=player,limit=1] player.cursor
execute if data entity @e[tag=test,limit=1] {ArmorItems:[{id:"minecraft:leather_horse_armor"}]} as @a run function skul:file9

#아이템 버림 이벤트
execute as @e[type=item] at @s run function skul:file10

execute as @e[type=item,tag=!canpickup] run data merge entity @s {PickupDelay:0s,Age:0s}
execute as @a if data entity @s Inventory[{Slot:-106b}] run function skul:file12