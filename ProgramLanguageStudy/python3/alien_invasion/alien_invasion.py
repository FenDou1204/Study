import sys
import pygame

from settings import Settings
from ship import Ship
import game_functions as gf
def run_game():
    #初始化游戏，创建运行窗口
    pygame.init()
    ai_settings = Settings()
    #game monitor
    screen = pygame.display.set_mode((ai_settings.screen_width, ai_settings.screen_height))
    pygame.display.set_caption("Alien")

    ship = Ship(screen)

    while True:
        #监视键盘鼠标
        gf.check_events()
        #da yin xin jie mian
        gf.update_screen(ai_settings, screen, ship)

run_game()

