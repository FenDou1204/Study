import sys

import pygame


def check_events():
    """an jian he shu biao shi jian"""
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.type == pygame.K_RIGHT:
                ship.rect.centerx += 1

def update_screen(ai_settings, screen, ship):
    """geng xin ping mu shang de tu xiang ,bing qiehuandao xin pingmu"""
    screen.fill(ai_settings.bg_color)
    ship.blitme()
    """dayin xin tu xiang """
    pygame.display.flip()
