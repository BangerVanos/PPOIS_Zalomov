import sys
import pygame
from scripts import configs as cf
from scripts.game_states import GameStates as gs
from scripts.ui_elements.scopes import Cross, Sight
from scripts.ui_elements.camera import CameraGroup


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
    while running:
        clock.tick(cf.FPS)
        screen.fill('black')
        camera_group.custom_draw()
        ui_group.draw(screen)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
        pygame.display.flip()
        ui_group.update(mouse_pos=pygame.mouse.get_pos())
    if not running:
        return gs.MAIN_MENU
