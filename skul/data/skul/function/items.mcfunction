scoreboard players set @s attack_speed 0
execute store result score bamboo items run clear @s turtle_helmet[custom_model_data=16] 0
scoreboard players operation bamboo items *= bamboo_speed multiple
scoreboard players operation @s attack_speed += bamboo items

scoreboard players operation @s attack_speed *= @s attack_cooltime
scoreboard players operation @s attack_speed /= percent multiple
scoreboard players operation @s attack_cooltime -= @s attack_speed