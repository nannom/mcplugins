#변수 초기값 지정
execute as @a run scoreboard players add @s attack_cooldown 0
execute as @a run scoreboard players add @s double 0

#스탯 초기값 세팅
execute as @a run scoreboard players set @s attack_cooltime 12
execute as @a run scoreboard players set @s damage 150
execute as @a run scoreboard players set @s maxhealth 150

#아이템별 스텟 변화
execute as @a run (
    scoreboard players set @s attack_speed 0
    execute store result score bamboo items run clear @s turtle_helmet[custom_model_data=16] 0
    scoreboard players operation bamboo items *= bamboo_speed multiple
    scoreboard players operation @s attack_speed += bamboo items

    scoreboard players operation @s attack_speed *= @s attack_cooltime
    scoreboard players operation @s attack_speed /= percent multiple
    scoreboard players operation @s attack_cooltime -= @s attack_speed
)

#공격 관련 엔티티 위치 세팅
execute as @e[tag=attack] at @a[tag=player] run tp ^ ^ ^1
execute as @e[tag=click] at @a[tag=player] run tp ~ ~-1 ~

#공격시
execute as @e[tag=click] on attacker at @e[tag=attack] if score @s attack_cooldown matches ..0 run (
    particle minecraft:sweep_attack ~ ~1.2 ~ 0 0 0 0 1
    execute store result score now damage run scoreboard players get @a[tag=player,limit=1] damage
    tag @e[distance=..1.5,tag=mob] add _damagetarget
    execute as @e[tag=attack] at @s run playsound minecraft:entity.blaze.shoot player @a ~ ~ ~ 0.5 2 0.5
    scoreboard players operation @s attack_cooldown = @s attack_cooltime
)
execute as @e[tag=click] on attacker run execute as @e[tag=click] run data remove entity @s attack
execute as @a if score @s attack_cooldown matches 1.. run scoreboard players remove @s attack_cooldown 1

#몬스터 AI(예시)
execute as @e[tag=mob] at @s if score @s hp matches ..0 run kill @s
execute as @e[tag=mob] at @s if block ~ ~-0.01 ~ air run tp ~ ~-0.1 ~
execute as @e[tag=mob] at @s unless block ~ ~ ~ air run tp @s ~ ~0.1 ~

#대쉬 조건설정
#execute as @a at @s unless data entity @s {Inventory:[{Slot:-106b,id:"minecraft:leather_horse_armor"}]} if data entity @s {SelectedItem:{id:"minecraft:leather_horse_armor"}} run scoreboard players set @s dash 1
#execute as @a at @s unless data entity @s {Inventory:[{Slot:-106b,id:"minecraft:leather_horse_armor"}]} if data entity @s {SelectedItem:{id:"minecraft:leather_horse_armor"}} run item replace entity @s weapon.mainhand from entity @s weapon.offhand
#execute as @a at @s unless data entity @s {Inventory:[{Slot:-106b,id:"minecraft:leather_horse_armor"}]} run item replace entity @s weapon.offhand with minecraft:leather_horse_armor[minecraft:custom_model_data=1,minecraft:hide_tooltip={},minecraft:custom_name="_"]
execute as @e[tag=click] on target run (
    execute if data entity @s {SelectedItemSlot:0} run scoreboard players set @s dash 1
    execute if data entity @s {SelectedItemSlot:1} run function skul:skills
    execute if data entity @s {SelectedItemSlot:2} run function skul:skills
    execute if data entity @s {SelectedItemSlot:3} run function skul:obb
    execute if data entity @s {SelectedItemSlot:8} run function skul:swap
)
execute as @e[tag=click] if data entity @s interaction run data remove entity @s interaction

#대쉬
execute as @a at @s if score @s dash matches 1.. run function skul:dash

#대쉬 종료
execute as @a at @s if score @s dash matches 8.. run attribute @s minecraft:generic.gravity base set 0.08
execute as @a at @s if score @s dash matches 8.. run scoreboard players set @s dash 0

#점프 이팩트
execute as @a at @s if score @s jump matches 1.. run playsound minecraft:item.firecharge.use player @a ~ ~ ~ 0.5 1 0.5
scoreboard players set @a jump 0

#버튼 이벤트
execute as @a[tag=player] at @s run execute as @e[tag=selectobj,limit=1,sort=nearest,distance=..5] at @s run particle minecraft:flame ~ ~0.5 ~ 0 0 0 0 0
execute as @a if data entity @s {OnGround:1b} run scoreboard players set @s double 0

#아이템 클릭 이벤트
item replace entity @e[tag=test] armor.head from entity @a[tag=player,limit=1] player.cursor
execute if data entity @e[tag=test,limit=1] {ArmorItems:[{id:"minecraft:leather_horse_armor"}]} as @a run function skul:inv
execute if data entity @e[tag=test,limit=1] {ArmorItems:[{id:"minecraft:leather_horse_armor"}]} as @a run item replace entity @s player.cursor with air

#아이템 버림 이벤트
execute as @e[type=item] at @s run function skul:entity_item

execute as @e[type=item,tag=!canpickup] run data merge entity @s {PickupDelay:0s,Age:0s}
execute as @a if data entity @s Inventory[{Slot:-106b}] run item replace entity @s weapon.mainhand from entity @s weapon.offhand
execute as @a if data entity @s Inventory[{Slot:-106b}] run item replace entity @s weapon.offhand with minecraft:air