import pygame
import file_path


SCREEN_WIDTH = 1600
SCREEN_HEIGHT = 900

FPS = 60

clock = pygame.time.Clock()

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Advanced Moorhuhn')
icon_image = pygame.image.load(file_path.ICON_DIR)
pygame.display.set_icon(icon_image)


def main():
    running = True

    while running:
        clock.tick(FPS)

        # event handler
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

    pygame.quit()
