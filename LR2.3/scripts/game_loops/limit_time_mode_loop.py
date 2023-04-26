import sys
import pygame
import random
from scripts import configs as cf
from scripts.game_states import GameStates as gs
from scripts.ui_elements.scopes import Cross, Sight
from scripts.ui_elements.camera import CameraGroup
from scripts.sprites.enemies import Enemy, MovementDirection

screen = pygame.display.set_mode((cf.SCREEN_WIDTH, cf.SCREEN_HEIGHT))
icon_image = pygame.image.load(cf.ICON_DIR)
pygame.display.set_icon(icon_image)
clock = pygame.time.Clock()
pygame.event.set_grab(True)


def limit_time_mode():
    time = cf.BASE_GAME_TIME
    pygame.display.set_caption('TankHuhn limit time mode')
    pygame.display.set_icon(icon_image)
    ui_group = pygame.sprite.Group()
    ui_group.add(Cross(), Sight())
    camera_group = CameraGroup(cf.BACKGROUND_DIR['bg_day'])
    running = True
    spawn_counter = 0
    while running:
        if spawn_counter % (cf.FPS * 15) == 0:
            Enemy(camera_group, 0, random.randint(0, cf.SCREEN_HEIGHT), cf.ENEMY_SPRITES_IMG['enemy_tank_1'],
                  (15, 7), 100, MovementDirection.RIGHT, cf.MapSize.STANDARD)
        spawn_counter += 1
        screen.fill('black')
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
        camera_group.custom_draw()
        camera_group.update()
        ui_group.draw(screen)
        ui_group.update(mouse_pos=pygame.mouse.get_pos())
        pygame.display.flip()
        clock.tick(cf.FPS)
    if not running:
        return gs.MAIN_MENU
