kill @e[type=!minecraft:player]
#summon minecraft:interaction ~ ~-1 ~ {Tags:[click],width:4.0f,height:4.0f}
execute as @a run attribute @s minecraft:generic.attack_speed base set 100
summon marker ~ ~1 ~ {Tags:[attack]}
summon armor_stand ~ ~ ~ {Tags:[test]}
execute as @a run attribute @s minecraft:generic.jump_strength base set 0.8
scoreboard objectives add attack_cooltime dummy
scoreboard objectives add attack_cooldown dummy
scoreboard objectives add hp dummy
scoreboard objectives add damage dummy
scoreboard objectives add dash dummy
scoreboard objectives add double dummy
scoreboard objectives add sneak minecraft.custom:minecraft.sneak_time
scoreboard objectives add jump minecraft.custom:minecraft.jump
scoreboard objectives add maxhealth dummy
scoreboard objectives add items dummy
scoreboard objectives add multiple dummy
scoreboard players set percent multiple 100
scoreboard players set bamboo_speed multiple 20
scoreboard objectives add attack_speed dummy